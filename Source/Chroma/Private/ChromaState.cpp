#include "ChromaState.h"
#include "ChromaSettings.h"
#include "ActorFolder.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Engine/Level.h"
#include "UObject/Package.h"
#include "UObject/MetaData.h"
#include "Editor.h"
#include "Editor/TransBuffer.h"
#include "Misc/Change.h"

namespace Chroma
{
    static uint64 ColorRevision=1;
    void RequestViewportRefresh() { ++ColorRevision; }
    uint64 ViewportRevision() { return ColorRevision; }
    static const FName ActorKey(TEXT("Chroma.Assignment.V1"));
    static const FString FolderPrefix(TEXT("Chroma.Folder.V1/"));
    FTarget ActorTarget(const AActor* Actor)
    {
        FTarget T;
        if(IsValid(Actor) && !Actor->IsTemplate() && Actor->GetWorld() && Actor->GetWorld()->WorldType==EWorldType::Editor)
        { T.Object=const_cast<AActor*>(Actor); T.Key=ActorKey; }
        return T;
    }
    FTarget FolderTarget(UWorld* World,const FFolder& Folder)
    {
        FTarget T;
        if(!World || World->WorldType!=EWorldType::Editor || Folder.IsNone()) return T;
        if(UActorFolder* Native=Folder.GetActorFolder()) { T.Object=Native; T.Key=ActorKey; }
        else if(ULevel* Level=(Folder.IsRootObjectValid() ? Folder.GetRootObjectAssociatedLevel() : World->PersistentLevel.Get()))
        { T.Object=Level; T.Key=FName(*(FolderPrefix+Folder.GetPath().ToString())); }
        return T;
    }
    FString Read(const FTarget& T)
    {
        UObject* O=T.Object.Get();
        return O ? O->GetPackage()->GetMetaData().GetValue(O,T.Key) : FString();
    }
    static void Restore(UObject* O,FName Key,const FString& Value)
    {
        if(!IsValid(O)) return;
        auto& Meta=O->GetPackage()->GetMetaData();
        if(Value.IsEmpty()) Meta.RemoveValue(O,Key); else Meta.SetValue(O,Key,*Value);
        O->GetPackage()->MarkPackageDirty();
        RequestViewportRefresh();
    }
    class FAssignmentChange final : public FCommandChange
    {
        FName Key; FString Before,After;
    public:
        FAssignmentChange(FName K,FString B,FString A):Key(K),Before(MoveTemp(B)),After(MoveTemp(A)) {}
        virtual void Apply(UObject* O) override { Restore(O,Key,After); }
        virtual void Revert(UObject* O) override { Restore(O,Key,Before); }
        virtual FString ToString() const override { return TEXT("Chroma color assignment"); }
    };
    void Write(const FTarget& T,const FString& Value)
    {
        UObject* O=T.Object.Get(); if(!O) return;
        const FString Before=Read(T); if(Before==Value) return;
        if(GUndo) GUndo->StoreUndo(O,MakeUnique<FAssignmentChange>(T.Key,Before,Value));
        Restore(O,T.Key,Value);
    }
    FString Custom(const FLinearColor& Color)
    { return TEXT("C:")+Color.ToFColor(true).ToHex().Left(6); }
    FChromaResolvedColor Decode(const FString& Value)
    {
        FChromaResolvedColor R; R.Assignment=Value;
        if(Value.StartsWith(TEXT("P:")))
        {
            if(!FGuid::Parse(Value.Mid(2),R.PresetId) || !R.PresetId.IsValid()) { R.Name=TEXT("Invalid preset"); return R; }
            for(const auto& P:GetDefault<UChromaSettings>()->Palette) if(P.Id==R.PresetId)
            { R.bHasColor=true; R.Color=P.Color; R.Name=P.Name; return R; }
            R.bMissingPreset=true; R.Name=TEXT("Missing preset");
        }
        else if(Value.StartsWith(TEXT("C:")) && Value.Len()==8)
        { R.bHasColor=true; R.Color=FLinearColor::FromSRGBColor(FColor::FromHex(Value.Mid(2))); R.Name=TEXT("Custom #")+Value.Mid(2); }
        else R.Name=TEXT("No Color");
        return R;
    }
    FChromaResolvedColor ResolveFolder(UWorld* World,FFolder Folder)
    {
        bool Inherited=false;
        while(!Folder.IsNone())
        {
            const FString Value=Read(FolderTarget(World,Folder));
            if(!Value.IsEmpty())
            { auto R=Decode(Value); R.bInherited=Inherited; R.Source=Folder.GetPath().ToString(); return R; }
            Folder=Folder.GetParent(); Inherited=true;
        }
        return Decode(FString());
    }
    FChromaResolvedColor ResolveActor(const AActor* Actor)
    {
        if(!ActorTarget(Actor).IsValid()) return Decode(FString());
        const FString Value=Read(ActorTarget(Actor));
        if(!Value.IsEmpty()) return Decode(Value);
        auto R=ResolveFolder(Actor->GetWorld(),Actor->GetFolder());
        R.bInherited=!R.Assignment.IsEmpty(); return R;
    }
    void FolderMoved(UWorld& World,const FFolder& Old,const FFolder& New)
    {
        RequestViewportRefresh();
        // Native actor folders have stable object identities. Legacy folders use
        // paths on their owning level. Migrate the whole subtree, transactionally.
        if(New.GetActorFolder()) return;
        FTarget A=FolderTarget(&World,Old), B=FolderTarget(&World,New);
        UObject* O=A.Object.Get(); if(!O || !B.IsValid()) return;
        auto& Meta=O->GetPackage()->GetMetaData();
        const auto* Map=Meta.ObjectMetaDataMap.Find(FSoftObjectPath(O)); if(!Map) return;
        TArray<TPair<FName,FString>> Moves;
        const FString Prefix=FolderPrefix+Old.GetPath().ToString();
        for(const auto& P:*Map) if(P.Key.ToString()==Prefix || P.Key.ToString().StartsWith(Prefix+TEXT("/"))) Moves.Add(P);
        for(const auto& P:Moves)
        {
            FTarget From=A; From.Key=P.Key; FTarget To=B;
            To.Key=FName(*(FolderPrefix+New.GetPath().ToString()+P.Key.ToString().Mid(Prefix.Len())));
            if(To.Object==From.Object && To.Key==From.Key) continue;
            Write(To,P.Value); Write(From,FString());
        }
    }
    void FolderDeleted(UWorld& World,const FFolder& Folder)
    {
        RequestViewportRefresh();
        // Native folder metadata follows the folder object through deletion/Undo.
        if(!Folder.GetActorFolder()) Write(FolderTarget(&World,Folder),FString());
    }
}

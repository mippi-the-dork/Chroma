#pragma once
#include "ChromaAPI.h"
#include "Folder.h"
class UWorld;
namespace Chroma
{
    struct FTarget
    {
        TWeakObjectPtr<UObject> Object;
        FName Key;
        bool IsValid() const { return Object.IsValid() && !Key.IsNone(); }
    };
    // Revision changes are coalesced by the editor module before refreshing rendering.
    void RequestViewportRefresh();
    uint64 ViewportRevision();
    FTarget ActorTarget(const AActor* Actor);
    FTarget FolderTarget(UWorld* World,const FFolder& Folder);
    FString Read(const FTarget& Target);
    void Write(const FTarget& Target,const FString& Assignment);
    FChromaResolvedColor Decode(const FString& Assignment);
    FChromaResolvedColor ResolveFolder(UWorld* World,FFolder Folder);
    FString Custom(const FLinearColor& Color);
    void FolderMoved(UWorld& World,const FFolder& Old,const FFolder& New);
    void FolderDeleted(UWorld& World,const FFolder& Folder);
}

// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ChromaAPI.h"
#include "ChromaSettings.h"
#include "Components/PrimitiveComponent.h"
#include "Editor.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "HAL/IConsoleManager.h"
#include "PrimitiveSceneProxy.h"
#include "SceneView.h"
#include "SceneViewExtension.h"
#include "Selection.h"

// Editor presentation only. Never writes a component property, selection flag,
// editor style preference, material, or custom-depth setting.
class FChromaSelectionOutline final : public FSceneViewExtensionBase
{
    struct FApplied
    {
        FPrimitiveSceneProxy* Proxy=nullptr; // Identity only; never dereference a saved proxy.
        uint8 Index=0;
    };
    TMap<TWeakObjectPtr<UPrimitiveComponent>,FApplied> Applied;
    TMap<FString,uint8> Slots;
    TWeakObjectPtr<UWorld> World;
    IConsoleVariable* EnableColors=nullptr;
    int32 PreviousEnable=0;
    bool bChangedEnable=false;
    bool bStopped=false;

    bool AcquireColors()
    {
        if(!EnableColors)
        {
            EnableColors=IConsoleManager::Get().FindConsoleVariable(TEXT("r.Viewport.EnableSelectionOutlineColors"));
            if(!EnableColors) return false;
            PreviousEnable=EnableColors->GetInt();
            if(PreviousEnable==0)
            {
                EnableColors->Set(1,ECVF_SetByCode);
                bChangedEnable=EnableColors->GetInt()==1;
            }
        }
        return EnableColors->GetInt()!=0;
    }
    void Restore()
    {
        for(const auto& Entry:Applied)
            if(UPrimitiveComponent* Component=Entry.Key.Get())
                if(Component->SceneProxy && Component->SceneProxy==Entry.Value.Proxy)
                    Component->SceneProxy->SetSelectionOutlineColorIndex_GameThread(Component->SelectionOutlineColorIndex);
        Applied.Reset(); Slots.Reset(); World.Reset();
        if(EnableColors && bChangedEnable && EnableColors->GetInt()==1)
            EnableColors->Set(PreviousEnable,ECVF_SetByCode);
        EnableColors=nullptr; bChangedEnable=false;
    }
public:
    explicit FChromaSelectionOutline(const FAutoRegister& AutoRegister)
        : FSceneViewExtensionBase(AutoRegister) {}

    void Stop() { bStopped=true; Restore(); }

    // Called by the editor ticker and before view setup. Examines only selected
    // actors, including their current components after construction-script rebuilds.
    bool Update()
    {
        UWorld* CurrentWorld=GEditor ? GEditor->GetEditorWorldContext().World() : nullptr;
        if(bStopped || !GEditor || GEditor->PlayWorld || !CurrentWorld ||
            CurrentWorld->WorldType!=EWorldType::Editor || !GetDefault<UChromaSettings>()->bTintSelectionOutlines)
        {
            const bool bChanged=!Applied.IsEmpty(); Restore(); return bChanged;
        }
        bool bChanged=false;
        if(World.IsValid() && World.Get()!=CurrentWorld) { Restore(); bChanged=true; }
        World=CurrentWorld;
        TMap<TWeakObjectPtr<UPrimitiveComponent>,FString> Desired;
        TSet<FString> Colors;
        bool Reserved[8]={};
        for(FSelectionIterator It(*GEditor->GetSelectedActors());It;++It)
        {
            AActor* Actor=Cast<AActor>(*It);
            if(!IsValid(Actor) || Actor->GetWorld()!=CurrentWorld) continue;
            const FChromaResolvedColor Resolved=Chroma::ResolveActor(Actor);
            TInlineComponentArray<UPrimitiveComponent*> Components;
            Actor->GetComponents(Components);
            for(UPrimitiveComponent* Component:Components)
            {
                if(!IsValid(Component) || !Component->SceneProxy) continue;
                // Respect explicit component outline indices owned by other tools.
                const uint8 Existing=Component->SelectionOutlineColorIndex;
                if(Existing!=0)
                {
                    if(Existing<8) Reserved[Existing]=true;
                    continue;
                }
                if(!Resolved.bHasColor) continue;
                FColor Color=Resolved.Color.ToFColor(true); Color.A=255;
                const FString Key=Color.ToHex();
                Desired.Add(Component,Key); Colors.Add(Key);
            }
        }
        const TMap<FString,uint8> PreviousSlots=Slots;
        for(auto It=Slots.CreateIterator();It;++It)
            if(!Colors.Contains(It.Key()) || Reserved[It.Value()]) It.RemoveCurrent();
        bool Occupied[8]={};
        for(int32 I=2;I<8;++I) Occupied[I]=Reserved[I];
        for(const auto& Entry:Slots) Occupied[Entry.Value]=true;
        TArray<FString> Sorted=Colors.Array(); Sorted.Sort();
        for(const FString& Color:Sorted)
        {
            if(Slots.Contains(Color)) continue;
            for(uint8 I=2;I<8;++I) if(!Occupied[I])
            { Slots.Add(Color,I); Occupied[I]=true; break; }
        }
        if(PreviousSlots.Num()!=Slots.Num()) bChanged=true;
        for(const auto& Entry:Slots)
        {
            const uint8* Old=PreviousSlots.Find(Entry.Key);
            if(!Old || *Old!=Entry.Value) bChanged=true;
        }
        if(Slots.IsEmpty() || !AcquireColors())
        {
            bChanged|=!Applied.IsEmpty(); Restore(); return bChanged;
        }
        for(auto It=Applied.CreateIterator();It;++It)
        {
            UPrimitiveComponent* Component=It.Key().Get();
            const FString* Color=Desired.Find(It.Key());
            if(!Component || !Component->SceneProxy || Component->SceneProxy!=It.Value().Proxy ||
                !Color || !Slots.Contains(*Color))
            {
                if(Component && Component->SceneProxy && Component->SceneProxy==It.Value().Proxy)
                    Component->SceneProxy->SetSelectionOutlineColorIndex_GameThread(Component->SelectionOutlineColorIndex);
                It.RemoveCurrent(); bChanged=true;
            }
        }
        for(const auto& Entry:Desired)
        {
            const uint8* Index=Slots.Find(Entry.Value);
            UPrimitiveComponent* Component=Entry.Key.Get();
            if(!Index || !Component || !Component->SceneProxy) continue;
            FApplied* Old=Applied.Find(Entry.Key);
            if(!Old || Old->Proxy!=Component->SceneProxy || Old->Index!=*Index)
            {
                // Deliberately use the proxy's color-only API. The component setter
                // also forces selection and changes the serialized bWantsEditorEffects flag.
                Component->SceneProxy->SetSelectionOutlineColorIndex_GameThread(*Index);
                FApplied Value; Value.Proxy=Component->SceneProxy; Value.Index=*Index;
                Applied.Add(Entry.Key,Value); bChanged=true;
            }
        }
        return bChanged;
    }

    virtual void SetupView(FSceneViewFamily& Family,FSceneView& View) override
    {
        Update();
        const UWorld* EditorWorld=World.Get();
        if(bStopped || !EditorWorld || Family.Scene!=EditorWorld->Scene || View.bIsGameView) return;
        for(const auto& Entry:Slots)
            View.AdditionalSelectionOutlineColors[Entry.Value-2]=FLinearColor::FromSRGBColor(FColor::FromHex(Entry.Key));
    }
};

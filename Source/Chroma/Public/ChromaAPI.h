// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
class AActor;
class UWorld;
struct FFolder;
/** Read-only integration surface for optional consumers such as Sift. Editor actors only. */
struct CHROMA_API FChromaResolvedColor
{
    bool bHasColor=false;
    bool bInherited=false;
    bool bMissingPreset=false;
    FGuid PresetId;
    FLinearColor Color=FLinearColor::Transparent;
    FString Name;
    FString Source;
    FString Assignment;
};
namespace Chroma
{
    CHROMA_API FChromaResolvedColor ResolveActor(const AActor* Actor);
    CHROMA_API FChromaResolvedColor ResolveFolder(UWorld* World, FFolder Folder);
}

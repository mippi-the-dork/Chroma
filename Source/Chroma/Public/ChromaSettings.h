// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "ChromaSettings.generated.h"

USTRUCT()
struct CHROMA_API FChromaPreset
{
    GENERATED_BODY()
    // Identity is deliberately not editable. Renaming/recoloring preserves references.
    UPROPERTY(VisibleAnywhere, Category="Color") FGuid Id;
    UPROPERTY(EditAnywhere, Category="Color") FString Name;
    UPROPERTY(EditAnywhere, Category="Color", meta=(HideAlphaChannel)) FLinearColor Color = FLinearColor::White;
};

UCLASS(Config=Chroma, DefaultConfig, meta=(DisplayName="Chroma"))
class CHROMA_API UChromaSettings : public UDeveloperSettings
{
    GENERATED_BODY()
public:
    UChromaSettings();
    UPROPERTY(Config, EditAnywhere, Category="Project Palette", meta=(TitleProperty="Name"))
    TArray<FChromaPreset> Palette;
    UPROPERTY(Config, EditAnywhere, Category="Outliner", meta=(DisplayName="Tint Outliner Icons", ToolTip="Tint native actor and folder icons with their effective Chroma color. Unassigned items keep their normal appearance."))
    bool bTintOutlinerIcons=true;
    UPROPERTY(Config, EditAnywhere, Category="Viewport", meta=(DisplayName="Tint Selection Outlines", ToolTip="Use Chroma colors for selected actors. Up to six distinct colors at once; additional colors keep the normal Unreal outline."))
    bool bTintSelectionOutlines=true;
    virtual FName GetSectionName() const override { return TEXT("Chroma"); }
    virtual FName GetCategoryName() const override { return TEXT("Plugins"); }
    virtual void PostEditChangeProperty(FPropertyChangedEvent& Event) override;
    virtual void PostEditUndo() override;
};

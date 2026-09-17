#pragma once
#include "ChromaState.h"
#include "SLevelViewport.h"
#include "LevelEditorViewport.h"
#include "Editor.h"
#include "EngineUtils.h"
#include "GameFramework/Actor.h"
#include "UnrealClient.h"
#include "GameFramework/ActorPrimitiveColorHandler.h"
#include "Framework/Application/SlateApplication.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/SOverlay.h"
#include "Widgets/SViewport.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Brushes/SlateRoundedBoxBrush.h"
#include "Styling/AppStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Widgets/Images/SImage.h"

/** Display only. Never consumes mouse input or changes selection. */
class SChromaViewportHover final : public SCompoundWidget
{
    TWeakPtr<SLevelViewport> View;
    TSharedPtr<SWidget> Badge;
    TSharedPtr<STextBlock> ActorLabel,ColorLabel,HexLabel,SourceLabel;
    // Owned brushes remain valid for the lifetime of the overlay.
    FSlateRoundedBoxBrush CardBrush{FLinearColor(.028f,.028f,.028f,.98f),6.f,FLinearColor(.12f,.12f,.12f,1),1.f};
    FSlateRoundedBoxBrush SwatchBrush{FLinearColor::White,4.f};
    FString DisplayedText;
    FLinearColor Color=FLinearColor::Gray;
    double NextProbe=0;
    void Hide() { if(Badge) Badge->SetVisibility(EVisibility::Collapsed); }
    void ShowCard(const FString& ActorName,const FString& ColorName,const FString& Hex,const FString& Source)
    {
        const FString Key=ActorName+TEXT("\n")+ColorName+TEXT("\n")+Hex+TEXT("\n")+Source;
        if(DisplayedText!=Key)
        {
            DisplayedText=Key;
            ActorLabel->SetText(FText::FromString(ActorName));
            ColorLabel->SetText(FText::FromString(ColorName));
            HexLabel->SetText(FText::FromString(Hex));
            SourceLabel->SetText(FText::FromString(Source));
        }
        Badge->SetVisibility(EVisibility::HitTestInvisible);
    }
    void ShowIdle()
    {
        Color=FLinearColor(.12f,.12f,.12f,1);
        ShowCard(TEXT("Hover an actor"),TEXT("Inspect its Chroma color"),TEXT("No actor under cursor"),TEXT("Color information follows your cursor."));
    }
public:
    SLATE_BEGIN_ARGS(SChromaViewportHover) {}
        SLATE_ARGUMENT(TWeakPtr<SLevelViewport>, Viewport)
    SLATE_END_ARGS()
    void Construct(const FArguments& Args)
    {
        View=Args._Viewport;
        SetVisibility(EVisibility::HitTestInvisible);
        const FLinearColor Muted(.48f,.48f,.48f,1);
        SAssignNew(Badge,SBox).WidthOverride(280.f).HeightOverride(142.f)
        [SNew(SBorder).BorderImage(&CardBrush).Padding(12.f)
            [SNew(SVerticalBox)
                +SVerticalBox::Slot().AutoHeight()
                    [SNew(SHorizontalBox)
                        +SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(0,0,6,0)
                            [SNew(SBox).WidthOverride(14.f).HeightOverride(14.f)
                                [SNew(SImage).Image_Lambda([]() -> const FSlateBrush* {
                                    const auto* Style=FSlateStyleRegistry::FindSlateStyle(TEXT("ChromaStyle"));
                                    return Style ? Style->GetBrush(TEXT("Chroma.Icon")) : FAppStyle::GetBrush(TEXT("NoBrush"));
                                }).ColorAndOpacity(Muted)]]
                        +SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
                            [SNew(STextBlock).Text(FText::FromString(TEXT("CHROMA")))
                                .Font(FAppStyle::GetFontStyle(TEXT("SmallFont"))).ColorAndOpacity(Muted)]]
                +SVerticalBox::Slot().AutoHeight().Padding(0,5,0,10)
                    [SAssignNew(ActorLabel,STextBlock)
                        .Font(FAppStyle::GetFontStyle(TEXT("NormalFontBold")))
                        .ColorAndOpacity(FLinearColor(.9f,.9f,.9f,1))
                        .OverflowPolicy(ETextOverflowPolicy::Ellipsis)]
                +SVerticalBox::Slot().AutoHeight()
                    [SNew(SHorizontalBox)
                        +SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(0,0,10,0)
                            [SNew(SBox).WidthOverride(28.f).HeightOverride(28.f)
                                [SNew(SBorder).BorderImage(&SwatchBrush).Padding(0)
                                    .BorderBackgroundColor_Lambda([this] { return Color; })]]
                        +SHorizontalBox::Slot().FillWidth(1).VAlign(VAlign_Center)
                            [SNew(SVerticalBox)
                                +SVerticalBox::Slot().AutoHeight()
                                    [SAssignNew(ColorLabel,STextBlock)
                                        .Font(FAppStyle::GetFontStyle(TEXT("NormalFont")))
                                        .ColorAndOpacity(FLinearColor(.85f,.85f,.85f,1))
                                        .OverflowPolicy(ETextOverflowPolicy::Ellipsis)]
                                +SVerticalBox::Slot().AutoHeight().Padding(0,2,0,0)
                                    [SAssignNew(HexLabel,STextBlock)
                                        .Font(FAppStyle::GetFontStyle(TEXT("SmallFont")))
                                        .ColorAndOpacity(Muted).OverflowPolicy(ETextOverflowPolicy::Ellipsis)]]]
                +SVerticalBox::Slot().AutoHeight().Padding(0,10,0,8)
                    [SNew(SBox).HeightOverride(1.f)
                        [SNew(SBorder).BorderImage(FAppStyle::GetBrush(TEXT("WhiteBrush")))
                            .Padding(0).BorderBackgroundColor(FLinearColor(.09f,.09f,.09f,1))]]
                +SVerticalBox::Slot().AutoHeight()
                    [SAssignNew(SourceLabel,STextBlock)
                        .Font(FAppStyle::GetFontStyle(TEXT("SmallFont")))
                        .ColorAndOpacity(Muted).OverflowPolicy(ETextOverflowPolicy::Ellipsis)]]];
        Hide();
        ChildSlot
        [SNew(SOverlay)
            +SOverlay::Slot().HAlign(HAlign_Left).VAlign(VAlign_Top).Padding(12.f,64.f,12.f,12.f)
                [Badge.ToSharedRef()]];
    }
    virtual void Tick(const FGeometry& Geometry,double Now,float Delta) override
    {
        SCompoundWidget::Tick(Geometry,Now,Delta);
#if ENABLE_ACTOR_PRIMITIVE_COLOR_HANDLER
        const auto V=View.Pin();
        auto& App=FSlateApplication::Get();
        if(!V || !GEditor || GEditor->PlayWorld
            || V->GetLevelViewportClient().GetViewMode()!=VMI_VisualizeActorColoration
            || FActorPrimitiveColorHandler::Get().GetActivePrimitiveColorHandler()!=FName(TEXT("Chroma")))
        { Hide(); NextProbe=0; return; }
        if(Badge->GetVisibility()==EVisibility::Collapsed) ShowIdle();
        // Keep the panel stable during interaction. Resume sampling on release.
        if(App.AnyMenusVisible() || !App.GetPressedMouseButtons().IsEmpty() || App.IsDragDropping())
        { NextProbe=0; return; }
        const auto Surface=V->GetViewportWidget().Pin();
        FViewport* Viewport=V->GetActiveViewport();
        if(!Surface || !Surface->IsHovered() || !Viewport) { ShowIdle(); NextProbe=0; return; }
        const FVector2D Cursor=App.GetCursorPos();
        if(Now<NextProbe) return;
        NextProbe=Now+.1;
        // Convert through the actual render surface, not the viewport toolbar.
        // Scaling by render size keeps hit testing correct at non-100% UI DPI.
        const FGeometry& SurfaceGeometry=Surface->GetCachedGeometry();
        const FVector2D SurfaceSize=SurfaceGeometry.GetLocalSize();
        const FVector2D Mouse=SurfaceGeometry.AbsoluteToLocal(Cursor);
        const FIntPoint Pixels=Viewport->GetSizeXY();
        if(SurfaceSize.X<=0 || SurfaceSize.Y<=0 || Pixels.X<=0 || Pixels.Y<=0
            || Mouse.X<0 || Mouse.Y<0 || Mouse.X>=SurfaceSize.X || Mouse.Y>=SurfaceSize.Y)
        { ShowIdle(); return; }
        const int32 X=FMath::Clamp(FMath::FloorToInt(Mouse.X/SurfaceSize.X*Pixels.X),0,Pixels.X-1);
        const int32 Y=FMath::Clamp(FMath::FloorToInt(Mouse.Y/SurfaceSize.Y*Pixels.Y),0,Pixels.Y-1);
        HHitProxy* Hit=Viewport->GetHitProxy(X,Y);
        AActor* Actor=nullptr;
        if(Hit && Hit->IsA(HActor::StaticGetType())) Actor=static_cast<HActor*>(Hit)->Actor.Get();
        if(!IsValid(Actor)) { ShowIdle(); return; }
        const FChromaResolvedColor Resolved=Chroma::ResolveActor(Actor);
        Color=Resolved.bHasColor ? Resolved.Color : FLinearColor(.18f,.18f,.18f,1);
        const FString Hex=Resolved.bHasColor ? TEXT("#")+Resolved.Color.ToFColor(true).ToHex().Left(6) : FString(TEXT("No color assigned"));
        FString Source;
        if(Resolved.bInherited) Source=TEXT("Inherited from ")+Resolved.Source;
        else if(Resolved.bMissingPreset) Source=TEXT("Preset missing. Reassign in Chroma.");
        else if(Resolved.Assignment==TEXT("N")) Source=TEXT("No Color override");
        else if(Resolved.bHasColor) Source=TEXT("Assigned directly to this actor");
        else Source=TEXT("No direct or inherited color");
        const FString Name=Resolved.Assignment.StartsWith(TEXT("C:")) ? FString(TEXT("Custom color")) : Resolved.Name;
        ShowCard(Actor->GetActorLabel(),Name,Hex,Source);
#else
        Hide();
#endif
    }
};

#pragma once
#include "ISceneOutlinerColumn.h"
#include "ISceneOutliner.h"
#include "SceneOutlinerPublicTypes.h"
#include "ActorTreeItem.h"
#include "FolderTreeItem.h"
#include "ChromaSettings.h"
#include "ChromaState.h"
#include "Engine/World.h"
#include "Editor.h"
#include "Widgets/Images/SImage.h"
#include "Layout/Children.h"
#include "Styling/AppStyle.h"

/** Decorates the existing label column. Native row construction and all column
 * behavior stay delegated, so rename, search, sorting and custom labels survive. */
class FChromaLabelColumn final : public ISceneOutlinerColumn
{
    TSharedRef<ISceneOutlinerColumn> Original;
    static TSharedPtr<SImage> FindImage(const TSharedRef<SWidget>& Widget,int32 Depth=0)
    {
        if(Depth>8) return nullptr;
        if(Widget->GetType()==FName(TEXT("SImage"))) return StaticCastSharedRef<SImage>(Widget);
        FChildren* Children=Widget->GetChildren();
        if(Children) for(int32 I=0;I<Children->Num();++I)
            if(auto Image=FindImage(Children->GetChildAt(I),Depth+1)) return Image;
        return nullptr;
    }
    static FChromaResolvedColor Resolve(const TWeakPtr<ISceneOutlinerTreeItem>& Weak)
    {
        if(!GetDefault<UChromaSettings>()->bTintOutlinerIcons) return {};
        if(auto Item=Weak.Pin())
        {
            if(const auto* Actor=Item->CastTo<FActorTreeItem>()) return Chroma::ResolveActor(Actor->Actor.Get());
            if(const auto* Folder=Item->CastTo<FFolderTreeItem>())
            {
                UWorld* World=GEditor ? GEditor->GetEditorWorldContext().World() : nullptr;
                return Chroma::ResolveFolder(World,Folder->GetFolder());
            }
        }
        return {};
    }
    struct FFolderBrush
    {
        const FSlateBrush* Source=nullptr;
        FSlateBrush Neutral;
    };
public:
    explicit FChromaLabelColumn(TSharedRef<ISceneOutlinerColumn> InOriginal) : Original(InOriginal) {}
    virtual FName GetColumnID() override { return Original->GetColumnID(); }
    virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override { return Original->ConstructHeaderRowColumn(); }
    virtual const TSharedRef<SWidget> ConstructRowWidget(FSceneOutlinerTreeItemRef Item,const STableRow<FSceneOutlinerTreeItemPtr>& Row) override
    {
        const auto Widget=Original->ConstructRowWidget(Item,Row);
        const bool IsActor=Item->IsA<FActorTreeItem>() && Widget->GetType()==FName(TEXT("SActorTreeLabel"));
        const bool IsFolder=Item->IsA<FFolderTreeItem>() && Widget->GetType()==FName(TEXT("SActorFolderTreeLabel"));
        // Unknown/custom label implementations are intentionally left intact.
        if(!IsActor && !IsFolder) return Widget;
        const auto Image=FindImage(Widget);
        if(!Image) return Widget;
        const TWeakPtr<ISceneOutlinerTreeItem> Weak=Item;
        Image->SetColorAndOpacity(TAttribute<FSlateColor>::CreateLambda([Weak,IsActor] {
            const auto Color=Resolve(Weak);
            if(Color.bHasColor) return FSlateColor(Color.Color.CopyWithNewOpacity(1.f));
            return IsActor ? FSlateColor::UseForeground() : FSlateColor(FLinearColor::White);
        }));
        if(IsFolder)
        {
            // The native folder brush can have its own yellow/gold tint. Use an
            // instance-owned neutral copy only while Chroma supplies a color;
            // never mutate the shared engine brush. Keep open/closed behavior.
            const auto Brush=MakeShared<FFolderBrush>();
            Image->SetImage(TAttribute<const FSlateBrush*>::CreateLambda([Weak,Brush]() -> const FSlateBrush* {
                const auto Item=Weak.Pin();
                const bool Open=Item && Item->Flags.bIsExpanded && Item->GetChildren().Num()>0;
                const FSlateBrush* Native=FAppStyle::GetBrush(Open ? TEXT("SceneOutliner.FolderOpen") : TEXT("SceneOutliner.FolderClosed"));
                if(!Resolve(Weak).bHasColor) return Native;
                if(Brush->Source!=Native)
                {
                    Brush->Source=Native; Brush->Neutral=*Native;
                    Brush->Neutral.TintColor=FSlateColor(FLinearColor::White);
                }
                return &Brush->Neutral;
            }));
        }
        return Widget;
    }
    virtual void Tick(double Now,float Delta) override { Original->Tick(Now,Delta); }
    virtual void PopulateSearchStrings(const ISceneOutlinerTreeItem& Item,TArray<FString>& Strings) const override { Original->PopulateSearchStrings(Item,Strings); }
    virtual bool SupportsSorting() const override { return Original->SupportsSorting(); }
    virtual void SortItems(TArray<FSceneOutlinerTreeItemPtr>& Items,EColumnSortMode::Type Mode) const override { Original->SortItems(Items,Mode); }
    virtual void OnSortRequested(EColumnSortPriority::Type Priority,EColumnSortMode::Type Mode) override { Original->OnSortRequested(Priority,Mode); }
    virtual bool IsSortReady() override { return Original->IsSortReady(); }
};

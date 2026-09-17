#pragma once
#include "ISceneOutlinerColumn.h"
#include "SceneOutlinerStandaloneTypes.h"
#include "ChromaState.h"
class SSceneOutliner;
class UWorld;
class FChromaColumn final : public ISceneOutlinerColumn
{
    TWeakPtr<SSceneOutliner> Outliner;
    TWeakObjectPtr<UWorld> World;
    TArray<FSceneOutlinerTreeItemPtr> ContextItems;
    UWorld* EditorWorld() const;
    Chroma::FTarget Target(const FSceneOutlinerTreeItemPtr& Item) const;
    FChromaResolvedColor Resolve(const FSceneOutlinerTreeItemPtr& Item) const;
    TArray<Chroma::FTarget> Targets(const FSceneOutlinerTreeItemPtr& Clicked) const;
    TArray<FSceneOutlinerTreeItemPtr> AllItems() const;
    FSceneOutlinerTreeItemID Parent(const FSceneOutlinerTreeItemPtr& Item) const;
    void SelectMatching(FSceneOutlinerTreeItemPtr Clicked,bool Siblings);
    TSharedRef<SWidget> Menu(FSceneOutlinerTreeItemPtr Item,bool ActionsOnly);
public:
    FChromaColumn(ISceneOutliner& View,UWorld* InWorld);
    FChromaColumn(TSharedPtr<ISceneOutliner> View,UWorld* InWorld);
    static TSharedRef<SWidget> MakeActorContextMenu(TSharedPtr<ISceneOutliner> View,UWorld* World,
        const TArray<TWeakObjectPtr<AActor>>& Actors,AActor* Sample);
    static FName ID() { return TEXT("Chroma.Color"); }
    virtual FName GetColumnID() override { return ID(); }
    virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;
    virtual const TSharedRef<SWidget> ConstructRowWidget(FSceneOutlinerTreeItemRef Item,const STableRow<FSceneOutlinerTreeItemPtr>& Row) override;
};

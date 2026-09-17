#include "ChromaColumn.h"
#include "ChromaSettings.h"
#include "SSceneOutliner.h"
#include "ActorTreeItem.h"
#include "FolderTreeItem.h"
#include "EditorActorFolders.h"
#include "EngineUtils.h"
#include "Editor.h"
#include "Selection.h"
#include "ScopedTransaction.h"
#include "Framework/Application/SlateApplication.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Widgets/Input/SComboButton.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/SNullWidget.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Colors/SColorBlock.h"
#include "Widgets/Colors/SColorPicker.h"
#include "Widgets/Text/STextBlock.h"
#include "Styling/AppStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Widgets/Images/SImage.h"
#include "ISettingsModule.h"
#include "Modules/ModuleManager.h"
#include "HAL/PlatformApplicationMisc.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "Engine/Level.h"
#include "Engine/World.h"
#include "Textures/SlateIcon.h"
#include "InputCoreTypes.h"

namespace
{
    bool CanEdit() { return GEditor && !GEditor->PlayWorld; }
    void Assign(const TArray<Chroma::FTarget>& Targets,const FString& Value)
    {
        if(!CanEdit()) return;
        const FScopedTransaction Transaction(NSLOCTEXT("Chroma","Assign","Chroma: Assign color"));
        for(const auto& T:Targets) Chroma::Write(T,Value);
    }
    bool ClipboardValue(FString& Value)
    {
        FPlatformApplicationMisc::ClipboardPaste(Value);
        if(!Value.RemoveFromStart(TEXT("Chroma.V1:"))) return false;
        const auto R=Chroma::Decode(Value);
        return Value==TEXT("N") || R.bHasColor || R.bMissingPreset;
    }
    bool Matches(const FChromaResolvedColor& A,const FChromaResolvedColor& B)
    {
        // Named labels match by stable identity, even if two labels share a color.
        if(A.PresetId.IsValid() || B.PresetId.IsValid()) return A.PresetId==B.PresetId;
        if(!A.bHasColor || !B.bHasColor) return A.bHasColor==B.bHasColor;
        return A.Assignment==B.Assignment;
    }
}
FChromaColumn::FChromaColumn(ISceneOutliner& View,UWorld* InWorld)
    : Outliner(StaticCastSharedRef<SSceneOutliner>(View.AsShared())),World(InWorld) {}
// The menu owns its model until dismissed. The model holds only weak actor and
// Outliner references, and menu action callbacks use weak model references.
class SChromaActorContextMenu final : public SCompoundWidget
{
    TSharedPtr<FChromaColumn> Model;
public:
    SLATE_BEGIN_ARGS(SChromaActorContextMenu) {}
        SLATE_ARGUMENT(TSharedPtr<FChromaColumn>, Model)
        SLATE_DEFAULT_SLOT(FArguments, Content)
    SLATE_END_ARGS()
    void Construct(const FArguments& Args) { Model=Args._Model; ChildSlot[Args._Content.Widget]; }
};
FChromaColumn::FChromaColumn(TSharedPtr<ISceneOutliner> View,UWorld* InWorld) : World(InWorld)
{
    if(View) Outliner=StaticCastSharedRef<SSceneOutliner>(View->AsShared());
}
TSharedRef<SWidget> FChromaColumn::MakeActorContextMenu(TSharedPtr<ISceneOutliner> View,UWorld* World,
    const TArray<TWeakObjectPtr<AActor>>& Actors,AActor* Sample)
{
    const auto Model=MakeShared<FChromaColumn>(View,World);
    FSceneOutlinerTreeItemPtr Reference;
    for(const auto& Weak:Actors) if(AActor* Actor=Weak.Get()) if(Chroma::ActorTarget(Actor).IsValid())
    {
        auto Item=MakeShared<FActorTreeItem>(Actor);
        Model->ContextItems.Add(Item);
        if(Actor==Sample) Reference=Item;
    }
    if(Model->ContextItems.IsEmpty()) return SNullWidget::NullWidget;
    if(!Reference) Reference=Model->ContextItems.Last();
    return SNew(SChromaActorContextMenu).Model(Model)[Model->Menu(Reference,false)];
}
UWorld* FChromaColumn::EditorWorld() const
{
    UWorld* Current=GEditor ? GEditor->GetEditorWorldContext().World() : nullptr;
    return Current ? Current : World.Get();
}
Chroma::FTarget FChromaColumn::Target(const FSceneOutlinerTreeItemPtr& Item) const
{
    if(Item) {
        if(const auto* A=Item->CastTo<FActorTreeItem>()) return Chroma::ActorTarget(A->Actor.Get());
        if(const auto* F=Item->CastTo<FFolderTreeItem>()) return Chroma::FolderTarget(EditorWorld(),F->GetFolder());
    }
    return {};
}
FChromaResolvedColor FChromaColumn::Resolve(const FSceneOutlinerTreeItemPtr& Item) const
{
    if(Item) {
        if(const auto* A=Item->CastTo<FActorTreeItem>()) return Chroma::ResolveActor(A->Actor.Get());
        if(const auto* F=Item->CastTo<FFolderTreeItem>()) return Chroma::ResolveFolder(EditorWorld(),F->GetFolder());
    }
    return {};
}
TArray<Chroma::FTarget> FChromaColumn::Targets(const FSceneOutlinerTreeItemPtr& Clicked) const
{
    TArray<Chroma::FTarget> Result;
    if(!ContextItems.IsEmpty())
    {
        for(const auto& I:ContextItems) { auto T=Target(I); if(T.IsValid()) Result.Add(T); }
        return Result;
    }
    if(auto View=Outliner.Pin())
    {
        const auto Selected=View->GetSelectedItems();
        bool SelectedClick=false;
        for(const auto& I:Selected) if(I->GetID()==Clicked->GetID()) SelectedClick=true;
        if(SelectedClick)
        {
            for(const auto& I:Selected) { auto T=Target(I); if(T.IsValid()) Result.Add(T); }
            return Result;
        }
    }
    auto T=Target(Clicked); if(T.IsValid()) Result.Add(T); return Result;
}
TArray<FSceneOutlinerTreeItemPtr> FChromaColumn::AllItems() const
{
    TArray<FSceneOutlinerTreeItemPtr> Items;
    UWorld* W=EditorWorld(); if(!W || W->WorldType!=EWorldType::Editor) return Items;
    FActorFolders::Get().ForEachFolder(*W,[&](const FFolder& F) { Items.Add(MakeShared<FFolderTreeItem>(F)); return true; });
    for(TActorIterator<AActor> It(W);It;++It)
        if(IsValid(*It) && !It->IsTemplate() && It->IsEditable() && It->IsListedInSceneOutliner()) Items.Add(MakeShared<FActorTreeItem>(*It));
    return Items;
}
FSceneOutlinerTreeItemID FChromaColumn::Parent(const FSceneOutlinerTreeItemPtr& Item) const
{
    if(const auto* A=Item->CastTo<FActorTreeItem>()) if(AActor* Actor=A->Actor.Get())
    {
        if(AActor* P=Actor->GetAttachParentActor()) return FActorTreeItem(P).GetID();
        return FFolderTreeItem(Actor->GetFolder()).GetID();
    }
    if(const auto* F=Item->CastTo<FFolderTreeItem>()) return FFolderTreeItem(F->GetFolder().GetParent()).GetID();
    return Item->GetID();
}
void FChromaColumn::SelectMatching(FSceneOutlinerTreeItemPtr Clicked,bool Siblings)
{
    auto View=Outliner.Pin(); if(!View || !CanEdit()) return;
    const auto Color=Resolve(Clicked);
    const auto ParentID=Parent(Clicked);
    TArray<FSceneOutlinerTreeItemPtr> Final;
    TSet<FSceneOutlinerTreeItemID> Seen;
    auto Add=[&](FSceneOutlinerTreeItemPtr I) { if(I && !Seen.Contains(I->GetID())) { Seen.Add(I->GetID()); Final.Add(I); } };
    if(FSlateApplication::Get().GetModifierKeys().IsShiftDown())
    {
        for(const auto& I:View->GetSelectedItems()) Add(I);
        for(FSelectionIterator It(*GEditor->GetSelectedActors());It;++It) if(AActor* A=Cast<AActor>(*It))
        { auto I=View->GetTreeItem(A); Add(I ? I : MakeShared<FActorTreeItem>(A)); }
    }
    int32 HiddenFolders=0;
    for(const auto& I:AllItems())
    {
        if(Siblings && Parent(I)!=ParentID) continue;
        if(!Matches(Color,Resolve(I))) continue;
        if(auto Live=View->GetTreeItem(I->GetID())) Add(Live);
        else if(I->IsA<FActorTreeItem>()) Add(I);
        else ++HiddenFolders;
        // Filtered-out folders cannot safely be selected through synthetic rows.
    }
    if(HiddenFolders)
    {
        FNotificationInfo Info(NSLOCTEXT("Chroma","FilteredFolders","Clear the Outliner filter to include matching folder rows hidden by that filter."));
        Info.ExpireDuration=5.f; FSlateNotificationManager::Get().AddNotification(Info);
    }
    if(Final.IsEmpty()) return;
    View->SetItemSelection(Final,true,ESelectInfo::Direct);
    View->AddToSelection(Final.Last(),ESelectInfo::OnMouseClick);
}
TSharedRef<SWidget> FChromaColumn::Menu(FSceneOutlinerTreeItemPtr Item,bool ActionsOnly)
{
    const TWeakPtr<FChromaColumn> Weak=StaticCastSharedRef<FChromaColumn>(AsShared());
    const auto Batch=Targets(Item);
    FMenuBuilder Menu(true,nullptr);
    if(!ActionsOnly)
    {
        const auto Current=Resolve(Item);
        bool Mixed=false;
        if(!ContextItems.IsEmpty())
        {
            for(const auto& I:ContextItems) if(!Matches(Current,Resolve(I))) Mixed=true;
        }
        else if(auto View=Outliner.Pin())
        {
            bool IsSelected=false;
            for(const auto& I:View->GetSelectedItems()) if(I->GetID()==Item->GetID()) IsSelected=true;
            if(IsSelected) for(const auto& I:View->GetSelectedItems())
                if(Target(I).IsValid() && !Matches(Current,Resolve(I))) Mixed=true;
        }
        Menu.BeginSection(NAME_None,NSLOCTEXT("Chroma","Current","Current Color"));
        // Use the same menu-entry layout as the palette so the swatch and label
        // align. This is informational: clicking it does not create an override.
        Menu.AddMenuEntry(FUIAction(FExecuteAction::CreateLambda([] {})),
            SNew(SHorizontalBox)
            +SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(0,0,8,0)
                [SNew(SBox).WidthOverride(12).HeightOverride(12)
                    [SNew(SColorBlock)
                        .Color(!Mixed && Current.bHasColor ? Current.Color : FLinearColor(.2f,.2f,.2f))
                        .Size(FVector2D(12,12))]]
            +SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
                [SNew(SVerticalBox)
                    +SVerticalBox::Slot().AutoHeight()
                        [SNew(STextBlock).Text(FText::FromString(Mixed ? TEXT("Multiple colors") : Current.Name))]
                    +SVerticalBox::Slot().AutoHeight()
                        [SNew(STextBlock)
                            .Visibility(Current.bInherited && !Mixed ? EVisibility::Visible : EVisibility::Collapsed)
                            .Text(FText::FromString(TEXT("Inherited from ")+Current.Source))]]);
        Menu.EndSection();
        auto ColorEntry=[&](const FString& Value)
        {
            const auto R=Chroma::Decode(Value);
            Menu.AddMenuEntry(FUIAction(FExecuteAction::CreateLambda([Batch,Value] { Assign(Batch,Value); })),
                SNew(SHorizontalBox)
                +SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(0,0,8,0)
                    [SNew(SColorBlock).Color(R.bHasColor ? R.Color : FLinearColor(.2f,.2f,.2f)).Size(FVector2D(12,12))]
                +SHorizontalBox::Slot().AutoWidth()[SNew(STextBlock).Text(FText::FromString(R.Name))]);
        };
        Menu.BeginSection(TEXT("Used"),NSLOCTEXT("Chroma","Used","Used in This Level (loaded items)"));
        TSet<FString> Used;
        for(const auto& I:AllItems()) { const auto R=Resolve(I); if(R.bHasColor || R.bMissingPreset) Used.Add(R.Assignment); }
        TArray<FString> Sorted=Used.Array();
        Sorted.Sort([](const FString& A,const FString& B) { return Chroma::Decode(A).Name<Chroma::Decode(B).Name; });
        for(const auto& Value:Sorted) ColorEntry(Value);
        Menu.EndSection();
        Menu.BeginSection(TEXT("Palette"),NSLOCTEXT("Chroma","Palette","Project Palette"));
        for(const auto& P:GetDefault<UChromaSettings>()->Palette) ColorEntry(TEXT("P:")+P.Id.ToString(EGuidFormats::Digits));
        Menu.AddMenuEntry(NSLOCTEXT("Chroma","Custom","Custom Color..."),FText::GetEmpty(),FSlateIcon(),FUIAction(FExecuteAction::CreateLambda([Batch,Current] {
            FColorPickerArgs Args; Args.bUseAlpha=false; Args.bOnlyRefreshOnOk=true;
            Args.InitialColor=Current.bHasColor ? Current.Color : FLinearColor::White;
            Args.OnColorCommitted=FOnLinearColorValueChanged::CreateLambda([Batch](FLinearColor C) { Assign(Batch,Chroma::Custom(C)); });
            OpenColorPicker(Args);
        })));
        Menu.AddMenuEntry(NSLOCTEXT("Chroma","Manage","Edit Named Colors..."),NSLOCTEXT("Chroma","ManageTip","Add, rename, or recolor shared presets in Project Settings. Existing assignments follow the preset."),FSlateIcon(),FUIAction(FExecuteAction::CreateLambda([] {
            if(auto* Settings=FModuleManager::GetModulePtr<ISettingsModule>(TEXT("Settings"))) Settings->ShowViewer(TEXT("Project"),TEXT("Plugins"),TEXT("Chroma"));
        })));
        Menu.EndSection();
    }
    Menu.BeginSection(TEXT("Actions"),NSLOCTEXT("Chroma","Actions","Chroma"));
    Menu.AddMenuEntry(NSLOCTEXT("Chroma","Match","Select Matching Color"),NSLOCTEXT("Chroma","MatchTip","Select matching loaded actors and visible folder rows. Shift-click adds to selection. Clear Outliner filters to include all folders. Requires an open World Outliner."),FSlateIcon(),FUIAction(FExecuteAction::CreateLambda([Weak,Item] { if(auto Self=Weak.Pin()) Self->SelectMatching(Item,false); }),FCanExecuteAction::CreateLambda([Weak] { auto Self=Weak.Pin(); return Self && Self->Outliner.IsValid() && CanEdit(); })));
    Menu.AddMenuEntry(NSLOCTEXT("Chroma","Siblings","Select Matching Color Among Siblings"),NSLOCTEXT("Chroma","SiblingsTip","Select this item and matching siblings under the same immediate Outliner parent. Shift-click adds to selection. Requires an open World Outliner."),FSlateIcon(),FUIAction(FExecuteAction::CreateLambda([Weak,Item] { if(auto Self=Weak.Pin()) Self->SelectMatching(Item,true); }),FCanExecuteAction::CreateLambda([Weak] { auto Self=Weak.Pin(); return Self && Self->Outliner.IsValid() && CanEdit(); })));
    FString Copied=Resolve(Item).Assignment; if(Copied.IsEmpty()) Copied=TEXT("N");
    Menu.AddMenuEntry(NSLOCTEXT("Chroma","Copy","Copy Chroma Color"),NSLOCTEXT("Chroma","CopyTip","Copy this item's effective named preset or custom color."),FSlateIcon(),FUIAction(FExecuteAction::CreateLambda([Copied] { FPlatformApplicationMisc::ClipboardCopy(*(TEXT("Chroma.V1:")+Copied)); })));
    Menu.AddMenuEntry(NSLOCTEXT("Chroma","Paste","Paste Chroma Color"),FText::GetEmpty(),FSlateIcon(),FUIAction(FExecuteAction::CreateLambda([Batch] { FString V; if(ClipboardValue(V)) Assign(Batch,V); }),FCanExecuteAction::CreateLambda([] { FString V; return ClipboardValue(V); })));
    Menu.AddMenuEntry(NSLOCTEXT("Chroma","Clear","Clear Override"),NSLOCTEXT("Chroma","ClearTip","Remove the explicit assignment and use the containing folder's color, if any."),FSlateIcon(),FUIAction(FExecuteAction::CreateLambda([Batch] { Assign(Batch,FString()); })));
    Menu.AddMenuEntry(NSLOCTEXT("Chroma","None","No Color"),NSLOCTEXT("Chroma","NoneTip","Explicitly suppress inherited color. Children inherit this choice unless they have their own override."),FSlateIcon(),FUIAction(FExecuteAction::CreateLambda([Batch] { Assign(Batch,TEXT("N")); })));
    Menu.EndSection(); return Menu.MakeWidget();
}
SHeaderRow::FColumn::FArguments FChromaColumn::ConstructHeaderRowColumn()
{
    return SHeaderRow::Column(ID()).DefaultLabel(NSLOCTEXT("Chroma","Header","Chroma")).FixedWidth(28.f)
        .HeaderContent()[SNew(SBox).HAlign(HAlign_Center).VAlign(VAlign_Center)
            .ToolTipText(NSLOCTEXT("Chroma","HeaderTip","Chroma: shared actor and folder colors"))
            [SNew(SBox).WidthOverride(16.f).HeightOverride(16.f)
                [SNew(SImage).Image_Lambda([]() -> const FSlateBrush* {
                    const auto* Style=FSlateStyleRegistry::FindSlateStyle(TEXT("ChromaStyle"));
                    return Style ? Style->GetBrush(TEXT("Chroma.Icon")) : FAppStyle::GetBrush(TEXT("NoBrush"));
                }).ColorAndOpacity(FLinearColor(.7f,.7f,.7f,1))]]];
}
const TSharedRef<SWidget> FChromaColumn::ConstructRowWidget(FSceneOutlinerTreeItemRef Item,const STableRow<FSceneOutlinerTreeItemPtr>&)
{
    if(!Target(Item).IsValid()) return SNullWidget::NullWidget;
    const TWeakPtr<FChromaColumn> Weak=StaticCastSharedRef<FChromaColumn>(AsShared());
    return SNew(SBox).HAlign(HAlign_Center).VAlign(VAlign_Center).WidthOverride(24).HeightOverride(20)
        [SNew(SBorder).BorderImage(FAppStyle::GetBrush(TEXT("NoBorder"))).Padding(0)
        .OnMouseButtonDown_Lambda([Weak,Item](const FGeometry&,const FPointerEvent& Event) {
            if(Event.GetEffectingButton()==EKeys::RightMouseButton && CanEdit()) if(auto Self=Weak.Pin()) if(auto View=Self->Outliner.Pin())
            {
                FSlateApplication::Get().PushMenu(View.ToSharedRef(),FWidgetPath(),Self->Menu(Item,true),Event.GetScreenSpacePosition(),FPopupTransitionEffect(FPopupTransitionEffect::ContextMenu));
                return FReply::Handled();
            }
            return FReply::Unhandled();
        })
        [SNew(SComboButton).HasDownArrow(false).ButtonStyle(FAppStyle::Get(),TEXT("SimpleButton"))
            .ContentPadding(FMargin(4,3)).IsEnabled_Lambda([] { return CanEdit(); })
            .OnGetMenuContent_Lambda([Weak,Item]() -> TSharedRef<SWidget> { if(auto Self=Weak.Pin()) return Self->Menu(Item,false); return SNullWidget::NullWidget; })
            .ToolTipText_Lambda([Weak,Item] {
                if(auto Self=Weak.Pin()) { const auto R=Self->Resolve(Item); return FText::FromString(R.Name+(R.bInherited ? TEXT("\nInherited from ")+R.Source : TEXT("\nExplicit assignment: ")+(Chroma::Read(Self->Target(Item)).IsEmpty() ? FString(TEXT("none")) : R.Name))+TEXT("\nClick to assign. Right-click for selection and copy actions.")); }
                return FText::GetEmpty();
            })
            .ButtonContent()[SNew(SColorBlock).Size(FVector2D(12,12)).Color_Lambda([Weak,Item] {
                if(auto Self=Weak.Pin()) { const auto R=Self->Resolve(Item); if(R.bHasColor) return R.Color; }
                return FLinearColor(.12f,.12f,.12f,1);
            })]]];
}

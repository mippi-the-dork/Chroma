#include "Modules/ModuleManager.h"
#include "ChromaColumn.h"
#include "ChromaSelectionOutline.h"
#include "ChromaLabelColumn.h"
#include "SSceneOutliner.h"
#include "SceneOutlinerMenuContext.h"
#include "SceneOutlinerModule.h"
#include "SceneOutlinerPublicTypes.h"
#include "EditorActorFolders.h"
#include "Editor.h"
#include "EditorUndoClient.h"
#include "LevelEditorViewport.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/ActorPrimitiveColorHandler.h"
#include "Containers/Ticker.h"
#include "ChromaViewportHover.h"
#include "LevelEditor.h"
#include "ILevelEditor.h"
#include "LevelEditorMenuContext.h"
#include "ToolMenus.h"
#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Brushes/SlateImageBrush.h"
#include "Textures/SlateIcon.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/Paths.h"
#include "Selection.h"

class FChromaModule final : public IModuleInterface, public FEditorUndoClient
{
    TSharedPtr<FSlateStyleSet> Style;
    TSharedPtr<FChromaSelectionOutline,ESPMode::ThreadSafe> SelectionOutline;
    FDelegateHandle Columns,Moved,Deleted,ActorFolderChanged,ActorAdded,MapOpened;
    FTSTicker::FDelegateHandle RefreshTicker;
    void RegisterActorMenu()
    {
        FToolMenuOwnerScoped Owner(this);
        UToolMenu* Menu=UToolMenus::Get()->ExtendMenu(TEXT("LevelEditor.ActorContextMenu"));
        Menu->AddDynamicSection(TEXT("Chroma.ActorMenu"),FNewToolMenuDelegate::CreateLambda([](UToolMenu* InMenu) {
            const auto* Context=InMenu->FindContext<ULevelEditorContextMenuContext>();
            if(!GEditor || GEditor->PlayWorld || !Context || Context->ContextType==ELevelEditorMenuContext::MainMenu) return;
            TArray<TWeakObjectPtr<AActor>> Actors;
            for(FSelectionIterator It(*GEditor->GetSelectedActors());It;++It)
                if(AActor* Actor=Cast<AActor>(*It)) if(Chroma::ActorTarget(Actor).IsValid()) Actors.Add(Actor);
            TWeakPtr<SSceneOutliner> OriginatingOutliner;
            if(const auto* OutlinerContext=InMenu->FindContext<USceneOutlinerMenuContext>())
            {
                OriginatingOutliner=OutlinerContext->SceneOutliner;
                if(auto View=OriginatingOutliner.Pin())
                {
                    Actors.Reset();
                    for(const auto& Item:View->GetSelectedItems()) if(const auto* Row=Item->CastTo<FActorTreeItem>())
                        if(Chroma::ActorTarget(Row->Actor.Get()).IsValid()) Actors.Add(Row->Actor);
                }
            }
            TWeakObjectPtr<AActor> Sample=Context->ContextType==ELevelEditorMenuContext::Viewport ? Context->HitProxyActor : TWeakObjectPtr<AActor>();
            if(Sample.IsValid() && Chroma::ActorTarget(Sample.Get()).IsValid())
            {
                if(!Actors.Contains(Sample)) { Actors.Reset(); Actors.Add(Sample); }
            }
            else Sample=Actors.IsEmpty() ? TWeakObjectPtr<AActor>() : Actors.Last();
            if(Actors.IsEmpty()) return;
            const TWeakPtr<ILevelEditor> Editor=Context->LevelEditor;
            const TWeakObjectPtr<UWorld> World=GEditor->GetEditorWorldContext().World();
            auto& Section=InMenu->AddSection(TEXT("Chroma"),NSLOCTEXT("Chroma","ActorSection","Chroma"));
            Section.AddSubMenu(TEXT("Chroma.Colors"),NSLOCTEXT("Chroma","ActorSubmenu","Color and Selection"),
                NSLOCTEXT("Chroma","ActorSubmenuTip","Assign colors to the selected actors, copy or paste Chroma colors, and select matching items."),
                FNewToolMenuDelegate::CreateLambda([Actors,Sample,Editor,World,OriginatingOutliner](UToolMenu* SubMenu) {
                    TSharedPtr<ISceneOutliner> Outliner=OriginatingOutliner.Pin();
                    if(!Outliner) if(auto E=Editor.Pin()) Outliner=E->GetMostRecentlyUsedSceneOutliner();
                    auto Content=FChromaColumn::MakeActorContextMenu(Outliner,World.Get(),Actors,Sample.Get());
                    SubMenu->AddSection(TEXT("Chroma.Controls")).AddEntry(
                        FToolMenuEntry::InitWidget(TEXT("Chroma.Palette"),Content,FText::GetEmpty(),true));
                }),false,FSlateIcon(TEXT("ChromaStyle"),TEXT("Chroma.Icon")));
        }));
    }
    struct FHoverOverlay
    {
        TWeakPtr<SLevelViewport> View;
        TSharedPtr<SChromaViewportHover> Widget;
    };
    TArray<FHoverOverlay> HoverOverlays;
    void AttachHoverOverlays()
    {
        HoverOverlays.RemoveAll([](const FHoverOverlay& Entry) { return !Entry.View.IsValid(); });
        auto* LevelEditor=FModuleManager::GetModulePtr<FLevelEditorModule>(TEXT("LevelEditor"));
        if(!LevelEditor) return;
        const auto Editor=LevelEditor->GetLevelEditorInstance().Pin();
        if(!Editor) return;
        for(const auto& View:Editor->GetViewports())
        {
            if(!View) continue;
            bool Found=false;
            for(const auto& Entry:HoverOverlays) if(Entry.View.Pin()==View) { Found=true; break; }
            if(Found) continue;
            FHoverOverlay Entry; Entry.View=View;
            Entry.Widget=SNew(SChromaViewportHover).Viewport(TWeakPtr<SLevelViewport>(View));
            View->AddOverlayWidget(Entry.Widget.ToSharedRef());
            HoverOverlays.Add(MoveTemp(Entry));
        }
    }
    uint64 LastRenderedRevision=0;
    TWeakObjectPtr<UWorld> LastRenderedWorld;
    bool bColorHandlerRegistered=false;
    static FName ColorHandlerName() { return TEXT("Chroma"); }

    bool TickViewport(float)
    {
        if(SelectionOutline && SelectionOutline->Update() && GEditor) GEditor->RedrawLevelEditingViewports();
#if ENABLE_ACTOR_PRIMITIVE_COLOR_HANDLER
        if(!bColorHandlerRegistered || !GEditor || GEditor->PlayWorld) return true;
        AttachHoverOverlays();
        auto& Colors=FActorPrimitiveColorHandler::Get();
        if(Colors.GetActivePrimitiveColorHandler()!=ColorHandlerName()) return true;
        bool bVisible=false;
        for(const FLevelEditorViewportClient* View:GEditor->GetLevelViewportClients())
            if(View && View->GetViewMode()==VMI_VisualizeActorColoration) { bVisible=true; break; }
        if(!bVisible) return true;
        UWorld* World=GEditor->GetEditorWorldContext().World();
        if(!World || World->WorldType!=EWorldType::Editor) return true;
        const uint64 Revision=Chroma::ViewportRevision();
        if(LastRenderedRevision==Revision && LastRenderedWorld.Get()==World) return true;
        // Metadata writes, palette edits, folder changes, and Undo/Redo only
        // increment a revision. Refresh once after the operation has completed.
        LastRenderedRevision=Revision; LastRenderedWorld=World;
        Colors.RefreshPrimitiveColorHandler(ColorHandlerName(),World);
        GEditor->RedrawLevelEditingViewports();
#endif
        return true;
    }
public:
    virtual void StartupModule() override
    {
        if(IsRunningCommandlet()) return;
        SelectionOutline=FSceneViewExtensions::NewExtension<FChromaSelectionOutline>();
        RefreshTicker=FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateRaw(this,&FChromaModule::TickViewport),.1f);
        if(const auto Plugin=IPluginManager::Get().FindPlugin(TEXT("Chroma")))
        {
            Style=MakeShared<FSlateStyleSet>(TEXT("ChromaStyle"));
            Style->Set(TEXT("Chroma.Icon"),new FSlateVectorImageBrush(
                FPaths::Combine(Plugin->GetBaseDir(),TEXT("Resources/Chroma-Header-Icon.svg")),FVector2D(16,16)));
            FSlateStyleRegistry::RegisterSlateStyle(*Style);
        }
        UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this,&FChromaModule::RegisterActorMenu));
        auto& Outliner=FModuleManager::LoadModuleChecked<FSceneOutlinerModule>(TEXT("SceneOutliner"));
        Columns=Outliner.OnCreateActorBrowserColumns().AddLambda([](FSceneOutlinerInitializationOptions& Options,UWorld* World) {
            if(auto* LabelInfo=Options.ColumnMap.Find(FSceneOutlinerBuiltInColumnTypes::Label()))
            {
                const FCreateSceneOutlinerColumn PreviousFactory=LabelInfo->Factory;
                LabelInfo->Factory=FCreateSceneOutlinerColumn::CreateLambda([PreviousFactory](ISceneOutliner& View) -> TSharedRef<ISceneOutlinerColumn> {
                    // Wrap this Outliner's existing factory, leaving global column
                    // registration and third-party column behavior unchanged.
                    const TSharedPtr<ISceneOutlinerColumn> Native=PreviousFactory.IsBound() ?
                        TSharedPtr<ISceneOutlinerColumn>(PreviousFactory.Execute(View)) :
                        FModuleManager::LoadModuleChecked<FSceneOutlinerModule>(TEXT("SceneOutliner")).FactoryColumn(FSceneOutlinerBuiltInColumnTypes::Label(),View);
                    check(Native.IsValid());
                    return MakeShared<FChromaLabelColumn>(Native.ToSharedRef());
                });
            }
            const auto* Label=Options.ColumnMap.Find(FSceneOutlinerBuiltInColumnTypes::Label());
            const uint8 Priority=Label ? Label->PriorityIndex : 10;
            for(auto& Pair:Options.ColumnMap) if(Pair.Value.PriorityIndex>=Priority && Pair.Value.PriorityIndex<255) ++Pair.Value.PriorityIndex;
            const TWeakObjectPtr<UWorld> WeakWorld(World);
            Options.ColumnMap.Add(FChromaColumn::ID(),FSceneOutlinerColumnInfo(ESceneOutlinerColumnVisibility::Visible,Priority,
                FCreateSceneOutlinerColumn::CreateLambda([WeakWorld](ISceneOutliner& View) { return MakeShared<FChromaColumn>(View,WeakWorld.Get()); }),
                true,TOptional<float>(),NSLOCTEXT("Chroma","Column","Chroma")));
        });
        Moved=FActorFolders::OnFolderMoved.AddStatic(&Chroma::FolderMoved);
        Deleted=FActorFolders::OnFolderDeleted.AddStatic(&Chroma::FolderDeleted);
#if ENABLE_ACTOR_PRIMITIVE_COLOR_HANDLER
        FActorPrimitiveColorHandler::Get().RegisterPrimitiveColorHandler(
            ColorHandlerName(),NSLOCTEXT("Chroma","ViewportMode","Chroma"),
            [](const UPrimitiveComponent* Component) -> FLinearColor {
                const FChromaResolvedColor Color=Chroma::ResolveActor(Component ? Component->GetOwner() : nullptr);
                return Color.bHasColor ? Color.Color.CopyWithNewOpacity(1.f) : FLinearColor(.18f,.18f,.18f,1.f);
            },
            [] { Chroma::RequestViewportRefresh(); },
            NSLOCTEXT("Chroma","ViewportModeTip","Display actors using their Chroma colors, including folder inheritance. Unassigned actors appear neutral gray."));
        bColorHandlerRegistered=true;
        if(GEngine)
        {
            ActorFolderChanged=GEngine->OnLevelActorFolderChanged().AddLambda([](const AActor*,FName) { Chroma::RequestViewportRefresh(); });
            ActorAdded=GEngine->OnLevelActorAdded().AddLambda([](AActor*) { Chroma::RequestViewportRefresh(); });
        }
        MapOpened=FEditorDelegates::OnMapOpened.AddLambda([](const FString&,bool) { Chroma::RequestViewportRefresh(); });
        if(GEditor) GEditor->RegisterForUndo(this);
#endif
    }
    virtual void PostUndo(bool bSuccess) override { if(bSuccess) Chroma::RequestViewportRefresh(); }
    virtual void PostRedo(bool bSuccess) override { if(bSuccess) Chroma::RequestViewportRefresh(); }
    virtual void ShutdownModule() override
    {
        UToolMenus::UnRegisterStartupCallback(this);
        UToolMenus::UnregisterOwner(this);
        FTSTicker::GetCoreTicker().RemoveTicker(RefreshTicker);
        if(SelectionOutline) { SelectionOutline->Stop(); SelectionOutline.Reset(); }
        for(const auto& Entry:HoverOverlays) if(auto View=Entry.View.Pin()) View->RemoveOverlayWidget(Entry.Widget.ToSharedRef());
        HoverOverlays.Reset();
        FEditorDelegates::OnMapOpened.Remove(MapOpened);
        if(GEngine)
        {
            GEngine->OnLevelActorFolderChanged().Remove(ActorFolderChanged);
            GEngine->OnLevelActorAdded().Remove(ActorAdded);
        }
        if(GEditor) GEditor->UnregisterForUndo(this);
#if ENABLE_ACTOR_PRIMITIVE_COLOR_HANDLER
        if(bColorHandlerRegistered)
        {
            auto& Colors=FActorPrimitiveColorHandler::Get();
            if(GEditor && Colors.GetActivePrimitiveColorHandler()==ColorHandlerName())
            {
                for(FLevelEditorViewportClient* View:GEditor->GetLevelViewportClients())
                    if(View && View->GetViewMode()==VMI_VisualizeActorColoration) View->SetViewMode(VMI_Lit);
            }
            Colors.UnregisterPrimitiveColorHandler(ColorHandlerName());
            bColorHandlerRegistered=false;
        }
#endif
        if(auto* Outliner=FModuleManager::GetModulePtr<FSceneOutlinerModule>(TEXT("SceneOutliner"))) Outliner->OnCreateActorBrowserColumns().Remove(Columns);
        FActorFolders::OnFolderMoved.Remove(Moved); FActorFolders::OnFolderDeleted.Remove(Deleted);
        if(Style) { FSlateStyleRegistry::UnRegisterSlateStyle(*Style); Style.Reset(); }
    }
    virtual bool SupportsDynamicReloading() override { return false; }
};
IMPLEMENT_MODULE(FChromaModule,Chroma)

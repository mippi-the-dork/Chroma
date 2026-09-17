# Chroma sources and implementation references

Chroma targets Unreal Engine 5.8.2. This document records the engine source and design references used during implementation. Referenced engine files are not redistributed here, and the plugin does not modify engine source. These references are not a license grant for Epic's code or assets.

## World Outliner and selection

- **SceneOutlinerModule.cpp, SceneOutlinerPublicTypes.h, and ISceneOutlinerColumn:** column registration, ordering, row construction, search, and sorting. Chroma inserts its swatch column before Item Label.
- **ActorTreeItem.cpp and ActorFolderTreeItem.cpp:** native actor/folder label structure and icon placement. Chroma wraps the existing label-column factory, forwards its behavior, and tints recognized native icon widgets. Custom label layouts remain untouched.
- **SSceneOutliner and Slate selection handling:** folder-aware batch selection stages the complete row selection before dispatching a native selection event. This follows the approach tested in Origin without depending on its module.
- **SImage and Slate brushes:** public image/color attributes provide tinting. Folder brushes are copied before their native tint is neutralized; shared engine brushes are not changed.

## Persistence and project settings

- **MetaData.h/.cpp and Package.h/.cpp:** UE 5.8 package-owned `FMetaData` storage. Chroma records explicit metadata changes for Undo/Redo through `FCommandChange`.
- **EditorActorFolders.h, WorldTransientFolders.cpp, WorldPersistentFolders.cpp, and WorldFolders.cpp:** native versus legacy folder storage and move/delete notifications. Chroma uses public folder APIs. Native folder assignments use their folder objects; legacy folder assignments use owning-level metadata and migrate with folder paths.
- **UDeveloperSettings:** `Config=Chroma` and `DefaultConfig` provide the shared project palette and settings. Named preset assignments reference stable GUIDs.
- **Focus:** its metadata persistence approach informed Chroma's independent implementation. No Focus dependency is introduced.

Actor/folder assignment data and project presets are designed to travel with version-controlled packages and configuration. Separate-workspace transfer has not yet been verified.

## Menus and color controls

- **Slate/AppFramework:** `FMenuBuilder`, `SComboButton`, `SColorBlock`, and Unreal's color picker provide native menu controls.
- **LevelEditorContextMenu.cpp and LevelEditorMenuContext.h:** actor context-menu integration and viewport sampling. The derived Outliner actor menu reuses the same Chroma palette with the originating Outliner context.
- **ILevelEditor::GetMostRecentlyUsedSceneOutliner:** connects viewport menu matching actions to an existing Outliner.
- **Motion Design / AvalancheOutliner:** reference for the single-swatch palette interaction. Chroma operates in the standard World Outliner and has no Motion Design or Avalanche dependency.

## Viewport coloration and hover information

- **FActorPrimitiveColorHandler:** registers Chroma as an Actor Coloration option and resolves effective color from component owners.
- **LevelEditorSubmenus.cpp and EditorViewportClient.cpp:** viewport menu and view-mode integration.
- **EditorUndoClient.h and FTSTicker:** completed transactions request coalesced viewport refreshes. Unchanged worlds are not continuously refreshed.
- **SLevelViewport::AddOverlayWidget / RemoveOverlayWidget and Slate layout:** attach the fixed information panel to editor viewports.
- **EngineUtils.h / HActor:** standard actor picking for hover information. Picking is throttled and accounts for viewport geometry and display scale. Specialized instance/custom hit proxies are not guaranteed.

## Selection outlines

- **PrimitiveComponent.h/.cpp:** the component outline setter also changes `bWantsEditorEffects` and invokes a selection override. Chroma avoids this setter.
- **PrimitiveSceneProxy.cpp:** `SetSelectionOutlineColorIndex_GameThread` queues a color-only change on a live render proxy. Chroma uses it without changing serialized component data or forcing selection.
- **SceneView.h, SceneViewExtension.h, and EditorViewportClient.cpp:** six additional per-view selection colors are initialized before `SetupView`. Chroma supplies a temporary palette through a scene-view extension.
- **PostProcessSelectionOutline.cpp/.usf:** slots 0 and 1 retain normal/subdued outlines; slots 2 through 7 provide extra colors. `r.Viewport.EnableSelectionOutlineColors` controls their use.
- **NaniteEditor.cpp:** selection groups encode their palette index into stencil values for outline compositing.
- **EditorPrimitivesRendering.cpp:** inspected for editor rendering context.

Chroma assigns at most six extra colors, preserves normal outlines for overflow, and releases its proxy overrides when no longer needed. It supplies colors per view without editing the saved editor-style palette. The renderer switch is enabled temporarily as needed and its prior value restored if it still has the value Chroma applied. Direct manipulation by other outline tools may conflict.

## Artwork

Mippi supplied `Chroma-Icon.png` and `Chroma-Header-Icon.svg` for the plugin. The PNG is included as `Resources/Icon128.png`; the SVG is used for the Outliner header, context submenu, and viewport panel. The supplied artwork is used unchanged.

## Validation record

Mippi confirmed the editor build and core color workflows, local persistence, viewport coloration, fixed hover panel, actor context menus, native icon tinting, and selection outlines. Outline tests covered ordinary static meshes, Nanite meshes, six-color overflow, deselection, disabling the setting, and color changes with Undo/Redo.

The icon and outline tint settings default on. Clean-project installation, plugin packaging, packaged-game builds, source-control transfer, and broader specialized-renderer coverage remain separate validation tasks.

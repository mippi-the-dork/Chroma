# Implementation and API — Technical

**Chroma v1.0.1 · Unreal Editor implementation**

## Module entry point

`FChromaModule` is an `IModuleInterface` and `FEditorUndoClient`. It starts style registration, Actor Browser column integration, native Actor context menu, Folder move/delete event listeners, an editor ticker, selection-outline view extension, and conditionally the primitive Actor Coloration handler.

## Key source ownership

- **`ChromaColumn.cpp`**: row target selection, swatch, palette, matching, copy/paste and context menus.
- **`ChromaState.cpp`**: encoded assignment, `FMetaData` persistence, Undo/Redo and effective Folder resolution.
- **`ChromaLabelColumn.h`**: native label-column forwarding and compatible icon tint.
- **`ChromaSelectionOutline.h`**: transient render-proxy outline indexes with six extra color slots.
- **`ChromaViewportHover.h`**: hit-test-invisible hover card with gated sampling.
- **`ChromaSettings.h/.cpp`**: configurable palette, defaults and appearance options.

## Public C++ read API

`Source/Chroma/Public/ChromaAPI.h` exports `FChromaResolvedColor` with `bHasColor`, `bInherited`, `bMissingPreset`, `PresetId`, `Color`, `Name`, `Source` and `Assignment`. It declares `Chroma::ResolveActor(const AActor*)` and `Chroma::ResolveFolder(UWorld*, FFolder)`.

This is a **read-only, editor-Actor-oriented** integration surface. Consumer code must account for the optional absence of Chroma and not assume a packaged-game runtime module.

## Rendering boundaries

Actor Coloration registration depends on `ENABLE_ACTOR_PRIMITIVE_COLOR_HANDLER`. Outline coloring uses per-view palette/scene-proxy changes, and the viewport inspector attaches to compatible editor viewports. None modifies material assets or serialized render component state for a color display.

## Shutdown

The module unregisters ToolMenus, ticker, viewport overlays, color handler and Outliner delegates, and stops the outline extension. Dynamic reload is not supported by this module.

## Source references

- [ChromaState.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaState.cpp)
- [ChromaModule.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaModule.cpp)
- [ChromaSettings.h](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Public/ChromaSettings.h)
- [ChromaAPI.h](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Public/ChromaAPI.h)

[Read Design](DESIGN.md) for user-facing behavior. **QA:** source-reviewed; no new UE build or Perforce testing is claimed here.

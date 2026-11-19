# Actor Coloration Visualization — Technical

**Chroma v1.0.1 · Unreal Editor implementation**

## Primitive color handler registration

At startup `FChromaModule` calls `FActorPrimitiveColorHandler::RegisterPrimitiveColorHandler` using `FName("Chroma")` when `ENABLE_ACTOR_PRIMITIVE_COLOR_HANDLER` is available. The handler obtains the component owner's `Chroma::ResolveActor` effective color and returns an opaque value, or neutral gray for unassigned Actors.

## Efficient refresh

Chroma maintains `ColorRevision`. Metadata writes, palette edits, Folder changes and Undo/Redo increment it. The editor ticker only requests `RefreshPrimitiveColorHandler` when the Chroma handler is active, a viewport uses `VMI_VisualizeActorColoration`, and the revision or world has changed.

This avoids continuous full-world recolor updates on every tick when nothing has changed.

## Restore normal view

The view mode uses native Actor Coloration, not a material replacement. At module shutdown, Chroma switches affected editor viewports back to Lit when Chroma's handler is still active, and unregisters the handler.

## Limits

Only Primitive Components handled by the engine's color-visualization path are affected. Editor-only and engine-feature conditional behavior is not proof of runtime or packaged-game visualization.

## Source references

- [ChromaColumn.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaColumn.cpp)
- [ChromaModule.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaModule.cpp)
- [ChromaSelectionOutline.h](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaSelectionOutline.h)
- [ChromaViewportHover.h](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaViewportHover.h)

[Read Design](DESIGN.md) for user workflows. **Validation:** source-reviewed; specialized viewport and renderer behavior requires project-specific editor QA.

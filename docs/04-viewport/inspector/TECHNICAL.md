# Viewport Color Inspector — Technical

**Chroma v1.0.1 · Unreal Editor implementation**

## Overlay construction

`SChromaViewportHover` is a native `SCompoundWidget` attached to `SLevelViewport` through `AddOverlayWidget`. The module discovers editor viewports and tracks weak references so overlays can be removed at shutdown.

The card includes a Chroma icon, Actor name, named/custom color, hex, and source. It uses a hit-test-invisible visibility mode so it does **not** consume mouse clicks.

## Sampling gates

The overlay checks for an editor world, an active `VMI_VisualizeActorColoration` mode and the active Chroma primitive-color handler. It hides in PIE and other modes. During open menus, pressed mouse buttons or dragging, it holds the last display instead of continuously re-picking.

## Performance and limitations

Hover picking is throttled and takes viewport coordinates/display scaling into account. The source uses normal editor hit-proxy paths, so special per-instance/custom proxy types are not universally supported.

## Lifetime

Viewport overlay widgets are removed on module shutdown. The data displayed comes from `ResolveActor`, so the inspector reports the same effective assignment and inherited source as the Outliner swatch.

## Source references

- [ChromaColumn.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaColumn.cpp)
- [ChromaModule.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaModule.cpp)
- [ChromaSelectionOutline.h](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaSelectionOutline.h)
- [ChromaViewportHover.h](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaViewportHover.h)

[Read Design](DESIGN.md) for user workflows. **Validation:** source-reviewed; specialized viewport and renderer behavior requires project-specific editor QA.

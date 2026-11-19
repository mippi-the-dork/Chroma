# Colored Selection Outlines — Technical

**Chroma v1.0.1 · Unreal Editor implementation**

## Scene view extension

`FChromaSelectionOutline` derives from `FSceneViewExtensionBase` and updates selected Actors' live Primitive Component scene proxies. It uses `SetSelectionOutlineColorIndex_GameThread` rather than the component setter, avoiding writes to component selection/editor-effects state.

The extension uses extra selection color indexes **2 through 7**, reserving normal/subdued editor slots. It examines `GEditor->GetSelectedActors()`, builds desired colors from effective Chroma assignments, and preserves explicit component outline indices owned by other systems.

## Slot allocation

<!-- Media target: IMAGE | outline-slots-technical | docs/assets/media/outline-slots-technical.png -->
<figure class="doc-media" data-kind="image" data-media-id="outline-slots-technical">
  <img src="../../assets/media-placeholder.png" alt="Selection-outline colors are assigned to transient per-view slots without changing saved component properties." loading="lazy">
  <figcaption>Selection-outline colors are assigned to transient per-view slots without changing saved component properties.
    <span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Create a diagram of selection outline slots 0–1 reserved for native/subdued outlines and slots 2–7 for Chroma colors. Show unique visible RGB values sharing slots and an overflow actor using the default outline.</span>
  </figcaption>
</figure>


Colors are grouped by the displayed sRGB color value, not by preset GUID, for rendering purposes. Up to six non-conflicting slots can be assigned; overflow remains at native outline rendering. Chroma's view extension supplies the per-view palette.

## Renderer state

`r.Viewport.EnableSelectionOutlineColors` may be temporarily enabled when necessary. The prior setting is restored when Chroma releases its change, provided another tool hasn't already changed the value.

## Lifecycle and safeguards

The module registers the extension during startup and calls `Stop()` at shutdown. The extension restores overridden proxy indices for components still matching their original live proxy. It applies only in appropriate editor worlds, not PIE/packaged gameplay.

The behavior depends on Unreal's selection-outline renderer and may vary with unsupported or specialized geometry.

## Source references

- [ChromaColumn.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaColumn.cpp)
- [ChromaModule.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaModule.cpp)
- [ChromaSelectionOutline.h](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaSelectionOutline.h)
- [ChromaViewportHover.h](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaViewportHover.h)

[Read Design](DESIGN.md) for user workflows. **Validation:** source-reviewed; specialized viewport and renderer behavior requires project-specific editor QA.

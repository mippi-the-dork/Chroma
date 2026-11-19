# Colored Selection Outlines — Design

**Chroma v1.0.1 · User guide**

## Recognize selected objects by color

Chroma can render an Actor's **normal viewport selection outline** in its effective Chroma color, so selecting Environment and Gameplay objects can produce Green and Orange outlines simultaneously.

The feature is enabled by default. To disable it, open **Project Settings → Plugins → Chroma → Viewport** and turn off **Tint Selection Outlines**.

## Six-color limit

<!-- Media target: IMAGE | outline-six-colors | docs/assets/media/outline-six-colors.png -->
<figure class="doc-media" data-kind="image" data-media-id="outline-six-colors">
  <img src="../../assets/media-placeholder.png" alt="Chroma uses up to six extra outline-color slots before falling back to Unreal's ordinary selection outline." loading="lazy">
  <figcaption>Chroma uses up to six extra outline-color slots before falling back to Unreal's ordinary selection outline.
    <span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Capture seven or more selected Actors with distinct effective Chroma colors in one viewport. Arrange them so the six colored outlines and at least one standard fallback outline are easy to distinguish; retain a visible selected-Actor Outliner list.</span>
  </figcaption>
</figure>


Chroma can use up to **six distinct extra outline-color slots at once**, when those slots are available. If more colors are selected, additional items use Unreal's normal selection outline. Other tools' explicitly assigned color slots can reduce the remaining capacity.

Actors sharing the same displayed Chroma color share one outline slot—even if the Actors have different assignments that happen to resolve to the same visible RGB color.

## Example workflow

Give three mesh Actors different named colors and select them. Observe each outline in the viewport. Add more uniquely colored Actors to test the slot limit, then clear the selection to return to standard presentation.

## Limitations

Specialized rendering paths, translucent geometry, Landscapes and per-instance editing may behave differently. Static Meshes and Nanite are the primary tested examples documented in the repository.

## Non-destructive behavior

Outline tinting doesn't change materials, serialized selection properties or the custom-depth configuration of your Actor. It affects transient editor presentation.

---

[Read Technical](TECHNICAL.md) for native Unreal integration, data ownership and implementation limits.

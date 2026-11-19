# Troubleshooting and FAQ — Design

**Chroma v1.0.1 · User guide**

## Chroma column missing

Check **Edit → Plugins** for an enabled Chroma plugin, restart the editor if just installed, and open the **standard World Outliner**. Chroma registers its swatch column in the Actor Browser, not every specialized Actor picker.

## Actor won't inherit a Folder color

Check whether the Actor has a direct color, or an explicit **No Color** assignment, which blocks inheritance. Use **Clear Override** when you intend to resume inheritance. Verify the Actor belongs to that **Outliner Folder**, not merely an attached parent Actor.

## Two items look the same but don't match

<!-- Media target: IMAGE | missing-preset-state | docs/assets/media/missing-preset-state.png -->
<figure class="doc-media" data-kind="image" data-media-id="missing-preset-state">
  <img src="../../assets/media-placeholder.png" alt="Named palette identity explains why visibly identical colors can represent different selectable organizational groups." loading="lazy">
  <figcaption>Named palette identity explains why visibly identical colors can represent different selectable organizational groups.
    <span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Capture the Chroma Project Palette with two named presets intentionally assigned the same RGB value and the Outliner with Actors assigned to each. Show the distinct names or tooltips next to visually matching swatches.</span>
  </figcaption>
</figure>


Two named presets can have identical RGB while retaining **different GUID identities**. Use the same named preset when you want one logical group. A custom RGB assignment isn't interchangeable with a similarly colored named preset.

## Matching selection skips some items

Chroma works with loaded editor Actors. Unloaded World Partition content isn't included. Filtered-out Actors can still be selected, but filtered-out Folder rows may be skipped; clear the Outliner filter when Chroma notifies you.

## Selection outline isn't colored

Check **Project Settings → Plugins → Chroma → Tint Selection Outlines**. Up to six extra distinct colors are available when renderer slots are free. Specialized geometry, translucency, Landscape and per-instance workflows can behave differently.

## Viewport visualization is unavailable or not recoloring

Use an ordinary editor viewport in the **Actor Coloration → Chroma** mode. Empty Actors and Folders have no geometry. The implementation requires compatible primitive color handler support and supported rendered components.

## Hover inspector shows no Actor

The inspector works only with the Chroma coloration view. Move the pointer onto supported Actor geometry, not empty space or an Outliner row. It intentionally pauses sampling while menus, camera navigation or drags are active.

## Changes disappear after reload

Confirm you saved the affected package and, for named preset changes, your Chroma project config. If a preset is missing, restore the project palette configuration or reassign affected items.

## Report a problem

Include Chroma and Unreal versions, Actor and Component types, whether a Folder or selection was involved, World Partition loaded state, settings, reproduction steps, and Output Log evidence.

---

[Read Technical](TECHNICAL.md) for source implementation and native engine boundaries.

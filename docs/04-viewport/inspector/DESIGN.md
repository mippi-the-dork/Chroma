# Viewport Color Inspector — Design

**Chroma v1.0.1 · User guide**

## Understand the color under your cursor

<!-- Media target: IMAGE | hover-inspector-panel | docs/assets/media/hover-inspector-panel.png -->
<figure class="doc-media" data-kind="image" data-media-id="hover-inspector-panel">
  <img src="../../assets/media-placeholder.png" alt="The Chroma viewport inspector identifies the hovered Actor, its effective color and the source of its assignment." loading="lazy">
  <figcaption>The Chroma viewport inspector identifies the hovered Actor, its effective color and the source of its assignment.
    <span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Capture Actor Coloration → Chroma active with the mouse over a mesh. Include the upper-left hover card showing Actor name, color name, hex value and 'Inherited from' or direct-source information; keep the hovered mesh visible.</span>
  </figcaption>
</figure>


While **Actor Coloration → Chroma** is active, Chroma displays a small information card near the upper-left of the editor viewport. Hover a supported Actor to view its **name**, effective color **name**, **hex value**, and **assignment source**.

The source helps distinguish a direct Actor assignment from an inherited Folder color. The card can also indicate No Color, a missing preset or an unassigned item.

## When the panel updates

<!-- Media target: GIF | hover-inspector-motion | docs/assets/media/hover-inspector-motion.gif -->
<figure class="doc-media" data-kind="gif" data-media-id="hover-inspector-motion">
  <img src="../../assets/media-placeholder.png" alt="The inspector updates on ordinary hovering and holds its most recent value during camera navigation or drag interactions." loading="lazy">
  <figcaption>The inspector updates on ordinary hovering and holds its most recent value during camera navigation or drag interactions.
    <span class="media-capture-instructions"><strong>Capture instructions · GIF:</strong> Record hovering two differently colored meshes to update the Chroma inspector, then briefly dragging/navigating the viewport to demonstrate that the card holds its prior readout and resumes on normal hover.</span>
  </figcaption>
</figure>


The inspector does not intercept viewport clicks. It pauses sampling while you navigate the camera, drag, or interact with open menus, then resumes once ordinary hovering returns. This avoids flickering or selecting the wrong target during navigation.

## Example

Hover a door displaying Green. The card identifies *Environment* and the folder it inherited from. Hover the adjacent Red critical objective to see its direct assignment.

## What it can't inspect

A Folder or empty Actor has no rendered geometry to point at. Specialized instancing or hit-proxy paths may not return the Actor that you'd expect. The overlay is a display aid, not an editor picking tool.

## Turning it off

Return the viewport to **Lit** or another mode. The Chroma inspector is only active during the compatible Chroma Actor Coloration view.

---

[Read Technical](TECHNICAL.md) for native Unreal integration, data ownership and implementation limits.

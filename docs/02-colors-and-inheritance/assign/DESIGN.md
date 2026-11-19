# Assign Colors — Design

**Chroma v1.0.1 · User guide**

## Use the Outliner swatch

<!-- Media target: IMAGE | palette-menu-anatomy | docs/assets/media/palette-menu-anatomy.png -->
<figure class="doc-media" data-kind="image" data-media-id="palette-menu-anatomy">
  <img src="../../assets/media-placeholder.png" alt="The Chroma palette combines used colors, reusable presets, custom color creation and assignment commands." loading="lazy">
  <figcaption>The Chroma palette combines used colors, reusable presets, custom color creation and assignment commands.
    <span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Capture a Chroma swatch menu expanded in a real World Outliner. Include Current Color, Used in This Level, Project Palette, Custom Color, Edit Named Colors, Clear Override and No Color in readable view; if menu is too tall use two connected stills.</span>
  </figcaption>
</figure>


Click the Chroma swatch next to an Actor or Folder. The palette shows **Current Color**, **Used in This Level (loaded items)**, the shared **Project Palette**, **Custom Color...** and useful commands.

Choose a named preset to give the item a stable project-defined color. Choose Custom Color when you want a one-off RGB color. The swatch immediately reflects the effective result.

## Actor versus Folder assignments

An Actor's direct assignment affects that Actor alone. A Folder assignment becomes the inherited default for its contents and nested folders unless a more specific assignment overrides it.

For example, assign **Environment = Green** to a folder. Its unassigned children display Green. Assign a child **Critical = Red** and only that child's branch or Actor uses the override.

## Which rows change?

If you clicked a row that's **already selected**, the chosen color applies to compatible selected Actor and Folder rows. If you clicked an **unselected** row, Chroma changes just that item. Use this distinction to prevent unintended batch edits.

## Clear versus No Color

- **Clear Override:** remove the direct assignment and resume inheritance from the folder.
- **No Color:** deliberately block inherited color for the item and its otherwise-unassigned descendants.

## Undo and save

Assignments use Unreal Undo/Redo and persist only after saving their owning Actor, Folder or level package. A Chroma color assignment does not affect Actor transforms, materials, runtime visuals or folder membership.

---

[Read Technical](TECHNICAL.md) for source implementation, native engine integration and data ownership.

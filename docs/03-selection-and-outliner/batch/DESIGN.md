# Multi-Selection Editing — Design

**Chroma v1.0.1 · User guide**

## How Chroma chooses targets

The most important rule is **whether the clicked row is already part of the current Outliner selection**.

| Where you click | Result |
| --- | --- |
| Chroma swatch on a **selected** row | Applies the chosen color or command to compatible selected Actors and Folders |
| Chroma swatch on an **unselected** row | Targets that one row |
| Actor context menu on a selection | Uses the compatible Actor selection available to the originating editor context |

## Example: color several props

<!-- Media target: GIF | batch-coloring | docs/assets/media/batch-coloring.gif -->
<figure class="doc-media" data-kind="gif" data-media-id="batch-coloring">
  <img src="../../assets/media-placeholder.png" alt="Color assignment applies to the compatible current selection when the clicked swatch belongs to that selection." loading="lazy">
  <figcaption>Color assignment applies to the compatible current selection when the clicked swatch belongs to that selection.
    <span class="media-capture-instructions"><strong>Capture instructions · GIF:</strong> Record three or more selected Actor rows with mixed initial colors, open the Chroma menu from one selected row, and assign a single named preset. Show the Multiple colors readout before and uniform color afterward.</span>
  </figcaption>
</figure>


1. Select four Actor rows in the World Outliner.
2. Click the Chroma swatch on one of those selected rows.
3. Choose a named preset, such as Environment.
4. All compatible selected rows receive that assignment, even if their previous colors differed.

The Current Color section can show **Multiple colors** for a mixed selection.

## Example: adjust one item without losing your selection

Click the swatch on an Actor not part of the existing selection. Only that Actor receives the action. The existing selection does not automatically become the target simply because it remains highlighted.

## Scope and saving

Chroma operates on valid loaded editor Actor and Folder rows. It does not modify unloaded World Partition Actors. Each changed target participates in a single Unreal Undo transaction; save affected Actor, Folder or level packages as usual.

---

[Read Technical](TECHNICAL.md) for native Unreal integration, data ownership and implementation limits.

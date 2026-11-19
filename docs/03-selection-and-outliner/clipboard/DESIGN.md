# Copy, Paste and Context Menu — Design

**Chroma v1.0.1 · User guide**

## Reuse a Chroma assignment

<!-- Media target: GIF | clipboard-color-workflow | docs/assets/media/clipboard-color-workflow.gif -->
<figure class="doc-media" data-kind="gif" data-media-id="clipboard-color-workflow">
  <img src="../../assets/media-placeholder.png" alt="Copy and Paste preserve a named assignment's identity rather than converting it to a one-off RGB value." loading="lazy">
  <figcaption>Copy and Paste preserve a named assignment's identity rather than converting it to a one-off RGB value.
    <span class="media-capture-instructions"><strong>Capture instructions · GIF:</strong> Record copying an inherited named preset from one Actor’s Chroma menu, then pasting onto another Actor outside that Folder. Show the destination’s explicit named assignment and swatch afterward.</span>
  </figcaption>
</figure>


Open the source item's Chroma menu and choose **Copy Chroma Color**. Then open a destination menu and choose **Paste Chroma Color**. Named assignments retain the same named preset identity rather than becoming an unrelated custom RGB value.

Paste uses the same selected-row rule as ordinary color assignment: if the clicked row is selected, compatible selected targets receive the paste; if it isn't, only the clicked item changes.

## What Copy copies

Copy uses the source item's **effective** Chroma assignment. An Actor inheriting a named color from a folder can supply that named assignment when copied; pasting it elsewhere creates an explicit assignment for the destination.

## Actor context menu

Right-click a compatible Actor and open **Chroma → Color and Selection**. The submenu provides normal Chroma color/selection actions without requiring you to find the narrow Outliner swatch.

For **Folder** coloring, use its swatch directly in the World Outliner. Right-clicking the swatch itself opens a compact action-oriented menu.

## Clipboard behavior

Only a recognizable Chroma-formatted clipboard value enables Paste. Ordinary copied text isn't treated as a color assignment.

## Undo and safety

Pasting a valid assignment is an ordinary Chroma metadata edit with Undo/Redo. It changes organizational color, not the Actor's native material or render state.

---

[Read Technical](TECHNICAL.md) for native Unreal integration, data ownership and implementation limits.

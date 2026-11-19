# Multi-Selection Editing — Technical

**Chroma v1.0.1 · Unreal Editor implementation**

## Selection targeting

<!-- Media target: IMAGE | clicked-row-targets | docs/assets/media/clicked-row-targets.png -->
<figure class="doc-media" data-kind="image" data-media-id="clicked-row-targets">
  <img src="../../assets/media-placeholder.png" alt="The clicked item decides whether Chroma resolves the whole selection or a single target." loading="lazy">
  <figcaption>The clicked item decides whether Chroma resolves the whole selection or a single target.
    <span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Draw a two-branch decision diagram with 'Clicked row already selected?' leading to valid selected Actor/Folder rows or only the clicked valid row, followed by one FScopedTransaction and per-target metadata writes.</span>
  </figcaption>
</figure>


`FChromaColumn::Targets` determines `SelectedClick` by comparing `GetSelectedItems()` IDs with the clicked row. A selected click builds a list of valid `FTarget` entries from selected items; an unselected click returns only the clicked valid target.

The context menu has a separate `ContextItems` path supplied by `MakeActorContextMenu`. It uses the selected Actors from an Outliner menu context when available, otherwise native editor Actor selection/viewport hit proxy.

## Batch editing

`Assign` creates one `FScopedTransaction` and calls `Chroma::Write` per target. Each write compares its previous metadata value and records a reversible `FCommandChange` when needed.

## Mixed state

`FChromaColumn::Menu` resolves the reference item and compares other items from the target selection using `Matches`. When values differ it shows **Multiple colors**, not an arbitrary average color.

## Boundaries

Chroma's selected-row targeting is not an attachment-descendant bulk traversal. It directly acts on selected compatible rows; Folder inheritance subsequently changes the effective colors of contents without writing explicit assignments to each child.

## Source references

- [ChromaColumn.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaColumn.cpp)
- [ChromaModule.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaModule.cpp)
- [ChromaSelectionOutline.h](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaSelectionOutline.h)
- [ChromaViewportHover.h](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaViewportHover.h)

[Read Design](DESIGN.md) for user workflows. **Validation:** source-reviewed; specialized viewport and renderer behavior requires project-specific editor QA.

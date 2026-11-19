# 03. Selection and Outliner

Color assignments are useful beyond decoration: the Chroma menu can apply one color across selected rows, select all matching loaded content or just matching siblings, and copy/paste the assignment type. Its native icon tinting can make these groups recognizable without opening a menu.

The clicked row determines scope: when it belongs to the current selection, Chroma targets that selection; otherwise it targets only the clicked item. Matching uses preset identity for named colors and stored values for custom colors.

## Typical workflow

<!-- Media target: IMAGE | selection-workflow-overview | docs/assets/media/selection-workflow-overview.png -->
<figure class="doc-media" data-kind="image" data-media-id="selection-workflow-overview">
  <img src="../assets/media-placeholder.png" alt="Chroma uses the clicked row's selection state to distinguish single-item changes from batch operations." loading="lazy">
  <figcaption>Chroma uses the clicked row's selection state to distinguish single-item changes from batch operations.
    <span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Capture an Outliner with several selected Actors and one unselected Actor. Highlight a swatch on a selected row and visually annotate that it targets the selected set, whereas the unselected row’s swatch affects only that row.</span>
  </figcaption>
</figure>


Select a Gameplay-colored Actor and choose Select Matching Color to collect every loaded Actor with the same preset identity. Shift adds results to the existing selection.

## Topics

| Topic | What it covers | Design | Technical |
| --- | --- | --- | --- |
| **Multi-Selection Editing** | Know exactly which selected Actors and Folders an action changes. | [Design](batch/DESIGN.md) | [Technical](batch/TECHNICAL.md) |
| **Matching Selection** | Select matching colors across a loaded editor world or among siblings. | [Design](matching/DESIGN.md) | [Technical](matching/TECHNICAL.md) |
| **Copy, Paste and Context Menu** | Reuse assignments and access Chroma from Actor context menus. | [Design](clipboard/DESIGN.md) | [Technical](clipboard/TECHNICAL.md) |
| **Tinted Outliner Icons** | Display effective Chroma colors on compatible native Actor and Folder icons. | [Design](icon-tint/DESIGN.md) | [Technical](icon-tint/TECHNICAL.md) |

## Important distinction

Matching selection uses loaded editor items and cannot safely select filtered-out folder rows; clear the filter when prompted.

Use **Design** for practical authoring steps and **Technical** for native Unreal implementation, persistence and integration details.

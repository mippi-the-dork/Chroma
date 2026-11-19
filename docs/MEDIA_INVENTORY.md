# Chroma Documentation Media Inventory

Chroma includes genuine hero artwork, existing animation demonstrations and viewport screenshots in the repository's `Doc/Images/` folder. Reuse them where they already explain a feature. Additional planned visuals use the **supplied neutral placeholder image** until captured.

Each placeholder has two distinct text lines: a reader-facing explanation and an explicit **Capture instructions · Image** or **Capture instructions · GIF** line describing the exact screenshot/animation or diagram required.

## Planned capture slots

| Topic / page | Media type | Expected file |
| --- | --- | --- |
| [01-getting-started/overview/DESIGN.md](01-getting-started/overview/DESIGN.md) | **IMAGE** | `assets/media/outliner-color-categories.png` |
| [01-getting-started/overview/TECHNICAL.md](01-getting-started/overview/TECHNICAL.md) | **IMAGE** | `assets/media/chroma-editor-system-map.png` |
| [01-getting-started/install/DESIGN.md](01-getting-started/install/DESIGN.md) | **IMAGE** | `assets/media/install-folder.png` |
| [01-getting-started/first-use/DESIGN.md](01-getting-started/first-use/DESIGN.md) | **GIF** | `assets/media/first-assign-workflow.gif` |
| [02-colors-and-inheritance/README.md](02-colors-and-inheritance/README.md) | **IMAGE** | `assets/media/color-state-overview.png` |
| [02-colors-and-inheritance/assign/DESIGN.md](02-colors-and-inheritance/assign/DESIGN.md) | **IMAGE** | `assets/media/palette-menu-anatomy.png` |
| [02-colors-and-inheritance/assign/TECHNICAL.md](02-colors-and-inheritance/assign/TECHNICAL.md) | **IMAGE** | `assets/media/assignment-data-flow.png` |
| [02-colors-and-inheritance/palette/DESIGN.md](02-colors-and-inheritance/palette/DESIGN.md) | **IMAGE** | `assets/media/named-palette-settings.png` |
| [02-colors-and-inheritance/palette/DESIGN.md](02-colors-and-inheritance/palette/DESIGN.md) | **GIF** | `assets/media/preset-recolor.gif` |
| [02-colors-and-inheritance/inheritance/TECHNICAL.md](02-colors-and-inheritance/inheritance/TECHNICAL.md) | **IMAGE** | `assets/media/folder-resolution-chain.png` |
| [02-colors-and-inheritance/overrides/DESIGN.md](02-colors-and-inheritance/overrides/DESIGN.md) | **GIF** | `assets/media/clear-versus-no-color.gif` |
| [02-colors-and-inheritance/overrides/TECHNICAL.md](02-colors-and-inheritance/overrides/TECHNICAL.md) | **IMAGE** | `assets/media/override-encoding.png` |
| [02-colors-and-inheritance/custom-and-used/DESIGN.md](02-colors-and-inheritance/custom-and-used/DESIGN.md) | **IMAGE** | `assets/media/used-colors-menu.png` |
| [03-selection-and-outliner/README.md](03-selection-and-outliner/README.md) | **IMAGE** | `assets/media/selection-workflow-overview.png` |
| [03-selection-and-outliner/batch/DESIGN.md](03-selection-and-outliner/batch/DESIGN.md) | **GIF** | `assets/media/batch-coloring.gif` |
| [03-selection-and-outliner/batch/TECHNICAL.md](03-selection-and-outliner/batch/TECHNICAL.md) | **IMAGE** | `assets/media/clicked-row-targets.png` |
| [03-selection-and-outliner/matching/TECHNICAL.md](03-selection-and-outliner/matching/TECHNICAL.md) | **IMAGE** | `assets/media/preset-matching-rules.png` |
| [03-selection-and-outliner/clipboard/DESIGN.md](03-selection-and-outliner/clipboard/DESIGN.md) | **GIF** | `assets/media/clipboard-color-workflow.gif` |
| [03-selection-and-outliner/clipboard/TECHNICAL.md](03-selection-and-outliner/clipboard/TECHNICAL.md) | **IMAGE** | `assets/media/clipboard-format.png` |
| [03-selection-and-outliner/icon-tint/DESIGN.md](03-selection-and-outliner/icon-tint/DESIGN.md) | **IMAGE** | `assets/media/tinted-native-icons.png` |
| [04-viewport/README.md](04-viewport/README.md) | **IMAGE** | `assets/media/viewport-modes-comparison.png` |
| [04-viewport/outlines/DESIGN.md](04-viewport/outlines/DESIGN.md) | **IMAGE** | `assets/media/outline-six-colors.png` |
| [04-viewport/outlines/TECHNICAL.md](04-viewport/outlines/TECHNICAL.md) | **IMAGE** | `assets/media/outline-slots-technical.png` |
| [04-viewport/visualization/DESIGN.md](04-viewport/visualization/DESIGN.md) | **GIF** | `assets/media/visualize-colors-toggle.gif` |
| [04-viewport/visualization/TECHNICAL.md](04-viewport/visualization/TECHNICAL.md) | **IMAGE** | `assets/media/viewport-handler-flow.png` |
| [04-viewport/inspector/DESIGN.md](04-viewport/inspector/DESIGN.md) | **IMAGE** | `assets/media/hover-inspector-panel.png` |
| [04-viewport/inspector/DESIGN.md](04-viewport/inspector/DESIGN.md) | **GIF** | `assets/media/hover-inspector-motion.gif` |
| [05-settings-and-support/README.md](05-settings-and-support/README.md) | **IMAGE** | `assets/media/settings-support-map.png` |
| [05-settings-and-support/settings/DESIGN.md](05-settings-and-support/settings/DESIGN.md) | **IMAGE** | `assets/media/presentation-toggles.png` |
| [05-settings-and-support/saving/TECHNICAL.md](05-settings-and-support/saving/TECHNICAL.md) | **IMAGE** | `assets/media/metadata-package-ownership.png` |
| [05-settings-and-support/saving/DESIGN.md](05-settings-and-support/saving/DESIGN.md) | **IMAGE** | `assets/media/save-team-workflow.png` |
| [05-settings-and-support/troubleshooting/DESIGN.md](05-settings-and-support/troubleshooting/DESIGN.md) | **IMAGE** | `assets/media/missing-preset-state.png` |
| [05-settings-and-support/architecture/TECHNICAL.md](05-settings-and-support/architecture/TECHNICAL.md) | **IMAGE** | `assets/media/architecture-map.png` |
| [05-settings-and-support/updating/DESIGN.md](05-settings-and-support/updating/DESIGN.md) | **IMAGE** | `assets/media/updating-plugin-folder.png` |
| [ROADMAP.md](ROADMAP.md) | **IMAGE** | `assets/media/roadmap-current-scope.png` |

## Replacing a placeholder

1. Capture the actual **Chroma v1.0.1** UI or author the specified source-grounded diagram. Avoid unrelated or fabricated engine UI.
2. Save the final PNG or GIF under `docs/assets/media/` using the exact name in this inventory.
3. Replace the figure's image `src` with the correct relative media path; retain accurate alt text and reader-facing caption.
4. The capture instruction may be removed when the final media is published, or retained while reviewing other outstanding slots.
5. Confirm rendering at desktop and mobile sizes, and verify GIF clarity, file size and reduced-motion considerations.

Complete details—including the caption and precisely what to capture—are maintained in [the media registry](assets/media-slots.json), keyed by a stable slot ID.

## Genuine existing assets

The documentation reuses these repository assets where appropriate: `Chroma-Hero.png`, `Chroma-Assigning-Colors.gif`, `Chroma-Inheritance.gif`, `Chroma-Matching.gif`, `Chroma-Selection-Outlines.png`, `Chroma-Lit.png`, `Chroma-Visualization.png` and `Chroma-Settings.png`.

[Documentation Audit](DOCUMENTATION_AUDIT.md) · [Verification Matrix](VERIFICATION_MATRIX.md)

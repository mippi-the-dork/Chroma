# Chroma Roadmap

**Current documented release:** **v1.0.1** · Unreal Engine 5.8.x · Win64 · Editor-only.

## Current release

<!-- Media target: IMAGE | roadmap-current-scope | docs/assets/media/roadmap-current-scope.png -->
<figure class="doc-media" data-kind="image" data-media-id="roadmap-current-scope">
  <img src="assets/media-placeholder.png" alt="Chroma v1.0.1 includes color assignments, matching-selection workflows, and editor viewport color presentation." loading="lazy">
  <figcaption>Chroma v1.0.1 includes color assignments, matching-selection workflows, and editor viewport color presentation.
    <span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Create a three-part current-release summary: Outliner swatch/palette, matching selection and Actor Coloration viewport. Use real Chroma UI captures in each panel. Label all as available in v1.0.1, not planned features.</span>
  </figcaption>
</figure>


Chroma v1.0.1 provides Actor and Folder color assignment, named project presets, custom colors, folder inheritance, No Color and Clear Override, matching-color selection, clipboard assignment, Outliner icon tint, colored viewport selection outlines, Actor Coloration visualization and a hover inspector.

This is the baseline for the current [Design/Technical manual](README.md). Features listed here are source-reviewed and documented as present; individual project workflows still deserve the testing described in the [Verification Matrix](VERIFICATION_MATRIX.md).

## How the roadmap is organized

| Stage | Status | Meaning |
| --- | --- | --- |
| **v1.0.1 — Current** | Released / documented | All features enumerated above |
| **Future releases** | Not yet committed | No additional feature scope or version milestone has been specified by the plugin author |

There is **no announced v2.0 feature list, date, or promise of new Chroma capabilities** in this documentation. Future features will be added here when their scope has been agreed and implementation begins.

## Quality and compatibility work to validate

These are **verification obligations**, not confirmed new product features:

- Confirm clean-project install, source build and plugin packaging on the exact supported UE 5.8/Win64 configurations.
- Validate Actor and native/legacy Folder metadata persistence across saves, reload, Undo/Redo, and team source-control transfer.
- Test World Partition loaded/unloaded Actor behavior, Outliner filtering, named-preset deletion and renamed/moved Folders.
- Review performance in large Outliners and viewport coloration in dense levels.
- Test selection outline rendering with Static Mesh, Nanite, Landscape, translucent and specialized per-instance workflows, documenting which actually work.
- Verify the documentation website in desktop/mobile browsers and replace all placeholder images/GIFs with real Chroma captures.

## Principles for future changes

New features should retain Chroma's core scope: native, concise **editor organization**, without replacing Actor materials, adding runtime Components or silently modifying world content. Changes should be source-grounded, documented in both Design and Technical guides, and accompanied by real verification results.

[Documentation Audit](DOCUMENTATION_AUDIT.md) · [Technical architecture](05-settings-and-support/architecture/TECHNICAL.md) · [Current release](README.md)

# Chroma Documentation Audit

**Baseline:** Chroma v1.0.1, source of truth: current Chroma C++ source, descriptor, README and `Doc/Sources.md`.

## What has been documented

The site covers five major subjects and twenty feature topics, each with distinct **Design** and **Technical** pages:

- Getting Started — plugin purpose, installation and first use
- Colors and Inheritance — assignments, named palette, inheritance, overrides and custom colors
- Selection and Outliner — mixed selection, matching, clipboard/context menus, icon tinting
- Viewport Presentation — selection outlines, Actor Coloration and hover inspector
- Settings, Saving and Support — project settings, package metadata, troubleshooting, technical architecture and updates

## Known documentation and verification gaps

| Priority | Area | What remains to verify or capture |
| --- | --- | --- |
| P1 | Real editor imagery | Replace planned placeholders with screenshots/GIFs from Chroma v1.0.1. Keep genuine repository artwork and demos where they already explain behavior. |
| P1 | Package persistence | Test Actor, native Folder and legacy Folder packages, Perforce/OFPA and Undo after reload in a clean project. |
| P1 | Renderer compatibility | Validate six-color overflow and selected renderer/primitive types in a running editor. |
| P1 | Filtering and selection | Confirm loaded-but-filtered Actor matching, hidden Folder notification and Shift selection behavior. |
| P1 | Website QA | Verify full-text search, links, responsive image sizing, sidebar and keyboard/mobile navigation in a real browser. |
| P2 | Source reference versions | Replace `main` source links with release-tag/commit references once a stable source release is identified. |
| P2 | Accessibility | Review contrast, focus feedback, GIF motion/reduced-motion alternatives and alt-text clarity. |

## Source-grounded distinctions worth preserving

**Named identity vs visible color:** Two presets with identical RGB are still distinct matching groups, but may share a viewport outline color slot. Custom RGB matching works through stored values.

**Clear Override vs No Color:** The former removes a direct assignment; the latter explicitly blocks inheritance. Folder inheritance follows folder paths, not Actor attachment.

**Visualization vs gameplay:** Outliner tint, outlines and Actor Coloration are transient editor presentation. Chroma does not replace materials or introduce runtime data.

**Source review vs live testing:** Reading an implementation and confirming a UI source path does not prove every Unreal version or browser configuration passed. Track real outcomes in [Verification Matrix](VERIFICATION_MATRIX.md).

## Documentation maintenance policy

Update both pages of each affected topic alongside any plugin behavior change. Add screenshots/GIFs showing the exact current interface. Document limitations and exceptions prominently; do not copy the README into both pages. Audit all navigation/asset links and distinguish unsupported target types from genuine failures.

The media inventory describes each outstanding capture. Preserve the two-line captions until the final visuals are delivered: public explanation first, explicit production capture instructions second.

[Media Inventory](MEDIA_INVENTORY.md) · [Verification Matrix](VERIFICATION_MATRIX.md)

# Chroma v1.0.1 Verification Matrix

**Target:** Unreal Engine 5.8.x · Win64 · Chroma v1.0.1.  
**Status:** Unless a row has an evidence record, **Not run**. The repository's `Doc/Sources.md` records earlier local confirmations of some behaviors, but this matrix does not claim to have rerun them.

Record engine patch version, plugin commit, project setup, Actor/Component classes, World Partition and OFPA settings, source control, tester/date, logs and captured media for every executed test.

## A. Color assignment and inheritance

| ID | Scenario | Expected | Status |
| --- | --- | --- | --- |
| CHR-01 | Open standard World Outliner with Chroma enabled | Swatch column appears before Item Label | Not run |
| CHR-02 | Assign one named preset and one custom color | Correct direct assignments and swatches | Not run |
| CHR-03 | Color parent Folder, nested Folder and new Actor | Nearest containing Folder's effective color inherited | Not run |
| CHR-04 | Attach Actor outside colored Folder | Attachment alone doesn't transfer parent color | Not run |
| CHR-05 | Assign Red override then Clear Override | Parent's color becomes effective again | Not run |
| CHR-06 | Choose No Color inside colored Folder | Inherited color blocked for otherwise-unassigned branch | Not run |
| CHR-07 | Rename/recolor preset and reload | Existing assignments keep same GUID identity | Not run |
| CHR-08 | Delete used named preset | Missing preset visible without reassignment | Not run |
| CHR-09 | Two presets with identical RGB | Visually same, still distinct logical matching groups | Not run |

## B. Selection and Outliner

| ID | Scenario | Expected | Status |
| --- | --- | --- | --- |
| CHR-10 | Click selected vs unselected swatch | Selected-row batch vs single clicked target | Not run |
| CHR-11 | Mixed Actor/Folder selection | Multiple colors state and consistent bulk assignment | Not run |
| CHR-12 | Select Matching Color and Matching Siblings | Correct loaded matches by identity, correct immediate parent | Not run |
| CHR-13 | Shift+match | Existing selection preserved and matches added | Not run |
| CHR-14 | Outliner search hides Actor/Folder matches | Filtered Actors can match; hidden Folder notification | Not run |
| CHR-15 | Copy named inherited preset, paste elsewhere | Effective preset identity preserved in destination | Not run |
| CHR-16 | Paste invalid ordinary clipboard text | Action unavailable, no assignment mutation | Not run |
| CHR-17 | Tint compatible Actor/Folder icons on/off | Native icons tinted and restored without data loss | Not run |

## C. Viewport and source control

| ID | Scenario | Expected | Status |
| --- | --- | --- | --- |
| CHR-18 | Select differently colored Static Mesh/Nanite Actors | Per-Actor Chroma outlines, no permanent Component writes | Not run |
| CHR-19 | Select more than six unique visible colors | Six extra color slots maximum, native overflow | Not run |
| CHR-20 | Reserve external explicit outline slots | Existing slots respected; no override conflicts | Not run |
| CHR-21 | Actor Coloration → Chroma and back to Lit | Organization visualization only, materials unchanged | Not run |
| CHR-22 | Hover geometry in Chroma view | Actor name, preset/hex/source appears; pauses during drag | Not run |
| CHR-23 | Empty Actor, Folder, translucent and Landscape | Document each observed support boundary | Not run |
| CHR-24 | Save/reload Actor and native/legacy Folder assignments | Metadata persists in correct package | Not run |
| CHR-25 | Undo/Redo multi-item color assignment | Correct previous values and effective colors restored | Not run |
| CHR-26 | Move/rename/delete legacy Folder, Undo | Metadata keys migrate/clear safely | Not run |
| CHR-27 | Perforce/OFPA two-workspace transfer of colors and palette | Correct packages and DefaultChroma.ini distributed | Not run |
| CHR-28 | Unloaded World Partition Actors | Not changed by loaded-only actions | Not run |
| CHR-29 | Large loaded level, rapid color changes | No severe Outliner or viewport performance regression | Not run |
| CHR-30 | Disable Chroma/close editor | View extensions, overlays, delegates safely released | Not run |

## D. Website and media

| ID | Scenario | Expected | Status |
| --- | --- | --- | --- |
| WEB-01 | Open all five categories and 40 paired pages | Design/Technical switch, breadcrumbs, pager work | Not run |
| WEB-02 | Search page title and phrase occurring only in body | Results include full-text matches and excerpts | Not run |
| WEB-03 | Browser navigation/back and direct `?page=` URL | Correct page/anchor state | Not run |
| WEB-04 | Check 320, 375, 768 and desktop widths | No clipped article images, sticky navigation usable | Not run |
| WEB-05 | Keyboard search, focus rings and reduced motion | Accessible controls and useful fallbacks | Not run |
| WEB-06 | Render real hero/icon/screenshots and placeholder GIF figures | Correct aspect ratios, no broken images | Not run |
| WEB-07 | Replace media by registry ID | Captions and capture instructions remain associated correctly | Not run |

**Reporting:** Record Passed, Failed, Blocked or Not applicable only with real steps/results/logs. Source inspection alone never counts as a passed runtime test.

[Documentation Audit](DOCUMENTATION_AUDIT.md) · [Media Inventory](MEDIA_INVENTORY.md)

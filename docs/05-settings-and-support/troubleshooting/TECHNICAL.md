# Troubleshooting and FAQ — Technical

**Chroma v1.0.1 · Unreal Editor implementation**

## Diagnostic ownership

| Symptom | Source subsystem |
| --- | --- |
| Column absent | `FChromaModule` Actor Browser registration and `FChromaColumn` |
| Wrong swatch/effective color | `Chroma::ResolveActor`, `ResolveFolder`, metadata |
| Missing named preset | `UChromaSettings::Palette` and GUID resolution |
| Matching skips Folder | `FChromaColumn::SelectMatching` filtered-folder safety |
| Icons not tinted | `FChromaLabelColumn`, compatible native Slate icon, setting |
| Outline unavailable | `FChromaSelectionOutline`, selection proxy/slot renderer |
| Viewport coloration ineffective | `FActorPrimitiveColorHandler`, `VMI_VisualizeActorColoration` |
| Hover inspector absent | `SChromaViewportHover`, editor view gating and hit proxy |
| Saving unexpected | `Chroma::Write`, `FMetaData`, owning package/source control |

## Controlled reproduction

Test in a simple UE 5.8.x editor world with one Static Mesh Actor and one Folder. Start with a default named palette, toggle one assignment, save/reload and Undo/Redo. Add filtering, selection, World Partition, icon tinting, outline slots or special mesh paths only after the simple case is understood.

## Known limitations

Only loaded editor Actors are enumerated for used colors/matching. Filtered Folder rows aren't always safely selectable. Selection outlines are limited to extra slots 2–7 and are mainly validated for ordinary meshes/Nanite. Actor Coloration depends on engine handler support. No Chroma runtime system should be expected in packaged games.

## Verification status

The README and `Doc/Sources.md` report local editor confirmation of core workflows and a subset of renderer cases. This documentation build did not independently rerun all engine or source-control tests. See [Verification Matrix](../../VERIFICATION_MATRIX.md) for pending cases.

## Source references

- [ChromaState.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaState.cpp)
- [ChromaModule.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaModule.cpp)
- [ChromaSettings.h](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Public/ChromaSettings.h)
- [ChromaAPI.h](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Public/ChromaAPI.h)

[Read Design](DESIGN.md) for user-facing behavior. **QA:** source-reviewed; no new UE build or Perforce testing is claimed here.

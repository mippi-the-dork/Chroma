# Matching Selection — Technical

**Chroma v1.0.1 · Unreal Editor implementation**

## Enumeration and matching

`FChromaColumn::AllItems` uses `FActorFolders::ForEachFolder` plus `TActorIterator<AActor>` to enumerate loaded eligible editor items. `SelectMatching` checks each item's resolved effective assignment and optional same-parent constraint.

`Matches` compares named preset GUID identities first. If either item has a preset ID, the IDs must match. Otherwise, it checks the presence of color and compares stored assignment values for custom colors.

## Immediate-parent logic

`Parent` uses an Actor's attach parent when present, otherwise its Outliner Folder. Folders use their parent Folder. **This sibling relationship is for selection scope**; it does not change Folder-only color inheritance rules.

## Filtered rows

When a matching Actor is not materialized as a visible tree item, `SelectMatching` can construct an Actor tree item for selection. For filtered-out Folders, the code deliberately does not synthesize an unsafe selection row: it increments a hidden-folder count and displays a notification recommending that the Outliner filter be cleared.

## Shift behavior

The code checks `FSlateApplication::Get().GetModifierKeys().IsShiftDown()` before replacing the set. In Shift mode it preserves the current Outliner selection and the selected native Actors, then adds new matching items without duplicate IDs.

## Preconditions

Matching requires a live Outliner and normal editor interaction (`GEditor` and no active `PlayWorld`). Unloaded World Partition Actor descriptors are not enumerated.

## Source references

- [ChromaColumn.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaColumn.cpp)
- [ChromaModule.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaModule.cpp)
- [ChromaSelectionOutline.h](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaSelectionOutline.h)
- [ChromaViewportHover.h](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaViewportHover.h)

[Read Design](DESIGN.md) for user workflows. **Validation:** source-reviewed; specialized viewport and renderer behavior requires project-specific editor QA.

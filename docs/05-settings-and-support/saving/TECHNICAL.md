# Saving and Team Workflows — Technical

**Chroma v1.0.1 · Unreal Editor implementation**

## Package-owned metadata

`Chroma::ActorTarget` uses an Actor metadata key `Chroma.Assignment.V1` in that Actor's owning `UPackage`. `FolderTarget` uses the native `UActorFolder` object when present, else an owning `ULevel` with a path-based metadata key `Chroma.Folder.V1/<path>`.

`Chroma::Read` retrieves `FMetaData::GetValue`. `Chroma::Restore` sets or removes metadata, marks the package dirty and increments a viewport revision counter. No new Actor/Component object is serialized for each assignment.

## Transaction implementation

`Chroma::FAssignmentChange` derives from `FCommandChange` and captures old/new values for one metadata key. `Write` calls `GUndo->StoreUndo` when undo is active. `Assign` wraps a bulk operation in `FScopedTransaction`.

## Folder moves and deletes

Native Folder metadata follows the Folder object. Path-backed legacy Folder values are remapped for moved folder subtrees by `FolderMoved`, using the `Chroma.Folder.V1/` prefix. `FolderDeleted` handles legacy path cleanup.

## Revisions and refresh

Palette changes and relevant editor/folder events call `RequestViewportRefresh`. The primitive color handler refreshes when the revision or world changes while the Chroma view mode is active.

## Source-control boundary

Chroma does not implement a Perforce provider, checkout system, merge strategy or repository synchronization. Protecting against unrelated package edits and validating team-transfer scenarios remains the user's standard project QA responsibility.

## Source references

- [ChromaState.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaState.cpp)
- [ChromaModule.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaModule.cpp)
- [ChromaSettings.h](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Public/ChromaSettings.h)
- [ChromaAPI.h](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Public/ChromaAPI.h)

[Read Design](DESIGN.md) for user-facing behavior. **QA:** source-reviewed; no new UE build or Perforce testing is claimed here.

# Saving and Team Workflows — Design

**Chroma v1.0.1 · User guide**

## What gets saved where?

Chroma doesn't place a runtime Component on each Actor. An Actor or Folder's color assignment is saved as **editor package metadata**. The location depends on the item and the folder representation: its Actor package, native Folder package, or associated level package.

Named presets and presentation preferences are saved through Chroma's **project configuration**.

## Saving a colored level

1. Apply your desired colors to loaded Actors and Folders.
2. Save the affected map and external Actor/Folder packages using **File → Save** or **Save All**.
3. If you've modified the named palette, include **Config/DefaultChroma.ini** with the project changes.
4. Reopen the map and verify the colors and folder inheritance look as expected.

## Perforce and other team tools

Share the affected packages and config through your usual source-control workflow. Chroma does not automatically check files out, submit revisions, synchronize collaborators or resolve file conflicts.

Under **One File Per Actor**, changing an Actor's explicit Chroma assignment may dirty that Actor's external package. A Folder color change may be stored with a native Folder or level package depending on the project.

## Undo and Redo

Assignment actions participate in Unreal's standard transaction history. Copy/Paste and bulk application use these same metadata changes. An Undo restores the previous direct assignment, after which the effective inherited result is recomputed.

## Limits

Current user documentation is based on source and reported local testing; cross-workspace Perforce transfers, failed saves and conflict handling have not been comprehensively validated here. Test in a disposable level before changing large team maps.

---

[Read Technical](TECHNICAL.md) for source implementation and native engine boundaries.

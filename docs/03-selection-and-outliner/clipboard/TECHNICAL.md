# Copy, Paste and Context Menu — Technical

**Chroma v1.0.1 · Unreal Editor implementation**

## Clipboard protocol

<!-- Media target: IMAGE | clipboard-format | docs/assets/media/clipboard-format.png -->
<figure class="doc-media" data-kind="image" data-media-id="clipboard-format">
  <img src="../../assets/media-placeholder.png" alt="Chroma clipboard values preserve a structured assignment type so paste can validate what it receives." loading="lazy">
  <figcaption>Chroma clipboard values preserve a structured assignment type so paste can validate what it receives.
    <span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Draw a small flow diagram from Copy effective assignment → text prefix Chroma.V1: → supported payload P:GUID, C:RRGGBB, or N → validation → Paste to selected target. Keep the format labels readable.</span>
  </figcaption>
</figure>


`FPlatformApplicationMisc::ClipboardCopy` writes a string beginning `Chroma.V1:`, followed by the effective assignment. `ClipboardValue` requires that prefix, strips it, decodes the remainder and accepts valid custom/preset representations or explicit `N`.

The palette's Copy action uses `Resolve(Item).Assignment` rather than only the item's direct metadata; an empty effective assignment is normalized to `N` for copying.

## Paste validity

The Paste menu entry uses `FCanExecuteAction` to check whether the clipboard can be decoded. A valid paste routes to `Assign(Batch, Value)`; this is the same transaction and per-target metadata write logic used by normal color choices.

## Context menu integration

`FChromaModule::RegisterActorMenu` extends `LevelEditor.ActorContextMenu` via `UToolMenus`. The submenu receives originating Outliner selections or the viewport hit Actor when appropriate; it uses `FChromaColumn::MakeActorContextMenu` to build the palette.

## Limitations

The paste protocol is an internal Chroma clipboard format, not a general-purpose color-picker text API. It should not be confused with plain hex-value copying from another application.

## Source references

- [ChromaColumn.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaColumn.cpp)
- [ChromaModule.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaModule.cpp)
- [ChromaSelectionOutline.h](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaSelectionOutline.h)
- [ChromaViewportHover.h](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaViewportHover.h)

[Read Design](DESIGN.md) for user workflows. **Validation:** source-reviewed; specialized viewport and renderer behavior requires project-specific editor QA.

# Overrides, Clear Override and No Color — Technical

**Chroma v1.0.1 · Unreal Editor implementation**

## Values and decoding

<!-- Media target: IMAGE | override-encoding | docs/assets/media/override-encoding.png -->
<figure class="doc-media" data-kind="image" data-media-id="override-encoding">
  <img src="../../assets/media-placeholder.png" alt="The empty assignment and explicit No Color value follow different resolution paths." loading="lazy">
  <figcaption>The empty assignment and explicit No Color value follow different resolution paths.
    <span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Create a comparison diagram of two otherwise identical Actors beneath a Green Folder: one with empty direct metadata inherits Green; the other with N returns No Color. Show P:GUID and C:RRGGBB as explicit overrides.</span>
  </figcaption>
</figure>


Chroma stores four assignment forms: empty string (no explicit assignment), `N` (No Color), `P:<GUID>` (named preset), and `C:<RRGGBB>` (custom color). `Chroma::Decode` returns the resolved state, including `bHasColor`, `bMissingPreset` and `Assignment`.

The menu's **Clear Override** calls `Assign(Batch, FString())` to remove the metadata value, letting `ResolveActor`/ `ResolveFolder` resume traversal. **No Color** calls `Assign(Batch, TEXT("N"))`; this is a nonempty stored value, so hierarchy traversal stops there.

## Inherited boundary

`ResolveFolder` returns at the first nonempty metadata value. An `N` assignment decodes as No Color without `bHasColor`, so descendants encounter this boundary unless they have their own deeper override.

## Transaction behavior

`Chroma::Write` compares before and after; unchanged values do not produce writes. Changed values use metadata undo changes and mark their package dirty. Folder moves and deletions also handle path-backed legacy metadata separately.

## Source references

- [ChromaState.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaState.cpp)
- [ChromaColumn.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaColumn.cpp)
- [ChromaModule.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaModule.cpp)

[Read Design](DESIGN.md) for practical user workflows. **Validation:** implementation inspected in source; additional clean-project runtime QA is tracked separately.

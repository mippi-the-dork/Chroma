# Folder Inheritance — Technical

**Chroma v1.0.1 · Unreal Editor implementation**

## Folder resolution algorithm

<!-- Media target: IMAGE | folder-resolution-chain | docs/assets/media/folder-resolution-chain.png -->
<figure class="doc-media" data-kind="image" data-media-id="folder-resolution-chain">
  <img src="../../assets/media-placeholder.png" alt="Effective color is resolved from the nearest explicit assignment in an Actor's containing folder hierarchy." loading="lazy">
  <figcaption>Effective color is resolved from the nearest explicit assignment in an Actor's containing folder hierarchy.
    <span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Draw a simple Actor → containing Folder → parent Folder chain with a direct Actor value checked first. Show the search stopping at the first nonempty assignment, including N as a stop condition; distinguish Actor attachments from Folder paths.</span>
  </figcaption>
</figure>


`Chroma::ResolveFolder(UWorld*, FFolder)` loops through the supplied Folder and its `GetParent()` chain. The first nonempty stored value is decoded into `FChromaResolvedColor`; `bInherited` records whether the resolution climbed to a parent, and `Source` holds the folder path.

`ResolveActor` first checks the Actor's metadata. Only when no direct value is present does it call `ResolveFolder(Actor->GetWorld(), Actor->GetFolder())`, marking the resolved value inherited when appropriate.

## Storage strategies

`FolderTarget` writes native Folder metadata to a `UActorFolder` object when available. Legacy/transient Folder paths use a key on the associated `ULevel`: `Chroma.Folder.V1/<path>`. `FolderMoved` migrates such legacy path keys for moved subtrees; native Folder identity normally follows its object.

## Important non-effects

No inheritance is written to child Actor packages just because a Folder changes. Actor attachments are not traversed for inheritance. The editor module requests a viewport-color refresh after relevant folder and Actor changes, but the outcome remains an editor display calculation.

## World Partition

Chroma resolves loaded Actors; unloaded Actor descriptors are not visited by the swatch/selection workflows. Folder metadata location varies with the project's native/legacy folder representation.

## Source references

- [ChromaState.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaState.cpp)
- [ChromaColumn.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaColumn.cpp)
- [ChromaModule.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaModule.cpp)

[Read Design](DESIGN.md) for practical user workflows. **Validation:** implementation inspected in source; additional clean-project runtime QA is tracked separately.

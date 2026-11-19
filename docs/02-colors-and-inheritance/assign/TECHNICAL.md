# Assign Colors — Technical

**Chroma v1.0.1 · Unreal Editor implementation**

## Menu and assignment path

`FChromaColumn::Menu` constructs the current-color section, used-color entries, project palette and custom picker. The custom picker uses `FColorPickerArgs` with alpha disabled and commits through the same assignment action as a named preset.

`FChromaColumn::Targets` resolves clicked versus selected-row scope. `Assign` starts `FScopedTransaction`; `Chroma::Write` records before/after metadata values as `FCommandChange` when Undo is active and marks the owning package dirty.

## Encoded states

<!-- Media target: IMAGE | assignment-data-flow | docs/assets/media/assignment-data-flow.png -->
<figure class="doc-media" data-kind="image" data-media-id="assignment-data-flow">
  <img src="../../assets/media-placeholder.png" alt="An assignment is encoded as a preset reference, custom RGB value, No Color marker or absence of an override." loading="lazy">
  <figcaption>An assignment is encoded as a preset reference, custom RGB value, No Color marker or absence of an override.
    <span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Create a compact diagram: Outliner swatch/menu → target selection → metadata Write/Undo → encoded assignment choices P:GUID, C:RRGGBB, N and empty. Differentiate direct storage from effective resolution.</span>
  </figcaption>
</figure>


`Chroma::ActorTarget` maps a valid editor Actor to metadata key `Chroma.Assignment.V1`. `FolderTarget` maps native `UActorFolder` objects similarly or falls back to owning level metadata using `Chroma.Folder.V1/` plus the folder path for legacy folders.

Assignments are encoded as a preset GUID (`P:`), an opaque custom-color string (`C:` + six hex digits), explicit No Color (`N`), or an empty value meaning no direct assignment.

## Effective result

`ResolveActor` checks its direct value, then calls `ResolveFolder` on its containing folder. That result is computed for display, matching and editor visualization; it is not copied into Actor materials or saved runtime Components.

## Source references

- [ChromaState.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaState.cpp)
- [ChromaColumn.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaColumn.cpp)
- [ChromaModule.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaModule.cpp)

[Read Design](DESIGN.md) for practical user workflows. **Validation:** implementation inspected in source; additional clean-project runtime QA is tracked separately.

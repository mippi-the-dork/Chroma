# Your First Color Workflow — Technical

**Chroma v1.0.1 · Unreal Editor implementation**

## Swatch row construction

`FChromaColumn::ConstructRowWidget` returns a compact `SComboButton` with no down arrow for valid Actor/Folder tree items. The swatch displays the result of `Chroma::ResolveActor` or `ResolveFolder`. Left-click opens the palette; right-click can open the action-only menu.

## Scope of a click

`FChromaColumn::Targets` checks whether the clicked row is already within the Outliner's selected set. If so, the action targets valid selected Actor and Folder rows. If not, only the clicked row is targeted. `Assign` wraps changes in `FScopedTransaction` and writes to each target.

## Saved behavior

`Chroma::Write` uses a metadata change object for undo and marks the owning package dirty when a stored assignment changes. Inheritance is resolved dynamically; child Actors do not need a copied direct assignment. Save packages through Unreal's normal operations.

## Rendering and tool context

`FChromaModule` registers the swatch column for the Actor Browser, wraps compatible native icon content, and registers editor viewport color presentation separately. Changing a color doesn't author new materials or Components.

## Source references

- [ChromaState.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaState.cpp)
- [ChromaColumn.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaColumn.cpp)
- [ChromaModule.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaModule.cpp)

[Read Design](DESIGN.md) for practical user workflows. **Validation:** implementation inspected in source; additional clean-project runtime QA is tracked separately.

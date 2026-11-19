# What Chroma Does — Technical

**Chroma v1.0.1 · Unreal Editor implementation**

## Editor-only integration

`Chroma.uplugin` declares the `Chroma` module as `Editor`, loaded `PostEngineInit`, allowing `Win64` and targeting Unreal Engine 5.8.0. The documented plugin version is 1.0.1, with UE 5.8.2 testing noted in the README.

## Systems involved

`FChromaModule` registers an `FChromaColumn` in the Actor Browser immediately before Item Label, wraps the existing label-column factory to tint compatible native icons, contributes Actor context-menu actions, registers a primitive Actor Coloration handler and a scene-view extension for selection outlines, and adds a viewport hover overlay.

`Chroma::ResolveActor` and `ResolveFolder` compute effective color from direct assignment and the folder hierarchy. They expose color/identity/source through `FChromaResolvedColor`; they do not modify native material or lighting properties.

## Ownership

Actor and Folder assignments are metadata in their owning `UPackage`. The shared named palette and two presentation toggles belong to `UChromaSettings` (`Config=Chroma`, `DefaultConfig`). Selection-outline tint and hover presentation are transient editor visuals.

## Boundaries

The API and assignment code accept Actors in `EWorldType::Editor`, not packaged worlds. The viewport color handler targets supported primitive geometry. Loaded-world enumeration does not include unloaded World Partition Actor packages.

## Source references

- [ChromaState.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaState.cpp)
- [ChromaColumn.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaColumn.cpp)
- [ChromaModule.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaModule.cpp)

[Read Design](DESIGN.md) for practical user workflows. **Validation:** implementation inspected in source; additional clean-project runtime QA is tracked separately.

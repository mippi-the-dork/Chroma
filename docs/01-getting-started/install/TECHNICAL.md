# Installation and Compatibility — Technical

**Chroma v1.0.1 · Unreal Editor implementation**

## Descriptor and build scope

`Chroma.uplugin` describes an `Editor` module with `LoadingPhase: PostEngineInit`, `PlatformAllowList: ["Win64"]`, `EngineVersion: 5.8.0` and `VersionName: 1.0.1`. `CanContainContent` is false. There is no separate runtime module.

`Chroma.Build.cs` declares editor-facing dependencies including SceneOutliner, LevelEditor, UnrealEd, Slate, PropertyEditor and DeveloperSettings. The plugin is compiled for an Unreal Editor target, not linked into packaged-game runtime builds.

## Startup

`FChromaModule::StartupModule` registers style resources, Outliner column creation, Actor context-menu hooks, folder move/delete listeners, primitive-color handler, view-extension outline support, and editor refresh callbacks. `IsRunningCommandlet()` prevents normal editor UI registration for commandlets.

## Diagnostic approach

If Chroma doesn't appear, distinguish module loading from Outliner column visibility. If palette menus appear but view coloring doesn't, inspect the enabled view mode, renderer support and project setting rather than assuming a module-load failure.

## Release cautions

The README documents Fab and release installation steps conditionally; it does **not** establish that every example archive or Fab listing is currently published. Always verify the actual current release artifact before downloading or promising binary compatibility.

## Source references

- [ChromaState.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaState.cpp)
- [ChromaColumn.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaColumn.cpp)
- [ChromaModule.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaModule.cpp)

[Read Design](DESIGN.md) for practical user workflows. **Validation:** implementation inspected in source; additional clean-project runtime QA is tracked separately.

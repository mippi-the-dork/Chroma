# Project Settings — Technical

**Chroma v1.0.1 · Unreal Editor implementation**

## UDeveloperSettings data

`UChromaSettings` is `UCLASS(Config=Chroma, DefaultConfig)`. It exposes `TArray<FChromaPreset> Palette`, `bool bTintOutlinerIcons=true` and `bool bTintSelectionOutlines=true`. It appears under the **Project / Plugins / Chroma** settings section.

`FChromaPreset` contains a GUID identity, name and linear color; the ID is `VisibleAnywhere`, not normally edited. The default palette creates six entries with fixed GUIDs and sRGB color choices.

## Post-edit behavior

`PostEditChangeProperty` checks for invalid/duplicate GUIDs, assigns a new GUID as necessary, forces alpha to 1, supplies a default nonblank name and calls `Chroma::RequestViewportRefresh()`. `PostEditUndo` refreshes default configuration and viewport colors.

## Consumer behavior

`FChromaLabelColumn` reads the Outliner toggle. `FChromaSelectionOutline` checks the outline toggle before applying render-proxy overrides. Neither toggle modifies Actor/Folder assignment metadata.

## Source control

Project config and package metadata are separate versioned resources. Changing shared named presets requires distributing `Config/DefaultChroma.ini`; color assignments can remain in external Actor and native Folder packages.

## Source references

- [ChromaState.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaState.cpp)
- [ChromaModule.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaModule.cpp)
- [ChromaSettings.h](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Public/ChromaSettings.h)
- [ChromaAPI.h](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Public/ChromaAPI.h)

[Read Design](DESIGN.md) for user-facing behavior. **QA:** source-reviewed; no new UE build or Perforce testing is claimed here.

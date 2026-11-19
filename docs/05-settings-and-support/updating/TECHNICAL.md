# Updating and Support — Technical

**Chroma v1.0.1 · Unreal Editor implementation**

## Compatibility contract

`Chroma.uplugin` documents `VersionName: 1.0.1`, `EngineVersion: 5.8.0`, `Editor` module, `PostEngineInit` loading and Win64 allowlist. This is evidence of the intended support target, not a compatibility test for each future engine patch.

## Persisted upgrade data

Color assignments use package metadata keys `Chroma.Assignment.V1` or `Chroma.Folder.V1/<path>` for applicable legacy Folder paths. Presets are `FChromaPreset` entries in `DefaultChroma.ini` with GUID identity. A plugin reinstall should not reset those user-owned packages/config values.

## Native dependencies and potential migration

The implementation uses Unreal editor-only types such as `SSceneOutliner`, `UActorFolder`, `FActorPrimitiveColorHandler`, `FSceneViewExtensionBase` and Slate icon widgets. A new engine version can change those internals or rendering paths and should undergo build and editor QA rather than simply updating `EngineVersion`.

## Bug reproduction requirements

For selection, identify whether the clicked row was already selected; for inherited colors, provide direct and Folder assignments; for renderer issues, identify primitive types, viewport mode and outline-color slot usage. For save issues, include the owning package/source-control state.

## Release validation

The repository's `Doc/Sources.md` records prior observed editor tests, but clean-project packaging and source-control transfer are still distinct validation obligations. See the [Verification Matrix](../../VERIFICATION_MATRIX.md) for the proposed reproducible checks.

## Source references

- [ChromaState.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaState.cpp)
- [ChromaModule.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaModule.cpp)
- [ChromaSettings.h](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Public/ChromaSettings.h)
- [ChromaAPI.h](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Public/ChromaAPI.h)

[Read Design](DESIGN.md) for user-facing behavior. **QA:** source-reviewed; no new UE build or Perforce testing is claimed here.

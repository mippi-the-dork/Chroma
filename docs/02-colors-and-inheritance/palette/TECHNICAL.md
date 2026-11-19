# Named Project Palette — Technical

**Chroma v1.0.1 · Unreal Editor implementation**

## Settings class and persisted identity

`UChromaSettings` is a `UDeveloperSettings` class declared `Config=Chroma, DefaultConfig`. `Palette` is a configurable array of `FChromaPreset` structs with `FGuid Id`, `FString Name` and `FLinearColor Color`. The ID is visible but not directly editable.

`UChromaSettings::UChromaSettings` supplies six defaults with stable preassigned GUIDs and RGB values. The settings change handler validates duplicate/missing IDs, forces alpha to 1 and normalizes empty names; it requests a viewport color refresh.

## Stored references

Assignments persist the preset's GUID as `P:<digits>`. `Chroma::Decode` resolves the GUID against the current `Palette`. Changing a preset's name or color updates the resolved result without rewriting all assignments.

If a GUID no longer resolves, `bMissingPreset` is true and `Name` becomes Missing preset; the original assignment is kept. Two presets with identical visual colors still have different GUID identities, affecting matching selection.

## Team-data ownership

Color preset definitions belong in the project Chroma configuration, conventionally `Config/DefaultChroma.ini`. Actor/Folder metadata may refer to these GUIDs; package and config files must travel together for consistent results.

## Source references

- [ChromaState.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaState.cpp)
- [ChromaColumn.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaColumn.cpp)
- [ChromaModule.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaModule.cpp)

[Read Design](DESIGN.md) for practical user workflows. **Validation:** implementation inspected in source; additional clean-project runtime QA is tracked separately.

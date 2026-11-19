# Custom and Used Colors — Technical

**Chroma v1.0.1 · Unreal Editor implementation**

## Custom encoding

`Chroma::Custom` converts the chosen `FLinearColor` to sRGB `FColor`, formats an uppercase hex string and stores `C:<RRGGBB>`. The `Chroma::Decode` custom path converts that value back with `FLinearColor::FromSRGBColor`. The color picker disables alpha and only commits when the user confirms.

## Used-color discovery

`FChromaColumn::Menu` calls `AllItems()` to enumerate valid loaded editor Actors and Folders, reads effective values with `Resolve`, collects their `Assignment` strings and sorts the results by decoded name. The list is computed from loaded editor items, not by scanning unloaded World Partition packages.

## Matching semantics

`Matches` first checks preset GUID identity if either result has one. Otherwise it compares whether both have a color; if both do, it compares the stored assignment. These rules prevent distinct named presets that share the same RGB color from silently merging into one named group.

## Limitations

A custom color's stored hex value is the identity used by matching. Color picker and sRGB rounding mean not every arbitrary linear floating-point color survives as an exact linear value; Chroma intentionally stores a compact six-digit sRGB color.

## Source references

- [ChromaState.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaState.cpp)
- [ChromaColumn.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaColumn.cpp)
- [ChromaModule.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaModule.cpp)

[Read Design](DESIGN.md) for practical user workflows. **Validation:** implementation inspected in source; additional clean-project runtime QA is tracked separately.

# Tinted Outliner Icons — Technical

**Chroma v1.0.1 · Unreal Editor implementation**

## Label-column wrapper

`FChromaModule` intercepts the Actor Browser's existing **Item Label column factory**, wrapping the previously registered factory rather than replacing it globally. `FChromaLabelColumn` forwards native behavior and targets recognized icon widgets for tinting.

`UChromaSettings::bTintOutlinerIcons` is a configurable project setting that defaults to true. The effective color comes from `Chroma::ResolveActor` or `ResolveFolder`, so inherited values are treated the same as direct values.

## Native compatibility

The wrapper applies tint only where the resulting label's Slate widget structure is compatible. It does not alter text editing, Outliner row identity or shared engine icon brush resources. Custom label-column renderers and strongly colored icon artwork may produce an unsupported or different visual result.

## Presentation versus data

No Actor or Folder metadata write is necessary to enable/disable icon tinting. Color assignments still persist independently of this display option, and the label column does not install runtime Components or modify materials.

## Source references

- [ChromaColumn.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaColumn.cpp)
- [ChromaModule.cpp](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaModule.cpp)
- [ChromaSelectionOutline.h](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaSelectionOutline.h)
- [ChromaViewportHover.h](https://github.com/mippi-the-dork/Chroma/blob/main/Source/Chroma/Private/ChromaViewportHover.h)

[Read Design](DESIGN.md) for user workflows. **Validation:** source-reviewed; specialized viewport and renderer behavior requires project-specific editor QA.

# Tinted Outliner Icons — Design

**Chroma v1.0.1 · User guide**

## Make folder organization visible immediately

<!-- Media target: IMAGE | tinted-native-icons | docs/assets/media/tinted-native-icons.png -->
<figure class="doc-media" data-kind="image" data-media-id="tinted-native-icons">
  <img src="../../assets/media-placeholder.png" alt="Compatible native Actor and Folder icons can display their inherited or directly assigned Chroma colors." loading="lazy">
  <figcaption>Compatible native Actor and Folder icons can display their inherited or directly assigned Chroma colors.
    <span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Capture an expanded Outliner with tinted green Environment, orange Gameplay and yellow Lighting icons. Include examples of both Folder icons and different Actor-type icons, with the Chroma swatches visible for comparison.</span>
  </figcaption>
</figure>


With **Tint Outliner Icons** enabled, compatible native Actor and Folder icons reflect their **effective Chroma color**. A folder colored Green can tint the icons of its inheriting Actors, while a nested Yellow override changes its branch.

The label text stays readable and native icons still communicate their normal Actor or Folder type. Chroma does not replace the built-in label behavior with a separate custom name widget.

## Turn icon tinting on or off

Open **Project Settings → Plugins → Chroma → Outliner** and set **Tint Outliner Icons**. It is enabled by default. Disabling it restores ordinary native icon appearance without clearing Chroma assignments.

## Example

In one World Outliner, Green Environment folders and mesh rows, Orange Gameplay Actors and Yellow Lighting icons become easier to distinguish without opening the palette for every row.

## What can look different

Some custom icons contain baked-in artwork/colors and may tint unpredictably. Third-party Outliner label implementations may not have a compatible native icon widget for Chroma to tint. Chroma leaves incompatible layouts intact rather than forcing a generic substitute.

## Persistence

Icon tinting is only presentation. The actual assignment stays in package metadata; changing this setting doesn't rewrite Actor colors or runtime content.

---

[Read Technical](TECHNICAL.md) for native Unreal integration, data ownership and implementation limits.

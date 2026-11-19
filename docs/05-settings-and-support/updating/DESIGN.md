# Updating and Support — Design

**Chroma v1.0.1 · User guide**

## Updating a precompiled release

<!-- Media target: IMAGE | updating-plugin-folder | docs/assets/media/updating-plugin-folder.png -->
<figure class="doc-media" data-kind="image" data-media-id="updating-plugin-folder">
  <img src="../../assets/media-placeholder.png" alt="A complete Chroma plugin directory can be replaced while keeping saved project color assignments in project content and configuration." loading="lazy">
  <figcaption>A complete Chroma plugin directory can be replaced while keeping saved project color assignments in project content and configuration.
    <span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Show YourProject/Plugins/Chroma as a complete folder in File Explorer next to an example versioned release archive. Include a callout indicating Unreal Editor is closed before replacing the folder.</span>
  </figcaption>
</figure>


1. Close Unreal Editor.
2. Download the new **compatible** Chroma plugin package from [Releases](https://github.com/mippi-the-dork/Chroma/releases) if available.
3. Replace the *complete* `YourProject/Plugins/Chroma/` directory.
4. Reopen the project, enable if necessary, and verify your existing saved folder/Actor colors.

Replacing the complete directory avoids mixing old Binaries, Source and Resources with newer versions.

## Updating a source installation

Pull the intended Chroma commit/tag in your project plugin directory, regenerate files if needed, and rebuild your Editor target. Do not mix a precompiled release installation and an unrelated source checkout in the same folder.

## Compatibility

The current documented version is **1.0.1**, targeting Unreal Engine **5.8.x**, with the README reporting testing on **5.8.2**, for **Win64** and Editor use. Compatibility with other versions/platforms is not established by the descriptor.

## Before reporting a bug

Try it on one Actor and Folder in a disposable level. Capture the Unreal Engine version, Chroma version, relevant settings, Editor or World Partition context, steps, and any Output Log messages.

Open an issue at [Chroma Issues](https://github.com/mippi-the-dork/Chroma/issues). Include screenshots or a short GIF when the issue is visual.

## What happens to my colors on an update?

The assignments reside in Actor/Folder/level packages, and named presets are in project config—not inside the plugin install folder. Replacing a plugin directory does not intentionally remove saved project color data. Back up the project and verify changes before major upgrades.

## Roadmap

See the [Roadmap](../../ROADMAP.md) for release status. Additional features should not be presented as shipped until backed by an actual Chroma release.

---

[Read Technical](TECHNICAL.md) for source implementation and native engine boundaries.

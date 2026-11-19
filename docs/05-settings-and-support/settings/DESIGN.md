# Project Settings — Design

**Chroma v1.0.1 · User guide**

## Find the settings

Open **Project Settings → Plugins → Chroma**. The settings are shared at the project level and divide into three areas.

| Group | Setting | Default |
| --- | --- | --- |
| **Project Palette** | Named entries with Name and Color | Six named colors |
| **Outliner** | **Tint Outliner Icons** | Enabled |
| **Viewport** | **Tint Selection Outlines** | Enabled |

Use **Edit Named Colors...** from any Chroma palette to jump to the project settings.

## Working with the palette

Choose names that help your team identify organizational roles. Rename and recolor existing presets freely: Actors referring to those presets retain their stable preset identity. Removing a preset that is still used makes those assignments show **Missing preset**, rather than silently changing them.

## Presentation switches

<!-- Media target: IMAGE | presentation-toggles | docs/assets/media/presentation-toggles.png -->
<figure class="doc-media" data-kind="image" data-media-id="presentation-toggles">
  <img src="../../assets/media-placeholder.png" alt="Project Settings independently controls tinted Outliner icons and colored viewport selection outlines." loading="lazy">
  <figcaption>Project Settings independently controls tinted Outliner icons and colored viewport selection outlines.
    <span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Capture Project Settings &gt; Plugins &gt; Chroma with Outliner and Viewport categories expanded. Keep both Tint Outliner Icons and Tint Selection Outlines checkboxes clearly visible and their current enabled defaults indicated.</span>
  </figcaption>
</figure>


Disabling **Tint Outliner Icons** restores normal compatible icons without removing Chroma color assignments. Disabling **Tint Selection Outlines** restores ordinary viewport outlines, also without removing assignments.

The separate **Actor Coloration → Chroma** view mode is selected from the viewport; it's not one of these two setting toggles.

## Sharing settings

Named colors live in the project's Chroma configuration (usually **Config/DefaultChroma.ini**). For teammates to see the same preset names and colors, share this config alongside affected Actor and Folder packages.

## Color consistency

Chroma's actual assignments belong to Actors and Folders. A setting can alter how colors are *displayed* without replacing which color an item *has*.

---

[Read Technical](TECHNICAL.md) for source implementation and native engine boundaries.

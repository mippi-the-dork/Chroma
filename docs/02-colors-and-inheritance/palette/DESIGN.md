# Named Project Palette — Design

**Chroma v1.0.1 · User guide**

## Give colors a shared meaning

<!-- Media target: IMAGE | named-palette-settings | docs/assets/media/named-palette-settings.png -->
<figure class="doc-media" data-kind="image" data-media-id="named-palette-settings">
  <img src="../../assets/media-placeholder.png" alt="Named project presets keep their identity when a team changes their names or visible colors." loading="lazy">
  <figcaption>Named project presets keep their identity when a team changes their names or visible colors.
    <span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Show Project Settings &gt; Plugins &gt; Chroma with the Project Palette expanded. Display at least four clearly named colors and their swatches, including Name and Color fields and the ability to add entries.</span>
  </figcaption>
</figure>


Use **Project Settings → Plugins → Chroma** or choose **Edit Named Colors...** in the Chroma swatch menu. Each named entry contains a **Name** and **Color**. The shipped starting palette includes Red, Orange, Yellow, Green, Blue and Purple, but projects can rename, recolor, delete or add entries.

A useful project vocabulary might be Environment (Green), Gameplay (Orange), Lighting (Yellow), Audio (Purple), Player (Blue), and Critical (Red). These are examples, not mandatory categories.

## Identity matters more than RGB

<!-- Media target: GIF | preset-recolor | docs/assets/media/preset-recolor.gif -->
<figure class="doc-media" data-kind="gif" data-media-id="preset-recolor">
  <img src="../../assets/media-placeholder.png" alt="Recoloring a named preset updates every Actor using that preset without individually editing their assignments." loading="lazy">
  <figcaption>Recoloring a named preset updates every Actor using that preset without individually editing their assignments.
    <span class="media-capture-instructions"><strong>Capture instructions · GIF:</strong> Record a named Gameplay preset used by several Actors. Change only that preset's Color in Project Settings, then show all corresponding Outliner swatches updating while their named identity remains Gameplay.</span>
  </figcaption>
</figure>


A preset keeps a **stable identity** even if its visible color or name changes. If 100 Actors refer to Gameplay, recoloring that preset updates how those Actors appear; you do not need to reassign each Actor. Two named presets can have the **same RGB** and still be different logical groups.

## Missing preset behavior

Deleting a named preset that is still referenced does not silently replace an assignment. Affected items display **Missing preset** until you reassign them or undo the deletion.

## When to use a custom color instead

Custom colors are appropriate for one-off notes, temporary categorization and visual exceptions. Named palette entries are better when many team members should recognize the same semantic group.

## Sharing the palette

Project named colors are stored through Chroma project configuration. Share **Config/DefaultChroma.ini** alongside any Actor/Folder packages referencing those presets so collaborators see consistent results.

---

[Read Technical](TECHNICAL.md) for source implementation, native engine integration and data ownership.

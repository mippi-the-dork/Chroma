# What Chroma Does — Design

**Chroma v1.0.1 · User guide**

## The core idea

<!-- Media target: IMAGE | outliner-color-categories | docs/assets/media/outliner-color-categories.png -->
<figure class="doc-media" data-kind="image" data-media-id="outliner-color-categories">
  <img src="../../assets/media-placeholder.png" alt="Chroma adds a compact color swatch beside Actors and Folders so a level's organization is visible at a glance." loading="lazy">
  <figcaption>Chroma adds a compact color swatch beside Actors and Folders so a level's organization is visible at a glance.
    <span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Capture the Unreal World Outliner with at least three named folders (Environment, Gameplay, Lighting), differently colored child Actors, and Chroma’s swatch column immediately before Item Label. Show the viewport alongside the Outliner for context.</span>
  </figcaption>
</figure>


World Outliner folders organize *where things live*, and Actor names describe *what they are*. Chroma adds a third signal: **what a thing belongs to**. A named color such as Gameplay, Environment or Critical provides context at a glance without renaming or reparenting anything.

## What you can do

- Assign named presets or one-off colors to Actors and Folders with a compact swatch next to **Item Label**.
- Let nested folders and Actors inherit their nearest containing Folder's effective color.
- Override an individual Actor, remove its override, or deliberately suppress inherited color with **No Color**.
- Select all matching loaded Actors, or matching siblings in the same immediate Outliner parent.
- Tint Outliner icons and selection outlines, or visualize supported geometry through **Actor Coloration → Chroma**.

## Practical example

Color the **Environment** folder Green, **Gameplay** Orange, and **Lighting** Yellow. Assign a critical trigger a Red override. The room still has the same materials and attachments, but its organization becomes much easier to scan. Selecting an Orange Actor and choosing **Select Matching Color** helps gather loaded gameplay objects without a name search.

## What does not change

Chroma doesn't create runtime Actors or Components, replace materials, move content between folders, or alter packaged visuals. Color inheritance follows Outliner **folders**, not Actor-to-Actor attachments.

## Start here

Read [Your First Color Workflow](../first-use/DESIGN.md), then [Folder Inheritance](../../02-colors-and-inheritance/inheritance/DESIGN.md).

---

[Read Technical](TECHNICAL.md) for source implementation, native engine integration and data ownership.

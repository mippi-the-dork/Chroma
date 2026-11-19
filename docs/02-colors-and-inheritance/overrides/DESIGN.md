# Overrides, Clear Override and No Color — Design

**Chroma v1.0.1 · User guide**

## Three different states

| State | Meaning | Example |
| --- | --- | --- |
| **Direct color** | The Actor or Folder explicitly chooses a color | A Red Critical Actor inside Green Environment |
| **Clear Override** | Removes the direct assignment and resumes Folder inheritance | The formerly Red Actor returns to Green |
| **No Color** | An explicit choice to stop inheritance | An uncolored Debug branch inside Green Environment |

## Workflow: temporarily override an item

<!-- Media target: GIF | clear-versus-no-color | docs/assets/media/clear-versus-no-color.gif -->
<figure class="doc-media" data-kind="gif" data-media-id="clear-versus-no-color">
  <img src="../../assets/media-placeholder.png" alt="Clear Override restores inherited color, while No Color intentionally blocks the inherited result." loading="lazy">
  <figcaption>Clear Override restores inherited color, while No Color intentionally blocks the inherited result.
    <span class="media-capture-instructions"><strong>Capture instructions · GIF:</strong> Record one Actor inside a Green Folder. Assign Red, choose Clear Override to return to Green, choose No Color to become uncolored, then Clear Override again. Keep the same row and swatch visible throughout.</span>
  </figcaption>
</figure>


1. Give the parent folder Green.
2. Select a child Actor and assign Red. This is a **direct override**.
3. Choose **Clear Override** on the child. Green returns because the folder remains Green.
4. Choose **No Color** instead. The child becomes intentionally uncolored.
5. Choose **Clear Override** again to restore inheritance.

## No Color on a Folder

A No Color Folder acts as an inheritance boundary for otherwise-unassigned items below it. Those items remain uncolored until a lower nested Folder or Actor defines a direct color.

## Common mistake

Clear Override and No Color are **not synonyms**. Clearing says *use what I inherit*; No Color says *don't inherit a color here*. Choosing No Color to “reset” an Actor can keep it uncolored despite a colored parent.

## Undo

These are ordinary Chroma assignment changes. Use Unreal Undo/Redo to restore the previous direct state, and save the appropriate Actor/Folder package when the desired result is finalized.

---

[Read Technical](TECHNICAL.md) for source implementation, native engine integration and data ownership.

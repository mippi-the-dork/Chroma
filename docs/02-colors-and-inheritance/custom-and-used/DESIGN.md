# Custom and Used Colors — Design

**Chroma v1.0.1 · User guide**

## Custom colors

Choose **Custom Color...** from the palette to open Unreal's normal color picker. Chroma accepts a color without creating a named project preset. This is useful for one-off scene notes or quick temporary categorization.

Custom colors are stored as color values. Unlike named presets, they **do not follow** a project palette rename or recolor.

## Used in This Level

The palette includes **Used in This Level (loaded items)**. This list collects colors currently used by loaded Actors and Folders, making it easy to reuse a color already present in the open editor world.

This is not the same as the project named palette. A used color can be custom or refer to a named preset, and the list depends on what is loaded.

## How matching works

Named colors match by **preset identity**, even when two presets happen to share RGB values. Custom colors match through the stored color value. Avoid assigning a custom orange swatch when you actually mean the named Gameplay preset; those may look similar but are not equivalent organizational assignments.

## Workflow

Select a temporary marker Actor, choose Custom Color, and pick a distinct hue. On another Actor, use Used in This Level to apply the existing value quickly. Later, create a named preset if the color needs a shared project meaning.

## Limitations

Used-color collection excludes unloaded World Partition Actors. A missing named preset can still appear in the current used-assignments list because it remains stored, but it cannot be resolved to its former color until the referenced preset is restored.

---

[Read Technical](TECHNICAL.md) for source implementation, native engine integration and data ownership.

# Implementation and API — Design

**Chroma v1.0.1 · User guide**

## Why Chroma is an Editor plugin

Chroma extends existing Unreal Editor UI and rendering rather than creating a new Actor class. It participates in the World Outliner, viewport selection, view modes and settings.

For end users, this means color organization follows the normal Actor/Folder packages. For technical integrators, it means changes should be made using editor-compatible APIs and only with appropriate world/context assumptions.

## Where the main pieces live

| Piece | Responsibility |
| --- | --- |
| Outliner column | Swatches, palette menu and selection commands |
| State resolver | Direct assignments and Folder inheritance |
| Project settings | Named palette and presentation toggles |
| Label wrapper | Optional tint on compatible native icon widgets |
| View extension | Up to six Chroma-colored selection outlines |
| Actor Coloration handler | Visualization of supported primitives by effective color |
| Viewport hover overlay | Color name, hex and source under the cursor |

## Read-only integration for other tools

Chroma exposes a **small read-only C++ API** for editor consumers to obtain an Actor or Folder's resolved color, including preset identity and whether it was inherited. This doesn't provide a general write or runtime integration API.

## What isn't an integration feature

Chroma doesn't auto-detect semantic categories from gameplay classes, synchronize colors through replication, replace Unreal's selection system, or provide a universal palette renderer for every third-party Outliner.

## Further reading

See the [Source Map Technical](TECHNICAL.md) companion for entry points and the repository's [implementation references](https://github.com/mippi-the-dork/Chroma/blob/main/Doc/Sources.md).

---

[Read Technical](TECHNICAL.md) for source implementation and native engine boundaries.

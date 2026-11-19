# Actor Coloration Visualization — Design

**Chroma v1.0.1 · User guide**

## Show the whole scene by organization

From the viewport's view-mode menu—usually labeled **Lit**—choose **Actor Coloration → Chroma**. Supported Actor geometry displays its effective Chroma assignment as a flat organizational color.

Unassigned content appears neutral gray. A mesh inheriting Green from its Environment folder displays Green; a Red direct override displays Red.

## Compare Lit and Chroma

In Lit mode you see normal materials and lighting. In Chroma's Actor Coloration mode you see organizational color independent of the material appearance. Switch back to **Lit** when your visual audit is finished.

## Why use it?

A large level can reveal misplaced content quickly. If an Environment mesh appears Orange because it belongs to a Gameplay-colored Folder or has a direct override, you can investigate its assignment immediately.

## Things it doesn't modify

The mode doesn't replace saved materials, move or hide Actors, modify runtime assets, or change a packaged game's visuals. It is an editor viewport representation.

## Limitations

Only supported **rendered Actor primitives** can be recolored. Folders and empty Actors contain no geometry. The mode's availability can depend on the engine's Actor Coloration support and active viewport context.

---

[Read Technical](TECHNICAL.md) for native Unreal integration, data ownership and implementation limits.

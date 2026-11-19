# 01. Getting Started

Chroma adds a compact swatch column immediately before **Item Label** in the standard World Outliner. It is intended for large editor worlds where folders and names alone don't make different kinds of level content easy to recognize.

A first session should establish one useful named palette, color a folder, override one Actor, then inspect the result in the Outliner and viewport. None of those actions changes Actor transforms, attachments, materials or gameplay behavior.

## Typical workflow

Enable Chroma, find the World Outliner swatch, create or choose a named color, apply it to a folder, and observe how its contents inherit the color.

## Topics

| Topic | What it covers | Design | Technical |
| --- | --- | --- | --- |
| **What Chroma Does** | Organize levels through named, custom, and inherited Actor and Folder colors. | [Design](overview/DESIGN.md) | [Technical](overview/TECHNICAL.md) |
| **Installation and Compatibility** | Install through Fab when available, a compatible Release, or C++ source. | [Design](install/DESIGN.md) | [Technical](install/TECHNICAL.md) |
| **Your First Color Workflow** | Assign, inherit, override, inspect, and save your first Chroma colors. | [Design](first-use/DESIGN.md) | [Technical](first-use/TECHNICAL.md) |

## Important distinction

This is an **Editor** plugin; a Chroma color is not a material, lighting override or runtime variable.

Use **Design** for practical authoring steps and **Technical** for native Unreal implementation, persistence and integration details.

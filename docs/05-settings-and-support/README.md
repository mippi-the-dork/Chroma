# 05. Settings, Saving and Support

Project settings control named presets and optional Outliner/viewport presentation. Actual Actor and Folder color assignments are saved as **package metadata**; palette definitions live in the project's Chroma configuration. Both may need sharing in a team.

Start troubleshooting by checking whether an Actor or Folder is loaded, whether you're using a valid World Outliner, whether color is inherited or explicit, and whether the viewport feature supports the geometry in question.

## Typical workflow

Set up named colors in Project Settings, apply them to loaded Actors/Folders, save the affected packages and Config/DefaultChroma.ini, and verify the level after reload.

## Topics

| Topic | What it covers | Design | Technical |
| --- | --- | --- | --- |
| **Project Settings** | Configure project palette, Outliner icons and selection-outline preferences. | [Design](settings/DESIGN.md) | [Technical](settings/TECHNICAL.md) |
| **Saving and Team Workflows** | Understand package metadata, source control and Undo/Redo. | [Design](saving/DESIGN.md) | [Technical](saving/TECHNICAL.md) |
| **Troubleshooting and FAQ** | Diagnose unavailable colors, filtering, visualization and rendering limitations. | [Design](troubleshooting/DESIGN.md) | [Technical](troubleshooting/TECHNICAL.md) |
| **Implementation and API** | Understand Chroma's editor modules, storage, rendering and read-only API. | [Design](architecture/DESIGN.md) | [Technical](architecture/TECHNICAL.md) |
| **Updating and Support** | Keep installations compatible and report reproducible problems. | [Design](updating/DESIGN.md) | [Technical](updating/TECHNICAL.md) |

## Important distinction

Source review documents implementation; clean-project packaging, source-control transfer and special renderer cases are not universally verified.

Use **Design** for practical authoring steps and **Technical** for native Unreal implementation, persistence and integration details.

# 02. Colors and Inheritance

Chroma resolves **effective color** by checking the item's own assignment and then its containing World Outliner folder hierarchy. A named preset, a custom RGB value, an explicit **No Color** assignment and the absence of an override are four distinct states.

Color organization follows **folder hierarchy**, not Actor attachments. New Actors placed in a colored folder inherit its effective color automatically unless assigned their own override. Preset identity survives renaming or recoloring.

## Typical workflow

Give an Environment folder Green, assign a critical Actor a Red override, then use Clear Override to return to Green. Use No Color to intentionally stop the inheritance.

## Topics

| Topic | What it covers | Design | Technical |
| --- | --- | --- | --- |
| **Assign Colors** | Use the Outliner swatch and palette to color Actors or Folders. | [Design](assign/DESIGN.md) | [Technical](assign/TECHNICAL.md) |
| **Named Project Palette** | Manage named color presets and understand stable preset identity. | [Design](palette/DESIGN.md) | [Technical](palette/TECHNICAL.md) |
| **Folder Inheritance** | Use folders as defaults, including nested overrides and new Actors. | [Design](inheritance/DESIGN.md) | [Technical](inheritance/TECHNICAL.md) |
| **Overrides, Clear Override and No Color** | Distinguish direct colors, inherited colors, explicit No Color, and clearing. | [Design](overrides/DESIGN.md) | [Technical](overrides/TECHNICAL.md) |
| **Custom and Used Colors** | Make one-off colors and reuse colors from loaded level content. | [Design](custom-and-used/DESIGN.md) | [Technical](custom-and-used/TECHNICAL.md) |

## Important distinction

**Clear Override** resumes inherited color. **No Color** blocks inherited color. Those operations intentionally do different things.

Use **Design** for practical authoring steps and **Technical** for native Unreal implementation, persistence and integration details.

# 04. Viewport Presentation

Chroma offers two different viewport views of organizational color. **Tint Selection Outlines** uses Chroma colors while Actors are selected. **Actor Coloration → Chroma** displays supported geometry in its effective color regardless of selection.

A hover inspector explains where an Actor's color came from. These are editor presentation features: they don't rewrite materials, visibility or packaged-game rendering.

## Typical workflow

<!-- Media target: IMAGE | viewport-modes-comparison | docs/assets/media/viewport-modes-comparison.png -->
<figure class="doc-media" data-kind="image" data-media-id="viewport-modes-comparison">
  <img src="../assets/media-placeholder.png" alt="Chroma displays organizational color through selection outlines and a separate Actor Coloration view mode." loading="lazy">
  <figcaption>Chroma displays organizational color through selection outlines and a separate Actor Coloration view mode.
    <span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Capture a side-by-side comparison of the same scene in normal Lit view with colored selection outlines and in Actor Coloration → Chroma with all supported geometry displayed by assignment. Use matching camera framing.</span>
  </figcaption>
</figure>


Assign colors to several meshes, select them to inspect colored outlines, then switch the viewport from Lit to Actor Coloration → Chroma to see all supported geometry by color.

## Topics

| Topic | What it covers | Design | Technical |
| --- | --- | --- | --- |
| **Colored Selection Outlines** | Use Chroma-based selection outlines and understand their six-color limit. | [Design](outlines/DESIGN.md) | [Technical](outlines/TECHNICAL.md) |
| **Actor Coloration Visualization** | Display geometry by effective organizational color in the editor viewport. | [Design](visualization/DESIGN.md) | [Technical](visualization/TECHNICAL.md) |
| **Viewport Color Inspector** | Read hovered Actor color, source, and assignment directly in the viewport. | [Design](inspector/DESIGN.md) | [Technical](inspector/TECHNICAL.md) |

## Important distinction

Selection-outline tinting has a limited number of extra colors, while Actor Coloration is a separate editor visualization mode.

Use **Design** for practical authoring steps and **Technical** for native Unreal implementation, persistence and integration details.

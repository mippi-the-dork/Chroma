# Chroma

Chroma brings color organization to Unreal Engine's World Outliner and viewport. Assign named or custom colors to actors and folders, select matching items, and recognize groups through color swatches, tinted icons, selection outlines, and a dedicated viewport visualization.

**Compatibility:** Tested in Unreal Engine 5.8.2 on Windows (64-bit).

Chroma works independently of Focus, Origin, Surface, and Motion Design. It requires no engine modifications and contains an editor-only module.

## Installation

1. Download the Chroma plugin ZIP from the repository's release **Assets**.
2. Close Unreal Editor and extract the `Chroma` folder into your project's `Plugins` folder. Create that folder if needed.
3. Confirm the descriptor is at `YourProject/Plugins/Chroma/Chroma.uplugin`.
4. Open your project and enable **Chroma** under **Edit > Plugins**.
5. Restart the editor if prompted.

Use the release plugin ZIP for a packaged plugin installation. GitHub's automatically generated source archives may require compilation. For a source installation, regenerate your C++ project files and build your project's **Development Editor** target with the matching engine version.

## Assigning colors

The Chroma column appears immediately before **Item Label**. When Focus is installed, Chroma sits between Focus and Item Label.

Click an item's swatch to open its palette. The menu shows the current color, colors used by loaded items in the level, project presets, and **Custom Color**. Named colors display their labels. Hover a swatch to see its assignment and inheritance source.

- Click the swatch of an already-selected item to assign a color to the selected actors and folders together.
- Click an unselected item's swatch to change only that item.
- Mixed selections show **Multiple colors**. Choosing a color applies it to the targeted selection.
- Right-click an actor in the viewport or Outliner and use **Chroma > Color and Selection** for color and selection actions. Actor context menus target actors; use the swatch column to include folder assignments.

## Folder inheritance

Folder colors provide the default for their contents, including nested folders. An explicit actor or folder assignment overrides the inherited color. Actors added to a colored folder inherit automatically. Actor attachment alone does not pass colors down the attachment hierarchy.

| Action | Result |
| --- | --- |
| Assign a color | Overrides the inherited color on the targeted item. |
| Clear Override | Removes the direct assignment and resumes folder inheritance. |
| No Color | Explicitly blocks inherited color on the item. For a folder, its contents also inherit no color unless they have an override. |

## Named colors

Choose **Edit Named Colors** in the palette, or open **Project Settings > Plugins > Chroma**.

Add, rename, and recolor project presets there. Assignments retain their preset identity when its name or color changes. Two separately named presets remain separate groups even if they look identical. **Custom Color** assigns an unnamed color directly.

Deleting a preset leaves affected assignments marked **Missing preset**. Reassign those items or undo the deletion. Missing presets do not silently become another color.

## Selection and copy/paste

- **Select Matching Color** selects loaded matching actors and folders in the current editor world.
- **Select Matching Color Among Siblings** limits matches to the same hierarchy level and includes the sampled item.
- Hold **Shift** when invoking either selection action to add matches to the current selection.
- **Copy Chroma Color** and **Paste Chroma Color** reuse a color assignment. Paste follows the menu's target selection.

Named-color matching uses preset identity. Custom-color matching uses its color value.

Swatch menus sample the clicked row. Viewport actor menus sample the right-clicked actor. Outliner actor menus use a selected actor from that Outliner; select a single reference actor when copying or matching from a mixed actor selection and the sampled color matters. Matching actions require an open World Outliner.

## Outliner icons and selection outlines

Both settings are enabled by default under **Project Settings > Plugins > Chroma**:

| Setting | Effect |
| --- | --- |
| Outliner > Tint Outliner Icons | Applies effective Chroma colors to native actor and folder icons. |
| Viewport > Tint Selection Outlines | Applies effective Chroma colors to selected actors' viewport outlines. |

Uncolored items retain their normal appearance. Existing projects retain an explicitly saved off setting. Unreal's own **Selection Outline** preference must be enabled to see outlines.

The viewport supports up to **six distinct Chroma outline colors simultaneously**. Additional colors use Unreal's normal outline until a slot becomes available. Identical displayed colors share a slot. Other tools using explicit outline slots can reduce the available number.

Custom actor artwork in standard Outliner rows receives the tint, but colors baked into an icon may affect the result. Plugins that replace the label widget with a custom layout are not tinted.

## Chroma viewport visualization

Open the viewport view-mode menu, normally labeled **Lit**, and choose **Actor Coloration > Chroma**.

Supported actor geometry displays its effective Chroma color. Unassigned actors, **No Color**, and missing presets appear neutral gray. Return to **Lit** to resume the normal display. This visualization does not replace saved materials or alter visibility.

A fixed panel in the upper-left corner identifies the actor under the cursor, its color, and its inheritance source. The panel holds its last result during dragging, camera navigation with mouse buttons held, or open menus, then resumes updating afterward. It does not intercept clicks.

Empty actors and folders have no geometry to recolor. Unsupported picking targets show the neutral hover prompt. Unreal shares the active Actor Coloration handler across viewports using that visualization; viewports in Lit remain in Lit.

## Saving and team sharing

Save changed levels, actors, and folders normally. Color assignments are stored as editor package metadata. Named presets and project settings belong in `Config/DefaultChroma.ini`.

To share Chroma organization through source control, include that configuration file and the affected map, external actor, and external folder packages. Keep preset changes and their dependent assignments together. Chroma does not automatically submit changes.

Local persistence has been tested. Transfer between separate source-control workspaces still requires validation. Chroma introduces no custom actor or component classes into saved levels.

## Scope and limitations

- Chroma operates on loaded editor actors and folders. Unloaded World Partition actors are excluded from editing, matching, icon tinting, and the used-color list.
- The used-color list includes loaded sublevels and is not limited by Outliner search. Filtered actor matches can be selected; filtered folder matches may require clearing the filter, with a notification when folders are skipped.
- Chroma editing and viewport tools target editor workflows, not PIE or simulation.
- Selection outlines have been tested with ordinary static meshes and Nanite meshes. Landscapes, translucent geometry, specialized rendering paths, and per-instance editing need broader coverage testing.
- Other plugins that directly control outline colors or the same renderer setting may conflict.
- Clean-project installation, plugin packaging, packaged-game builds, and source-control transfer remain release validation tasks. Editor testing does not establish those results.

See [Doc/Sources.md](Doc/Sources.md) for implementation references and artwork attribution.

# Maintaining Chroma Documentation

## Source of truth

Use the current `Chroma.uplugin`, README and `Source/Chroma/` implementation. Inspect the affected C++ code before promising behavior. The site is currently based on **Chroma v1.0.1**.

## Design and Technical remain separate

**Design** explains what users see, click and accomplish, how they troubleshoot normal problems, and what outcomes to expect. **Technical** documents state, engine interfaces, exact C++ types, data ownership and limitations. Keep both informative on their own; do not duplicate the same long README text.

## Adding or changing a feature

1. Update the relevant topic's Design and Technical pages together.
2. If adding a topic, update its numbered category's `README.md` table and the homepage category count.
3. Add or update visual material in [Media Inventory](MEDIA_INVENTORY.md) and `assets/media-slots.json`.
4. Keep a real reader-facing caption and separate precise **Capture instructions · Image/GIF** line for placeholders.
5. Check Markdown links, image source paths, sidebar navigation, full-text search and responsive layout.
6. Record verified Unreal Editor results in [Verification Matrix](VERIFICATION_MATRIX.md), never confuse source review with a passed test.

## Image sources

The Chroma repository already provides genuine hero, assignment, inheritance, matching, settings, selection-outline and visualization images/GIFs under `Doc/Images/`. Reuse them with captions before asking for new captures. Do not use fabricated UI screenshots.

Planned placeholder images live in `docs/assets/media-placeholder.png` and are referenced with relative links. The machine-readable registry specifies intended final PNG or GIF filenames and detailed capture requirements.

## Publishing

GitHub Pages should deploy from **main /docs** at `https://mippi-the-dork.github.io/Chroma/`. After merge, verify the live Pages rendering and links. Deployment settings are repository-level and may require owner configuration.

## Versions and roadmap

Keep [Roadmap](ROADMAP.md) truthful: v1.0.1 is current, and additional feature commitments have not been supplied. Do not invent v2.0 features or release dates. When Chroma ships an update, revise source links and the documentation baseline.

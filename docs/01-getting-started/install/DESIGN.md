# Installation and Compatibility — Design

**Chroma v1.0.1 · User guide**

## Choosing an installation

You can install Chroma through **Fab when listed**, a matching precompiled GitHub Release when available, or directly from [source](https://github.com/mippi-the-dork/Chroma).

### Installing a release

1. Close Unreal Editor.
2. Choose a ZIP compatible with your engine and platform from [Chroma Releases](https://github.com/mippi-the-dork/Chroma/releases).
3. Extract the full **Chroma** folder under `YourProject/Plugins/`, placing `Chroma.uplugin` at `YourProject/Plugins/Chroma/Chroma.uplugin`.
4. Reopen the project. Under **Edit → Plugins**, enable Chroma if required and restart when prompted.
5. Open the standard World Outliner and look for the small Chroma column before **Item Label**.

Do not treat GitHub's automatically generated source archive as a precompiled release.

### Installing the source

Clone `https://github.com/mippi-the-dork/Chroma.git` inside your project's `Plugins` directory. Generate Visual Studio project files if necessary and build the project's **Editor** target with the correct Unreal C++ toolchain.

## Compatibility

| Item | Documented target |
| --- | --- |
| Chroma | **1.0.1** |
| Unreal Engine | **5.8.x** (descriptor `5.8.0`, README tested `5.8.2`) |
| Platform | **Windows 64-bit** |
| Module | **Editor-only** |

Other platforms or engine versions are not verified by this manual.

## Common installation problems

No swatch column? Check that the plugin is enabled and that you're viewing the **standard World Outliner**, not another Actor picker. Restart after installation. A failed C++ build means your editor/compiler toolchain or plugin version needs checking; it does not necessarily indicate a Chroma color-data problem.

---

[Read Technical](TECHNICAL.md) for source implementation, native engine integration and data ownership.

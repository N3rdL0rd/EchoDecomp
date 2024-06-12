# Echo Arena Decompilation Project

This project is a work in progress (WIP) that aims to decompile Echo Arena and its related engine components.

## Status

The project is currently in the early stages of development. If you are interested in contributing, please see the [Contributing](#contributing) section below.

### Does it compile?

The definitive question for any decompilation project! And the answer is...

***NO! - Or, at least, not yet***

## What this project is (and isn't)

This project is:

- An attempt to decompile Echo Arena and its related engine components (RAD15/14).
- A resource for modders and server developers who want to extend the game's functionality or gain insights into how it works.
- (Eventually) a fully matching decompilation that can be used to build a working version of the game.

This project is not:

- A platform for illegal activities. Decompiling is done for educational purposes and we do not endorse or support any form of illegal activities related to game hacking or piracy.
- A finished product. This is a work in progress and there may be incomplete or inaccurate information.
- A port to OpenXR or SteamVR. This project focuses entirely on the original Oculus APIs and does not aim to port the game to other platforms, although it may be possible to do so in the future with the information gained from this project.
- A modding platform or modloader. This project is focused on decompiling the game and its engine, not on creating mods or modding tools. However, we hope that this project will enable modders to create new and exciting mods for the game.
- A complete decompilation of the RAD15/14 engine. This project is focused on decompiling Echo Arena itself (`echovr.exe`), but not the entire engine. However, the parts of the engine that are used by Echo Arena will be decompiled as part of this project.

## Structure

The project is divided into several main components:

- `echovr` - Decompilation of v34.4.631547.1 (latest playable version).
  - `scripts` - Decompilation of each of the game script DLLs.
  - `echovr` - Decompilation of the main game executable.
- `echovr58` - Decompilation of v1.58 (debug symbols version).
  - `scripts` - Decompilation of each of the game script DLLs.
  - `EchoArena` - Decompilation of the main game executable.
- `utils` - Utility scripts and tools for decompilation and analysis.
- `docs` - Documentation and guides for contributors and users.

## Contributing

In order to get started decompiling Echo Arena, see the [Getting Started](docs/gettingstarted.md) guide. Or, if you think you know what you're doing, feel free to jump right in! Join our [Discord server](https://discord.gg/f57yNaJmRg) to chat with other contributors and get help with the decompilation process. We welcome contributions from anyone interested in game development or reverse engineering. If you have any information or findings that you think could benefit this project, please feel free to share them with us. You can contribute by submitting pull requests or by opening issues on our GitHub page.

## Legal and Licensing

This project is not licensed under any open-source license, as it is a decompilation of copyrighted software. However, we aim to respect the rights of the original developers at Ready at Dawn and Oculus, and we do not intend to distribute any copyrighted material. We encourage contributors to respect the rights of the original developers and to avoid sharing any copyrighted material. If you have any concerns about the legality of this project, please contact us on our Discord server.

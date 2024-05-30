# Getting Started

This guide will walk you through the process of setting up your decompilation environment and getting started with decompiling Echo Arena.

## Prerequisites

> [!TIP]
> If you don't have the money to buy IDA Pro, you can shoot me a DM on Discord (@n3rdl0rd) and I can provide you with a temporary license.

Before you begin, you will need the following tools and resources:

- [Ghidra](https://ghidra-sre.org/) (free) or [IDA Pro](https://www.hex-rays.com/products/ida/) (paid, reccomended) - A disassembler and decompiler for reverse engineering
- A copy of Echo Arena v34.4.631547.1 (the latest playable version of the game before its shutdown) - You can obtain this either from the Oculus Store (by [downgrading](https://computerelite.github.io/tools/Oculus/OculusDowngraderGuide.html) if you previously owned the game) or from [here](https://drive.google.com/file/d/1At6J2RssQTHzYtOLJ6riLHsqdj-TROEg/view)
- (Optional) A copy of Echo Arena v1.58 (a version that accidentally shipped with debug symbols) - You can only obtain this from the Oculus Store by downgrading if you previously owned the game
- (Optional) Python 3.8 or later - To run various tools in the repository

## Getting the Game Versions

For v34.4.631547.1, you can either get it by using [OculusDowngrader](https://computerelite.github.io/tools/Oculus/OculusDowngraderGuide.html) or by downloading it from [here](https://drive.google.com/file/d/1At6J2RssQTHzYtOLJ6riLHsqdj-TROEg/view).

For v1.58, you can get it only by downgrading the game using [OculusDowngrader](https://computerelite.github.io/tools/Oculus/OculusDowngraderGuide.html). If you download this version and encounter an error like the one shown below, you can ignore it as it is not important for the decompilation process.

```plaintext
Download finished. Processing files...
Processing _data\5828984418\win7\primary\e5bd8207135b8887\v13363680368\ea49e53700c44a2c (12.17 MB)
Processing _data\5828984418\win7\GPU\005a5579fb36b249\v13363680368\6113bd53bd411194 (47.38 MB)
Processing _data\5828984418\win7\GPU\005a5579fb36b249\v13363680368\c6bc8607972268c9 (21.78 MB)
Processed 0 / 3 files successfully

Only 1877 out of 1880 files are valid! The files were unable to get repaired. You can reinstall the version by simply downloading it again via the tool.
Download failed
```

Place the game files in the echovr/orig and echovr58/orig directories respectively.

## Methodology

The general approach to decompiling Echo Arena is as follows:

- Use a decompiler to generate pseudo-C code from the latest version of the executable (`echovr.exe`).
- Use a decompiler to generate much more accurate C code from v1.58 of the executable, which contains debug symbols.
- Compare the two sets of decompiled code to identify similar functions - those that are similar enough can have their names and types inferred from the debug symbols.
- Use the inferred names and types to improve the decompilation of the latest version of the executable.
  - Note: the last two steps can be partially automated with [rizzo.py](https://github.com/grayhatacademy/ida/tree/master/plugins/rizzo) if you're using IDA, which is also available in `./utils` for convenience.
- Stub out incompletely decompiled functions to allow at least partial compilation of the game.
- Attempt compilation of the game and check for errors. If none arise, the decompilation is likely at least partially correct.
- Use a decompiler to decompile this newly compiled version of the game and check for differences between it and the original instructions that were decompiled.
- Use the differences to improve the decompilation further.
- Repeat the process until your decompiled function matches the original instructions.
- Document any findings or insights you gain from the decompilation process.
- Contribute your findings back to the community by submitting pull requests on the GitHub repository.
- Celebrate your success!
- Repeat the process for the next function.

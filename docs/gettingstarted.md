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

Place the game files in the echovr/orig and echovr58/orig directories respectively. Run the following command to verify that everything is correct:

```batch
python utils/verify_game_files.py
```

If everything is correct, you should see the following output:

```plaintext
SHA256 Checksum: e89460d67e0634c3bd70bf363d51c2f8dc36d5b2ecdbd97c134ef29fd0e118fb

EchoVR v34.4.631547.1 verified!

SHA256 Checksum: 9d27c0746d567200f494d32dcb30fbb855a34a4aab38042986590c5409e8bee0

EchoVR v1.58 verified!
```

If v1.58 isn't verified correctly, just check by hand that the SHA256 checksums of the following files match:

```plaintext
bin\win7\EchoArena.exe - 1df128a8742da1a24488dd03a4a3ff84785c444f15f12cd89b7ded5800573d46
bin\win7\EchoArena.pdb - beac9fce00ef7b38af29debcfa9dab140f9139751682ec00b826e3bc5e6709ce
bin\win7\pnsovr.dll    - fc75bcdd6f147abff6b07b80dd5675813911adcf73f7227029c01f7a7de4e129
bin\win7\pnsrad.dll    - fbb1a73168ab88678e324bf63aba1794120aad7f24288d34bdbb62e52d1a36f1
```

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

## About Stubbing

When stubbing out a function, you should replace all the decompiled code with a single return statement, or, if you do not expect to compile at all, a comment indicating that the function is incomplete, preferably:

```c
// TODO: stubbed
```

These conventions are important for maintaining consistency across the project and for ensuring that the decompiled code is as readable as possible, as well as easy to search for in the future.

## Next Steps (or; "What should I work on?")

If you're using VSCode, wait! You can install the [Todo Tree](https://marketplace.visualstudio.com/items?itemName=Gruntfuggly.todo-tree) extension to easily see all the `TODO` comments in the project. This will help you find what to work on next much more easily - just go to the TODOs tab in the sidebar, select "Flat view", and select "Grouped by tag". Expand the TODOs and you'll see everything that needs to be done.

Look at the files in the `echovr` and `echovr58` directories. The code is organized into directories for each namespace, and a file for each class or function. You can start by looking at the `NRadEngine` namespace, which contains the engine classes, and the NRadGame namespace (which is nested inside NRadEngine), which contains the game-specific classes. Find a function that is stubbed or doesn't compile (most likely one that calls a function that hasn't been stubbed or decopmiled yet) and start working on it. If you have any questions, feel free to ask in the Discord server.

## Tips

- Focus on one function at a time. If you jump around too much, you'll never make any real progress.
- Ignore `__fastcall` calling conventions for functions that don't have any arguments. IDA and Ghidra will often get this wrong, and it's not worth the effort to fix it with a plugin.
- When committing changes, make sure to include the fully qualified name of the function or class you worked on in the commit message. Basically, don't do what I did in the first few commits. If you decompile a large number of classes, you may group them together in a single commit, but make sure to include the names of all the classes in the pull request description.
  - For instance, if I decompiled the `CSysString.ToUpper` function in v1.58, I would include the following in the commit message: `echovr58: decompiled NRadEngine::CSysString::ToUpper()`.
<!-- TODO: more tips -->

## Good luck and happy decompiling! 🎉

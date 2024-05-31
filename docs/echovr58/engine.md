# EchoVR v1.58 - Engine Notes (RAD14)

This document contains notes on the RAD engine used by EchoVR v1.58. The engine is a modified version of RAD14, which is a proprietary engine developed by Ready At Dawn Studios. The engine is used in several games, including Echo VR, Lone Echo, and Lone Echo II.

## Naming Schemes

From the PDB leaks, we can glean some information about internal naming schemes used by the RAD engine. The engine uses a prefixing scheme for its classes, namespaces, and other symbols. Here are some of the prefixes we have observed so far:

- `C*` - Classes
- `C*T` - Template classes
- `N*` - Namespaces
- `CSys` - System-related classes

Because of this strict standardization, it is possible to infer the type of a symbol based on its name alone. This is incredibly useful when decompiling v1.58, but less so when decompiling the latest version of the game.

## Game Code vs Engine Code - Where does it start?

Because this project is in such an early stage, it's hard to say. My personal theory is that EchoArena.exe contains *just* the engine, and that the actual game-specific logic is located somewhere else, quite possibly in one of the DLLs. So far, we have not found any game-specific logic in EchoArena.exe, but we have found a **lot** of engine code.

## Metadata and Information

The following is a non-exhaustive list of information about the RAD engine executable:

- **Original PDB Filename**: `d:\projects\rad14\dev\_build\win7\goldmaster\bin\r14.pdb`
  - This path is from the development environment of the engine - the hash is identical to that of the PDB included with v1.58, so it is likely that `r14.pdb` is the original name for the PDB, instead of the bundled `EchoArena.pdb`.

## Stuff so far

- `NRadEngine` - The main engine namespace
- `CMemory` - Memory management class
- `CRT0.h` - Runtime initialization class
- `CSysTime` - System time class
- `CSysOs` - System OS info class
- `CSysString` - String class
- `CFixedStringT` - Fixed-size string class
- `CLoggingData` - Logging data class
- `NWriteLog` - Logging namespace

## Unresolved Issues

- [`NRadEngine::QueryCPUExtensions`](https://github.com/N3rdL0rd/EchoDecomp/blob/main/echovr58/EchoArena/NRadEngine/NRadEngine.cpp#L112) decompiles to inline assembly, which does not cooperate with IDA's pseudocode output. It has been stubbed out for now - see the IDA-generated decompilation [here](/echovr58/wip/NRadEngine.cpp) (note: modified by hand for readability).

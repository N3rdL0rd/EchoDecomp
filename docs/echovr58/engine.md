# EchoVR v1.58 - Engine Notes (RAD14)

This document contains notes on the RAD engine used by EchoVR v1.58. The engine is a modified version of RAD14, which is a proprietary engine developed by Ready At Dawn Studios. The engine is used in several games, including Echo VR, Lone Echo, and Lone Echo II.

## Naming Schemes

From the PDB leaks, we can glean some information about internal naming schemes used by the RAD engine. The engine uses a prefixing scheme for its classes, namespaces, and other symbols. Here are some of the prefixes we have observed so far:

- `C*` - Classes
- `N*` - Namespaces
- `CSys` - System-related classes

## Game Code vs Engine Code - Where does it start?

Because this project is in such an early stage, it's hard to say. My personal theory is that EchoArena.exe contains *just* the engine, and that the actual game-specific logic is located somewhere else, quite possibly in one of the DLLs. So far, we have not found any game-specific logic in EchoArena.exe, but we have found a **lot** of engine code. 

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

#include <Windows.h>
#include "NRadEngine/include/NRadEngine.h"
#include "NRadEngine/include/CRT0.h"


int __fastcall WinMain(HINSTANCE__ *hinst, HINSTANCE__ *previnstance, char *cmdline, int cmdshow)
{
    const char *CommandLineA; // rax
    unsigned int res; // ebx
    int result; // rax

    NRadEngine::CRT0::Init();
    CommandLineA = GetCommandLineA();
    res = NRadEngine::Main(CommandLineA);
    NRadEngine::CSysOS::Shutdown();
    result = res;
    NRadEngine::gLoggingInitialized = 0;
    return result;
}
#include <Windows.h>
#include "NRadEngine/include/NRadEngine.h"
#include "NRadEngine/include/CRT0.h"


int __fastcall WinMain(HINSTANCE__ *hinst, HINSTANCE__ *previnstance, char *cmdline, int cmdshow)
{
    NRadEngine::CRT0::Init();
    const char *CommandLineA = GetCommandLineA();
    unsigned int res = NRadEngine::Main(CommandLineA);
    NRadEngine::CSysOS::Shutdown();
    NRadEngine::gLoggingInitialized = 0;
    return (int)res;
}
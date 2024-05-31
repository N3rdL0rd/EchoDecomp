#include <vcruntime_string.h>
#include <intrin.h>
#include "NRadEngine/include/NRadEngine.h"
#include "NRadEngine/NRadGame/include/CR14Game.h"
#include "NRadEngine/NWriteLog/include/NWriteLog.h"

namespace NRadEngine {
    __int64 __fastcall Main(const char *argv) {
        return NRadEngine::Main_(argv); // ! incorrect parameter count, investigation needed
    }

    __int64 __fastcall Main_(const char *argv, __int64 a2, float a3, float a4) {
        // Variable declarations
        NRadEngine::CAllocator *currentMemoryContext; 
        NRadEngine::NRadGame::CR14Game *gameInstance; 
        __int64 returnCode; 
        NRadEngine::CAllocator *memoryContext1; 
        NRadEngine::CAllocator *memoryContext2; 
        NRadEngine::CAllocator *memoryContext3; 
        NRadEngine::CMainArgs mainArgs; 
        __int64 v16 = -2i64; // ? unused
        NRadEngine::CFixedStringT<512> result; 
        NRadEngine::CFixedStringT<512> dst; 

        // Initialization
        NRadEngine::CStringTable::CStringTable(&mainArgs.argvector);
        currentMemoryContext = NRadEngine::CMemoryContext::CurrentPtr();
        mainArgs.symbolmap.mem = 0i64;
        mainArgs.symbolmap.size = 0i64;
        mainArgs.symbolmap.allocator = currentMemoryContext;
        NRadEngine::CMemBlockA<0>::Constructor_(&mainArgs.symbolmap, 0i64);
        mainArgs.symbolmap.expand = 32i64;
        memset(&mainArgs.symbolmap.iallocated, 0, 32);
        NRadEngine::CMainArgs::Set(&mainArgs, argv);

        // CPU check
        if ( (NRadEngine::QueryCPUExtensions() & 0x38) != 56 )
        {
            NRadEngine::CSysWindow::ShowMessageBox(
            0i64,
            "CPU doesn't meet the minimum spec. The game needs the SSE4.1/SSE4.2/AVX instruction sets to run. You'll need to up"
            "grade your CPU to Oculus' minimum spec to play.",
            "Lone Echo/Echo Arena");
            NRadEngine::CRT0::Exit(-40i64);
        }

        // Log engine version header
        NRadEngine::NWriteLog::WriteLog(
            NRadEngine::NWriteLog::eInfo,
            0i64,
            "==========================================================\n"
            " R14\n"
            "==========================================================");

        // Game instance creation
        currentMemoryContext = NRadEngine::CMemoryContext::CurrentPtr();
        gameInstance = (NRadEngine::NRadGame::CR14Game *)currentMemoryContext->Alloc(currentMemoryContext, 17192ui64);
        if ( gameInstance )
        {
            NRadEngine::NRadGame::CR14Game::CR14Game(gameInstance, &mainArgs, a3, a4);
        }
        else
        {
            gameInstance = 0i64;
        }

        // Game instance setup
        gameInstance->appname = "Lone Echo";
        NRadEngine::CMemory::Fill(&dst, 0, 0x200ui64);
        NRadEngine::CSysInfo::GetExecutableFile(&dst);
        NRadEngine::CMemory::Fill(&result, 0, 0x200ui64);
        NRadEngine::CSysFile::GetBaseName(&result, &dst);
        NRadEngine::CSysString::ToLower(result.data, 0x200ui64);
        if ( !NRadEngine::CSysString::Compare(result.data, "echoarena.exe", 1u, 0x200ui64) ) // seriously??
            NRadEngine::NRadGame::CR14Game::SetMultiplayerApp(gameInstance);

        // Run game
        gameInstance->Run(gameInstance);
        returnCode = gameInstance->returncode;

        // Cleanup
        memoryContext1 = NRadEngine::CMemoryContext::CurrentPtr();
        memoryContext2 = NRadEngine::CMemoryContext::CurrentPtr();
        NRadEngine::CMemoryContext::SetCurrent(memoryContext2);
        memoryContext3 = NRadEngine::CMemoryContext::CurrentPtr();
        ((void (__fastcall *)(NRadEngine::NRadGame::CR14Game *, _QWORD))gameInstance->~CncaGame)(gameInstance, 0i64);
        memoryContext3->Free(memoryContext3, gameInstance);
        NRadEngine::CMemoryContext::SetCurrent(memoryContext1);
        NRadEngine::CMainArgs::Cleanup(&mainArgs);
        if ( (mainArgs.symbolmap.flags.flags[0] & 3) != 0 )
        {
            mainArgs.symbolmap.mem = 0i64;
            mainArgs.symbolmap.size = 0i64;
        }
        if ( mainArgs.symbolmap.size && mainArgs.symbolmap.mem )
        {
            ((void (__fastcall *)(NRadEngine::CAllocator *))mainArgs.symbolmap.allocator->Free)(mainArgs.symbolmap.allocator);
            mainArgs.symbolmap.mem = 0i64;
            mainArgs.symbolmap.size = 0i64;
        }
        NRadEngine::CStringTable::~CStringTable(&mainArgs.argvector);

        return returnCode;
    }

    __int64 QueryCPUExtensions() {
        return 0xFF; // * stubbed, see echovr58/wip/NRadEngine.cpp and docs/echovr58/engine.md#unresolved-issues
    }
}
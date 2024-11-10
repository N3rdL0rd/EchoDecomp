#include "NRadEngine/include/NRadEngine.h"

#include <vcruntime_string.h>
#include <intrin.h>
#include "include/ints.h"
#include "NRadEngine/include/NRadEngine.h"
#include "NRadEngine/NRadGame/include/CR14Game.h"
#include "NRadEngine/NWriteLog/include/NWriteLog.h"
#include "NRadEngine/include/CSysString.h"
#include "NRadEngine/include/CSysInfo.h"
#include "NRadEngine/include/CSysFile.h"

namespace NRadEngine
{
    __int64 __fastcall Main(const char *argv)
    {
        return NRadEngine::Main_(argv); // TODO: incorrect parameter count, investigation needed
    }

    __int64 __fastcall Main_(const char *argv, __int64 a2, float a3, float a4)
    {
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
        // TODO: a lot of this is unimplemented - symbolmap is a type of CMap, which is very complex comparatively
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
        if ((NRadEngine::QueryCPUExtensions() & 0x38) != 56)
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
        gameInstance = (NRadEngine::NRadGame::CR14Game *)currentMemoryContext->Alloc(currentMemoryContext, 17192ui64); // TODO: ida refuses to decompile Alloc()
        if (gameInstance)
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
        if (!NRadEngine::CSysString::Compare(result.data, "echoarena.exe", 1u, 0x200ui64)) // match case, up to 512 characters
            NRadEngine::NRadGame::CR14Game::SetMultiplayerApp(gameInstance);

        // Run game
        gameInstance->Run(gameInstance); // TODO: IDA also doesn't want to decompile this
        returnCode = gameInstance->returncode;

        // Cleanup
        memoryContext1 = NRadEngine::CMemoryContext::CurrentPtr();
        NRadEngine::CMemoryContext::SetCurrent(memoryContext2);
        memoryContext2 = NRadEngine::CMemoryContext::CurrentPtr();
        ((void(__fastcall *)(NRadEngine::NRadGame::CR14Game *, _QWORD))gameInstance->~CncaGame)(gameInstance, 0i64);
        memoryContext2->Free(memoryContext3, gameInstance);
        memoryContext3 = NRadEngine::CMemoryContext::CurrentPtr();
        NRadEngine::CMemoryContext::SetCurrent(memoryContext3);
        NRadEngine::CMainArgs::Cleanup(&mainArgs);
        if ((mainArgs.symbolmap.flags.flags[0] & 3) != 0)
        {
            mainArgs.symbolmap.mem = 0i64;
            mainArgs.symbolmap.size = 0i64;
        }
        if (mainArgs.symbolmap.size && mainArgs.symbolmap.mem)
        {
            ((void(__fastcall *)(NRadEngine::CAllocator *))mainArgs.symbolmap.allocator->Free)(mainArgs.symbolmap.allocator);
            mainArgs.symbolmap.mem = 0i64;
            mainArgs.symbolmap.size = 0i64;
        }
        NRadEngine::CStringTable::~CStringTable(&mainArgs.argvector);

        return returnCode;
    }

    __int64 QueryCPUExtensions()
    {
        return 0xFF; // TODO: stubbed, see echovr58/wip/NRadEngine.cpp and docs/echovr58/engine.md#unresolved-issues
    }

    LRESULT WindowProc(HWND__ *wnd, unsigned int msg, unsigned __int64 wparam, __int64 lparam)
    {
        // TODO: decipher
        unsigned __int64 _wparam; // rbx
        int xlimit;               // ecx
        int ylimit;               // edx
        tagPOINT Point;           // [rsp+20h] [rbp-28h] BYREF
        tagRECT Rect;             // [rsp+28h] [rbp-20h] BYREF

        _wparam = wparam;
        if (msg == 2)
        {
            NRadEngine::gWindowEvents.flags[0] |= 0x10;
            return 0i64;
        }
        if (msg == 16)
        {
            DestroyWindow(wnd);
            return 0i64;
        }
        if (msg != 32)
        {
            if (msg == 256)
            {
                switch (wparam)
                {
                case 0x1Bui64:
                    NRadEngine::gWindowEvents.flags[0] |= 2;
                    return 0i64;
                case 0x79ui64:
                LABEL_9:
                    NRadEngine::gWindowEvents.flags[0] |= 4;
                    return 0i64;
                case 0x7Aui64:
                    NRadEngine::gWindowEvents.flags[0] |= 8;
                    return 0i64;
                }
            }
            else
            {
                if (msg != 260)
                    return DefWindowProcA(wnd, msg, wparam, lparam);
                switch (wparam)
                {
                case 0xDui64:
                    NRadEngine::gWindowEvents.flags[0] |= 1;
                    return 0i64;
                case 0x79ui64:
                    goto LABEL_9;
                case 0x73ui64:
                    msg = 260;
                    wparam = 115i64;
                    return DefWindowProcA(wnd, msg, wparam, lparam);
                }
            }
            return 0i64;
        }
        if (NRadEngine::gShowSystemCursor)
        {
            msg = 32;
            return DefWindowProcA(wnd, msg, wparam, lparam);
        }
        Point = 0i64;
        GetCursorPos(&Point);
        ScreenToClient(wnd, &Point);
        *(_QWORD *)&Rect.left = 0i64;
        *(_QWORD *)&Rect.right = 0i64;
        GetClientRect(wnd, &Rect);
        xlimit = Rect.right - Rect.left;
        ylimit = Rect.bottom - Rect.top;
        Rect.right -= Rect.left;
        Rect.bottom -= Rect.top;
        if (Point.x < 0 || Point.x > xlimit || Point.y < 0 || Point.y > ylimit)
            return DefWindowProcA(wnd, 0x20u, _wparam, lparam);
        SetCursor(0i64);
        return 1i64;
    }
}
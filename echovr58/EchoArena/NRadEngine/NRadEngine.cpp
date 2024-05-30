#include <vcruntime_string.h>
#include "NRadEngine/include/CMemory.h"

namespace NRadEngine {
    __int64 __fastcall Main(const char *argv) {
        return NRadEngine::Main_(argv);
    }

    __int64 __fastcall Main_(const char *argv, __int64 a2, float a3, float a4) {
        NRadEngine::CAllocator *v5; // rax
        NRadEngine::CAllocator *memory_context_ptr; // rax
        NRadEngine::NRadGame::CR14Game *v7; // rax
        NRadEngine::NRadGame::CR14Game *v8; // rax
        NRadEngine::NRadGame::CR14Game *v9; // rsi
        __int64 returncode; // r14
        NRadEngine::CAllocator *v11; // rdi
        NRadEngine::CAllocator *v12; // rax
        NRadEngine::CAllocator *v13; // rbx
        NRadEngine::CMainArgs v15; // [rsp+20h] [rbp-E0h] BYREF
        __int64 v16; // [rsp+E0h] [rbp-20h]
        NRadEngine::CFixedStringT<512> result; // [rsp+F0h] [rbp-10h] BYREF
        NRadEngine::CFixedStringT<512> dst; // [rsp+2F0h] [rbp+1F0h] BYREF

        v16 = -2i64;
        NRadEngine::CStringTable::CStringTable(&v15.argvector);
        v5 = NRadEngine::CMemoryContext::CurrentPtr();
        v15.symbolmap.mem = 0i64;
        v15.symbolmap.size = 0i64;
        v15.symbolmap.allocator = v5;
        NRadEngine::CMemBlockA<0>::Constructor_(&v15.symbolmap, 0i64);
        v15.symbolmap.expand = 32i64;
        memset(&v15.symbolmap.iallocated, 0, 32);
        NRadEngine::CMainArgs::Set(&v15, argv);
        if ( (NRadEngine::QueryCPUExtensions() & 0x38) != 56 )
        {
            NRadEngine::CSysWindow::ShowMessageBox(
            0i64,
            "CPU doesn't meet the minimum spec. The game needs the SSE4.1/SSE4.2/AVX instruction sets to run. You'll need to up"
            "grade your CPU to Oculus' minimum spec to play.",
            "Lone Echo/Echo Arena");
            NRadEngine::CRT0::Exit(-40i64);
        }
        NRadEngine::NWriteLog::WriteLog(
            eInfo,
            0i64,
            "==========================================================\n"
            " R14\n"
            "==========================================================");
        memory_context_ptr = NRadEngine::CMemoryContext::CurrentPtr();
        v7 = (NRadEngine::NRadGame::CR14Game *)memory_context_ptr->Alloc(memory_context_ptr, 17192ui64);
        if ( v7 )
        {
            NRadEngine::NRadGame::CR14Game::CR14Game(v7, &v15, a3, a4);
            v9 = v8;
        }
        else
        {
            v9 = 0i64;
        }
        v9->appname = "Lone Echo";
        NRadEngine::CMemory::Fill(&dst, 0, 0x200ui64);
        NRadEngine::CSysInfo::GetExecutableFile(&dst);
        NRadEngine::CMemory::Fill(&result, 0, 0x200ui64);
        NRadEngine::CSysFile::GetBaseName(&result, &dst);
        NRadEngine::CSysString::ToLower(result.data, 0x200ui64);
        if ( !NRadEngine::CSysString::Compare(result.data, "echoarena.exe", 1u, 0x200ui64) )
            NRadEngine::NRadGame::CR14Game::SetMultiplayerApp(v9);
        v9->Run(v9);
        returncode = v9->returncode;
        v11 = NRadEngine::CMemoryContext::CurrentPtr();
        v12 = NRadEngine::CMemoryContext::CurrentPtr();
        NRadEngine::CMemoryContext::SetCurrent(v12);
        v13 = NRadEngine::CMemoryContext::CurrentPtr();
        ((void (__fastcall *)(NRadEngine::NRadGame::CR14Game *, _QWORD))v9->~CncaGame)(v9, 0i64);
        v13->Free(v13, v9);
        NRadEngine::CMemoryContext::SetCurrent(v11);
        NRadEngine::CMainArgs::Cleanup(&v15);
        if ( (v15.symbolmap.flags.flags[0] & 3) != 0 )
        {
            v15.symbolmap.mem = 0i64;
            v15.symbolmap.size = 0i64;
        }
        if ( v15.symbolmap.size && v15.symbolmap.mem )
        {
            ((void (__fastcall *)(NRadEngine::CAllocator *))v15.symbolmap.allocator->Free)(v15.symbolmap.allocator);
            v15.symbolmap.mem = 0i64;
            v15.symbolmap.size = 0i64;
        }
        NRadEngine::CStringTable::~CStringTable(&v15.argvector);
        return returncode;
    }
}

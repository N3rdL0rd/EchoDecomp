#include <Windows.h>
#include <DbgHelp.h>
#include "NRadEngine/include/globals.h"
#include "NRadEngine/include/CSysTime.h"
#include "NRadEngine/include/CMemory.h"

namespace NRadEngine {
    class CSysOS {
        public:
        static void Init(void) {
            UINT ErrorMode; // eax
            NRadEngine::CFixedStringT<512> dst; // [rsp+20h] [rbp-408h] BYREF
            NRadEngine::CFixedStringT<512> result; // [rsp+220h] [rbp-208h] BYREF

            NRadEngine::CSysTime::Init();
            NRadEngine::CMemory::Fill(&dst, 0, 0x200ui64);
            NRadEngine::CSysInfo::GetExecutableDirectory(&dst);
            NRadEngine::CSysInfo::SetProjectDirFrom(&dst);
            ErrorMode = GetErrorMode();
            SetErrorMode(ErrorMode | 3);
            NRadEngine::gWinMainThread = GetCurrentThreadId();
            NRadEngine::CMemory::Fill(&result, 0, 0x200ui64);
            NRadEngine::CSysInfo::GetEnvironment("TEMP", &result);
            GetLongPathNameA(result.data, NRadEngine::tempdir.data, 0x200u);
        }

        static void InitDbgSymbolLookups(void)
        {
            HANDLE CurrentProcess; // rbx
            const char *ProjectDir; // rdi
            DWORD LastError; // eax
            unsigned __int64 v3; // rax
            __int64 v4; // rdx
            unsigned __int64 v5; // rdi
            unsigned __int64 i; // rcx

            char v7; // al
            NRadEngine::CFixedStringT<128> Buffer; // [rsp+40h] [rbp-288h] BYREF
            NRadEngine::CFixedStringT<512> dst; // [rsp+C0h] [rbp-208h] BYREF

            CurrentProcess = GetCurrentProcess();
            SymSetOptions(0x14u);
            ProjectDir = NRadEngine::CSysInfo::GetProjectDir();
            NRadEngine::CMemory::Fill(&dst, 0, 0x200ui64);
            NRadEngine::CFixedStringT<512>::SPrintF(&dst, "cache*%s\\_temp\\symbols;srv*\\\\airship\\Symbols", ProjectDir);
            if ( !SymInitialize(CurrentProcess, dst.data, 1) )
            {
                NRadEngine::CMemory::Fill(&Buffer, 0, 0x80ui64);
                LastError = GetLastError();
                FormatMessageA(0x1200u, 0i64, LastError, 0x400u, Buffer.data, 0x80u, 0i64);
                NRadEngine::CSysString::Remove(Buffer.data, "\r", 1u);
                v3 = NRadEngine::CSysString::Length(Buffer.data, 0x80ui64) + 1;
                if ( v3 < 0x80 )
                memset(&Buffer.data[v3], 0, 128 - v3);
                NRadEngine::CFixedStringT<128>::StripLeadingSpaces(&Buffer);
                v4 = 0i64;
                v5 = 0i64;
                for ( i = 0i64; i < 0x80; ++i )
                {
                    v7 = Buffer.data[i];
                    if ( !v7 )
                        break;
                    if ( v7 == 32 || (unsigned __int8)(v7 - 9) <= 1u ) {
                        if ( !v4 ) {
                        v4 = 1i64;
                        v5 = i;
                        }
                    } else {
                        v4 = 0i64;
                    }
                }
                if ( v4 && v5 < NRadEngine::CSysString::Length(Buffer.data, 0x80ui64) )
                {
                    Buffer.data[v5] = 0;
                    if ( v5 + 1 < 0x80 )
                        memset(&Buffer.data[v5 + 1], 0, 128 - (v5 + 1));
                }
                NRadEngine::NWriteLog::WriteLog(
                    (NRadEngine::NWriteLog::ELogLevel)8,
                    0i64,
                    "Failed to initialize symbol handler: %s",
                    Buffer.data);
            }
        }

        static void Shutdown(void)
        {
            NRadEngine::CSysTime::Shutdown();
        }
    };
}
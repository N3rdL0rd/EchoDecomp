#include "NRadEngine/include/CSysFile.h"

#include "NRadEngine/include/CFixedStringT.h"
#include "NRadEngine/include/CSysString.h"
#include "NRadEngine/include/CMemory.h"
#include <minwindef.h>

namespace NRadEngine
{
    class CSysFile
    {
    public:
        static void NRadEngine::CSysFile::GetBaseName(
            NRadEngine::CFixedStringT<512> *result,
            const NRadEngine::CFixedStringT<512> *path)
        {
            // TODO: sane variable names
            int v4;              // eax
            int v5;              // eax
            __int64 IndexOf;     // rax
            unsigned __int64 v7; // rbx
            __int64 v8;          // rsi
            char *v9;            // r14

            NRadEngine::CMemory::Fill(result, 0, 0x200ui64);
            NRadEngine::CFixedStringT<512>::Append<512>(result, path); // TODO: Fix template argument
            // TODO: fix LOBYTE issues
            LOBYTE(v4) = NRadEngine::CSysString::EndsWith(result->data, NRadEngine::CSysFile::kPathSeparator, 1u); // TODO: implement kPathSeparator and various CSysString functions
            if (v4)
            {
                do
                {
                    result->data[NRadEngine::CSysString::Length(result->data, 0x200ui64) - 1] = 0;
                    LOBYTE(v5) = NRadEngine::CSysString::EndsWith(result->data, NRadEngine::CSysFile::kPathSeparator, 1u);
                } while (v5);
            }
            IndexOf = NRadEngine::CSysString::LastIndexOf(
                result->data,
                NRadEngine::CSysFile::kPathSeparator,
                1u,
                0xFFFFFFFFFFFFFFFFui64);
            if (IndexOf != -1 || (IndexOf = NRadEngine::CSysString::LastIndexOf(result->data, 47, 1u, 0xFFFFFFFFFFFFFFFFui64), IndexOf != -1))
            {
                v7 = IndexOf + 1;
                v8 = 0i64;
                if (IndexOf + 1 < (unsigned __int64)NRadEngine::CSysString::Length(result->data, 0x200ui64))
                {
                    v9 = &result->data[-v7];
                    do
                    {
                        v9[v7] = result->data[v7];
                        ++v7;
                        ++v8;
                    } while (v7 < NRadEngine::CSysString::Length(result->data, 0x200ui64));
                }
                result->data[v8] = 0;
            }
        }
    };
}
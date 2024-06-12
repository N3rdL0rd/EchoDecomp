#include "NRadEngine/include/CMemory.h"

#include <vcruntime_string.h>

namespace NRadEngine
{
    class CMemory
    {
    public:
        static void __fastcall Fill(void *destination, int value, size_t numBytes)
        {
            // TODO: stubbed
        }
        static void *__fastcall Move(void *dst, const void *src, unsigned __int64 count)
        {
            if (count)
                return memmove(dst, src, count);
            else
                return 0i64;
        }
        static void *__fastcall Copy(void *dst, const void *src, unsigned __int64 count)
        {
            if (!count)
                return 0i64;
            memmove(dst, src, count);
            return dst;
        }
    };
}
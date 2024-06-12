#include "NRadEngine/include/CSymbol64.h"
#include "NRadEngine/include/globals.h"

#include <minwindef.h>

namespace NRadEngine
{
    class CSymbol64
    {
        public:
        static __int64 CalculateSymbolValue(
            const char *str,
            __int64 base,
            unsigned int record,
            unsigned __int64 maxlen,
            unsigned int upload)
        {
            const char *currentChar;
            __int64 hashValue;
            unsigned __int64 lengthRemaining;
            char normalizedChar;
            unsigned __int64 tempHash;
            void(__fastcall * RecordMethod64)(NRadEngine::CSymbol64, const char *, NRadEngine::CSymbol64, unsigned __int64, unsigned int);
            unsigned __int8 lastByte;

            if (!str || !*str)
                return base;
            currentChar = str;
            hashValue = base;
            lastByte = HIBYTE(base);
            lengthRemaining = maxlen;
            do
            {
                if (!lengthRemaining--)
                    break;
                normalizedChar = *currentChar;
                tempHash = (hashValue << 8) ^ NRadEngine::precache[lastByte];
                if ((unsigned __int8)(*currentChar - 65) <= 0x19u)
                    normalizedChar += 32;
                ++currentChar;
                hashValue = normalizedChar ^ tempHash;
                lastByte = HIBYTE(hashValue);
            } while (*currentChar);
            if (record)
            {
                RecordMethod64 = NRadEngine::CSymbolLookup::GetRecordMethod64(); // TODO: CSymbolLookup
                if (RecordMethod64)
                    ((void(__fastcall *)(__int64, const char *, __int64, unsigned __int64, unsigned int))RecordMethod64)(
                        hashValue,
                        str,
                        base,
                        maxlen,
                        upload);
            }
            return hashValue;
        }
    };
}
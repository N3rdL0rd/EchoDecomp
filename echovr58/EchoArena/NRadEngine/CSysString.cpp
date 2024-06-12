#include "NRadEngine/include/CSysString.h"

namespace NRadEngine
{
    class CSysString
    {
    public:
        static signed __int64 Length(const char *str, unsigned __int64 maxlen)
        {
            const char *i;
            for (i = str; maxlen; ++i)
            {
                --maxlen;
                if (!*i)
                    break;
            }
            return i - str;
        }
        static void ToLower(char *str, unsigned __int64 maxLength)
        {
            char current;

            for (; *str; *str++ = current)
            {
                if (!maxLength--)
                    break;
                current = *str;
                if ((unsigned __int8)(*str - 'A') <= 'Z' - 'A')
                    current += 32; // HACK: all uppercase letters are 32 bytes away from their lowercase counterparts ('A' - 'a' = -32, 'B' - 'b' = -32, etc.)
            }
        }
        static void ToUpper(char *str, unsigned __int64 maxLength)
        {
            char current;

            for (; *str; *str++ = current)
            {
                if (!maxLength--)
                    break;
                current = *str;
                if ((unsigned __int8)(*str - 'a') <= 'z' - 'a')
                    current -= 32; // HACK: see above
            }
        }
        static __int64 Compare(
            const char *str1,
            const char *str2,
            unsigned int matchcase,
            unsigned __int64 len)
        {
            signed __int64 offset;
            char charFromStr1;
            char charFromStr2;
            __int64 comparisonResult;

            if (len)
            {
                offset = str1 - str2;
                do
                {
                    charFromStr1 = str2[offset];
                    if (!charFromStr1 && !*str2) // If end of either string is reached
                        break;
                    charFromStr2 = *str2;
                    if (!matchcase)
                    {
                        if ((unsigned __int8)(charFromStr1 - 'A') <= 0x19u) // convert both characters to uppercase
                            charFromStr1 += 32;
                        if ((unsigned __int8)(charFromStr2 - 'A') <= 0x19u)
                            charFromStr2 += 32;
                    }
                    if (charFromStr1 >= charFromStr2)
                        comparisonResult = charFromStr1 > charFromStr2;
                    else
                        comparisonResult = -1i64;
                    ++str2;
                    if (comparisonResult)
                        return comparisonResult;
                    --len;
                } while (len);
            }
            return 0i64;
        }
    };
}
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
        static __int64 Compare(char ch0, char ch1, unsigned int matchcase)
        {
            if (!matchcase)
            {
                if ((unsigned __int8)(ch0 - 65) <= 0x19u)
                    ch0 += 32;
                if ((unsigned __int8)(ch1 - 65) <= 0x19u)
                    ch1 += 32;
            }
            if (ch0 >= ch1)
                return ch0 > ch1;
            else
                return -1i64;
        }
        static char *Copy(char *dst, const char *src, unsigned __int64 dstsize)
        {
            /**
             * Copies a string from `src` to `dst` up to `dstsize` - 1 characters, ensuring the result is null-terminated.
             *
             * @param dst The destination buffer where the string will be copied to.
             * @param src The source string to be copied.
             * @param dstsize The size of the destination buffer. This includes space for the null terminator.
             * @return Returns the original `dst` pointer.
             *
             * @note If `dstsize` is 0, the function immediately returns `dst` without copying any characters.
             *       The function copies characters from `src` to `dst` until either the end of `src` is reached
             *       or `dstsize` - 1 characters have been copied. The destination string will always be null-terminated,
             *       even if truncation occurs due to `dstsize` being smaller than the length of `src`.
             */
            signed __int64 offset;
            char current_char;

            if (!dstsize)
                return dst;
            char *original_dst = dst;
            unsigned __int64 remaining_space = dstsize - 1;
            if (remaining_space)
            {
                offset = src - dst;
                do
                {
                    current_char = dst[offset];
                    if (!current_char)
                        break;
                    *dst++ = current_char;
                    --remaining_space;
                } while (remaining_space);
            }
            *dst = 0;
            return original_dst;
        }
        static __int64 Count(
            const char *str,
            char val,
            unsigned int matchcase,
            unsigned __int64 fromidx,
            unsigned __int64 toidx)
        {
            /**
             * Counts occurrences of a character `val` in the string `str` within the specified range.
             *
             * @param str The string in which to search for occurrences of `val`.
             * @param val The character to count occurrences of.
             * @param matchcase Flag indicating whether the comparison is case-sensitive (1) or not (0).
             * @param fromidx The starting index (inclusive) within `str` to begin searching.
             * @param toidx The ending index (exclusive) within `str` to stop searching.
             * @return Returns the number of times `val` occurs in `str` between `fromidx` and `toidx`.
             *
             * @note If `fromidx` is negative or greater than or equal to `toidx`, the function returns 0.
             *       The function iterates over the characters in `str` between indices `fromidx` and `toidx - 1`.
             *       It counts occurrences of `val` based on the `matchcase` flag, considering case-sensitivity as specified.
             */
            __int64 count = 0;            // Initialize count of occurrences
            unsigned __int64 current_idx; // Current index in the loop
            const char *current_char;     // Pointer to the current character in `str`
            char current_char_lowercase;  // Lowercase version of `current_char`
            char val_lowercase;           // Lowercase version of `val`

            for (current_idx = 0; fromidx < toidx; fromidx = current_idx + 1)
            {
                if (fromidx)
                {
                    current_idx = fromidx + 1;
                    current_char = str;
                    if (fromidx != -1i64)
                    {
                        do
                        {
                            --current_idx;
                            if (!*current_char)
                                break;
                            ++current_char;
                        } while (current_idx);
                    }
                    if (fromidx >= current_char - str)
                        goto END_LOOP;
                }
                current_char = &str[fromidx];
                current_char_lowercase = *current_char;
                if (!*current_char)
                {
                END_LOOP:
                    current_idx = -1i64;
                }
                else
                {
                    while (1)
                    {
                        val_lowercase = val;
                        if (!matchcase)
                        {
                            if ((unsigned __int8)(current_char_lowercase - 65) <= 0x19u)
                                current_char_lowercase += 32;
                            if ((unsigned __int8)(val - 65) <= 0x19u)
                                val_lowercase = val + 32;
                        }
                        if (current_char_lowercase >= val_lowercase && current_char_lowercase <= val_lowercase)
                            break;
                        current_char_lowercase = *++current_char;
                        if (!current_char_lowercase)
                            goto END_LOOP;
                    }
                    current_idx = current_char - str;
                }
                if (current_idx < toidx)
                    ++count;
            }
            return count;
        }
        static signed __int64 DataToHex(
            const char *data,
            unsigned __int64 datalen,
            char *str,
            unsigned __int64 strlen)
        {
            /**
             * Converts binary data to hexadecimal representation and stores it in a string.
             *
             * @param data Pointer to the binary data to be converted.
             * @param datalen Length of the binary data in bytes.
             * @param str Pointer to the output string where hexadecimal representation will be stored.
             * @param strlen Length of the output string buffer in bytes.
             * @return Returns the number of characters written to `str`, excluding the null terminator.
             *
             * @note The function converts each byte of `data` into two hexadecimal characters.
             *       It stops converting when either `datalen` bytes are processed or `strlen` becomes insufficient.
             *       The output in `str` is always null-terminated if `strlen` permits.
             */
            unsigned __int64 max_conversions = datalen; // Maximum number of conversions to perform
            char *output_ptr;                           // Pointer to current position in `str` to write output
            unsigned __int64 remaining_space;           // Remaining space in `str` buffer
            unsigned __int8 high_nibble;                // Upper 4 bits of the current byte
            char hex_high;                              // Hexadecimal character representing the upper nibble
            unsigned __int8 low_nibble;                 // Lower 4 bits of the current byte
            char hex_low;                               // Hexadecimal character representing the lower nibble
            if (strlen < 2 * datalen + 1)
                max_conversions = (strlen - 1) >> 1;

            output_ptr = str;
            remaining_space = strlen;

            for (; max_conversions > 0; --max_conversions)
            {
                if (!remaining_space || !remaining_space--)
                    break;

                high_nibble = (*data >> 4) & 0xF;
                hex_high = high_nibble >= 0xA ? high_nibble + 55 : high_nibble + 48;
                *output_ptr++ = hex_high;

                low_nibble = *data & 0xF;
                hex_low = low_nibble >= 0xA ? low_nibble + 55 : low_nibble + 48;
                *output_ptr++ = hex_low;

                ++data;
            }

            // Ensure null-termination if space permits
            if (remaining_space - 1 <= 0xFFFFFFFFFFFFFFFDui64)
                *output_ptr++ = '\0';

            return output_ptr - str;
        }
    };
}
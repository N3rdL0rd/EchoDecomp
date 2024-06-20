#include "NRadEngine/include/CSysString.h"

#include <minwindef.h>
#include <ints.h>
#include <stringapiset.h>

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
        static __int64 EndsWith(const char *str, const char *suffix, unsigned int matchcase)
        {
            /**
             * Checks if a string ends with a specific suffix.
             *
             * @param str The string to check.
             * @param suffix The suffix to compare against the end of `str`.
             * @param matchcase Flag indicating whether the comparison is case-sensitive (1) or not (0).
             * @return Returns 1 if `str` ends with `suffix` (case-sensitive or insensitive based on `matchcase`),
             *         otherwise returns 0.
             */
            __int64 str_length;
            const char *str_ptr;
            unsigned __int64 suffix_length;
            const char *suffix_ptr;
            __int64 compare_length;
            const char *compare_ptr;
            unsigned int result;
            char suffix_char;
            char str_char;
            __int64 comparison_result;
            bool equal;

            str_length = -1i64;
            str_ptr = str;
            do
            {
                --str_length;
                if (!*str_ptr)
                    break;
                ++str_ptr;
            } while (str_length);
            suffix_length = str_ptr - str;
            suffix_ptr = suffix;

            compare_length = -1i64;
            do
            {
                --compare_length;
                if (!*suffix_ptr)
                    break;
                ++suffix_ptr;
            } while (compare_length);
            compare_length = suffix_ptr - suffix;

            // If the suffix is longer than the string, it cannot be a suffix
            if (suffix_length < compare_length)
                return 0i64;

            comparison_result = -1i64;
            compare_ptr = &str[suffix_length - compare_length - (_QWORD)suffix];

            result = 0;
            do
            {
                suffix_char = suffix[(_QWORD)compare_ptr];
                if (!suffix_char && !*suffix)
                    break;
                str_char = *suffix;
                if (!matchcase)
                {
                    if ((unsigned __int8)(suffix_char - 65) <= 0x19u)
                        suffix_char += 32;
                    if ((unsigned __int8)(str_char - 65) <= 0x19u)
                        str_char += 32;
                }
                if (suffix_char >= str_char)
                    comparison_result = suffix_char > str_char;
                else
                    comparison_result = -1i64;
                ++suffix;
                equal = comparison_result == 0;
                if (comparison_result)
                    goto END;
                --result;
            } while (result);
            equal = 1;

        END:
            // expands to ((BYTE)(((DWORD_PTR)(result)) & 0xff)) = v19; - not sure what this is supposed to do - maybe v15 = LOBYTE(v19)?
            // LOBYTE(v15) = v19; // TODO: investigate LOBYTE macro and ida's decompilation
            result = LOBYTE(equal); // temporary fix
            return result;
        }
        static char EndsWith(const char *str, char suffix, unsigned int matchcase)
        {
            /**
             * Checks if a string ends with a specific character.
             *
             * @param str The string to check.
             * @param suffix The character to compare against the last character of `str`.
             * @param matchcase Flag indicating whether the comparison is case-sensitive (1) or not (0).
             * @return Returns 1 if the last character of `str` matches `suffix` (case-sensitive or insensitive based on `matchcase`),
             *         otherwise returns 0.
             */
            signed __int64 str_length;
            signed __int8 last_char;
            int result = -1;
            char str_char;
            char suffix_char;

            str_length = -1;
            const char *str_ptr = str;
            do
            {
                --str_length;
                if (!*str_ptr)
                    break;
                ++str_ptr;
            } while (str_length);

            if (str_length)
            {
                last_char = str[str_length - 1];

                if (!matchcase)
                {
                    if ((unsigned __int8)(last_char - 65) <= 0x19u)
                        last_char += 32;
                    if ((unsigned __int8)(suffix - 65) <= 0x19u)
                        suffix += 32;
                }

                if (last_char >= suffix)
                    result = last_char > suffix;

                // LOBYTE(v7) = v3 == 0;
                // TODO: investigate LOBYTE macro
                result = LOBYTE(result == 0); // temporary fix
            }

            return result;
        }
        static void FromWideChar(char *dst, const wchar_t *src, unsigned __int64 dstsize)
        {
            WideCharToMultiByte(0, 0, src, -1, dst, dstsize, 0i64, 0i64);
        }
        static void FromWideCharFast(char *dst, const wchar_t *src, unsigned __int64 dstsize)
        {
            unsigned __int64 copy_length;
            unsigned __int64 copy_index;

            __int64 src_length = -1;
            const wchar_t *src_ptr = src;
            do
            {
                --src_length;
                if (!*src_ptr)
                    break;
                ++src_ptr;
            } while (src_length);

            copy_length = src_ptr - src;

            if (dstsize - 1 < copy_length)
                copy_length = dstsize - 1;

            copy_index = 0;

            while (copy_index < copy_length)
            {
                dst[copy_index] = (char)src[copy_index];
                ++copy_index;
            }

            // Ensure null-termination
            dst[copy_length] = '\0';
        }
        static signed __int64 IndexOf(
            const char *str,
            const char *substr,
            unsigned int matchcase,
            unsigned __int64 fromidx)
        {
            __int64 substr_length;
            __int64 str_length;
            const char *substr_ptr;
            const char *str_ptr;

            substr_length = -1;
            substr_ptr = substr;
            do
            {
                --substr_length;
                if (!*substr_ptr)
                    break;
                ++substr_ptr;
            } while (substr_length);

            str_length = -1;
            str_ptr = str;
            do
            {
                --str_length;
                if (!*str_ptr)
                    break;
                ++str_ptr;
            } while (str_length);

            return IndexOf(str, str_ptr - str, substr, substr_ptr - substr, matchcase, fromidx);
        }
        static signed __int64 IndexOf(
            const char *str,
            char ch,
            unsigned int matchcase,
            unsigned __int64 fromidx)
        {
            unsigned __int64 str_length;
            const char *search_ptr;
            char current_char;
            char search_char;

            if (fromidx)
            {
                str_length = fromidx + 1;
                search_ptr = str;
                if (fromidx != -1i64)
                {
                    do
                    {
                        --str_length;
                        if (!*search_ptr)
                            break;
                        ++search_ptr;
                    } while (str_length);
                }
                if (fromidx >= search_ptr - str)
                    return -1i64;
            }

            const char *start_ptr = &str[fromidx];
            current_char = str[fromidx];
            if (!current_char)
                return -1i64;

            while (1)
            {
                search_char = ch;
                if (!matchcase)
                {
                    if ((unsigned __int8)(current_char - 65) <= 0x19u)
                        current_char += 32;
                    if ((unsigned __int8)(ch - 65) <= 0x19u)
                        search_char += 32;
                }
                if (current_char >= search_char && current_char <= search_char)
                    break;
                current_char = *++start_ptr;
                if (!current_char)
                    return -1i64;
            }

            return start_ptr - str;
        }
        static signed __int64 IndexOf(
            const char *str,
            unsigned __int64 strlength,
            const char *substr,
            unsigned __int64 substrlength,
            unsigned int matchcase,
            unsigned __int64 fromidx)
        {
            const char *end_search;
            const char *search_start;
            signed __int64 substr_index;
            unsigned __int64 remaining_length;
            const char *substr_ptr;
            char current_char;
            char search_char;

            end_search = &str[strlength - substrlength];
            search_start = &str[fromidx];

            if (search_start > end_search)
                return -1i64;

            substr_index = search_start - substr;

        SEARCHLOOP:
            remaining_length = substrlength;
            substr_ptr = substr;

            while (remaining_length)
            {
                current_char = substr_ptr[substr_index];
                if (!current_char && !*substr_ptr)
                    break;
                search_char = *substr_ptr;
                if (!matchcase)
                {
                    if ((unsigned __int8)(current_char - 65) <= 0x19u)
                        current_char += 32;
                    if ((unsigned __int8)(search_char - 65) <= 0x19u)
                        search_char += 32;
                }
                if (current_char >= search_char)
                {
                    if (current_char > search_char)
                    {
                        ++search_start;
                        ++substr_index;
                        if (search_start <= end_search)
                            goto SEARCHLOOP;
                        return -1i64;
                    }
                }
                else
                {
                    substr_index = -1i64;
                }
                ++substr_ptr;
            }

            return search_start - str;
        }
        static signed __int64 IndexOf(
            const char *str,
            unsigned __int64 strlength,
            char ch,
            unsigned int matchcase,
            unsigned __int64 fromidx)
        {
            const char *end_search;
            const char *search_start;
            char current_char;
            char search_char;

            end_search = &str[strlength];
            search_start = &str[fromidx];

            if (search_start >= end_search)
                return -1i64;

            while (1)
            {
                current_char = *search_start;
                search_char = ch;

                if (!matchcase)
                {
                    if ((unsigned __int8)(current_char - 65) <= 0x19u)
                        current_char += 32;
                    if ((unsigned __int8)(search_char - 65) <= 0x19u)
                        search_char += 32;
                }

                if (current_char >= search_char && current_char <= search_char)
                    break;

                if (++search_start >= end_search)
                    return -1i64;
            }

            return search_start - str;
        }
        static __int64 IsUInt64(const char *str, __int64 base)
        {
            char char_value;
            unsigned int digit_value;
            __int64 digit_count;

            const char *current_char = str;

            if (!str)
                return 0i64;

            while (*current_char == 32 || *current_char == 9)
                ++current_char;

            if (*current_char == 48 && ((*current_char + 1 - 88) & 0xDF) == 0)
            {
                if (*(current_char + 1) == 88)
                {
                    base = 16i64;
                    current_char += 2;
                }
            }
            else if (*current_char == 43) // Handle leading '+' sign
            {
                ++current_char;
            }

            char_value = *current_char;
            digit_count = 0i64;

            while (char_value)
            {
                // Determine the numeric value of the character with some hacky math
                if ((unsigned __int8)(char_value - 48) > 9u)
                {
                    if ((unsigned __int8)(char_value - 97) > 0x19u)
                    {
                        if ((unsigned __int8)(char_value - 65) > 0x19u)
                            return 0i64;
                        digit_value = char_value - 55;
                    }
                    else
                    {
                        digit_value = char_value - 87;
                    }
                }
                else
                {
                    digit_value = char_value - 48;
                }

                if (digit_value < 0 || digit_value >= base)
                    return 0i64;

                char_value = *++current_char;
                ++digit_count;
            }

            // Return 1 if at least one valid digit was found, otherwise 0
            // LOBYTE(digit_count) = digit_count != 0; // todo: investigate LOBYTE macro
            digit_count = LOBYTE(digit_count != 0); // temporary fix
            return digit_count;
        }
        static bool IsWhiteSpace(char c) // originally _BOOL8, but bool is more readable and functionally equivalent
        {
            return c == 32 || (unsigned __int8)(c - 9) <= 4u; // neat trick!
        }
        static __int64 LastIndexOf(
            const char *str,
            char ch,
            unsigned int matchcase,
            unsigned __int64 fromidx)
        {
            char search_char;
            __int64 result_idx;
            __int64 str_offset;

            if (matchcase)
            {
                if ((unsigned __int8)(ch - 65) > 0x19u)
                    search_char = ch;
                else
                    search_char = ch + 32;
                if ((unsigned __int8)(ch - 97) <= 0x19u)
                    ch -= 32;
            }
            else
            {
                search_char = ch;
            }

            result_idx = -1i64;

            if (fromidx)
            {
                str_offset = -(__int64)str;
                do
                {
                    char current_char = *str;
                    if (!current_char)
                        break;
                    if (current_char == search_char || current_char == ch)
                        result_idx = (__int64)&str[str_offset];
                    ++str;
                    --fromidx;
                } while (fromidx);
            }

            return result_idx;
        }
        static signed __int64 LastIndexOf(
            const char *str,
            unsigned __int64 strlength,
            const char *substr,
            unsigned __int64 substrlength,
            unsigned int matchcase)
        {
            const char *end_ptr;
            signed __int64 substr_index;
            unsigned __int64 current_length;
            const char *current_substr;
            char str_char;
            char substr_char;
            __int64 comparison;

            end_ptr = &str[strlength - substrlength];

            if (end_ptr < str)
                return -1i64;

            substr_index = end_ptr - substr;

        LABEL_3:
            current_length = substrlength;
            for (current_substr = substr; current_length; --current_length)
            {
                str_char = current_substr[substr_index];
                if (!str_char && !*current_substr)
                    break;
                substr_char = *current_substr;
                if (!matchcase)
                {
                    if ((unsigned __int8)(str_char - 65) <= 0x19u)
                        str_char += 32;
                    if ((unsigned __int8)(substr_char - 65) <= 0x19u)
                        substr_char += 32;
                }
                if (str_char >= substr_char)
                    comparison = str_char > substr_char;
                else
                    comparison = -1i64;
                ++current_substr;
                if (comparison)
                {
                    --end_ptr;
                    --substr_index;
                    if (end_ptr >= str)
                        goto LABEL_3;
                    return -1i64;
                }
            }
            return end_ptr - str;
        }
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
        static __int64 Length(const wchar_t *str, unsigned __int64 maxlen)
        {
            const wchar_t *i; // rax

            for (i = str; maxlen; ++i)
            {
                --maxlen;
                if (!*i)
                    break;
            }
            return i - str;
        }
    };
}
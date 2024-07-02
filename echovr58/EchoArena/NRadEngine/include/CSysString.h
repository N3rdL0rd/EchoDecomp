#include <minwindef.h>

namespace NRadEngine
{
    class CSysString
    {
    public:
        static signed __int64 Length(const char *str, unsigned __int64 maxlen);
        static void ToLower(char *str, unsigned __int64 maxLength);
        static void ToUpper(char *str, unsigned __int64 maxLength);
        static __int64 Compare(const char *str1, const char *str2, unsigned int matchcase, unsigned __int64 len);
        static __int64 Compare(char ch0, char ch1, unsigned int matchcase);
        static char *Copy(char *dst, const char *src, unsigned __int64 dstsize);
        static __int64 Count(const char *str, char val, unsigned int matchcase, unsigned __int64 fromidx, unsigned __int64 toidx);
        static signed __int64 DataToHex(const char *data, unsigned __int64 datalen, char *str, unsigned __int64 strlen);
        static __int64 EndsWith(const char *str, const char *suffix, unsigned int matchcase);
        static char EndsWith(const char *str, char suffix, unsigned int matchcase);
        static void FromWideChar(char *dst, const wchar_t *src, unsigned __int64 dstsize);
        static void FromWideCharFast(char *dst, const wchar_t *src, unsigned __int64 dstsize);
        static signed __int64 IndexOf(const char *str, char ch, unsigned int matchcase, unsigned __int64 fromidx);
        static signed __int64 IndexOf(const char *str, unsigned __int64 strlength, const char *substr, unsigned __int64 substrlength, unsigned int matchcase, unsigned __int64 fromidx);
        static signed __int64 IndexOf(const char *str, unsigned __int64 strlength, char ch, unsigned int matchcase, unsigned __int64 fromidx);
        static __int64 IsUInt64(const char *str, __int64 base);
        static __int64 LastIndexOf(const char *str, char ch, unsigned int matchcase, unsigned __int64 fromidx);
        static signed __int64 LastIndexOf(const char *str, unsigned __int64 strlength, const char *substr, unsigned __int64 substrlength, unsigned int matchcase);
        static signed __int64 Length(const wchar_t *str, unsigned __int64 maxlen);
        static void Remove(char *sourceString, const char *substringToRemove, unsigned int matchCase);
        static void Replace(char *string, char oldChar, char newChar, unsigned int matchCase);
        static unsigned __int64 SNPrintF(char *outputBuffer, unsigned __int64 bufferLength, const char *formatString, ...);
        static unsigned __int64 SScanF(const char *inputBuffer, const char *formatString, ...);
        static bool StartsWith(const char *mainString, const char *prefixString, unsigned int matchCase, unsigned __int64 startIndex);
        static void SubString(const char *sourceString, unsigned __int64 sourceLength, unsigned __int64 startIndex, unsigned __int64 endIndex, char *outputString);
        static void ToAlphaNumeric(char *inputString, char replacementChar);
        static void ToLower(char *inputString, unsigned __int64 maxLength);
        static NRadEngine::CSymbol64 *ToSymbol(NRadEngine::CSymbol64 *result, const char *str, unsigned int record, unsigned int upload);
        static unsigned __int64 ToUInt32(const char *str, __int64 base);
        static __int64 ToUInt64(const char *inputString, __int64 radix);
        static void ToWideChar(wchar_t *dst, const char *src, unsigned __int64 dstsize);
        static unsigned __int64 VSCPrintF(const char *formatString, char *argumentList);
        static unsigned __int64 VSNPrintF(char *outputBuffer, unsigned __int64 bufferSize, const char *formatString, char *argumentList);
    };
}

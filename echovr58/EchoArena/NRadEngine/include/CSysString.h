namespace NRadEngine
{
    class CSysString
    {
    public:
        static signed __int64 __fastcall Length(const char *str, unsigned __int64 maxlen);
        static void ToUpper(char *str, unsigned __int64 maxLength);
        static void ToLower(char *str, unsigned __int64 maxLength);
        static __int64 Compare(
            const char *str1,
            const char *str2,
            unsigned int matchcase,
            unsigned __int64 len);
    };
}
namespace NRadEngine
{
    class CStringTable
    {
        public:
        NRadEngine::CTable<char> chararray; // TODO: CTable
        static unsigned __int64 __fastcall Grow(const char *string);

        private:
        static unsigned __int64 __fastcall InternalGrow(const char *string, unsigned __int64 len);
    };
}
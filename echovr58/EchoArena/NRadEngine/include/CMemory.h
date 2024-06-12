namespace NRadEngine {
    class CMemory {
        public:
        static void Fill(void* destination, int value, size_t numBytes);
        static void *__fastcall Move(void *dst, const void *src, unsigned __int64 count);
        static void *__fastcall Copy(void *dst, const void *src, unsigned __int64 count);
    };
}
namespace NRadEngine {
    class CSymbol64 {
        public:
        static __int64 CalculateSymbolValue(
            const char *str,
            __int64 base,
            unsigned int record,
            unsigned __int64 maxlen,
            unsigned int upload);
    };
}
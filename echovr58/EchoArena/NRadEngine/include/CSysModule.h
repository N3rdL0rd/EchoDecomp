#include "NRadEngine/include/CFixedStringT.h"

namespace NRadEngine
{
    class CSysModule {
        public:
        static void GetModuleFile(unsigned __int64 module, NRadEngine::CFixedStringT<512> *path);
    };
}
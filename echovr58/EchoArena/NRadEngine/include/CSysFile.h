#include "NRadEngine/include/CFixedStringT.h"

namespace NRadEngine
{
    class CSysFile
    {
        public:
        static void GetBaseName(NRadEngine::CFixedStringT<512> *result, const NRadEngine::CFixedStringT<512> *path);
    };
}
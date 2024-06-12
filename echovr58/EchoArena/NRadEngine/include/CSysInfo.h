#include "NRadEngine/include/CFixedStringT.h"
#include "NRadEngine/include/CSysModule.h"

namespace NRadEngine
{
    class CSysInfo
    {
        public:
        static void GetExecutableFile(NRadEngine::CFixedStringT<512> *path);
    };
}
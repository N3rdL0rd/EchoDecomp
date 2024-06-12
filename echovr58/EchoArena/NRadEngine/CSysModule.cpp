#include "NRadEngine/include/CSysModule.h"

#include <wtypes.h>
#include "NRadEngine/include/CFixedStringT.h"

namespace NRadEngine
{
    class CSysModule {
        public:
        static void GetModuleFile(unsigned __int64 module, NRadEngine::CFixedStringT<512> *path)
        {
            GetModuleFileNameA((HMODULE)module, path->data, 0x200u);
        }
    };
}
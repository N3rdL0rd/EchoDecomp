#include "NRadEngine/include/CSysInfo.h"

#include "NRadEngine/include/CFixedStringT.h"
#include "NRadEngine/include/CSysModule.h"

namespace NRadEngine
{
    class CSysInfo
    {
        public:
        static void GetExecutableFile(NRadEngine::CFixedStringT<512> *path)
        {
            NRadEngine::CSysModule::GetModuleFile(0i64, path);
        }
    };
}
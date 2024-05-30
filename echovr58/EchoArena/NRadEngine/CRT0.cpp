#include <cstdio>
#include "NRadEngine/include/globals.h"
#include "NRadEngine/include/CSysOs.h"

namespace NRadEngine {
    class CRT0 {
        public:
        static void InitPlatform(void) {
            NRadEngine::gLoggingInitialized = 1;
            NRadEngine::CSysOS::Init();
            NRadEngine::CSysOS::InitDbgSymbolLookups();
        }

        static void Init() {
            char _Buffer[264];
            sprintf(_Buffer, "RAD_Version: release148823");
            InitPlatform();
        }
    };
}

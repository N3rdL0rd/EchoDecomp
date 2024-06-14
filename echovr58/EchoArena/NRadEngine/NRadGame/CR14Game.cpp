#include "NRadEngine/NRadGame/include/CR14Game.h"

namespace NRadEngine {
    namespace NRadGame {
        class CR14Game {
            public:
            char *appname;
            NRadEngine::CFlagsT<unsigned __int64,1> flags; // TODO: CFlagsT
            __int64 returncode;
            static void SetMultiplayerApp(NRadEngine::NRadGame::CR14Game *obj)
            {
                obj->flags.flags[0] |= 0x800000000000000ui64;
                obj->flags.flags[0] |= 0x1000000000000000ui64;
            }
        };
    }
}
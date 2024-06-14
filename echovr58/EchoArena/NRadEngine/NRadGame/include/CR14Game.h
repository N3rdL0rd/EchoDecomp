namespace NRadEngine {
    namespace NRadGame {
        class CR14Game {
            public:
            char *appname;
            NRadEngine::CFlagsT<unsigned __int64,1> flags;
            __int64 returncode;
            static void SetMultiplayerApp(NRadEngine::NRadGame::CR14Game *obj);
        };
    }
}
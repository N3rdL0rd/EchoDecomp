#include <windows.h>

namespace NRadEngine {
    class CSysTime {
        private:
        static LARGE_INTEGER tick_cur;
        static unsigned __int64 tick_min;
        public:
        static void Init() {
            QueryPerformanceCounter(&NRadEngine::CSysTime::tick_cur);
            NRadEngine::CSysTime::tick_min = NRadEngine::CSysTime::tick_cur.QuadPart;
            timeBeginPeriod(1u);
        }
        static void Shutdown() {
            timeEndPeriod(1u);
        }
    };
}
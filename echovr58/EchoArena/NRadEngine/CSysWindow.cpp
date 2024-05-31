#include <Windows.h>
#include "NRadEngine/NWriteLog/include/NWriteLog.h"

namespace NRadEngine {
    class CSysWindow {
        public:
        static void __fastcall ShowMessageBox(int *handle, const char *msg, const char *caption)
        {
            NRadEngine::NWriteLog::WriteLog(
                NRadEngine::NWriteLog::eInfo,
                0i64,
                "=================================================================================");
            if ( caption )
                NRadEngine::NWriteLog::WriteLog(NRadEngine::NWriteLog::eInfo, 0i64, "%s\n", caption);
            if ( msg )
                NRadEngine::NWriteLog::WriteLog(NRadEngine::NWriteLog::eInfo, 0i64, "%s", msg);
            NRadEngine::NWriteLog::WriteLog(
                NRadEngine::NWriteLog::eInfo,
                0i64,
                "=================================================================================");
            MessageBoxA((HWND)handle, msg, caption, 0);
        }
    };
}
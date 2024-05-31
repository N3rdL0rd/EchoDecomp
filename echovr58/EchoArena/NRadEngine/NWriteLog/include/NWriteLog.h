#include <cstdarg>

namespace NRadEngine {
    namespace NWriteLog {
        enum ELogLevel {
            eError = 0,
            eWarning = 1,
            eInfo = 2,
            eDebug = 3,
            eVerbose = 4
        };

        void WriteLog(NRadEngine::NWriteLog::ELogLevel loglevel, unsigned __int64 channel, const char *format, ...);
        void WriteLogV(NRadEngine::NWriteLog::ELogLevel loglevel, unsigned __int64 channel, const char *format, char *args);
    }
}
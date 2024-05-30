#include <cstdarg>
#include <vcruntime_string.h>
#include "NRadEngine/include/CMemory.h"
#include "NRadEngine/include/CSysString.h"

namespace NRadEngine {
    class NWriteLog {
        public:
        enum ELogLevel {
            eError = 0,
            eWarning = 1,
            eInfo = 2,
            eDebug = 3,
            eVerbose = 4
        };
        void WriteLog(NRadEngine::NWriteLog::ELogLevel loglevel, unsigned __int64 channel, const char *format, ...) {
            va_list args;
            va_start(args, format);
            NRadEngine::NWriteLog::WriteLogV(loglevel, channel, format, args);
        }
        private:
        void WriteLogV(NRadEngine::NWriteLog::ELogLevel loglevel, unsigned __int64 channel, const char *format, char *args) {
            unsigned __int64 length; // rax
            NRadEngine::CLoggingData *loggingData; // rax
            unsigned __int64 iused; // rcx
            char dst[2048]; // [rsp+20h] [rbp-808h] BYREF

            NRadEngine::CMemory::Fill(dst, 0, 0x800ui64);
            if ( NRadEngine::CSysString::Compare(format, "%s", 1u, 0xFFFFFFFFFFFFFFFFui64) )
            {
                if ( NRadEngine::CSysString::IndexOf(format, 37, 1u, 0i64) != -1 )
                {
                NRadEngine::CSysString::VSNPrintF(dst, 0x800ui64, format, args);
                length = NRadEngine::CSysString::Length(dst, 0x800ui64) + 1;
                if ( length < 0x800 )
                    memset(&dst[length], 0, 2048 - length);
                format = dst;
                }
            }
            else
            {
                format = *(const char **)args;
            }
            if ( NRadEngine::CGlobal<NRadEngine::CEnvironment,0>::instance )
            {
                loggingData = NRadEngine::CEnvData<NRadEngine::CLoggingData,0>::Instance();
                if ( loggingData )
                {
                if ( (loggingData->logoptions.flags[0] & 1) != 0 )
                    return;
                iused = loggingData->callbacksremote.iused;
                if ( (loggingData->logoptions.flags[0] & 2) == 0 )
                    iused += loggingData->callbackslocal.iused;
                if ( iused )
                {
                    NRadEngine::CLoggingData::ExecuteAllCallbacks(loggingData, format, channel, loglevel);
                    return;
                }
                NRadEngine::CLoggingData::AddToHistory(loggingData, format, loglevel);
                }
            }
            NRadEngine::NWriteLog::DefaultLogTarget(loglevel, channel, format);
        }
    }
}
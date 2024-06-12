#include "NRadEngine/include/CLoggingData.h"

namespace NRadEngine {
    class CLoggingData {
        public:
        static CLoggingData NRadEngine::CEnvData<NRadEngine::CLoggingData,0>::Instance()
        {
        DWORD TlsHandle; // edi
        NRadEngine::CLoggingData *result; // rax
        void *Global; // rbx

        TlsHandle = NRadEngine::CEnvData<NRadEngine::CLoggingData,0>::tls;
        if ( NRadEngine::CEnvData<NRadEngine::CLoggingData,0>::tls == -1 )
        {
            TlsHandle = NRadEngine::CEnvironment::GetTlsHandle(
                        NRadEngine::CGlobal<NRadEngine::CEnvironment,0>::instance,
                        *(NRadEngine::CSymbol64 *)((unsigned __int64)"QOlPrEfIxCLoggingData" & 0xFFFFFFFFFFFFFFF8ui64),
                        0i64);
            NRadEngine::CEnvData<NRadEngine::CLoggingData,0>::tls = TlsHandle;
        }
        result = (NRadEngine::CLoggingData *)NRadEngine::CSysThread::GetTLS(TlsHandle);
        if ( !result )
        {
            if ( NRadEngine::CGlobal<NRadEngine::CEnvironment,0>::instance )
            {
            Global = NRadEngine::CEnvironment::GetGlobal(
                        NRadEngine::CGlobal<NRadEngine::CEnvironment,0>::instance,
                        *(NRadEngine::CSymbol64 *)((unsigned __int64)"QOlPrEfIxCLoggingData" & 0xFFFFFFFFFFFFFFF8ui64),
                        0i64);
            NRadEngine::CSysThread::SetTLS(TlsHandle, Global);
            return (NRadEngine::CLoggingData *)Global;
            }
        }
        return result;
        }
    };
}
#include "NRadEngine/include/CMemoryContext.h"

#include "NRadEngine/include/CAllocator.h"

namespace NRadEngine {
    class CMemoryContext {
        public:
        static NRadEngine::CAllocator *CurrentPtr() {
            // TODO: stubbed
        }

        static void SetCurrent(NRadEngine::CAllocator *allocator)
        {
            NRadEngine::CSysThread::SetTLS(NRadEngine::CThreadData<NRadEngine::CAllocator,0>::data.slot, allocator); // TODO: CSysThread, CThreadData, data
        }
    };
}
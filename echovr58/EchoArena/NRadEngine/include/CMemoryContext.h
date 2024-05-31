#include "NRadEngine/include/CAllocator.h"

namespace NRadEngine {
    class CMemoryContext {
        public:
        static NRadEngine::CAllocator *CurrentPtr();
    };
}
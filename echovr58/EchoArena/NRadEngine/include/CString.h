#include "NRadEngine/include/CMemParmsT.h"

namespace NRadEngine {
    class CString {
    public:
        unsigned __int64 iused;
        unsigned __int64 iallocated;
        unsigned __int64 expand;
        unsigned __int64 size;
        void *mem;
        CString(const char *begin, const char *end, unsigned int readonly, const NRadEngine::CMemParmsT<unsigned __int64> *dp);
    };
}
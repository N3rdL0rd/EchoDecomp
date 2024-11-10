#include "NRadEngine/include/CAllocator.h"

namespace NRadEngine {
    class CAllocator {
        // abstract class.
        public:
            const char *label;
            CAllocator *parent;
            CAllocator *child;
            CAllocator *sibling;
            CFlagsT<unsigned __int64,1> flags; // TODO: CFlagsT

            CAllocator() {
                label = 0LL;
                parent = 0LL;
                child = 0LL;
                sibling = 0LL;
                flags.flags[0] = 0LL;
                flags.flags[0] |= 1uLL;
            }

            void *Alloc(unsigned __int64 size);
            void *ReAlloc(const void *memory, unsigned __int64 size);
            void *Calloc(unsigned __int64 num, unsigned __int64 size);
            void *ReCalloc(const void *memory, unsigned __int64 num, unsigned __int64 size);
            void *AllocAligned(unsigned __int64 alignment, unsigned __int64 size);
            void Free(const void *memory);
            void FreeAligned(const void *memory);
            unsigned __int64 Used();
            unsigned __int64 Available();
            void Stats(NRadEngine::SAllocatorStats *stats); // TODO: SAllocatorStats
            void WriteAllocations();
            unsigned __int64 AllocationSize(const void * memory);
            unsigned int MemIsInAllocator(const void *, unsigned __int64); // TODO: symbol names for these?
            unsigned int IsElephantAllocator(); // TODO: should these two be bool return type?
    };
}
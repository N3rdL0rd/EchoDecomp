#include "NRadEngine/include/CString.h"

#include "NRadEngine/include/CMemory.h"

namespace NRadEngine
{
    class CString
    {
    public:
        unsigned __int64 iused;
        unsigned __int64 iallocated;
        unsigned __int64 expand;
        unsigned __int64 size;
        void *mem;

        CString(const char *begin, const char *end, unsigned int readonly, const NRadEngine::CMemParmsT<unsigned __int64> *dp)
        {
            unsigned __int64 v9;
            unsigned __int64 v12;

            NRadEngine::CTableA<char, 0>::CTableA<char, 0>(this, dp); // TODO: implement CTableA
            v9 = end - begin + 1;
            if (readonly)
            {
                NRadEngine::CTableA<unsigned char, 0>::SetExternalReadOnly((NRadEngine::CTableA<unsigned char, 0> *)this, begin, v9);
            }
            else
            {
                if (v9)
                {
                    iallocated = this->iallocated;
                    if (v9 + this->iused > iallocated)
                    {
                        expand = this->expand;
                        if (iallocated >= expand)
                            expand = this->iallocated;
                        v12 = v9;
                        if (expand >= v9)
                            v12 = expand;
                        NRadEngine::CMemBlockA<0>::Resize(this, v12 + iallocated, 1u); // TODO: implement CMemBlockA
                        this->iallocated += v12;
                    }
                    this->iused += v9;
                }
                NRadEngine::CMemory::Copy(this->mem, begin, v9);
                *((unsigned char *)this->mem + this->iused - 1) = 0;
            }
        }
    };
}
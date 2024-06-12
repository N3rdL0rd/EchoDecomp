#include "NRadEngine/include/CStringTable.h"

#include "NRadEngine/include/CMemory.h"
#include "NRadEngine/include/CSysString.h"

namespace NRadEngine
{
    class CStringTable
    {
        public:
        NRadEngine::CTable<char> chararray;

        unsigned __int64 __fastcall Grow(const char *string)
        {
            return this->InternalGrow(string, 0xFFFFFFFFFFFFFFFFui64);
        }

        unsigned __int64 __fastcall InternalGrow(
            const char *string,
            unsigned __int64 len)
        {
            unsigned __int64 v3;         // r15
            const char *v4;              // rdi
            void *v6;                    // r12
            unsigned __int64 iused;      // r13
            unsigned __int64 v8;         // rbp
            unsigned __int64 iallocated; // rcx
            unsigned __int64 expand;     // r14
            unsigned __int64 size;       // rax
            unsigned __int64 v12;        // rsi
            void *mem;                   // rdx
            char *v14;                   // rax
            char *v15;                   // rcx
            unsigned __int64 v16;        // rax
            unsigned __int64 v17;        // rcx
            unsigned __int64 v18;        // rsi
            unsigned __int64 v19;        // rax
            unsigned __int64 v20;        // rdi
            void *v21;                   // rdx
            unsigned __int64 result;     // rax
            char *v23;                   // rax
            char *v24;                   // rcx
            unsigned __int64 v25;        // rax
            unsigned __int64 v26;        // rdx
            unsigned __int64 v27;        // rcx
            _DWORD *v28;                 // rax
            unsigned __int64 v29;        // rcx
            unsigned __int64 v30;        // rsi
            unsigned __int64 v31;        // rax
            unsigned __int64 v32;        // rdi
            char *v33;                   // rax
            char *v34;                   // rcx
            unsigned __int64 v35;        // rax

            v3 = len;
            v4 = string;
            if (len == -1i64)
                v3 = NRadEngine::CSysString::Length(string, 0xFFFFFFFFFFFFFFFFui64);
            ++this->stringcount;
            v6 = 0i64;
            iused = this->chararray.iused;
            v8 = 0i64;
            if (!v3)
                goto LABEL_21;
            while (*v4)
            {
                iallocated = this->chararray.iallocated;
                if (this->chararray.iused >= iallocated)
                {
                    expand = this->chararray.iallocated;
                    size = this->chararray.size;
                    if (this->chararray.expand >= iallocated)
                        expand = this->chararray.expand;
                    v12 = iallocated + expand;
                    if (iallocated + expand != size)
                    {
                        if (size)
                            mem = this->chararray.mem;
                        else
                            mem = 0i64;
                        v14 = (char *)this->chararray.allocator->ReAlloc(this->chararray.allocator, mem, v12);
                        this->chararray.mem = v14;
                        v15 = v14;
                        if (v12)
                        {
                            v16 = this->chararray.size;
                            if (v12 > v16)
                                NRadEngine::CMemory::Fill(&v15[v16], 0, v12 - v16);
                        }
                        else
                        {
                            this->chararray.mem = (void *)-1i64;
                        }
                        this->chararray.size = v12;
                    }
                    this->chararray.iallocated += expand;
                }
                ++this->chararray.iused;
                if (v4)
                    *((_BYTE *)this->chararray.mem + this->chararray.iused - 1) = *v4;
                ++v8;
                ++v4;
                if (v8 >= v3)
                    goto LABEL_21;
            }
            if (!v8)
                return -1i64;
        LABEL_21:
            v17 = this->chararray.iallocated;
            if (this->chararray.iused >= v17)
            {
                v18 = this->chararray.iallocated;
                v19 = this->chararray.size;
                if (this->chararray.expand >= v17)
                    v18 = this->chararray.expand;
                v20 = v17 + v18;
                if (v17 + v18 != v19)
                {
                    if (v19)
                        v21 = this->chararray.mem;
                    else
                        v21 = 0i64;
                    v23 = (char *)this->chararray.allocator->ReAlloc(this->chararray.allocator, v21, v20);
                    this->chararray.mem = v23;
                    v24 = v23;
                    if (v20)
                    {
                        v25 = this->chararray.size;
                        if (v20 > v25)
                            NRadEngine::CMemory::Fill(&v24[v25], 0, v20 - v25);
                    }
                    else
                    {
                        this->chararray.mem = (void *)-1i64;
                    }
                    this->chararray.size = v20;
                }
                this->chararray.iallocated += v18;
            }
            ++this->chararray.iused;
            v26 = 0i64;
            *((_BYTE *)this->chararray.mem + this->chararray.iused - 1) = 0;
            v27 = this->indexmap.iused;
            if (v27)
            {
                while (this->freeindices)
                {
                    v28 = this->indexmap.mem;
                    if (v28[v26] == -1)
                    {
                        v28[v26] = iused;
                        result = v26;
                        --this->freeindices;
                        return result;
                    }
                    if (++v26 >= v27)
                        break;
                }
            }
            v29 = this->indexmap.iallocated;
            if (this->indexmap.iused >= v29)
            {
                v30 = this->indexmap.iallocated;
                v31 = this->indexmap.size;
                if (this->indexmap.expand >= v29)
                    v30 = this->indexmap.expand;
                v32 = 4 * (v29 + v30);
                if (v32 != v31)
                {
                    if (v31)
                        v6 = this->indexmap.mem;
                    v33 = (char *)this->indexmap.allocator->ReAlloc(this->indexmap.allocator, v6, v32);
                    this->indexmap.mem = v33;
                    v34 = v33;
                    if (v32)
                    {
                        v35 = this->indexmap.size;
                        if (v32 > v35)
                            NRadEngine::CMemory::Fill(&v34[v35], 0, v32 - v35);
                    }
                    else
                    {
                        this->indexmap.mem = (void *)-1i64;
                    }
                    this->indexmap.size = v32;
                }
                this->indexmap.iallocated += v30;
            }
            *((_DWORD *)this->indexmap.mem + this->indexmap.iused++) = iused;
            return this->indexmap.iused - 1;
        }
    };
}
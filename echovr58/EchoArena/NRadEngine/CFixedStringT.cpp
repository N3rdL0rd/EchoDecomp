#include "NRadEngine/include/CFixedStringT.h"

namespace NRadEngine
{
    template <int N>
    class CFixedStringT
    {
    public:
        char data[N];
        // TODO: investigate this function and why it's a template - also, the implementation is most likely incorrect, more decompiled examples needed
        template <int M>
        NRadEngine::CFixedStringT<N> *Append<M>(
            const NRadEngine::CFixedStringT<N> *this,
            const NRadEngine::CFixedStringT<M> *other)
        {
            unsigned __int64 otherLength;
            signed __int64 thisLength;
            unsigned __int64 remainingSpace;
            char *destination;
            unsigned __int64 newLength;

            otherLength = NRadEngine::CSysString::Length(other->data, 0x200ui64);
            thisLength = NRadEngine::CSysString::Length(this->data, 0x200ui64);
            remainingSpace = M - thisLength;
            destination = &this->data[thisLength];

            if (remainingSpace < otherLength)
                otherLength = remainingSpace;

            NRadEngine::CMemory::Move(&this->data[thisLength], other, otherLength);

            if (remainingSpace > otherLength)
                destination[otherLength] = 0;

            this->data[M - 1] = 0;

            newLength = NRadEngine::CSysString::Length(this->data, 0x200ui64) + 1;

            if (newLength < 0x200)
                memset(&this->data[newLength], 0, M - newLength);

            return this;
        }
    };
}
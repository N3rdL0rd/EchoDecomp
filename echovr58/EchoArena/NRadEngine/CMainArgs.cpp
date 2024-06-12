#include "NRadEngine/include/CMainArgs.h"

#include <vcruntime_string.h>
#include <cstdint>
#include "NRadEngine/include/CMemParmsT.h"
#include "NRadEngine/include/CMemoryContext.h"
#include "NRadEngine/include/CString.h"
#include "NRadEngine/include/CStringTable.h"
#include "NRadEngine/include/CMemory.h"
#include "NRadEngine/include/CSysString.h"
#include "NRadEngine/include/CSymbol64.h"
#include "NRadEngine/include/CMap.h"

namespace NRadEngine
{
    class CMainArgs
    {
        public:
        NRadEngine::CMap<NRadEngine::CSymbol64, unsigned __int64> symbolmap;
        void __fastcall Set(const char *commandLine)
        {
            const char *currentChar;
            char charIter;
            char nextChar;
            unsigned int isSpecialChar;
            const char *argStart;
            char delimiter;
            char nextCharInLoop;
            unsigned __int64 usedSymbols;
            char lambdaVar;

            if (commandLine)
            {
                currentChar = commandLine;
                while (*currentChar)
                {
                    for (charIter = *currentChar; charIter > 0; charIter = *++currentChar)
                    {
                        if (charIter > 32) // charIter > ' '
                            break;
                    }
                    nextChar = *currentChar;
                    if (!*currentChar)
                        break;
                    isSpecialChar = 0;
                    argStart = currentChar;
                    if ((nextChar == 45 || nextChar == -106 || nextChar == 43) && (unsigned __int8)(currentChar[1] - 48) > 9u) // nextChar == '-' || nextChar == 'Ê' || nextChar == '+'
                        isSpecialChar = 1;
                    delimiter = 0;
                    if (nextChar == 34 || nextChar == 91) // nextChar == '"' || nextChar == '['
                    {
                        nextCharInLoop = currentChar[1];
                        delimiter = 93;     // delimiter = ']'
                        if (nextChar == 34) // nextChar == '"'
                            delimiter = 34; // delimiter = '"'
                        for (argStart = ++currentChar; nextCharInLoop != delimiter; nextCharInLoop = *++currentChar)
                        {
                            if (!nextCharInLoop)
                                break;
                        }
                    }
                    else
                    {
                        for (; nextChar != 32; nextChar = *++currentChar) // nextChar != ' '
                        {
                            if (!nextChar)
                                break;
                        }
                    }
                    this->Append(argStart, currentChar - argStart, isSpecialChar);
                    if (delimiter && *currentChar == delimiter)
                        ++currentChar;
                }
                // TODO: whatever the hell this is
                if ((this->symbolmap.status.flags[0] & 1) != 0)
                {
                    usedSymbols = this->symbolmap.usedSymbols;
                    if (usedSymbols)
                        NRadEngine::Sort<_lambda_a190b07859813b90ca5300dfe65fb5dd_, NRadEngine::CSimpleKey<NRadEngine::CSymbol64, NRadEngine::CSymbol64>, NRadEngine::CSimpleKey<NRadEngine::CSymbol64, NRadEngine::CSymbol64> *, _lambda_a705d3f9cf8f747a6c63bbef182e99eb_, 512>(
                            (NRadEngine::CSimpleKey<void(__cdecl *)(NRadEngine::CSerializer *, NRadEngine::CErrorDb *, int &), NRadEngine::CSymbol64> *)this->symbolmap.mem,
                            usedSymbols,
                            (const NRadEngine::Sort::__l2::<lambda_2316775773a712a82392bfd62825745d> *)&lambdaVar,
                            (const NRadEngine::Sort::__l2::<lambda_407386be78b4ac6e363779667f9892a4> *)&lambdaVar);
                    this->symbolmap.status.flags[0] &= ~1u;
                }
            }
        }

        void __fastcall Append(const char *inputStr, unsigned __int64 length, unsigned int isArg)
        {
            unsigned __int64 remainingLength; // rsi
            const char *currentChar; // rbx
            unsigned __int64 copyLength; // rdi
            unsigned __int64 straLength; // rax
            unsigned __int64 argVectorIndex; // rbp
            char currentCharValue; // cl
            __int64 symbolValue; // rax
            const char *_hostname; // rcx
            __int64 calculatedSymbolValue; // rdi
            unsigned __int64 allocatedSymbols; // rcx
            unsigned __int64 expandSymbols; // rbx
            __int64 *symbolMapEntry; // r8
            NRadEngine::CMemParmsT<unsigned __int64> memParams; // [rsp+30h] [rbp-878h] BYREF
            NRadEngine::CString processedString; // TODO: constructor
            __int64 v20; // [rsp+80h] [rbp-828h]
            char stra[2048]; // [rsp+90h] [rbp-818h] BYREF

            v20 = -2i64;
            remainingLength = length;
            currentChar = inputStr;
            copyLength = length;
            if (length > 0x800)
                copyLength = 2048i64;
            NRadEngine::CMemory::Move(stra, inputStr, copyLength);
            if (copyLength < 0x800)
                stra[copyLength] = 0;
            stra[2047] = 0;
            straLength = NRadEngine::CSysString::Length(stra, 0x800ui64) + 1;
            if (straLength < 0x800)
                memset(&stra[straLength], 0, 2048 - straLength);
            argVectorIndex = NRadEngine::CStringTable::Grow(&this->argvector, stra); // TODO: decompile
            if (isArg)
            {
                while (1)
                {
                    currentCharValue = *currentChar;
                    if (*currentChar != 45 && currentCharValue != -106 && currentCharValue != 43)
                        break;
                    if (!currentCharValue)
                        break;
                    ++currentChar;
                    --remainingLength;
                }
                memParams.prealloc = 0i64;
                memParams.expandf = 32i64;
                memParams.allocator = NRadEngine::CMemoryContext::CurrentPtr();
                NRadEngine::CString::CString(&processedString, currentChar, &currentChar[remainingLength], 0, &memParams); // TODO: constructor matching arguments
                _hostname = hostname; // TODO: undefined reference to hostname
                if (*(uint64_t *)(symbolValue + 40))
                    _hostname = *(const char **)symbolValue;
                calculatedSymbolValue = NRadEngine::CSymbol64::CalculateSymbolValue( // TODO: decompile
                    _hostname,
                    NRadEngine::kEmptySymbol_0.value, // TODO: implement kEmptySymbol_0
                    0,
                    0xFFFFFFFFFFFFFFFFui64,
                    1u);
                if ((processedString.flags.flags[0] & 3) != 0)
                {
                    processedString.mem = 0i64;
                    processedString.size = 0i64;
                }
                // TODO (below): add neccesary attributes to NRadEngine::CMap and NRadEngine::CSymbol64, as well as CString
                if (processedString.size && processedString.mem)
                {
                    ((void(__fastcall *)(NRadEngine::CAllocator *))processedString.allocator->Free)(processedString.allocator);
                    processedString.mem = 0i64;
                    processedString.size = 0i64;
                }
                allocatedSymbols = this->symbolmap.iallocated;
                if (this->symbolmap.iused >= allocatedSymbols)
                {
                    expandSymbols = this->symbolmap.iallocated;
                    if (this->symbolmap.expand >= allocatedSymbols)
                        expandSymbols = this->symbolmap.expand;
                    NRadEngine::CMemBlockA<0>::Resize(&this->symbolmap, 16 * (allocatedSymbols + expandSymbols), 1u);
                    this->symbolmap.iallocated += expandSymbols;
                }
                ++this->symbolmap.iused;
                symbolMapEntry = (__int64 *)((char *)this->symbolmap.mem + 16 * this->symbolmap.iused - 16);
                *symbolMapEntry = calculatedSymbolValue;
                symbolMapEntry[1] = argVectorIndex;
                this->symbolmap.status.flags[0] |= 1u;
            }
        }    };
}
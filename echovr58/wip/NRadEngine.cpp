#include <vcruntime_string.h>
#include <intrin.h>
#include "NRadEngine/include/CMemory.h"
#include "NRadGame/include/CR14Game.h"
#include "NRadEngine/include/CRT0.h"
#include "NRadEngine/include/CSysWindow.h"

namespace NRadEngine {
    __int64 QueryCPUExtensions() {
        int cpuInfo1;
        int cpuInfo2;
        unsigned int cpuFeature;
        int cpuFeature1;
        char cpuInfo3;
        int cpuFeature2;
        int cpuFeature3;
        unsigned int finalFeature;
    
        // 1. Initial CPUID Check
        _RAX = 0i64;
        __asm { cpuid }
        if ( (int)_RAX < 1 )
            return 0i64;
    
        // 2. Checking for SSE Support
        _RAX = 1i64;
        __asm { cpuid }
        cpuInfo1 = _RDX;
        cpuInfo2 = _RCX;
        cpuFeature = ((unsigned int)_RDX >> 25) & 1;
        cpuFeature1 = cpuFeature | 2;
        if ( (cpuInfo1 & 0x4000000) == 0 )
            cpuFeature1 = cpuFeature;
    
        // 3. Checking for SSE2 Support
        cpuInfo3 = _RCX;
        cpuFeature2 = cpuFeature1 | 4;
        if ( (cpuInfo3 & 1) == 0 )
            cpuFeature2 = cpuFeature1;
    
        // 4. Checking for SSE3 Support
        cpuFeature3 = cpuFeature2 | 8;
        if ( (cpuInfo2 & 0x80000) == 0 )
            cpuFeature3 = cpuFeature2;
    
        // 5. Checking for SSSE3 Support
        finalFeature = cpuFeature3 | 0x10;
        if ( (cpuInfo2 & 0x100000) == 0 )
            finalFeature = cpuFeature3;
    
        // 6. Checking for SSE4.1 Support and OS Support for XSAVE and XRSTOR
        if ( (cpuInfo2 & 0x8000000) != 0 && (cpuInfo2 & 0x10000000) != 0 )
            __asm { xgetbv }
    
        return finalFeature; // Return bitmasked version - basically just "does it work on this CPU?"
    }
}
#include <Windows.h>
#include "NRadEngine/NWriteLog/include/NWriteLog.h"
#include "include/ints.h"
#include "NRadEngine/include/globals.h"

namespace NRadEngine {
    class CSysWindow {
    public:
        static void AbsoluteWindowExtents(int *windowHandle, NRadEngine::CQuad *windowExtents);
        static int *Create(const char *windowName, const NRadEngine::CQuad *windowExtents, unsigned int isHidden);
        static void Destroy(int *handle);
        static bool ExternalProcessWindowHasFocus(int *extwinhandle);
        LONG_PTR GetAltEnterStatus(int *handle);
        static __int64 GetEscapePressed(int *handle);
        static bool IsActive(int *handle);
        void MinimizeWindow(int *handle);
        static bool ProcessWindowHasFocus();
        static void SetClientAreaSize(int *handle, unsigned int w, unsigned int h);
        static void ShowMessageBox(int *handle, const char *msg, const char *caption);
        static void ShowSystemCursor(unsigned int show);
        static int UpdateWindow(int *handle);
        static void WindowExtents(int *handle, NRadEngine::CQuad *extents);
    };
}
#include "NRadEngine/include/CSysWindow.h"

#include <Windows.h>
#include <emmintrin.h>
#include "NRadEngine/NWriteLog/include/NWriteLog.h"
#include "include/ints.h"
#include "NRadEngine/include/globals.h"

namespace NRadEngine
{
    class CSysWindow
    {
    public:
        static void AbsoluteWindowExtents(int *windowHandle, NRadEngine::CQuad *windowExtents) // TODO: NRadEngine::CQuad
        {
            tagRECT windowRect; // [rsp+20h] [rbp-18h] BYREF

            *(_QWORD *)&windowRect.left = 0i64;
            *(_QWORD *)&windowRect.right = 0i64;

            GetWindowRect((HWND)windowHandle, &windowRect);

            *(__m128d *)windowExtents = *__mm_unpacklo_pd( // TODO: decipher
                (__m128d)_mm_unpacklo_ps(
                    (__m128)COERCE_UNSIGNED_INT((float)windowRect.left),
                    (__m128)COERCE_UNSIGNED_INT((float)windowRect.top)),
                (__m128d)_mm_unpacklo_ps(
                    (__m128)COERCE_UNSIGNED_INT((float)windowRect.right),
                    (__m128)COERCE_UNSIGNED_INT((float)windowRect.bottom)));
        }
        static int *Create(const char *windowName, const NRadEngine::CQuad *windowExtents, unsigned int isHidden)
        {
            float windowHeight;
            DWORD windowStyle;
            float windowWidth;
            int windowX;
            int *result;
            HWND windowHandle;
            tagRECT windowRect;
            WNDCLASSEXA windowClass;
            NRadEngine::C2Vector topLeft; // TODO: NRadEngine::C2Vector

            windowClass.cbSize = 80;
            windowClass.style = 3;
            windowClass.lpfnWndProc = NRadEngine::WindowProc; // TODO: WindowProc
            windowClass.lpszClassName = "WindowsClass";
            windowClass.hInstance = GetModuleHandleA(0i64);
            windowClass.hIcon = 0i64;
            windowClass.hIconSm = 0i64;
            *(_QWORD *)&windowClass.cbClsExtra = 0i64; // TODO: why is this not found?
            *(_OWORD *)&windowClass.hbrBackground = 0i64;
            windowClass.hCursor = LoadCursorA(0i64, (LPCSTR)0x7F00);
            RegisterClassExA(&windowClass);

            windowHeight = windowExtents->h.y - windowExtents->l.y;
            topLeft = windowExtents->l;
            windowStyle = 282001408;
            windowWidth = (float)(windowExtents->h.x - windowExtents->l.x) + COERCE_FLOAT(*(_QWORD *)&windowExtents->l); // TODO: decipher COERCE_* macros
            windowX = (int)COERCE_FLOAT(*(_QWORD *)&windowExtents->l);

            if (isHidden)
                windowStyle = 13565952;

            windowRect.left = (int)topLeft.x;
            windowRect.top = (int)topLeft.y;
            windowRect.right = (int)windowWidth;
            windowRect.bottom = (int)(float)(windowHeight + topLeft.y);
            AdjustWindowRectEx(&windowRect, windowStyle, 0, 0);

            result = (int *)CreateWindowExA(
                0,
                "WindowsClass",
                windowName,
                windowStyle,
                windowX,
                (int)topLeft.y,
                windowRect.right - windowRect.left,
                windowRect.bottom - windowRect.top,
                0i64,
                0i64,
                windowClass.hInstance,
                0i64);

            windowHandle = (HWND)result;
            if (result)
            {
                if (!isHidden)
                    ShowWindow((HWND)result, 1);
                UpdateWindow(windowHandle);
                return (int *)windowHandle;
            }
            return result;
        }
        static void Destroy(int *handle)
        {
            HMODULE ModuleHandleA;
            DestroyWindow((HWND)handle);
            ModuleHandleA = GetModuleHandleA(0i64);
            UnregisterClassA("WindowsClass", ModuleHandleA);
        }
        static bool ExternalProcessWindowHasFocus(int *extwinhandle)
        {
            DWORD WindowThreadProcessId;
            tagGUITHREADINFO pgui;
            WindowThreadProcessId = GetWindowThreadProcessId((HWND)extwinhandle, 0i64);
            pgui.cbSize = 72;
            GetGUIThreadInfo(WindowThreadProcessId, &pgui);
            return pgui.hwndFocus == (HWND__ *)extwinhandle;
        }
        LONG_PTR GetAltEnterStatus(int *handle)
        {
            return GetWindowLongPtrA((HWND)handle, -21) & 1;
        }
        static __int64 GetEscapePressed(int *handle)
        {
            return ((unsigned int)GetWindowLongPtrA((HWND)handle, -21) >> 1) & 1;
        }
        static bool IsActive(int *handle)
        {
            return handle == (int *)GetActiveWindow();
        }
        void MinimizeWindow(int *handle)
        {
            ShowWindow((HWND)handle, 7);
        }
        static bool ProcessWindowHasFocus()
        {
            DWORD CurrentProcessId;
            HWND ForegroundWindow;
            unsigned int dwProcessId;

            CurrentProcessId = GetCurrentProcessId();
            ForegroundWindow = GetForegroundWindow();
            dwProcessId = 0;
            GetWindowThreadProcessId(ForegroundWindow, &dwProcessId); // TODO: argument of type "unsigned int *" is incompatible with parameter of type "LPDWORD" (aka "unsigned long *")
            return dwProcessId == CurrentProcessId;
        }
        static void SetClientAreaSize(int *handle, unsigned int w, unsigned int h)
        {
            LONG WindowLongA;
            LONG v7;
            tagRECT Rect;

            *(_QWORD *)&Rect.left = 0i64;
            *(_QWORD *)&Rect.right = 0i64;
            GetWindowRect((HWND)handle, &Rect);
            Rect.right = w + Rect.left;
            Rect.bottom = h + Rect.top;
            WindowLongA = GetWindowLongA((HWND)handle, -20);
            v7 = GetWindowLongA((HWND)handle, -16);
            AdjustWindowRectEx(&Rect, v7, 0, WindowLongA);
            SetWindowPos((HWND)handle, (HWND)handle, 0, 0, Rect.right - Rect.left, Rect.bottom - Rect.top, 0x416u);
        }
        static void ShowMessageBox(int *handle, const char *msg, const char *caption)
        {
            NRadEngine::NWriteLog::WriteLog(
                NRadEngine::NWriteLog::eInfo,
                0i64,
                "=================================================================================");
            if (caption)
                NRadEngine::NWriteLog::WriteLog(NRadEngine::NWriteLog::eInfo, 0i64, "%s\n", caption);
            if (msg)
                NRadEngine::NWriteLog::WriteLog(NRadEngine::NWriteLog::eInfo, 0i64, "%s", msg);
            NRadEngine::NWriteLog::WriteLog(
                NRadEngine::NWriteLog::eInfo,
                0i64,
                "=================================================================================");
            MessageBoxA((HWND)handle, msg, caption, 0);
        }
        static void ShowSystemCursor(unsigned int show)
        {
            NRadEngine::gShowSystemCursor = show;
        }
        static int UpdateWindow(int *handle)
        {
            int result;      // eax
            unsigned int v3; // ebx
            tagMSG Msg;      // [rsp+30h] [rbp-38h] BYREF

            NRadEngine::gWindowEvents.flags[0] = 0; // TODO: gWindowEvents, and in turn, CFlagsT is not found
            result = IsWindow((HWND)handle);
            if (result)
            {
                memset(&Msg, 0, sizeof(Msg));
                while (PeekMessageA(&Msg, (HWND)handle, 0, 0, 1u))
                {
                    if (Msg.message == 275 && (int *)Msg.hwnd == handle)
                        NRadEngine::NWriteLog::WriteLog(NRadEngine::NWriteLog::eInfo, 0i64, "Timer generated for our window");
                    TranslateMessage(&Msg);
                    DispatchMessageA(&Msg);
                }
                SetThreadExecutionState(3u);
                v3 = (NRadEngine::gWindowEvents.flags[0] >> 4) & 1;
                SetWindowLongPtrA(Msg.hwnd, -21, NRadEngine::gWindowEvents.flags[0]);
                NRadEngine::gWindowEvents.flags[0] = 0;
                return v3 ^ 1;
            }
            return result;
        }
        static void WindowExtents(int *handle, NRadEngine::CQuad *extents)
        {
            tagRECT Rect; // [rsp+20h] [rbp-18h] BYREF

            *(_QWORD *)&Rect.left = 0i64;
            *(_QWORD *)&Rect.right = 0i64;
            GetClientRect((HWND)handle, &Rect);
            // TODO: decipher
            *(__m128d *)extents = _mm_unpacklo_pd(
                (__m128d)_mm_unpacklo_ps(
                    (__m128)COERCE_UNSIGNED_INT((float)Rect.left),
                    (__m128)COERCE_UNSIGNED_INT((float)Rect.top)),
                (__m128d)_mm_unpacklo_ps(
                    (__m128)COERCE_UNSIGNED_INT((float)Rect.right),
                    (__m128)COERCE_UNSIGNED_INT((float)Rect.bottom)));
        }
    };
}
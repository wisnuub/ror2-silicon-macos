/* Minimal kernel32/user32/ntdll compatibility for the game's few Windows P/Invokes.
 * RoR2.dll calls these for console attach, window flashing and timer resolution;
 * Rewired_Windows.dll is only used on Windows but is covered so stray calls fail soft.
 * Everything reports "not available" except where a real answer is cheap. */
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define EXPORT __attribute__((visibility("default")))
#define ZERO(name) EXPORT intptr_t name(void) { return 0; }

/* kernel32 */
EXPORT uint32_t GetCurrentProcessId(void) { return (uint32_t)getpid(); }
EXPORT uint32_t GetCurrentThreadId(void) { uint64_t t; pthread_threadid_np(NULL, &t); return (uint32_t)t; }
EXPORT intptr_t GetCurrentProcess(void) { return -1; }
EXPORT uint32_t GetLastError(void) { return 120; /* ERROR_CALL_NOT_IMPLEMENTED */ }
EXPORT void RtlZeroMemory(void* p, size_t n) { if (p) memset(p, 0, n); }
EXPORT int32_t IsWow64Process(intptr_t h, int32_t* wow) { if (wow) *wow = 0; return 1; }
ZERO(AllocConsole) ZERO(AttachConsole) ZERO(FreeConsole) ZERO(GetConsoleWindow)
ZERO(GetModuleHandle) ZERO(GetModuleHandleW) ZERO(GetModuleFileName) ZERO(GetModuleFileNameW)
ZERO(LoadLibrary) ZERO(LoadLibraryW) ZERO(GetProcAddress) ZERO(FreeLibrary)
ZERO(CancelIo) ZERO(CancelIoEx) ZERO(CancelSynchronousIo) ZERO(CloseHandle) ZERO(CreateEventW)
ZERO(DeviceIoControl) ZERO(FormatMessageW) ZERO(GetOverlappedResult) ZERO(GetProcessHeap)
ZERO(GlobalAlloc) ZERO(GlobalFree) ZERO(GlobalLock) ZERO(GlobalUnlock) ZERO(HeapAlloc) ZERO(HeapFree)
ZERO(PeekNamedPipe) ZERO(ReadFile) ZERO(ReadFileEx) ZERO(SetEvent) ZERO(SetNamedPipeHandleState)
ZERO(SleepEx) ZERO(WaitNamedPipe) ZERO(WriteFile) ZERO(WriteFileEx)
EXPORT intptr_t CreateFileW(void) { return -1; /* INVALID_HANDLE_VALUE */ }
EXPORT uint32_t WaitForSingleObject(void) { return 0xFFFFFFFF; /* WAIT_FAILED */ }
EXPORT uint32_t WaitForSingleObjectEx(void) { return 0xFFFFFFFF; }

/* ntdll: report the 1 ms resolution macOS timers already give. */
EXPORT int32_t NtQueryTimerResolution(uint32_t* minimum, uint32_t* maximum, uint32_t* current) {
    if (minimum) *minimum = 156250;
    if (maximum) *maximum = 5000;
    if (current) *current = 10000;
    return 0;
}
EXPORT int32_t NtSetTimerResolution(uint32_t desired, int32_t set, uint32_t* current) {
    if (current) *current = 10000;
    return 0;
}

/* user32 */
ZERO(EnumWindows) ZERO(FlashWindowEx) ZERO(GetActiveWindow) ZERO(GetWindowThreadProcessId) ZERO(PostMessage)
ZERO(CallNextHookEx) ZERO(CallWindowProc) ZERO(ClientToScreen) ZERO(CreateWindowEx) ZERO(CreateWindowExW)
ZERO(DefWindowProcW) ZERO(DestroyWindow) ZERO(DispatchMessage) ZERO(GetAsyncKeyState) ZERO(GetClientRect)
ZERO(GetCursorPos) ZERO(GetFocus) ZERO(GetForegroundWindow) ZERO(GetKeyState) ZERO(GetKeyboardLayout)
ZERO(GetKeyboardLayoutNameW) ZERO(GetKeyboardState) ZERO(GetMessage) ZERO(GetMessageW) ZERO(GetRawInputBuffer)
ZERO(GetRawInputData) ZERO(GetRawInputDeviceInfoW) ZERO(GetRawInputDeviceList) ZERO(GetRegisteredRawInputDevices)
ZERO(GetSystemMetrics) ZERO(GetWindowLong) ZERO(GetWindowLongPtr) ZERO(GetWindowLongPtrW) ZERO(GetWindowLongW)
ZERO(GetWindowRect) ZERO(IsWindow) ZERO(MapVirtualKeyExW) ZERO(MapVirtualKeyW) ZERO(OpenInputDesktop)
ZERO(PeekMessage) ZERO(PeekMessageW) ZERO(PostThreadMessage) ZERO(RegisterClassW) ZERO(RegisterDeviceNotification)
ZERO(RegisterDeviceNotificationW) ZERO(RegisterRawInputDevices) ZERO(SendMessage) ZERO(SendMessageTimeout)
ZERO(SetCursorPos) ZERO(SetParent) ZERO(SetWindowLong) ZERO(SetWindowLongPtr) ZERO(SetWindowLongPtrW)
ZERO(SetWindowLongW) ZERO(SetWindowsHookEx) ZERO(ShowWindow) ZERO(SwapMouseButton) ZERO(SystemParametersInfo)
ZERO(TranslateMessage) ZERO(UnhookWindowsHookEx) ZERO(UnregisterClassW) ZERO(UnregisterDeviceNotification)

/* xinput: no controller via XInput (Rewired/Unity use GameController on macOS). */
EXPORT uint32_t XInputGetState(void) { return 1167; /* ERROR_DEVICE_NOT_CONNECTED */ }
EXPORT uint32_t XInputSetState(void) { return 1167; }
EXPORT uint32_t XInputGetCapabilities(void) { return 1167; }
EXPORT uint32_t XInputGetBatteryInformation(void) { return 1167; }
EXPORT uint32_t XInputGetKeystroke(void) { return 1167; }
EXPORT uint32_t XInputGetDSoundAudioDeviceGuids(void) { return 1167; }
EXPORT void XInputEnable(void) {}

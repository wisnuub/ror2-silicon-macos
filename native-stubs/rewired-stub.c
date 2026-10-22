/*
 * Stub for Rewired_DirectInput.dll / libRewired_DirectInput.dylib
 * and Rewired_WindowsGamingInput.dll / libRewired_WindowsGamingInput.dylib
 *
 * These are Windows-only input backends. On Mac, Rewired uses
 * the HID/CoreHID backend from its managed Rewired_Core.dll.
 *
 * Build:
 *   cc -shared -o libRewired_DirectInput.dylib rewired-stub.c -arch arm64
 *   cp libRewired_DirectInput.dylib libRewired_WindowsGamingInput.dylib
 */

__attribute__((visibility("default")))
int RewiredDirectInputInit(void) { return 0; }

__attribute__((visibility("default")))
void RewiredDirectInputShutdown(void) {}

__attribute__((visibility("default")))
int RewiredWindowsGamingInputInit(void) { return 0; }

__attribute__((visibility("default")))
void RewiredWindowsGamingInputShutdown(void) {}

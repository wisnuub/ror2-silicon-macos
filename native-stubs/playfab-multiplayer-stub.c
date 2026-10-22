/*
 * Stub for PlayFabMultiplayerWin.dll / libPlayFabMultiplayer.dylib
 *
 * No-op exports so the Mono loader resolves the DLL without crash.
 * SteamTransportMod skips all PlayFab multiplayer code paths.
 *
 * Build: cc -shared -o libPlayFabMultiplayer.dylib playfab-multiplayer-stub.c -arch arm64
 */
#include <stdint.h>
#include <stddef.h>

typedef uint32_t HRESULT;
#define S_OK 0

__attribute__((visibility("default")))
HRESULT PFMultiplayerInitialize(const char* titleId, void** handle)
{
    if (handle) *handle = NULL;
    return S_OK;
}

__attribute__((visibility("default")))
HRESULT PFMultiplayerUninitialize(void* h) { return S_OK; }

__attribute__((visibility("default")))
HRESULT PFMultiplayerStartProcessingMatchmakingStateChanges(void* h, uint32_t* c, void** ch)
{
    if (c) *c = 0;
    if (ch) *ch = NULL;
    return S_OK;
}

__attribute__((visibility("default")))
HRESULT PFMultiplayerFinishProcessingMatchmakingStateChanges(void* h, uint32_t c, void* ch)
{
    return S_OK;
}

__attribute__((visibility("default")))
HRESULT PFMultiplayerStartProcessingLobbyStateChanges(void* h, uint32_t* c, void** ch)
{
    if (c) *c = 0;
    if (ch) *ch = NULL;
    return S_OK;
}

__attribute__((visibility("default")))
HRESULT PFMultiplayerFinishProcessingLobbyStateChanges(void* h, uint32_t c, void* ch)
{
    return S_OK;
}

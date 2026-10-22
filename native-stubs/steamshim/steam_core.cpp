// Core Steamworks entry points for the SDK 1.42 shim: forwarded to the real (current SDK)
// libsteam_api, loaded from libsteam_api_real.dylib next to this library.
#include "steam_api.h"
#include "steam_gameserver.h"
#include <dlfcn.h>
#include <string>
#include <cstdio>

#define S_SHIM extern "C" __attribute__((visibility("default")))

static void* RealLib()
{
    static void* handle = [] {
        Dl_info info;
        dladdr((void*)&RealLib, &info);
        std::string dir(info.dli_fname);
        dir = dir.substr(0, dir.rfind('/') + 1);
        void* h = dlopen((dir + "libsteam_api_real.dylib").c_str(), RTLD_NOW | RTLD_LOCAL);
        if (!h) fprintf(stderr, "[steamshim] cannot load libsteam_api_real.dylib: %s\n", dlerror());
        return h;
    }();
    return handle;
}

template <typename F> static F Real(const char* name)
{
    void* lib = RealLib();
    F f = lib ? (F)dlsym(lib, name) : nullptr;
    if (!f) fprintf(stderr, "[steamshim] missing %s in real libsteam_api\n", name);
    return f;
}

#define FORWARD(ret, name, params, args) \
    S_SHIM ret name params { static auto f = Real<ret(*) params>(#name); return f args; }

// Interface versions Facepunch.Steamworks (SDK 1.42) requests; the new init verifies Steam serves them.
static const char kInterfaceVersions[] =
    "SteamClient017\0SteamUser019\0SteamFriends015\0SteamUtils009\0SteamMatchMaking009\0"
    "SteamMatchMakingServers002\0SteamNetworking005\0SteamController006\0";

typedef char SteamErrMsg[1024];

S_SHIM bool SteamAPI_Init()
{
    static auto f = Real<int (*)(const char*, SteamErrMsg*)>("SteamInternal_SteamAPI_Init");
    if (!f) return false;
    SteamErrMsg err = {0};
    int result = f(kInterfaceVersions, &err);
    if (result != 0) fprintf(stderr, "[steamshim] SteamAPI_Init failed (%d): %s\n", result, err);
    return result == 0;
}

S_SHIM bool SteamInternal_GameServer_Init(uint32 unIP, uint16 usSteamPort, uint16 usGamePort, uint16 usQueryPort,
                                          EServerMode eServerMode, const char* pchVersionString)
{
    static auto f = Real<int (*)(uint32, uint16, uint16, EServerMode, const char*, const char*, SteamErrMsg*)>(
        "SteamInternal_GameServer_Init_V2");
    if (!f) return false;
    SteamErrMsg err = {0};
    int result = f(unIP, usGamePort, usQueryPort, eServerMode, pchVersionString,
                   "SteamGameServer012\0SteamGameServerStats001\0SteamUtils009\0SteamNetworking005\0", &err);
    if (result != 0) fprintf(stderr, "[steamshim] GameServer init failed (%d): %s\n", result, err);
    return result == 0;
}

FORWARD(void, SteamAPI_Shutdown, (), ())
FORWARD(bool, SteamAPI_RestartAppIfNecessary, (uint32 appId), (appId))
FORWARD(void, SteamAPI_RunCallbacks, (), ())
FORWARD(void, SteamAPI_RegisterCallback, (class CCallbackBase* cb, int id), (cb, id))
FORWARD(void, SteamAPI_UnregisterCallback, (class CCallbackBase* cb), (cb))
FORWARD(void, SteamAPI_RegisterCallResult, (class CCallbackBase* cb, SteamAPICall_t call), (cb, call))
FORWARD(void, SteamAPI_UnregisterCallResult, (class CCallbackBase* cb, SteamAPICall_t call), (cb, call))
FORWARD(HSteamPipe, SteamAPI_GetHSteamPipe, (), ())
FORWARD(HSteamUser, SteamAPI_GetHSteamUser, (), ())
FORWARD(void*, SteamInternal_CreateInterface, (const char* version), (version))
FORWARD(bool, SteamAPI_IsSteamRunning, (), ())
FORWARD(void, SteamGameServer_Shutdown, (), ())
FORWARD(void, SteamGameServer_RunCallbacks, (), ())
FORWARD(HSteamPipe, SteamGameServer_GetHSteamPipe, (), ())
FORWARD(HSteamUser, SteamGameServer_GetHSteamUser, (), ())

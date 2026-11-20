// Core Steamworks entry points for the SDK 1.42 shim: forwarded to the real (current SDK)
// libsteam_api, loaded from libsteam_api_real.dylib next to this library.
#include "steam_api.h"
#include "steam_gameserver.h"
#include <CoreFoundation/CoreFoundation.h>
#include <CoreServices/CoreServices.h>
#include <dlfcn.h>
#include <unistd.h>
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

// ---- Ownership check -----------------------------------------------------------------------------
// This Mac build is only for players who own Risk of Rain 2 on Steam. When the game starts Steam,
// ask the Steam app on this Mac (through Valve's own library, not this shim's exports) whether the
// logged-in account owns the game. Steam counts Family Sharing and offline mode as owned, the same
// as for the Windows game. If Steam isn't running, won't start the game, or the account doesn't
// own it, show a macOS alert and quit.
static const uint32 kRoR2AppId = 632360;

// Show a native alert (CoreFoundation, safe before and outside the Unity UI) and quit the game.
// With a store button, that button opens the game's page in the Steam app.
[[noreturn]] static void FailAndQuit(const char* title, const std::string& message, bool storeButton)
{
    fprintf(stderr, "[steamshim] %s: %s\n", title, message.c_str());
#ifdef STEAMSHIM_TEST
    _exit(storeButton ? 12 : 11);
#else
    CFStringRef t = CFStringCreateWithCString(nullptr, title, kCFStringEncodingUTF8);
    CFStringRef m = CFStringCreateWithCString(nullptr, message.c_str(), kCFStringEncodingUTF8);
    CFOptionFlags response = 0;
    CFUserNotificationDisplayAlert(0, kCFUserNotificationStopAlertLevel, nullptr, nullptr, nullptr, t, m,
                                   CFSTR("Quit"), storeButton ? CFSTR("Open in Steam") : nullptr, nullptr, &response);
    if (storeButton && (response & 0x3) == kCFUserNotificationAlternateResponse) {
        CFURLRef url = CFURLCreateWithBytes(nullptr, (const UInt8*)"steam://store/632360", 20, kCFStringEncodingUTF8, nullptr);
        if (url) { LSOpenCFURLRef(url, nullptr); CFRelease(url); }
    }
    _exit(1);
#endif
}

static void CheckOwnership(int initResult, const char* initError)
{
    static auto running = Real<bool (*)()>("SteamAPI_IsSteamRunning");
    if (initResult != 0) {
        if (initResult == 2 || (running && !running()))   // k_ESteamAPIInitResult_NoSteamClient
            FailAndQuit("Steam is not running",
                        "Risk of Rain 2 needs the Steam app.\n\nOpen Steam, log in with the account that owns "
                        "Risk of Rain 2, then open the game again.", false);
        FailAndQuit("Steam did not start Risk of Rain 2",
                    std::string("Steam is running, but it would not start Risk of Rain 2 for the account that is "
                                "logged in.\n\nLog in to Steam with the account that owns Risk of Rain 2, then open "
                                "the game again.\n\nSteam said: ") + (initError[0] ? initError : "no reason given"),
                    false);
    }
    static auto apps = Real<void* (*)()>("SteamAPI_SteamApps_v009");
    static auto subscribed = Real<bool (*)(void*, uint32)>("SteamAPI_ISteamApps_BIsSubscribedApp");
    static auto family = Real<bool (*)(void*)>("SteamAPI_ISteamApps_BIsSubscribedFromFamilySharing");
    void* steamApps = apps ? apps() : nullptr;
    if (!steamApps || !subscribed)
        FailAndQuit("Steam did not start Risk of Rain 2",
                    "The game could not ask Steam whether this account owns Risk of Rain 2.\n\nUpdate Steam, then "
                    "open the game again.", false);
    uint32 appId = kRoR2AppId;
#ifdef STEAMSHIM_TEST
    if (const char* t = getenv("STEAMSHIM_TEST_APPID")) appId = (uint32)strtoul(t, nullptr, 10);  // test builds only
#endif
    if (!subscribed(steamApps, appId))
        FailAndQuit("Risk of Rain 2 is not in your Steam library",
                    "The Steam account that is logged in does not own Risk of Rain 2.\n\nThis Mac version is free, "
                    "but only for players who own the game on Steam. Log in with the account that owns it, or get "
                    "the game on Steam, then open the game again.", true);
    fprintf(stderr, "[steamshim] Steam: this account owns Risk of Rain 2%s\n",
            family && family(steamApps) ? " (Family Sharing)" : "");
}

S_SHIM bool SteamAPI_Init()
{
    static auto f = Real<int (*)(const char*, SteamErrMsg*)>("SteamInternal_SteamAPI_Init");
    SteamErrMsg err = {0};
    int result = f ? f(kInterfaceVersions, &err) : 1;
    if (result != 0) fprintf(stderr, "[steamshim] SteamAPI_Init failed (%d): %s\n", result, err);
    CheckOwnership(result, err);
    return true;
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

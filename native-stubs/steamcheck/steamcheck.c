// steamcheck: confirm that Steam is running, a user is logged in, and that user owns Risk of Rain 2.
//
//   steamcheck <path to libsteam_api.dylib>
//
// Uses only Valve's Steamworks API, talking to the Steam app on this Mac. Exit codes:
//   0 owned, 2 Steam not running, 3 Steam API could not start, 4 not logged in, 5 not owned.
#include <dlfcn.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define ROR2_APPID 632360u
typedef char SteamErrMsg[1024];

int main(int argc, char** argv)
{
    if (argc < 2) { fprintf(stderr, "usage: steamcheck <libsteam_api.dylib>\n"); return 1; }
    void* lib = dlopen(argv[1], RTLD_NOW | RTLD_LOCAL);
    if (!lib) { fprintf(stderr, "steamcheck: cannot load %s: %s\n", argv[1], dlerror()); return 1; }
#define SYM(ret, name, args) ret (*name) args = (ret (*) args)dlsym(lib, #name); \
    if (!name) { fprintf(stderr, "steamcheck: missing %s\n", #name); return 1; }
    SYM(bool, SteamAPI_IsSteamRunning, (void))
    SYM(int, SteamAPI_InitFlat, (SteamErrMsg*))
    SYM(void, SteamAPI_Shutdown, (void))
    SYM(void*, SteamAPI_SteamApps_v009, (void))
    SYM(void*, SteamAPI_SteamUser_v023, (void))
    SYM(bool, SteamAPI_ISteamUser_BLoggedOn, (void*))
    SYM(bool, SteamAPI_ISteamApps_BIsSubscribedApp, (void*, uint32_t))
    SYM(bool, SteamAPI_ISteamApps_BIsSubscribedFromFamilySharing, (void*))

    if (!SteamAPI_IsSteamRunning()) {
        printf("Steam is not running. Open Steam and log in, then try again.\n");
        return 2;
    }
    // Check in the game's own name, the same way the game does when it starts
    setenv("SteamAppId", "632360", 1);
    setenv("SteamGameId", "632360", 1);
    SteamErrMsg err = {0};
    // Steam prints its own start-up lines (including the account's Steam ID); keep them out of logs
    fflush(stdout); int saved = dup(1), devnull = open("/dev/null", O_WRONLY); dup2(devnull, 1);
    int init = SteamAPI_InitFlat(&err);
    fflush(stdout); dup2(saved, 1); close(saved); close(devnull);
    if (init != 0) {
        printf("Steam is running, but it would not start Risk of Rain 2 for this account (%s).\n"
               "Make sure you are logged in to the Steam account that owns the game.\n", err);
        return 3;
    }
    int rc = 0;
    if (!SteamAPI_ISteamUser_BLoggedOn(SteamAPI_SteamUser_v023())) {
        printf("Steam is running but not logged in. Log in to Steam, then try again.\n");
        rc = 4;
    } else if (!SteamAPI_ISteamApps_BIsSubscribedApp(SteamAPI_SteamApps_v009(), ROR2_APPID)) {
        printf("This Steam account does not own Risk of Rain 2. You need to own the game to build it.\n");
        rc = 5;
    } else {
        bool family = SteamAPI_ISteamApps_BIsSubscribedFromFamilySharing(SteamAPI_SteamApps_v009());
        printf("OK: Steam is running and this account owns Risk of Rain 2%s.\n", family ? " (through Steam Family Sharing)" : "");
    }
    SteamAPI_Shutdown();
    return rc;
}

/* Stub for discord_game_sdk.dll / libdiscord_game_sdk.dylib */
#include <stdint.h>
#include <stddef.h>

typedef int32_t EDiscordResult;
#define DiscordResult_Ok 0
#define DiscordResult_NotRunning 29

__attribute__((visibility("default")))
EDiscordResult DiscordCreate(int version, void* params, void** core) {
    if (core) *core = NULL;
    return DiscordResult_NotRunning;
}

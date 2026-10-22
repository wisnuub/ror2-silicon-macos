/*
 * Stub for PartyWin32.dll / libParty.dylib
 *
 * Exports every symbol that the managed PiaNetworkTransport P/Invokes,
 * returning safe no-op values. With SteamTransportMod active, these
 * functions are never called. The stub exists only so the Mono loader
 * doesn't abort on missing native dependencies at assembly load time.
 *
 * Build: cc -shared -o libParty.dylib party-stub.c -arch arm64
 */
#include <stdint.h>
#include <stddef.h>

typedef uint32_t PartyError;
#define PARTY_SUCCESS 0

__attribute__((visibility("default")))
PartyError PartyInitialize(const void* titleId, void** handle)
{
    if (handle) *handle = NULL;
    return PARTY_SUCCESS;
}

__attribute__((visibility("default")))
PartyError PartyCleanup(void* handle) { return PARTY_SUCCESS; }

__attribute__((visibility("default")))
PartyError PartyStartProcessingStateChanges(void* h, uint32_t* count, void** changes)
{
    if (count) *count = 0;
    if (changes) *changes = NULL;
    return PARTY_SUCCESS;
}

__attribute__((visibility("default")))
PartyError PartyFinishProcessingStateChanges(void* h, uint32_t c, void* ch)
{
    return PARTY_SUCCESS;
}

__attribute__((visibility("default")))
PartyError PartyCreateLocalUser(void* h, const char* id, void** user)
{
    if (user) *user = NULL;
    return PARTY_SUCCESS;
}

__attribute__((visibility("default")))
PartyError PartyDestroyLocalUser(void* h, void* user) { return PARTY_SUCCESS; }

__attribute__((visibility("default")))
PartyError PartyCreateNewNetwork(void* h, void* user, void* cfg, uint32_t rc, void* regions, void* invite, void** net)
{
    if (net) *net = NULL;
    return PARTY_SUCCESS;
}

__attribute__((visibility("default")))
PartyError PartyConnectToNetwork(void* h, void* desc, void** net)
{
    if (net) *net = NULL;
    return PARTY_SUCCESS;
}

__attribute__((visibility("default")))
PartyError PartyLeaveNetwork(void* h, void* net) { return PARTY_SUCCESS; }

__attribute__((visibility("default")))
PartyError PartyCreateEndpoint(void* h, void* net, void* user, uint32_t ps, void* pd, void** ep)
{
    if (ep) *ep = NULL;
    return PARTY_SUCCESS;
}

__attribute__((visibility("default")))
PartyError PartyDestroyEndpoint(void* h, void* ep) { return PARTY_SUCCESS; }

__attribute__((visibility("default")))
PartyError PartySendMessage(void* h, void* ep, uint32_t tc, void* targets, uint32_t opt, void* cfg, uint32_t ds, const void* data)
{
    return PARTY_SUCCESS;
}

__attribute__((visibility("default")))
PartyError PartySetOption(void* h, void* obj, uint32_t opt, const void* val)
{
    return PARTY_SUCCESS;
}

__attribute__((visibility("default")))
PartyError PartyGetOption(void* h, void* obj, uint32_t opt, void* val)
{
    return PARTY_SUCCESS;
}

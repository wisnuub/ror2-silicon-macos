/* BCrypt stub for macOS.
 * .NET Core's System.IO uses Windows BCrypt for hashing. On macOS
 * the call sites throw EntryPointNotFoundException which is caught
 * by Mono. This stub silences the DLL-not-found fallback spam. */
#include <stdint.h>
#include <string.h>

typedef int32_t NTSTATUS;
#define STATUS_SUCCESS 0
#define STATUS_NOT_SUPPORTED ((NTSTATUS)0xC00000BB)

NTSTATUS BCryptOpenAlgorithmProvider(void **phAlgorithm, const void *pszAlgId,
                                     const void *pszImplementation, uint32_t dwFlags) {
    if (phAlgorithm) *phAlgorithm = (void*)1;
    return STATUS_SUCCESS;
}

NTSTATUS BCryptCloseAlgorithmProvider(void *hAlgorithm, uint32_t dwFlags) {
    return STATUS_SUCCESS;
}

NTSTATUS BCryptGenRandom(void *hAlgorithm, uint8_t *pbBuffer,
                         uint32_t cbBuffer, uint32_t dwFlags) {
    if (pbBuffer && cbBuffer > 0)
        memset(pbBuffer, 0x42, cbBuffer);
    return STATUS_SUCCESS;
}

NTSTATUS BCryptCreateHash(void *hAlgorithm, void **phHash,
                          uint8_t *pbHashObject, uint32_t cbHashObject,
                          const uint8_t *pbSecret, uint32_t cbSecret,
                          uint32_t dwFlags) {
    if (phHash) *phHash = (void*)2;
    return STATUS_SUCCESS;
}

NTSTATUS BCryptDestroyHash(void *hHash) { return STATUS_SUCCESS; }
NTSTATUS BCryptHashData(void *hHash, const uint8_t *pbInput,
                        uint32_t cbInput, uint32_t dwFlags) { return STATUS_SUCCESS; }
NTSTATUS BCryptFinishHash(void *hHash, uint8_t *pbOutput,
                          uint32_t cbOutput, uint32_t dwFlags) {
    if (pbOutput && cbOutput > 0)
        memset(pbOutput, 0, cbOutput);
    return STATUS_SUCCESS;
}

NTSTATUS BCryptGetProperty(void *hObject, const void *pszProperty,
                           uint8_t *pbOutput, uint32_t cbOutput,
                           uint32_t *pcbResult, uint32_t dwFlags) {
    if (pcbResult) *pcbResult = 0;
    return STATUS_NOT_SUPPORTED;
}

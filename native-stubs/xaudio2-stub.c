/* Stub for xaudio2_9redist.dll - not needed on Mac (Wwise handles audio) */
#include <stdint.h>
__attribute__((visibility("default")))
int32_t XAudio2Create(void** ppXAudio2, uint32_t Flags, uint32_t XAudio2Processor) {
    if (ppXAudio2) *ppXAudio2 = 0;
    return -1;
}

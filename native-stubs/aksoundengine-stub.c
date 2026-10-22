/*
 * Auto-generated stub for AkSoundEngine.dll / libAkSoundEngine.dylib
 *
 * Contains 1280 no-op exports matching the Wwise Unity integration P/Invokes.
 * Returns safe defaults (0/NULL/false) so the game loads without audio.
 * Replace with the real Wwise macOS SDK for actual audio support.
 *
 * Build: cc -shared -o libAkSoundEngine.dylib aksoundengine-stub.c -arch arm64
 */
#include <stdint.h>
#include <stddef.h>

typedef int32_t AKRESULT;
#define AK_Success 1
#define AK_NotInitialized 7

static int g_initialized = 0;

__attribute__((visibility("default")))
int CSharp_IsInitialized(void) {
    return g_initialized;
}

__attribute__((visibility("default")))
AKRESULT CSharp_RenderAudio__SWIG_0(void) {
    return AK_Success;
}

__attribute__((visibility("default")))
AKRESULT CSharp_RenderAudio__SWIG_1(int allowSyncRender) {
    return AK_Success;
}

__attribute__((visibility("default")))
AKRESULT CSharp_SetOfflineRenderingFrameTime(float time) { return AK_Success; }

__attribute__((visibility("default")))
AKRESULT CSharp_SetOfflineRendering(int offline) { return AK_Success; }

__attribute__((visibility("default")))
void CSharp_Suspend__SWIG_0(void) {}

__attribute__((visibility("default")))
void CSharp_Suspend__SWIG_1(int renderAnyway) {}

__attribute__((visibility("default")))
void CSharp_Suspend__SWIG_2(int renderAnyway, int fastResume) {}

__attribute__((visibility("default")))
AKRESULT CSharp_WakeupFromSuspend__SWIG_0(void) { return AK_Success; }

__attribute__((visibility("default")))
AKRESULT CSharp_WakeupFromSuspend__SWIG_1(uint32_t timeout) { return AK_Success; }

__attribute__((visibility("default")))
AKRESULT CSharp_AkCallbackSerializer_Init(void* info) { return AK_Success; }

__attribute__((visibility("default")))
void CSharp_AkCallbackSerializer_Term(void) {}

__attribute__((visibility("default")))
void CSharp_MonitorStreamMgrInit(void* settings) {}

__attribute__((visibility("default")))
void CSharp_MonitorStreamingDeviceInit(void* settings) {}

__attribute__((visibility("default")))
void CSharp_MonitorStreamMgrTerm(void) {}

__attribute__((visibility("default")))
AKRESULT CSharp_Init(void* settings) {
    g_initialized = 1;
    return AK_Success;
}

__attribute__((visibility("default")))
AKRESULT CSharp_InitSpatialAudio(void* settings) { return AK_Success; }

__attribute__((visibility("default")))
AKRESULT CSharp_InitCommunication(void* settings) { return AK_Success; }

__attribute__((visibility("default")))
void CSharp_Term(void) {
    g_initialized = 0;
}

__attribute__((visibility("default")))
void CSharp_GetDefaultInitSettings(void* settings) {}

__attribute__((visibility("default")))
void CSharp_GetDefaultPlatformInitSettings(void* settings) {}

/* Generic no-op stubs for remaining 1259 exports */

__attribute__((visibility("default")))
void* CSharp_AK_INVALID_SHARE_SET_ID_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AK_INVALID_PIPELINE_ID_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AK_INVALID_AUDIO_OBJECT_ID_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AK_SOUNDBANK_VERSION_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkJobType_Generic_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkJobType_AudioProcessing_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkJobType_SpatialAudio_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AK_NUM_JOB_TYPES_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkAudioSettings_uNumSamplesPerFrame_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkAudioSettings_uNumSamplesPerFrame_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkAudioSettings_uNumSamplesPerSecond_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkAudioSettings_uNumSamplesPerSecond_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_AkAudioSettings(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkAudioSettings(void* p) {}

__attribute__((visibility("default")))
void CSharp_AkDeviceDescription_idDevice_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkDeviceDescription_idDevice_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkDeviceDescription_deviceName_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkDeviceDescription_deviceName_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkDeviceDescription_deviceStateMask_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkDeviceDescription_deviceStateMask_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkDeviceDescription_isDefaultDevice_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkDeviceDescription_isDefaultDevice_get(void* self) { return NULL; }

__attribute__((visibility("default")))
int CSharp_AkDeviceDescription_Clear(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkDeviceDescription_GetSizeOf(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkDeviceDescription_Clone(void) { return 0; }

__attribute__((visibility("default")))
void* CSharp_new_AkDeviceDescription(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkDeviceDescription(void* p) {}

__attribute__((visibility("default")))
int CSharp_AkWorldTransform_Position(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkWorldTransform_OrientationFront(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkWorldTransform_OrientationTop(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkWorldTransform_Set__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkWorldTransform_Set__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkWorldTransform_SetPosition__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkWorldTransform_SetPosition__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkWorldTransform_SetOrientation__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkWorldTransform_SetOrientation__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
void* CSharp_new_AkWorldTransform(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkWorldTransform(void* p) {}

__attribute__((visibility("default")))
int CSharp_AkTransform_Position(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkTransform_OrientationFront(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkTransform_OrientationTop(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkTransform_Set__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkTransform_Set__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkTransform_SetPosition__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkTransform_SetPosition__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkTransform_SetOrientation__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkTransform_SetOrientation__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
void* CSharp_new_AkTransform(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkTransform(void* p) {}

__attribute__((visibility("default")))
int CSharp_ConvertAkVector64ToAkVector(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_ConvertAkWorldTransformToAkTransform(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_ConvertAkVectorToAkVector64(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_ConvertAkTransformToAkWorldTransform(void) { return 0; }

__attribute__((visibility("default")))
void CSharp_AkObstructionOcclusionValues_occlusion_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkObstructionOcclusionValues_occlusion_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkObstructionOcclusionValues_obstruction_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkObstructionOcclusionValues_obstruction_get(void* self) { return NULL; }

__attribute__((visibility("default")))
int CSharp_AkObstructionOcclusionValues_Clear(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkObstructionOcclusionValues_GetSizeOf(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkObstructionOcclusionValues_Clone(void) { return 0; }

__attribute__((visibility("default")))
void* CSharp_new_AkObstructionOcclusionValues(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkObstructionOcclusionValues(void* p) {}

__attribute__((visibility("default")))
void CSharp_AkChannelEmitter_position_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkChannelEmitter_position_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkChannelEmitter_uInputChannels_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkChannelEmitter_uInputChannels_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkChannelEmitter_padding_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkChannelEmitter_padding_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkChannelEmitter(void* p) {}

__attribute__((visibility("default")))
void CSharp_AkAuxSendValue_listenerID_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkAuxSendValue_listenerID_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkAuxSendValue_auxBusID_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkAuxSendValue_auxBusID_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkAuxSendValue_fControlValue_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkAuxSendValue_fControlValue_get(void* self) { return NULL; }

__attribute__((visibility("default")))
int CSharp_AkAuxSendValue_Set(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkAuxSendValue_IsSame(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkAuxSendValue_GetSizeOf(void) { return 0; }

__attribute__((visibility("default")))
void CSharp_delete_AkAuxSendValue(void* p) {}

__attribute__((visibility("default")))
void* CSharp_new_AkRamp__SWIG_0(void) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_AkRamp__SWIG_1(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkRamp_fPrev_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkRamp_fPrev_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkRamp_fNext_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkRamp_fNext_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkRamp(void* p) {}

__attribute__((visibility("default")))
void* CSharp_AK_INT_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AK_FLOAT_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AK_INTERLEAVED_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AK_NONINTERLEAVED_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AK_LE_NATIVE_BITSPERSAMPLE_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AK_LE_NATIVE_SAMPLETYPE_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AK_LE_NATIVE_INTERLEAVE_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkAudioFormat_uSampleRate_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkAudioFormat_uSampleRate_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkAudioFormat_channelConfig_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkAudioFormat_channelConfig_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkAudioFormat_uBitsPerSample_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkAudioFormat_uBitsPerSample_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkAudioFormat_uBlockAlign_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkAudioFormat_uBlockAlign_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkAudioFormat_uTypeID_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkAudioFormat_uTypeID_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkAudioFormat_uInterleaveID_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkAudioFormat_uInterleaveID_get(void* self) { return NULL; }

__attribute__((visibility("default")))
int CSharp_AkAudioFormat_GetNumChannels(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkAudioFormat_GetBitsPerSample(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkAudioFormat_GetBlockAlign(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkAudioFormat_GetTypeID(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkAudioFormat_GetInterleaveID(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkAudioFormat_SetAll(void) { return 0; }

__attribute__((visibility("default")))
void* CSharp_new_AkAudioFormat(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkAudioFormat(void* p) {}

__attribute__((visibility("default")))
int CSharp_IsBankCodecID(void) { return 0; }

__attribute__((visibility("default")))
void* CSharp_new_Ak3dData(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_Ak3dData_xform_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_Ak3dData_xform_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_Ak3dData_spread_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_Ak3dData_spread_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_Ak3dData_focus_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_Ak3dData_focus_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_Ak3dData_uEmitterChannelMask_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_Ak3dData_uEmitterChannelMask_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_Ak3dData(void* p) {}

__attribute__((visibility("default")))
void* CSharp_new_AkBehavioralPositioningData(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkBehavioralPositioningData_center_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkBehavioralPositioningData_center_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkBehavioralPositioningData_panLR_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkBehavioralPositioningData_panLR_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkBehavioralPositioningData_panBF_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkBehavioralPositioningData_panBF_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkBehavioralPositioningData_panDU_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkBehavioralPositioningData_panDU_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkBehavioralPositioningData_panSpatMix_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkBehavioralPositioningData_panSpatMix_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkBehavioralPositioningData_spatMode_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkBehavioralPositioningData_spatMode_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkBehavioralPositioningData_panType_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkBehavioralPositioningData_panType_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkBehavioralPositioningData_enableHeightSpread_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkBehavioralPositioningData_enableHeightSpread_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkBehavioralPositioningData(void* p) {}

__attribute__((visibility("default")))
void CSharp_AkPositioningData_threeD_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkPositioningData_threeD_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkPositioningData_behavioral_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkPositioningData_behavioral_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_AkPositioningData(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkPositioningData(void* p) {}

__attribute__((visibility("default")))
void CSharp_Ak3DAudioSinkCapabilities_channelConfig_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_Ak3DAudioSinkCapabilities_channelConfig_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_Ak3DAudioSinkCapabilities_uMaxSystemAudioObjects_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_Ak3DAudioSinkCapabilities_uMaxSystemAudioObjects_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_Ak3DAudioSinkCapabilities_uAvailableSystemAudioObjects_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_Ak3DAudioSinkCapabilities_uAvailableSystemAudioObjects_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_Ak3DAudioSinkCapabilities_bPassthrough_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_Ak3DAudioSinkCapabilities_bPassthrough_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_Ak3DAudioSinkCapabilities_bMultiChannelObjects_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_Ak3DAudioSinkCapabilities_bMultiChannelObjects_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_Ak3DAudioSinkCapabilities(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_Ak3DAudioSinkCapabilities(void* p) {}

__attribute__((visibility("default")))
void CSharp_AkIterator_pItem_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkIterator_pItem_get(void* self) { return NULL; }

__attribute__((visibility("default")))
int CSharp_AkIterator_NextIter(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkIterator_PrevIter(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkIterator_GetItem(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkIterator_IsEqualTo(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkIterator_IsDifferentFrom(void) { return 0; }

__attribute__((visibility("default")))
void* CSharp_new_AkIterator(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkIterator(void* p) {}

__attribute__((visibility("default")))
int CSharp_AkStdMovePolicy_IsTrivial(void) { return 0; }

__attribute__((visibility("default")))
void* CSharp_new_AkStdMovePolicy(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkStdMovePolicy(void* p) {}

__attribute__((visibility("default")))
int CSharp_AkTrivialStdMovePolicy_IsTrivial(void) { return 0; }

__attribute__((visibility("default")))
void* CSharp_new_AkTrivialStdMovePolicy(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkTrivialStdMovePolicy(void* p) {}

__attribute__((visibility("default")))
void* CSharp_new_AkPlaylistItem__SWIG_0(void) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_AkPlaylistItem__SWIG_1(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkPlaylistItem(void* p) {}

__attribute__((visibility("default")))
int CSharp_AkPlaylistItem_Assign(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkPlaylistItem_IsEqualTo(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkPlaylistItem_SetExternalSources(void) { return 0; }

__attribute__((visibility("default")))
void CSharp_AkPlaylistItem_audioNodeID_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkPlaylistItem_audioNodeID_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkPlaylistItem_msDelay_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkPlaylistItem_msDelay_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkPlaylistItem_pCustomInfo_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkPlaylistItem_pCustomInfo_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_AkPlaylistArray(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkPlaylistArray(void* p) {}

__attribute__((visibility("default")))
int CSharp_AkPlaylistArray_Begin(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkPlaylistArray_End(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkPlaylistArray_FindEx(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkPlaylistArray_Erase__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkPlaylistArray_Erase__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkPlaylistArray_EraseSwap__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkPlaylistArray_EraseSwap__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkPlaylistArray_IsGrowingAllowed(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkPlaylistArray_Reserve(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkPlaylistArray_ReserveExtra(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkPlaylistArray_Reserved(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkPlaylistArray_Term(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkPlaylistArray_Length(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkPlaylistArray_Data(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkPlaylistArray_IsEmpty(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkPlaylistArray_Exists(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkPlaylistArray_AddLast__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkPlaylistArray_AddLast__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkPlaylistArray_Last(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkPlaylistArray_RemoveLast(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkPlaylistArray_Remove(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkPlaylistArray_RemoveSwap(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkPlaylistArray_RemoveAll(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkPlaylistArray_ItemAtIndex(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkPlaylistArray_Insert__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkPlaylistArray_Insert__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkPlaylistArray_GrowArray__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkPlaylistArray_GrowArray__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkPlaylistArray_Resize(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkPlaylistArray_Transfer(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkPlaylistArray_Copy(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkPlaylist_Enqueue__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkPlaylist_Enqueue__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkPlaylist_Enqueue__SWIG_2(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkPlaylist_Enqueue__SWIG_3(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkPlaylist_Enqueue__SWIG_4(void) { return 0; }

__attribute__((visibility("default")))
void* CSharp_new_AkPlaylist(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkPlaylist(void* p) {}

__attribute__((visibility("default")))
int CSharp_DynamicSequenceOpen__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_DynamicSequenceOpen__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_DynamicSequenceOpen__SWIG_2(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_DynamicSequenceClose(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_DynamicSequencePlay__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_DynamicSequencePlay__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_DynamicSequencePlay__SWIG_2(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_DynamicSequencePause__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_DynamicSequencePause__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_DynamicSequencePause__SWIG_2(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_DynamicSequenceResume__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_DynamicSequenceResume__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_DynamicSequenceResume__SWIG_2(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_DynamicSequenceStop__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_DynamicSequenceStop__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_DynamicSequenceStop__SWIG_2(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_DynamicSequenceBreak(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_Seek__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_Seek__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_DynamicSequenceGetPauseTimes(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_DynamicSequenceLockPlaylist(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_DynamicSequenceUnlockPlaylist(void) { return 0; }

__attribute__((visibility("default")))
void* CSharp_new_AkOutputSettings__SWIG_0(void) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_AkOutputSettings__SWIG_1(void) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_AkOutputSettings__SWIG_2(void) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_AkOutputSettings__SWIG_3(void) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_AkOutputSettings__SWIG_4(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkOutputSettings_audioDeviceShareset_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkOutputSettings_audioDeviceShareset_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkOutputSettings_idDevice_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkOutputSettings_idDevice_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkOutputSettings_ePanningRule_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkOutputSettings_ePanningRule_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkOutputSettings_channelConfig_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkOutputSettings_channelConfig_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkOutputSettings(void* p) {}

__attribute__((visibility("default")))
void CSharp_AkInitSettings_uMaxNumPaths_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkInitSettings_uMaxNumPaths_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkInitSettings_uCommandQueueSize_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkInitSettings_uCommandQueueSize_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkInitSettings_bEnableGameSyncPreparation_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkInitSettings_bEnableGameSyncPreparation_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkInitSettings_uContinuousPlaybackLookAhead_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkInitSettings_uContinuousPlaybackLookAhead_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkInitSettings_uNumSamplesPerFrame_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkInitSettings_uNumSamplesPerFrame_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkInitSettings_uMonitorQueuePoolSize_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkInitSettings_uMonitorQueuePoolSize_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkInitSettings_uCpuMonitorQueueMaxSize_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkInitSettings_uCpuMonitorQueueMaxSize_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkInitSettings_settingsMainOutput_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkInitSettings_settingsMainOutput_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkInitSettings_uMaxHardwareTimeoutMs_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkInitSettings_uMaxHardwareTimeoutMs_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkInitSettings_bUseSoundBankMgrThread_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkInitSettings_bUseSoundBankMgrThread_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkInitSettings_bUseLEngineThread_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkInitSettings_bUseLEngineThread_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkInitSettings_szPluginDLLPath_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkInitSettings_szPluginDLLPath_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkInitSettings_eFloorPlane_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkInitSettings_eFloorPlane_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkInitSettings_fGameUnitsToMeters_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkInitSettings_fGameUnitsToMeters_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkInitSettings_uBankReadBufferSize_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkInitSettings_uBankReadBufferSize_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkInitSettings_fDebugOutOfRangeLimit_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkInitSettings_fDebugOutOfRangeLimit_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkInitSettings_bDebugOutOfRangeCheckEnabled_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkInitSettings_bDebugOutOfRangeCheckEnabled_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkInitSettings(void* p) {}

__attribute__((visibility("default")))
void CSharp_AkSourceSettings_sourceID_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkSourceSettings_sourceID_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkSourceSettings_pMediaMemory_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkSourceSettings_pMediaMemory_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkSourceSettings_uMediaSize_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkSourceSettings_uMediaSize_get(void* self) { return NULL; }

__attribute__((visibility("default")))
int CSharp_AkSourceSettings_Clear(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkSourceSettings_GetSizeOf(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkSourceSettings_Clone(void) { return 0; }

__attribute__((visibility("default")))
void* CSharp_new_AkSourceSettings(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkSourceSettings(void* p) {}

__attribute__((visibility("default")))
void* CSharp_GetAudioSettings(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_GetSpeakerConfiguration__SWIG_0(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_GetSpeakerConfiguration__SWIG_1(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_GetOutputDeviceConfiguration(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_GetPanningRule__SWIG_0(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_GetPanningRule__SWIG_1(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_SetPanningRule__SWIG_0(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetPanningRule__SWIG_1(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_GetSpeakerAngles__SWIG_0(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_GetSpeakerAngles__SWIG_1(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_SetSpeakerAngles__SWIG_0(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetSpeakerAngles__SWIG_1(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetVolumeThreshold(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetMaxNumVoicesLimit(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetJobMgrMaxActiveWorkers(void* self, void* val) {}

__attribute__((visibility("default")))
int CSharp_RegisterPluginDLL__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_RegisterPluginDLL__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_IsPluginRegistered(void) { return 0; }

__attribute__((visibility("default")))
void* CSharp_GetIDFromString__SWIG_0(void* self) { return NULL; }

__attribute__((visibility("default")))
int CSharp_PostEvent__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PostEvent__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PostEvent__SWIG_2(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PostEvent__SWIG_3(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PostEvent__SWIG_4(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PostEvent__SWIG_5(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PostEvent__SWIG_6(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PostEvent__SWIG_7(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_ExecuteActionOnEvent__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_ExecuteActionOnEvent__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_ExecuteActionOnEvent__SWIG_2(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_ExecuteActionOnEvent__SWIG_3(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_ExecuteActionOnEvent__SWIG_4(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_ExecuteActionOnEvent__SWIG_5(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_ExecuteActionOnEvent__SWIG_6(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_ExecuteActionOnEvent__SWIG_7(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_ExecuteActionOnEvent__SWIG_8(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_ExecuteActionOnEvent__SWIG_9(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PostMIDIOnEvent__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PostMIDIOnEvent__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PostMIDIOnEvent__SWIG_2(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PostMIDIOnEvent__SWIG_3(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_StopMIDIOnEvent__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_StopMIDIOnEvent__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_StopMIDIOnEvent__SWIG_2(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_StopMIDIOnEvent__SWIG_3(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PinEventInStreamCache__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PinEventInStreamCache__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_UnpinEventInStreamCache__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_UnpinEventInStreamCache__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
void* CSharp_GetBufferStatusForPinnedEvent__SWIG_0(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_GetBufferStatusForPinnedEvent__SWIG_1(void* self) { return NULL; }

__attribute__((visibility("default")))
int CSharp_SeekOnEvent__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_SeekOnEvent__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_SeekOnEvent__SWIG_2(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_SeekOnEvent__SWIG_3(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_SeekOnEvent__SWIG_4(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_SeekOnEvent__SWIG_5(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_SeekOnEvent__SWIG_9(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_SeekOnEvent__SWIG_10(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_SeekOnEvent__SWIG_11(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_SeekOnEvent__SWIG_12(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_SeekOnEvent__SWIG_13(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_SeekOnEvent__SWIG_14(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_CancelEventCallbackCookie(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_CancelEventCallbackGameObject(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_CancelEventCallback(void) { return 0; }

__attribute__((visibility("default")))
void* CSharp_GetSourcePlayPosition__SWIG_0(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_GetSourcePlayPosition__SWIG_1(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_GetSourceStreamBuffering(void* self) { return NULL; }

__attribute__((visibility("default")))
int CSharp_StopAll__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_StopAll__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_StopPlayingID__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_StopPlayingID__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_StopPlayingID__SWIG_2(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_ExecuteActionOnPlayingID__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_ExecuteActionOnPlayingID__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_ExecuteActionOnPlayingID__SWIG_2(void) { return 0; }

__attribute__((visibility("default")))
void CSharp_SetRandomSeed(void* self, void* val) {}

__attribute__((visibility("default")))
int CSharp_MuteBackgroundMusic(void) { return 0; }

__attribute__((visibility("default")))
void* CSharp_GetBackgroundMusicMute(void* self) { return NULL; }

__attribute__((visibility("default")))
int CSharp_SendPluginCustomGameData(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_UnregisterAllGameObj(void) { return 0; }

__attribute__((visibility("default")))
void CSharp_SetMultiplePositions__SWIG_0(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetMultiplePositions__SWIG_1(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetMultiplePositions__SWIG_2(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetMultiplePositions__SWIG_3(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetMultiplePositions__SWIG_4(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetMultiplePositions__SWIG_5(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetScalingFactor(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetDistanceProbe(void* self, void* val) {}

__attribute__((visibility("default")))
int CSharp_ClearBanks(void) { return 0; }

__attribute__((visibility("default")))
void CSharp_SetBankLoadIOSettings(void* self, void* val) {}

__attribute__((visibility("default")))
int CSharp_LoadBank__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_LoadBank__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_LoadBank__SWIG_4(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_LoadBank__SWIG_5(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_LoadBankMemoryView__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_LoadBankMemoryView__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_LoadBankMemoryCopy__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_LoadBankMemoryCopy__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_LoadBank__SWIG_6(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_LoadBank__SWIG_7(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_LoadBank__SWIG_10(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_LoadBank__SWIG_11(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_LoadBankMemoryView__SWIG_2(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_LoadBankMemoryView__SWIG_3(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_LoadBankMemoryCopy__SWIG_2(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_LoadBankMemoryCopy__SWIG_3(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_UnloadBank__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_UnloadBank__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_UnloadBank__SWIG_4(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_UnloadBank__SWIG_5(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_UnloadBank__SWIG_6(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_UnloadBank__SWIG_7(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_UnloadBank__SWIG_10(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_UnloadBank__SWIG_11(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_CancelBankCallbackCookie(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PrepareBank__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PrepareBank__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PrepareBank__SWIG_2(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PrepareBank__SWIG_6(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PrepareBank__SWIG_7(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PrepareBank__SWIG_8(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PrepareBank__SWIG_9(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PrepareBank__SWIG_10(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PrepareBank__SWIG_11(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PrepareBank__SWIG_15(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PrepareBank__SWIG_16(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PrepareBank__SWIG_17(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_ClearPreparedEvents(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PrepareEvent__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PrepareEvent__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PrepareEvent__SWIG_2(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PrepareEvent__SWIG_3(void) { return 0; }

__attribute__((visibility("default")))
void CSharp_SetMedia(void* self, void* val) {}

__attribute__((visibility("default")))
int CSharp_UnsetMedia(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PrepareGameSyncs__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PrepareGameSyncs__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PrepareGameSyncs__SWIG_2(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PrepareGameSyncs__SWIG_3(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AddListener(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_RemoveListener(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AddDefaultListener(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_RemoveDefaultListener(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_ResetListenersToDefault(void) { return 0; }

__attribute__((visibility("default")))
void CSharp_SetListenerSpatialization__SWIG_0(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetListenerSpatialization__SWIG_1(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetRTPCValue__SWIG_0(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetRTPCValue__SWIG_1(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetRTPCValue__SWIG_2(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetRTPCValue__SWIG_3(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetRTPCValue__SWIG_4(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetRTPCValue__SWIG_5(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetRTPCValue__SWIG_6(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetRTPCValue__SWIG_7(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetRTPCValue__SWIG_8(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetRTPCValue__SWIG_9(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetRTPCValueByPlayingID__SWIG_0(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetRTPCValueByPlayingID__SWIG_1(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetRTPCValueByPlayingID__SWIG_2(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetRTPCValueByPlayingID__SWIG_3(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetRTPCValueByPlayingID__SWIG_4(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetRTPCValueByPlayingID__SWIG_5(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetRTPCValueByPlayingID__SWIG_6(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetRTPCValueByPlayingID__SWIG_7(void* self, void* val) {}

__attribute__((visibility("default")))
int CSharp_ResetRTPCValue__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_ResetRTPCValue__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_ResetRTPCValue__SWIG_2(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_ResetRTPCValue__SWIG_3(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_ResetRTPCValue__SWIG_4(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_ResetRTPCValue__SWIG_5(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_ResetRTPCValue__SWIG_6(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_ResetRTPCValue__SWIG_7(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_ResetRTPCValue__SWIG_8(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_ResetRTPCValue__SWIG_9(void) { return 0; }

__attribute__((visibility("default")))
void CSharp_SetSwitch__SWIG_0(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetSwitch__SWIG_1(void* self, void* val) {}

__attribute__((visibility("default")))
int CSharp_PostTrigger__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PostTrigger__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
void CSharp_SetState__SWIG_0(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetState__SWIG_1(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetGameObjectAuxSendValues(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetGameObjectOutputBusVolume(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetActorMixerEffect(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetBusEffect__SWIG_0(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetBusEffect__SWIG_1(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetOutputDeviceEffect(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetMixer__SWIG_0(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetMixer__SWIG_1(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetBusConfig__SWIG_0(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetBusConfig__SWIG_1(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetObjectObstructionAndOcclusion(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetMultipleObstructionAndOcclusion(void* self, void* val) {}

__attribute__((visibility("default")))
int CSharp_StartOutputCapture(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_StopOutputCapture(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AddOutputCaptureMarker(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AddOutputCaptureBinaryMarker(void) { return 0; }

__attribute__((visibility("default")))
void* CSharp_GetSampleRate(void* self) { return NULL; }

__attribute__((visibility("default")))
int CSharp_StartProfilerCapture(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_StopProfilerCapture(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_RemoveOutput(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_ReplaceOutput__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_ReplaceOutput__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
void* CSharp_GetOutputID__SWIG_0(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_GetOutputID__SWIG_1(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_SetBusDevice__SWIG_0(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetBusDevice__SWIG_1(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_GetDeviceList__SWIG_0(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_GetDeviceList__SWIG_1(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_SetOutputVolume(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_GetDeviceSpatialAudioSupport(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_GetBufferTick(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_GetSampleTick(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkSegmentInfo_iCurrentPosition_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkSegmentInfo_iCurrentPosition_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkSegmentInfo_iPreEntryDuration_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkSegmentInfo_iPreEntryDuration_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkSegmentInfo_iActiveDuration_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkSegmentInfo_iActiveDuration_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkSegmentInfo_iPostExitDuration_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkSegmentInfo_iPostExitDuration_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkSegmentInfo_iRemainingLookAheadTime_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkSegmentInfo_iRemainingLookAheadTime_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkSegmentInfo_fBeatDuration_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkSegmentInfo_fBeatDuration_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkSegmentInfo_fBarDuration_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkSegmentInfo_fBarDuration_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkSegmentInfo_fGridDuration_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkSegmentInfo_fGridDuration_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkSegmentInfo_fGridOffset_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkSegmentInfo_fGridOffset_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_AkSegmentInfo(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkSegmentInfo(void* p) {}

__attribute__((visibility("default")))
void CSharp_AkResourceMonitorDataSummary_totalCPU_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkResourceMonitorDataSummary_totalCPU_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkResourceMonitorDataSummary_pluginCPU_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkResourceMonitorDataSummary_pluginCPU_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkResourceMonitorDataSummary_physicalVoices_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkResourceMonitorDataSummary_physicalVoices_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkResourceMonitorDataSummary_virtualVoices_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkResourceMonitorDataSummary_virtualVoices_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkResourceMonitorDataSummary_totalVoices_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkResourceMonitorDataSummary_totalVoices_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkResourceMonitorDataSummary_nbActiveEvents_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkResourceMonitorDataSummary_nbActiveEvents_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_AkResourceMonitorDataSummary(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkResourceMonitorDataSummary(void* p) {}

__attribute__((visibility("default")))
void* CSharp_AK_INVALID_MIDI_CHANNEL_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AK_INVALID_MIDI_NOTE_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkMIDIEvent_byChan_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkMIDIEvent_byChan_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkMIDIEvent_tGen_byParam1_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkMIDIEvent_tGen_byParam1_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkMIDIEvent_tGen_byParam2_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkMIDIEvent_tGen_byParam2_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_AkMIDIEvent_tGen(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkMIDIEvent_tGen(void* p) {}

__attribute__((visibility("default")))
void CSharp_AkMIDIEvent_tNoteOnOff_byNote_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkMIDIEvent_tNoteOnOff_byNote_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkMIDIEvent_tNoteOnOff_byVelocity_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkMIDIEvent_tNoteOnOff_byVelocity_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_AkMIDIEvent_tNoteOnOff(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkMIDIEvent_tNoteOnOff(void* p) {}

__attribute__((visibility("default")))
void CSharp_AkMIDIEvent_tCc_byCc_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkMIDIEvent_tCc_byCc_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkMIDIEvent_tCc_byValue_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkMIDIEvent_tCc_byValue_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_AkMIDIEvent_tCc(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkMIDIEvent_tCc(void* p) {}

__attribute__((visibility("default")))
void CSharp_AkMIDIEvent_tPitchBend_byValueLsb_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkMIDIEvent_tPitchBend_byValueLsb_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkMIDIEvent_tPitchBend_byValueMsb_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkMIDIEvent_tPitchBend_byValueMsb_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_AkMIDIEvent_tPitchBend(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkMIDIEvent_tPitchBend(void* p) {}

__attribute__((visibility("default")))
void CSharp_AkMIDIEvent_tNoteAftertouch_byNote_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkMIDIEvent_tNoteAftertouch_byNote_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkMIDIEvent_tNoteAftertouch_byValue_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkMIDIEvent_tNoteAftertouch_byValue_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_AkMIDIEvent_tNoteAftertouch(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkMIDIEvent_tNoteAftertouch(void* p) {}

__attribute__((visibility("default")))
void CSharp_AkMIDIEvent_tChanAftertouch_byValue_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkMIDIEvent_tChanAftertouch_byValue_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_AkMIDIEvent_tChanAftertouch(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkMIDIEvent_tChanAftertouch(void* p) {}

__attribute__((visibility("default")))
void CSharp_AkMIDIEvent_tProgramChange_byProgramNum_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkMIDIEvent_tProgramChange_byProgramNum_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_AkMIDIEvent_tProgramChange(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkMIDIEvent_tProgramChange(void* p) {}

__attribute__((visibility("default")))
void CSharp_AkMIDIEvent_tWwiseCmd_uCmd_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkMIDIEvent_tWwiseCmd_uCmd_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkMIDIEvent_tWwiseCmd_uArg_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkMIDIEvent_tWwiseCmd_uArg_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_AkMIDIEvent_tWwiseCmd(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkMIDIEvent_tWwiseCmd(void* p) {}

__attribute__((visibility("default")))
void CSharp_AkMIDIEvent_Gen_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkMIDIEvent_Gen_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkMIDIEvent_Cc_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkMIDIEvent_Cc_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkMIDIEvent_NoteOnOff_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkMIDIEvent_NoteOnOff_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkMIDIEvent_PitchBend_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkMIDIEvent_PitchBend_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkMIDIEvent_NoteAftertouch_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkMIDIEvent_NoteAftertouch_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkMIDIEvent_ChanAftertouch_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkMIDIEvent_ChanAftertouch_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkMIDIEvent_ProgramChange_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkMIDIEvent_ProgramChange_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkMIDIEvent_WwiseCmd_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkMIDIEvent_WwiseCmd_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkMIDIEvent_byType_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkMIDIEvent_byType_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkMIDIEvent_byOnOffNote_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkMIDIEvent_byOnOffNote_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkMIDIEvent_byVelocity_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkMIDIEvent_byVelocity_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkMIDIEvent_byCc_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkMIDIEvent_byCc_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkMIDIEvent_byCcValue_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkMIDIEvent_byCcValue_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkMIDIEvent_byValueLsb_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkMIDIEvent_byValueLsb_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkMIDIEvent_byValueMsb_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkMIDIEvent_byValueMsb_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkMIDIEvent_byAftertouchNote_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkMIDIEvent_byAftertouchNote_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkMIDIEvent_byNoteAftertouchValue_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkMIDIEvent_byNoteAftertouchValue_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkMIDIEvent_byChanAftertouchValue_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkMIDIEvent_byChanAftertouchValue_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkMIDIEvent_byProgramNum_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkMIDIEvent_byProgramNum_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkMIDIEvent_uCmd_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkMIDIEvent_uCmd_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkMIDIEvent_uArg_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkMIDIEvent_uArg_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_AkMIDIEvent(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkMIDIEvent(void* p) {}

__attribute__((visibility("default")))
void CSharp_AkMIDIPost_uOffset_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkMIDIPost_uOffset_get(void* self) { return NULL; }

__attribute__((visibility("default")))
int CSharp_AkMIDIPost_PostOnEvent__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkMIDIPost_PostOnEvent__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkMIDIPost_PostOnEvent__SWIG_2(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkMIDIPost_PostOnEvent__SWIG_3(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkMIDIPost_Clone(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkMIDIPost_GetSizeOf(void) { return 0; }

__attribute__((visibility("default")))
void* CSharp_new_AkMIDIPost(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkMIDIPost(void* p) {}

__attribute__((visibility("default")))
void CSharp_AkMusicSettings_fStreamingLookAheadRatio_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkMusicSettings_fStreamingLookAheadRatio_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkMusicSettings(void* p) {}

__attribute__((visibility("default")))
void* CSharp_GetPlayingSegmentInfo__SWIG_0(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_GetPlayingSegmentInfo__SWIG_1(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkSerializedCallbackHeader_pPackage_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkSerializedCallbackHeader_eType_get(void* self) { return NULL; }

__attribute__((visibility("default")))
int CSharp_AkSerializedCallbackHeader_GetData(void) { return 0; }

__attribute__((visibility("default")))
void* CSharp_AkSerializedCallbackHeader_pNext_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_AkSerializedCallbackHeader(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkSerializedCallbackHeader(void* p) {}

__attribute__((visibility("default")))
void* CSharp_AkCallbackInfo_pCookie_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkCallbackInfo_gameObjID_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_AkCallbackInfo(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkCallbackInfo(void* p) {}

__attribute__((visibility("default")))
void* CSharp_AkEventCallbackInfo_playingID_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkEventCallbackInfo_eventID_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_AkEventCallbackInfo(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkEventCallbackInfo(void* p) {}

__attribute__((visibility("default")))
void* CSharp_AkMIDIEventCallbackInfo_byChan_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkMIDIEventCallbackInfo_byParam1_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkMIDIEventCallbackInfo_byParam2_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkMIDIEventCallbackInfo_byType_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkMIDIEventCallbackInfo_byOnOffNote_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkMIDIEventCallbackInfo_byVelocity_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkMIDIEventCallbackInfo_byCc_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkMIDIEventCallbackInfo_byCcValue_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkMIDIEventCallbackInfo_byValueLsb_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkMIDIEventCallbackInfo_byValueMsb_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkMIDIEventCallbackInfo_byAftertouchNote_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkMIDIEventCallbackInfo_byNoteAftertouchValue_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkMIDIEventCallbackInfo_byChanAftertouchValue_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkMIDIEventCallbackInfo_byProgramNum_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_AkMIDIEventCallbackInfo(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkMIDIEventCallbackInfo(void* p) {}

__attribute__((visibility("default")))
void* CSharp_AkMarkerCallbackInfo_uIdentifier_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkMarkerCallbackInfo_uPosition_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkMarkerCallbackInfo_strLabel_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_AkMarkerCallbackInfo(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkMarkerCallbackInfo(void* p) {}

__attribute__((visibility("default")))
void* CSharp_AkDurationCallbackInfo_fDuration_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkDurationCallbackInfo_fEstimatedDuration_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkDurationCallbackInfo_audioNodeID_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkDurationCallbackInfo_mediaID_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkDurationCallbackInfo_bStreaming_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_AkDurationCallbackInfo(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkDurationCallbackInfo(void* p) {}

__attribute__((visibility("default")))
void* CSharp_AkDynamicSequenceItemCallbackInfo_playingID_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkDynamicSequenceItemCallbackInfo_audioNodeID_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkDynamicSequenceItemCallbackInfo_pCustomInfo_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_AkDynamicSequenceItemCallbackInfo(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkDynamicSequenceItemCallbackInfo(void* p) {}

__attribute__((visibility("default")))
void* CSharp_AkMusicSyncCallbackInfo_playingID_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkMusicSyncCallbackInfo_segmentInfo_iCurrentPosition_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkMusicSyncCallbackInfo_segmentInfo_iPreEntryDuration_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkMusicSyncCallbackInfo_segmentInfo_iActiveDuration_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkMusicSyncCallbackInfo_segmentInfo_iPostExitDuration_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkMusicSyncCallbackInfo_segmentInfo_iRemainingLookAheadTime_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkMusicSyncCallbackInfo_segmentInfo_fBeatDuration_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkMusicSyncCallbackInfo_segmentInfo_fBarDuration_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkMusicSyncCallbackInfo_segmentInfo_fGridDuration_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkMusicSyncCallbackInfo_segmentInfo_fGridOffset_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkMusicSyncCallbackInfo_musicSyncType_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkMusicSyncCallbackInfo_userCueName_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_AkMusicSyncCallbackInfo(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkMusicSyncCallbackInfo(void* p) {}

__attribute__((visibility("default")))
void* CSharp_AkMusicPlaylistCallbackInfo_playlistID_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkMusicPlaylistCallbackInfo_uNumPlaylistItems_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkMusicPlaylistCallbackInfo_uPlaylistSelection_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkMusicPlaylistCallbackInfo_uPlaylistItemDone_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_AkMusicPlaylistCallbackInfo(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkMusicPlaylistCallbackInfo(void* p) {}

__attribute__((visibility("default")))
void* CSharp_AkBankCallbackInfo_bankID_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkBankCallbackInfo_inMemoryBankPtr_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkBankCallbackInfo_loadResult_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_AkBankCallbackInfo(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkBankCallbackInfo(void* p) {}

__attribute__((visibility("default")))
void* CSharp_AkMonitoringCallbackInfo_errorCode_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkMonitoringCallbackInfo_errorLevel_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkMonitoringCallbackInfo_playingID_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkMonitoringCallbackInfo_gameObjID_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_AkMonitoringCallbackInfo_message_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_AkMonitoringCallbackInfo(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkMonitoringCallbackInfo(void* p) {}

__attribute__((visibility("default")))
void* CSharp_AkAudioInterruptionCallbackInfo_bEnterInterruption_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_AkAudioInterruptionCallbackInfo(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkAudioInterruptionCallbackInfo(void* p) {}

__attribute__((visibility("default")))
void* CSharp_AkAudioSourceChangeCallbackInfo_bOtherAudioPlaying_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_AkAudioSourceChangeCallbackInfo(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkAudioSourceChangeCallbackInfo(void* p) {}

__attribute__((visibility("default")))
int CSharp_AkCallbackSerializer_Lock(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkCallbackSerializer_Unlock(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkCallbackSerializer_SetLocalOutput(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkCallbackSerializer_AudioSourceChangeCallbackFunc(void) { return 0; }

__attribute__((visibility("default")))
void* CSharp_new_AkCallbackSerializer(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkCallbackSerializer(void* p) {}

__attribute__((visibility("default")))
void* CSharp_new_MsgContext__SWIG_0(void) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_MsgContext__SWIG_1(void) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_MsgContext__SWIG_2(void) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_MsgContext__SWIG_3(void) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_MsgContext__SWIG_4(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_MsgContext_in_playingID_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_MsgContext_in_playingID_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_MsgContext_in_gameObjID_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_MsgContext_in_gameObjID_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_MsgContext_in_soundID_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_MsgContext_in_soundID_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_MsgContext_in_bIsBus_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_MsgContext_in_bIsBus_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_MsgContext(void* p) {}

__attribute__((visibility("default")))
void* CSharp_new_MonitorErrorInfo__SWIG_0(void) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_MonitorErrorInfo__SWIG_1(void) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_MonitorErrorInfo__SWIG_2(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_MonitorErrorInfo_m_name_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_MonitorErrorInfo_m_name_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_MonitorErrorInfo_m_message_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_MonitorErrorInfo_m_message_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_MonitorErrorInfo(void* p) {}

__attribute__((visibility("default")))
int CSharp_PostCode__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PostCode__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PostCode__SWIG_2(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PostCode__SWIG_3(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PostCode__SWIG_4(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PostCodeVarArg(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PostString__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PostString__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PostString__SWIG_2(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PostString__SWIG_3(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PostString__SWIG_4(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_ResetTranslator(void) { return 0; }

__attribute__((visibility("default")))
void* CSharp_GetTimeStamp(void* self) { return NULL; }

__attribute__((visibility("default")))
int CSharp_MonitorStreamingDeviceDestroyed(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkMemCpy(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkMemMove(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkMemSet(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkGetDefaultHighPriorityThreadProperties(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_ResolveDialogueEvent__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_ResolveDialogueEvent__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
void* CSharp_GetDialogueEventCustomPropertyValue__SWIG_0(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_GetDialogueEventCustomPropertyValue__SWIG_1(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkPositioningInfo_fCenterPct_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkPositioningInfo_fCenterPct_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkPositioningInfo_pannerType_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkPositioningInfo_pannerType_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkPositioningInfo_e3dPositioningType_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkPositioningInfo_e3dPositioningType_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkPositioningInfo_bHoldEmitterPosAndOrient_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkPositioningInfo_bHoldEmitterPosAndOrient_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkPositioningInfo_e3DSpatializationMode_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkPositioningInfo_e3DSpatializationMode_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkPositioningInfo_bEnableAttenuation_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkPositioningInfo_bEnableAttenuation_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkPositioningInfo_bUseConeAttenuation_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkPositioningInfo_bUseConeAttenuation_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkPositioningInfo_fInnerAngle_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkPositioningInfo_fInnerAngle_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkPositioningInfo_fOuterAngle_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkPositioningInfo_fOuterAngle_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkPositioningInfo_fConeMaxAttenuation_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkPositioningInfo_fConeMaxAttenuation_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkPositioningInfo_LPFCone_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkPositioningInfo_LPFCone_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkPositioningInfo_HPFCone_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkPositioningInfo_HPFCone_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkPositioningInfo_fMaxDistance_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkPositioningInfo_fMaxDistance_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkPositioningInfo_fVolDryAtMaxDist_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkPositioningInfo_fVolDryAtMaxDist_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkPositioningInfo_fVolAuxGameDefAtMaxDist_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkPositioningInfo_fVolAuxGameDefAtMaxDist_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkPositioningInfo_fVolAuxUserDefAtMaxDist_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkPositioningInfo_fVolAuxUserDefAtMaxDist_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkPositioningInfo_LPFValueAtMaxDist_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkPositioningInfo_LPFValueAtMaxDist_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkPositioningInfo_HPFValueAtMaxDist_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkPositioningInfo_HPFValueAtMaxDist_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_AkPositioningInfo(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkPositioningInfo(void* p) {}

__attribute__((visibility("default")))
void CSharp_AkObjectInfo_objID_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkObjectInfo_objID_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkObjectInfo_parentID_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkObjectInfo_parentID_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkObjectInfo_iDepth_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkObjectInfo_iDepth_get(void* self) { return NULL; }

__attribute__((visibility("default")))
int CSharp_AkObjectInfo_Clear(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkObjectInfo_GetSizeOf(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkObjectInfo_Clone(void) { return 0; }

__attribute__((visibility("default")))
void* CSharp_new_AkObjectInfo(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkObjectInfo(void* p) {}

__attribute__((visibility("default")))
void* CSharp_GetPosition(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_GetListenerPosition(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_GetRTPCValue__SWIG_0(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_GetRTPCValue__SWIG_1(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_GetSwitch__SWIG_0(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_GetSwitch__SWIG_1(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_GetState__SWIG_0(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_GetState__SWIG_1(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_GetGameObjectAuxSendValues(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_GetGameObjectDryLevelValue(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_GetObjectObstructionAndOcclusion(void* self) { return NULL; }

__attribute__((visibility("default")))
int CSharp_QueryAudioObjectIDs__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_QueryAudioObjectIDs__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
void* CSharp_GetPositioningInfo(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_GetIsGameObjectActive(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_GetMaxRadius(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_GetEventIDFromPlayingID(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_GetGameObjectFromPlayingID(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_GetPlayingIDsFromGameObject(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_GetCustomPropertyValue__SWIG_0(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_GetCustomPropertyValue__SWIG_1(void* self) { return NULL; }

__attribute__((visibility("default")))
int CSharp_AK_SPEAKER_SETUP_FIX_LEFT_TO_CENTER(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AK_SPEAKER_SETUP_FIX_REAR_TO_SIDE(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AK_SPEAKER_SETUP_CONVERT_TO_SUPPORTED(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_ChannelMaskToNumChannels(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_ChannelMaskFromNumChannels(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_ChannelBitToIndex(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_HasSurroundChannels(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_HasStrictlyOnePairOfSurroundChannels(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_HasSideAndRearChannels(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_HasHeightChannels(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_BackToSideChannels(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_StdChannelIndexToDisplayIndex(void) { return 0; }

__attribute__((visibility("default")))
void CSharp_AkChannelConfig_uNumChannels_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkChannelConfig_uNumChannels_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkChannelConfig_eConfigType_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkChannelConfig_eConfigType_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkChannelConfig_uChannelMask_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkChannelConfig_uChannelMask_get(void* self) { return NULL; }

__attribute__((visibility("default")))
int CSharp_AkChannelConfig_Standard(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkChannelConfig_Anonymous(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkChannelConfig_Ambisonic(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkChannelConfig_Object(void) { return 0; }

__attribute__((visibility("default")))
void* CSharp_new_AkChannelConfig__SWIG_0(void) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_AkChannelConfig__SWIG_1(void) { return NULL; }

__attribute__((visibility("default")))
int CSharp_AkChannelConfig_Clear(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkChannelConfig_SetStandard(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkChannelConfig_SetStandardOrAnonymous(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkChannelConfig_SetAnonymous(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkChannelConfig_SetAmbisonic(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkChannelConfig_SetObject(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkChannelConfig_SetSameAsMainMix(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkChannelConfig_SetSameAsPassthrough(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkChannelConfig_IsValid(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkChannelConfig_Serialize(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkChannelConfig_Deserialize(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkChannelConfig_RemoveLFE(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkChannelConfig_RemoveCenter(void) { return 0; }

__attribute__((visibility("default")))
void CSharp_delete_AkChannelConfig(void* p) {}

__attribute__((visibility("default")))
void* CSharp_new_AkImageSourceParams__SWIG_0(void) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_AkImageSourceParams__SWIG_1(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkImageSourceParams_sourcePosition_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkImageSourceParams_sourcePosition_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkImageSourceParams_fDistanceScalingFactor_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkImageSourceParams_fDistanceScalingFactor_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkImageSourceParams_fLevel_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkImageSourceParams_fLevel_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkImageSourceParams_fDiffraction_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkImageSourceParams_fDiffraction_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkImageSourceParams_uDiffractionEmitterSide_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkImageSourceParams_uDiffractionEmitterSide_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkImageSourceParams_uDiffractionListenerSide_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkImageSourceParams_uDiffractionListenerSide_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkImageSourceParams(void* p) {}

__attribute__((visibility("default")))
void* CSharp_kDefaultDiffractionMaxEdges_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_kDefaultDiffractionMaxPaths_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_kMaxDiffraction_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_kHashListBlockAllocItemCount_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_kDiffractionMaxEdges_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_kDiffractionMaxPaths_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_kPortalToPortalDiffractionMaxPaths_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_AkSpatialAudioInitSettings(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkSpatialAudioInitSettings_uMaxSoundPropagationDepth_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkSpatialAudioInitSettings_uMaxSoundPropagationDepth_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkSpatialAudioInitSettings_fMovementThreshold_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkSpatialAudioInitSettings_fMovementThreshold_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkSpatialAudioInitSettings_uNumberOfPrimaryRays_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkSpatialAudioInitSettings_uNumberOfPrimaryRays_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkSpatialAudioInitSettings_uMaxReflectionOrder_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkSpatialAudioInitSettings_uMaxReflectionOrder_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkSpatialAudioInitSettings_uMaxDiffractionOrder_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkSpatialAudioInitSettings_uMaxDiffractionOrder_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkSpatialAudioInitSettings_uMaxEmitterRoomAuxSends_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkSpatialAudioInitSettings_uMaxEmitterRoomAuxSends_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkSpatialAudioInitSettings_uDiffractionOnReflectionsOrder_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkSpatialAudioInitSettings_uDiffractionOnReflectionsOrder_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkSpatialAudioInitSettings_fMaxPathLength_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkSpatialAudioInitSettings_fMaxPathLength_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkSpatialAudioInitSettings_fCPULimitPercentage_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkSpatialAudioInitSettings_fCPULimitPercentage_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkSpatialAudioInitSettings_uLoadBalancingSpread_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkSpatialAudioInitSettings_uLoadBalancingSpread_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkSpatialAudioInitSettings_bEnableGeometricDiffractionAndTransmission_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkSpatialAudioInitSettings_bEnableGeometricDiffractionAndTransmission_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkSpatialAudioInitSettings_bCalcEmitterVirtualPosition_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkSpatialAudioInitSettings_bCalcEmitterVirtualPosition_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkSpatialAudioInitSettings(void* p) {}

__attribute__((visibility("default")))
void* CSharp_new_AkImageSourceSettings__SWIG_0(void) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_AkImageSourceSettings__SWIG_1(void) { return NULL; }

__attribute__((visibility("default")))
int CSharp_AkImageSourceSettings_SetOneTexture(void) { return 0; }

__attribute__((visibility("default")))
void CSharp_AkImageSourceSettings_params__set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkImageSourceSettings_params__get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkImageSourceSettings(void* p) {}

__attribute__((visibility("default")))
void* CSharp_new_AkExtent__SWIG_0(void) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_AkExtent__SWIG_1(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkExtent_halfWidth_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkExtent_halfWidth_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkExtent_halfHeight_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkExtent_halfHeight_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkExtent_halfDepth_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkExtent_halfDepth_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkExtent(void* p) {}

__attribute__((visibility("default")))
void* CSharp_new_AkTriangle__SWIG_0(void) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_AkTriangle__SWIG_1(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkTriangle_point0_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkTriangle_point0_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkTriangle_point1_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkTriangle_point1_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkTriangle_point2_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkTriangle_point2_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkTriangle_surface_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkTriangle_surface_get(void* self) { return NULL; }

__attribute__((visibility("default")))
int CSharp_AkTriangle_Clear(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkTriangle_GetSizeOf(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkTriangle_Clone(void) { return 0; }

__attribute__((visibility("default")))
void CSharp_delete_AkTriangle(void* p) {}

__attribute__((visibility("default")))
void* CSharp_new_AkAcousticSurface(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkAcousticSurface_textureID_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkAcousticSurface_textureID_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkAcousticSurface_transmissionLoss_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkAcousticSurface_transmissionLoss_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkAcousticSurface_strName_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkAcousticSurface_strName_get(void* self) { return NULL; }

__attribute__((visibility("default")))
int CSharp_AkAcousticSurface_Clear(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkAcousticSurface_DeleteName(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkAcousticSurface_GetSizeOf(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkAcousticSurface_Clone(void) { return 0; }

__attribute__((visibility("default")))
void CSharp_delete_AkAcousticSurface(void* p) {}

__attribute__((visibility("default")))
void CSharp_AkReflectionPathInfo_imageSource_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkReflectionPathInfo_imageSource_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkReflectionPathInfo_numPathPoints_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkReflectionPathInfo_numPathPoints_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkReflectionPathInfo_numReflections_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkReflectionPathInfo_numReflections_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkReflectionPathInfo_level_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkReflectionPathInfo_level_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkReflectionPathInfo_isOccluded_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkReflectionPathInfo_isOccluded_get(void* self) { return NULL; }

__attribute__((visibility("default")))
int CSharp_AkReflectionPathInfo_GetSizeOf(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkReflectionPathInfo_GetPathPoint(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkReflectionPathInfo_GetAcousticSurface(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkReflectionPathInfo_GetDiffraction(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkReflectionPathInfo_Clone(void) { return 0; }

__attribute__((visibility("default")))
void* CSharp_new_AkReflectionPathInfo(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkReflectionPathInfo(void* p) {}

__attribute__((visibility("default")))
void CSharp_AkDiffractionPathInfo_emitterPos_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkDiffractionPathInfo_emitterPos_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkDiffractionPathInfo_virtualPos_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkDiffractionPathInfo_virtualPos_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkDiffractionPathInfo_nodeCount_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkDiffractionPathInfo_nodeCount_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkDiffractionPathInfo_diffraction_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkDiffractionPathInfo_diffraction_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkDiffractionPathInfo_transmissionLoss_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkDiffractionPathInfo_transmissionLoss_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkDiffractionPathInfo_totLength_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkDiffractionPathInfo_totLength_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkDiffractionPathInfo_obstructionValue_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkDiffractionPathInfo_obstructionValue_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkDiffractionPathInfo_occlusionValue_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkDiffractionPathInfo_occlusionValue_get(void* self) { return NULL; }

__attribute__((visibility("default")))
int CSharp_AkDiffractionPathInfo_GetSizeOf(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkDiffractionPathInfo_GetNodes(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkDiffractionPathInfo_GetAngles(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkDiffractionPathInfo_GetPortals(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkDiffractionPathInfo_GetRooms(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkDiffractionPathInfo_Clone(void) { return 0; }

__attribute__((visibility("default")))
void* CSharp_new_AkDiffractionPathInfo(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkDiffractionPathInfo(void* p) {}

__attribute__((visibility("default")))
void* CSharp_new_AkRoomParams(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkRoomParams_Front_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkRoomParams_Front_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkRoomParams_Up_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkRoomParams_Up_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkRoomParams_ReverbAuxBus_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkRoomParams_ReverbAuxBus_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkRoomParams_ReverbLevel_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkRoomParams_ReverbLevel_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkRoomParams_TransmissionLoss_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkRoomParams_TransmissionLoss_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkRoomParams_RoomGameObj_AuxSendLevelToSelf_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkRoomParams_RoomGameObj_AuxSendLevelToSelf_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkRoomParams_RoomGameObj_KeepRegistered_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkRoomParams_RoomGameObj_KeepRegistered_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkRoomParams_RoomPriority_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkRoomParams_RoomPriority_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkRoomParams(void* p) {}

__attribute__((visibility("default")))
void* CSharp_new_AkGeometryInstanceParams(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkGeometryInstanceParams_PositionAndOrientation_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkGeometryInstanceParams_PositionAndOrientation_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkGeometryInstanceParams_Scale_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkGeometryInstanceParams_Scale_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkGeometryInstanceParams_UseForReflectionAndDiffraction_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkGeometryInstanceParams_UseForReflectionAndDiffraction_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkGeometryInstanceParams(void* p) {}

__attribute__((visibility("default")))
void CSharp_SetGameObjectRadius(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetImageSource__SWIG_0(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetImageSource__SWIG_1(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetImageSource__SWIG_2(void* self, void* val) {}

__attribute__((visibility("default")))
int CSharp_RemoveImageSource__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_RemoveImageSource__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_RemoveImageSource__SWIG_2(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_ClearImageSources__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_ClearImageSources__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_ClearImageSources__SWIG_2(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_RemoveGeometry(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_RemoveGeometryInstance(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_RemoveRoom(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_RemovePortal(void) { return 0; }

__attribute__((visibility("default")))
void CSharp_SetReverbZone(void* self, void* val) {}

__attribute__((visibility("default")))
int CSharp_RemoveReverbZone(void) { return 0; }

__attribute__((visibility("default")))
void CSharp_SetGameObjectInRoom(void* self, void* val) {}

__attribute__((visibility("default")))
int CSharp_UnsetGameObjectInRoom(void) { return 0; }

__attribute__((visibility("default")))
void CSharp_SetReflectionsOrder(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetDiffractionOrder(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetMaxEmitterRoomAuxSends(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetNumberOfPrimaryRays(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetLoadBalancingSpread(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetEarlyReflectionsAuxSend(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetEarlyReflectionsVolume(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetPortalObstructionAndOcclusion(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetGameObjectToPortalObstruction(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetPortalToPortalObstruction(void* self, void* val) {}

__attribute__((visibility("default")))
int CSharp_QueryWetDiffraction(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_ResetStochasticEngine(void) { return 0; }

__attribute__((visibility("default")))
void CSharp_AkPlatformInitSettings_threadLEngine_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkPlatformInitSettings_threadLEngine_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkPlatformInitSettings_threadOutputMgr_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkPlatformInitSettings_threadOutputMgr_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkPlatformInitSettings_threadBankManager_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkPlatformInitSettings_threadBankManager_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkPlatformInitSettings_threadMonitor_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkPlatformInitSettings_threadMonitor_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkPlatformInitSettings_uNumRefillsInVoice_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkPlatformInitSettings_uNumRefillsInVoice_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkPlatformInitSettings_uSampleRate_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkPlatformInitSettings_uSampleRate_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkPlatformInitSettings_bEnableAvxSupport_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkPlatformInitSettings_bEnableAvxSupport_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkPlatformInitSettings_uMaxSystemAudioObjects_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkPlatformInitSettings_uMaxSystemAudioObjects_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkPlatformInitSettings_bEnableDirectInputSupport_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkPlatformInitSettings_bEnableDirectInputSupport_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkPlatformInitSettings(void* p) {}

__attribute__((visibility("default")))
void* CSharp_GetDeviceIDFromName(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_GetWindowsDeviceName__SWIG_0(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_GetWindowsDeviceName__SWIG_1(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_GetWindowsDeviceCount__SWIG_0(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_GetWindowsDeviceCount__SWIG_1(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkStreamMgrSettings(void* p) {}

__attribute__((visibility("default")))
void CSharp_AkDeviceSettings_pIOMemory_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkDeviceSettings_pIOMemory_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkDeviceSettings_uIOMemorySize_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkDeviceSettings_uIOMemorySize_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkDeviceSettings_uIOMemoryAlignment_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkDeviceSettings_uIOMemoryAlignment_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkDeviceSettings_ePoolAttributes_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkDeviceSettings_ePoolAttributes_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkDeviceSettings_uGranularity_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkDeviceSettings_uGranularity_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkDeviceSettings_threadProperties_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkDeviceSettings_threadProperties_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkDeviceSettings_fTargetAutoStmBufferLength_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkDeviceSettings_fTargetAutoStmBufferLength_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkDeviceSettings_uMaxConcurrentIO_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkDeviceSettings_uMaxConcurrentIO_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkDeviceSettings_bUseStreamCache_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkDeviceSettings_bUseStreamCache_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkDeviceSettings_uMaxCachePinnedBytes_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkDeviceSettings_uMaxCachePinnedBytes_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkDeviceSettings(void* p) {}

__attribute__((visibility("default")))
void CSharp_AkThreadProperties_nPriority_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkThreadProperties_nPriority_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkThreadProperties_dwAffinityMask_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkThreadProperties_dwAffinityMask_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkThreadProperties_uStackSize_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkThreadProperties_uStackSize_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_AkThreadProperties(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkThreadProperties(void* p) {}

__attribute__((visibility("default")))
void CSharp_SetErrorLogger__SWIG_0(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetErrorLogger__SWIG_1(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetAudioInputCallbacks(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_delete_AkUnityPlatformSpecificSettings(void* p) {}

__attribute__((visibility("default")))
void* CSharp_new_AkCommunicationSettings(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkCommunicationSettings_uPoolSize_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkCommunicationSettings_uPoolSize_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkCommunicationSettings_uDiscoveryBroadcastPort_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkCommunicationSettings_uDiscoveryBroadcastPort_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkCommunicationSettings_uCommandPort_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkCommunicationSettings_uCommandPort_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkCommunicationSettings_commSystem_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkCommunicationSettings_commSystem_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkCommunicationSettings_bInitSystemLib_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkCommunicationSettings_bInitSystemLib_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkCommunicationSettings_szAppNetworkName_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkCommunicationSettings_szAppNetworkName_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkCommunicationSettings(void* p) {}

__attribute__((visibility("default")))
void* CSharp_new_AkInitializationSettings(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkInitializationSettings(void* p) {}

__attribute__((visibility("default")))
void CSharp_AkInitializationSettings_streamMgrSettings_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkInitializationSettings_streamMgrSettings_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkInitializationSettings_deviceSettings_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkInitializationSettings_deviceSettings_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkInitializationSettings_initSettings_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkInitializationSettings_initSettings_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkInitializationSettings_platformSettings_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkInitializationSettings_platformSettings_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkInitializationSettings_musicSettings_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkInitializationSettings_musicSettings_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkInitializationSettings_unityPlatformSpecificSettings_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkInitializationSettings_unityPlatformSpecificSettings_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkInitializationSettings_uMemAllocationSizeLimit_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkInitializationSettings_uMemAllocationSizeLimit_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkInitializationSettings_uMemDebugLevel_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkInitializationSettings_uMemDebugLevel_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkInitializationSettings_uMemSpanCount_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkInitializationSettings_uMemSpanCount_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_AkExternalSourceInfo__SWIG_0(void) { return NULL; }

__attribute__((visibility("default")))
void CSharp_delete_AkExternalSourceInfo(void* p) {}

__attribute__((visibility("default")))
void* CSharp_new_AkExternalSourceInfo__SWIG_1(void) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_AkExternalSourceInfo__SWIG_2(void) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_new_AkExternalSourceInfo__SWIG_3(void) { return NULL; }

__attribute__((visibility("default")))
int CSharp_AkExternalSourceInfo_Clear(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkExternalSourceInfo_Clone(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkExternalSourceInfo_GetSizeOf(void) { return 0; }

__attribute__((visibility("default")))
void CSharp_AkExternalSourceInfo_iExternalSrcCookie_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkExternalSourceInfo_iExternalSrcCookie_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkExternalSourceInfo_idCodec_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkExternalSourceInfo_idCodec_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkExternalSourceInfo_szFile_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkExternalSourceInfo_szFile_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkExternalSourceInfo_pInMemory_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkExternalSourceInfo_pInMemory_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkExternalSourceInfo_uiMemorySize_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkExternalSourceInfo_uiMemorySize_get(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_AkExternalSourceInfo_idFile_set(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_AkExternalSourceInfo_idFile_get(void* self) { return NULL; }

__attribute__((visibility("default")))
int CSharp_RegisterGameObjInternal(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_UnregisterGameObjInternal(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_RegisterGameObjInternal_WithName(void) { return 0; }

__attribute__((visibility("default")))
void CSharp_SetBasePath(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetCurrentLanguage(void* self, void* val) {}

__attribute__((visibility("default")))
int CSharp_LoadFilePackage(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AddBasePath(void) { return 0; }

__attribute__((visibility("default")))
void CSharp_SetGameName(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetDecodedBankPath(void* self, void* val) {}

__attribute__((visibility("default")))
int CSharp_LoadAndDecodeBank(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_LoadAndDecodeBankFromMemory(void) { return 0; }

__attribute__((visibility("default")))
void* CSharp_GetCurrentLanguage(void* self) { return NULL; }

__attribute__((visibility("default")))
int CSharp_UnloadFilePackage(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_UnloadAllFilePackages(void) { return 0; }

__attribute__((visibility("default")))
void CSharp_SetObjectPosition(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_GetSourceMultiplePlayPositions__SWIG_0(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_GetSourceMultiplePlayPositions__SWIG_1(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_SetListeners(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetDefaultListeners(void* self, void* val) {}

__attribute__((visibility("default")))
void* CSharp_GetNumOutputDevices(void* self) { return NULL; }

__attribute__((visibility("default")))
int CSharp_AddOutput__SWIG_0(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AddOutput__SWIG_1(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AddOutput__SWIG_2(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AddOutput__SWIG_3(void) { return 0; }

__attribute__((visibility("default")))
void* CSharp_GetDefaultStreamSettings(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_GetDefaultDeviceSettings(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_GetDefaultMusicSettings(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_GetMajorMinorVersion(void* self) { return NULL; }

__attribute__((visibility("default")))
void* CSharp_GetSubminorBuildVersion(void* self) { return NULL; }

__attribute__((visibility("default")))
int CSharp_StartResourceMonitoring(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_StopResourceMonitoring(void) { return 0; }

__attribute__((visibility("default")))
void* CSharp_GetResourceMonitorDataSummary(void* self) { return NULL; }

__attribute__((visibility("default")))
int CSharp_StartDeviceCapture(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_StopDeviceCapture(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_ClearCaptureData(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_UpdateCaptureSampleCount(void) { return 0; }

__attribute__((visibility("default")))
void* CSharp_GetCaptureSamples(void* self) { return NULL; }

__attribute__((visibility("default")))
void CSharp_SetRoomPortal(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetRoom(void* self, void* val) {}

__attribute__((visibility("default")))
int CSharp_RegisterSpatialAudioListener(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_UnregisterSpatialAudioListener(void) { return 0; }

__attribute__((visibility("default")))
void CSharp_SetGeometry(void* self, void* val) {}

__attribute__((visibility("default")))
void CSharp_SetGeometryInstance(void* self, void* val) {}

__attribute__((visibility("default")))
int CSharp_QueryReflectionPaths(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_QueryDiffractionPaths(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_PerformStreamMgrIO(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkPlaylist_SWIGUpcast(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkMIDIPost_SWIGUpcast(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkEventCallbackInfo_SWIGUpcast(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkMIDIEventCallbackInfo_SWIGUpcast(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkMarkerCallbackInfo_SWIGUpcast(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkDurationCallbackInfo_SWIGUpcast(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkDynamicSequenceItemCallbackInfo_SWIGUpcast(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkMusicSyncCallbackInfo_SWIGUpcast(void) { return 0; }

__attribute__((visibility("default")))
int CSharp_AkMusicPlaylistCallbackInfo_SWIGUpcast(void) { return 0; }


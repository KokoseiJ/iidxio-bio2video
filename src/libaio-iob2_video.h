#include <stdint.h>
#include <stdbool.h>

#ifndef BIO2_LIBAIO_IOB2_VIDEO_H
#define BIO2_LIBAIO_IOB2_VIDEO_H

void * __fastcall aioIob2Bi2xTDJ_Create(void *AioNMgrIob2, uint8_t a2);
// max size for dest is 202 / 0xCA
void * __fastcall aioIob2Bi2xTDJ_GetDeviceStatus(
	void *this, void *dest, uint32_t size
);

void * __fastcall aioIob2Bi2xTDJ_SetEffectButtonLamp(void *this, bool state);
void __fastcall aioIob2Bi2xTDJ_SetPlayerButtonLAmp(
	void *this, uint32_t playerSide, uint32_t buttonIdx, bool state
);
void * __fastcall aioIob2Bi2xTDJ_SetStartLamp(
	void *this, uint32_t playerSide, bool state
);
void * __fastcall aioIob2Bi2xTDJ_SetVefxButtonLamp(void *this, bool state);

#endif


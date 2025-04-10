#ifndef BIO2_LIBAIO_IOB2_VIDEO_H
#define BIO2_LIBAIO_IOB2_VIDEO_H

#include <stdint.h>
#include <stdbool.h>

void * __fastcall aioIob2Bi2xTDJ_Create(void *AioNMgrIob2, uint8_t a2);
// max size for dest is 202 / 0xCA
void * __fastcall aioIob2Bi2xTDJ_GetDeviceStatus(
	void *this, void *dest, uint32_t size
);

void * __fastcall aioIob2Bi2xTDJ_SetEffectButtonLamp(void *this, bool state);
void __fastcall aioIob2Bi2xTDJ_SetPlayerButtonLamp(
	void *this, uint32_t playerSide, uint32_t buttonIdx, bool state
);
void * __fastcall aioIob2Bi2xTDJ_SetStartLamp(
	void *this, uint32_t playerSide, bool state
);
void * __fastcall aioIob2Bi2xTDJ_SetVefxButtonLamp(void *this, bool state);

// Card reader LED
void __fastcall aioIob2Bi2xTDJ_SetIccrLed(void *this, uint32_t playerSide, uint32_t colorValue);

// Pillar LEDs (ws2812)?
// sectionNum is seemingly used to decide which section to fill with?
// sectionNum range 0~16 (17 sections)
// ledData seems to be 24bit raw ws2812 data (MSB green, red, blue LSB)
void __fastcall aioIob2Bi2xTDJ_SetTapeLedData(void *this, uint32_t sectionNum, void *ledData);

void __fastcall aioIob2Bi2xTDJ_SetTurnTableLed(void *this, uint32_t playerSide, uint32_t colorValue);
void * __fastcall aioIob2Bi2xTDJ_SetTurnTableResist(void *this, uint32_t playerSide, uint8_t resistance);

void __fastcall aioIob2Bi2xTDJ_SetWooferLed(void *this, uint32_t colorValue);

#endif

/*
TapeLed offset? (probably the address of the beginning of each section)
.data:000000018002C280 rev_tapeled_offset_ dd 0, 13h, 10026h, 20053h, 30080h, 40095h, 400CBh, 400D6h
.data:000000018002C2A0                     dd 400E1h, 50117h, 50128h, 60139h, 6017Dh, 601C1h, 701FEh
.data:000000018002C2BC                     dd 70242h, 70286h, 802C3h
*/


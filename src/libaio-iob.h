#ifndef LIBAIO_IOB_H
#define LIBAIO_IOB_H

#include <stdint.h>

void * __fastcall aioIob2Bi2x_OpenSciUsbCdc(uint8_t a1);
void * __fastcall aioNMgrIob2_Create(void *aioIob2Bi2x, uint16_t a2);

typedef void _fastcall (*aioNMgrIob_BeginManage_t)(void *this);

void * __fastcall aioIob2Bi2x_CreateWriteFirmContext(uint32_t a1, int a2);
void * __fastcall aioIob2Bi2x_DestroyWriteFirmContext(void *fuck);
uint64_t __fastcall aioIob2Bi2x_WriteFirmGetState(void *this);
void * __fastcall aioIob2Bi2x_WriteFirmIsCompleted(int a1);
void * __fastcall aioIob2Bi2x_WriteFirmIsError(int a1);

#endif


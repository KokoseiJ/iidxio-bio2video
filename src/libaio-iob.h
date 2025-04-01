#ifndef LIBAIO_IOB_H
#define LIBAIO_IOB_H

#include <stdint.h>

void * __fastcall aioIob2Bi2x_OpenSciUsbCdc(uint8_t a1);
void * __fastcall aioNMgrIob2_Create(void *aioIob2Bi2x, uint16_t a2);

typedef void _fastcall (*aioNMgrIob_BeginManage_t)(void *this);

#endif


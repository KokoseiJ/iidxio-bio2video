#include "libaio_wrap.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <windows.h>

void *init_bi2x() {
	void *sciUsbCdc, *aioNMgrIob2, *bi2xTdj;
	aioNMgrIob_BeginManage_t aioNMgrIob_BeginManage;

	sciUsbCdc = aioIob2Bi2x_OpenSciUsbCdc(0);
	if (!sciUsbCdc) goto error;
	
	aioNMgrIob2 = aioNMgrIob2_Create(sciUsbCdc, 0);
	if (!aioNMgrIob2) goto error;

	bi2xTdj = aioIob2Bi2xTDJ_Create(aioNMgrIob2, 1);
	if (!bi2xTdj) goto error;

	aioNMgrIob_BeginManage = (*(void***)aioNMgrIob2)[10];
	if (!aioNMgrIob_BeginManage) goto error;

	aioNMgrIob_BeginManage(aioNMgrIob2);

	return bi2xTdj;

error:
	return NULL;
}

bool write_firm() {
	bool rtnval;
	void *writeFirmCtx;
	uint32_t writeFirmState;
       
	printf("[*] Cleaning up writeFirmContext...\n");
	aioIob2Bi2x_DestroyWriteFirmContext(NULL);
	printf("[*] Creating writeFirmContext...\n");
	writeFirmCtx = aioIob2Bi2x_CreateWriteFirmContext(0, 1);
	if (!writeFirmCtx) return false;

	printf("[*] Checking");

	while (true) {
		writeFirmState = aioIob2Bi2x_WriteFirmGetState(writeFirmCtx);
		printf(".");
		if (aioIob2Bi2x_WriteFirmIsError(writeFirmState)) {
			printf("\n[!] WriteFirm error!\n");
			rtnval = false;
			goto cleanup;
		}

		if (aioIob2Bi2x_WriteFirmIsCompleted(writeFirmState)) {
			printf("\n[*] Writefirm Complete!\n");
			rtnval = true;
			goto cleanup;
		}

		Sleep(1000);
	}

cleanup:
	printf("[*] Destrying writeFirm...\n");
	aioIob2Bi2x_DestroyWriteFirmContext(NULL);
	return rtnval;
}


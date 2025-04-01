#include "libaio_wrap.h"

void *init_bio2() {
	void *sciUsbCdc, *aioNMgrIob2, *bi2xTdj;
	aioNMgrIob_BeginManage_t aioNMgrIob_BeginManage;

	sciUsbCdc = aioIob2Bi2x_OpenSciUsbCdc(0);
	if (!sciUsbCdc) goto error;
	
	aioNMgrIob2 = aioNMgrIob2_Create(sciUsbCdc, 0);
	if (!aioNMgrIob2) goto error;

	bi2xTdj = aioIob2Bi2xTDJ_Create(aioNMgrIob2, 1);
	if (!bi2xTdj) goto error;

	aioNMgrIob_BeginManage = (aioNMgrIob2 + 80);
	if (!aioNMgrIob_BeginManage) goto error;

	aioNMgrIob_BeginManage(aioNMgrIob2);

	return bi2xTdj;

error:
	return NULL;
}


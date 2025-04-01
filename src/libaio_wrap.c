#include "libaio_wrap.h"

void *init_bio2() {
	void *sciUsbCdc = aioIob2Bi2x_OpenSciUsbCdc(0);
	if (!sciUsbCdc) goto error;
	
	void *aioNMgrIob2 = aioNMgrIob2_Create(sciUsbCdc, 0);
	if (!aioNMgrIob2) goto error;

	void *bi2xTdj = aioIob2Bi2xTDJ_Create(aioNMgrIob2, 1);

	aioNMgrIob_BeginManage_t aioNMgrIob_BeginManage = (aioNMgrIob2 + 80);
	aioNMgrIob_BeginManage(aioNMgrIob2);

	return bi2xTdj;
}


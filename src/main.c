#include "bi2x_tdj.h"
#include "libaio_wrap.h"

#include <stdint.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define BI2X_TIMEOUT 10

int main() {
	struct tdj_status buffer = {0,};
	unsigned int start_time;

	printf("[*] Initializing Bi2x...\n");

	void *bi2x = init_bio2();
	if (!bi2x) {
		printf("[!] Failed to initialize bio2!\n");
		return 1;
	}

	printf("[*] Object created, trying writefirm...\n");

	if (!write_firm()) {
		printf("[!] Failed to write firmware!\n");
		return 1;
	}
	
	printf("[*] Waiting for bi2x to come online");
	start_time = GetTickCount();
	while (!buffer.is_online) {
		if (GetTickCount() - start_time > BI2X_TIMEOUT * 1000) {
			printf("\n[!] Bi2x timeout!\n");
			return 1;
		}
		printf(".");

		aioNodeCtl_UpdateDevicesStatus();
		aioIob2Bi2xTDJ_GetDeviceStatus(bi2x, &buffer, sizeof(buffer));
		Sleep(1000);
	}
	printf("hello there!\n");

	printf("[*] Poll ready, press enter when you're ready:");
	_getch();

	while (1) {
		aioNodeCtl_UpdateDevicesStatus();
		aioIob2Bi2xTDJ_GetDeviceStatus(bi2x, &buffer, sizeof(buffer));

		printf("sq %d ot %d os %d oc %d 1s %d 2s %d ee %d ev %d 1t %d 2t %d p1 %d%d%d%d%d%d%d p2 %d%d%d%d%d%d%d\n",
			buffer.seq1, buffer.test, buffer.service, buffer.coin, buffer.p1_start, buffer.p2_start,
			buffer.effects, buffer.vefx, buffer.p1_tt, buffer.p2_tt,
			buffer.p1_1, buffer.p1_2, buffer.p1_3, buffer.p1_4, buffer.p1_5, buffer.p1_6, buffer.p1_7,
			buffer.p2_1, buffer.p2_2, buffer.p2_3, buffer.p2_4, buffer.p2_5, buffer.p2_6, buffer.p2_7
		);
		Sleep(1);
	}

	return 0;
}


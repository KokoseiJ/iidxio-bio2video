#include "libaio_wrap.h"

#include <stdint.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>

int main() {
	uint8_t buffer[202] = {0,};

	int i;

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

	printf("[*] Poll ready, press enter when you're ready:");
	_getch();

	

	while (1) {
		aioNodeCtl_UpdateDevicesStatus();
		aioIob2Bi2xTDJ_GetDeviceStatus(bi2x, buffer, sizeof(buffer));

		system("cls");

		for(i=0; i<202; i++) {
			printf("%c%02hhx", 
				(i % 25 == 0 ? '\n' : ' '),
				buffer[i]
			);
		}
	}

	return 0;
}


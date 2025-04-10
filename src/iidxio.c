#include "bi2x_tdj.h"
#include "libaio_wrap.h"
#include "bemanitools/glue.h"
#include "bemanitools/iidxio.h"
#include <windows.h>
#include <stdbool.h>
#include <stdint.h>

#define MODULE "iidxio-bio2video"
#define BI2X_TIMEOUT 30000

log_formatter_t misc, info, warning, fatal;

thread_create_t thread_create;
thread_join_t thread_join;
thread_destroy_t thread_destroy;

void *bi2x = NULL;
struct tdj_status bi2x_status;

void iidx_io_set_loggers(
    log_formatter_t p_misc,
    log_formatter_t p_info,
    log_formatter_t p_warning,
    log_formatter_t p_fatal)
{
	misc = p_misc;
	info = p_info;
	warning = p_warning;
	fatal = p_fatal;

	return;
}

bool iidx_io_init(
    thread_create_t p_thread_create,
    thread_join_t p_thread_join,
    thread_destroy_t p_thread_destroy)
{
	unsigned int start_time;

	thread_create = p_thread_create;
	thread_join = p_thread_join;
	thread_destroy = p_thread_destroy;

	info(MODULE, "Hello, World!");

	bi2x = init_bi2x();
	if (!bi2x) {
		fatal(MODULE, "Failed to initialize BI2X!");
		return false;
	}

	info(MODULE, "BI2X object created, trying writefirm...");

	if (!write_firm()) {
		fatal(MODULE, "Failed to write firmware!");
		return false;
	}

	info(MODULE, "Waiting for BI2X to come online...");

	start_time = GetTickCount();
	while (!bi2x_status.is_online) {
		if (GetTickCount() - start_time > BI2X_TIMEOUT) {
			fatal(MODULE, "BI2X Timeout!");
			return false;
		}
		iidx_io_ep1_send();
		iidx_io_ep2_recv();
		Sleep(1);
	}

	info(MODULE, "BI2X device initialized.");
	return true;
}

void iidx_io_fini(void) {
	// TODO: do something...
	return;
}

/* Set the deck lighting state. See enum iidx_io_deck_light above. */

void iidx_io_ep1_set_deck_lights(uint16_t deck_lights) {
	int player_side, button_idx;

	for (player_side=0; player_side<2; player_side++) {
		for (button_idx=0; button_idx<7; button_idx++) {
			aioIob2Bi2xTDJ_SetPlayerButtonLamp(
				bi2x, player_side, button_idx,
				deck_lights >> (player_side * 7 + button_idx) & 1
			);
		}
	}
	return;
}

/* Set front panel lighting state. See enum iidx_io_panel_light above. */

void iidx_io_ep1_set_panel_lights(uint8_t panel_lights) {
	aioIob2Bi2xTDJ_SetStartLamp(
		bi2x, 0, panel_lights >> IIDX_IO_PANEL_LIGHT_P1_START & 1
	);
	aioIob2Bi2xTDJ_SetStartLamp(
		bi2x, 1, panel_lights >> IIDX_IO_PANEL_LIGHT_P2_START & 1
	);
	aioIob2Bi2xTDJ_SetVefxButtonLamp(
		bi2x, panel_lights >> IIDX_IO_PANEL_LIGHT_VEFX & 1
	);
	aioIob2Bi2xTDJ_SetEffectButtonLamp(
		bi2x, panel_lights >> IIDX_IO_PANEL_LIGHT_EFFECT & 1
	);

	return;
}

/* Set state of the eight halogens above the marquee. */

void iidx_io_ep1_set_top_lamps(uint8_t top_lamps) {
	// TODO: Somehow map this to LM lights
	return;
}

/* Switch the top neons on or off. */

void iidx_io_ep1_set_top_neons(bool top_neons) {
	// TODO: Also somehow map this to LM lights
	return;
}

/* Transmit the lighting state to the lighting controller. This function is
   called immediately after all of the other iidx_io_ep1_set_*() functions.

   Return false in the event of an IO error. This will lock the game into an
   IO error screen. */

bool iidx_io_ep1_send(void) {
	aioNodeCtl_UpdateDevicesStatus();
	return true;
}

/* Read input state from the input controller. This function is called
   immediately before all of the iidx_io_ep2_get_*() functions.

   Return false in the event of an IO error. This will lock the game into an
   IO error screen. */

bool iidx_io_ep2_recv(void) {
	aioIob2Bi2xTDJ_GetDeviceStatus(bi2x, &bi2x_status, sizeof(bi2x_status));
	return true;
}

/* Get absolute turntable position, expressed in 1/256ths of a rotation.
   player_no is either 0 or 1. */

uint8_t iidx_io_ep2_get_turntable(uint8_t player_no) {
	return (player_no == 0) ? bi2x_status.p1_tt : bi2x_status.p2_tt;
}

/* Get slider position, where 0 is the bottom position and 15 is the topmost
   position. slider_no is a number between 0 (leftmost) and 4 (rightmost). */

uint8_t iidx_io_ep2_get_slider(uint8_t slider_no) {
	// STUB: bi2x sadly doesn't have this. Report max for all
	return 15;
}

/* Get the state of the system buttons. See enums above. */

uint8_t iidx_io_ep2_get_sys(void) {
	return	bi2x_status.test	<< IIDX_IO_SYS_TEST	|
		bi2x_status.service	<< IIDX_IO_SYS_SERVICE	|
		bi2x_status.coin	<< IIDX_IO_SYS_COIN	;
}

/* Get the state of the panel buttons. See enums above. */

uint8_t iidx_io_ep2_get_panel(void) {
	return	bi2x_status.p1_start	<< IIDX_IO_PANEL_P1_START	|
		bi2x_status.p2_start	<< IIDX_IO_PANEL_P2_START	|
		bi2x_status.vefx	<< IIDX_IO_PANEL_VEFX		|
		bi2x_status.effect	<< IIDX_IO_PANEL_EFFECT		;
}

/* Get the state of the 14 key buttons. See enums above. */

uint16_t iidx_io_ep2_get_keys(void) {
	return	bi2x_status.p1_1 << IIDX_IO_KEY_P1_1 |
		bi2x_status.p1_2 << IIDX_IO_KEY_P1_2 |
		bi2x_status.p1_3 << IIDX_IO_KEY_P1_3 |
		bi2x_status.p1_4 << IIDX_IO_KEY_P1_4 |
		bi2x_status.p1_5 << IIDX_IO_KEY_P1_5 |
		bi2x_status.p1_6 << IIDX_IO_KEY_P1_6 |
		bi2x_status.p1_7 << IIDX_IO_KEY_P1_7 |
		bi2x_status.p2_1 << IIDX_IO_KEY_P2_1 |
		bi2x_status.p2_2 << IIDX_IO_KEY_P2_2 |
		bi2x_status.p2_3 << IIDX_IO_KEY_P2_3 |
		bi2x_status.p2_4 << IIDX_IO_KEY_P2_4 |
		bi2x_status.p2_5 << IIDX_IO_KEY_P2_5 |
		bi2x_status.p2_6 << IIDX_IO_KEY_P2_6 |
		bi2x_status.p2_7 << IIDX_IO_KEY_P2_7 ;
}

/* Write a nine-character string to the 16-segment display. This happens on a
   different schedule to all of the other IO operations, so you should initiate
   the communication as soon as this function is called */

bool iidx_io_ep3_write_16seg(const char *text) {
	// STUB: guess what bi2x also doesn't have...
	return true;
}


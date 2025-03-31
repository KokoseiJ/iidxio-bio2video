#include <stdbool.h>
#include <stdint.h>
#include "bemanitools/glue.h"
#include "bemanitools/iidxio.h"

void iidx_io_set_loggers(
    log_formatter_t misc,
    log_formatter_t info,
    log_formatter_t warning,
    log_formatter_t fatal) {
	return;
}

bool iidx_io_init(
    thread_create_t thread_create,
    thread_join_t thread_join,
    thread_destroy_t thread_destroy) {
	return true;
}

void iidx_io_fini(void) {
	return;
}

/* Set the deck lighting state. See enum iidx_io_deck_light above. */

void iidx_io_ep1_set_deck_lights(uint16_t deck_lights) {
	return;
}

/* Set front panel lighting state. See enum iidx_io_panel_light above. */

void iidx_io_ep1_set_panel_lights(uint8_t panel_lights) {
	return;
}

/* Set state of the eight halogens above the marquee. */

void iidx_io_ep1_set_top_lamps(uint8_t top_lamps) {
	return;
}

/* Switch the top neons on or off. */

void iidx_io_ep1_set_top_neons(bool top_neons) {
	return;
}

/* Transmit the lighting state to the lighting controller. This function is
   called immediately after all of the other iidx_io_ep1_set_*() functions.

   Return false in the event of an IO error. This will lock the game into an
   IO error screen. */

bool iidx_io_ep1_send(void) {
	// TODO: UpdateDevicesStatus
	return true;
}

/* Read input state from the input controller. This function is called
   immediately before all of the iidx_io_ep2_get_*() functions.

   Return false in the event of an IO error. This will lock the game into an
   IO error screen. */

bool iidx_io_ep2_recv(void) {
	// TODO: GetDeviceStatus
	return true;
}

/* Get absolute turntable position, expressed in 1/256ths of a rotation.
   player_no is either 0 or 1. */

uint8_t iidx_io_ep2_get_turntable(uint8_t player_no) {
	return 69;
}

/* Get slider position, where 0 is the bottom position and 15 is the topmost
   position. slider_no is a number between 0 (leftmost) and 4 (rightmost). */

uint8_t iidx_io_ep2_get_slider(uint8_t slider_no) {
	// STUB: bi2x sadly doesn't have this. Report max for all
	return 15;
}

/* Get the state of the system buttons. See enums above. */

uint8_t iidx_io_ep2_get_sys(void) {
	return 0;
}

/* Get the state of the panel buttons. See enums above. */

uint8_t iidx_io_ep2_get_panel(void) {
	return 0;
}

/* Get the state of the 14 key buttons. See enums above. */

uint16_t iidx_io_ep2_get_keys(void) {
	return 0;
}

/* Write a nine-character string to the 16-segment display. This happens on a
   different schedule to all of the other IO operations, so you should initiate
   the communication as soon as this function is called */

bool iidx_io_ep3_write_16seg(const char *text) {
	// STUB: guess what bi2x also doesn't have...
	return true;
}


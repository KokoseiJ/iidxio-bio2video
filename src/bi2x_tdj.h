#ifndef BIO2_BI2X_TDJ_H
#define BIO2_BI2X_TDJ_H

#include <stdint.h>

struct tdj_status {
	uint8_t seq1;
	uint8_t seq2;
	uint8_t is_online;
	uint8_t unk03;
	uint8_t test;
	uint8_t service;
	uint8_t coin;
	uint8_t unk07;
	uint8_t p1_start;
	uint8_t p2_start;
	uint8_t vefx;
	uint8_t effect;
	uint8_t unk12[8];
	uint8_t p1_tt;
	uint8_t p2_tt;
	uint8_t unk22[5];
	uint8_t p1_1;
	uint8_t p1_2;
	uint8_t p1_3;
	uint8_t p1_4;
	uint8_t p1_5;
	uint8_t p1_6;
	uint8_t p1_7;
	uint8_t p2_1;
	uint8_t p2_2;
	uint8_t p2_3;
	uint8_t p2_4;
	uint8_t p2_5;
	uint8_t p2_6;
	uint8_t p2_7;
};

#endif


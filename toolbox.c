//
// toolbox.c
// 
// Tools source for sbb_reg
// 
// (20060922-20060922, cearn)
//
// === NOTES ===
// * This is a _small_ set of typedefs, #defines and inlines that can 
//   be found in tonclib, and might not represent the 
//   final forms.

#include "toolbox.h"

// === (tonc_core.c) ==================================================

u16 __key_curr= 0, __key_prev= 0;

u32 lfsr = 0xACE1u;
u32 bit;

unsigned rand()
{
	bit = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5) ) & 1;
	return lfsr = ((lfsr >> 1) | (bit << 15)) & 0xFFFF;
}
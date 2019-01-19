//
//  BIOS call functions
//
//! \file tonc_bios.h
//! \author J Vijn
//! \date 20060508 - 20070208
//
// === NOTES ===
//
// Pretty much copied verbatim from Pern and dkARM's libgba
// (which in turn is copied from CowBite Spec (which got its info from 
//  GBATek))
// 
//
// === NOTES ===
// * Make SURE your data is aligned to 32bit boundaries. Defining data
//   as u32 (and I do mean define; not merely cast) ensures this. Either 
//   that or use __attribute__(( aligned(4) ))
// * There is a large (70 cycle in and out) overhead for SWIs. If you 
//   know what they do, consider creating replacement code
// * div by 0 locks up GBA. 
// * Cpu(Fast)Set's count is in chunks, not bytes. CpuFastSet REQUIRES
//   n*32 byte data
// * SoftReset is funky with interrupts on.
// * VBlankIntrWait is your friend. If you have a VBlank isr that clears 
//   REG_IFBIOS as well. Use this instead of REG_VCOUNT polling for
//   VSync.
// * I haven't tested many of these functions. The ones that are have a 
//   plus (+) behind their numbers.
// * I've switched to the standard BIOS names. 

#ifndef TONC_BIOS
#define TONC_BIOS

#ifndef NULL
#define NULL (void*)0
#endif

#include "tonc_irq.h"

void VBlankIntrWait(void);


#endif // TONC_BIOS

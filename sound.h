#ifndef SOUND_H
#define SOUND_H

#include "toolbox.h"

extern const u32 _binary_lo1234_pcm_start[]; //the sample. its a pcm wave file converted to an elf file with objcopyroda.exe (devrs.com/gba) 

void InterruptProcess(void) __attribute__ ((section(".iwram"), long_call)); //the interrupt handler from crt0.s

void sound_init();
void sound_start();

#endif
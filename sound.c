#include "toolbox.h"
#include "sound.h"
#include "music.h"

//const u32 _binary_lo1234_pcm_start[9178];

int pos = 0;
int step = 0xffff;

void InterruptProcess(void){
	pos += step;
	if (pos >= music_LENGTH) {
		pos = 0;
		REG_TM0CNT_H=0; //disable timer 0
		REG_DMA1CNT_H=0; //stop DMA
		sound_init();
		sound_start();
	} else {
		//REG_DMA1SAD=(unsigned long) (music_DATA + pos);
		//while(1); We also make it into here at least once.
	}
	if (pos + step > music_LENGTH) {
		REG_TM1CNT_L = (vu16)(0xffff - (music_LENGTH - pos));
	} else {
		REG_TM1CNT_L = 0;//0xffff - step;
	}
	REG_TM1CNT_H=0xC4; //enable timer1 + irq and cascade from timer 0
	//while(1); We do make it into here after 4 seconds.
//sample finished!,stop Direct sound

//REG_TM0CNT_H=0; //disable timer 0
//REG_DMA1CNT_H=0; //stop DMA

//clear the interrupt(s)
REG_IF |= REG_IF;
}

void sound_init() {
	//play a mono sound at 16khz
	//uses timer 0 as sampling rate source
	//uses timer 1 to count the samples played in order to stop the sound 
	REG_SOUNDCNT_H=0x0b0F; //enable DS A&B + fifo reset + use timer0 + max 
		//volume to L and R
	REG_SOUNDCNT_X=0x0080; //turn sound chip on

	REG_DMA1SAD=(unsigned long)music_DATA;//_binary_lo1234_pcm_start;
		//dma1 source
	REG_DMA1DAD=0x040000a0; //write to FIFO A address
	REG_DMA1CNT_H=0xb600; //dma control: DMA enabled+ start on 
		//FIFO+32bit+repeat+increment source&dest

	REG_TM1CNT_L=0x0; //0xffff-the number of samples to play
	REG_TM1CNT_H=0xC4; //enable timer1 + irq and cascade from timer 0

	//Don't enable these, our master switch is taking care of that.
	//REG_IE=0x10; //enable irq for timer 1 
	//REG_IME=1; //master enable interrupts

	//Formula for playback frequency is: 0xFFFF-round(cpuFreq/playbackFreq)
	//65536-round(2^24/16000)=0xFBE8
	REG_TM0CNT_L=0xFBE8; //16khz playback freq
	
	/*
		True stereo output is a simple extension of the above code:
		
		Set REG_SOUNDCNT_H to send DS A to right output and DS B to left
		Set DMA1 source to the right buffer, and destination to DS A FIFO
		Set DMA2 source to the left buffer, and destination to DS B FIFO
		Set timer 0 as sampling rate source for both DS A&B
	*/
}

void sound_start() {
	REG_TM0CNT_H=0x0080; //enable timer0
}
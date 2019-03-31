//
// map_block1.c
// showing map-block boundaries regular backgrounds
//
// (20031114 - 20060317, Cearn)

#include "mode.h"
#include "tonc_bios.h"
#include "sound.h"

int main()
{
	mode_set(MODE_EXPLORE);
	irq_init(NULL);
	irq_add(II_VBLANK, NULL);
	irq_add(II_TIMER1, InterruptProcess);
	sound_init();
	sound_start();

	while(1)
	{
		VBlankIntrWait();
		mode_tick();
	}
	return 0;
}

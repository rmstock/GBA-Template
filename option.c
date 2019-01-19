#include "option.h"
#include "background.h"
#include "palette.h"
#include "display.h"
#include "sprite.h"

void option_init() {
	//background_init();
	//palette_init();
	//display_init();
	//sprite_init();
}

void option_tick() {
		vid_vsync();

		key_poll();
		//sprite_tick();
		//sprite_write();
}

void option_save() {
	//TODO
}
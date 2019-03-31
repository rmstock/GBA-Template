#include "explore.h"
#include "background.h"
#include "palette.h"
#include "display.h"
#include "sprite.h"

void explore_init() {
	background_init();
	palette_init();
	display_init();
	sprite_init();
}

void explore_tick() {
	sprite_write();
	key_poll();
	sprite_tick();
}

void explore_save(){
	//TODO
}
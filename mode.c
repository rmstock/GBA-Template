#include "mode.h"
#include "panic.h"

#include "explore.h"
#include "option.h"

int mode_current;
fptr mode_tick;

void mode_set(int mode) {
	mode_save();
	if (mode == MODE_OPTION) {
		option_init();
		mode_tick = option_tick;
	} else if (mode == MODE_EXPLORE) {
		explore_init();
		mode_tick = explore_tick;
	} else {
		panic(MODE_NONE);
		option_init();
		mode_tick = option_tick;
	}
	mode_current = mode;
}

void mode_save() {
	if (mode_current == MODE_EXPLORE) {
		explore_save();
	} else if (mode_current == MODE_OPTION) {
		option_save();
	}//else do nothing.
}
#include "display.h"

#include "toolbox.h"

void display_init()
{
	REG_DISPCNT= DCNT_MODE0 | DCNT_BG0 | DCNT_OBJ | DCNT_OBJ_1D;
}
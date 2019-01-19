#include "panic.h"

#include "toolbox.h"

void panic(int error) {
	pal_bg_mem[2] = (unsigned short)error;
}
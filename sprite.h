#ifndef SPRITE_H
#define SPRITE_H

#include "types.h"
#include "toolbox.h"
#include "input.h"
#include "memdef.h"

#define SSIZE 8
#define OBJ_BUFFER_SIZE 128

extern OBJ_ATTR obj_buffer[OBJ_BUFFER_SIZE];

void sprite_init();
void sprite_tick();
void sprite_write();

#endif

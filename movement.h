#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "types.h"
#include "sprite.h"

void movement_shift(u32 num);
void movement_vert(u32 num);
void movement_jump(u32 num);

extern s32 posX[OBJ_BUFFER_SIZE], posY[OBJ_BUFFER_SIZE];//Actual sprite position in pixels.
extern u32 jumping[OBJ_BUFFER_SIZE];
extern s32 moveX, moveY; //Velocity of current sprite. 

s32 open_horz(s32 px, s32 py);
s32 open_vert(s32 px, s32 py);

#endif

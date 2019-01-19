#include "sprite.h"

#include "types.h"
#include "toolbox.h"
#include "input.h"
#include "memdef.h"
#include "sprites.h"
#include <string.h>
#include "background.h"
#include "movement.h"
#include "oam_util.h"

#define PLAYER 0

OBJ_ATTR obj_buffer[128];
OBJ_AFFINE *const obj_aff_buffer = (OBJ_AFFINE*)obj_buffer;

void sprite_init()
{
	oam_init(obj_buffer, 128);//Clears data so that we don't render garbage.
	posX[0] = 120;
	posY[0] = 80;
	obj_set_attr(&obj_buffer[0], (ATTR0_SQUARE | ATTR0_8BPP) & (~ATTR0_HIDE), ATTR1_SIZE_8x8, ATTR2_PALBANK(0) | (ball_INDEX * 2));
	obj_set_pos(&obj_buffer[0], posX[0], posY[0]);
	//obj_set_attr(&obj_buffer[1], (ATTR0_SQUARE | ATTR0_8BPP) & (~ATTR0_HIDE), ATTR1_SIZE_8x8, ATTR2_PALBANK(0) | (ball_INDEX * 2));
	//obj_set_pos(&obj_buffer[1], 0, 0);
	memcpy32(&tile8_mem[4][0], sprites_Tiles, sprites_COUNT * 64);//Copy sprite image data to sprite data area.
}

void sprite_tick()
{
	for (u32 num = 0; num < OBJ_BUFFER_SIZE; num++) {
		int temp = key_tri_horz();
		moveX = temp;//Side to side movement.
		if (temp > 0) obj_buffer[num].attr1 |= ATTR1_HFLIP; //Make the character face the right way.
		else if (temp < 0) obj_buffer[num].attr1 &= !ATTR1_HFLIP;
		movement_jump(num);
		movement_shift(num);//This limits us to 1px movement per frame.
		movement_vert(num);	//Faster movement needs to be sparing and more like teleport.
	}
	
	int x = (posX[PLAYER]) - 120;
	int y = (posY[PLAYER]) - 80;
	//Keep player centered, unless they get close to edges.
	BG_POINT bg0_pt= background_offset(x, y);
	//background_offset(x,y);
	for (u32 num = 0; num < OBJ_BUFFER_SIZE; num++) {
		int dx = (posX[num]) - bg0_pt.x;
		int dy = (posY[num]) - bg0_pt.y;
		
		obj_set_pos(&obj_buffer[num], dx, dy);
	}
}

void sprite_write()
{
	oam_copy(oam_mem, obj_buffer, OBJ_BUFFER_SIZE);
}
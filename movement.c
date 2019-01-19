#include "movement.h"
#include "types.h"
#include "background.h"
#include "oam_util.h"
#include "tiles.h"

#define SBB_0 28//Magic Number

s32 posX[OBJ_BUFFER_SIZE], posY[OBJ_BUFFER_SIZE];//Actual sprite position in pixels.
s32 moveX, moveY; //Velocity of current sprite. TODO Would be lovely to pipeline.
u32 jumping[OBJ_BUFFER_SIZE];

int open_horz(s32 px, s32 py) {
	// Don't let the test go over the map.
	if (px < 0 || py < 0) return 0;
	
	u32 tileX = (u32)px>>3;
	u32 tileY = (u32)py>>3;
	u32 tileIndex = tileX | tileY << 6;//map is 64 tiles wide
	u32 tileBelow = tileX | (tileY + 1) << 6;
	//tileIndex needs to be clear, and below needs to be clear unless we are along the 
	//top edge of our tile.
	return (bg_tiles[tileIndex].empty &&
		(!(py & 7) || bg_tiles[tileBelow].empty));
}

int open_vert(s32 px, s32 py) {
	// Don't let the test go over the map.
	if (px < 0 || py < 0) return 0;
	
	u32 tileX = (u32)px>>3;//TileX, rename?
	u32 tileY = (u32)py>>3;
	u32 tileIndex = tileX | tileY << 6;//map is 64 tiles wide
	u32 tileRight = (tileX + 1) | tileY << 6;
	//tileIndex needs to be clear, and below needs to be clear unless we are along the 
	//top edge of our tile.
	if (tileIndex >= 1024 * 4) {//Offscreen
		return 0;//You can't fall through, and you can jump off of.
	}
	return (bg_tiles[tileIndex].empty &&
		(!(px & 7) || bg_tiles[tileRight].empty));
}

void movement_jump(u32 num) {
	int key = key_tri_vert() == -1 ? 1: 0;
	u32 *jump = &jumping[num];
	if (*jump) {
		(*jump)++;
		if (key && *jump < 26) {
			moveY = -1;
		} else {
			moveY = 1;
		}
	} else if (key && !open_vert(posX[num],posY[num] + 8)) {
		moveY = -1;
		*jump = 1; 
	} else {
		moveY = 1;
	}
}


void movement_vert(u32 num) {
	if (moveY > 0)
	{
		//tile down.
		s32 sy = posY[num] + 8;
		if (open_vert(posX[num], sy))
		{
			posY[num] += 1;
		} else if (key_tri_vert() != -1) jumping[num] = 0;//Needed to stop jumping.
	}//Move a pixel up.
	else if (moveY < 0)
	{
		s32 sy = posY[num] - 1;
		if (open_vert(posX[num], sy))
		{
			posY[num] = sy;
		} else if (key_tri_vert() == -1) jumping[num] = 26;//Max hight in jumping, make fall.
	}
	if (posY[num] < 0) posY[num] = 0;
	else if (posY[num] >= (BHEIGHT - SSIZE)) posY[num] = (BHEIGHT - SSIZE);//Tiles * 8 - screen_width

}

void movement_shift(u32 num) {
	//Move a pixel to the right
	if (moveX > 0)
	{
		//tile to right.
		s32 sx = posX[num] + 8;
		if (open_horz(sx, posY[num]))
		{
			posX[num] += 1;
		}
	}//Move a pixel to the left.
	else if (moveX < 0)
	{
		s32 sx = posX[num] - 1;
		if (open_horz(sx, posY[num]))
		{
			posX[num] = sx;
		}
	}
	if (posX[num] < 0) posX[num] = 0;
	else if (posX[num] >= BWIDTH - SSIZE) posX[num] = BWIDTH - SSIZE;//Tiles - screen_width
}
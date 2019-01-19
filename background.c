#include "background.h"
#include "tiles.h"
#include "display.h"
#include "oam_util.h"

#define CBB_0  0
#define SBB_0 28 //Magic number. See TONC.

SCR_ENTRY *bg0_map= se_mem[SBB_0];
BG_POINT bg0_pt = {0,0};
TileType bg_tiles[4096];

void background_init()
{
	// initialize a background
	REG_BG0CNT= BG_CBB(CBB_0) | BG_SBB(SBB_0) | BG_8BPP | BG_REG_64x64;
	REG_BG0HOFS= 0;
	REG_BG0VOFS= 0;

	memcpy32(&tile8_mem[CBB_0][0],tiles_Tiles, tiles_COUNT * 16);

	volatile SCR_ENTRY *pse = bg0_map;
	for(u32 ii=0; ii<4096; ii++)
	{
		SCR_ENTRY tile = rand() & 15;
		if ((tile < 3))
		{
			tile = green_single_INDEX;
			bg_tiles[ii].empty = 0;
		} else {
			tile = white_INDEX;
			bg_tiles[ii].empty = 1;
		}
		bg_tiles[ii].tile = tile;//Fill with random data.
		pse[se_index(ii & 63, (ii & 0xFFFFC0) >> 6, 64)] = (SCR_ENTRY)(tile);
		//if (tile == candle_INDEX) addCandle(ii & 63, ii & ~63);//Add candle to candle list.
	}
}

BG_POINT background_offset(int x, int y)
{
	//If the player gets too close to the edges, cap scrolling.
	if (x < 0) x = 0;
	else if (x >= BWIDTH - DWIDTH) x = BWIDTH - DWIDTH;
	if (y < 0) y = 0;
	else if (y >= BHEIGHT - DHEIGHT) y = BHEIGHT - DHEIGHT;
	bg0_pt.x = (s16)x;
	bg0_pt.y = (s16)y;
	REG_BG_OFS[0]= bg0_pt;	// write new position
	return bg0_pt;
}
#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "types.h"
#include "toolbox.h"

#define BWIDTH 512
#define BHEIGHT 512

typedef struct TileType 
{
	u16 tile;
	u16 empty;
} TileType;

extern SCR_ENTRY *bg0_map;
extern BG_POINT bg0_pt;
extern TileType bg_tiles[4096];

void background_init();
BG_POINT background_offset();

#endif

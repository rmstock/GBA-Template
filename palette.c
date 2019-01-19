

#include "toolbox.h"
#include "palette.h"

//#include <stdio.h>

#define RED_RANGE 6
#define GRN_RANGE 7
#define BLU_RANGE 6

u32 redSkip = 51;//255 / (RED_RANGE - 1);
u32 grnSkip = 42;//255 / (GRN_RANGE - 1);
u32 bluSkip = 51;//255 / (BLU_RANGE - 1);

void palette_init()
{
    memcpy32(pal_bg_mem, palette_mem, 128);
	memcpy32(pal_obj_mem, palette_mem, 128);
}

const unsigned int palette_mem[128] =
{
	0x00000000,
    0x00060000,
0x0013000c,
0x001f0019,
0x00a600a0,
0x00b300ac,
0x00bf00b9,
0x01460140,
0x0153014c,
0x015f0159,
0x01e601e0,
0x01f301ec,
0x01ff01f9,
0x02a602a0,
0x02b302ac,
0x02bf02b9,
0x03460340,
0x0353034c,
0x035f0359,
0x03e603e0,
0x03f303ec,
0x03ff03f9,
0x18061800,
0x1813180c,
0x181f1819,
0x18a618a0,
0x18b318ac,
0x18bf18b9,
0x19461940,
0x1953194c,
0x195f1959,
0x19e619e0,
0x19f319ec,
0x19ff19f9,
0x1aa61aa0,
0x1ab31aac,
0x1abf1ab9,
0x1b461b40,
0x1b531b4c,
0x1b5f1b59,
0x1be61be0,
0x1bf31bec,
0x1bff1bf9,
0x30063000,
0x3013300c,
0x301f3019,
0x30a630a0,
0x30b330ac,
0x30bf30b9,
0x31463140,
0x3153314c,
0x315f3159,
0x31e631e0,
0x31f331ec,
0x31ff31f9,
0x32a632a0,
0x32b332ac,
0x32bf32b9,
0x33463340,
0x3353334c,
0x335f3359,
0x33e633e0,
0x33f333ec,
0x33ff33f9,
0x4c064c00,
0x4c134c0c,
0x4c1f4c19,
0x4ca64ca0,
0x4cb34cac,
0x4cbf4cb9,
0x4d464d40,
0x4d534d4c,
0x4d5f4d59,
0x4de64de0,
0x4df34dec,
0x4dff4df9,
0x4ea64ea0,
0x4eb34eac,
0x4ebf4eb9,
0x4f464f40,
0x4f534f4c,
0x4f5f4f59,
0x4fe64fe0,
0x4ff34fec,
0x4fff4ff9,
0x64066400,
0x6413640c,
0x641f6419,
0x64a664a0,
0x64b364ac,
0x64bf64b9,
0x65466540,
0x6553654c,
0x655f6559,
0x65e665e0,
0x65f365ec,
0x65ff65f9,
0x66a666a0,
0x66b366ac,
0x66bf66b9,
0x67466740,
0x6753674c,
0x675f6759,
0x67e667e0,
0x67f367ec,
0x67ff67f9,
0x7c067c00,
0x7c137c0c,
0x7c1f7c19,
0x7ca67ca0,
0x7cb37cac,
0x7cbf7cb9,
0x7d467d40,
0x7d537d4c,
0x7d5f7d59,
0x7de67de0,
0x7df37dec,
0x7dff7df9,
0x7ea67ea0,
0x7eb37eac,
0x7ebf7eb9,
0x7f467f40,
0x7f537f4c,
0x7f5f7f59,
0x7fe67fe0,
0x7ff37fec,
0x7fff7ff9,
0x00000000,
};

/*void generatePalette()
{
	u32 red = 0, green = 0, blue = 0;
	u32 index = 2;
	for (int b = 0; b < BLU_RANGE; b++)
	{
		for (int g = 0; g < GRN_RANGE; g++)
		{
			for (int r = 0; r < RED_RANGE; r++)
			{
				pal_bg_mem[index] = (COLOR)(red >> 3 | ((green << 2) & 0b1111100000) | ((blue << 7) & 0b111110000000000));
				red += redSkip;
				index++;
			}
			green += grnSkip;
			red = 0;
		}
		blue += bluSkip;
		green = 0;
	}
	pal_bg_mem[252] = 0xFFFF;
	pal_bg_mem[253] = 0x4210;
}*/

//FILE *opf;

//void main()
//{
//	generatePalette();
//	opf = fopen("my.pal", "w");
//	for(int i = 0; i < 128; i++)
//	{
//		fprintf(opf,"0x%08x\n", pal2[i]); //pal2[i+1], pal2[i+2], pal2[i+3]);
//	}
//	fclose(opf);
//}

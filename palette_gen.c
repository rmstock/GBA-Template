

//#include "toolbox.h"
#include "palette_gen.h"

#include <stdio.h>

#define RED_RANGE 6
#define GRN_RANGE 7
#define BLU_RANGE 6

unsigned int redSkip = 51;//255 / (RED_RANGE - 1);
unsigned int grnSkip = 42;//255 / (GRN_RANGE - 1);
unsigned int bluSkip = 51;//255 / (BLU_RANGE - 1);
unsigned short pal[256];

//0BBBBBGGGGGRRRRR

void generatePalette()
{
	unsigned int red = 0, green = 0, blue = 0;
	int index = 2;
	for (int b = 0; b < BLU_RANGE; b++)
	{
		for (int g = 0; g < GRN_RANGE; g++)
		{
			for (int r = 0; r < RED_RANGE; r++)
			{
				pal[index] = red >> 3 | ((green << 2) & 0b1111100000) | ((blue << 7) & 0b111110000000000);
				red += redSkip;
				index++;
			}
			green += grnSkip;
			red = 0;
		}
		blue += bluSkip;
		green = 0;
	}
}

FILE *opf;

void main()
{
	generatePalette();
	opf = fopen("my.pal", "w");
	unsigned int * pal2 = (unsigned int *)pal;
	for(int i = 0; i < 128; i++)
	{
		fprintf(opf,"0x%08x\n", pal2[i]); //pal2[i+1], pal2[i+2], pal2[i+3]);
	}
	fclose(opf);
}
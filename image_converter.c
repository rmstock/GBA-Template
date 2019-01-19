#include "image_converter.h"

#include "bmpread.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char* palette_file;
int start;
char** image_names;
char* fileName;
unsigned char* rgb_palette;//256 * 3 values of 5 bits each shifted up 2;
image* images;
int count;
int ind = 0;

void read_palette()
{
	FILE* file = fopen(palette_file, "r");
	if (!file)
	{
		printf("Palette file not found at %s.\n", palette_file);
		exit(1);
	}
    size_t maxlength = 300;
	char* line = malloc(maxlength + 1);
	int length;
    int lineNum = 0;
	while (length = getline(&line, &maxlength, file))//300 seems like a long enough line.
	{
        lineNum++;
        if (length != 11)
            break;
        //printf("Line Number: %d\n", lineNum);
		int compound = (int)strtol(line, NULL, 0);
		//These values are two 15 bit values together in this bit pattern.
		//0b0bbbbbgggggrrrrr0bbbbbgggggrrrrr with the lower byte being first;
		int r1 = compound & 0x1F;
		int g1 = (compound >> 5) & 0x1F;
		int b1 = (compound >> 10) & 0x1F;
		int r2 = (compound >> 16) & 0x1F;
		int g2 = (compound >> 21) & 0x1F;
		int b2 = (compound >> 26) & 0x1F;
		//I want these values to be compared to 8 bit colors, so I need to shift them up.
		rgb_palette[ind++] = r1 << 3;
		rgb_palette[ind++] = g1 << 3;
		rgb_palette[ind++] = b1 << 3;
		rgb_palette[ind++] = r2 << 3;
		rgb_palette[ind++] = g2 << 3;
		rgb_palette[ind++] = b2 << 3;
	}
}

void read_image(int number)
{
    bmpread_t bitmap;

	if (!bmpread(image_names[number], 0, &bitmap))
	{
		printf("Image file not found at %s.\n",image_names[number]);
		exit(1);
	}
	int sizeX3 = bitmap.width * bitmap.height * 3;
	images[number].name = image_names[number];
	images[number].size = sizeX3 / 3;
	if(images[number].size != 64)
	{
		printf("We can't handle non-8x8 data right now.\n");
		exit(1);
	}
	images[number].indexs = malloc(sizeof(char) * images[number].size);
	for (int i = 0; i < sizeX3; i+=3)
	{
		int red = bitmap.data[i];
		int green = bitmap.data[i + 1];
		int blue = bitmap.data[i + 2];
		if (red && blue == 255 && green == 0)
		{
			images[number].indexs[63 - i/3] = 0;
			continue;
		}
		float distance = 256;//large value;
		int closest = 2;
		for (int j = 6; j < 256 * 3; j += 3)
		{
			int pRed = rgb_palette[j];
			int pGreen = rgb_palette[j + 1];
			int pBlue = rgb_palette[j+2];
			int diffR = pRed - red;
			int diffB = pBlue - blue;
			int diffG = pGreen - green;
			float dist = sqrt(diffR * diffR + diffG * diffG + diffB * diffB);
			if (dist < distance)
			{
				distance = dist;
				closest = j / 3;
			}
		}
        images[number].indexs[63 - i / 3] = closest;
	}
}

void make_header()
{
	int len = strlen(fileName) + 3;//.h\0
	char fname[len];
	strcpy(fname, fileName);
	strcat(fname, ".h");
	FILE *header;
	header = fopen(fname, "w");
	if(header)
	{
		fprintf(header, "#ifndef %s_HEADER\n", fileName);
		fprintf(header, "#define %s_HEADER\n", fileName);
		
		fprintf(header, "extern const unsigned char %s_Tiles[%d];\n", fileName, count * 64);
		fprintf(header, "#define %s_COUNT %d\n", fileName, count);
		int offset = 0;
		for (int i = 0; i < count; i++)
		{
			char* minusExt;
			char* lastdot;
			minusExt = malloc(strlen(images[i].name) + 1);
			strcpy (minusExt, images[i].name);
			lastdot = strrchr(minusExt, '.');
			*lastdot = '\0';
			fprintf(header, "#define %s_OFFSET %d\n", minusExt, offset);
			offset +=  images[i].size;
			fprintf(header, "#define %s_INDEX %d\n", minusExt, i + start);
			free(minusExt);
		}

		fprintf(header, "#endif\n");
	}
	fclose(header);
}

void make_data()
{
	int len = strlen(fileName) + 3;//.h\0
	char fname[len];
	char hname[len];
	strcpy(fname, fileName);
	strcpy(hname, fileName);
	strcat(fname, ".c");
	strcat(hname,".h");
	FILE *data;
	data = fopen(fname, "w");
	if(data)
	{
		fprintf(data, "#include \"%s\"\n", hname);
		fprintf(data, "const unsigned char %s_Tiles[%d] = {\n", fileName, count * 64);
		int* array;
		for (int i = 0; i < count; i++)
		{
			for (int j = 0; j < 64; j++)
			{
				fprintf(data, "0x%02x,\n", images[i].indexs[j]);
			}
		}

		fprintf(data, "};");
	}
	fclose(data);
}

int main(int argc, char **argv)
{
	if (argc < 5)
	{
		printf("Usage: image_converter.exe fileName index_start palette.cfg <image1.png> [image2.png etc.]\n");
		if (argc == 1)
        {
            printf("Using defaults.\n");
            fileName = "grass";
            start = 1;
            palette_file = "my.pal";
            image_names = malloc(sizeof(char*));
            image_names[0] = malloc(10);
            strcpy(image_names[0], "grass.bmp");
            images = malloc(sizeof(image));
            count = 1;
        } else {
            exit(1);
        }
	} else {
        palette_file = argv[3];
        start = atoi(argv[2]);
        fileName = argv[1];
        image_names = &argv[4];
        images = malloc(sizeof(image) * argc - 3);
        count = argc - 4;
    }
    rgb_palette = malloc(256*3);//rbg*256 entries
	read_palette();
    if (argc > 4)
    {
        for (int i = 4; i < argc; i++)
        {
            read_image(i - 4);
        }
    } else if (argc == 1)
    {
        read_image(0);
    }
	make_header();
	make_data();
}

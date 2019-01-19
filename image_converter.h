
#ifndef IMAGE_CONVERTER_H
#define IMAGE_CONVERTER_H

typedef struct imagetag
{
	char* name;
	int size;
	unsigned char* indexs;//index into 256 palette
} image;

typedef struct tagcolor24
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
} color24;

#endif
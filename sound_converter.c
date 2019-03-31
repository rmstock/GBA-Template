#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

struct WAVE_HEADER{
    char Chunk[4];
    int ChunkSize;
    char format[4];
    char Sub_chunk1ID[4];
    int Sub_chunk1Size;
    short int AudioFormat;
    short int NumChannels;
    int SampleRate;
    int ByteRate;
    short int BlockAlign;
    short int BitsPerSample;
}WAVE_HEADER;

short int* file_data;
unsigned int file_length;
char* simple_name;

struct WAVE_HEADER waveheader;

void addTriangeNoise() {
	const int total_area = 128 * 129; //1+2+3... 1-128 * 2. Magic Number!
	const int half_area = total_area / 2;
	srand(time(0));
	for (int i = 0; i < file_length / 2; i++) {
		int random = rand() % total_area + 1; 	//Number between 1 and 
												//area inclusive
		if (random > half_area) {
			//Upper half;
			//Need to flip our area number, and make total_area -1 == 1;
			random = total_area - random;
			int lower = sqrt(random);
			int bound = (lower * (lower + 1))/ 2;
			if (random >= bound) {
				lower++;
			}
			// 1 = 127
			// 2 = 126
			//printf("%d\n", file_data[i]);
			file_data[i] += 128 - lower;
			//printf("%d\n", file_data[i]);
		} else {
			//Lower half;
			//1 = -128;
			int lower = sqrt(random);
			int bound = (lower * (lower + 1))/ 2;
			if (random >= bound) {
				lower++;
			}
			//printf("%d\n", file_data[i]);
			file_data[i] += -129 + lower;//
			//printf("%d\n", file_data[i]);
		}
		//printf("%d\n", file_data[i]);
	}
}

void make_header() {
	FILE *header;
	
	int filename_length = strlen(simple_name) + 3;//.h\0
	char file_name[filename_length];
	strcpy(file_name, simple_name);
	strcat(file_name, ".h");
	header = fopen(file_name, "w");
	if (header) {
		fprintf(header, "#ifndef %s_HEADER\n", simple_name);
		fprintf(header, "#define %s_HEADER\n", simple_name);
		
		fprintf(header, "extern const signed char %s_DATA[%d];\n", simple_name, file_length / 2);
		fprintf(header, "#define %s_LENGTH %d\n", simple_name, file_length / 2);

		fprintf(header, "#endif\n");
	}
	fclose(header);
}

void make_data()
{
	int len = strlen(simple_name) + 3;//.h\0
	char fname[len];
	char hname[len];
	strcpy(fname, simple_name);
	strcpy(hname, simple_name);
	strcat(fname, ".c");
	strcat(hname, ".h");
	FILE *data;
	data = fopen(fname, "w");
	if(data)
	{
		fprintf(data, "#include \"%s\"\n", hname);
		fprintf(data, "const signed char %s_DATA[%d] = {\n", simple_name, file_length / 2);
		for (int j = 0; j < file_length / 2; j++)
		{
			signed char value = file_data[j] >> 8;
			fprintf(data, "%d,\n", value);
			//printf("%d\n", value);
		}

		fprintf(data, "};");
	}
	fclose(data);
}

int main(int argc, char** argv){
	if (argc != 3) {
		printf("Usage: sound_converter.exe output_file_without_extension music_file.wav\n");
		exit(1);
	}
	FILE *sound;
	
	sound = fopen(argv[2],"r");
	if (!sound) {
		printf("Couldn't open %s\n", argv[2]);
		exit(1);
	}
	
	simple_name = argv[1];
	//char D;
	fread(&waveheader,sizeof(waveheader),1,sound);
	printf("BitsPerSample : %d\n", waveheader.BitsPerSample);
	//TODO
	//Sub_chunk2Size is located at 0x50 or byte 80 for NO REASON!
	//Data Begins 2 bytes later. I'm not sure why I have this extra data,
	// but I'll try to kill it.
	//printf("Byte Count: %X\n", waveheader.Sub_chunk2Size);
	
	//I could search for the DATA section by checking SubchunkSize1 and some 
	//math, but this should work too.
	char D;
	int found = 0;
	while (!found) {
		fread(&D, 1, 1, sound);
		if (D == 'd'){
			fread(&D, 1, 1, sound);
			if (D == 'a') {
				fread(&D, 1, 1, sound);
				if (D == 't') {
					fread(&D, 1, 1, sound);
					if (D == 'a') {
						found = 1;
					}
				}
			}
		}
	};
	//file_length = waveheader.Sub_chunk2Size;
	fread(&file_length, 4, 1, sound);
	file_data = malloc(file_length);
	fread(file_data,file_length,1,sound);
	addTriangeNoise();
	make_header();
	make_data();
	fclose(sound);
}
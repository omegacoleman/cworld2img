#include "FreeImage.h"
#include "toksin.hpp"
#include <stdio.h>

RGBQUAD qpixel_air = {255, 255, 255, 255};
RGBQUAD qpixel_dirt = {0, 0, 0, 255};
RGBQUAD qpixel_unknown = {0, 0, 255, 255};

world c_world;

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("Usage : cworld2img input_filename.bin output_filename.png\n\n");
		return 0;
	}
	FreeImage_Initialise();
	FIBITMAP *bitmap = FreeImage_Allocate(WORLD_WIDTH, WORLD_HEIGHT, 32);
	if(!bitmap)
	{
		printf("Error while allocating image. Aborting");
		return -1;
	}
	FILE *fd = fopen(argv[1], "rb");
	fread(c_world.solids, sizeof(block), WORLD_HEIGHT * WORLD_WIDTH, fd);
	fclose(fd);
	for(int i = 0; i < WORLD_HEIGHT; i++)
	{
		for(int j = 0; j < WORLD_WIDTH; j++)
		{
			switch(c_world.solids[WORLD_WIDTH * i + j])
			{
			case BLCK_AIR:
				FreeImage_SetPixelColor(bitmap, j, WORLD_HEIGHT - i, &qpixel_air);break;
			case BLCK_DIRT:
				FreeImage_SetPixelColor(bitmap, j, WORLD_HEIGHT - i, &qpixel_dirt);break;
			default:
				FreeImage_SetPixelColor(bitmap, j, WORLD_HEIGHT - i, &qpixel_unknown);break;
			}
		}
	}
	if(!FreeImage_Save(FIF_PNG, bitmap, argv[2], 0))
	{
		printf("Error while saving image. Aborting");
		return -1;
	}
	FreeImage_DeInitialise();
	return 0;
}
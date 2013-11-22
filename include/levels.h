#ifndef LEVELS_H
#define LEVELS_H

#define MAPSIZE

typedef struct
{
	u16		 width;
	u16		 height;
	s16		*maplayout;
	u16		 footersize;
	u16		 numberOfEntrypoints;
	s16		*entrypointList;

} level;


// Include binary files:


//Binary files for level "test":

	#include "test_level_bin.h"
	#include "test_MAP_BG0_00_00_bin.h"
	#include "test_MAP_BG0_00_01_bin.h"
	#include "test_MAP_BG0_00_02_bin.h"
	#include "test_MAP_BG0_00_03_bin.h"
	#include "test_MAP_BG0_01_00_bin.h"
	#include "test_MAP_BG0_01_01_bin.h"
	#include "test_MAP_BG0_01_02_bin.h"
	#include "test_MAP_BG0_01_03_bin.h"
	#include "test_MAP_BG0_02_00_bin.h"
	#include "test_MAP_BG0_02_01_bin.h"
	#include "test_MAP_BG0_02_02_bin.h"
	#include "test_MAP_BG0_02_03_bin.h"
	#include "test_MAP_BG0_03_00_bin.h"
	#include "test_MAP_BG0_03_01_bin.h"
	#include "test_MAP_BG0_03_02_bin.h"
	#include "test_MAP_BG0_03_03_bin.h"
	#include "test_pal_bin.h"
	#include "test_tiles_bin.h"



//Functions:

u16 *lvl_get_mappointers(char *level,u16 x, u16 y)
{


	//If blocks for level "test":

	if ((strcmp(level,"test") == 0) && (x == 0) && (y == 0))
	{
		return (u16*)test_MAP_BG0_00_00_bin;
	}

	if ((strcmp(level,"test") == 0) && (x == 0) && (y == 1))
	{
		return (u16*)test_MAP_BG0_00_01_bin;
	}

	if ((strcmp(level,"test") == 0) && (x == 0) && (y == 2))
	{
		return (u16*)test_MAP_BG0_00_02_bin;
	}

	if ((strcmp(level,"test") == 0) && (x == 0) && (y == 3))
	{
		return (u16*)test_MAP_BG0_00_03_bin;
	}

	if ((strcmp(level,"test") == 0) && (x == 1) && (y == 0))
	{
		return (u16*)test_MAP_BG0_01_00_bin;
	}

	if ((strcmp(level,"test") == 0) && (x == 1) && (y == 1))
	{
		return (u16*)test_MAP_BG0_01_01_bin;
	}

	if ((strcmp(level,"test") == 0) && (x == 1) && (y == 2))
	{
		return (u16*)test_MAP_BG0_01_02_bin;
	}

	if ((strcmp(level,"test") == 0) && (x == 1) && (y == 3))
	{
		return (u16*)test_MAP_BG0_01_03_bin;
	}

	if ((strcmp(level,"test") == 0) && (x == 2) && (y == 0))
	{
		return (u16*)test_MAP_BG0_02_00_bin;
	}

	if ((strcmp(level,"test") == 0) && (x == 2) && (y == 1))
	{
		return (u16*)test_MAP_BG0_02_01_bin;
	}

	if ((strcmp(level,"test") == 0) && (x == 2) && (y == 2))
	{
		return (u16*)test_MAP_BG0_02_02_bin;
	}

	if ((strcmp(level,"test") == 0) && (x == 2) && (y == 3))
	{
		return (u16*)test_MAP_BG0_02_03_bin;
	}

	if ((strcmp(level,"test") == 0) && (x == 3) && (y == 0))
	{
		return (u16*)test_MAP_BG0_03_00_bin;
	}

	if ((strcmp(level,"test") == 0) && (x == 3) && (y == 1))
	{
		return (u16*)test_MAP_BG0_03_01_bin;
	}

	if ((strcmp(level,"test") == 0) && (x == 3) && (y == 2))
	{
		return (u16*)test_MAP_BG0_03_02_bin;
	}

	if ((strcmp(level,"test") == 0) && (x == 3) && (y == 3))
	{
		return (u16*)test_MAP_BG0_03_03_bin;
	}


	//Level not loaded:

	if (strcmp(level,"test") == 0) return (u16*)test_MAP_BG0_00_00_bin;

}//End of function lvl_get_test_mappointers


level lvl_loadLevel(char *levelname)
{
	level rstruct;

		if (strcmp(levelname,"test") == 0)
	{
		rstruct.width                =  test_level_bin[0 * sizeof(u16)];
		rstruct.height               =  test_level_bin[1 * sizeof(u16)];
		rstruct.maplayout            =  (s16*)&test_level_bin[2 * sizeof(s16)];
		rstruct.footersize           =  test_level_bin[(2 + ((rstruct.width) * (rstruct.height))) * sizeof(u16)];
		rstruct.numberOfEntrypoints  =  test_level_bin[(3 + ((rstruct.width) * (rstruct.height))) * sizeof(u16)];
		rstruct.entrypointList       =  (s16*)&test_level_bin[(4 + ((rstruct.width) * (rstruct.height))) * sizeof(s16)];


	//Load level's tileset and palette:

	memcpy((void*)BG_TILE_RAM(2), test_tiles_bin, test_tiles_bin_size);
	memcpy((void*)BG_PALETTE, test_pal_bin, test_pal_bin_size);

		return (rstruct);
	}

	//Level not loaded:

	else

	{
		rstruct.width                =  0;
		rstruct.height               =  0;
		rstruct.maplayout            =  0;
		rstruct.footersize           =  0;
		rstruct.numberOfEntrypoints  =  0;
		rstruct.entrypointList       =  0;

		return (rstruct);
	}

}//End of function lvl_loadLevel

#endif //LEVELS_H

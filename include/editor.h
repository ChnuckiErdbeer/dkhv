#ifndef editor_H
#define editor_H

//FUNCTION PROTOTYPES:

void ed_startEditor(void);


void ed_startEditor(void)
{
    consoleDemoInit();



//    memcpy((void*)BG_TILE_RAM(1), m1024x1024Tiles_bin, m1024x1024Tiles_bin_size);

	//memcpy((void*)BG_MAP_RAM(3), m1024x1024Map_bin, m1024x1024Map_bin_size);

//memcpy((void*)BG_PALETTE, m1024x1024Pal_bin, m1024x1024Pal_bin_size);

    while(1)
    {
        swiWaitForVBlank();
    }



}


#endif // editor_H

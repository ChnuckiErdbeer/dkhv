// Including libnds’ set of defines
#include <nds.h>

// Icluding standard c headers:
#include <stdio.h>

// Including my own headers:
#include "vector.h"
#include "tools.h"
#include "debug.h"
#include "error.h"
#include "cam.h"
#include "editor.h"

// Include level data:

#include "levels.h"

#define current_gfxset protoC:\devkitPro\##projects\dsgame\##LEVELS\##TILESETS\test.png

#define LAYER0 0x0
#define LAYER1 0x1
#define LAYER2 0x1 << 1
#define LAYEr3 0x1 << 2

#define TL    0
#define TR 1024
#define BL 2048
#define BR 3072

#define CAM_POS vec_Sum(scrollPos,cenOffset)

int main()
{
    //Set Video mode to MODE_2_2D and activate BG0:

    REG_DISPCNT = MODE_0_2D | DISPLAY_BG0_ACTIVE;
	REG_BG0CNT = BG_64x64 | BG_COLOR_256 | BG_MAP_BASE(1) | BG_TILE_BASE(4);

    // Set VRAM bank A for background display:

    VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;

    //ed_startEditor();

    //Copy tiles, map and palette to VRAM:

    memcpy((void*)BG_TILE_RAM(4), sieben_tiles_bin, sieben_tiles_bin_size);

	memcpy((void*)(BG_MAP_RAM(1) + TL),sieben_map0_bin, sieben_map0_bin_size);
	memcpy((void*)(BG_MAP_RAM(1) + TR),sieben_map0_bin, sieben_map0_bin_size);
	memcpy((void*)(BG_MAP_RAM(1) + BL),sieben_map0_bin, sieben_map0_bin_size);
	memcpy((void*)(BG_MAP_RAM(1) + BR),sieben_map0_bin, sieben_map0_bin_size);


	memcpy((void*)BG_PALETTE, gnade_pal_bin, gnade_pal_bin_size);






    consoleDemoInit();




    vec_2d          scrollPos = {0,0};

    vec_2d          camMagnet = {128,96};

    vec_2d          scrollDirection = {0,0};

    u8              cam_speed = 5;

    s16             i;




//MAIN LOOP:

    while(1){

        // COMPUTE PLAYER INPUT:
        scanKeys();
        touchPosition touch;

        int held = keysHeld();

        if (held & KEY_LEFT)    camMagnet.x--;
        if (held & KEY_RIGHT)   camMagnet.x++;
        if (held & KEY_UP)      camMagnet.y--;
        if (held & KEY_DOWN)    camMagnet.y++;
        if (held & KEY_TOUCH)
        {
            touchRead(&touch);
            camMagnet.x = touch.px;
            camMagnet.y = touch.py;

        }

        //MOVE CAMERA:


        if (vec_Len(vec_Dif(CAM_POS,camMagnet)) > (CAM_MAX_SPEED))          //If camMagnet is more than CAM_MAX_SPEED steps away:
        {
            if (cam_speed < CAM_MAX_SPEED) cam_speed++;                     //Increase cam_speed until it hits CAM_MAX_SPEED.
        }

        if (vec_Len(vec_Dif(CAM_POS,camMagnet)) < (CAM_MAX_SPEED))          //If camMagnet is less than CAM_MAX_SPEED steps away:
        {
            if (cam_speed > 0) cam_speed--;                                 //Decrease cam_speed until it hits 0.
        }


        for(i = 0; i < cam_speed; i++)                                      //Move the cam for cam_speed steps.
        {
            if (vec_Null(scrollDirection))                                  //If scrollDirection is 0 while the destination has not yet been reached:
            {
                scrollDirection = bresSeg(CAM_POS,camMagnet);               //Set scrollDirection to the next Bresenham-segment. (See tools.h st: #bresseg)
            }

            scrollDirection = vec_taxi(&scrollPos,scrollDirection);         //Move camera one step towards camMagnet.
        }

        //Write the data to the scroll register.
        printf("scrollPos.x: %i\n",scrollPos.x>>8);
        printf("scrollPos.y: %i\n",scrollPos.y>>8);

        if (scrollPos.y >> 8 == -92)
        {
            memcpy((void*)(BG_MAP_RAM(1) + BL),drei_map0_bin, drei_map0_bin_size);
        }

        if (scrollPos.y == -91)
        {
            memcpy((void*)(BG_MAP_RAM(1) + BL),vier_map0_bin, vier_map0_bin_size);
        }

		REG_BG0HOFS = scrollPos.x;
        REG_BG0VOFS = scrollPos.y;

        swiWaitForVBlank();
        consoleClear();
};



    return(0);
}

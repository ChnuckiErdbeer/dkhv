// Include libnds’ set of defines
#include <nds.h>

// Include standard c headers:
#include <stdio.h>

// Global defines:
#define current_gfxset protoC:\devkitPro\##projects\dsgame\##LEVELS\##TILESETS\test.png

#define LAYER0 0x0
#define LAYER1 0x1
#define LAYER2 0x1 << 1
#define LAYEr3 0x1 << 2


#define TL 0b00
#define TR 0b01
#define BL 0b10
#define BR 0b11

#define CAM_POS vec_Sum(scrollPos,cenOffset)


// Include my own headers:
#include "vector.h"
#include "tools.h"
#include "debug.h"
#include "error.h"
#include "cam.h"
#include "editor.h"

// Include level data:

#include "levels.h"





int main()
{
    //Set Video mode to MODE_2_2D and activate BG0:

    REG_DISPCNT = MODE_0_2D | DISPLAY_BG0_ACTIVE;
	REG_BG0CNT = BG_64x64 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(2);

    // Set VRAM bank A for background display:

    VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;




    //Load level:

    char current_level_name[128] = "test";


    level current_level;

    current_level = lvl_loadLevel(current_level_name);



    consoleDemoInit();

    ;






    //Copy maps to VRAM:

    map_2x2 quadrants;

    quadrants.tl.x = 0;
    quadrants.tl.y = 0;

    quadrants.bl.x = 0;
    quadrants.bl.y = 1;

    quadrants.tr.x = 1;
    quadrants.tr.y = 0;

    quadrants.br.x = 1;
    quadrants.br.y = 1;



    memcpy((void*)(BG_MAP_RAM(0) + (1024 * TL)),lvl_get_mappointers(current_level_name,quadrants.tl.x,quadrants.tl.y), 2048);
    memcpy((void*)(BG_MAP_RAM(0) + (1024 * BL)),lvl_get_mappointers(current_level_name,quadrants.bl.x,quadrants.bl.y), 2048);
    memcpy((void*)(BG_MAP_RAM(0) + (1024 * TR)),lvl_get_mappointers(current_level_name,quadrants.tr.x,quadrants.tr.y), 2048);
    memcpy((void*)(BG_MAP_RAM(0) + (1024 * BR)),lvl_get_mappointers(current_level_name,quadrants.br.x,quadrants.br.y), 2048);




    vec_2d          scrollPos = {0,0};

    vec_2d          camMagnet = {128,96};

    vec_2d          scrollDirection = {0,0};

    u8              cam_speed = 5;

    s16             i;

    u16             current_quadrant = TL;

    vec_2d          previous_scrollPos  = {scrollPos.x, scrollPos.y};


//MAIN LOOP:

    //cam_update_quadrants(current_level_name,scrollPos,previous_scrollPos);

//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv





//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^






    while(1){

        // COMPUTE PLAYER INPUT:
        scanKeys();


        int down = keysDown();

        if (down & KEY_LEFT)    camMagnet.x-=256;
        if (down & KEY_RIGHT)   camMagnet.x+=256;
        if (down & KEY_UP)      camMagnet.y-=256;
        if (down & KEY_DOWN)    camMagnet.y+=256;


//        int held = keysHeld();
//
//        if (held & KEY_LEFT)    camMagnet.x-=1;
//        if (held & KEY_RIGHT)   camMagnet.x+=1;
//        if (held & KEY_UP)      camMagnet.y-=1;
//        if (held & KEY_DOWN)    camMagnet.y+=1;

//        touchPosition touch;

//        if (held & KEY_TOUCH)
//        {
//            touchRead(&touch);
//            camMagnet.x = touch.px;
//            camMagnet.y = touch.py;
//
//        }

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



        current_quadrant = (isOdd(scrollPos.x >> 8)) | (isOdd(scrollPos.y >> 8) << 1);

        quadrants = cam_update_quadrants(current_level_name,quadrants,scrollPos,previous_scrollPos);


		REG_BG0HOFS = scrollPos.x;
        REG_BG0VOFS = scrollPos.y;

        previous_scrollPos = scrollPos;


        //deb_waitforbutton("VBLANK");
        swiWaitForVBlank();

        consoleClear();
};



    return(0);
}

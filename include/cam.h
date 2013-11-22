//╔═══════════╗
//║ C A M . H ║═════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗
//╠═══════════╝                                                                                                                 ║
//║                                                                                                                             ║
//║     Camera engine.                                                                                                          ║
//║                                                                                                                             ║
//╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝

#ifndef CAM_H
#define CAM_H

#include "vector.h"
#include "tools.h"
#include "levels.h"

#define CAM_SPEED 5             //In pixels/v-ram-cycles.
#define CAM_ACC 10              //Linear acceleration. In increases/v-ram-cycles.
#define CAM_DEC 5               //Linear deceleration. In decreases/v-ram-cycles.
#define CAM_X_OFFSET 128
#define CAM_Y_OFFSET 96

#define SCREEN_MIDX 128
#define SCREEN_MIDY 96

#define CAM_MAX_SPEED 10

#define QXFL(n)  (n ^ 1)
#define QYFL(n)  (n ^ 1 << 1)
#define QXYFL(n) (n ^ 0b11)



typedef struct
{
	vec_2d	tl;
	vec_2d	bl;
	vec_2d	tr;
	vec_2d	br;

}map_2x2;



const vec_2d    cenOffset= {128,96};

//FUNCTION PROTOTYPES:

map_2x2  cam_update_quadrants(                          //(st: upd_quad)      Checks which quadrants have to be updated and updates them.
                              char *levelname,
                              map_2x2 old_quadrant_map,
                              vec_2d current_pos,
                              vec_2d previous_pos
                             );

void     cam_det_quad_seq(                              //(st: det_quad_seq)   Sets the sequence of the quadrants seen from current position.
                          u16 quadrat_sequence[4],
                          s16 current_quadrant
                         );

//FUNCTIONS:



//╔══════════╤═══════════════════════╗
//║ FUNCTION │ cam_update_quadrants: ╠═════════════════════════════════════════════════════════════════════════════════#upd_quad╗
//║··········└───────────────────────╜                                                                                          ║
//║                                                                                                                             ║
//║  Checks if new maps have to be loaded to the quadrants and loads them if so.                                                ║
//║                                                                                                                             ║
//║  Arguments:                                                                                                                 ║
//║                                                                                                                             ║
//║                                                                                                                             ║
//║  char   *levelname          (the name of the current level)                                                                 ║
//║  map2x2 old_quadrant_map    (wich quarter contains wich map. (should be updated by this function!))                         ║
//║  vec_2d current_pos         (the current camera position (not rendered yet)                                                 ║
//║  vec_2d previous_pos        (the last camera position(rendered yet)                                                         ║
//║                                                                                                                             ║
//║  Return:                                                                                                                    ║
//║                                                                                                                             ║
//║  Returns an updated version of the transfered old_quadrant_map. This function is meaned to be used once per vram-cycle      ║
//║  to update an existing map_2x2.                                                                                             ║
//╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝
map_2x2 cam_update_quadrants(char *levelname,map_2x2 old_quadrant_map,vec_2d current_pos, vec_2d previous_pos)
{
    s16     current_quadrant  = (isOdd(current_pos.x  >> 8)) | (isOdd(current_pos.y  >> 8) << 1);
    s16     previous_quadrant = (isOdd(previous_pos.x >> 8)) | (isOdd(previous_pos.y >> 8) << 1);

    vec_2d  current_map;
    current_map.x = (current_pos.x >> 8);
    current_map.y = (current_pos.y >> 8);

    vec_2d  previous_map;
    previous_map.x = (previous_pos.x >> 8);
    previous_map.y = (previous_pos.y >> 8);


    u16 *quadrant_sequence;
    quadrant_sequence = malloc(4 * sizeof(u16));

    cam_det_quad_seq(quadrant_sequence, current_quadrant);


    //Build new quadrant map:

    map_2x2 quadrant_map;

    int i;

    for (i = 0; i < 4; i++)
    {
        if (quadrant_sequence[i] == TL)
        {
            quadrant_map.tl.x = current_map.x +  (i & 0b01);
            quadrant_map.tl.y = current_map.y + ((i & 0b10) >> 1);
        }

        if (quadrant_sequence[i] == TR)
        {
            quadrant_map.tr.x = current_map.x +  (i & 0b01);
            quadrant_map.tr.y = current_map.y + ((i & 0b10) >> 1);
        }

        if (quadrant_sequence[i] == BL)
        {
            quadrant_map.bl.x = current_map.x +  (i & 0b01);
            quadrant_map.bl.y = current_map.y + ((i & 0b10) >> 1);
        }

        if (quadrant_sequence[i] == BR)
        {
            quadrant_map.br.x = current_map.x +  (i & 0b01);
            quadrant_map.br.y = current_map.y + ((i & 0b10) >> 1);
        }
    }

    free (quadrant_sequence);

    // Check whether visible maps must be updated and update if so:

    if (!vec_Eq(quadrant_map.tl,old_quadrant_map.tl))
    {
         memcpy
         (
            (void*)(BG_MAP_RAM(0) + (1024 * TL))
            ,
            lvl_get_mappointers
            (
                levelname
                ,
                quadrant_map.tl.x
                ,
                quadrant_map.tl.y
            )
          ,
          2048
        );
    }

     if (!vec_Eq(quadrant_map.tr,old_quadrant_map.tr))
    {
         memcpy
         (
            (void*)(BG_MAP_RAM(0) + (1024 * TR))
            ,
            lvl_get_mappointers
            (
                levelname
                ,
                quadrant_map.tr.x
                ,
                quadrant_map.tr.y
            )
          ,
          2048
        );
    }

    if (!vec_Eq(quadrant_map.bl,old_quadrant_map.bl))
    {
         memcpy
         (
            (void*)(BG_MAP_RAM(0) + (1024 * BL))
            ,
            lvl_get_mappointers
            (
                levelname
                ,
                quadrant_map.bl.x
                ,
                quadrant_map.bl.y
            )
          ,
          2048
        );
    }

    if (!vec_Eq(quadrant_map.br,old_quadrant_map.br))
    {
         memcpy
         (
            (void*)(BG_MAP_RAM(0) + (1024 * BR))
            ,
            lvl_get_mappointers
            (
                levelname
                ,
                quadrant_map.br.x
                ,
                quadrant_map.br.y
            )
          ,
          2048
        );
    }

    return (quadrant_map);

}

//╔══════════╤═══════════════════╗
//║ FUNCTION │ cam_det_quad_seq: ╠═════════════════════════════════════════════════════════════════════════════════#det_quad_seq╗
//║··········└───────────────────╜                                                                                              ║
//║                                                                                                                             ║
//║  Sets the sequence of the quadrants seen from current position.                                                             ║
//║                                                                                                                             ║
//║  Arguments:                                                                                                                 ║
//║                                                                                                                             ║
//║  u16 *quadrant_sequence     (pointer to array of four u16s wich will be filled with the corresponding                       ║
//║                              quadrants identifiers.)                                                                        ║
//║                                                                                                                             ║
//║  s16  current_quadrant      (The quadrant containing the top left pixel of the screen)                                      ║
//║                                                                                                                             ║
//║  Return:                                                                                                                    ║
//║                                                                                                                             ║
//║  Updates the value at "quadrat_sequence". Refers quadrants TL TR BL BR to the sequence they appear on screen.               ║
//║                                                                                                                             ║
//╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝
void cam_det_quad_seq(u16 *quadrant_sequence,s16 current_quadrant)
{

    if (current_quadrant == TL)
    {
        quadrant_sequence[0] = TL;
        quadrant_sequence[1] = TR;
        quadrant_sequence[2] = BL;
        quadrant_sequence[3] = BR;
    }

    if (current_quadrant == TR)
    {

        quadrant_sequence[0] = TR;
        quadrant_sequence[1] = TL;
        quadrant_sequence[2] = BR;
        quadrant_sequence[3] = BL;
    }

    if (current_quadrant == BL)
    {
        quadrant_sequence[0] = BL;
        quadrant_sequence[1] = BR;
        quadrant_sequence[2] = TL;
        quadrant_sequence[3] = TR;
    }

    if (current_quadrant == BR)
    {
        quadrant_sequence[0] = BR;
        quadrant_sequence[1] = BL;
        quadrant_sequence[2] = TR;
        quadrant_sequence[3] = TL;
    }

}

#endif // CAM_H

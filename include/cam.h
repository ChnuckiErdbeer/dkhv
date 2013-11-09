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

#define CAM_SPEED 5             //In pixels/v-ram-cycles.
#define CAM_ACC 10              //Linear acceleration. In increases/v-ram-cycles.
#define CAM_DEC 5               //Linear deceleration. In decreases/v-ram-cycles.
#define CAM_X_OFFSET 128
#define CAM_Y_OFFSET 96

#define SCREEN_MIDX 128
#define SCREEN_MIDY 96

#define CAM_MAX_SPEED 10



const vec_2d    cenOffset= {128,96};

//FUNCTION PROTOTYPES:

//FUNCTIONS:


#endif // CAM_H

//╔═══════════════╗
//║ D E B U G . H ║═════════════════════════════════════════════════════════════════════════════════════════════════════════════╗
//╠═══════════════╝                                                                                                             ║
//║                                                                                                                             ║
//║     Some tools for debugging.                                                                                               ║
//║                                                                                                                             ║
//╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝

#ifndef DEBUG_H
#define DEBUG_H

#include "vector.h"


// FUNCTION PROTOTYPES:

void    deb_printBinary(s16 value);         //(st: pbin)    Prints binary of value to console.
void    deb_waitforbutton();                //(st: wait)    Pauses until button x is pressed.
void    deb_printvec_2d(vec_2d vect);       //(st: pvec)    Prints the coordinates of vector vect to console.


// FUNCTIONS:

void deb_printBinary(s16 value)                                                                                          //#pbin
{
    int pval;
    int i;

    printf("Binary value of %i is:\n",value);

    for (i = 15; i >= 0; i--){

        pval = (value & 0x1 << (i)) >> i;
        printf("%i|",pval);
    }

    printf("\n");
}

void deb_waitforbutton()                                                                                                  //#pwait
{
    while(1)
    {
        scanKeys();

        int held = keysHeld();

        if (held & KEY_X) break;

    }
}

void deb_printvec_2d(vec_2d vect)                                                                                         //#pvec
{
    printf("{%i,%i}", vect.x, vect.y);
}

#endif // DEBUG_H

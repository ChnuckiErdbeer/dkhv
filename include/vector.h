// VECTOR.H
//
// Defines types for 2D/3d vectors and supplys functions to modify them.

#ifndef vector_H
#define vector_H

#include "tools.h"


//TYPES:

typedef s16 vec;

typedef struct{
    vec x;
    vec y;
}vec_2d;

typedef struct{
    vec x;
    vec y;
    vec z;
}vec_3d;


//FUNCTION PROTOTYPES:

vec_2d  vec_3to2d(vec_3d a);                        //(st: 3to2d)   3d to 2d vector conversion.
vec_3d  vec_2to3d(vec_2d a);                        //(st: 2to3d)   2d to 3d vector conversion.

vec_2d  vec_Sum    (vec_2d a, vec_2d v);            //(st: add)     Vector addition.
vec_3d  vec_Sum3d  (vec_3d a, vec_3d v);
vec_3d  vec_Sum2d3d(vec_2d a, vec_3d v);
vec_3d  vec_Sum3d2d(vec_3d a, vec_2d v);

vec_2d  vec_Dif    (vec_2d a, vec_2d b);            //(st: dif)     Vector substraction.
vec_3d  vec_Dif3d  (vec_3d a, vec_3d b);
vec_3d  vec_Dif2d3d(vec_2d a, vec_3d b);
vec_3d  vec_Dif3d2d(vec_3d a, vec_2d b);


vec_2d  vec_Smul  (s16 l,vec_2d a);                 //(st: smul)    Vector scalar-multiplication.
vec_3d  vec_Smul3d(s16 l,vec_3d a);

bool    vec_Eq    (vec_2d a, vec_2d b);             //(st: equal)   Checks wheter two vectors are equal.
bool    vec_Eq3d  (vec_3d a, vec_3d b);
bool    vec_Eq2d3d(vec_2d a, vec_3d b);
bool    vec_Eq3d2d(vec_3d a, vec_2d b);

bool    vec_Null  (vec_2d a);                       //(st: null)    Checks if a vector is a null vector.
bool    vec_Null3d(vec_3d a);

u16     vec_Len  (vec_2d a);                        //(st: len)     Returns the length of a vector using the manhattan norm.
u16     vec_Len3d(vec_3d a);

vec_2d  bresSeg(vec_2d origin, vec_2d target);      //(st: bresseg) Returns the 2d vector equivalent of a Bresenham-line segment.

vec_2d  vec_taxi(vec_2d *offset, vec_2d direction); //(st: taxi)    Moves a point one step into an direction.

//FUNCTIONS:


//╔══════════╤════════════╗
//║ FUNCTION │ vec_3to2d: ╠═══════════════════════════════════════════════════════════════════════════════════════════════#3to2d╗
//║··········└────────────╜                                                                                                     ║
//║                                                                                                                             ║
//║  Takes a 3d vector and returns a corresponding 2d vector by ignoring the z value.                                           ║
//║                                                                                                                             ║
//╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝
vec_2d  vec_3to2d(vec_3d a)         //Returns a 2d vector, cotaining x and y values of the supplied 3d vector.
{
    vec_2d rvalue;
    rvalue.x = a.x;
    rvalue.y = a.y;

    return (rvalue);
}

//╔══════════╤════════════╗
//║ FUNCTION │ vec_2to3d: ╠═══════════════════════════════════════════════════════════════════════════════════════════════#2to3d╗
//║··········└────────────╜                                                                                                     ║
//║                                                                                                                             ║
//║  Takes a 2d vector and returns a correstponding 3d vector with z set to 0.                                                  ║
//║                                                                                                                             ║
//╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝
vec_3d vec_2to3d(vec_2d a)          //Returns a 3d vector, containing x and y values of the supplied 3d vector and 0 in z.
{
    vec_3d rvalue;
    rvalue.x = a.x;
    rvalue.y = a.y;
    rvalue.z = 0;

    return (rvalue);
}


//╔══════════╤══════════╗
//║ FUNCTION │ vec_Sum: ╠═══════════════════════════════════════════════════════════════════════════════════════════════════#sum╗
//║··········└──────────╜                                                                                                       ║
//║                                                                                                                             ║
//║  Returns the sum of two vectors.                                                                                            ║
//║                                                                                                                             ║
//║  Arguements:                                                                                                                ║
//║                                                                                                                             ║
//║     vec:   a        //First of two vectors to sum.                                                                          ║
//║     vec:   b        //Second of two vectors to sum.                                                                         ║
//║                                                                                                                             ║
//║  Return:                                                                                                                    ║
//║                                                                                                                             ║
//║     Return type is vec_2d:  if all arguments are of type vec_2d.                                                            ║
//║     Return type is vec_3d:  if at least one argument is of type vec_3d.                                                     ║
//║                                                                                                                             ║
//╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝
vec_2d vec_Sum  (vec_2d a, vec_2d b)
{

    a.x += b.x;
    a.y += b.y;

    return(a);
}


vec_3d vec_Sum3d(vec_3d a, vec_3d b)
{

    a.x += b.x;
    a.y += b.y;
    a.z += b.z;

    return(a);
}

vec_3d vec_Sum2d3d(vec_2d a, vec_3d b)
{
    b.x += a.x;
    b.y += a.y;

    return(b);
}

vec_3d vec_Sum3d2d(vec_3d a, vec_2d b)
{
    a.x += b.x;
    a.y += b.y;

    return(a);
}
//╔══════════╤══════════╗
//║ FUNCTION │ vec_Dif: ╠═══════════════════════════════════════════════════════════════════════════════════════════════════#dif╗
//║··········└──────────╜                                                                                                       ║
//║                                                                                                                             ║
//║  Substracts vector b from vector a and returns the result.                                                                  ║
//║                                                                                                                             ║
//║  Arguements:                                                                                                                ║
//║                                                                                                                             ║
//║     vec_2d or vec_3d:   a                                                                                                   ║
//║     vec_2d or vec_3d:   b  .                                                                                                ║
//║                                                                                                                             ║
//║  Return:                                                                                                                    ║
//║                                                                                                                             ║
//║     Return type is vec_2d:  if all arguments are of type vec_2d.                                                            ║
//║     Return type is vec_3d:  if at least one argument is of type vec_3d.                                                     ║
//║                                                                                                                             ║
//╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝
vec_2d vec_Dif  (vec_2d a, vec_2d b)
{
    a.x -= b.x;
    a.y -= b.y;

    return(a);
}

vec_3d vec_Dif3d(vec_3d a, vec_3d b)
{
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;

    return(a);
}

vec_3d vec_Dif2d3d(vec_2d a, vec_3d b)
{
    b.x = a.x - b.x;
    b.y = a.y - b.y;

    return(b);
}

vec_3d vec_Dif3d2d(vec_3d a, vec_2d b)
{
    a.x -= b.x;
    a.y -= b.y;

    return(a);
}

//╔══════════╤═══════════╗
//║ FUNCTION │ vec_Smul: ╠═════════════════════════════════════════════════════════════════════════════════════════════════#smul╗
//║··········└───────────╜                                                                                                      ║
//║                                                                                                                             ║
//║  Scalar-multiplies vector a with scalar l.                                                                                  ║
//║                                                                                                                             ║
//║  Arguments:                                                                                                                 ║
//║                                                                                                                             ║
//║    s16                  l (the scalar)                                                                                      ║
//║    vec_2d or vec_3d     a (the vector)                                                                                      ║
//║                                                                                                                             ║
//║  Return:                                                                                                                    ║
//║                                                                                                                             ║
//║     Return type is that of a.                                                                                               ║
//║                                                                                                                             ║
//╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝

vec_2d vec_Smul  (s16 l,vec_2d a)
{
    a.x *= l;
    a.y *= l;

    return(a);
}

vec_3d vec_Smul3d(s16 l,vec_3d a)
{
    a.x *= l;
    a.y *= l;
    a.z *= l;

    return(a);
}

//╔══════════╤═════════╗
//║ FUNCTION │ vec_Eq: ╠═════════════════════════════════════════════════════════════════════════════════════════════════════#eq╗
//║··········└─────────╜                                                                                                        ║
//║                                                                                                                             ║
//║  Checks whether two vectors a and b are equal.                                                                              ║
//║                                                                                                                             ║
//║  Arguments:                                                                                                                 ║
//║                                                                                                                             ║
//║    vec_2d or vec_3d     a (vector 1)                                                                                        ║
//║    vec_2d or vec_3d     b (vector 2)                                                                                        ║
//║                                                                                                                             ║
//║  Return:                                                                                                                    ║
//║                                                                                                                             ║
//║     Returns true if all coexisting coordinates are equal.                                                                   ║
//║                                                                                                                             ║
//╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝


bool vec_Eq  (vec_2d a, vec_2d b)
{

    if ((a.x == b.x) && (a.y == b.y)) return(true);
    else return(false);
}

bool vec_Eq3d(vec_3d a, vec_3d b)
{

    if ((a.x == b.x) && (a.y == b.y) && (a.z == b.z)) return(true);
    else return(false);
}

bool vec_Eq2d3d(vec_2d a, vec_3d b)
{

    if ((a.x == b.x) && (a.y == b.y)) return(true);
    else return(false);
}

bool vec_Eq3d2d(vec_3d a, vec_2d b)
{

    if ((a.x == b.x) && (a.y == b.y)) return(true);
    else return(false);
}

//╔══════════╤═══════════╗
//║ FUNCTION │ vec_Null: ╠═════════════════════════════════════════════════════════════════════════════════════════════════#null╗
//║··········└───────────╜                                                                                                      ║
//║                                                                                                                             ║
//║  Checks if a vector is a null vector.                                                                                       ║
//║                                                                                                                             ║
//║  Arguments:                                                                                                                 ║
//║                                                                                                                             ║
//║    vec_2d or vec_3d     a (the vector                                                                                       ║
//║                                                                                                                             ║
//║  Return:                                                                                                                    ║
//║                                                                                                                             ║
//║     Returns true if all coordinates of a are 0.                                                                             ║
//║                                                                                                                             ║
//╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝
bool vec_Null  (vec_2d a)
{

    if ((a.x == 0) && (a.y == 0)) return(true);
    else return(false);
}

bool vec_Null3d(vec_3d a)
{

    if ((a.x == 0) && (a.y == 0) && (a.z == 0)) return(true);
    else return(false);
}

//╔══════════╤══════════╗
//║ FUNCTION │ vec_Len: ╠═══════════════════════════════════════════════════════════════════════════════════════════════════#len╗
//║··········└──────────╜                                                                                                       ║
//║                                                                                                                             ║
//║  Returns the length of vector a using the manhattan norm. (||a|| = |a.1| + |a.2| + ... + |a.n|)                             ║
//║                                                                                                                             ║
//║  Arguments:                                                                                                                 ║
//║                                                                                                                             ║
//║    vec_2d or vec_3d     a (the vector)                                                                                      ║
//║                                                                                                                             ║
//║  Return:                                                                                                                    ║
//║                                                                                                                             ║
//║     Returns ||a||                                                                                                           ║
//║                                                                                                                             ║
//╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝
u16 vec_Len  (vec_2d a)
{
   return(abs(a.x) + abs(a.y)); //Manhattan norm.
}

u16 vec_Len3d(vec_3d a)
{
   return(abs(a.x) + abs(a.y) + abs(a.z)); //Manhattan norm.
}

//╔══════════╤══════════╗
//║ FUNCTION │ bresSeg: ╠═══════════════════════════════════════════════════════════════════════════════════════════════#bresseg╗
//║··········└──────────╜                                                                                                       ║
//║                                                                                                                             ║
//║  Returns a vector pointing to the second segment of a Bresenham-line from "origin" to "target".                             ║
//║                                                                                                                             ║
//║                                                                                                                             ║
//║  A Bresenham line can for example look like this:                                                                           ║
//║                                                                                                                             ║
//║  ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒     Legend:                                                                                     ║
//║  ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██TT▒▒                                                                                                 ║
//║  ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒████▒▒▒▒▒▒     OO = Origin                                                                                 ║
//║  ▒▒▒▒▒▒▒▒▒▒██████▒▒▒▒▒▒▒▒▒▒     TT = Target                                                                                 ║
//║  ▒▒▒▒▒▒VV██▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒     VV = Returned 2d Vector                                                                     ║
//║  ▒▒OO██▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒                                                                                                 ║
//║  ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒                                                                                                 ║
//║                                                                                                                             ║
//║  This function is useful when you want some entity like a sprite or the camera ("origin") move straight towards "target".   ║
//║  Just let the function calculate the next vector, move your entity step by step in the faster direction (the one with the   ║
//║  larger absolute value), then once in the slower direction and then request the next Bresenham-segment from the new         ║
//║  position. If you update the screen once or more in between the steps, the entity will move along the Bresenham-line        ║
//║  towards "target".                                                                                                          ║
//║                                                                                                                             ║
//║  Arguments:                                                                                                                 ║
//║                                                                                                                             ║
//║      vec_2d     origin:    Startpoint of the Bresenham-line.                                                                ║
//║      vec_2d     target:    Endpoint of the bresenham-line.                                                                  ║
//║                                                                                                                             ║
//║  Return:                                                                                                                    ║
//║                                                                                                                             ║
//║      vec_2d     rvalue:    the vector to the next Bresenham-segment.                                                        ║
//║                                                                                                                             ║
//╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝
vec_2d bresSeg(vec_2d origin, vec_2d target){

    s16 xdiff = target.x - origin.x;
    s16 ydiff = target.y - origin.y;

    vec_2d returnvalue;

    if(xdiff == 0)
    {
        returnvalue.x = 0;
        returnvalue.y = ydiff;
        return(returnvalue);
    }

    if(ydiff == 0)
    {
        returnvalue.x = xdiff;
        returnvalue.y = 0;
        return(returnvalue);
    }

    returnvalue.x = sgn(xdiff);          //Set returnvalue.x to sign of xdiff. At least one step in this direction has to be made.
    returnvalue.y = sgn(ydiff);          //Set returnvalue.y to sign of ydiff. At least one step in this direction has to be made.

    //If x is the fast direction:

    if (abs(xdiff)>abs(ydiff)){

        s16 temp = ydiff;

        while(abs(temp) < abs(xdiff))    //While temp doesn't grow out xdiff..
        {
            grow(&temp,abs(ydiff));            //...grow temp with the speed of ydiff
            grow(&returnvalue.x,1);       //and count the grows in returnvalue.x with the sign set right to keep directional info.
        }
    }

    //If y is the fast direction:

    if (abs(xdiff)<abs(ydiff)){

        s16 temp = xdiff;

        while(abs(temp) > abs(xdiff))    //While temp doesn't grow out ydiff..
        {
            grow(&temp,abs(xdiff));            //...grow temp with the speed of xdiff
            grow(&returnvalue.y,1);       //and count the grows in returnvalue.y with the sign set right to keep directional info.
        }
    }

    return (returnvalue);
}

//╔══════════╤═══════════╗
//║ FUNCTION │ vec_Taxi: ╠═════════════════════════════════════════════════════════════════════════════════════════════════#taxi╗
//║··········└───────────╜                                                                                                      ║
//║                                                                                                                             ║
//║  Increases vector "offset" one step in the direction of the longer coordinate of "direction".                               ║
//║                                                                                                                             ║
//║  The name Taxi derives from the Manhattan-norm we are using wich is also called taxi-norm. What this function does can      ║
//║  be easily understood by imagining a taxi driving from point "offset" to destination "offset + direction".                  ║
//║                                                                                                                             ║
//║                                                                                                                             ║
//║   ████  ████  ████  ████  ████  ████  ████  Legend:                                                                         ║
//║   ████  ████  ████  ████  ████  ████  ████                                                                                  ║
//║   ████  ████  ████  ████  ████  ██▓▓  ▓▓██      TT = taxi / offset                                                          ║
//║       02>>>>03>>>>04>>>>05>>>>06>>>>DD          DD = destination / (offset + direction)                                     ║
//║   ████/\████/\████/\████/\████/\██▓▓/\▓▓██                                                                                  ║
//║   ████/\████/\████/\████/\████/\██▓▓/\▓▓██  The was the taxy can travel towards it's destination has much in common with    ║
//║       01>>>>02>>>>03>>>>04>>>>05>>>>06      the way drawing pixel lines functions. It doesn't matter how often the          ║
//║   ████/\████/\████/\████/\████/\██▓▓/\▓▓██  taxi-driver turns into another street. As long as he doesn't turn away from     ║
//║   ██▓▓/\▓▓▓▓/\▓▓▓▓/\▓▓▓▓/\▓▓▓▓/\▓▓▓▓/\▓▓██  his destination, he will always travel the same distance. In this case 7        ║
//║       TT>>>>01>>>>02>>>>03>>>>04>>>>05      If this function is repaetedly called on the same vector, it's taxi-driver      ║
//║   ██▓▓  ▓▓▓▓  ▓▓▓▓  ▓▓▓▓  ▓▓▓▓  ▓▓▓▓  ▓▓██  drives along the marked road: First in the longer direction, than in the        ║
//║   ████  ████  ████  ████  ████  ████  ████  shorter one, until both directions equally long. After that he randomly decides ║
//║   ████  ████  ████  ████  ████  ████  ████  wich turns to take.                                                             ║
//║                                                                                                                             ║
//║                                                                                                                             ║
//║  Arguments:                                                                                                                 ║
//║                                                                                                                             ║
//║    vec_2d     *offset       //Pointer to the vector of the entity you want to move.                                         ║
//║    vec_2d      direction    //The direction your entity wants to move.                                                      ║
//║                                                                                                                             ║
//║  Return:                                                                                                                    ║
//║                                                                                                                             ║
//║     The function advances vector "offset" one step into "direction" and returns the updated direction to the destination.   ║
//║                                                                                                                             ║
//╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝
vec_2d vec_taxi(vec_2d *offset, vec_2d direction)
{


    if (abs(direction.x) > abs(direction.y))        //If x is the longer ride.
    {
        offset->x += sgn(direction.x);
        shrink(&direction.x,1);
    }
    if (abs(direction.x) < abs(direction.y))
    {
        offset->y += sgn(direction.y);
        shrink(&direction.y,1);
    }
    else
    {
        if(rand() < (RAND_MAX >> 1))
        {
            offset->x += sgn(direction.x);
            shrink(&direction.x,1);
        }
        else
        {
            offset->y += sgn(direction.y);
            shrink(&direction.y,1);
        }
    }

return(direction);
}

#endif /* vector_H */

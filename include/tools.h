//╔═══════════════╗
//║ T O O L S . H ║═════════════════════════════════════════════════════════════════════════════════════════════════════════════╗
//╠═══════════════╝                                                                                                             ║
//║                                                                                                                             ║
//║     A collection of tools.                                                                                                  ║
//║                                                                                                                             ║
//╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝

#ifndef tools_H
#define tools_H

#define shrink(n,m) grow(n,-m)

//FUNCTION STANDART-RETURN-MAKROS:

#define POS         0x1             //Flag if returnvalue is positive;
#define OV          0x1 << 1        //Flag if overflow occured.
#define GET_OV(n)   (n >> 1) & 1;   //overflow flags status

// FUNCTION PROTOTYPES:

s8      grow (s16 *value,s16 speed);            //(st: grow)    Increases absolute value leaving the sign intact.
int     sgn(int value);                         //(st: sgn)     Returns the sign of value.
bool    isPos(int value);                       //(st: ispos)   Returns true if value is positive or 0;
bool    isNeg(int value);                       //(st: isneg)   Returns true if value is negative or 0;
bool    isEven(s16 value);                      //(st: iseven)  Returns true if value is even.
bool    isOdd(s16 value);                       //(st: isodd)   Returns true if value is odd.
s16     maxOf(s16 i, s16 j);                    //(st: maxof)   Retruns the maximum of i and j.




//FUNCTIONS:

//╔══════════╤═══════╗
//║ FUNCTION │ grow: ╠═════════════════════════════════════════════════════════════════════════════════════════════════════#grow╗
//║··········└───────╜                                                                                                          ║
//║                                                                                                                             ║
//║  Increases the absolute value at "*value" by "speed", leaving it's sign intact                                              ║
//║                                                                                                                             ║
//║  Arguments:                                                                                                                 ║
//║                                                                                                                             ║
//║      value:  value to grow                                                                                                  ║
//║      spreed: speed of growth (can be negative to shrink)                                                                    ║
//║                                                                                                                             ║
//║  Return: standart.                                                                                                          ║
//║                                                                                                                             ║
//║      If "*value" would grow larger than max(s16) or smaller than min(s16)                                                   ║
//║      "*value" is reseted to 0 plus the remainig value and the OV flag is                                                    ║
//║      set in the srvalue.                                                                                                    ║
//║                                                                                                                             ║
//║      If "speed" is negative the function will shrink the value until it reaches 0.                                          ║
//║                                                                                                                             ║
//║      If "*value" is 0 the function can't decide wheter to grow negatively or positively                                     ║
//║      and returns 0 leaving "*value" as it is.                                                                               ║
//║                                                                                                                             ║
//║      Note: There is also a macro called shrink wich is just grow with "speed" negated.                                      ║
//║                                                                                                                             ║
//║                                                                                                                             ║
//╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝
s8 grow (s16 *value,s16 speed)
{
    s8 srvalue = 0;

        if (*value == 0)
    {
        return(0);         //"value" has to have an initial direction.
    }

    if (*value  > 0)
    {
        if((32767 - *value) < speed)  //Check if an overflow would occure. 23767 is max(s16).
        {
            srvalue |= OV;    //Set overflow flag.
            *value = speed - (32767 - *value);     //Reset value to start from 0 plus rest of speed.
        }
        else *value += speed;

        if(*value <= 0)
            {
                *value = 0;
                return (srvalue);
            }else return(srvalue | POS);
    }

    if (*value  < 0)
    {
        if((-32768 - *value) > -speed) //Check if an overflow would occure. -23768 is min(s16).
        {
            srvalue |= OV;    //Set overflow flag.
            *value = -speed + (-32768 - *value);  //Reset value to start from 0 minus rest of speed.

        }
        else *value -= speed;

        if(*value >= 0)
        {
            *value = 0;
            return (srvalue);
        } else return(srvalue);

    }
    return srvalue; //Unrechable. Only to stop compiler from complaining.

}

//╔══════════╤══════╗
//║ FUNCTION │ sgn: ╠═══════════════════════════════════════════════════════════════════════════════════════════════════════#sgn╗
//║··········└──────╜                                                                                                           ║
//║ Returns the sign of "value".                                                                                                ║
//║                                                                                                                             ║
//║ Parameters:                                                                                                                 ║
//║                                                                                                                             ║
//║     int value   (our value)                                                                                                 ║
//║                                                                                                                             ║
//║ Return:                                                                                                                     ║
//║                                                                                                                             ║
//║     if value is positive:  1                                                                                                ║
//║     if value is negative: -1                                                                                                ║
//║     if value is 0:         0                                                                                                ║
//║                                                                                                                             ║
//╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝
int sgn(int value){

    if (value == 0) return  0;
    if (value  < 0) return -1;
    else return 1;
}

//╔══════════╤════════╗
//║ FUNCTION │ isPos: ╠═══════════════════════════════════════════════════════════════════════════════════════════════════#ispos╗
//║··········└────────╜                                                                                                         ║
//║ Returns true if value is positive.                                                                                          ║
//║ 0 ist interpreted as positive.                                                                                              ║
//║                                                                                                                             ║
//║ Parameters:                                                                                                                 ║
//║                                                                                                                             ║
//║     int value   (our value)                                                                                                 ║
//║                                                                                                                             ║
//║ Return:                                                                                                                     ║
//║                                                                                                                             ║
//║     if value is positive:  true                                                                                             ║
//║     if value is negative:  false                                                                                            ║
//║     if value is 0:         true                                                                                             ║
//║                                                                                                                             ║
//╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝
bool isPos(int value){

    if (value  < 0) return  false;
    else return true;
}
//╔══════════╤════════╗
//║ FUNCTION │ isNeg: ╠═══════════════════════════════════════════════════════════════════════════════════════════════════#isneg╗
//║··········└────────╜                                                                                                         ║
//║ Returns true if value is negative.                                                                                          ║
//║ 0 ist interpreted as negative.                                                                                              ║
//║                                                                                                                             ║
//║ Parameters:                                                                                                                 ║
//║                                                                                                                             ║
//║     int value   (our value)                                                                                                 ║
//║                                                                                                                             ║
//║ Return:                                                                                                                     ║
//║                                                                                                                             ║
//║     if value is positive:  false                                                                                            ║
//║     if value is negative:  true                                                                                             ║
//║     if value is 0:         true                                                                                             ║
//║                                                                                                                             ║
//╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝
bool isNeg(int value){

    if (value > 0) return  false;
    else return true;
}

//╔══════════╤═════════╗
//║ FUNCTION │ isEven: ╠═════════════════════════════════════════════════════════════════════════════════════════════════#iseven╗
//║··········└─────────╜                                                                                                        ║
//║ Returns true if value is even.                                                                                              ║
//║                                                                                                                             ║
//║ Parameters:                                                                                                                 ║
//║                                                                                                                             ║
//║     int value   (our value)                                                                                                 ║
//║                                                                                                                             ║
//║ Return:                                                                                                                     ║
//║                                                                                                                             ║
//║     if value is even:  true                                                                                                 ║
//║     if value is odd:   false                                                                                                ║
//║                                                                                                                             ║
//╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝
bool isEven(s16 value)
{
    return !(value %2);

}

//╔══════════╤════════╗
//║ FUNCTION │ isOdd: ╠═══════════════════════════════════════════════════════════════════════════════════════════════════#isodd╗
//║··········└────────╜                                                                                                         ║
//║ Returns true if value is odd.                                                                                               ║
//║                                                                                                                             ║
//║ Parameters:                                                                                                                 ║
//║                                                                                                                             ║
//║     int value   (our value)                                                                                                 ║
//║                                                                                                                             ║
//║ Return:                                                                                                                     ║
//║                                                                                                                             ║
//║     if value is even:  false                                                                                                ║
//║     if value is odd:   true                                                                                                 ║
//║                                                                                                                             ║
//╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝
bool isOdd(s16 value)
{
    return (value %2);
}

//╔══════════╤════════╗
//║ FUNCTION │ maxOf: ╠═══════════════════════════════════════════════════════════════════════════════════════════════════#maxof╗
//║··········└────────╜                                                                                                         ║
//║ Returns the maximum of two values i and j                                                                                   ║
//║                                                                                                                             ║
//║ Parameters:                                                                                                                 ║
//║                                                                                                                             ║
//║     int value   (our value)                                                                                                 ║
//║                                                                                                                             ║
//║ Return:                                                                                                                     ║
//║                                                                                                                             ║
//║     maximum of i and j                                                                                                      ║
//║                                                                                                                             ║
//╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝
s16 maxOf(s16 i, s16 j)
{
    if (i > j) return (i);
    else return (j);
}

//╔══════════╤════════╗
//║ FUNCTION │ minOf: ╠═══════════════════════════════════════════════════════════════════════════════════════════════════#minof╗
//║··········└────────╜                                                                                                         ║
//║ Returns the minimum of two values i and j                                                                                   ║
//║                                                                                                                             ║
//║ Parameters:                                                                                                                 ║
//║                                                                                                                             ║
//║     int value   (our value)                                                                                                 ║
//║                                                                                                                             ║
//║ Return:                                                                                                                     ║
//║                                                                                                                             ║
//║     minimum of i and j                                                                                                      ║
//║                                                                                                                             ║
//╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝
s16 minOf(s16 i, s16 j)
{
    if (i < j) return (i);
    else return (j);
}

#endif /* tools_H */

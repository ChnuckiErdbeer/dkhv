#ifndef ERROR_H
#define ERROR_H

void error(s16 id);

void error(s16 id){

    switch(id)
    {
        case 100:   printf("Error %i: scrollDirection must be (0,n) or (n,0)!\n",id);
                    break;

        default:    printf("ERROR OF ERRORS!! Undefined Errocode: %i\n",id);
                    break;
    }

    while(1);
}
#endif // ERROR_H

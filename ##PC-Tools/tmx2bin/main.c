#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define mapname argv[1]

#define TILEOFFS(x,y) (2 * x * y)

typedef unsigned short  tile_t;






void        error(int id);
int         findStringInFile(char *filename, char *searchString, int fromHereOn);
int         stringToInt(char *mystring);
int         getNumberFromFile(char *filename,int offset);
int         getStringLen(char *filename,int offset);
const char *getQStringFromFile(char *filename, int offset);
void        getMapFilename(char *returnstring,char *outpufilename,char *layername,int x, int y);
void        writeLayerToFile(char *layerName, char *tmxfilename, char *outputfilename, int offset,int width, int height);


void error(int id){

    printf("\n");

    switch(id)
    {
        case 0  :   printf("Error %i: Please add your tmx file as argument!\n",id);
                    break;

        case 1  :   printf("Error %i: Couldn't open tmx file.\n",id);
                    break;

        case 2  :   printf("Error %i: Couldn't create output file.\n",id);
                    break;

        case 3  :   printf("Error %i: Couldn't write to output file.\n",id);
                    break;

        case 10 :   printf("Error %i: Can't find \"width\" in tmx-file.\n",id);
                    break;

        case 11 :   printf("Error %i: Can't find \"heigth\" in tmx-file.\n",id);
                    break;

        case 12 :   printf("Error %i: At least one of the layers is corrupt.(\"csv\"> not found.)\n          Did you choose CSV as your layer-format in Tiled?",id);
                    break;

        case 100:   printf("Error %i: Func: findStringInFile: String contains non numeral characters!\n",id);
                    break;

        case 101:   printf("Error %i: Func: getStringLen: Initial char has to be '\"'.\n",id);
                    break;

        case 102:   printf("Error %i: Func: getStringLen: EOF before '\"' was spotted.\n",id);
                    break;

        case 110:   printf("Error %i: Func: writeLayerToFile: Tilenumber is larger than 1024.\n",id);
                    break;

        case 111:   printf("Error %i: Func: writeLayerToFile: Tilenumber is negative.\n",id);
                    break;

        case 112:   printf("Error %i: Func: writeLayerToFile: Couldnt write binary file.\n",id);
                    break;

        default:    printf("ERROR OF ERRORS!! Undefined Errocode: %i\n",id);
                    break;
    }

    printf("\n");
    exit(id);
}

int findStringInFile(char *filename, char *searchString, int fromHereOn)
{
    int rvalue = -1;

    char buffer[strlen(searchString)];

    FILE *file;
    file = fopen(filename,"rb");
    if (file == NULL) error(1);

    fseek(file,0,SEEK_END);
    int filelen = ftell(file);


    char a;
    int i;

    while((fromHereOn + strlen(searchString)) < filelen)
    {
        fseek(file, fromHereOn, SEEK_SET);

        for (i = 0; i < strlen(searchString); i++)
        {
            buffer[i] = fgetc(file);
        }
        buffer[i] = 0;


        if (strncmp(buffer,searchString,strlen(searchString)) == 0)
        {
            return (fromHereOn);
        }

        fromHereOn++;

    }

    return (-1);

    fclose(file);
}

int stringToInt(char *mystring)
{

    int     rvalue=0;
    char    a ;
    int     i = 0;
    int     sign = 1;

    if (mystring[0] == '-')
    {
        i++;
        sign = -1;
    }

    while((a = mystring[i]) != 0)
    {
        a &= 0b00001111;        //Ignore upper nibble of a. If a was an ascii-numeral, it now has its value as an int.

        if ((a >= 0) && (a < 10))
        {

            rvalue *= 10;
            rvalue += (a);

        }
        else
        {
            error(100);
        }

        i++;
    }

    return (rvalue * sign);
}

int getNumberFromFile(char *filename,int offset)
{
    char buffer[6];

    int i;
    char a;

    FILE *file;
    file = fopen(filename,"rb");
    if (file == 0) error(1);



    fseek(file,offset,SEEK_SET);

    i = 0;

    a = fgetc(file);

    if (a == '-')
    {
        buffer[i] = a;
        i++;
    }

    while(i < 6)
    {
        if (isdigit(a))
        {
            buffer[i] = a;
            i++;
        }
        else break;

        a = fgetc(file);
    }

    fclose(file);

    buffer[i] = 0;


    return(stringToInt(buffer));
}

int getStringLen(char *filename,int offset){

    FILE *file;
    file = fopen(filename,"rb");
    if(ferror(file)) error(1);

    int i = 0;
    char a;

    fseek(file,offset,SEEK_SET);

    a = fgetc(file);

    if(a != '\"') error(101);

    while ((a = fgetc(file)) != '\"')
    {
        if (feof(file) != 0) error(102);
        i++;
    }
    fclose(file);

    return (i);
}

const char *getQStringFromFile(char *filename, int offset)
{
    FILE *file;
    file = fopen (filename,"rb");
    if(ferror(file) != 0) error(1);

    int strLength = getStringLen(filename,offset);

    char rstring[strLength + 1];

    int i;

    fseek(file, offset +1, SEEK_SET);

    for (i = 0; i < strLength; i++)
    {
        rstring[i] = fgetc(file);
    }

    rstring[i] = 0;

    return(rstring);

    fclose(file);
}


void getMapFilename(char *returnstring,char *outputfilename,char *layername,int x, int y)
{
    char *xs;
    char *ys;

    xs = malloc(8);       //String for x-position.
    ys = malloc(8);       //String for y-position.


    itoa(x,xs,10);              //Set xs to current maps x position.
    itoa(y,ys,10);              //Set ys to current maps y position.

    //Set output filename in format: "outputfilename_layername_(x,y).bin"

    strcpy(returnstring,outputfilename);
    strcat(returnstring,"_");
    strcat(returnstring,layername);
    strcat(returnstring,"_(");
    strcat(returnstring,xs);
    strcat(returnstring,",");
    strcat(returnstring,ys);
    strcat(returnstring,").bin");

    free (xs);
    free (ys);
}

void writeLayerToFile(char *layerName, char *tmxfilename, char *outputfilename, int offset,int width, int height)
{


    FILE *output;

    int  i = 0;
    int  j = 0;

    i = width >> 5;
    j = height >> 5;

    char *filename;


    tile_t *current_level;

    current_level = malloc(32*32*32*32); //32 x 32 maps with 32 x 32 tiles.


    filename = malloc(256);     //String for filename of current file.


    i = 0;
    j = 0;


    while (j < height)          //Line
    {

        int filechange = 0;

        while (i < (width))     //Row
        {




            current_level[(i >> 5) * (j >> 5) + (i % 32) * (j % 32)] = getNumberFromFile(tmxfilename,offset);


            //Step behind the numbers:

            if (current_level[(i >> 5) * (j >> 5) + (i % 32) * (j % 32)] >= 0)
            {
                offset++;
                if (current_level[(i >> 5) * (j >> 5) + (i % 32) * (j % 32)] > 9)
                {
                    offset++;
                    if (current_level[(i >> 5) * (j >> 5) + (i % 32) * (j % 32)] > 99)
                    {
                        current_level[(i >> 5) * (j >> 5) + (i % 32) * (j % 32)]++;
                        if (current_level[(i >> 5) * (j >> 5) + (i % 32) * (j % 32)] > 999)
                        {
                            current_level[(i >> 5) * (j >> 5) + (i % 32) * (j % 32)]++;
                            if (current_level[(i >> 5) * (j >> 5) + (i % 32) * (j % 32)] > 1024) error(110);
                        }

                    }
                }
            } else error(111);

            //Step behind the ',':
            offset++;

            i++;
        }

        printf("|");
        offset++; //Skip the newline char.

        j++;
        filechange = 0;
        i=0;
    }

        printf("[SUCCESS!]\n");



     //Create the binary files:

    for (i = 0; i < (width >> 5);i++)           //width  / 32 = number of map rows
    {
        for (j = 0; j < (height >> 5); j++)     //heigth / 32 = number of map lines
        {

            bool  mapempty = true;

            int x,y;

            for (x = 0; x < 32; x++)
            {
                for (y = 0; y < 32; y++)
                {
                    if (current_level[(i) * (j) + (x) * (y)] != 0)
                    mapempty = false;

                }
            }

            if (mapempty == false)
            {

                //ggg files are garbled.
                getMapFilename(filename,outputfilename,layerName,i,j);
                output = fopen(filename,"wb");
                if(output == 0) error(112);



                fwrite(&current_level[(i) * (j)],sizeof (tile_t),(32*32),output);

                //CONSIDER ADDING ONE ADDITIONAL EMPTY TILE

                fclose(output);




            }





        }
    }


        free (filename);
        free (current_level);





}



int main(int argc, char *argv[])
{

    //  ARGUMENTS:
    //
    //  tmx2bin.exe mapname numoflayers startinglayer
    //
    //  mapname:        Name of the .tmx file, created by tiled. Also used for output filename.
    //                  PASSED TO tmx2bin WITHOUT THE .tmx POSTFIX!!!!
    //                  Map has to be 32x32, 64x33, 32x64 or 64x64 tiles with 256 colors from one palette,
    //                  or 16x16, 32x32, 64x64 or 128x128 tiles with 16 colors from 16 palettes.
    //                  Map's layer-format has to be CSV.
    //
    //  numoflayers:    Number of layers to be converted to binary NDS format.
    //                  If not set, tmx2bin will convert all layers it finds up to the fourth one.
    //                  (NDS can use up to four tile-layers per screen.)
    //
    //  startinglayer:  Specifies wich layer is the first to convert. (0 is first layer!)
    //                  Example: "tmx2bin mytmx.tmx 2 5" will result in converting layers 5 and 6.



    int i,j;

    char temp[16];

    int numoflayers = 4;
    int startlayer = 0;


    int layers = 0;


    // Handling arguments:

    switch (argc)
    {
        case 1 :   error(0);
                   break;

        case 3 :   numoflayers = stringToInt(argv[2]);
                   break;

        case 4 :   numoflayers = stringToInt(argv[2]);
                   startlayer  = stringToInt(argv[3]);
                   break;
    }

    char tmxname[strlen(mapname) + 4];
    strcpy(tmxname,mapname);
    strcat(tmxname,".tmx");


    //Set variables:

    int offset = 0;
    int layercount = 0;

    while (layercount < (startlayer + numoflayers))
    {

        do
        {
             //Search for next layer in tmx file:

            offset = findStringInFile(tmxname, "layer name=",offset);
            if (offset == -1)
            {
                printf("No layer behind layer %i found in tmx-file.\n",layercount-1);
                exit(0);
            }
            offset += strlen("layer name=");

            layercount++;
        }
        while (layercount <= startlayer);

        //Set layers variables:

        char currentLayerName[64];
        strcpy(currentLayerName, getQStringFromFile(tmxname,offset));

        offset = findStringInFile(tmxname, "width=\"",offset);
        if(offset == -1) error (10);
        offset += strlen("width=\"");
        int width = getNumberFromFile(tmxname,offset);

        offset = findStringInFile(tmxname, "height=\"",offset);
        if(offset == -1) error (11);
        offset += strlen("height=\"");
        int height = getNumberFromFile(tmxname,offset);

        //Write the layer:

        offset = findStringInFile(tmxname, "csv\">\n",offset);
        if(offset == -1) error (12);
        offset += strlen("csv\">\n");

        printf("\nConverting layer number %i named: \"%s\".\n",layercount - 1,currentLayerName);
        writeLayerToFile(currentLayerName, tmxname, mapname, offset, width, height);
        printf(" [SUCCESS!]\n\n");
    }

    exit(0);
}

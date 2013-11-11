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
int         getNumberFromFileInMemory(char *mempos,int offset);
int         getStringLen(char *filename,int offset);
const char *getQStringFromFile(char *filename, int offset);
void        getMapFilename(char *returnstring,char *outpufilename,char *layername,int x, int y);
void        writeLayerToFile(char *layerName, char *tmxfilename, char *outputfilename, int offset,int width, int height);
int         maxof(int x, int y);


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

        case 113:   printf("Error %i: Func: writeLayerToFile: Couldnt create level file.\n",id);
                    break;

        case 114:   printf("Error %i: Func: writeLayerToFile: Couldnt access level file.\n",id);
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

int getNumberFromFileInMemory(char *mempos,int offset)
{
    char buffer[6];

    int i;
    char a;
    i = 0;

    a = mempos[offset];
    offset++;

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

        a = mempos[offset];
        offset++;
    }

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


    itoa(x,xs,10);              //Set xs to current maps x position in the levels map raster.
    itoa(y,ys,10);              //Set ys to current maps y position.

    //Set output filename in format: "outputfilename_layername_(x,y).bin"

    strcpy(returnstring,outputfilename);
    strcat(returnstring,"_");
    strcat(returnstring,layername);
    strcat(returnstring,"_");
    strcat(returnstring,xs);
    strcat(returnstring,",");
    strcat(returnstring,ys);
    strcat(returnstring,").bin");

    free (xs);
    free (ys);
}

int maxof(int x, int y)
{
    if (x > y) return x;
    else return y;
}

void writeLayerToFile(char *layerName, char *tmxfilename, char *outputfilename, int offset,int width, int height)
{

    //Read entire tmx-file into memory:

    FILE *tmxfile;

    tmxfile = fopen(tmxfilename,"rb");
    if (tmxfile == 0) error(1);

    fseek(tmxfile,0,SEEK_END);

    char *tmx;

    unsigned int sizeoftmxfile = ftell(tmxfile);

    tmx = malloc(sizeoftmxfile);

    fseek(tmxfile,0,SEEK_SET);

    fread(tmx,sizeoftmxfile,1,tmxfile);         //tmx-file is now at position tmx in memory.

    fclose(tmxfile);



    int  i = 0;
    int  j = 0;

    i = width >> 5;
    j = height >> 5;

    char *filename;


    tile_t *current_level;

    int tiles_in_level = (width >> 5) * (height >> 5) * 32 * 32;    //(widht / 32) x (heigth / 32) maps with each 32 x 32 tiles.
    current_level = malloc(tiles_in_level * sizeof(short));


    filename = malloc(256);     //String for filename of current file.


    i = 0;
    j = 0;


    //Read interleaved map file into planar ram-segment current_level:

    printf("\n Read all submaps from layer: ");

    while (j < height)          //Step through the lines in interleaved tmx
    {

        int filechange = 0;

        while (i < (width))     //Setp through the rows in interleaved tmx
        {


            unsigned short tempi;


            //Now we step throug each tile in a line, and every 32 tiles append them to another corresponding ram segment.
            //
            //A simplified example where maps have 2x2 instead of 32x32 tiles:
            //
            //  tmx:            11223344        ram:            11112222
            //  (interleaved)   11223344        (planar)        33334444
            //                  55667788                        55556666
            //                  55667788                        77778888
            //
            //As you can see, while in the tmx file the data four our binary output files appears in a nested (interleaved)
            //form when stepping throug the entries one by one (11223344112233445566778855667788), in our ram-segment the
            //maps are stored sequentially (planar) (111122223333444445555666677778888). This way we can easily write our
            //map with only one call to fwrite for each file.
            //
            //We step tile per tile through all the map defining lines of our tmx file
            //And write the value of each tile to the according position in our memory segment.


            #define MAP_POS_IN_RAM(x,y)  ((x / 32) % (width >> 5) + (y / 32) * (width >> 5)) * 1024
            #define TILE_POS_IN_MAP(x,y)  (x % 32) + (32 * (y % 32))
            #define TILENR(x,y) (MAP_POS_IN_RAM(x,y)+TILE_POS_IN_MAP(x,y))



            current_level[TILENR(i,j)] = getNumberFromFileInMemory(tmx,offset);


              //Step behind the numbers:

             if (current_level[TILENR(i,j)] >= 0)
             {
                 offset++;
                 if (current_level[TILENR(i,j)] > 9)
                 {
                      offset++;
                     if (current_level[TILENR(i,j)] > 99)
                     {
                         offset++;
                         if (current_level[TILENR(i,j)] > 999)
                         {
                             offset++;
                             if (current_level[TILENR(i,j)] > 1024) error(110);
                         }

                     }

                }
            } else error(111);

            //Step behind the ',':
            offset++;

            i++;
        }


        offset++; //Skip the newline char.

        j++;
        filechange = 0;
        i=0;
    }

        printf("[SUCCESS!]\n");


    printf("\nCREATE FILES: \n\n");


    //Create the binary files:

    printf("Create level-file:");
    FILE *output;
    FILE *levelfile;

    strcpy(filename,outputfilename);
    strcat(filename,"_level.bin");
    levelfile = fopen(filename,"wb");   //Create empty levelfile.
    if (levelfile == 0) error(113);

    printf(" [DONE]\n");

    //Write level header:

    printf("Write level-file-header with standart settings:");

    {
        unsigned int temp = width >> 5;
        fwrite(&temp,2,1,levelfile);

        temp = height >> 5;
        fwrite(&temp,2,1,levelfile);
    }

    fclose(levelfile);

    printf("[DONE]\n\n");

    printf("Create map-files and write map raster to level file:\n\n");

    bool mapisempty = true;
    int actual_width = 0;
    int actual_height = 0;



    for (i = 0; i < (tiles_in_level);i++)                                   //Step tile per tile through memory-segment.
    {
         if (current_level[i] != 0) mapisempty = false;                     //Set mapisempty to false whenever a tile is found that is not = 0.

        if ((i % 1024) == 1023)                                             //Whenever we reach the last tile of a map:
        {


            if (mapisempty == false)                                        //Check if the map wasn't empty.
            {
                getMapFilename(filename,outputfilename,layerName,((i - 1023) / (width << 5)),(((i - 1023) >> 10) % (width >> 5)));

                if ((i+1) % (width * 32) == 0) printf("[]\n");
                else printf("[]");


                output = fopen(filename,"wb");
                if (output == 0) error(112);

                fwrite(&(current_level[i - (1023)]),1024 * 2,1,output);

                fclose(output);




                strcpy(filename,outputfilename);
                strcat(filename,"_level.bin");
                levelfile = fopen(filename,"ab");
                if (levelfile == 0) error(114);

                short temp = 0b1000000000000000;
                fwrite(&temp,2,1,levelfile);


                fclose(levelfile);

                actual_width = maxof(actual_width,(((i - 1023) >> 10) % (width >> 5)));
                actual_height = maxof(actual_height,((i - 1023) / (width << 5)));

                mapisempty = true;
            }

            else
            {

                if ((i+1) % (width * 32) == 0) printf("::\n");
                else printf("::");
                getMapFilename(filename,outputfilename,layerName,((i - 1023) / (width << 5)),(((i - 1023) >> 10) % (width >> 5)));




                strcpy(filename,outputfilename);
                strcat(filename,"_level.bin");
                levelfile = fopen(filename,"ab");

                if (levelfile == 0) error(114);

                short temp = 0;
                fwrite(&temp,2,1,levelfile);


                fclose(levelfile);
            }
        }
    }

    printf("Update level header with updated settings:\n");

    strcpy(filename,outputfilename);
    strcat(filename,"_level.bin");
    levelfile = fopen(filename,"r+b");   //Create empty levelfile.
    if (levelfile == 0) error(113);

    fseek(levelfile,0,SEEK_SET);

    actual_width++;
    actual_height++;

    printf("New level width:  %i maps.\n",actual_width);
    printf("New level height: %i maps.\n",actual_height);
    fwrite(&actual_width,2,1,levelfile);
    fwrite(&actual_height,2,1,levelfile);


    free (filename);
    free (current_level);
    free (tmx);
    #undef MAP_POS_IN_RAM(x,y)
    #undef TILE_POS_IN_MAP(x,y)
    #undef TILENR(x,y)
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
        printf("[OVERALL SUCCESS!]\n\n");
    }

    exit(0);
}

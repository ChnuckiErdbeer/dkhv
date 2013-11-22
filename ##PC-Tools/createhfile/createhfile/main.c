#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "tools.h"



int main(int argc, char *argv[])
{
   FILE *source;
   FILE *target;




    if(argc < 3)                                    //Check if enough arguments were provided.
    {
        printf("Arguments wrong!!\n");
        exit (1);
    }


    target = fopen (argv[2],"rb");                 //Open levels.h

    if (target == 0) error(10);


    //Read levels.h to memory:

    fseek(target,0,SEEK_END);                       //Navigate to the end of levels.h
    int levelFileSize = ftell(target);              //Set levelFileSize.

    char *levels_h;

    levels_h = malloc(levelFileSize);                //Allocate memory to fit levels.h in.
    if (levels_h == NULL) error(100);

   long i;
    fseek(target,0,SEEK_SET);
    char a;
    for(i = 0; i < levelFileSize; i++)              //Write levels.h to memory.
    {
        a = fgetc(target);
        levels_h[i] = a;
    }

    levels_h[i] = 0;

    {                                                  //For some unknown reason fclose fails if not waited for a moment. !?!
            int pupi;
            for(pupi = 0; pupi < 433333; pupi++);
    }

   // fclose (target); //Crashes if enabled !!???!!!



    //Retrieve levelname:

    i = findStringInFile(argv[1], "_level.bin", 0);     //Seach for level file in dir-created-file.
    if (i == 0) error (50);

    source = fopen(argv[1],"rb");                       //Navigate to the beginning of level-filename in source file.
    if (source == 0)error(11);


    fseek(source,i,SEEK_SET);

    long j = 0;


    while(fgetc(source) != '\n')
    {
        if ((ftell (source)) == 1)
        {
            fseek(source,0,SEEK_SET);
            break;
        }

        fseek(source,-2,SEEK_CUR);
        j++;
    }

    char levelname[256];

    for (i = 0; i < j; i++)                             //Extract level name from source file.
    {
        levelname[i] = fgetc(source);
    }

    levelname[i] = 0;


    fclose (source);


    // Delete old levels.h

    target = fopen (argv[2],"wb");                      //Open levels.h as an empty file.
    if (target == 0) error(10);

    //Write intro to level file:

    fputs("#ifndef LEVELS_H\n",target);
    fputs("#define LEVELS_H\n",target);
    fputc('\n\n',target);
    fputs("typedef struct\n",target);
    fputs("{\n",target);
    fputs("\tu16\t\t width;\n",target);
    fputs("\tu16\t\t height;\n",target);
    fputs("\ts16\t\t*maplayout;\n",target);
    fputs("\tu16\t\t footersize;\n",target);
    fputs("\tu16\t\t numberOfEntrypoints;\n",target);
    fputs("\ts16\t\t*entrypointList;\n\n",target);
    fputs("} level;\n\n\n",target);
    fputs("// Include binary files:\n",target);


    //Write the include lines:

    //First the lines from the old file:
    long offset = findStringInMemory(levels_h,levelFileSize,"Include binary files:\n",0);
    offset += strlen("Include binary files:\n");

    int functionsOffset = findStringInMemory(levels_h,levelFileSize,"\n//Functions:",(int)offset);

    for (i = 0; i < (functionsOffset - offset); i++)
    {
        fputc(levels_h[offset + i],target);
    }

    //Then the new lines:
    fputs("\n//Binary files for level \"",target);                                             //Write comment.
    fputs(levelname,target);
    fputs("\":\n\n",target);


    source = fopen(argv[1],"rb");
    if (source == 0) error(11);

    fseek(source,0,SEEK_END);              //Get sourcefile-size.
    int sourceSize = ftell(source);
    fseek(source,0,SEEK_SET);

    char line[512];

    i = 0;

    while(ftell(source) < sourceSize)
    {
        while((a = fgetc(source)) != '.')
        {
            if (ftell(source) == sourceSize) break;
            if (a == '\n') error(51);
            line[i] = a;
            i++;
        }

        if (ftell(source) < sourceSize)
        {
            line[i] = 0;

            fputs("\t#include \"",target);
            fputs(line,target);
            fputs("_bin.h\"\n",target);

            i = 0;

            while((a = fgetc(source)) != '\n')
            {
                if(ftell(source) == sourceSize) break;
            }
        }
    }

    fputs("\n\n//Functions:\n\n",target);

    offset = findStringInMemory(levels_h,levelFileSize,"//Level not loaded:\n",offset);

    offset += strlen("//Level not loaded:\n");

    fputs("u16 *lvl_get_test_mappointers(char *level,u16 x, u16 y)\n",target);
    fputs("{\n",target);



    j = findStringInMemory(levels_h,levelFileSize,"}//End of function lvl_get_test_mappointers",offset);

    //Write old if blocks of lvl_get_test_mappointers to target file:

    for (i = 0; i < (j - offset); i++)
    {
        fputc(levels_h[offset + i],target);
    }

    //Write new if blocks:

    fputs("\n\t//If blocks for level \"",target);
    fputs(levelname,target);
    fputs("\":\n\n",target);

    fseek(source,0,SEEK_SET);

    i = 0;

    while(ftell(source) < sourceSize)
    {
        while((a = fgetc(source)) != '.')
        {
            if (ftell(source) == sourceSize) break;
            if (a == '\n') error(51);
            line[i] = a;
            i++;
        }


        if (ftell(source) < sourceSize)
        {
            line[i] = 0;

            if
                (
                   (strcmp(line + i - 5,"level") != 0)
                && (strcmp(line + i - 5,"tiles") != 0)
                && (strcmp(line + i - 3,"pal"  ) != 0)


                )
            {

                fputs("\tif ((strcmp(level,\"",target);
                fputs(levelname,target);
                fputs("\") == 0) && (x == ",target);
                if (line[i-5] != '0') fputc(line[i-5],target);
                fputc(line[i-4],target);
                fputs(") && (y == ",target);
                if (line[i-2] != '0') fputc(line[i-2],target);
                fputc(line[i-1],target);
                fputs("))\n",target);

                fputs("\t{\n",target);

                fputs("\t\treturn (u16*)",target);
                fputs(line,target);
                fputs("_bin;\n",target);

                fputs("\t}\n\n",target);
            }

            i = 0;

            while((a = fgetc(source)) != '\n')
            {
                if(ftell(source) == sourceSize) break;
            }
        }
    }



    fputs("\n\t//Level not loaded:\n\n",target);

    fputs("\tif (strcmp(level,\"",target);
    fputs(levelname,target);
    fputs("\") == 0) return (u16*)",target);
    fputs(levelname,target);
    fputs("_MAP_BG0_00_00_bin;\n\n",target);

    fputs("}//End of function lvl_get_test_mappointers\n\n\n",target);

    offset = findStringInMemory(levels_h,levelFileSize,"level lvl_loadLevel(char *levelname)",offset);

    j = findStringInMemory(levels_h,levelFileSize,"//Level not loaded:",offset);

    //Copy old if blocks to target:

    for (i = 0; i < (j - offset); i++)
    {
        fputc(levels_h[offset + i],target);
    }

    //Write new if blocks:


    fputs("\tif (strcmp(levelname,\"",target);
    fputs(levelname,target);
    fputs("\") == 0)\n",target);
    fputs("\t{\n",target);

    fputs("\t\trstruct.width                =  ",target);
    fputs(levelname,target);
    fputs("_level_bin[0 * sizeof(u16)];\n",target);

    fputs("\t\trstruct.height               =  ",target);
    fputs(levelname,target);
    fputs("_level_bin[1 * sizeof(u16)];\n",target);

    fputs("\t\trstruct.maplayout            = &",target);
    fputs(levelname,target);
    fputs("_level_bin[2 * sizeof(u16)];\n",target);

    fputs("\t\trstruct.footersize           =  ",target);
    fputs(levelname,target);
    fputs("_level_bin[(2 + ((rstruct.width) * (rstruct.height))) * sizeof(u16)];\n",target);

    fputs("\t\trstruct.numberOfEntrypoints  =  ",target);
    fputs(levelname,target);
    fputs("_level_bin[(3 + ((rstruct.width) * (rstruct.height))) * sizeof(u16)];\n",target);

    fputs("\t\trstruct.entrypointList       = &",target);
    fputs(levelname,target);
    fputs("_level_bin[(4 + ((rstruct.width) * (rstruct.height))) * sizeof(u16)];\n\n",target);

    //Load level's tileset and palette:
    fputs("\n\t//Load level's tileset and palette:\n\n",target);

    fputs("\tmemcpy((void*)BG_TILE_RAM(2), ",target);
    fputs(levelname,target);
    fputs("_tiles_bin, ",target);
    fputs(levelname,target);
    fputs("_tiles_bin_size);\n",target);

    fputs("\tmemcpy((void*)BG_PALETTE, ",target);
    fputs(levelname,target);
    fputs("_pal_bin, ",target);
    fputs(levelname,target);
    fputs("_pal_bin_size);\n\n",target);

    fputs("\t\treturn (rstruct);\n",target);
    fputs("\t}\n\n",target);

    fputs("\t//Level not loaded:\n\n",target);

    //Else:

    fputs("\telse\n\n",target);
    fputs("\t{\n",target);

    fputs("\t\trstruct.width                =  ",target);
    fputs("0;\n",target);

    fputs("\t\trstruct.height               =  ",target);
    fputs("0;\n",target);

    fputs("\t\trstruct.maplayout            =  ",target);
    fputs("0;\n",target);

    fputs("\t\trstruct.footersize           =  ",target);
    fputs("0;\n",target);

    fputs("\t\trstruct.numberOfEntrypoints  =  ",target);
    fputs("0;\n",target);

    fputs("\t\trstruct.entrypointList       =  ",target);
    fputs("0;\n\n",target);

    fputs("\t\treturn (rstruct);\n",target);
    fputs("\t}\n\n",target);









    fputs("}//End of function lvl_loadLevel\n\n",target);

    fputs("#endif //LEVELS_H",target);


    fclose(source);
    fclose(target);
    free(levels_h);

}

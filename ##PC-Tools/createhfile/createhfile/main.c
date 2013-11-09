#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
   FILE *source;
   FILE *target;


    if(argc < 3)
    {
        printf("Arguments wrong!!\n");
        exit (1);
    }



    target = fopen (argv[2],"r+b");

    if (target == 0)
    {
        printf("Couldn't open target file");
        exit (1);
    }

    fseek(target,-1,SEEK_END);

    int i = 0;

    while(fgetc(target) != '#')
    {
        fseek(target,-2,SEEK_CUR);
        i++;
    }

    fseek(target,-2,SEEK_CUR);

    for (i; i >= 0; i--) fputc(' ',target);
    fputc('\n',target);

    fclose(target);

    target = fopen (argv[2],"ab");

      if (target == 0)
    {
        printf("Couldn't open target file for append.");
        exit (1);
    }

    char *line;
    line = malloc(200);

    i = 0;
    char a;

    source = fopen (argv[1],"rb");
    if (source == 0)
    {
        printf("Couldn't open source file");
        exit (1);
    }

    while(1)
    {
        for (i = 0; i < 200; i++)
        {
            a = fgetc(source);
            if (feof(source) != 0)
            {
                fputc('\n',target);
                fputs("#endif \\\\LEVELS_H",target);

                free(line);
                fclose(source);
                fclose(target);

                exit(0);
            }


            if (a != '.')
            {
                line[i]=a;
            }
            else break;

        }

        line[i] = 0;

        fputs("#include \"",target);
        fputs(line,target);
        fputs("_bin.h\"\n",target);

        while(a = fgetc(source) != '\n')
        {
            if (feof(source) != 0)
            {
                fputc('\n',target);
                fputs("#endif \\\\LEVELS_H",target);

                free(line);
                fclose(source);
                fclose(target);

                exit(0);
            }
        }



    }





}

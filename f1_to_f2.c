#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[])
{
    char *firstFileName, *secondFileName;
    if (argc > 2)
    {
        firstFileName = argv[1];
        secondFileName = argv[2];
    }
    else 
    {
        printf("file name not specified");
        return 1;
    }
    FILE *f1 = fopen(firstFileName, "r");
    FILE *f2 = fopen(secondFileName, "w");   
    char s[255];
    while((fgets(s, 255, f1)) != NULL)
    {
        if (s[strlen(s) - 1] != '\n')
        {
            fprintf(f2, "%s\n%s", s, s);
        }
        else 
            fprintf(f2, "%s%s", s, s);
    }    
    fclose(f1);
    fclose(f2);

    return 0;
}

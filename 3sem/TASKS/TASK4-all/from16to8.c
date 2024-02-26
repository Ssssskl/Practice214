#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define L_E 0xFFFE
#define B_E 0xFEFF
#define big 1
#define little 0

int main(int argc, char **argv) 
{
    FILE *file_in;
    FILE *file_out;

    file_in = stdin;
    file_out = stdout;

    char utf8_1, utf8_2, utf8_3;
    unsigned short utf16 = 0;
    unsigned short bom;

    if (argc > 1)
    {
        if (strcmp(argv[1], "-i") != 0)
        {
            printf("error\n");
            exit(EXIT_FAILURE);
        }
        else
        {
            if ((file_in = fopen(argv[2], "r")) == NULL) 
            {
                perror(argv[2]);
                exit(EXIT_FAILURE);
            }
        }  
        if (argc > 3)
        {
            if (strcmp(argv[3], "-o") != 0)
            {
                printf("error\n");
                exit(EXIT_FAILURE);
            }
            else
            {
                if ((file_out = fopen(argv[4], "w")) == NULL) 
                {
                    perror(argv[4]);
                    exit(EXIT_FAILURE);
                }
            }
        }  
    }
    
    int number_of_bytes; 

    number_of_bytes = fread(&utf16, sizeof(char), 2, file_in);

    if (number_of_bytes == 2) 
    {
        if (utf16 == B_E) 
        {
            bom = little;
        } 
        else if (utf16 == L_E) 
        {
            bom = big;
        } 
        else if (argc > 5) 
        {
            if (argc == 6) 
            {
                if (strcmp(argv[5], "-le") == 0) 
                {
                    bom = little;
                    fseek(file_in, 0, SEEK_SET);
                } 
                else if (strcmp(argv[5], "-be") == 0) 
                {
                    bom = big;
                    fseek(file_in, 0, SEEK_SET);
                }
            } 
            else 
            {
                if (((strcmp(argv[5], "-le") == 0) && (strcmp(argv[6], "-be") == 0)) ||
                    ((strcmp(argv[5], "-be") == 0) && (strcmp(argv[6], "-le") == 0))) {
                    fprintf(stderr, "\n");
                    exit(EXIT_FAILURE);
                }
            }
        } 
        else 
        {
            bom = little;
            fprintf(stderr, "Bom is not announced, -le is set by default\n");
            fseek(file_in, 0, SEEK_SET);
        }
    } 
    else 
    {
        bom = little;
        fprintf(stderr, "Number of bytes is less than 2\n");
        fseek(file_in, 0, SEEK_SET);
    }

    number_of_bytes = fread(&utf16, sizeof(char), 2, file_in);

    while (number_of_bytes == 2) 
    {
        if (bom == big) 
        {  
            utf8_1 = (char)(utf16 >> 8); 
            utf16 <<= 8;
            utf16 += utf8_1;
        }
        if (utf16 < 128) 
        {
            utf8_1 = (char) utf16;
            fwrite(&utf8_1, 1, 1, file_out);
        } 
        else if (utf16 < 2048) 
        {
            utf8_2 = (char)(utf16 & 0x3F);  
            utf8_2 += 128;
            utf16 >>= 6;
            utf8_1 = (char)(utf16);
            utf8_1 += 128 + 64;
            fwrite(&utf8_1, 1, 1, file_out);
            fwrite(&utf8_2, 1, 1, file_out);
        } 
        else 
        {
            utf8_3 = (char)(utf16 & 0x3F);  
            utf8_3 += 128;
            utf16 >>= 6;
            utf8_2 = (char)(utf16 & 0x3F);  
            utf8_2 += 128;
            utf16 >>= 6;
            utf8_1 = (char)(utf16);
            utf8_1 += 128 + 64 + 32;
            fwrite(&utf8_1, 1, 1, file_out);
            fwrite(&utf8_2, 1, 1, file_out);
            fwrite(&utf8_3, 1, 1, file_out);
        }
        number_of_bytes = fread(&utf16, sizeof(char), 2, file_in);
    }

    if (number_of_bytes == 1) 
    {
        fprintf(stderr, "Incorrect number of bytes, pairs can't be matched\n");
    }

    fclose(file_in);
    fclose(file_out);
    return 0;
}

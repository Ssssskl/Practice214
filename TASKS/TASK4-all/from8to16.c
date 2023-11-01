#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define L_E 0xFFFE
#define B_E 0xFEFF

int main(int argc, char **argv)
{
    FILE *file_in;
    FILE *file_out;

    file_in = stdin;
    file_out = stdout;

    unsigned char utf8 = 0, correct_in = 0;
    unsigned short utf16 = 0;
    unsigned short bom = B_E;

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

    if (argc > 5)
    {
        if (argc == 7) 
        {
            if ((strcmp(argv[5], "-be") == 0) && (strcmp(argv[6], "-le") == 0) || (strcmp(argv[5], "-le") == 0) && (strcmp(argv[6], "-be") == 0)) 
            {
                fprintf(stderr, "Different decoding ways\n");
                exit(EXIT_FAILURE);
            }
        } 
        else 
        {
            if (argc == 6) 
            {
                if (strcmp(argv[5], "-be") == 0) 
                {
                    bom = B_E;
                } 
                else if (strcmp(argv[5], "-le") == 0) 
                {
                    bom = L_E;
                }
            } 
            else 
            {
                bom = L_E;
            }
        }
    }
    
    unsigned char utf8_byte1 = 0, utf8_byte2 = 0, utf8_byte3 = 0;

    fread(&utf8_byte1, sizeof(unsigned char), 1, file_in);
    fread(&utf8_byte2, sizeof(unsigned char), 1, file_in);
    fread(&utf8_byte3, sizeof(unsigned char), 1, file_in);

    if ((!((utf8_byte1 = 0xEF) && (utf8_byte2 = 0xBB) && (utf8_byte3 = 0xBF))) || (!((utf8_byte1 == 0xEF) && (utf8_byte2 == 0xBF) && (utf8_byte3 == 0xBE))))
    {
        fseek(file_in, 0, SEEK_SET);
    }

    fwrite(&bom, sizeof(unsigned short), 1, file_out);
    fread(&utf8, sizeof(unsigned char), 1, file_in);
    
    while (!feof(file_in))
    {
        utf16 = 0;
        if ((utf8 >> 7) == 0)  //0 x x x x x x x
        {
            utf16 += utf8;
            correct_in = 1;
        }
        else if ((utf8 >> 5) == 0x6) //1 1 0 x x x x x  
        {
            utf8 &= 0x1F;  // mul on mask 00011111
            utf16 += utf8;
            utf16 <<= 6;
            fread(&utf8, sizeof(unsigned char), 1, file_in);
            if ((utf8 >> 6) == 0x2) // 1 0 y y y y y y
            {
                utf8 &= 0x3F; // mul on mask 00111111
                utf16 += utf8;
                correct_in = 1;
            }
            else
            {
                fprintf(stderr, "Second byte of two bytes in pair is incorrect." 
                            "It is: %hx with position %ld\n", utf8, ftell(file_in));
            }
        }
        else if ((utf8 >> 4) == 0xE) // 1 1 1 0 x x x x 
        {
            utf8 &= 0xF; // mul on mask 00001111
            utf16 += utf8;
            utf16 <<= 6;
            fread(&utf8, sizeof(unsigned char), 1, file_in);
            if ((utf8 >> 6) == 0x2) //1 0 y y y y y y
            {
                utf8 &= 0x3F; // mul on mask 00111111
                utf16 += utf8;
                utf16 <<= 6;
                fread(&utf8, sizeof(unsigned char), 1, file_in);
                if ((utf8 >> 6) == 0x2) //1 0 z z z z z z
                {
                    utf8 &= 0x3F; // mul on mask 00111111
                    utf16 += utf8;
                    correct_in = 1;
                }
                else 
                {
                    fprintf(stderr, "Third byte of tree bytes in triplet is incorrect."
                        "It is: %hhx with position %ld\n", utf8, ftell(file_in));
                }
            }
            else 
            {
                fprintf(stderr, "Second byte of tree bytes in triplet is incorrect." 
                        "It is: %hhx with position %ld\n", utf8, ftell(file_in));
            }
        }
        else
        {
            fprintf(stderr, "First byte is incorrect."
                            "It is: %hhx with position %ld\n", utf8, ftell(file_in));
        }

        if (correct_in)
        {
            if (bom == L_E)
            {
                utf8 = (unsigned char) (utf16 >> 8); // mul on mask 1111111100000000
                fwrite(&utf8, sizeof(unsigned char), 1, file_out);
                utf8 = (unsigned char) (utf16); // mul on mask 0000000011111111
                fwrite(&utf8, sizeof(unsigned char), 1, file_out);
            }
            else
            {
                fwrite(&utf16, sizeof(unsigned short), 1, file_out);
            }
            correct_in = 0;
        }
        fread(&utf8, sizeof(unsigned char), 1, file_in);
    }

    fclose(file_in);
    fclose(file_out);
    return 0;
}
    

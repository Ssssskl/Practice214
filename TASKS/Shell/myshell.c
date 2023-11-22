#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


#define COLOR_GREEN "\e[1;32m"
#define RESET "\e[m"


int flag_eof = 0;
int flag_quot = 0;
int kol = 0;
int quot_pair = 0;
int file = 0;
int new_line = 0;
int errors = 0;

const char special_symbols[5] = "&|<>\0";
const char single_symbols[4] = ";()\0";

char *read_word(FILE *file_in)
{
    int is_word = 0;
    int is_spec_sym = 0;
    char c = 0;
    int iword = 0;
    char *word = (char *)malloc(sizeof(char));
    word[iword] = 0;

    while ((c = getc(file_in)) != EOF) 
    {
        if (flag_quot) 
        {
            if(c == '\n')
            {
                new_line = 1;
                flag_quot = 0;
                fprintf(stderr,"Invalid quality of quotes\n");
                errors = 1;
                free(word);
                return NULL;
            } 
            if (c == '"') 
            {
                flag_quot = 0;
            } 
            else 
            {
                word = (char *)realloc(word, (iword + 2) * sizeof(char));
                word[iword] = c;
                iword++;
            }
        } 
        else if (is_spec_sym) 
        {
            is_spec_sym = 0;
            if (c == word[iword - 1]) 
            {
                word = (char *)realloc(word, (iword + 2) * sizeof(char));
                word[iword] = c;
                iword++;
                word[iword] = 0;
                return word;
            } 
            else 
            {
                ungetc(c, file_in);
                word[iword] = 0;
                return word;
            }
        } 
        else if (isspace(c)) 
        {
            if (is_word) 
            { 
                if (c == '\n') 
                {
                    new_line = 1;
                }
                word[iword] = 0;
                return word;
            } 
            else 
            { 
                if (c == '\n') 
                {
                    new_line = 1;
                    free(word);
                    word = NULL;
                    return NULL;
                }
                continue; 
            }
        } 
        else if (c == '"') 
        {
            is_word = 1;
            flag_quot = 1;
        }
        else if (strchr(special_symbols, c)) 
        {
            if (is_word) 
            {
                ungetc(c, file_in);
                word[iword] = 0;
                return word;
            } 
            else 
            {
                is_spec_sym = 1;
                word = (char *)realloc(word, (iword + 2) * sizeof(char));
                word[iword] = c;
                iword++;
            }
        } 
        else if (strchr(single_symbols, c)) 
        {
            if (is_word) 
            {
                ungetc(c, file_in);
                word[iword] = 0;
                return word;
            } 
            else 
            {
                word = (char *)realloc(word, (iword + 2) * sizeof(char));
                word[0] = c;
                word[1]= '\0';
                return word;
            }
        } 
        else 
        {               
            is_word = 1;
            word = (char *)realloc(word, (iword + 2) * sizeof(char));
            word[iword] = c;
            iword++;
        }
    }
    flag_eof = 1;
    if (word != NULL) 
    {
        free(word);
        return NULL;
    } else 
    {
        word[iword] = 0;
        return word;
    }
}

char **add_to_massiv (char **massiv, char *word)
{
    massiv = realloc(massiv, (kol + 2)*sizeof(char*));
    massiv[kol] = word;
    kol ++;
    massiv[kol] = NULL;
    return massiv;
}

void free_massiv(char** massiv)
{
    while(*massiv != NULL)
    {
        free(*massiv);
        massiv++; 
    }
}

// void massiv_out(char **massiv)
// {
//     char** newmassiv = massiv;
//     while (*newmassiv != NULL) 
//     {
//         printf("%s\n",*newmassiv);
//         newmassiv++;
//     }
// }

int is_cd(char **massiv) 
{
    if (!strcmp(massiv[0], "cd")) 
    {
        if (massiv[1] == NULL) 
        {
            chdir(getenv("HOME"));
        } 
        else if ((massiv[2] != NULL) || chdir(massiv[1])) 
        {
            printf("Error in changing directory\n");
            return -1;
        }
        return 1;
    }
    return 0;
}

int main(int argc, char ** argv)
{
    FILE *file_in;
    
    file_in = stdin;

    char *word;
    char **massiv;

    if (argc == 2)
    {
        file_in = fopen(argv[1], "r");
        file = 1;
    }

    while(!flag_eof)
    {
        if (!file)
        {
            printf("%s> %s", COLOR_GREEN, RESET); 
        }

        kol = 0;
        massiv = malloc(sizeof(char*));
        new_line = 0;
        errors = 0;

        while(!flag_eof && !new_line && !errors)
        {
            word = read_word(file_in);
            massiv = add_to_massiv(massiv, word);
        }
        if (errors)
        {
            free_massiv(massiv);
            free(massiv);
            continue;
        }
        if (!flag_eof && (*massiv != NULL))
        {
            //massiv_out(massiv);
            if ((is_cd(massiv)) == 0)
            {
                pid_t pid = fork();    

                if (pid == -1) //process ended with trouble
                {
                    perror("System error");
                    exit(1);
                }
                else if (pid == 0) // process ended normally
                {
                    execvp(massiv[0], massiv);
                    perror("Error");
                    exit(2);   
                }
                wait(0);
            }
                
        } 
        free_massiv(massiv);
        free(massiv);
    }

    if (argc == 2)
    {
        fclose(file_in);
    } 
    printf("\n");
    return 0;
}

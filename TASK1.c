#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int M = 10;

char* readstr(void)
{
    int n, k = 0;
    char* s = malloc(M);
    if (s == NULL) 
        return NULL;
    while (fgets(s+k, M, stdin))
    {
        n = strlen(s);
        if (s[n-1] != '\n')
        {
            k = k+M-1;
            s = realloc(s,k+M);
            if (s == NULL) 
                return NULL;
        }
        else
        {
            s[n-1] = '\0';
            return s;
        }
    }
    free(s);
    return NULL;   
}

char** massiv(void)
{
    int n = 0, k = M;
    char **strings = malloc(k*sizeof(char*));
    char* s = readstr();
    while (s != NULL)
    {   
        if (n >= k - 1)
        {
            k = k + M;
            strings = realloc(strings, k*sizeof(char*));
        }
        strings[n] = s;
        n++;
        s = readstr();
    }
    return strings;
    
}

void sort_str(char** strings)
{
    char *s;
    for (int i=0; strings[i] != NULL; i++)
    {
        for (int j=i+1; strings[j] != NULL; j++)
        {
            if (strcmp(strings[i], strings[j]) > 0)
                {
                    s = strings[i];
                    strings[i] = strings[j];
                    strings[j] = s;
                }
        }
    }

}

void out (char** strings){
    while (*strings != NULL) {
        printf("%s\n",*strings);
        strings++;
    }
}

void del_all(char** strings)
{
    while (*strings != NULL)
    {
        free(*strings);
        strings ++;
    }
}


int main()
{
    char **strings = malloc(M*sizeof(char*));;
    strings = massiv();
    printf("%s\n", "Sorted array:");
    sort_str(strings);
    out(strings);
    del_all(strings);
    free(strings);
}

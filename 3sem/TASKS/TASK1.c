#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define M 10

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

/*char** massiv(void)
{
    int n = 0, k = M;
    char **strings = calloc(k, sizeof(char*));
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
}*/

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
    int n = 0, k = M;
    char **strings = calloc(k, sizeof(char*));
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
    strings[n] = NULL;
    char** str;
    printf("%s\n", "Sorted array:");
    sort_str(strings);
    str = strings;
    for (*str; *str != NULL; str++)
    {
        printf("%s\n", *str);
    }
    del_all(strings);
    free(strings);
}

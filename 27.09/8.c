#include <stdio.h>
#include <string.h>

char* strstr1 (char *s1, char *s2)
{
    if (s1 == NULL || s2 == NULL)
        return NULL;
    int i = 0;
    int lena = strlen(s2);
    while (*s1)
    {
        if (*s1 == *s2)
        {
            i++;
            if (i == lena)
                return s1 - lena +1;
            s2++;
        }
        else
        {
            s2 = s2 - i;
            i = 0;
        }
        s1++;
    }
    return NULL;
}


int main(int argc, char* argv[])
{
    for(int i = 1; i < argc; i++)
    {
        char* s1 = argv[i]; 
        char* s2 = strstr1(s1, "end");
        while ( s2 != NULL) 
        {
            s1 = s2;
            s2 = strstr1(s2+1, "end");
        }
        printf("%s\n", s1);
    }
}


#include <stdio.h>
#include <string.h>

int mystrcmp(char *s1, char *s2)
{
    for (*s1,*s2; (*s1==*s2) && (*s1!=0) && (*s2!=0); s1++, s2++);
        if (*s1<*s2) 
            return -1;
        else
            if (*s1>*s2)
                return 1;
            else
                return 0; 
}

int main()
{
    char s1[]="asdfg";
    char s2[]="asdfg";
    printf("%d\n", mystrcmp(s1,s2));
}

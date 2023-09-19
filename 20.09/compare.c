#include <stdio.h>
#include <string.h>

int mystrcmp(char *s1, char *s2)
{
    for (*s1,*s2; (*s1==*s2) && (*s1!=0); s1++, s2++);
    if (*s1!=*s2) 
        return 0;
    else
        return 1;
}

int main()
{
    char s1[]="asdfg";
    char s2[]="asdfgee";
    printf("%d\n", mystrcmp(s1,s2));
}
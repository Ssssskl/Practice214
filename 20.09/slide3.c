#include <stdio.h>
#include <string.h>

void copy (char src[], char dst[])
{
    while (*dst++=*src++);
}


void cdelete(char *s, char c)
{
    while (*s!=0)
    {
        if (*s==c)
        {
            copy(s+1,s);
            continue;
        }
        s++;     
    }  
} 

int main()
{
    char s[]="dadadadada";
    char c='d';
    cdelete(s,c);
    printf("%s\n", s);
}
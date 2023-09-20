#include <stdio.h>
#include <string.h>

char * copy (char *src, char *dst)
{
    char *ret=dst;
    while (*src)
    {
        *dst=*src;
        src++;
        dst++;
    }
    *dst=0;
    return ret;
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

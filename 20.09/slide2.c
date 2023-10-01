#include <stdio.h>
#include <string.h>

void reverse(char *s)
{
    char c;
    char *m=s+strlen(s)-1;
    for (*m, *s; m>s; m--, s++)
    {
        c=*s;
        *s=*m;
        *m=c;
    }
} 

int main()
{
    char s[]="asdfg";
    reverse(s);
    printf("%s\n", s);
}

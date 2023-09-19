#include <stdio.h>
#include <string.h>

void reverse(char *s)
{
    int m=strlen(s);
    char c;
    for (int i=0; i<m/2; i++)
    {
        c=s[i];
        s[i]=s[m-i-1];
        s[m-i-1]=c;
    }
    printf("%s\n", s);
} 

int main()
{
    char s[]="asdfg";
    reverse(s);
}

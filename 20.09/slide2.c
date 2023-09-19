#include <stdio.h>
#include <string.h>

void reverse(char s[])
{
    int m=strlen(s);
    char с;
    for (int i=0; i<m/2; i++)
    {
        с=s[i];
        s[i]=s[m-i-1];
        s[m-i-1]=с;
    }
    printf("%s", s);
} 

int main()
{
    char s[]="qwer";
    reverse(s);
}
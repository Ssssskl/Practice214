#include <stdio.h>
#include <string.h>

void reverse(char s[])
{
    int m=strlen(s);
    char l[m];
    for (int i=m-1; i>=0; i--)
    {
        l[m-i-1]=s[i];
    }
    printf("%s\n", l);
} 

int main()
{
    char s[]="dfghjkl";
    reverse(s);
}
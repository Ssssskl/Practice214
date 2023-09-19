#include <stdio.h>
#include <string.h>

void cdelete(char s[], char c)
{
    int k=0;
    for (int i=0; i<strlen(s); i++)
    {
        if (s[i]==c)
            k+=1;
    }
    int m=strlen(s)-k;
    char l[m];
    int j=0;
    for (int i=0; i<strlen(s); i++)
    {
        if (s[i]!=c)
        {
            l[j]=s[i];
            j++;
        }
    }
    s=l;
    printf("%s\n", s);
} 

int main()
{
    char s[]="ddddaa";
    char c='d';
    cdelete(s,c);
}
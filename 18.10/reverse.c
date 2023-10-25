#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack{
    char * str;
    struct stack *next;
} stack;

void put_in(stack ** st, char *str)
{
    stack *st1;
    st1 = malloc(sizeof(stack));
    st1 -> str = malloc(strlen(str) + 1);
    strcpy(st1 -> str, str);
    st1 -> next = *st;
    (*st) = st1;
}

void print_Stack(stack *st)
{
    while(st != NULL)
    {
        printf("%s", st -> str);
        st = st -> next;
    }
    return;
}


int main(int argc, char *argv[])
{
    FILE *f = fopen("./file1.txt", "r");
    stack *st =NULL;
    char *s;
    while((s = fgets(s, 255, f)) != NULL)
    {
        if(strlen(s) <= 7) 
        {
            put_in(&st, s);
        }
    }
    print_Stack(st);
    fclose(f);
    return 0;
}
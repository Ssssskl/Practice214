#include <stdio.h>
#include <stdlib.h>

typedef struct stack{
    int i;
    struct stack *next;
} stack;

void put_in(stack ** st, int i)
{
    stack *st1;
    st1 = malloc(sizeof(stack));
    st1 -> i = i;
    st1 -> next = *st;
    (*st) = st1;
}

void print_Stack_in_file(stack *st, FILE *f)
{
    while(st != NULL)
    {
        fprintf(f, "%d", st -> i);
        st = st -> next;
    }
    return;
}

int main(int argc, char *argv[])
{
    FILE *f = fopen("./file1.txt", "r");
    stack *st =NULL;
    int n;
    while(fscanf(f, "%d", &n) != EOF)
    {
        put_in(&st, n);
    }
    f = fopen("./file.txt", "w");
    print_Stack_in_file(st, f);
    fclose(f);
    return 0;
}

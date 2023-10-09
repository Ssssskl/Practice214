#include <stdio.h>
#include <string.h>

/*
Описать структуру однонаправленного списка целых чисел,
-- написать функцию,
      --- вставляющую заданный элемент в конец заданного списка,
      ---  удаляющую первое вхождение заданного элемента из заданного списка,
      ---  удаляющую все вхождения заданного элемента из заданного списка.
*/
struct list
{
    int value;
    struct list *next;
};


void toend (struct list *next, int elem)
{
    struct list *m, *t;
    m = next;
    while (m -> next) 
    {
        m = m -> next;
    }
    t = (struct list*)malloc(sizeof(struct list));
    t -> value = elem;
    t -> next = NULL;
    m -> next = t;
}


void del_1 (struct list *next, int elem)
{
    struct list *p, *m;
    p = NULL;
    m = next;
    while (m != NULL)
    {
        if ( m -> value = elem)
        {
            p -> next = m -> next;
            free(m);
            break;
        }
        p = m;
        m = m -> next;
    }
}

void del_all(struct list *next, int elem)
{
    struct list *p, *m;
    p = NULL;
    m = next;
    while (m != NULL)
    {
        if ( m -> value = elem)
        {
            p -> next = m -> next;
            free(m);
        }
        p = m;
        m = m -> next;
    }
}

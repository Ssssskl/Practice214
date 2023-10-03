#include <stdio.h>
#include <string.h>

/*Описать структуру дерева двоичного поиска  (элементы целочисленные),
-- написать функцию, распечатывающую числа, хранящиеся в дереве, по возрастанию. 
*/

struct tree {
  int value;           
  struct tree *left;  
  struct tree *right; 
};

void PrintTree (struct tree *r)
{
    while (r -> left != NULL)
    {
        PrintTree (r -> left);
        printf("%d\n", r -> value);
        PrintTree (r -> right);
    }
}

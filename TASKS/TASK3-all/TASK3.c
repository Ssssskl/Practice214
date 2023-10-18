#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define M 10

typedef struct tree
{
    char *word;
    int counter;
    struct tree *left;
    struct tree *right;
} tree;



void insert(tree **t, char* w) 
{
    if (*t == NULL) 
    {
        *t = malloc(sizeof(tree));
        int l = strlen(w) + 1;
        (*t) -> word = malloc(l);
        strcpy((*t) -> word, w);
        (*t) -> left = NULL;
        (*t) -> right = NULL;
        (*t) -> counter = 1;
        return;
    }
    if (strcmp(w, (*t) -> word) > 0) 
    {
        insert(&((*t) -> right), w);
    } 
    else if (strcmp(w, (*t) -> word) < 0) 
    {
        insert(&((*t) -> left), w);
    }
    else 
    {
        (*t) -> counter ++;
    }
}

char *read_word (FILE *file)
{
    int n = M, k = 0, c = 0;
    char *s = malloc(M);
    c = fgetc(file);
    if (c == EOF)
    {
        free(s);
        return NULL;
    }
    if (ispunct(c) || isspace(c)) 
    {
        *s = c;
        *(s + 1) = '\0';
        return s;
    }
    if (isdigit(c))
    {
        while (isdigit(c))
        {
            *(s + k) = c;
            k++;
            c = fgetc (file);
        }
        *(s + k) = '\0';
        return s;
    }
    while (c != '\n')
    {
        if (ispunct(c) || isspace(c))
        {
            ungetc(c, file);
            *(s + k) = '\0';
            return s;
        }
        if (k == n - 2)
        {
            s = realloc(s, k + M);
            n += M;
            if (!s) 
                return NULL;
        }
        *(s + k) = c;
        k++;
        c = fgetc(file);
    }
    *(s + k) = '\0';
    return s;
}

void printTree(tree *t, int n) 
{ 
    if (t != NULL) 
    {
        printTree(t -> left, n);
        double cred = (double)(t -> counter)/n;
        printf("%s   %d   %f\n", t -> word, t -> counter, cred);
        printTree(t -> right, n);
    }
}

void build_new_tree(tree **out, tree **t)
{
	if (*out == NULL)
    {
        *out = malloc(sizeof(tree));
        (*out) -> word = (*t) -> word;	
        (*out) -> counter = (*t) -> counter;
        (*out) -> left = (*out) -> right = NULL;
        return;
    }
    if ((*out) -> counter < (*t) -> counter) 
        build_new_tree(&((*out) -> left), t);
    else 
        build_new_tree(&((*out) -> right), t);
}

void insert_new_tree(tree **out, tree **t)
{
	if((*t) == NULL) 
        return;
	insert_new_tree(out, &(*t) -> right);
	build_new_tree(out, t);
	insert_new_tree(out, &(*t) -> left);
}

void tree_free_word(tree **t)
{
    if((*t) == NULL) 
        return;
    tree_free_word(&((*t) -> left));
    tree_free_word(&((*t) -> right));
    free((*t) -> word);
}

void tree_free(tree** t)
{
    if ((*t) == NULL) 
        return;
    tree_free(&((*t) -> left));
    tree_free(&((*t) -> right));
    free(*t);
}

int main()
{
    FILE *file;
    file = fopen ("./hotel.txt" , "r");
    tree *t = NULL;
    tree *out = NULL;
    int num = 0;
    char *word;
    while ((word = read_word(file)) != NULL)
    {
        if ((*word == 0) || isspace(*word))
        {
            free(word);
            continue;
        }
        num++;
        insert(&t, word);
        free(word);
    }
    insert_new_tree(&out, &t);
    printTree(out, num);
    tree_free_word(&t);
    tree_free(&t);
	tree_free(&out);
    fclose(file);
}

/*
Prefix = atas, kiri, kanan
Postfix = kiri,kanan,atas
Infix = kiri,atas,kanan
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct treenode
{
    char value;
    struct treenode *left, *right;
} treenode;

treenode *createnode(char value)
{
    treenode *newnode = (treenode *)malloc(sizeof(treenode));
    if (newnode != NULL)
    {
        newnode->left = newnode->right = NULL;
        newnode->value = value;
        return newnode;
    }
    return NULL;
}

int main()
{
    char infix[] = "A + B * C";
}
#include <stdio.h>
#include <stdlib.h>

void confirm()
{
    getchar();
    getchar();
}

typedef struct treenode
{
    int value;
    struct treenode *left, *right;
} treenode;

treenode *createnode(int value)
{
    // malloc it
    treenode *newnode = (treenode *)malloc(sizeof(treenode));

    // check it malloc succeed,
    // if it does then set left right as NULL and pass the value

    if (newnode != NULL)
    {
        newnode->left = NULL;
        newnode->right = NULL;
        newnode->value = value;
    }

    // return the newnode that has been created
    return newnode;
}

void insertBranch(treenode *root, int currentIndex, int *array, int len)
{
    // insert to left
    if (currentIndex * 2 <= len)
    {
        root->left = createnode(array[currentIndex * 2]);
    }
    // insert to right
    if (currentIndex * 2 + 1 <= len)
    {
        root->right = createnode(array[currentIndex * 2 + 1]);
    }
    // if checking already out of bound from array then exit
    if (currentIndex * 2 + 1 > len)
    {
        return;
    }
    // recursion
    insertBranch(root->left, currentIndex * 2, array, len);
    insertBranch(root->right, currentIndex * 2 + 1, array, len);
}

void printTree(treenode *root)
{
    if (!root)
    {
        return;
    }
    else
    {
        printTree(root->left);
        printf("%d ", root->value);
        printTree(root->right);
    }
}

int main()
{
    int len;
    printf("Enter length of array: ");
    scanf("%d", &len);
    printf("Array: ");
    int *array = (int *)malloc((len + 1) * sizeof(int));
    for (int i = 1; i <= len; i++)
    {
        scanf("%d", &array[i]);
    }
    treenode *root = createnode(array[1]);
    insertBranch(root, 1, array, len);
    printf("Tree: ");
    printTree(root);
    free(root);
}
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
    struct treenode *left;
    struct treenode *right;
} treenode;

treenode *createnode(int value)
{
    treenode *newnode = (treenode *)malloc(sizeof(treenode));
    if (newnode != NULL)
    {
        newnode->left = NULL;
        newnode->right = NULL;
        newnode->value = value;
    }
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
    // return call if one recursion already exceed len (the array)
    if (currentIndex * 2 + 1 > len)
    {
        return;
    }

    // the recursions
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
        // go to the leftmost leaf
        printTree(root->left);
        printf("%d ", root->value);
        printTree(root->right);
    }
}

int main()
{
    int len;
    printf("Length of array: ");
    scanf("%d", &len);
    printf("Array: ");
    int *array = (int *)malloc((len + 1) * sizeof(int));
    for (int i = 1; i <= len; i++)
    {
        scanf("%d", &array[i]);
    }
    treenode *root = createnode(array[1]);
    insertBranch(root, 1, array, len);
    printf("Tree: \n");
    printTree(root);
    puts("");
    printf("%d", root->left->left->value);
    free(root);
}
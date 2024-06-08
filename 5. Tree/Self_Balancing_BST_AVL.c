#include <stdio.h>
#include <stdlib.h>

// kurang delete liat aja
// https://www.geeksforgeeks.org/deletion-in-an-avl-tree/

typedef struct treenode
{
    int value;
    struct treenode *left, *right;
    int height;
} treenode;
treenode *root = NULL;

treenode *newnode(int value)
{
    treenode *newnode = (treenode *)malloc(sizeof(treenode));
    newnode->value = value;
    newnode->left = newnode->right = NULL;
    newnode->height = 1; // is leaf
    return newnode;
}

int height(treenode *temp)
{
    if (temp == NULL)
    {
        return 0;
    }
    return temp->height;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int balanceFactor(treenode *temp)
{
    if (temp == NULL)
    {
        return 0;
    }
    return (height(temp->left) - height(temp->right));
}

treenode *rightRotate(treenode *target)
{
    treenode *leftChild = target->left;
    treenode *rightSubLeftChild = leftChild->right;

    // the rotation
    leftChild->right = target;
    target->left = rightSubLeftChild;

    // update height
    target->height = max(height(target->left), height(target->right)) + 1;
    leftChild->height = max(height(leftChild->left), height(leftChild->right)) + 1;

    // return newnode idk
    return leftChild;
}

treenode *leftRotate(treenode *target)
{
    treenode *rightChild = target->right;
    treenode *leftSubRightChild = rightChild->left;

    // the rotation
    rightChild->left = target;
    target->right = leftSubRightChild;

    // update height
    target->height = max(height(target->left), height(target->right)) + 1;
    rightChild->height = max(height(rightChild->left), height(rightChild->right)) + 1;

    return rightChild;
}

treenode *STDinsert(treenode *root, int value)
{
    // 1. Basic BST insert

    if (root == NULL)
    {
        return (newnode(value));
    }

    if (root->value > value)
    {
        root->left = STDinsert(root->left, value);
    }
    else if (root->value < value)
    {
        root->right = STDinsert(root->right, value);
    }
    else // means equal to the root, not allowed
    {
        return root;
    }
    // somewhere here i started going up ??? wtf
    // yes i just checked. at this point after recursively going down
    // it also starts going up. "RECURSIVE UNWINDING"
    // IT EXECUTES THE WHOLE BLOCK BELOW EVERYTIME UNTIL ROOT.

    // BELOW ROOT IS = TO CURRENT NODE (THAT IS UNWINDING UP)!

    // 2. Update height of ancestor node
    root->height = max(height(root->left), height(root->right)) + 1;

    // 3. Checking if the current inserted node is unbalanced or not
    int BF = balanceFactor(root);

    // left left case (LL)
    if (BF > 1 && root->left->value > value)
    {
        return rightRotate(root);
    }

    // Right right case (RR)
    if (BF < -1 && root->right->value < value)
    {
        return leftRotate(root);
    }

    // Left right case (LR)
    if (BF > 1 && root->left->value < value)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right left case (RL)
    if (BF < -1 && root->right->value > value)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    // return new root
    return root;
}

void preOrder(treenode *root)
{
    if (root != NULL)
    {
        printf("%d ", root->value);
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main()
{
    root = STDinsert(root, 10);
    root = STDinsert(root, 20);
    root = STDinsert(root, 30);
    root = STDinsert(root, 40);
    root = STDinsert(root, 50);
    root = STDinsert(root, 25);
    printf("Preorder of AVL: ");
    preOrder(root);
}
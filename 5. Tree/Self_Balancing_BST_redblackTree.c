#include <stdio.h>
#include <stdlib.h>

typedef struct treenode
{
    int value;
    int color; // 1-red | 0-black
    struct treenode *left, *right, *parent;
} treenode;

treenode *root = NULL;

treenode *STDinsert(treenode *node, treenode *temp)
{
    if (node == NULL)
    {
        return temp;
    }
    if (temp->value < node->value)
    {
        node->left = STDinsert(node->left, temp);
        node->left->parent = node;
    }
    else if (temp->value > node->value)
    {
        node->right = STDinsert(node->right, temp);
        node->right->parent = node;
    }
    return node;
}

treenode *leftRotate(treenode *temp)
{
    treenode *right = temp->right;
    temp->right = right->left;
    if (temp->right)
    {
        temp->right->parent = temp;
    }
    right->parent = temp->parent;
    if (!temp->parent)
    {
        root = right;
    }
    else if (temp == temp->parent->left)
    {
        temp->parent->left = right;
    }
    right->left = temp;
    temp->parent = right;
}

treenode *rightRotate(treenode *temp)
{
    treenode *left = temp->left;
    temp->left = left->right;
    if (temp->left)
    {
        temp->left->parent = temp;
    }
    left->parent = temp->parent;
    if (!temp->parent)
    {
        root = left;
    }
    else if (temp == temp->parent->left)
    {
        temp->parent->left = left;
    }
    else
    {
        temp->parent->right = left;
    }
    left->right = temp;
    temp->parent = left;
}

void fixUp(treenode *root, treenode *pt)
{
    treenode *parent_pt = NULL;
    treenode *grand_parent_pt = NULL;

    while ((pt != root) && (pt->color != 0) && (pt->parent->color == 1))
    {
        parent_pt = pt->parent;
        grand_parent_pt = pt->parent->parent;
        /*
        Case : A
        Parent of pt is left child of Grand-parent of pt
        */
        if (parent_pt == grand_parent_pt->left)
        {
            treenode *uncle_pt = grand_parent_pt->right;
            /*
            Case : 1
            The uncle of pt is also red
            Only recoloring needed!
            */
            if (uncle_pt != NULL && uncle_pt->color == 1)
            {
                grand_parent_pt->color = 1;
                parent_pt->color = 0;
                uncle_pt->color = 0;
                pt = grand_parent_pt;
            }

            else
            {
                /*
                Case : 2
                pt is right child of it's parent
                Left-Rotation is needed!
                */
                if (pt == parent_pt->right)
                {
                    leftRotate(parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }
                /*
                Case : 3
                pt is left child of it's parent
                Right-Rotation is needed!
                */
                rightRotate(grand_parent_pt);
                int t = parent_pt->color;
                parent_pt->color = grand_parent_pt->color;
                grand_parent_pt->color = t;
                pt = parent_pt;
            }
        }
        /*
        Case : B
        Parent of pt is right child of Grand-parent of pt
        */
        else
        {
            treenode *uncle_pt = grand_parent_pt->left;
            /*
            Case : 1
            The uncle of pt is also red
            Only Recoloring needed!
            */
            if ((uncle_pt != NULL) && (uncle_pt->color == 1))
            {
                grand_parent_pt->color = 1;
                parent_pt->color = 0;
                uncle_pt->color = 0;
                pt = grand_parent_pt;
            }
            else
            {
                /*
                Case : 2
                pt is left child of it's parent
                Right Rotation is needed!
                */
                if (pt == parent_pt->left)
                {
                    rightRotate(parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }
                /*
                Case : 3
                pt is right child of it's parent
                Left Rotation is needed!
                */
                leftRotate(grand_parent_pt);
                int t = parent_pt->color;
                parent_pt->color = grand_parent_pt->color;
                grand_parent_pt->color = t;
                pt = parent_pt;
            }
        }
    }
}

void inOrder(treenode *root)
{
    if (root != NULL)
    {
        inOrder(root->left);
        printf(" %d ", root->value);
        inOrder(root->right);
    }
}

int main()
{
    int n = 7;
    int a[7] = {7, 6, 5, 4, 3, 2, 1};
    for (int i = 0; i < n; i++)
    {
        treenode *temp = (treenode *)malloc(sizeof(treenode));
        temp->right = NULL;
        temp->left = NULL;
        temp->parent = NULL;
        temp->value = a[i];
        temp->color = 1;
        root = STDinsert(root, temp);
        fixUp(root, temp);
        root->color = 0;
    }
    printf("InOrder\n");
    inOrder(root);
}
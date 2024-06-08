#include <stdio.h>
#include <stdlib.h>

typedef struct treenode
{
    int value;
    struct treenode *left, *right;
} treenode;

treenode *newnode(int value)
{
    treenode *newnode = (treenode *)malloc(sizeof(treenode));
    newnode->value = value;
    newnode->left = newnode->right = NULL;
    return newnode;
}
treenode *search(treenode *root, int target)
{
    if (root == NULL || root->value == target)
    {
        return root;
    }

    if (root->value < target)
    {
        return search(root->right, target);
    }
    return search(root->left, target);
}

// the algo is: recursively go to the target, and then createnode there.
treenode *insert(treenode *node, int value)
{
    if (node == NULL)
    {
        return newnode(value);
    }
    if (value < node->value)
    {
        node->left = insert(node->left, value);
    }
    else if (value > node->value)
    {
        node->right = insert(node->right, value);
    }
    return node;
}

// go to the leftmost
treenode *findMIN(treenode *root)
{
    if (root == NULL)
    {
        return NULL;
    }
    else if (root->left != NULL)
    {
        return findMIN(root->left);
    }
    return root;
}

// go to the rightmost
treenode *findMAX(treenode *root)
{
    if (root == NULL)
    {
        return NULL;
    }

    if (root->right != NULL)
    {
        return findMAX(root->right);
    }
    return root;
}

void postOrder(treenode *root)
{
    if (root != NULL)
    {
        postOrder(root->left);
        postOrder(root->right);
        printf(" %d ", root->value);
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

void preOrder(treenode *root)
{
    if (root != NULL)
    {
        printf(" %d ", root->value);
        preOrder(root->left);
        preOrder(root->right);
    }
}

// treenode *delete(treenode *root, int target)
// {

//     // if not found or tree is empty
//     if (root == NULL)
//     {
//         return NULL;
//     }

//     // tranversal until target == root->value
//     // "ROOT" is now the target where we need to delete it
//     if (target > root->value)
//     {
//         root->right = delete (root->right, target);
//     }
//     else if (target < root->value)
//     {
//         root->left = delete (root->left, target);
//     }
//     // condition of target == root->value
//     else
//     {

//         // 1st condition, no child nodes.
//         if (root->left == NULL && root->right == NULL)
//         {
//             free(root);
//             return NULL;
//         }
//         // 2nd condition, 1 child node.
//         else if (root->left == NULL || root->right == NULL)
//         {
//             // temp holds the child
//             treenode *temp;
//             if (root->left == NULL)
//             {
//                 temp = root->right;
//             }
//             else
//             {
//                 temp = root->left;
//             }
//             free(root);
//             // replaces the current node into the child that was held by temp
//             return temp;
//         }
//         // 3rd condition, 2 child node, swap with predecessor / sucessor
//         else
//         {
//             // if not specifed  you need to use predecessor!

//             // find the leftmost of right child of root
//             // Successor
//             // treenode *temp = findMIN(root->right);
//             // root->value = temp->value;
//             // // search that temp and delete it as we already switch places.
//             // root->right = delete (root->right, temp->value);

//             // Predecessor
//             treenode *temp = findMAX(root->left);
//             root->value = temp->value;
//             // search that temp and delete it as we already switch places.
//             root->left = delete (root->left, temp->value);
//         }
//     }
//     return root;
// }
treenode *delete(treenode *root, int target)
{
    if (root == NULL)
    {
        return NULL;
    }

    if (target > root->value)
    {
        root->right = delete (root->right, target);
    }
    else if (target < root->value)
    {
        root->left = delete (root->left, target);
    }
    else
    {
        if (root->left == NULL && root->right == NULL)
        {
            root->left = NULL;
            root->right = NULL;
            free(root);
            return NULL;
        }
        else if (root->left != NULL && root->right != NULL)
        {
            treenode *temp = findMAX(root->left);
            // printf("Temp Val: %d\n", temp->value);
            root->value = temp->value;
            root->left = delete (root->left, temp->value);
        }
        else
        {
            treenode *temp;
            if (root->left == NULL)
            {
                temp = root->right;
            }
            else
            {
                temp = root->left;
            }
            free(root);
            // ganti root jadi temp
            return temp;
        }
    }
    return root;
}

int main()
{
    // intiliaze root
    treenode *root = NULL;
    // insert first root
    root = insert(root, 30);

    // use the algorithm of insert
    // read it as: insert from root
    insert(root, 30);
    insert(root, 25);
    insert(root, 50);
    insert(root, 100);
    insert(root, 27);
    insert(root, 20);
    delete (root, 30);
    delete (root, 100);

    // printf("Root: %d\n", root->value);
    // printf("Root->left: %d\n", root->left->value);
    // printf("Root->right: %d\n", root->right->value);
    // printf("Root->right->right: %d\n", root->right->right->value);
    printf("PreOrder: ");
    preOrder(root);
    puts("");
    printf("InOrder: ");
    inOrder(root);
    puts("");
    printf("PostOrder: ");
    postOrder(root);
}
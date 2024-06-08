#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack
{
    char value;
    struct stack *left, *right;

} stack;

stack *head = NULL;
stack *tail = NULL;

stack *newStack(char value)
{
    stack *newStack = (stack *)malloc(sizeof(stack));
    if (newStack != NULL)
    {
        newStack->value = value;
        newStack->left = newStack->right = NULL;
        return newStack;
    }
    return NULL;
}

void push(char value)
{
    stack *temp = newStack(value);
    if (head == NULL)
    {
        head = tail = temp;
    }
    else
    {
        tail->next = temp;
        temp->prev = tail;
        tail = temp;
    }
}

char pop()
{
    char result;
    stack *curr = tail;

    // if stack is not empty
    if (tail != NULL)
    {
        result = tail->val;
        if (tail == head)
        {
            head = tail = NULL;
        }
        else
        {
            tail = tail->prev;
            tail->next = NULL;
        }
        free(curr);
    }
    return result;
}

char top()
{
    if (tail == NULL)
    {
        return 0;
    }
    else
    {
        return (tail->val);
    }
}

// THE EXPRESSION TREE
typedef struct treenode
{
    char value;
    struct stack *left, *right;
} treenode;

treenode *newnode(char value)
{
    treenode *newnode = (treenode *)malloc(sizeof(treenode));
    if (newnode != NULL)
    {
        newnode->value = value;
        newnode->left = newnode->right = NULL;
        return newnode;
    }
    return NULL;
}

int main()
{
    int IMPORTANT = 1;
    while (IMPORTANT)
    {
        system("cls");
        printf("-- INFIX to Expression Tree --\n");
        printf("1. Convert infix to Expression Tree\n2. Print Prefix\n3. Print Infix\n4. Print Postfix\n5. Exit\n");
        printf("Choice: ");
        int choice;
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        {
            printf("Your Infix Input:\n");
            char *infix = (char *)calloc((1000), sizeof(char));
            scanf("%[^\n]", infix);
            bruh operatorStack;
            bruh operandStack;

            break;
        }
        case 2:
        {
            break;
        }
        case 3:
        {
            break;
        }
        case 4:
        {
            break;
        }
        case 5:
        {
            printf("Program is now exitting...");
            getchar();
            IMPORTANT = 0;
            break;
        }
        default:
        {
            printf("Invalid Choice...");
            getchar();
            break;
        }
        }
    }
}
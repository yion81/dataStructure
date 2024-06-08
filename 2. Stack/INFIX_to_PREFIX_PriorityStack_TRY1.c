#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void confirm()
{
    getchar();
    getchar();
}

typedef struct stack
{
    char val;
    struct stack *next, *prev;
} stack;

stack *head = NULL;
stack *tail = NULL;

stack *newStack(char value)
{
    stack *new = (stack *)malloc(sizeof(stack));
    new->next = new->prev = NULL;
    new->val = value;

    // return the news stack
    return new;
}

// push tail with no return
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

// pop tail with return
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

// top is just || look at tail
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

// return 0 if stack is empty
int isEmpty()
{
    return (head == NULL);
}

// return the priority for operators (higher is more important)
int priority(char op)
{
    switch (op)
    {
    case '^':
        return 3;
    case '*':
    case '/':
        return 2;
    case '+':
    case '-':
        return 1;
    default:
        return 0;
    }
}

void infixTOprefix(char *infix, char *prefix)
{
    char currSymbol, nextSymbol;
    int j = 0;
    for (int i = strlen(infix) - 1; i > 0; i--)
    {
        currSymbol = infix[i];
        switch (currSymbol)
        {
            // find (: just push to stack
        case ')':
        {
            push(currSymbol);
            break;
        }
            // find ): pop all until find '('
        case '(':
        {
            while ((nextSymbol = pop()) != ')')
            {
                prefix[j++] = nextSymbol;
            }
            break;
        }
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
        {
            // if operator, and stack is not empty and current top stack prio >= prio current operator
            // keep popping
            while (!isEmpty() && (priority(top()) > priority(currSymbol)))
            {
                prefix[j++] = pop();
            }
            // always push.
            push(currSymbol);
            break;
        }
            // if it's number or operand just put it into postfix string
        default:
        {
            prefix[j++] = currSymbol;
        }
        }
    }

    while (!isEmpty())
    {
        prefix[j++] = pop();
    }
}

int main()
{
    int IMPORTANT = 1;
    while (IMPORTANT)
    {
        system("cls");
        printf("    --Priority Stack INFIX to PREFIX--\n");
        printf("1. Convert INFIX to PREFIX\n2. Exit\n");
        int choice;
        printf("Choice: ");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
        {
            printf("Your INFIX input:\n");
            char *infix = (char *)calloc((1000), sizeof(char));
            char *prefix = (char *)calloc((1000), sizeof(char));
            scanf("%[^\n]", infix);
            infixTOprefix(infix, prefix);
            printf("Prefix: %s\n", prefix);
            printf("Press enter to continue...");
            confirm();
            break;
        }
        case 2:
        {
            printf("Program will not exit...");
            IMPORTANT = 0;
            getchar();
            break;
        }
        }
    }
}
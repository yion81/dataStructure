#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void confirm()
{
    getchar();
    getchar();
}

typedef struct stack
{
    int value;
    struct stack *next;
} stack;

stack *top = NULL;

void push(int value)
{
    stack *temp = (stack *)malloc(sizeof(stack));
    temp->value = value;
    temp->next = NULL;
    if (top == NULL)
    {
        top = temp;
    }
    else
    {
        temp->next = top;
        top = temp;
    }
}

void pop()
{
    if (top == NULL)
    {
        return;
    }
    else
    {
        stack *ptr = top;
        top = top->next;
        free(ptr);
    }
}

int peekTOP()
{
    if (top != NULL)
        return (top->value);
    else
        return -1;
}

void calculate(char *notation)
{
    for (int i = 0; i < strlen(notation); i++)
    {
        if (notation[i] >= '0' && notation[i] <= '9')
        {
            push(notation[i] - '0');
        }
        else
        {
            int a = peekTOP();
            pop();
            int b = peekTOP();
            pop();
            switch (notation[i])
            {
            case '-':
            {
                push(b - a);
                break;
            }
            case '+':
            {
                push(b + a);
                break;
            }
            case '/':
            {
                push(b / a);
                break;
            }
            case '*':
            {
                push(b * a);
                break;
            }
            case '^':
            {
                push(pow(b, a));
                break;
            }
            }
        }
    }
    printf("Result: %d\n", peekTOP());
}

int main()
{
    char notation[] = "765*32^-+";
    calculate(notation);
}
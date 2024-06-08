#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct stack
{
    char val;
    struct stack *next, *prev;
} *head = NULL, *tail = NULL;

// Functions for Stack purposes

struct stack *newStack(char val)
{ // Create and return new stack
    struct stack *new = malloc(sizeof(struct stack));
    new->next = NULL;
    new->prev = NULL;
    new->val = val;
    return new;
}

// push tail
void push(char val)
{ // Push new stack
    struct stack *temp = newStack(val);
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
    struct stack *curr = tail;
    if (tail != NULL)
    {
        result = tail->val; // Parse val of tail into variable 'result'
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
{ // Get the top value in a stack
    if (tail == NULL)
    {
        return 0;
    }
    else
    {
        return tail->val;
    }
}

int isEmpty()
{ // Check if stack is empty or not
    return head == NULL;
}
/////////////////////

// Functions Infix to Postfix
int priority(char op)
{ // Get current op priorities
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

void intopo(char *infix, char *postfix)
{
    char currentSymbol, nextSymbol;
    int j = 0;
    for (int i = 0; i < strlen(infix); i++)
    {
        currentSymbol = infix[i];
        switch (currentSymbol)
        {
        // Case 1 kalo symbol = '('
        case '(':
            push(currentSymbol); // Cukup langsung push '(' kedalam stack
            break;

        // Case 2 kalo symbol = ')'
        case ')':
            while ((nextSymbol = pop()) != '(')
            {                              // Kita bakal pop terus smpe dpt '(' didalem stack
                postfix[j++] = nextSymbol; // Selagi kita pop, kita masukkin yg udh kita pop ke dalam postfix
            }
            break;

        // Case 3 buat operator
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
            while (!isEmpty() && (priority(top()) >= priority(currentSymbol)))
            { // Check dlu apakah stacknya kosong atau tidak
                // lalu bandingkan prioritas operator paling atas dalam stack dengan operator yg sekarang
                postfix[j++] = pop(); // Jika kondisi diatas terpenuhi (Stack tidak empty dan stack teratas memiliki prioritas
                                      // Lebih atau sama dengan current operator)
            }
            push(currentSymbol);
            break; // Jika kondisi tidak terpenuhi maka push currentsymbol ke dalam stack
        // Case 4 jika currentSymbol adalah angka
        default:
            postfix[j++] = currentSymbol; // Langsung saja masukkan dalam postfix
        }
    }

    // Penutupan
    while (!isEmpty())
    { // Kosongkan stack lalu masukkan kedalam postfix :>
        postfix[j++] = pop();
    }
}
/////////////////////////////////////////////////////////////////

int main()
{
    char infix[100] = "7+(9-5)*2";
    char postfix[100];
    intopo(infix, postfix);
    printf("Infix: %s\nPostfix: %s", infix, postfix);
}
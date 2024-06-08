#include <stdio.h>
#include <stdlib.h>

int dataSize = 0;

struct node *head = NULL;
struct node *tail = NULL;

typedef struct node
{
    int data;
    struct node *next;
} node;

void confirm()
{
    getchar();
    getchar();
}

void push();
void pop();
void displayList();

int main()
{
    int IMPORTANT = 1;
    int choice;
    while (IMPORTANT)
    {
        system("cls");
        printf("--Stack Using Single Linked List--\n");
        displayList();
        puts("");
        printf("1. Push\n2. Pop\n3. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        {
            push();
            break;
        }
        case 2:
        {
            pop();
            break;
        }
        case 3:
        {
            IMPORTANT = 0;
            printf("Program will now exit...");
            confirm();
            break;
        }
        }
    }
}

void displayList()
{
    if (head == NULL)
    {
        printf("Current Stack is empty\n");
        return;
    }
    else
    {
        printf("Stack: ");
        node *ptr = head;
        while (ptr != NULL)
        {
            if (ptr->next != NULL)
            {
                printf("%d -> ", ptr->data);
            }
            else
            {
                printf("%d", ptr->data);
            }
            ptr = ptr->next;
        }
        puts("");
        printf("Current Data Size: %d\n", dataSize);
    }
}

void push()
{
    node *temp = (node *)malloc(sizeof(node));
    node *cursor = head;
    printf("Enter data: ");
    scanf("%d", &temp->data);
    if (head == NULL)
    {
        temp->next = NULL;
        head = temp;
        tail = temp;
    }
    else if (temp->data < head->data)
    {
        // push head
        temp->next = head;
        head = temp;
    }
    else if (temp->data > tail->data)
    {
        // push tail
        node *ptr = tail;
        ptr->next = temp;
        tail = temp;
        temp->next = NULL;
    }
    else
    {
        while (temp->data > cursor->next->data)
        {
            cursor = cursor->next;
        }
        temp->next = cursor->next;
        cursor->next = temp;
    }

    dataSize++;
}

void pop()
{
    if (head == NULL)
    {
        printf("Stack is already empty.\n");
        confirm();
        return;
    }
    else
    {
        node *ptr = head;
        head = head->next;
        free(ptr);
    }
    dataSize--;
}
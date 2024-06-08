// Higher number = Higher Priority

#include <stdio.h>
#include <stdlib.h>

int dataSize = 0;

struct node *head = NULL;
struct node *tail = NULL;

typedef struct node
{
    int data;
    struct node *next;
    struct node *prev;
} node;

void confirm()
{
    getchar();
    getchar();
}

void displayList();
void push();
void pop();

int main()
{
    int mainLOOP = 1;
    int choice;
    while (mainLOOP)
    {
        system("cls");
        printf("--Priority Queue Using Linked List--\n");
        displayList();
        puts("");
        printf("1. Push\n2. Pop\n3. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        {
            printf("Data to push: ");
            int dataToPush;
            scanf("%d", &dataToPush);
            push(dataToPush);
            break;
        }
        case 2:
        {
            pop();
            break;
        }
        case 3:
        {
            printf("Program will now exit...");
            confirm();
            mainLOOP = 0;
            break;
        }
        }
    }
}

void displayList()
{
    if (head == NULL)
    {
        printf("Current Linked list is empty\n");
        return;
    }
    else
    {
        printf("Linked list: ");
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

// push mid
void push(int data)
{
    node *temp = (node *)malloc(sizeof(node));
    node *ptr = head;
    temp->data = data;
    temp->next = NULL;
    temp->prev = NULL;

    if (head == NULL)
    {
        head = temp;
        tail = temp;
    }
    // push head
    else if (temp->data < head->data)
    {
        temp->next = head;
        head->prev = temp;
        head = temp;
        return;
    }
    // push tail
    else if (temp->data > tail->data)
    {
        tail->next = temp;
        temp->prev = tail;
        tail = temp;
        return;
    }
    else
    {
        while (temp->data > ptr->next->data)
        {
            ptr = ptr->next;
        }
        temp->next = ptr->next;
        temp->prev = ptr;
        ptr->next->prev = temp;
        ptr->next = temp;
    }
}

void pop()
{
    if (head == NULL)
    {
        printf("Linked list is already empty.\n");
        confirm();
        return;
    }
    else if (head == tail)
    {
        free(head);
        head = NULL;
        tail = NULL;
        printf("Tail Popped...");
    }
    else
    {
        node *ptr = tail;
        tail = tail->prev;
        free(ptr);
        tail->next = NULL;
        printf("Tail Popped...");
    }
}
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

void displayList();
void pushHead();
void pushIndex();
void pushSorted();
void pushTail();
void popHead();
void popIndex();
void popElement();
void popTail();
void popAll();

int main()
{
    int IMPORTANT = 1;
    int choice;
    while (IMPORTANT)
    {
        system("cls");
        printf("--SINGLE LINKED LIST--\n");
        displayList();
        puts("");
        printf("1. Push head O(1)\n2. Push from index O(N)\n3. Push Sorted O(N)\n4. Push tail O(1)\n5. Pop head O(1)\n6. Pop from index O(N)\n7. Pop element O(N)\n8. Pop tail O(N)\n9. PopAll\n10. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        {
            pushHead();
            break;
        }
        case 2:
        {
            pushIndex();
            break;
        }
        case 3:
        {
            pushSorted();
            break;
        }
        case 4:
        {
            pushTail();
            break;
        }
        case 5:
        {
            popHead();
            break;
        }
        case 6:
        {
            popIndex();
            break;
        }
        case 7:
        {
            popElement();
            break;
        }
        case 8:
        {
            popTail();
            break;
        }
        case 9:
        {
            popAll();
            break;
        }
        case 10:
        {
            popAll();
            printf("Program will now exit...");
            confirm();
            IMPORTANT = 0;
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

void pushHead()
{
    node *temp = (node *)malloc(sizeof(node));
    printf("Enter data: ");
    scanf("%d", &temp->data);
    temp->next = NULL;
    if (head == NULL)
    {
        head = temp;
        tail = temp;
    }
    else
    {
        temp->next = head;
        head = temp;
    }
    dataSize++;
}

void pushIndex()
{

    node *temp = (node *)malloc(sizeof(node));
    printf("Enter data: ");
    scanf("%d", &temp->data);
    temp->next = NULL;
    if (head == NULL)
    {
        head = temp;
        tail = temp;
    }
    else
    {
        node *prev;
        node *ptr = head;
        int position;
        while (1)
        {
            printf("Enter position to push (Cannot be 0 or %d), enter -1 to exit: ", dataSize);
            scanf("%d", &position);
            if (position == -1)
            {
                free(temp);
                return;
            }
            if (position >= 1 && position < dataSize)
            {
                break;
            }
        }
        for (int i = 0; i < position; i++)
        {
            prev = ptr;
            ptr = ptr->next;
        }
        temp->next = ptr;
        prev->next = temp;
    }
    dataSize++;
}

void pushSorted()
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

void pushTail()
{
    node *temp = (node *)malloc(sizeof(node));
    printf("Enter data: ");
    scanf("%d", &temp->data);
    temp->next = NULL;
    if (head == NULL)
    {
        head = temp;
        tail = temp;
    }
    else
    {
        node *ptr = tail;
        ptr->next = temp;
        tail = temp;
    }
    dataSize++;
}

void popHead()
{
    if (head == NULL)
    {
        printf("Linked list is already empty.\n");
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

void popIndex()
{
    if (head == NULL)
    {
        printf("Linked list is already empty.\n");
        confirm();
        return;
    }
    else
    {
        int position;
        while (1)
        {
            printf("Enter position to push (Cannot be 0 or %d), enter -1 to exit: ", dataSize);
            scanf("%d", &position);
            if (position == -1)
            {
                return;
            }
            if (position >= 1 && position < dataSize)
            {
                break;
            }
        }

        node *ptr = head;
        node *prev;
        for (int i = 0; i < position; i++)
        {
            prev = ptr;
            ptr = ptr->next;
        }
        prev->next = ptr->next;
        free(ptr);
    }
    dataSize--;
}

void popElement()
{
    if (head == NULL)
    {
        printf("Linked list is already empty.\n");
        confirm();
        return;
    }
    node *temp = (node *)malloc(sizeof(node));
    printf("Element to delete: ");
    scanf("%d", &temp->data);
    if (temp->data == head->data)
    {
        // pop head
        node *ptr = head;
        head = head->next;
        free(ptr);
    }
    else if (temp->data == tail->data)
    {
        // pop tail
        if (dataSize == 1)
        {
            free(tail);
            head = NULL;
            tail = NULL;
        }
        else
        {
            node *ptr = head;
            node *toDelete = tail;
            while (ptr->next != tail)
            {
                ptr = ptr->next;
            }
            ptr->next = NULL;
            free(toDelete);
            tail = ptr;
        }
    }
    else
    {
        node *ptr = head;
        node *prev;
        while (ptr != NULL && ptr->data != temp->data)
        {
            prev = ptr;
            ptr = ptr->next;
        }
        if (ptr == NULL)
        {
            printf("%d element is no found...", temp->data);
            confirm();
            free(temp);
            return;
        }
        else
        {
            prev->next = ptr->next;
            ptr->next = NULL;
            free(ptr);
        }
    }
    dataSize--;
}

void popTail()
{
    if (head == NULL)
    {
        printf("Linked list is already empty.\n");
        confirm();
        return;
    }
    else if (dataSize == 1)
    {
        free(tail);
        head = NULL;
        tail = NULL;
    }
    else
    {
        node *ptr = head;
        node *toDelete = tail;
        while (ptr->next != tail)
        {
            ptr = ptr->next;
        }
        ptr->next = NULL;
        free(toDelete);
        tail = ptr;
    }
    dataSize--;
}

void popAll()
{
    while (head != NULL)
    {
        node *ptr = head;
        head = head->next;
        free(ptr);
    }
    dataSize = 0;
}
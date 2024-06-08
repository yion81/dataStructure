#include <stdio.h>
#include <stdlib.h>

int dataSize = 0;

struct node *head = NULL;
struct node *tail = NULL;
// struct node *mid = NULL;

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

// temp call
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
    while (IMPORTANT)
    {
        system("cls");
        printf("         --Doubly Linked List--\n");
        printf("--All Time Complexity is WORST TESTCASE--");
        puts("");
        // reverseDisplayList();
        displayList();
        printf("1. Push head    | O(1)\n2. Push index   | O(N/2)\n3. Push sorted  | O(N)\n4. Push tail    | O(1)\n5. Pop head     | O(1)\n6. Pop index    | O(N/2)\n7. Pop element  | O(N)\n8. Pop tail     | O(1)\n9. PopAll       | O(N)\n10. Exit\n");

        // for push mid you can make it O(N/2) also for element (THIS IS IF SORTED)
        // you can make global variable for mid which change depending the thing
        // after that compare that to the current thingy
        // that determines between oing from hhead or tail.

        printf("Choice: ");
        int choice;
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        {
            int data;
            printf("Enter data: ");
            scanf("%d", &data);
            pushHead(data);
            break;
        }
        case 2:
        {
            int data;
            printf("Enter data: ");
            scanf("%d", &data);
            if (head == NULL)
            {
                pushHead(data);
            }
            else
            {
                int index;
                while (1)
                {
                    printf("Enter index (0 - %d): ", dataSize - 1);
                    scanf("%d", &index);
                    if (index >= 0 && index <= dataSize - 1)
                    {
                        break;
                    }
                }
                pushIndex(data, index);
            }
            break;
        }
        case 3:
        {
            int data;
            printf("Enter data: ");
            scanf("%d", &data);
            pushSorted(data);
            break;
        }
        case 4:
        {
            int data;
            printf("Enter data: ");
            scanf("%d", &data);
            pushTail(data);
            break;
        }
        case 5:
        {
            popHead();
            break;
        }
        case 6:
        {
            int index;
            printf("Enter index: ");
            scanf("%d", &index);
            popIndex(index);
            break;
        }
        case 7:
        {
            int data;
            printf("Enter data to pop: ");
            scanf("%d", &data);
            popElement(data);
            break;
        }
        case 8:
        {
            popTail();
            break;
        }
        case 9:
        {
            if (head == NULL)
            {
                printf("Current List is already empty!\n");
                confirm();
            }
            else
            {
                popAll();
                printf("Popped all elements...");
                confirm();
            }
            dataSize = 0;
            break;
        }
        case 10:
        {
            IMPORTANT = 0;
            printf("Program will now exit...");
            popAll();
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
        printf("Current List is empty!\n");
    }
    else
    {
        printf("Current List: ");
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
        printf("Current List Size: %d\n", dataSize);
    }
}

void reverseDisplayList()
{
    if (head == NULL)
    {
        printf("Current List is empty!\n");
    }
    else
    {
        printf("Current List: ");
        node *ptr = tail;
        while (ptr != NULL)
        {
            if (ptr->prev != NULL)
            {
                printf("%d -> ", ptr->data);
            }
            else
            {
                printf("%d", ptr->data);
            }
            ptr = ptr->prev;
        }
        puts("");
        printf("Current List Size: %d\n", dataSize);
    }
}

void pushHead(int data)
{
    node *temp = (node *)malloc(sizeof(node));
    temp->data = data;
    temp->next = NULL;
    temp->prev = NULL;
    if (head == NULL)
    {
        head = temp;
        tail = temp;
    }
    else
    {
        temp->next = head;
        head->prev = temp;
        head = temp;
    }

    dataSize++;
}

void pushTail(int data)
{
    node *temp = (node *)malloc(sizeof(node));
    temp->data = data;
    temp->next = NULL;
    if (head == NULL)
    {
        head = temp;
        tail = temp;
    }
    else
    {
        tail->next = temp;
        temp->prev = tail;
        tail = temp;
    }
    dataSize++;
}

void pushIndex(int data, int index)
{
    if (index == 0)
    {
        pushHead(data);
        return;
    }
    else if (index == (dataSize - 1))
    {
        pushTail(data);
        return;
    }

    node *temp = (node *)malloc(sizeof(node));

    temp->data = data;
    temp->next = NULL;
    temp->prev = NULL;
    node *ptr;

    // traversal from head
    if (index <= (dataSize / 2))
    {
        ptr = head;
        for (int i = 0; i < index - 1; i++)
        {
            ptr = ptr->next;
        }
    }
    // from tail
    else
    {
        ptr = tail;
        for (int i = dataSize - 1; i > index; i--)
        {
            ptr = ptr->prev;
        }
    }
    temp->prev = ptr;
    temp->next = ptr->next;
    ptr->next->prev = temp;
    ptr->next = temp;

    dataSize++;
}

void pushSorted(int data)
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
    else if (temp->data < head->data)
    {
        pushHead(data);
        return;
    }
    else if (temp->data > tail->data)
    {
        pushTail(data);
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
    else if (head == tail)
    {
        free(head);
        head = NULL;
        tail = NULL;
        printf("Head Popped...");
    }
    else
    {
        node *ptr = head;
        head = head->next;
        free(ptr);
        head->prev = NULL;
        printf("Head Popped...");
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
    dataSize--;
}

void popIndex(int index)
{
    if (head == NULL)
    {
        printf("Linked list is already empty.\n");
        confirm();
        return;
    }
    else if (index == 0)
    {
        popHead();
        return;
    }
    else if (index == (dataSize - 1))
    {
        popTail();
        return;
    }
    else
    {
        node *ptr;
        // traversal from head
        if (index <= (dataSize / 2))
        {
            ptr = head;
            for (int i = 0; i < index; i++)
            {
                ptr = ptr->next;
            }
        }
        // from tail
        else
        {
            ptr = tail;
            for (int i = dataSize; i > index; i--)
            {
                ptr = ptr->prev;
            }
        }
        ptr->next->prev = ptr->prev;
        ptr->prev->next = ptr->next;
        free(ptr);
    }
    dataSize--;
}

void popElement(int data)
{
    if (head == NULL)
    {
        printf("Linked list is already empty.\n");
        confirm();
        return;
    }
    node *temp = (node *)malloc(sizeof(node));
    temp->data = data;
    if (temp->data == head->data)
    {
        // pop head
        popHead();
        return;
    }
    else if (temp->data == tail->data)
    {
        // pop tail
        popTail();
        return;
    }
    else
    {
        node *ptr = head;
        while (ptr != NULL && ptr->data != temp->data)
        {
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
            ptr->next->prev = ptr->prev;
            ptr->prev->next = ptr->next;
            free(ptr);
        }
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
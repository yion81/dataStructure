#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// global variable count for the amount of the prefix printing we have
int count = 1;

// confirming, just press enter to actually continue
void confirm()
{
    getchar();
    getchar();
}

// check if there's space
int hasSpace(char *string)
{
    int length = strlen(string);
    for (int i = 0; i < length; i++)
    {
        // 32 is ascii for whitespace or 'space'
        if (string[i] == 32)
        {
            return 1;
        }
    }
    return 0;
}

// the main trienode
typedef struct trienode
{
    // current word
    char ch;
    // description for the word
    char description[1001];
    // is it a leaf? if it is, it's a word
    int isWord;
    struct trienode *children[128];
} trienode;

// creating trienode and returning the pointer to the newnode.
trienode *createnode(char ch)
{
    trienode *node = (trienode *)malloc(sizeof(trienode));
    node->ch = ch;
    node->isWord = 0;
    // memset is better than "for loop" to set all children to null.
    memset(node->children, 0, sizeof(node->children));
    return node;
}

void insertWord(trienode **root, const char *word, const char *description)
{
    if (*root == NULL)
    {
        *root = createnode('*');
    }

    // start tranversing from root.
    trienode *curr = *root;
    int length = strlen(word);
    // how we transverse through trienode
    for (int i = 0; i < length; i++)
    {
        // if current node is empty, create that node.
        if (curr->children[word[i]] == NULL)
        {
            curr->children[word[i]] = createnode(word[i]);
        }
        // go to next word.
        curr = curr->children[word[i]];
    }

    // we are at children
    strcpy(curr->description, description);
    // check if the node is a word already if it has, print different lines.
    if (curr->isWord == 1)
    {
        printf("Sucessfully updated a slang word.\n");
    }
    // the other line.
    else
    {
        curr->isWord = 1;
        printf("Sucessfully released new slang word.\n");
    }
}

void printTrie(trienode *node, char *string, int depth)
{
    // base case if it's empty then just return
    if (node == NULL)
    {
        return;
    }

    // put the current character to the string
    string[depth] = node->ch;

    // check if this current node isWord
    if (node->isWord)
    {
        // if it is, put \0 to the end of string and print
        string[depth + 1] = '\0';
        printf("%d. %s\n", count++, string);
    }
    // go to all 128 children.
    for (int i = 0; i < 128; i++)
    {
        printTrie(node->children[i], string, depth + 1);
    }
}

void search(trienode *curr, const char *prefix, const char *temp)
{
    if (curr == NULL)
    {
        return;
    }
    char string[100];
    int depth = 0;
    // traverse to prefix
    while (*prefix)
    {
        if (curr == NULL)
        {
            return;
        }
        curr = curr->children[*prefix];
        string[depth++] = *prefix++;
    }
    // check if after traversing, it's null or not, if it is exit.
    if (curr == NULL)
    {
        return;
    }

    printf("Words starts with \"%s\":\n", temp);

    // for failsafe...
    if (curr->isWord)
    {
        string[depth] = '\0';
        printf("%d. %s\n", count++, string);
    }
    // go to all possible childrens on that prefix
    for (int i = 0; i < 128; i++)
    {
        if (curr->children[i] != NULL)
        {
            printTrie(curr->children[i], string, depth);
        }
    }
}

// this is for case 4 almost the same as search function,
// the only difference is the input
void searchALL(trienode *curr, const char *prefix)
{
    if (curr == NULL)
    {
        return;
    }
    char string[100];
    int depth = 0;
    while (*prefix)
    {
        if (curr == NULL)
        {
            return;
        }
        curr = curr->children[*prefix];
        string[depth++] = *prefix++;
    }
    printf("List of all slang words in the dictionary:\n");
    if (curr->isWord)
    {
        string[depth] = '\0';
        printf("%d. %s\n", count++, string);
    }
    for (int i = 0; i < 128; i++)
    {
        if (curr->children[i] != NULL)
        {
            printTrie(curr->children[i], string, depth);
        }
    }
}

// check if it exist or not
int exist(trienode *root, const char *wordTF, const char *temp)
{
    // put the traversing as "curr" starting at root
    trienode *curr = root;
    // traverse to the word
    while (*wordTF)
    {
        if (curr == NULL || curr->children[*wordTF] == NULL)
        {
            return 0;
        }
        curr = curr->children[*wordTF];
        wordTF++;
    }

    // print the slang and desc if isWord is == 1
    if (curr != NULL && curr->isWord)
    {
        printf("Slang word  : %s\n", temp);
        printf("Description : %s\n", curr->description);
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    // int for loop program
    int mainLOOP = 1;

    // making root node
    trienode *root = NULL;

    // mainloop
    while (mainLOOP)
    {
        // clear system's history
        system("cls");
        printf("    ________________________________   _______\n    7  _  77     77     77     77  7   7     7\n    |   __||  7  ||  7  ||   __!|  |   |  ___!\n    |  _  ||  |  ||  |  ||  !  7|  !___|  __|_\n    |  7  ||  !  ||  !  ||     ||     7|     7\n    !_____!!_____!!_____!!_____!!_____!!_____!\n");
        printf("1. Release a new slang word\n2. Search a slang word\n3. View all slang words starting with a certain prefix word\n4. View all slang words\n5. Exit\n");
        printf("Your choice: ");
        int choice;
        scanf("%d", &choice);
        // getchar to fix anything wrong with the input. (to be safe).

        switch (choice)
        {
        case 1:
        {
            char slangWord[1001];
            char description[1001];
            // setting up slangword Validation
            while (1)
            {
                // getchar to fix any overflow char
                getchar();
                printf("Input a new slang word [Must be more than 1 characters and contains no space]: ");
                scanf("%[^\n]", slangWord);
                // break condition
                if (!hasSpace(slangWord) && strlen(slangWord) > 1)
                {
                    break;
                }
            }

            // setting up description Validation
            while (1)
            {
                // getchar to fix any overflow char
                getchar();
                printf("Input a new slang word description [Must be more than 2 words]: ");
                scanf("%[^\n]", description);
                // break condition
                if (hasSpace(description))
                {
                    break;
                }
            }
            puts("");

            // insert the slang and description into trienode
            insertWord(&root, slangWord, description);

            // confirmation as in TC (testcase)
            printf("Press enter to continue...");
            confirm();
            break;
        }
        case 2:
        {
            char toSearch[1001];

            // validate Searching string
            while (1)
            {
                // getchar to fix any overflow char
                getchar();
                printf("Input a slang word to be searched [Must be more than 1 characters and contains no space]: ");
                scanf("%[^\n]", toSearch);
                // break condition
                if (!hasSpace(toSearch) && strlen(toSearch) > 1)
                {
                    break;
                }
            }
            puts("");
            // check if it exist or not, if it does, print on exist func
            if (!exist(root, toSearch, toSearch))
            {
                printf("There is no \"%s\" in the dictionary.\n", toSearch);
            }

            // confirm user
            printf("Press enter to continue...");
            confirm();
            break;
        }
        case 3:
        {
            // getchar to fix any overflow char
            getchar();
            // set count back as 1
            count = 1;
            char toSearch[1001];
            printf("Input a prefix to be searched: ");
            scanf("%[^\n]", toSearch);
            puts("");
            search(root, toSearch, toSearch);
            // basically, after search function works,
            // if "count" didn't update, then there was no prefix found.
            // so we check if count == 1
            if (count == 1)
            {
                printf("There is no prefix \"%s\" in the dictionary.\n", toSearch);
            }
            printf("Press enter to continue...");
            confirm();
            break;
        }
        case 4:
        {
            // set count back as 1
            count = 1;
            searchALL(root, "");
            // basically, after search function works,
            // if "count" didn't update, then there was no prefix found.
            // so we check if count == 1
            if (count == 1)
            {
                printf("There is no slang word yet in the dictionary.\n");
            }
            printf("Press enter to continue...");
            confirm();
            break;
        }
        case 5:
        {
            system("cls");
            printf("Thank you for using the program... Have a nice day :)\n");
            printf("Press anything to continue...");
            confirm();
            // put mainLOOP (the loop that keeps the program running) as 0 to stop it
            mainLOOP = 0;
            break;
        }
        }
    }
}
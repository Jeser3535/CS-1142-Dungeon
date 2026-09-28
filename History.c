/*
 * Author: Jesse Sergent
 * Email: jtsergen
 * Description: This program maintains a chronological record of all player actions    * using a linked list. It supports adding new moves to the end of the list and        * clearing the entire history to prevent memory leaks.
 */

#include "History.h"
#include <stdio.h>
#include <stdlib.h>

// declares
void historyInit(History* history)
{
    history->first = NULL;
    history->last = NULL;
}
// add information to history 
void historyAdd(History* history, Action action)
{
    Node* newNode = malloc(sizeof(Node));
    if (newNode != NULL)
    {
        newNode->action = action;
        newNode->next = NULL;

        if (history->first == NULL)
        {
            history->first = newNode;
            history->last = newNode;
        }
        else
        {
            history->last->next = newNode;
            history->last = newNode;
        }
    }
}
// prints the history 
void historyPrint(const History* history)
{
    Node* current = history->first;
    while (current != NULL)
    {
        printf("%s", actionToString(current->action));
        if (current->next != NULL)
        {
            printf(" ");
        }
        current = current->next;
    }
    printf("\n");
}

void historyUninit(History* history)
{
    Node* current = history->first;
    while (current != NULL)
    {
        Node* next = current->next;
        free(current);
        current = next;
    }
    history->first = NULL;
    history->last = NULL;
}

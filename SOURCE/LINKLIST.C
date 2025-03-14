#include "LINKLIST.H"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//链表用来将较多数据存储到内存中以方便进行频繁访问

void linklist_add_data(LINKLIST *pList, LINKLIST_USER data)
{
    LINKLIST_NODE *p = (LINKLIST_NODE *)malloc(sizeof(LINKLIST_NODE));
    LINKLIST_NODE *last = pList->HEAD;
    p->USER_DATA = data;
    p->NEXT = NULL;
    if (last)
    {
        while (last->NEXT)
        {
            last = last->NEXT;
        }
        // attach
        last->NEXT = p;
        p->line = last->line + 1;
    }
    else
    {
        pList->HEAD = p;
        p->line = 1;
    }

    return;
}

void linklist_print_data(LINKLIST *pList)
{
    LINKLIST_NODE *p;
    printf("All data:\n");
    for (p = pList->HEAD; p; p = p->NEXT)
    {
        printf("Line %d:\t", p->line);
        printf("%s %d %s %s %d %c\n", p->USER_DATA.usrn, p->USER_DATA.ID, p->USER_DATA.location, p->USER_DATA.anual_check, p->USER_DATA.account_state);
    }
    printf("\n");

    return;
}

int linklist_find_data(LINKLIST *pList, char *usrn)
{
    LINKLIST_NODE *p;
    int isFound = 0;
    for (p = pList->HEAD; p; p = p->NEXT)
    {
        if (strcmp(p->USER_DATA.usrn, usrn) == 0)
        {
            //printf("Found!\n");
            isFound = 1;
            break;
        }
    }
    if (!isFound)
    {
        //printf("Not found!\n");
    }

    return isFound;
}

void linklist_delete_data(LINKLIST *pList, char *usrn)
{
    LINKLIST_NODE *p;
    LINKLIST_NODE *q;
    for (q = NULL, p = pList->HEAD; p; q = p, p = p->NEXT)
    {
        if (strcmp(p->USER_DATA.usrn, usrn) == 0)
        {
            if (q)
            {
                q->NEXT = p->NEXT;
            }
            else
            {
                pList->HEAD = p->NEXT;
            }
            free(p);
            break;
        }
    }

    return;
}

void linklist_clear(LINKLIST *pList)
{
    LINKLIST_NODE *q;
    LINKLIST_NODE *p;
    for (p = pList->HEAD; p; p = q)
    {
        q = p->NEXT;
        free(p);
    }

    return;
}

LINKLIST list;
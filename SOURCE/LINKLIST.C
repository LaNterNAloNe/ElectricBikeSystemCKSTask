#include "LINKLIST.H"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//链表用来将较多数据存储到内存中以方便进行频繁访问

void linklist_add_data(LINKLIST *pList, LINKLIST_USER data)
{
    LINKLIST_NODE *p = (LINKLIST_NODE *)malloc(sizeof(LINKLIST_NODE));
    LINKLIST_NODE *last = pList->head;
    p->userdata = data;
    p->next = NULL;
    if (last)
    {
        while (last->next)
        {
            last = last->next;
        }
        // attach
        last->next = p;
        p->line = last->line + 1;
    }
    else
    {
        pList->head = p;
        p->line = 1;
    }

    return;
}

void linklist_print_data(LINKLIST *pList)
{
    LINKLIST_NODE *p;
    printf("All data:\n");
    for (p = pList->head; p; p = p->next)
    {
        printf("Line %d:\t", p->line);
        printf("%s %s %s %c %c\n", p->userdata.ID, p->userdata.pass, p->userdata.license, p->userdata.check, p->userdata.location);
    }
    printf("\n");

    return;
}

int linklist_find_data(LINKLIST *pList, char *ID)
{
    LINKLIST_NODE *p;
    int isFound = 0;
    for (p = pList->head; p; p = p->next)
    {
        if (strcmp(p->userdata.ID, ID) == 0)
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

void linklist_delete_data(LINKLIST *pList, char *ID)
{
    LINKLIST_NODE *p;
    LINKLIST_NODE *q;
    for (q = NULL, p = pList->head; p; q = p, p = p->next)
    {
        if (strcmp(p->userdata.ID, ID) == 0)
        {
            if (q)
            {
                q->next = p->next;
            }
            else
            {
                pList->head = p->next;
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
    for (p = pList->head; p; p = q)
    {
        q = p->next;
        free(p);
    }

    return;
}

LINKLIST list;
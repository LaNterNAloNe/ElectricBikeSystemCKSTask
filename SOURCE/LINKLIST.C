#include "LINKLIST.H"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//链表用来将较多数据存储到内存中以方便进行频繁访问

/**********************************************************
NAME:linklist_add_data
VALUE:pList自定链表，NEW_USER_DATA待加入链表的结构体
FUNCTION:将一个结构体添加到链表中
**********************************************************/
void linklist_add_data(LINKLIST *pList, LINKLIST_USER NEW_USER_DATA)
{
    LINKLIST_NODE *DATA_NODE = (LINKLIST_NODE *)malloc(sizeof(LINKLIST_NODE));
    LINKLIST_NODE *LAST_NODE = pList->HEAD; // LAST_NODE要找到链表中最后一个节点，先指向头结点

    DATA_NODE->USER_DATA = NEW_USER_DATA;
    DATA_NODE->NEXT = NULL; // 对传入的要加入链表的结构体处理一下，先定义指向下一节点的指针为空（下一节点待后续添加）

    if (LAST_NODE)  // 如果头节点不为空，则一直遍历到链表末尾
    {
        while (LAST_NODE->NEXT) LAST_NODE = LAST_NODE->NEXT;

        LAST_NODE->NEXT = DATA_NODE; // 查找到末尾节点后，将新加的结构体连接上去，并标明所在序号
        DATA_NODE->PREVIOUS = LAST_NODE;
        DATA_NODE->chain_lenth = LAST_NODE->chain_lenth + 1;
    }else  // 如果头结点为空，则将新加的结构体定义为头结点
    {
        pList->HEAD = DATA_NODE;
        DATA_NODE->chain_lenth = 1;
        DATA_NODE->PREVIOUS = NULL; // 将头结点指向前一节点的指针定义为NULL，作为开头
    }

    return;
}


/**********************************************************
NAME:linklist_find_data
VALUE:pList自定链表，str要搜索的内容
FUNCTION:利用传入的字符串，查找链表中相应内容
**********************************************************/
int linklist_find_data(LINKLIST *pList, char *str, char *needed_finding)
{
    LINKLIST_NODE *ptr;
    int isFound = 0;
    char *buffer;
    for (ptr = pList->HEAD; ptr; ptr = ptr->NEXT)
    {
        if (!strcmp(needed_finding,"username")) {
            if (!strcmp(ptr->USER_DATA.usrn, str))
                isFound++;
        }
        if (!strcmp(needed_finding,"id")) {
            itoa(ptr->USER_DATA.ID,buffer,10);
            if(strcmp(buffer, str) == 0)
                isFound++;
        }
        if (!strcmp(needed_finding,"realname")) {
            if(!strcmp(ptr->USER_DATA.rln, str)) 
                isFound++;
        }
        if (!strcmp(needed_finding,"location")) {
            if(!strcmp(ptr->USER_DATA.location, str))
                isFound++;
        }
        if (!strcmp(needed_finding,"anualcheck")) {
            itoa(ptr->USER_DATA.anual_check,buffer,10);
            if(!strcmp(buffer, str))
                isFound++;
        }
        if (strcmp(needed_finding,"accountstate")) {
            itoa((int)ptr->USER_DATA.account_state-'0',buffer,10);
            if(!strcmp(buffer, str))
                isFound++;
        }
        if (strcmp(needed_finding,"violations")) {
            itoa(ptr->USER_DATA.violations,buffer,10);
            if(!strcmp(buffer, str))
                isFound++;
        }
        if (isFound) return isFound;
    }

    return isFound;
}


/**********************************************************
NAME:linklist_delete_data
VALUE:pList自定链表，usrn要清除的数据的用户名，只通过用户名查找
FUNCTION:利用传入的字符串，查找链表中相应内容
**********************************************************/
int linklist_delete_data(LINKLIST *pList, char *usrn)
{
    LINKLIST_NODE *ptr_previous;
    LINKLIST_NODE *ptr_next; // 定义两个一前一后的指针，分别指向链表中相邻两个结构体，从开头开始遍历
    for (ptr_previous = NULL, ptr_next = pList->HEAD; ptr_next; ptr_previous = ptr_next, ptr_next = ptr_next->NEXT)
    {
        if (strcmp(ptr_next->USER_DATA.usrn, usrn) == 0)
        {
            if (ptr_previous) ptr_previous->NEXT = ptr_next->NEXT; // 如果前者指针不为空，则将前者指针指向 _后者指针指向的结构体中的_ NEXT指针
            else pList->HEAD = ptr_next->NEXT; // 如果前者指针为空，则将前者指针指向的结构体作为链表头
            free(ptr_next); // 最后释放要删除的节点
            return 1;
        }
    }

    return 0;
}


/**********************************************************
NAME:linklist_clear
VALUE:pList自定链表
FUNCTION:将链表释放
**********************************************************/
void linklist_clear(LINKLIST *pList) {
    LINKLIST_NODE *next;
    LINKLIST_NODE *current = pList->HEAD;

    if (!pList) return;
    while (current) {
        next = current->NEXT; // 先保存后释放 
        free(current);
        current = next;
    }
    pList->HEAD = NULL; // 清除悬空指针 
    free(pList);
}
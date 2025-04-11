#ifndef LINKLIST_H
#define LINKLIST_H

#include"GROCERY.H"

#define USER_DATA_FILE_NAME "C:\\EBS\\DATA\\USRDAT.TXT"

typedef struct _LINKLIST_USER_{
    unsigned long ID;
    char usrn[15];
    char rln[16];
    char location[10];
    char ebike_ID[10];
    char ebike_license[7];
    unsigned long anual_check;
    int violations;
    char account_state;
    char ebike_state;
} LINKLIST_USER;

// typedef struct
// {
//     int ID;
//     char rln[16];
//     char ebike_ID[10];
//     char account_state;
// } LINKLIST_LICENSE;

// typedef union
// {
//     LINKLIST_LICENSE USER_LICENSE;
//     LINKLIST_USER USER_DATA;
// }LINKLIST_BODY;

typedef struct _LINKLISTNODE_
{
    int chain_lenth;
    LINKLIST_USER USER_DATA;
    struct _LINKLISTNODE_ *PREVIOUS;
    struct _LINKLISTNODE_ *NEXT;
} LINKLIST_NODE;

typedef struct _LINKLIST_
{
    LINKLIST_NODE *HEAD;
} LINKLIST;

void linklist_add_data(LINKLIST *pList, LINKLIST_USER NEW_USER_DATA);
int linklist_find_data(LINKLIST *pList, char *str, char *needed_finding);
int linklist_delete_data(LINKLIST *pList, char *usrn);
int linklist_get_length(LINKLIST *pList);
void linklist_get_to_node(LINKLIST *pList, int index, LINKLIST_NODE **ptr);
void linklist_clear(LINKLIST *pList);
void linklist_get_user_data(LINKLIST *LIST);
int linklist_write_user_data(LINKLIST *pList);

#endif
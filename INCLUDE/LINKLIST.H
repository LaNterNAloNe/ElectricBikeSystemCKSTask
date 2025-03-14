typedef struct
{
    int ID;
    char usrn[10];
    char rln[15];
    char location[10];
    int anual_check;
    char account_state;
} LINKLIST_USER;

typedef struct
{
    int chain_lenth;
    LINKLIST_USER USER_DATA;
    struct LINKLIST_NODE *PREVIOUS;
    struct LINKLIST_NODE *NEXT;
} LINKLIST_NODE;

typedef struct
{
    LINKLIST_NODE *HEAD;
} LINKLIST;

void linklist_add_data(LINKLIST *pList, LINKLIST_USER NEW_USER_DATA);
int linklist_find_data(LINKLIST *pList, char *str, char *needed_finding);
int linklist_delete_data(LINKLIST *pList, char *usrn);
void linklist_clear(LINKLIST *pList);

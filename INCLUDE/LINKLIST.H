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
    int line;
    LINKLIST_USER USER_DATA;
    struct LINKLIST_NODE *NEXT;
} LINKLIST_NODE;

typedef struct
{
    LINKLIST_NODE *HEAD;
} LINKLIST;

void linklist_add_data(LINKLIST *pList, LINKLIST_USER data);
void linklist_print_data(LINKLIST *pList);
int linklist_find_data(LINKLIST *pList, char *ID);
void linklist_delete_data(LINKLIST *pList, char *ID);
void linklist_clear(LINKLIST *pList);

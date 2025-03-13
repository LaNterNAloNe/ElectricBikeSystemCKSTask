typedef struct
{
    char ID[15];
    char pass[15];
    char license[15];
    char check;
    char location;
} LINKLIST_USER;

typedef struct
{
    int line;
    LINKLIST_USER userdata;
    struct LINKLIST_NODE *next;
} LINKLIST_NODE;

typedef struct
{
    LINKLIST_NODE *head;
} LINKLIST;

void linklist_add_data(LINKLIST *pList, LINKLIST_USER data);
void linklist_print_data(LINKLIST *pList);
int linklist_find_data(LINKLIST *pList, char *ID);
void linklist_delete_data(LINKLIST *pList, char *ID);
void linklist_clear(LINKLIST *pList);

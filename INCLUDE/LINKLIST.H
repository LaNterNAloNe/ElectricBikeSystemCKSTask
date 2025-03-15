typedef struct
{
    int ID;
    char usrn[15];
    char rln[16];
    char location[10];
    char ebike_ID[10];
    char ebike_license[7];
    int anual_check;
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

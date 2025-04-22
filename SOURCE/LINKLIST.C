#include "LINKLIST.H"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

    if (LAST_NODE) // 如果头结点不为空，则遍历到末尾节点，第一个判断条件是针对刚初始化的链表的头结点的
    {
        while (LAST_NODE->NEXT) LAST_NODE = LAST_NODE->NEXT;

        LAST_NODE->NEXT = DATA_NODE; // 查找到末尾节点后，将新加的结构体连接上去，并标明所在序号
        DATA_NODE->PREVIOUS = LAST_NODE;
        DATA_NODE->chain_lenth = LAST_NODE->chain_lenth + 1;
    }else  // 如果头结点为空，则将新加的结构体定义为头结点，序号为1
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
    int chain_length = 0;
    char *buffer;
    for (ptr = pList->HEAD; ptr; ptr = ptr->NEXT)
    {
        if (!strcmp(needed_finding,"username")) {
            if (!strcmp(ptr->USER_DATA.usrn, str))
                chain_length = ptr->chain_lenth;
        }
        if (!strcmp(needed_finding,"id")) {
            itoa(ptr->USER_DATA.ID,buffer,10);
            if(strcmp(buffer, str) == 0)
                chain_length = ptr->chain_lenth;
        }
        if (!strcmp(needed_finding,"realname")) {
            if(!strcmp(ptr->USER_DATA.rln, str))
                chain_length = ptr->chain_lenth;
        }
        if (!strcmp(needed_finding,"location")) {
            if(!strcmp(ptr->USER_DATA.location, str))
                chain_length = ptr->chain_lenth;
        }
        if (!strcmp(needed_finding,"anual_check")) {
            itoa(ptr->USER_DATA.anual_check,buffer,10);
            if(!strcmp(buffer, str))
                chain_length = ptr->chain_lenth;
        }
        if (strcmp(needed_finding,"account_state")) {
            itoa((int)ptr->USER_DATA.account_state-'0',buffer,10);
            if(!strcmp(buffer, str))
                chain_length = ptr->chain_lenth;
        }
        if (strcmp(needed_finding,"violations")) {
            itoa(ptr->USER_DATA.violations,buffer,10);
            if(!strcmp(buffer, str))
                chain_length = ptr->chain_lenth; // 如果找到，则返回该节点的序号
        }
        if (chain_length) return chain_length; // 如果找到，则返回该节点的序号
    }

    return -1; // 如果没有找到，则返回0
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
NAME:linklist_get_length
VALUE:pList自定链表
FUNCTION:获取链表的长度
**********************************************************/
int linklist_get_length(LINKLIST *pList)
{
    int length = 0;
    LINKLIST_NODE *ptr = pList->HEAD; // 定义一个指针指向链表头
    while(ptr){
        // show_num(10,10,ptr->USER_DATA.ID,MY_WHITE); // 显示链表中每个节点的ID
        // getch();
        length++;
        ptr = ptr->NEXT; // 遍历链表，直到指针为空
    }
    return length;
}

/**********************************************************
NAME:linklist_get_to_node
VALUE:pList自定链表，index要查找的节点的序号，ptr要矫正的节点指针，传入一个二级指针以修改需要移动的指针的地址
FUNCTION:将传入的指针矫正到相应的节点
**********************************************************/
void linklist_get_to_node(LINKLIST *pList, int index, LINKLIST_NODE **ptr){
    int i;
    for(i = 1, *ptr = pList->HEAD; i <= index; i++, *ptr = (*ptr)->NEXT);
    return;
}


/**********************************************************
NAME:linklist_clear
VALUE:pList自定链表
FUNCTION:将链表释放
**********************************************************/

void linklist_clear(LINKLIST *pList)
{
    LINKLIST_NODE *q;
    LINKLIST_NODE *p = pList->HEAD;
    while (p != NULL)
    {
        q = p->NEXT;
        free(p);
        p = q;
    }
    free(pList); // 释放链表结构体
    pList->HEAD = NULL; // 重置头指针
    return;
}

/**********************************************************
NAME:linklist_get_user_data
VALUE:pList自定链表
FUNCTION:将信息获取到链表中
**********************************************************/
void linklist_get_user_data(LINKLIST *LIST)
{
    char buffer[120];        // 定义缓冲区
    char *token;             // 定义获取截断字符串的token
    LINKLIST_USER LIST_USER; // 定义结构体，准备加入链表

    FILE *fp_USER_DATA_read = fopen(USER_DATA_FILE_NAME, "r");
    if (fp_USER_DATA_read == NULL)
        getch(), exit(1);
    fseek(fp_USER_DATA_read, 0, SEEK_END); // 将文件指针置于开头，开始遍历文件
    if (ftell(fp_USER_DATA_read) == 0) { // 如果文件为空，则直接返回
        fclose(fp_USER_DATA_read);
        return;
    }

    fseek(fp_USER_DATA_read, 0, SEEK_SET); // 将文件指针置于开头，开始遍历文件

    while (fgets(buffer, sizeof(buffer), fp_USER_DATA_read))
    {
        if (!strcmp(buffer, "\0"))
            continue;
    
        token = strtok(buffer, ",");
        LIST_USER.ID = token ? atol(token) : 0;

        strncpy(LIST_USER.usrn, strtok(NULL, ","), sizeof(LIST_USER.usrn));
        strncpy(LIST_USER.rln, strtok(NULL, ","), sizeof(LIST_USER.rln));
        strncpy(LIST_USER.location, strtok(NULL, ","), sizeof(LIST_USER.location));
        strncpy(LIST_USER.ebike_ID, strtok(NULL, ","), sizeof(LIST_USER.ebike_ID));
        strncpy(LIST_USER.ebike_license, strtok(NULL, ","), sizeof(LIST_USER.ebike_license));

        token = strtok(NULL, ",");
        LIST_USER.anual_check = token ? atol(token) : 0;

        token = strtok(NULL, ",");
        LIST_USER.violations = token ? atoi(token) : 0;

        token = strtok(NULL, ",");
        LIST_USER.account_state = (token && *token) ? *token : ACTIVE;

        token = strtok(NULL, ",\n");
        LIST_USER.ebike_state = (token && *token) ? *token : ACTIVE;

        linklist_add_data(LIST, LIST_USER);

        memset(buffer, 0, sizeof(buffer));
        memset(&LIST_USER, 0, sizeof(LINKLIST_USER)); // 确保结构体清零
    }
    fclose(fp_USER_DATA_read); // 关闭文件
}

// void linklist_get_user_data(LINKLIST *LIST)
// {
//     int parsed;
//     char buffer[120];
//     LINKLIST_USER LIST_USER;
//     FILE *fp = fopen(USER_DATA_FILE_NAME, "r");
//     if (!fp)
//         exit(1);

//     // 预判空文件（原逻辑保留）
//     fseek(fp, 0, SEEK_END);
//     if (ftell(fp) == 0)
//     {
//         fclose(fp);
//         return;
//     }
//     fseek(fp, 0, SEEK_SET);

//     while (fgets(buffer, sizeof(buffer), fp))
//     {
//         if (buffer[0] == '\0')
//             continue;

//         // 改进2：使用sscanf替代strtok
//         parsed = sscanf(buffer,
//                         "%19[^,],%19[^,],%19[^,],%19[^,],%19[^,],%ld,%d,%c,%c",
//                         LIST_USER.usrn,
//                         LIST_USER.rln,
//                         LIST_USER.location,
//                         LIST_USER.ebike_ID,
//                         LIST_USER.ebike_license,
//                         &LIST_USER.anual_check,
//                         &LIST_USER.violations,
//                         &LIST_USER.account_state,
//                         &LIST_USER.ebike_state);

//         LIST_USER.account_state = (parsed >= 8) ? LIST_USER.account_state : ACTIVE;
//         LIST_USER.ebike_state = (parsed >= 9) ? LIST_USER.ebike_state : ACTIVE;

//         linklist_add_data(LIST, LIST_USER);
//         memset(&LIST_USER, 0, sizeof(LINKLIST_USER));
//     }
//     fclose(fp);
// }

/**********************************************************
NAME:linklist_write_user_data
VALUE:pList自定链表
FUNCTION:将链表数据原子化写入文件，确保与原读取逻辑兼容
RETURN:0成功，-1失败
***********************************************************/
int linklist_write_user_data(LINKLIST *pList)
{
    const char *TMP_PATH = "DATA\\TEMP.tmp"; // 临时文件名
    const char *FINAL_PATH = "DATA\\USRDAT.TXT";
    FILE *fp = NULL;
    LINKLIST_NODE *ptr = pList->HEAD;
    char buffer[200]; // 扩大缓冲区防止溢出

    fp = fopen(TMP_PATH, "w+"); // 打开临时文件
    if (!fp)
    {
        perror("linklist_write_user_data: can not create temp file");
        return -1;
    }

    while (ptr != NULL) // 遍历链表并写入
    {
        // 按字段顺序格式化字符串
        sprintf(buffer,"%d,%s,%s,%s,%s,%s,%d,%d,%c,%c,\n",
                ptr->USER_DATA.ID,
                ptr->USER_DATA.usrn,
                ptr->USER_DATA.rln,
                ptr->USER_DATA.location,
                ptr->USER_DATA.ebike_ID,
                ptr->USER_DATA.ebike_license,
                ptr->USER_DATA.anual_check,
                ptr->USER_DATA.violations,
                ptr->USER_DATA.account_state,
                ptr->USER_DATA.ebike_state);

        // 写入文件并检查错误
        if (fputs(buffer, fp) == EOF)
        {
            perror("linklist_write_user_data: write to temp file failed");
            ptr = NULL;
            fclose(fp);
            remove(TMP_PATH);
            getch();
            exit(1);
        }
        ptr = ptr->NEXT;
    }

    fclose(fp);

    remove(FINAL_PATH); // 删除原文件
    if (rename(TMP_PATH, FINAL_PATH) != 0) // 替换文件
    {
        perror("linklist_write_user_data: rename temp file failed");
        ptr = NULL;
        remove(TMP_PATH);
        getch();
        exit(1);
    }
    ptr = NULL;

    return 0;
}
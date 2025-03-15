#ifndef LOGIN_H
#define LOGIN_H

#include <stdio.h>
#include <graphics.h>
#include <string.h>
#include <conio.h>
#include <DOS.H>
#include <ctype.h>
#include <stdlib.H>
#include"GROCERY.H"
#include"MOUSE.H"
#include"INPUTCH.H"
#include"HZ.H"

//定义登录界面可交互块的坐标
#define USERNAME_X1 220
#define USERNAME_Y1 170
#define USERNAME_X2 480
#define USERNAME_Y2 205
#define PASSWORD_X1 220
#define PASSWORD_Y1 260
#define PASSWORD_X2 480
#define PASSWORD_Y2 295
#define LOGIN_X1 230
#define LOGIN_Y1 320
#define LOGIN_X2 330
#define LOGIN_Y2 370
#define REGISTER_X1 360
#define REGISTER_Y1 320
#define REGISTER_X2 460
#define REGISTER_Y2 370
#define ADMIN_X1 130
#define ADMIN_Y1 330
#define ADMIN_X2 210
#define ADMIN_Y2 350
#define ADMIN_LOGIN_X1 295
#define ADMIN_LOGIN_Y1 320
#define ADMIN_LOGIN_X2 395
#define ADMIN_LOGIN_Y2 370
#define EXITPROGRAM_X1 10
#define EXITPROGRAM_Y1 10
#define EXITPROGRAM_X2 50
#define EXITPROGRAM_Y2 50
#define ACTIVE_USERNAME 1
#define ACTIVE_PASSWORD 2
#define ACTIVE_LOGIN 3
#define ACTIVE_REGISTER 4
#define ACTIVE_ADMIN 5
#define ACTIVE_ADMIN_LOGIN 6
#define EXIT_PROGRAM -1
#define ACTIVE_NONE 0

//定义密码，用户名最大长度
#define MAX_LEN 14

//声明函数
void login(int *page,int *uid);
void login_admin(int *page,int *uid);
void _register(int *page);
void drawgraph_login(void);
void drawgraph_admin_login(void);
void drawgraph_register(void);
void flushLoginGraph(int *tag,int *page);
void userlogin_judge(char *usrn,char *psw,int *uid);
void adminlogin_judge(char *usrn,char *psw,int *uid);
int userregister_judge(char *usrn,char *psw);
void switchPage();
void anime_register_success();
void anime_register_fail(int err);
void anime_login_success();
void anime_login_fail();
void anime_admin_login_success();
void anime_admin_login_fail();

typedef struct {
    int ID;
    char usrn[MAX_LEN];
    char psw[MAX_LEN];
    char state;
}USER_LOGIN_DATA;
//若要修改结构体信息，则记得删掉之前的.DAT文件重新写入账号信息

typedef struct {
    int uid;
    char usrn[MAX_LEN];
    char psw[MAX_LEN];
}ADMIN_LOGIN_DATA;

#endif

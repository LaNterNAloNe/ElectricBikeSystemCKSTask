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
#define MAX_LEN 15

//声明函数
void login(int *page);
void login_admin(int *page);
void _register(int *page);
void drawgraph_login(void);
void drawgraph_admin_login(void);
void drawgraph_register(void);
void flushLoginGraph(int *tag,int *page);
void switchPage();


#endif

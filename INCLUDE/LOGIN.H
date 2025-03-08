#ifndef LOGIN_H
#define LOGIN_H

#include <graphics.h>
#include <string.h>
#include <conio.h>
#include <DOS.H>
#include <ctype.h>
#include"KEYINPUT.H"
#include"MOUSE.H"
#include"INPUTCH.H"

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
#define ADMIN_X1 160
#define ADMIN_Y1 330
#define ADMIN_X2 200
#define ADMIN_Y2 360


void login(int *page,int *num);
void drawgraph_login(void);


#endif

// typedef struct {
// 	int x1, y1, x2, y2;    // 输入框坐标
// 	char text[MAX_INPUT_LEN]; // 输入内容
// 	char placeholder[20];        // 提示文字字段 
// 	int cursor_pos;         // 光标位置
// 	int is_active;          // 是否激活状态
// 	unsigned long last_blink;    // 光标计时器 
// } InputBox;
// /* 宏定义 */
// #define MAX_USERNAME_LEN 20 
// #define MAX_PASSWORD_LEN 16 
// #define ADMIN_USER "admin"
// #define ADMIN_PASS "admin"
// #define ERR_EMPTY   -1 
// #define ERR_INVALID -2 
// #define MAX_INPUT_LEN 20
// #define TIMER_FREQ 1193180L // 8253 PIT频率 
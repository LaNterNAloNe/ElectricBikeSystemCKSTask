#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include<conio.h>
#include<graphics.h>
#include<stdio.h>
#include<stdlib.h>
#include<bios.h>
#include<string.h>
#include<dos.h>
#include<math.h>
#include<time.h>

#include"HZ.H"
#include"MOUSE.H"
#include"LOGIN.H"
#include"KEYINPUT.H"

//声明显示模式，驱动器
const int driver =VGA;
const int mode =VGAHI;

//定义page各个状态
#define EXIT 0
#define LOGIN 1
#define LOGIN_ADMIN 2
#define REGISTER 3

#define MAIN_USER 10
#define USER_BIKE_REGISTER 11
#define USER_BIKE_LICENSE 12
#define USER_BIKE_ANULL_AND_WROTEOUT 13
#define USER_INFO 14
#define USER_MESSAGE 15
#define USER_DATAGRAPH 16

#define MAIN_ADMIN 20
#define ADMIN_BIKE_REGISTER 21
#define ADMIN_BIKE_LICENSE 22
#define ADMIN_BIKE_ANULL_AND_WROTEOUT 23
#define ADMIN_BIKE_PENALIZE 24
#define ADMIN_INFO 25
#define ADMIN_MESSAGE 26
#define ADMIN_DATABASE 27

void drawExittingProgram(void){
    setcolor(BLUE);
    setfillstyle(SOLID_FILL, CYAN);
    bar(120,120,520,390);
    puthz(180, 200, "你正在退出程序，按任意键退出", 24, 20, WHITE);
}

#endif
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

#include "HZ.H"
#include "MOUSE.H"
#include "LOGIN.H"
#include "GROCERY.H"
#include "_ADMIN_.H"
#include "USER.H"

void drawExittingProgram(int err){
    setfillstyle(SOLID_FILL, CYAN);
    bar(120,120,520,390);
    if(err == 0) puthz(180, 200, "你正在退出程序，按任意键退出", 24, 20, MY_WHITE);
    if(err == 1) puthz(180, 200, "无法打开用户数据库", 24, 20, MY_RED);
}

#endif

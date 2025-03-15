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


void initcolorpalette(){
    setrgbpalette(MY_LIGHTBLUE, 12,158,245);//浅蓝背景-1
	setrgbpalette(MY_LIGHTGRAY, 235,235,235);//浅灰框-1
	setrgbpalette(MY_BLACK, 0, 0, 0);//黑色
	setrgbpalette(MY_YELLOW, 240, 230,75);//黄色
	setrgbpalette(MY_RED, 255, 0, 0);//红色
	setrgbpalette(MY_WHITE, 255, 255, 255);//白色
    setrgbpalette(MY_GREEN, 0, 255, 0);//绿色
}

void drawExittingProgram(int err){
    setfillstyle(SOLID_FILL, CYAN);
    bar(120,120,520,390);
    if(err == 0) puthz(180, 200, "你正在退出程序，按任意键退出", 24, 20, MY_WHITE);
    if(err == 1) puthz(180, 200, "无法打开用户数据库", 24, 20, MY_RED);
}

#endif

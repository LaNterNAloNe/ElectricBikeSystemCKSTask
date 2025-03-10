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
#include"GROCERY.H"

//声明显示模式，驱动器
const int driver =VGA;
const int mode =VGAHI;

void drawExittingProgram(void){
    setfillstyle(SOLID_FILL, CYAN);
    bar(120,120,520,390);
    puthz(180, 200, "你正在退出程序，按任意键退出", 24, 20, MY_WHITE);
}

#endif
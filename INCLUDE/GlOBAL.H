#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#pragma option -N+ -Z -G-      //大内存模型/关闭堆栈检查/紧凑代码/全局优化 

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

void initcolorpalette();
void drawExittingProgram(int err);



#endif

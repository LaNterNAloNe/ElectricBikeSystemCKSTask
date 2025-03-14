#ifndef __ADMIN__H_
#define __ADMIN__H_

#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<conio.h>
#include<string.h>
#include"GROCERY.H"
#include"LINKLIST.H"
#include"MOUSE.H"
#include"HZ.H"


//定义界面坐标
#define MENU_X1 0
#define MENU_Y1 0
#define MENU_X2 120
#define MENU_Y2 480
#define INTERFACE_A_X1 121
#define INTERFACE_A_Y1 0
#define INTERFACE_A_X2 380
#define INTERFACE_A_Y2 480
#define INTERFACE_B_X1 381
#define INTERFACE_B_Y1 0
#define INTERFACE_B_X2 640
#define INTERFACE_B_Y2 480

//定义按钮坐标
#define ADMIN_BUTTON1_X1 20
#define ADMIN_BUTTON1_Y1 10
#define ADMIN_BUTTON1_X2 100
#define ADMIN_BUTTON1_Y2 43

#define ADMIN_BUTTON2_X1 20
#define ADMIN_BUTTON2_Y1 50
#define ADMIN_BUTTON2_X2 100
#define ADMIN_BUTTON2_Y2 83

#define ADMIN_BUTTON3_X1 20
#define ADMIN_BUTTON3_Y1 90
#define ADMIN_BUTTON3_X2 100
#define ADMIN_BUTTON3_Y2 123

#define ADMIN_BUTTON4_X1 20
#define ADMIN_BUTTON4_Y1 130
#define ADMIN_BUTTON4_X2 100
#define ADMIN_BUTTON4_Y2 163

#define ADMIN_BUTTON5_X1 20
#define ADMIN_BUTTON5_Y1 170
#define ADMIN_BUTTON5_X2 100
#define ADMIN_BUTTON5_Y2 203

#define ADMIN_BUTTON6_X1 20
#define ADMIN_BUTTON6_Y1 210
#define ADMIN_BUTTON6_X2 100
#define ADMIN_BUTTON6_Y2 243

#define ADMIN_EXIT_X1 10
#define ADMIN_EXIT_Y1 440
#define ADMIN_EXIT_X2 25
#define ADMIN_EXIT_Y2 455

#define ADMIN_EXIT_MENU_X1 10
#define ADMIN_EXIT_MENU_Y1 380
#define ADMIN_EXIT_MENU_X2 80
#define ADMIN_EXIT_MENU_Y2 430


//定义激活状态
#define ACTIVE_ADMIN_NULL 0
#define ACTIVE_ADMIN_BUTTON1 1
#define ACTIVE_ADMIN_BUTTON2 2
#define ACTIVE_ADMIN_BUTTON3 3
#define ACTIVE_ADMIN_BUTTON4 4
#define ACTIVE_ADMIN_BUTTON5 5
#define ACTIVE_ADMIN_BUTTON6 6
#define ACTIVE_ADMIN_EXIT 7

typedef void (*DRAWFUNCTION) (int coord1,int coord2,int coord3,int coord4);
typedef void (*CLEARFUNCTION) (int coord1,int coord2,int coord3,int coord4);

typedef struct {
    int x1, x2, y1, y2;
    int active_tag;
    DRAWFUNCTION drawfunc;
    CLEARFUNCTION clearfunc;
} ADMIN_BUTTONS;

void main_admin(int *page,int *ID);
void drawgraph_admin_main(void);
void draw_cues(int x,int y,int null1,int null2);
void clear_cues(int x1,int y1,int x2,int y2);
void draw_exit(int x1,int y1,int x2,int y2);
void clear_exit(int x1,int y1,int x2,int y2);
int admin_exitting(int *page);
void draw_exit_menu(int x1,int y1,int x2,int y2);
void clear_exit_menu(int x1,int y1,int x2,int y2);
void flush_admin_main_graph(int *tag,int button_counts,ADMIN_BUTTONS AdminButtons[]);
void get_user_data(LINKLIST *LIST);
void AdminswitchPage(){
	int i,j,k;
	setfillstyle(SOLID_FILL,MY_LIGHTBLUE);
	for(i=0;i<16;i++)
		for(j=0;j<12;j++)
			for(k=0;k<=5;k++)
			{
				bar(i*40+20-k*4,j*40+20-k*4,i*40+20+k*4,j*40+20+k*4);
				delay(1);
			}
}

#define STRUCT_LENGTH(Struct) (sizeof(Struct)/sizeof(Struct[0]))

#endif
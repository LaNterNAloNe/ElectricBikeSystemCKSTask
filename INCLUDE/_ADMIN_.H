#ifndef __ADMIN__H_
#define __ADMIN__H_

#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<conio.h>
#include <alloc.h>    // DOS内存管理头文件 
#include<string.h>
#include"GROCERY.H"
#include"LINKLIST.H"
#include"MOUSE.H"
#include"HZ.H"


//定义界面坐标
#define ADMIN_MENU_X1 0
#define ADMIN_MENU_Y1 0
#define ADMIN_MENU_X2 120
#define ADMIN_MENU_Y2 480
#define ADMIN_INTERFACE_A_X1 121
#define ADMIN_INTERFACE_A_Y1 0
#define ADMIN_INTERFACE_A_X2 380
#define ADMIN_INTERFACE_A_Y2 480
#define ADMIN_INTERFACE_B_X1 381
#define ADMIN_INTERFACE_B_Y1 0
#define ADMIN_INTERFACE_B_X2 640
#define ADMIN_INTERFACE_B_Y2 480
#define ADMIN_INTERFACE_X1 121
#define ADMIN_INTERFACE_Y1 0
#define ADMIN_INTERFACE_X2 640
#define ADMIN_INTERFACE_Y2 480

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

#define ADMIN_FEATURE1_X1 130
#define ADMIN_FEATURE1_Y1 440
#define ADMIN_FEATURE1_X2 200
#define ADMIN_FEATURE1_Y2 470

#define ADMIN_FEATURE2_X1 208
#define ADMIN_FEATURE2_Y1 440
#define ADMIN_FEATURE2_X2 278
#define ADMIN_FEATURE2_Y2 470

#define ADMIN_FEATURE3_X1 286
#define ADMIN_FEATURE3_Y1 440
#define ADMIN_FEATURE3_X2 356
#define ADMIN_FEATURE3_Y2 470

#define ADMIN_FEATURE4_X1 364
#define ADMIN_FEATURE4_Y1 440
#define ADMIN_FEATURE4_X2 434
#define ADMIN_FEATURE4_Y2 470

#define ADMIN_FEATURE5_X1 442
#define ADMIN_FEATURE5_Y1 440
#define ADMIN_FEATURE5_X2 512
#define ADMIN_FEATURE5_Y2 470

#define ADMIN_FEATURE6_X1 520
#define ADMIN_FEATURE6_Y1 440
#define ADMIN_FEATURE6_X2 590
#define ADMIN_FEATURE6_Y2 470

#define ADMIN_FEATURE_SEARCH_X1 130
#define ADMIN_FEATURE_SEARCH_Y1 390
#define ADMIN_FEATURE_SEARCH_X2 340
#define ADMIN_FEATURE_SEARCH_Y2 420

#define ADMIN_FEATURE_EXIT_X1 610
#define ADMIN_FEATURE_EXIT_Y1 450
#define ADMIN_FEATURE_EXIT_X2 630
#define ADMIN_FEATURE_EXIT_Y2 470


//定义激活状态
#define ACTIVE_ADMIN_NULL 0
#define ACTIVE_ADMIN_BUTTON1 1
#define ACTIVE_ADMIN_BUTTON2 2
#define ACTIVE_ADMIN_BUTTON3 3
#define ACTIVE_ADMIN_BUTTON4 4
#define ACTIVE_ADMIN_BUTTON5 5
#define ACTIVE_ADMIN_BUTTON6 6
#define ACTIVE_ADMIN_EXIT 7
#define ACTIVE_ADMIN_FEATURE1 8
#define ACTIVE_ADMIN_FEATURE2 9
#define ACTIVE_ADMIN_FEATURE3 10
#define ACTIVE_ADMIN_FEATURE4 11
#define ACTIVE_ADMIN_FEATURE5 12
#define ACTIVE_ADMIN_FEATURE6 13
#define ACTIVE_ADMIN_FEATURE_SEARCH 14
#define ACTIVE_ADMIN_FEATURE_EXIT 20


typedef void (*DRAWFUNCTION) (int coord1,int coord2,int coord3,int coord4);
typedef void (*CLEARFUNCTION) (int coord1,int coord2,int coord3,int coord4);

typedef struct {
    int x1, x2, y1, y2;
    int active_tag;
    DRAWFUNCTION drawfunc;
    CLEARFUNCTION clearfunc;
} ADMIN_BUTTONS;

typedef struct {
    char rln[16];
	int ID;
	char ebike_ID[10];
    int apply_time;
	int conduct_time;
    int result;
} EBIKE_REGISTER;

void main_admin(int *page,int *ID);
void drawgraph_admin_menu(void);
void draw_cues(int x,int y,int null1,int null2);
void clear_cues(int x1,int y1,int x2,int y2);
void draw_rectangle(int x1,int y1,int x2,int y2);
void clear_rectangle(int x1,int y1,int x2,int y2);
void draw_exit(int x1,int y1,int x2,int y2);
void clear_exit(int x1,int y1,int x2,int y2);
int admin_exitting(int *page);
void draw_exit_menu(int x1,int y1,int x2,int y2);
void clear_exit_menu(int x1,int y1,int x2,int y2);

void admin_bike_register(int *page,int *id);
void drawgraph_admin_bike_register();
void list_search_register_request(int id_list[8],FILE *fp,int mode,int page_change,int is_clear,char *search_str,char *search_needed);
int list_admin_register_search_is_valid(EBIKE_REGISTER TEMP,char *search_str,char *search_needed,int mode);

void admin_flush_graph(int *tag,int button_counts,ADMIN_BUTTONS AdminButtons[]);
void handle_click_event_admin_main(int *page);
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


 
/* 获取当前程序内存使用量（单位：KB） */
unsigned long get_used_memory() {
    struct heapinfo *hi;
    unsigned long total = 0;
 
    // 遍历堆内存分配块 
    hi->ptr  = NULL;
    while(heapwalk(hi) == _HEAPOK) {
        if(hi->in_use)  
            total += hi->size;  // 累计已分配内存 
    }
 
    // 转换为KB（DOS内存块以16字节为单位）
    return (total * 16) / 1024; 
}

void display_memory_usage(int x, int y) {
    static char mem_str[20];
    unsigned long mem_used;

    // 获取内存数据 
    mem_used = get_used_memory();

    // 构建显示字符串 
    sprintf(mem_str, "MEM: %lu KB", mem_used);
 
    // 图形模式输出（带背景刷新）
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, BLUE);
    bar(x-5, y-5, x+textwidth(mem_str)+5, y+textheight(mem_str)+5);
    settextstyle(DEFAULT_FONT,NULL,1);
    outtextxy(x, y, mem_str);
    sprintf(mem_str,"FARMEM LEFT: %lu Byte",farcoreleft());
    outtextxy(x,y+10,mem_str);
}

#define STRUCT_LENGTH(Struct) (sizeof(Struct)/sizeof(Struct[0]))

#endif

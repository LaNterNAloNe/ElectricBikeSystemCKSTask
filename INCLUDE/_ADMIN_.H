#ifndef __ADMIN__H_
#define __ADMIN__H_

#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<time.h>
#include<conio.h>
#include<string.h>
#include"GROCERY.H"
#include"LINKLIST.H"
#include"MOUSE.H"
#include"HZ.H"
#include"debug.h"
#include"LOGIN.H"


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

#define ADMIN_BUTTON7_X1 20
#define ADMIN_BUTTON7_Y1 250
#define ADMIN_BUTTON7_X2 100
#define ADMIN_BUTTON7_Y2 283

#define ADMIN_EXIT_X1 10
#define ADMIN_EXIT_Y1 440
#define ADMIN_EXIT_X2 25
#define ADMIN_EXIT_Y2 455

#define ADMIN_INFO_X1 40
#define ADMIN_INFO_Y1 435
#define ADMIN_INFO_X2 60
#define ADMIN_INFO_Y2 460

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

#define ADMIN_FEATURE_UP_X1 350
#define ADMIN_FEATURE_UP_Y1 395
#define ADMIN_FEATURE_UP_X2 370
#define ADMIN_FEATURE_UP_Y2 415

#define ADMIN_FEATURE_DOWN_X1 380
#define ADMIN_FEATURE_DOWN_Y1 395
#define ADMIN_FEATURE_DOWN_X2 400
#define ADMIN_FEATURE_DOWN_Y2 415

//定义数据标志
enum
{
    ADMIN_DATABASE_NULL = 0,
    ADMIN_DATABASE_EBIKE_MANAGE,
    ADMIN_DATABASE_USER_INFO,
    ADMIN_DATABASE_EBIKE_INFO,
    ADMIN_DATABASE_EBIKE_PASS_IN_OUT,
}
ADMIN_DATABASE_FLAG;

// 定义激活状态
enum
{
    ACTIVE_ADMIN_NULL = 0,
    ACTIVE_ADMIN_BUTTON1,
    ACTIVE_ADMIN_BUTTON2,
    ACTIVE_ADMIN_BUTTON3,
    ACTIVE_ADMIN_BUTTON4,
    ACTIVE_ADMIN_BUTTON5,
    ACTIVE_ADMIN_BUTTON6,
    ACTIVE_ADMIN_BUTTON7,
    ACTIVE_ADMIN_EXIT,
    ACTIVE_ADMIN_FEATURE1,
    ACTIVE_ADMIN_FEATURE2,
    ACTIVE_ADMIN_FEATURE3,
    ACTIVE_ADMIN_FEATURE4,
    ACTIVE_ADMIN_FEATURE5,
    ACTIVE_ADMIN_FEATURE6,
    ACTIVE_ADMIN_FEATURE_SEARCH,
    ACTIVE_ADMIN_FEATURE_UP,
    ACTIVE_ADMIN_FEATURE_DOWN,
    ACTIVE_ADMIN_FEATURE_EXIT,
    ACTIVE_ADMIN_INFO,
} ADMIN_ACTIVE_TAG;

typedef void (*DRAWFUNCTION)(int coord1, int coord2, int coord3, int coord4);
typedef void (*CLEARFUNCTION) (int coord1,int coord2,int coord3,int coord4);

typedef struct {
    int x1, x2, y1, y2;
    int active_tag;
    DRAWFUNCTION drawfunc;
    CLEARFUNCTION clearfunc;
} ADMIN_BUTTONS;

typedef struct {
    char rln[16];
	unsigned long ID;
	char ebike_ID[10];
    char ebike_license[10];
    char location[10];
    int anual_check;
    int violations;
    int apply_time;
	int conduct_time;
    int result;
} EBIKE_INFO;


// 主界面
void main_admin(int *page,unsigned long *ID);
// 车辆信息处理界面
void admin_manage_bike_module(int *page, unsigned long *ID, LINKLIST *LIST, char *file_path, char *list_mode);
// 数据一览界面
void admin_database(int *page, unsigned long *ID, LINKLIST *LIST);
// 管理员信息界面
void admin_info(int *page, unsigned long *ID);


// 绘制画面
void drawgraph_admin_menu(void);
void drawgraph_admin_feature(int page);
void drawgraph_admin_database(void);
void drawgraph_admin_database_user_info(void);
void drawgraph_admin_info(unsigned long ID);

// 按钮状态刷新
void define_admin_buttons(ADMIN_BUTTONS AdminButtons[], int button_counts);
void admin_flush_buttons(int *tag,int button_counts,ADMIN_BUTTONS AdminButtons[]);
void admin_handle_manage_feature_event(LINKLIST *LIST, int *page, char *search_str, unsigned long *id_list,
                                       FILE *fp_EBIKE_INFO_read, int *mode, int selected_id);
void admin_handle_buttons_event(int *page);
void admin_handle_database_event(LINKLIST *LIST, int *flag,int *page, unsigned long *id_list, FILE *fp_EBIKE_INFO_read, char *search_str);

// 列表函数
void admin_list_info(LINKLIST *LIST, const int max, const int interval, unsigned long id_list[], FILE *fp, char *file_type,
                     char *list_mode, int search_mode, int page_change, int is_clear, char *search_str, char *search_needed);
void admin_show_ebike_manage_info(EBIKE_INFO TEMP, const int max, const int interval, int listed_item, char *list_mode, int list_sequence);
void admin_show_user_info(USER_LOGIN_DATA TEMP, const int max, const int interval, int listed_item, int list_sequence);
void admin_show_ebike_info(LINKLIST_USER usrdat, const int max, const int interval, int listed_item, int list_sequence);
int list_ebike_manage_is_valid(EBIKE_INFO TEMP, char *list_mode, char *search_str, char *search_needed, int search_mode);
int list_user_data_is_valid(USER_LOGIN_DATA TEMP, char *search_str, char *search_needed);
int list_ebike_info_is_valid(LINKLIST_USER usrdat, char *search_str, char *search_needed);
void list_show_page_index(unsigned int page_index, unsigned int page_count, const int max, const int interval);
void handle_list_select_line_admin(unsigned long id_list[], unsigned long *selected_id, const int max, const int interval);

// 搜索函数
unsigned long int find_ebike_info(FILE *fp, char *search_str, char *search_needed);

// 其他杂项
void draw_person(int x1,int y1,int x2,int y2);
void clear_person(int x1,int y1,int x2,int y2);
void draw_cues(int x, int y, int null1, int null2);
void clear_cues(int x1, int y1, int x2, int y2);
void draw_rectangle(int x1, int y1, int x2, int y2);
void clear_rectangle(int x1, int y1, int x2, int y2);
void draw_exit(int x1, int y1, int x2, int y2);
void clear_exit(int x1, int y1, int x2, int y2);
void draw_exit_menu(int x1, int y1, int x2, int y2);
void clear_exit_menu(int x1, int y1, int x2, int y2);
void draw_flip_up(int x1, int y1, int x2, int y2);
void clear_flip_up(int x1, int y1, int x2, int y2);
void draw_flip_down(int x1, int y1, int x2, int y2);
void clear_flip_down(int x1, int y1, int x2, int y2);

void admin_pass_failed_anime(int button_x1, int button_y1, int button_x2, int button_y2, int result);
int admin_exitting(int *page);
void AdminswitchPage();

#define STRUCT_LENGTH(Struct) (sizeof(Struct)/sizeof(Struct[0]))

#endif

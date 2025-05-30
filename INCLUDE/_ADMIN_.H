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
#include"DEBUG.H"
#include"LOGIN.H"
#include"LIST.H"
#include"MESSAGE.H"
#include"INPUTHZ.H"
#include"RANDOM.H"

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
#define ADMIN_LIST_DATA_INTERFACE_X1 20
#define ADMIN_LIST_DATA_INTERFACE_Y1 40
#define ADMIN_LIST_DATA_INTERFACE_X2 220
#define ADMIN_LIST_DATA_INTERFACE_Y2 440
#define ADMIN_MODIFY_DATA_INTERFACE_X1 220
#define ADMIN_MODIFY_DATA_INTERFACE_Y1 40
#define ADMIN_MODIFY_DATA_INTERFACE_X2 620
#define ADMIN_MODIFY_DATA_INTERFACE_Y2 440

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

#define ADMIN_MODIFY_DATA_EXIT_X1 20
#define ADMIN_MODIFY_DATA_EXIT_Y1 10
#define ADMIN_MODIFY_DATA_EXIT_X2 40
#define ADMIN_MODIFY_DATA_EXIT_Y2 30

#define ADMIN_MODIFY_DATA_SAVE_X1 600
#define ADMIN_MODIFY_DATA_SAVE_Y1 10
#define ADMIN_MODIFY_DATA_SAVE_X2 620
#define ADMIN_MODIFY_DATA_SAVE_Y2 30

#define ADMIN_MODIFY_DATA_INPUTBAR1_X1 230
#define ADMIN_MODIFY_DATA_INPUTBAR1_Y1 80
#define ADMIN_MODIFY_DATA_INPUTBAR1_X2 530
#define ADMIN_MODIFY_DATA_INPUTBAR1_Y2 110
#define ADMIN_MODIFY_DATA_INPUTBAR2_X1 230
#define ADMIN_MODIFY_DATA_INPUTBAR2_Y1 130
#define ADMIN_MODIFY_DATA_INPUTBAR2_X2 530
#define ADMIN_MODIFY_DATA_INPUTBAR2_Y2 160
#define ADMIN_MODIFY_DATA_INPUTBAR3_X1 230
#define ADMIN_MODIFY_DATA_INPUTBAR3_Y1 180
#define ADMIN_MODIFY_DATA_INPUTBAR3_X2 530
#define ADMIN_MODIFY_DATA_INPUTBAR3_Y2 210
#define ADMIN_MODIFY_DATA_INPUTBAR4_X1 230
#define ADMIN_MODIFY_DATA_INPUTBAR4_Y1 230
#define ADMIN_MODIFY_DATA_INPUTBAR4_X2 530
#define ADMIN_MODIFY_DATA_INPUTBAR4_Y2 260
#define ADMIN_MODIFY_DATA_INPUTBAR5_X1 230
#define ADMIN_MODIFY_DATA_INPUTBAR5_Y1 280
#define ADMIN_MODIFY_DATA_INPUTBAR5_X2 530
#define ADMIN_MODIFY_DATA_INPUTBAR5_Y2 310
#define ADMIN_MODIFY_DATA_INPUTBAR6_X1 230
#define ADMIN_MODIFY_DATA_INPUTBAR6_Y1 330
#define ADMIN_MODIFY_DATA_INPUTBAR6_X2 530
#define ADMIN_MODIFY_DATA_INPUTBAR6_Y2 360
#define ADMIN_MODIFY_DATA_INPUTBAR7_X1 230
#define ADMIN_MODIFY_DATA_INPUTBAR7_Y1 380
#define ADMIN_MODIFY_DATA_INPUTBAR7_X2 530
#define ADMIN_MODIFY_DATA_INPUTBAR7_Y2 410

#define ADMIN_MODIFY_DATA_FREEZE_X1 ADMIN_MODIFY_DATA_INPUTBAR5_X1
#define ADMIN_MODIFY_DATA_FREEZE_Y1 ADMIN_MODIFY_DATA_INPUTBAR5_Y1
#define ADMIN_MODIFY_DATA_FREEZE_X2 ADMIN_MODIFY_DATA_INPUTBAR5_X1 + 80
#define ADMIN_MODIFY_DATA_FREEZE_Y2 ADMIN_MODIFY_DATA_INPUTBAR5_Y2

#define ADMIN_MODIFY_DATA_BAN_X1 ADMIN_MODIFY_DATA_INPUTBAR5_X1 + 100
#define ADMIN_MODIFY_DATA_BAN_Y1 ADMIN_MODIFY_DATA_INPUTBAR5_Y1
#define ADMIN_MODIFY_DATA_BAN_X2 ADMIN_MODIFY_DATA_INPUTBAR5_X1 + 180
#define ADMIN_MODIFY_DATA_BAN_Y2 ADMIN_MODIFY_DATA_INPUTBAR5_Y2

#define ADMIN_MODIFY_DATA_RESTORE_X1 ADMIN_MODIFY_DATA_INPUTBAR5_X1 + 200
#define ADMIN_MODIFY_DATA_RESTORE_Y1 ADMIN_MODIFY_DATA_INPUTBAR5_Y1
#define ADMIN_MODIFY_DATA_RESTORE_X2 ADMIN_MODIFY_DATA_INPUTBAR5_X1 + 280
#define ADMIN_MODIFY_DATA_RESTORE_Y2 ADMIN_MODIFY_DATA_INPUTBAR5_Y2

#define ADMIN_MESSAGE_REPLY_X1 10
#define ADMIN_MESSAGE_REPLY_Y1 100
#define ADMIN_MESSAGE_REPLY_X2 80
#define ADMIN_MESSAGE_REPLY_Y2 130

#define ADMIN_MESSAGE_EXIT_X1 ADMIN_MODIFY_DATA_EXIT_X1
#define ADMIN_MESSAGE_EXIT_Y1 ADMIN_MODIFY_DATA_EXIT_Y1
#define ADMIN_MESSAGE_EXIT_X2 ADMIN_MODIFY_DATA_EXIT_X2
#define ADMIN_MESSAGE_EXIT_Y2 ADMIN_MODIFY_DATA_EXIT_Y2

//定义数据标志
enum
{
    ADMIN_DATABASE_NULL = 0,
    ADMIN_DATABASE_EBIKE_MANAGE,
    ADMIN_DATABASE_USER_INFO,
    ADMIN_DATABASE_EBIKE_INFO,
    ADMIN_DATABASE_EBIKE_PASS_IN_OUT,
};

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
    ACTIVE_ADMIN_MODIFY_EXIT,
    ACTIVE_ADMIN_MODIFY_SAVE,
    ACTIVE_ADMIN_MODIFY_INPUTBAR1,
    ACTIVE_ADMIN_MODIFY_INPUTBAR2,
    ACTIVE_ADMIN_MODIFY_INPUTBAR3,
    ACTIVE_ADMIN_MODIFY_INPUTBAR4,
    ACTIVE_ADMIN_MODIFY_INPUTBAR5,
    ACTIVE_ADMIN_MODIFY_INPUTBAR6,
    ACTIVE_ADMIN_MODIFY_INPUTBAR7,
    ACTIVE_ADMIN_MODIFY_FREEZE,
    ACTIVE_ADMIN_MODIFY_BAN,
    ACTIVE_ADMIN_MODIFY_RESTORE,
    ACTIVE_ADMIN_MESSAGE_REPLY,
    ACTIVE_ADMIN_MESSAGE_EXIT,
};

// 定义车辆进入理由
enum
{
    EBIKE_IN_OUT_NULL = 0,
    EBIKE_IN_OUT_REGISTERED_UNIT_IN,
    EBIKE_IN_OUT_REGISTERED_UNIT_OUT,
    EBIKE_IN_TAKE_OUT,
    EBIKE_OUT_TAKE_OUT,
    EBIKE_IN_VISIT,
    EBIKE_OUT_VISIT,
    EBIKE_IN_OTHER,
    EBIKE_OUT_OTHER,
};

typedef void (*DRAWFUNCTION) (int coord1, int coord2, int coord3, int coord4);
typedef void (*CLEARFUNCTION) (int coord1, int coord2, int coord3, int coord4);

typedef struct _ADMIN_BUTTONS_{
    int x1, x2, y1, y2;
    int active_tag;
    DRAWFUNCTION drawfunc;
    CLEARFUNCTION clearfunc;
} ADMIN_BUTTONS;

typedef struct _EBIKE_INFO_{
    char rln[16];
	unsigned long ID;
	char ebike_ID[10];
    char ebike_license[10];
    char location[10];
    long anual_check;
    int violations;
    long apply_time;
	long conduct_time;
    int result;
} EBIKE_INFO;

typedef struct _EBIKE_IN_OUT_{
    unsigned long apply_id;
    char ebike_id[8];
    char ebike_license[10];
    char location[15];
    long in_time;
    long out_time;
    int comment;
    int result;
} EBIKE_IN_OUT;

typedef struct _MODIFY_EBIKE_DATA_{
    char ebike_id_buffer[7];     // 输入框输入信息储存
    char ebike_license_buffer[9]; // 输入框输入信息储存
    char anual_check_buffer[11];  // 输入框输入信息储存
    char location_buffer[15];  // 输入框输入信息储存
} MODIFY_EBIKE_DATA_BUFFER;


// 主界面
void main_admin(int *page,unsigned long *ID);
// 车辆信息处理界面
void admin_manage_bike_module(int *page, unsigned long *ID, LINKLIST *LIST, char *file_path, char *list_mode);
// 数据一览界面
void admin_database(int *page, unsigned long *ID, LINKLIST *LIST);
void admin_modify_data(LINKLIST *LIST, FILE *fp, char *file_type, unsigned long *user_id);
// 消息中心界面
void admin_message_center(int *page, unsigned long *ID);
// 管理员信息界面
void admin_info(int *page, unsigned long *ID);

// 绘制画面
void drawgraph_admin_menu(void);
void drawgraph_admin_feature(int page);
void drawgraph_admin_database(void);
void drawgraph_admin_database_user_info(void);
void drawgraph_admin_database_ebike_info(void);
void drawgraph_admin_database_ebike_pass_in_out(void);
int drawgraph_admin_modify_data(FILE *fp, LINKLIST *LIST, int flag, unsigned long user_id);
void drawgraph_admin_message_center(void);
void drawgraph_admin_info(unsigned long ID);

// 画面点击事件函数
void admin_handle_manage_feature_event(LINKLIST *LIST, long ID, int *page, char *search_str, unsigned long *id_list,
                                       FILE *fp_EBIKE_INFO_read, int *mode, unsigned long *selected_id);
void admin_handle_buttons_event(int *page);
void admin_handle_database_event(LINKLIST *LIST, int *flag, int *page, unsigned long *id_list,
                                 FILE **fp, char *search_str, char *search_needed, unsigned long *selected_id);
void admin_handle_modify_user_data_event(FILE *fp, unsigned long *user_id, int *isReturn);
void admin_handle_modify_ebike_data_event(LINKLIST *LIST, unsigned long *user_id, int *isReturn);
void admin_handle_message_click_event(FILE *fp, int *page, unsigned long id_list[], unsigned long *selected_id,
                                      char *search_str, char *search_needed);

// 二进制文件数据操作函数
long find_file_info(FILE *fp, char *file_type, char *search_str, char *search_needed);
int modify_user_info(FILE *fp, unsigned long user_id, char *modify_str, char *modify_needed);
void modify_ebike_info(LINKLIST *LIST, unsigned long user_id, char *modify_str, char *modify_needed);

// 判断输入合理性函数
int admin_check_ebike_info(LINKLIST *LIST, MODIFY_EBIKE_DATA_BUFFER temp, unsigned long user_id);
int admin_check_ebike_id(char *ebike_id);
int admin_check_ebike_license(char *ebike_license);
int admin_check_anual_check(char *now, unsigned long prev);

// 其他杂项
void define_admin_buttons(ADMIN_BUTTONS AdminButtons[], int page);
void admin_get_buttons(ADMIN_BUTTONS *AdminButtons, ADMIN_BUTTONS *Examples);
void admin_flush_buttons(int *tag, int button_counts, ADMIN_BUTTONS AdminButtons[]);

void draw_person(int x1, int y1, int x2, int y2);
void clear_person(int x1,int y1,int x2,int y2);
void draw_cues(int x, int y, int null1, int null2);
void clear_cues(int x1, int y1, int x2, int y2);
void draw_accept(int x1,int y1,int x2,int y2);
void clear_accept(int x1,int y1,int x2,int y2);
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

void admin_pass_failed_anime(int button_x1, int button_y1, int button_x2, int button_y2, int result, char *prev_text);
int admin_exitting(int *page);
void AdminswitchPage();

#define STRUCT_LENGTH(Struct) (sizeof(Struct)/sizeof(Struct[0]))

#endif

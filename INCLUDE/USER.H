#ifndef _USER_H_
#define _USER_H_

#include <stdio.h>
#include <graphics.h>
#include <string.h>
#include <conio.h>
#include <DOS.H>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#include"GROCERY.H"
#include"MOUSE.H"
#include"INPUTCH.H"
#include"HZ.H"
#include "LINKLIST.H"
#include "_ADMIN_.H"
#include "QUIZ.H"

//按钮位置
#define USER_BIKE_REGISTER_X1 0
#define USER_BIKE_REGISTER_X2 150
#define USER_BIKE_REGISTER_Y1 60
#define USER_BIKE_REGISTER_Y2 110
#define USER_BIKE_LICENSE_X1 0
#define USER_BIKE_LICENSE_X2 150
#define USER_BIKE_LICENSE_Y1 115
#define USER_BIKE_LICENSE_Y2 165
#define USER_BIKE_ANUAL_X1 0
#define USER_BIKE_ANUAL_X2 150
#define USER_BIKE_ANUAL_Y1 170
#define USER_BIKE_ANUAL_Y2 220
#define USER_BIKE_WROTEOUT_X1 0
#define USER_BIKE_WROTEOUT_X2 150
#define USER_BIKE_WROTEOUT_Y1 225
#define USER_BIKE_WROTEOUT_Y2 275
#define USER_INFO_X1 0
#define USER_INFO_X2 150
#define USER_INFO_Y1 280
#define USER_INFO_Y2 330
#define USER_MESSAGE_X1 0
#define USER_MESSAGE_X2 150
#define USER_MESSAGE_Y1 335
#define USER_MESSAGE_Y2 385
#define USER_DATAGRAPH_X1 0
#define USER_DATAGRAPH_X2 150
#define USER_DATAGRAPH_Y1 390
#define USER_DATAGRAPH_Y2 440
#define USER_BACK_X1 575
#define USER_BACK_X2 635
#define USER_BACK_Y1 10
#define USER_BACK_Y2 50
#define USER_EXIT_X1 10
#define USER_EXIT_X2 50
#define USER_EXIT_Y1 10
#define USER_EXIT_Y2 50

#define USER_BIKE_REGISTER_BUTTON1_X1 280
#define USER_BIKE_REGISTER_BUTTON1_X2 360
#define USER_BIKE_REGISTER_BUTTON1_Y1 420
#define USER_BIKE_REGISTER_BUTTON1_Y2 460
#define USER_BIKE_REGISTER_BUTTON2_X1 410
#define USER_BIKE_REGISTER_BUTTON2_X2 490
#define USER_BIKE_REGISTER_BUTTON2_Y1 420
#define USER_BIKE_REGISTER_BUTTON2_Y2 460

#define USER_BIKE_REGISTER_INPUT1_X1 250
#define USER_BIKE_REGISTER_INPUT1_X2 600
#define USER_BIKE_REGISTER_INPUT1_Y1 160
#define USER_BIKE_REGISTER_INPUT1_Y2 195
#define USER_BIKE_REGISTER_INPUT2_X1 250
#define USER_BIKE_REGISTER_INPUT2_X2 600
#define USER_BIKE_REGISTER_INPUT2_Y1 225
#define USER_BIKE_REGISTER_INPUT2_Y2 260

#define USER_BIKE_LICENSE_BUTTON1_X1 340
#define USER_BIKE_LICENSE_BUTTON1_X2 420
#define USER_BIKE_LICENSE_BUTTON1_Y1 420
#define USER_BIKE_LICENSE_BUTTON1_Y2 455
#define USER_BIKE_LICENSE_BUTTON2_X1 335
#define USER_BIKE_LICENSE_BUTTON2_X2 415
#define USER_BIKE_LICENSE_BUTTON2_Y1 120
#define USER_BIKE_LICENSE_BUTTON2_Y2 150

//选择时间地点的小方块
#define USER_BIKE_LICENSE_BOX1_1_X1 280  
#define USER_BIKE_LICENSE_BOX1_1_X2 295
#define USER_BIKE_LICENSE_BOX1_1_Y1 165
#define USER_BIKE_LICENSE_BOX1_1_Y2 180
#define USER_BIKE_LICENSE_BOX1_2_X1 440
#define USER_BIKE_LICENSE_BOX1_2_X2 455
#define USER_BIKE_LICENSE_BOX1_2_Y1 165
#define USER_BIKE_LICENSE_BOX1_2_Y2 180
#define USER_BIKE_LICENSE_BOX1_3_X1 600
#define USER_BIKE_LICENSE_BOX1_3_X2 615
#define USER_BIKE_LICENSE_BOX1_3_Y1 165
#define USER_BIKE_LICENSE_BOX1_3_Y2 180
#define USER_BIKE_LICENSE_BOX2_1_X1 350
#define USER_BIKE_LICENSE_BOX2_1_X2 365
#define USER_BIKE_LICENSE_BOX2_1_Y1 295
#define USER_BIKE_LICENSE_BOX2_1_Y2 310
#define USER_BIKE_LICENSE_BOX2_2_X1 350
#define USER_BIKE_LICENSE_BOX2_2_X2 365
#define USER_BIKE_LICENSE_BOX2_2_Y1 330
#define USER_BIKE_LICENSE_BOX2_2_Y2 345
#define USER_BIKE_LICENSE_BOX2_3_X1 350
#define USER_BIKE_LICENSE_BOX2_3_X2 365
#define USER_BIKE_LICENSE_BOX2_3_Y1 365
#define USER_BIKE_LICENSE_BOX2_3_Y2 380
#define USER_BIKE_LICENSE_BOX3_1_X1 600
#define USER_BIKE_LICENSE_BOX3_1_X2 615
#define USER_BIKE_LICENSE_BOX3_1_Y1 310
#define USER_BIKE_LICENSE_BOX3_1_Y2 325
#define USER_BIKE_LICENSE_BOX3_2_X1 600
#define USER_BIKE_LICENSE_BOX3_2_X2 615
#define USER_BIKE_LICENSE_BOX3_2_Y1 350
#define USER_BIKE_LICENSE_BOX3_2_Y2 365
#define USER_BIKE_LICENSE_BOX3_3_X1 0
#define USER_BIKE_LICENSE_BOX3_3_X2 0
#define USER_BIKE_LICENSE_BOX3_3_Y1 0
#define USER_BIKE_LICENSE_BOX3_3_Y2 0
#define USER_LICENSE_NOTICE_BUTTON1_X1 220
#define USER_LICENSE_NOTICE_BUTTON1_X2 320
#define USER_LICENSE_NOTICE_BUTTON1_Y1 380
#define USER_LICENSE_NOTICE_BUTTON1_Y2 420
#define USER_LICENSE_NOTICE_BUTTON2_X1 440
#define USER_LICENSE_NOTICE_BUTTON2_X2 540
#define USER_LICENSE_NOTICE_BUTTON2_Y1 380
#define USER_LICENSE_NOTICE_BUTTON2_Y2 420

#define USER_BIKE_WROTEOUT_BUTTON1_X1 260
#define USER_BIKE_WROTEOUT_BUTTON1_X2 340
#define USER_BIKE_WROTEOUT_BUTTON1_Y1 420
#define USER_BIKE_WROTEOUT_BUTTON1_Y2 460
#define USER_BIKE_WROTEOUT_BUTTON2_X1 440
#define USER_BIKE_WROTEOUT_BUTTON2_X2 520
#define USER_BIKE_WROTEOUT_BUTTON2_Y1 420
#define USER_BIKE_WROTEOUT_BUTTON2_Y2 460
#define USER_BIKE_WROTEOUT_INPUT1_X1 250
#define USER_BIKE_WROTEOUT_INPUT1_X2 600
#define USER_BIKE_WROTEOUT_INPUT1_Y1 150
#define USER_BIKE_WROTEOUT_INPUT1_Y2 185
#define USER_BIKE_WROTEOUT_INPUT2_X1 250
#define USER_BIKE_WROTEOUT_INPUT2_X2 600
#define USER_BIKE_WROTEOUT_INPUT2_Y1 220
#define USER_BIKE_WROTEOUT_INPUT2_Y2 255
#define USER_BIKE_WROTEOUT_INPUT3_X1 250
#define USER_BIKE_WROTEOUT_INPUT3_X2 600
#define USER_BIKE_WROTEOUT_INPUT3_Y1 290
#define USER_BIKE_WROTEOUT_INPUT3_Y2 325
#define USER_BIKE_WROTEOUT_INPUT4_X1 250
#define USER_BIKE_WROTEOUT_INPUT4_X2 600
#define USER_BIKE_WROTEOUT_INPUT4_Y1 375
#define USER_BIKE_WROTEOUT_INPUT4_Y2 420

#define USER_QUIZ_BUTTON1_X1 130
#define USER_QUIZ_BUTTON1_X2 200
#define USER_QUIZ_BUTTON1_Y1 435
#define USER_QUIZ_BUTTON1_Y2 470
#define USER_QUIZ_BUTTON2_X1 360
#define USER_QUIZ_BUTTON2_X2 430
#define USER_QUIZ_BUTTON2_Y1 435
#define USER_QUIZ_BUTTON2_Y2 470
#define USER_QUIZ_BUTTON3_X1 530
#define USER_QUIZ_BUTTON3_X2 620
#define USER_QUIZ_BUTTON3_Y1 435
#define USER_QUIZ_BUTTON3_Y2 470
#define USER_QUIZ_EXIT_X1 10
#define USER_QUIZ_EXIT_X2 40
#define USER_QUIZ_EXIT_Y1 10
#define USER_QUIZ_EXIT_Y2 40
#define USER_QUIZ_BACK_X1 560
#define USER_QUIZ_BACK_X2 620
#define USER_QUIZ_BACK_Y1 10
#define USER_QUIZ_BACK_Y2 40
#define USER_QUIZ_RESULT_BUTTON1_X1 220
#define USER_QUIZ_RESULT_BUTTON1_X2 280
#define USER_QUIZ_RESULT_BUTTON1_Y1 390
#define USER_QUIZ_RESULT_BUTTON1_Y2 425
#define USER_QUIZ_RESULT_BUTTON2_X1 380
#define USER_QUIZ_RESULT_BUTTON2_X2 440
#define USER_QUIZ_RESULT_BUTTON2_Y1 390
#define USER_QUIZ_RESULT_BUTTON2_Y2 425

#define QUIZ_PAGE_COUNT 4  //题目页数
#define QUESTION_PER_PAGE 3 //每页3题，最好别改
#define LASTING_TIME 600 //测试时间十分钟

#define INPUT_X1      100    // 输入框左上角X
#define INPUT_Y1      100    // 输入框左上角Y
#define INPUT_X2      400    // 输入框右下角X
#define INPUT_Y2      140    // 输入框右下角Y
#define INPUT_INNER_X (INPUT_X1+1) // 输入区域X起点
#define INPUT_INNER_Y (INPUT_Y1+1) // 输入区域Y起点
#define INPUT_INNER_W (INPUT_X2-INPUT_X1-2) // 输入区域宽度
#define INPUT_INNER_H (INPUT_Y2-INPUT_Y1-2) // 输入区域高度
#define TEXT_OFFSET_X 10     // 文字X偏移量
#define TEXT_OFFSET_Y 20     // 文字Y偏移量


//激活状态
#define ACTIVE_USER_NONE 0
#define ACTIVE_USER_BIKE_REGISTER 1
#define ACTIVE_USER_BIKE_LICENSE 2
#define ACTIVE_USER_BIKE_ANUAL 3
#define ACTIVE_USER_BIKE_WROTEOUT 4
#define ACTIVE_USER_INFO 5
#define ACTIVE_USER_MESSAGE 6
#define ACTIVE_USER_DATAGRAPH 7
#define ACTIVE_USER_BACK 8
#define ACTIVE_USER_EXIT 9

typedef struct {
	int x1, x2, y1, y2;
	int active_tag;
	int page;
}user_button;

typedef struct {
	int x1, x2, y1, y2;
}user_box;
// typedef struct {
// 	char rln[16];
// 	unsigned long ID;
// 	char ebike_ID[10];
// 	char ebike_license[10];
// 	char location[10];
// 	unsigned long apply_time;
// 	unsigned long conduct_time;
// 	int result;
// } EBIKE_INFO;

void user_main(int *page);
void drawgraph_user_main(int *page);
void flushUserMain(int* tag, int button_count, user_button UserButtons[]);
void user_bike_register(int* page, unsigned long* id);
void drawgraph_user_bike_register_new(void);
void drawgraph_user_bike_register_info(unsigned long *id);
void flushUserRegister(int *tag);
int EBIKE_INFO_judge(char *usrn,char *e_bike_id,unsigned long *id);
void anime_user_bike_register_fail(int flag);
int ebike_user_register_judge(unsigned long* ID);
void user_bike_register_getinfo(EBIKE_INFO *user_info,unsigned long *id);

void user_bike_license_notice(int* page, unsigned long* id);
void drawgraph_user_license_notice(unsigned long* id);
void flushUserLicenseNotice(int* tag);

void user_bike_license(int* page, unsigned long* id);
void drawgraph_user_bike_license(unsigned long *id,user_box box[3][3] );
void flushUserLicense(user_box box[3][3],int data[3]);
void handle_click_user_license(user_box box[3][3], int data[3]);
void add_days_to_date(char* date_string, int days_to_add);
void user_license_data_judge(int* data);

void user_quiz(int* page, unsigned long* id);
void drawgraph_quiz_notice();
void drawgraph_user_quiz(int *quiz_page, int page_count);
void flushUserQuiz(int* tag, int *box_tag,user_button UserButtons[],question quiz[],char *answer,int quiz_page,int review_flag);
void drawgraph_quiz_review(int* quiz_page, int page_count,int pass_flag);
void drawgraph_user_quiz_pass(int result[][QUESTION_PER_PAGE], int page_count);
void drawgraph_user_quiz_fail(int result[][QUESTION_PER_PAGE], int page_count);
void FlushQuizResult(int* tag, user_button UserButtons[]);

void user_bike_anual();

void user_bike_wroteout(int *page,unsigned long *id);
void drawgraph_user_bike_wroteout_warning();
void drawgraph_user_wroteout();
void flushUserWroteoutWarning();
void flushUserWroteout(int *tag,user_button UserButtons[]);


void user_info();
void user_message();
void user_datagraph();

int handle_click_main(int button_num, user_button WroteoutButtons[]);
void anime_login_success_user();

#define STRUCT_LENGTH(Struct) (sizeof(Struct)/sizeof(Struct[0]))
#endif
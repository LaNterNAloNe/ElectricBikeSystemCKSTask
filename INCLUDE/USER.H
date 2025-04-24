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
#include "RANDOM.H"

//按钮位置
#define USER_BIKE_REGISTER_X1 0
#define USER_BIKE_REGISTER_X2 150
#define USER_BIKE_REGISTER_Y1 60
#define USER_BIKE_REGISTER_Y2 110
#define USER_BIKE_LICENSE_X1 0
#define USER_BIKE_LICENSE_X2 150
#define USER_BIKE_LICENSE_Y1 115
#define USER_BIKE_LICENSE_Y2 165
#define USER_ANNUAL_X1 0
#define USER_ANNUAL_X2 150
#define USER_ANNUAL_Y1 170
#define USER_ANNUAL_Y2 220
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
#define USER_HELP_X1 0
#define USER_HELP_X2 150
#define USER_HELP_Y1 390
#define USER_HELP_Y2 440
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
#define USER_BIKE_REGISTER_INPUT3_X1 300
#define USER_BIKE_REGISTER_INPUT3_Y1 283
#define USER_BIKE_REGISTER_INPUT3_X2 390
#define USER_BIKE_REGISTER_INPUT3_Y2 318
#define USER_BIKE_REGISTER_INPUT4_X1 520
#define USER_BIKE_REGISTER_INPUT4_Y1 283
#define USER_BIKE_REGISTER_INPUT4_X2 620
#define USER_BIKE_REGISTER_INPUT4_Y2 318
#define USER_BIKE_REGISTER_INPUT5_X1 300
#define USER_BIKE_REGISTER_INPUT5_Y1 345
#define USER_BIKE_REGISTER_INPUT5_X2 390
#define USER_BIKE_REGISTER_INPUT5_Y2 380
#define USER_BIKE_REGISTER_INPUT6_X1 540
#define USER_BIKE_REGISTER_INPUT6_Y1 345
#define USER_BIKE_REGISTER_INPUT6_X2 620
#define USER_BIKE_REGISTER_INPUT6_Y2 380



#define USER_BIKE_LICENSE_BUTTON1_X1 340
#define USER_BIKE_LICENSE_BUTTON1_X2 420
#define USER_BIKE_LICENSE_BUTTON1_Y1 420
#define USER_BIKE_LICENSE_BUTTON1_Y2 460
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
#define USER_BIKE_WROTEOUT_INPUT2_Y1 230
#define USER_BIKE_WROTEOUT_INPUT2_Y2 265
#define USER_BIKE_WROTEOUT_INPUT3_X1 250
#define USER_BIKE_WROTEOUT_INPUT3_X2 600
#define USER_BIKE_WROTEOUT_INPUT3_Y1 310
#define USER_BIKE_WROTEOUT_INPUT3_Y2 345
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

// 账户安全按钮的坐标和标识
#define USER_INFO_ACCOUNT_X1      260
#define USER_INFO_ACCOUNT_X2      320
#define USER_INFO_ACCOUNT_Y1      220
#define USER_INFO_ACCOUNT_Y2      250
#define USER_INFO_BIKEINFO_X1     490
#define USER_INFO_BIKEINFO_X2     550
#define USER_INFO_BIKEINFO_Y1     220
#define USER_INFO_BIKEINFO_Y2     250
#define USER_INFO_BIKEDATA_X1     490
#define USER_INFO_BIKEDATA_X2     550
#define USER_INFO_BIKEDATA_Y1     390
#define USER_INFO_BIKEDATA_Y2     420
#define USER_INFO_PASSWORD_X1     260
#define USER_INFO_PASSWORD_X2     320
#define USER_INFO_PASSWORD_Y1     390
#define USER_INFO_PASSWORD_Y2     420


#define HELP_ANNOUNCE1_X1 240
#define HELP_ANNOUNCE1_X2 300
#define HELP_ANNOUNCE1_Y1 170
#define HELP_ANNOUNCE1_Y2 200
#define HELP_ANNOUNCE2_X1 240
#define HELP_ANNOUNCE2_X2 300
#define HELP_ANNOUNCE2_Y1 290
#define HELP_ANNOUNCE2_Y2 320
#define HELP_ANNOUNCE3_X1 240
#define HELP_ANNOUNCE3_X2 300
#define HELP_ANNOUNCE3_Y1 400
#define HELP_ANNOUNCE3_Y2 430
#define HELP_ANNOUNCE_BACK_X1 350
#define HELP_ANNOUNCE_BACK_X2 400
#define HELP_ANNOUNCE_BACK_Y1 450
#define HELP_ANNOUNCE_BACK_Y2 475
#define HELP_BUTTON1_X1 460
#define HELP_BUTTON1_X2 520
#define HELP_BUTTON1_Y1 170
#define HELP_BUTTON1_Y2 200
#define HELP_BUTTON2_X1 460
#define HELP_BUTTON2_X2 520
#define HELP_BUTTON2_Y1 290
#define HELP_BUTTON2_Y2 320
#define HELP_BUTTON3_X1 460
#define HELP_BUTTON3_X2 520
#define HELP_BUTTON3_Y1 400
#define HELP_BUTTON3_Y2 430

#define HELP_ANNOUNCE 123

#define BIKEINFO_BUTTON1_X1 200
#define BIKEINFO_BUTTON1_X2 260
#define BIKEINFO_BUTTON1_Y1 430
#define BIKEINFO_BUTTON1_Y2 460

#define USER_ANNUAL_BUTTON1_X1 340
#define USER_ANNUAL_BUTTON1_X2 410
#define USER_ANNUAL_BUTTON1_Y1 435
#define USER_ANNUAL_BUTTON1_Y2 460

#define BIKEDATA_BUTTON1_X1 340
#define BIKEDATA_BUTTON1_X2 410
#define BIKEDATA_BUTTON1_Y1 430
#define BIKEDATA_BUTTON1_Y2 460


#define USER_MESSAGE_OUT_BUTTON1_X1 320
#define USER_MESSAGE_OUT_BUTTON1_X2 335
#define USER_MESSAGE_OUT_BUTTON1_Y1 130
#define USER_MESSAGE_OUT_BUTTON1_Y2 145
#define USER_MESSAGE_OUT_BUTTON2_X1 585
#define USER_MESSAGE_OUT_BUTTON2_X2 600
#define USER_MESSAGE_OUT_BUTTON2_Y1 130
#define USER_MESSAGE_OUT_BUTTON2_Y2 145
#define USER_MESSAGE_OUT_BUTTON3_X1 320    
#define USER_MESSAGE_OUT_BUTTON3_X2 335
#define USER_MESSAGE_OUT_BUTTON3_Y1 170
#define USER_MESSAGE_OUT_BUTTON3_Y2 185
#define USER_MESSAGE_OUT_BUTTON4_X1 585    
#define USER_MESSAGE_OUT_BUTTON4_X2 600
#define USER_MESSAGE_OUT_BUTTON4_Y1 170
#define USER_MESSAGE_OUT_BUTTON4_Y2 185
#define USER_MESSAGE_OUT_BUTTON5_X1 175    
#define USER_MESSAGE_OUT_BUTTON5_X2 190
#define USER_MESSAGE_OUT_BUTTON5_Y1 220
#define USER_MESSAGE_OUT_BUTTON5_Y2 235
#define USER_MESSAGE_OUT_BUTTON6_X1 300    
#define USER_MESSAGE_OUT_BUTTON6_X2 360
#define USER_MESSAGE_OUT_BUTTON6_Y1 430
#define USER_MESSAGE_OUT_BUTTON6_Y2 460
#define USER_MESSAGE_OUT_BUTTON7_X1 460    
#define USER_MESSAGE_OUT_BUTTON7_X2 520
#define USER_MESSAGE_OUT_BUTTON7_Y1 430
#define USER_MESSAGE_OUT_BUTTON7_Y2 460
#define USER_MESSAGE_OUT_INPUT1_X1 260
#define USER_MESSAGE_OUT_INPUT1_X2 600
#define USER_MESSAGE_OUT_INPUT1_Y1 215
#define USER_MESSAGE_OUT_INPUT1_Y2 240
#define USER_MESSAGE_OUT_INPUT2_X1 180
#define USER_MESSAGE_OUT_INPUT2_X2 600
#define USER_MESSAGE_OUT_INPUT2_Y1 310
#define USER_MESSAGE_OUT_INPUT2_Y2 405

#define USER_MESSAGE_FEATURE1_X1 130
#define USER_MESSAGE_FEATURE1_Y1 440
#define USER_MESSAGE_FEATURE1_X2 200
#define USER_MESSAGE_FEATURE1_Y2 470
#define USER_MESSAGE_FEATURE6_X1 520
#define USER_MESSAGE_FEATURE6_Y1 440
#define USER_MESSAGE_FEATURE6_X2 590
#define USER_MESSAGE_FEATURE6_Y2 470
#define USER_MESSAGE_FEATURE_EXIT_X1 610
#define USER_MESSAGE_FEATURE_EXIT_Y1 450
#define USER_MESSAGE_FEATURE_EXIT_X2 630
#define USER_MESSAGE_FEATURE_EXIT_Y2 470
#define USER_MESSAGE_FEATURE_UP_X1 220
#define USER_MESSAGE_FEATURE_UP_Y1 355
#define USER_MESSAGE_FEATURE_UP_X2 300
#define USER_MESSAGE_FEATURE_UP_Y2 395
#define USER_MESSAGE_FEATURE_DOWN_X1 380
#define USER_MESSAGE_FEATURE_DOWN_Y1 355
#define USER_MESSAGE_FEATURE_DOWN_X2 460
#define USER_MESSAGE_FEATURE_DOWN_Y2 395
#define USER_MESSAGE_REPLY_X1 10
#define USER_MESSAGE_REPLY_Y1 100
#define USER_MESSAGE_REPLY_X2 80
#define USER_MESSAGE_REPLY_Y2 130
#define USER_MESSAGE_EXIT_X1 20
#define USER_MESSAGE_EXIT_Y1 10
#define USER_MESSAGE_EXIT_X2 40
#define USER_MESSAGE_EXIT_Y2 30

//激活状态
#define ACTIVE_USER_NONE 0
#define ACTIVE_USER_BIKE_REGISTER 1
#define ACTIVE_USER_BIKE_LICENSE 2
#define ACTIVE_USER_ANNUAL 3
#define ACTIVE_USER_BIKE_WROTEOUT 4
#define ACTIVE_USER_INFO 5
#define ACTIVE_USER_INFO_ACCOUNT 51
#define ACTIVE_USER_INFO_BIKEINFO 52
#define ACTIVE_USER_INFO_BIKEDATA 53
#define ACTIVE_USER_INFO_PASSWORD 54
#define ACTIVE_USER_MESSAGE 6
#define ACTIVE_USER_HELP 7
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

typedef struct {
	unsigned long id;
	char color[8];
	char weight[8];
	char length[8];
	char battery[8];
	int is_quiz;
} EBIKE_MOREINFO;

void user_main(int *page);
void drawgraph_user_main(int *page);
void flushUserMain(int* tag, int button_count, user_button UserButtons[]);
void user_bike_register(int* page, unsigned long* id);
void drawgraph_user_bike_register_new(void);
void drawgraph_user_bike_register_info(unsigned long *id);
void flushUserRegister(int *tag);
int EBIKE_INFO_judge(char *usrn,char *e_bike_id,unsigned long *id);
void anime_user_bike_register_fail(int flag);
int user_ebike_register_judge(unsigned long* ID);
void user_bike_register_getinfo(struct _EBIKE_INFO_ *user_info,unsigned long *id);
void write_user_register_moreinfo(unsigned long *id,char* color, char* length, char* battery, char* weight);
int user_get_ebike_moreinfo(EBIKE_MOREINFO* moreinfo, unsigned long* id);

void user_bike_license_notice(int* page, unsigned long* id);
void drawgraph_user_license_notice(unsigned long* id);
void flushUserLicenseNotice(int* tag);

void user_bike_license(int* page, unsigned long* id);
void drawgraph_user_bike_license(unsigned long *id,user_box box[3][3] );
void flushUserLicense(user_box box[3][3],int data[3]);
void handle_click_user_license(user_box box[3][3], int data[3]);
void add_days_to_date(char* date_string, int days_to_add);
int user_license_data_judge(int* data,unsigned long *id);
int ebike_license_judge(unsigned long* id);

void user_quiz(int* page, unsigned long* id);
void drawgraph_quiz_notice();
void drawgraph_user_quiz(int *quiz_page, int page_count);
void flushUserQuiz(int* tag, int *box_tag,user_button UserButtons[],question quiz[],char *answer,int quiz_page,int review_flag);
void drawgraph_quiz_review(int* quiz_page, int page_count,int pass_flag);
void drawgraph_user_quiz_pass(int result[][QUESTION_PER_PAGE], int page_count);
void drawgraph_user_quiz_fail(int result[][QUESTION_PER_PAGE], int page_count);
void FlushQuizResult(int* tag, user_button UserButtons[]);
void write_quiz_result_to_file(unsigned long* id);
int quiz_judge(unsigned long* id);


void user_annual(int* page, unsigned long* id);
void drawgraph_user_bike_annual(int flag);
void user_annual_write(unsigned long* id);
int ebike_annual_judge(unsigned long* id);

void user_help(int* page, unsigned long* id);
void drawgraph_user_help();
void FlushUserHelp(int* tag, int button_count, user_button UserButtons[]);
int handle_click_user_help(int button_num, user_button UserButtons[]);
void drawgraph_user_help_announce(int announce);

void user_bike_wroteout(int *page,unsigned long *id);
void drawgraph_user_bike_wroteout_warning();
void drawgraph_user_wroteout();
void flushUserWroteoutWarning();
void flushUserWroteout(int *tag,user_button UserButtons[]);
int wroteout_info_judge(char* usrn, char* e_bike_id, char* password, unsigned long* id);
void wroteout_delete_data(unsigned long* id);
void draw_user_wroteout_fail(int wroteout_flag);

void user_info(int* page, unsigned long* id);
void flushUserInfo(int* tag, int button_count, user_button UserButtons[]);
void drawgraph_user_info();
int handle_click_info(int button_num, user_button UserButtons[]);

void user_bikeinfo(int* page, unsigned long* id);
void handle_button_and_hzinput(char* new_text, char* old_text, int* button_state, int* hz_input_len, int x, int y, int len,int *tick);
void handle_button_and_chinput(char* new_text, char* old_text, int* button_state, int max_input, int x, int y, int len, int* tick);
void flushChangeButton(int *tag_main,int* tag, int pos_xy[][2], int len, int count,int button_state[]);
void drawgraph_user_bike_moreinfo(unsigned long* id,int pos_xy[][2],int count,int len);
void change_user_info_moreinfo(char input_text[][10], int state[], unsigned long id);

void user_bikedata(int* page, unsigned long* id);
void drawgraph_user_bikedata(unsigned long* id);

void user_info_password(int* page, int* id);
void drawgraph_user_password();
int user_password_change(unsigned long* id, char* old_password, char* new_password);

void user_message(int *page ,unsigned long *id);
void drawgraph_user_message_center();
void drawgraph_user_main_message();
void user_handle_message_click_event(FILE* fp, int* page, unsigned long id_list[], unsigned long* selected_id,char* search_str, char* search_needed);
//void define_user_message_buttons(struct _ADMIN_BUTTONS_ AdminButtons[], int page);


void user_message_out(int* page, unsigned long* id);
void drawgraph_user_message_out(user_button* UserButtons);
void flushMessageOut(int* change_tag, user_button *UserButtons, int button_count);
void handle_message_out_click(user_button* UserButtons,int *topic);
void user_message_send( int topic, char* topic_text, char* content_text, unsigned long* id);

int handle_click_main(int button_num, user_button WroteoutButtons[]);
void anime_login_success_user(int x1,int y1,int x2,int y2);

#define STRUCT_LENGTH(Struct) (sizeof(Struct)/sizeof(Struct[0]))
#endif
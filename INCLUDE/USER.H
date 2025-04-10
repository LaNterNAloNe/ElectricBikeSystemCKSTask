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

//��ťλ��
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
#define USER_BIKE_REGISTER_INPUT3_X1 250
#define USER_BIKE_REGISTER_INPUT3_X2 600
#define USER_BIKE_REGISTER_INPUT3_Y1 160
#define USER_BIKE_REGISTER_INPUT3_Y2 195
#define USER_BIKE_REGISTER_INPUT4_X1 250
#define USER_BIKE_REGISTER_INPUT4_X2 600
#define USER_BIKE_REGISTER_INPUT4_Y1 160
#define USER_BIKE_REGISTER_INPUT4_Y2 195
#define USER_BIKE_REGISTER_INPUT5_X1 250
#define USER_BIKE_REGISTER_INPUT5_X2 600
#define USER_BIKE_REGISTER_INPUT5_Y1 160
#define USER_BIKE_REGISTER_INPUT5_Y2 195

//����״̬
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
int ebike_user_judge(unsigned long* ID);
void user_bike_register_getinfo(EBIKE_INFO *user_info,unsigned long *id);

void user_bike_license(int* page, unsigned long* id);
void drawgraph_user_bike_license();


void user_bike_anual();
void user_bike_wroteout();
void user_info();
void user_message();
void user_datagraph();
int handle_click_main(int button_num, user_button UserButtons[]);
void anime_login_success_user();

#define STRUCT_LENGTH(Struct) (sizeof(Struct)/sizeof(Struct[0]))
#endif
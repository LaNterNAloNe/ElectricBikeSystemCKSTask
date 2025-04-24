#ifndef GROCERY_H
#define GROCERY_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <graphics.h>
#include "MOUSE.H"


#define TEST -1
#define EXIT 0
#define LOGIN 1
#define LOGIN_ADMIN 2
#define REGISTER 3
#define REGISTER_ID_INPUT 4
 

#define MAIN_USER 10
#define USER_BIKE_REGISTER 11
#define USER_BIKE_LICENSE_NOTICE 120
#define USER_BIKE_LICENSE 121
#define USER_ANNUAL 13
#define USER_BIKE_WROTEOUT 14
#define USER_INFO 15
#define USER_INFO_ACCOUNT 151
#define USER_INFO_BIKEINFO 152
#define USER_INFO_BIKEDATA 153
#define USER_INFO_PASSWORD 154
#define USER_MESSAGE 161
#define USER_MESSAGE_OUT 162
#define USER_HELP 17
#define USER_QUIZ 18

#define MAIN_ADMIN 20
#define ADMIN_BIKE_REGISTER 21
#define ADMIN_BIKE_LICENSE 22
#define ADMIN_BIKE_ANUAL 23
#define ADMIN_BIKE_BROKEN 24
#define ADMIN_BIKE_VIOLATION 25
#define ADMIN_INFO 26
#define ADMIN_MESSAGE 27
#define ADMIN_DATABASE 28
#define ADMIN_MODIFY_DATA_USER_INFO 29
#define ADMIN_MODIFY_DATA_EBIKE_INFO 210
#define ADMIN_MODIFY_DATA_EBIKE_PASS_IN_OUT 211
#define ADMIN_MESSAGE_DISPLAY 212
#define ADMIN_MESSAGE_REPLY 213

//宏定义自定义颜色盘
#define MY_LIGHTBLUE 0
#define MY_LIGHTGRAY 1
#define MY_BLACK 2
#define MY_YELLOW 3
#define MY_RED 4
#define MY_WHITE 5
#define MY_GREEN 6
#define MY_CREAM 7
#define USER_DEFINED_COLOR 15

//定义用户状态
#define ACTIVE '0'
#define FROZEN '1'
#define BANNED '2'
//定义车辆状态
#define ACTIVE '0'
#define BROKEN '1'

//定义处理情况
#define PASSED 1
#define FAILED 0
#define PENDING -1

//定义调试模式
#define debug_mode 1

unsigned long get_approx_time(char *time_buffer);
unsigned long get_exact_time(char *time_buffer);

void initcolorpalette();
void drawExittingProgram(int err);

long constrain_int(long input, long min, long max);

void reset_file();

#endif



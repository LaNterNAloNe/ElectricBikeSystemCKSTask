#ifndef GROCERY_H
#define GROCERY_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <graphics.h>
#include "MOUSE.H"

/* 数字键（取低字节ASCII码） */
#define NUM0 0x30 // '0'
#define NUM1 0x31 // '1'
#define NUM2 0x32 // '2'
#define NUM3 0x33 // '3'
#define NUM4 0x34 // '4'
#define NUM5 0x35 // '5'
#define NUM6 0x36 // '6'
#define NUM7 0x37 // '7'
#define NUM8 0x38 // '8'
#define NUM9 0x39 // '9'

/* 功能键（无标准ASCII，展示扫描码） */
#define F1 0x3B
#define F2 0x3C
#define F3 0x3D
#define F4 0x3E
#define F5 0x3F
#define F6 0x40
#define F7 0x41
#define F8 0x42
#define F9 0x43
#define F10 0x44
#define F11 0x57
#define F12 0x58

/* 符号与控制键 */
#define TILDE 0x60     // '`'
#define TAB 0x09       // '\t'
#define SPACE 0x20     // ' '
#define ENTER 0x0D     // '\r'
#define ESCAPE 0x1B    // ESC
#define BACKSPACE 0x08 // '\b'
#define BACKSLASH 0x5C // '\'

/* 方向键（无ASCII，保留原十进制值） */
#define UP 0x4800 // 上箭头（↑）
#define DOWN 0x5000 // 下箭头（↓）
#define LEFT 0x4B00     // 左箭头（←）
#define RIGHT 0x4D00    // 右箭头（→）

/* 控制键（无ASCII，展示扫描码） */
#define CAPSLOCK 0x3A
#define SHIFT 0x2A
#define CTRL 0x1D
#define ALT 0x38

/* 数字区扩展键（取低字节ASCII） */
#define ZERO 0x30  // '0'
#define ONE 0x31   // '1'
#define TWO 0x32   // '2'
#define THREE 0x33 // '3'
#define FOUR 0x34  // '4'
#define FIVE 0x35  // '5'
#define SIX 0x36   // '6'
#define SEVEN 0x37 // '7'
#define EIGHT 0x38 // '8'
#define NINE 0x39  // '9'




#define TEST -1
#define EXIT 0
#define LOGIN 1
#define LOGIN_ADMIN 2
#define REGISTER 3
#define REGISTER_ID_INPUT 4

#define MAIN_USER 10
#define USER_BIKE_REGISTER 11
#define USER_BIKE_LICENSE 12
#define USER_BIKE_ANUAL 13
#define USER_BIKE_WROTEOUT 14
#define USER_INFO 15
#define USER_MESSAGE 16
#define USER_DATAGRAPH 17

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

//宏定义自定义颜色盘
#define MY_LIGHTBLUE 0
#define MY_LIGHTGRAY 1
#define MY_BLACK 2
#define MY_YELLOW 3
#define MY_RED 4
#define MY_WHITE 5
#define MY_GREEN 6
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

//定义列表顺序
#define ASCENDING 1
#define DESCENDING 0
//定义列表模式
#define LIST_PENDING 0
#define LIST_FINISHED 1
//定义清理列表参数
#define LIST_CLEAR 1
#define LIST_CLEAR_CONTINUE 2
#define LIST_FLUSH 3
#define LIST_NO_CLEAR 0
//定义列表翻页参数
#define LIST_PAGEDOWN 1
#define LIST_PAGEUP -1
#define LIST_STAY 0
// 列表参数
#define LIST_INTERVAL 30
#define LIST_LIMIT 8

//输入框
#define INPUTBAR_NO_CLEAR 0
#define INPUTBAR_CLEAR 1
#define INPUTBAR_CLEAR_CONTINUE 2

//定义调试模式
#define debug_mode 1

unsigned long get_approx_time(char *time_buffer);
unsigned long get_exact_time(char *time_buffer);

void initcolorpalette();
void drawExittingProgram(int err);

#endif



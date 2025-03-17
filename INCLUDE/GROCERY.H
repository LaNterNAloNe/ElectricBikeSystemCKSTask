#ifndef GROCERY_H
#define GROCERY_H

#define NUM0 0x5230
#define NUM1 0x4f31
#define NUM2 0x5032
#define NUM3 0x5133
#define NUM4 0x4134
#define NUM5 0x4c35
#define NUM6 0x4d36
#define NUM7 0x4737
#define NUM8 0x4838
#define NUM9 0x4939
#define F1 0x3b
#define F2 0x3c
#define F3 0x3d
#define F4 0x3e
#define F5 0x3f
#define F6 0x40
#define F7 0x41
#define F8 0x42
#define F9 0x43
#define F10 0x44
#define F11 0x57
#define F12 0x58
#define TILDE 0x29
#define TAB 0x0F
#define BACKSLASH 0x2B
#define ENTER 0x1c0d
#define BACK 0x0e08
#define ESC 0x011b
#define KEYBOARD_RIGHT 185
#define KEYBOARD_LEFT 186
#define KEYBOARD_UP 183
#define KEYBOARD_DOWN 184
#define ONE 0x0231
#define TWO 0x0332
#define THREE 0x0433
#define FOUR 0x0534
#define FIVE 0x0635
#define SIX 0x0736
#define SEVEN 0x0837
#define EIGHT 0x0938
#define NINE 0x0a39
#define ZERO 0x0b30


//定义page各个状态
#define TEST -1
#define EXIT 0
#define LOGIN 1
#define LOGIN_ADMIN 2
#define REGISTER 3

#define MAIN_USER 10
#define USER_BIKE_REGISTER 11
#define USER_BIKE_LICENSE 12
#define USER_BIKE_ANUAL_AND_WROTEOUT 13
#define USER_INFO 14
#define USER_MESSAGE 15
#define USER_DATAGRAPH 16

#define MAIN_ADMIN 20
#define ADMIN_BIKE_REGISTER 21
#define ADMIN_BIKE_LICENSE 22
#define ADMIN_BIKE_ANUAL_AND_WROTEOUT 23
#define ADMIN_BIKE_PENALIZE 24
#define ADMIN_INFO 25
#define ADMIN_MESSAGE 26
#define ADMIN_DATABASE 27

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

#define ACTIVE '0'
#define BROKEN '1'

#define debug_mode 0


#endif



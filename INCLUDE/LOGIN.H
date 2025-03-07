#ifndef LOGIN_H
#define LOGIN_H

#include <graphics.h>
#include <string.h>
#include <conio.h>
#include <DOS.H>
#include"KEYINPUT.H"
#include"MOUSE.H"
#define MAX_INPUT_LEN 20
#define TIMER_FREQ 1193180L // 8253 PIT频率 

typedef struct {
	int x1, y1, x2, y2;    // 输入框坐标
	char text[MAX_INPUT_LEN]; // 输入内容
	char placeholder[20];        // 提示文字字段 
	int cursor_pos;         // 光标位置
	int is_active;          // 是否激活状态
	unsigned long last_blink;    // 光标计时器 
} InputBox;

void login(int *page);
void draw_login_graph(void);
void draw_input_box(InputBox *box);
void handle_input(InputBox *box, int key);
int validate_input(InputBox *box);
unsigned long GetTickCount(void);


#endif
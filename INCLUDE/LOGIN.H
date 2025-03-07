#ifndef LOGIN_H
#define LOGIN_H

#include <graphics.h>
#include <string.h>
#include <conio.h>
#include"KEYINPUT.H"
#define MAX_INPUT_LEN 20

typedef struct {
	int x1, y1, x2, y2;    // 输入框坐标
	char text[MAX_INPUT_LEN]; // 输入内容
	int cursor_pos;         // 光标位置
	int is_active;          // 是否激活状态
} InputBox;

void login(int *page);
void draw_input_box(InputBox *box);
void handle_input(InputBox *box, int key);

#endif
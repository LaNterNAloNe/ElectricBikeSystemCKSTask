#ifndef _QUIZ_H_
#define _QUIZ_H_

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
#include"HZ.H"


#define LINE_HEIGHT      35     /* 行高（题干与选项间距） */
#define OPTION_SPACING   240    /* 选项之间的水平间距 */
#define OPTION_TEXT_SPACE  65   //选项文本相对坐标
#define OPTION_LETTER_SPACE 40  //选项字母相对坐标
#define box_size 15             //选项框大小
#define box_a_x 0               //各选项框相对坐标
#define box_a_y 1+LINE_HEIGHT
#define box_b_x box_a_x+OPTION_SPACING
#define box_b_y box_a_y
#define box_c_x box_a_x
#define box_c_y box_a_y+LINE_HEIGHT
#define box_d_x box_b_x
#define box_d_y box_b_y+LINE_HEIGHT

typedef struct {
    char main_text[60];
    char options[4][30];
    char correctAnswer;
    int id;
    int x,y;
}question;

//void add_question_to_file(question* questions_to_add, int question_count);
void generate_quiz(question* quiz, int question_count, int(*question_position_xy)[2]);//生成题目（包含位置）
void handle_click_quiz(question* quiz, char* answer, int question_count);//处理点击答题
void draw_quiz(question quiz[], int question_count);//画出题目
//void print_question_answer(question * quiz,int* answer,int question_count);
#endif
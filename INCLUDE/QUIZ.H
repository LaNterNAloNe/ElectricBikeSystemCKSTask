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
#include <io.h>
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
#define QUIZ_PAGE_COUNT 4  //题目页数
#define QUESTION_PER_PAGE 3 //每页3题
#define PASSING_GRADE 0.75 //75分合格

typedef struct {
    char main_text[50];//题干，最多30字（均为汉字）
    char options[4][30];//四个选项，每个最多15字（均为汉字）
    char correctAnswer;//A,B,C,D之一
    int id;
    int x,y;
}question;

void add_question_to_file(question* questions_to_add, int add_question_count);//向题库添加题目
void delete_data_file();//删除题库
void generate_quiz(question quiz[][QUESTION_PER_PAGE], int page_count, int question_position_xy[][2]);//生成题目（包含位置）
void handle_click_quiz(question* quiz, char* answer, int question_count);//处理点击答题
void draw_quiz(question quiz[], int question_count);//画出题目
int judge_answer(question quiz[][QUESTION_PER_PAGE], char anwser[][QUESTION_PER_PAGE], int result[][QUESTION_PER_PAGE], int page_count);
void printbox(question quiz[], char answer[]);//根据选择答案涂黑选项框（换页时绘制当前页面所选择的选项框）
int FlushQuiz(question quiz[],int question_count,int *box_tag);//检测鼠标是否在选项框内并刷新选项框状态
void init_box_xy(question quiz, int box_xy[4][4]);//根据question的x,y坐标确定四个选项框坐标box_xy[A,B,C,D][x1,y1,x2,y2]
void draw_countdown(int remain_sec, int x, int y);//计时器
void store_data();//题库录入
void draw_quiz_answer(question quiz[], char answer[], int question_count);

#endif
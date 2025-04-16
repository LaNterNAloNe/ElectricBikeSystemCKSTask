#include "QUIZ.H"


void draw_quiz(question quiz[],int question_count) {
    int i,j;  
    char abcd[4][2] = { "A","B","C","D" };
    int box_xy[4][4]; //选项框位置
    for(i=0;i<question_count;i++){
        //初始化选项框坐标
        box_xy[0][0] = quiz[i].x + box_a_x;
        box_xy[0][1] = quiz[i].y + box_a_y;
        box_xy[0][2] = quiz[i].x + box_a_x + box_size;
        box_xy[0][3] = quiz[i].y + box_a_y + box_size;
        box_xy[1][0] = quiz[i].x + box_b_x;
        box_xy[1][1] = quiz[i].y + box_b_y;
        box_xy[1][2] = quiz[i].x + box_b_x + box_size;
        box_xy[1][3] = quiz[i].y + box_b_y + box_size;
        box_xy[2][0] = quiz[i].x + box_c_x;
        box_xy[2][1] = quiz[i].y + box_c_y;
        box_xy[2][2] = quiz[i].x + box_c_x + box_size;
        box_xy[2][3] = quiz[i].y + box_c_y + box_size;
        box_xy[3][0] = quiz[i].x + box_d_x;
        box_xy[3][1] = quiz[i].y + box_d_y;
        box_xy[3][2] = quiz[i].x + box_d_x + box_size;
        box_xy[3][3] = quiz[i].y + box_d_y + box_size;

        setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2); // 默认字体，水平方向，大小2

        /* 绘制题干 */
        puthz(quiz[i].x, quiz[i].y, quiz[i].main_text, 16, 15, MY_BLACK);
        /* 绘制四个选项（两行两列） */
        for (j = 0; j < 4; j++)
        {
            /* 计算选项位置：水平间隔OPTION_SPACING，垂直下移LINE_HEIGHT */
            puthz(
                quiz[i].x + OPTION_TEXT_SPACE + (j % 2) * OPTION_SPACING, /* 选项X坐标 */
                quiz[i].y + (j / 2 + 1) * LINE_HEIGHT,          /* 选项Y坐标 */
                quiz[i].options[j],
                16, 15, MY_BLACK);
            //选项字母
            setcolor(MY_BLACK);
            outtextxy(quiz[i].x + OPTION_LETTER_SPACE + (j % 2) * OPTION_SPACING,
                quiz[i].y + (j / 2 + 1) * LINE_HEIGHT,
                abcd[j]);
            //选项方框
            setcolor(MY_LIGHTGRAY);
            rectangle(box_xy[j][0], box_xy[j][1], box_xy[j][2], box_xy[j][3]);
        }
    }
    
}

void generate_quiz(question* quiz, int question_count, int(*question_position_xy)[2]) {
    /*FILE* fp_QUESTION_read = fopen("C:\\EBS\\DATA\\QUIZ.DAT", "rb");
    if (fp_QUESTION_read == NULL) {
        fclose(fp_QUESTION_read);
        exit(0);
    }
    fseek(fp_QUESTION_read, 0, SEEK_END);
    question_counts = ftell(fp_QUESTION_read) / sizeof(question);//初始操作完成，接下来开始遍历数据

    for (i = 0; i < account_counts; i++) {
        fseek(fp_QUESTION_read, i * sizeof(EBIKE_INFO), SEEK_SET);
        fread(&TEMP, sizeof(EBIKE_INFO), 1, fp_QUESTION_read); //逐个读取，每个用户信息

        if (*id == TEMP.ID) {
            strcpy(user_info->rln, TEMP.rln);			//获取账密和uid
            strcpy(user_info->ebike_ID, TEMP.ebike_ID);
            strcpy(user_info->ebike_license, TEMP.ebike_license);
            strcpy(user_info->location, TEMP.location);
            user_info->apply_time = TEMP.apply_time;
            user_info->anual_check = -1;
            user_info->violations = -1;
            user_info->conduct_time = TEMP.conduct_time;
            user_info->result = TEMP.result;
            if (fclose(fp_QUESTION_read) != 0) getch(), exit(1);
            return;
        }
    }
    if (fclose(fp_QUESTION_read) != 0) getch(), exit(1);
    return;*/
}


void handle_click_quiz(question* quiz, char* answer, int question_count) {
    int i, j;
    int box_xy[4][4]; //选项框位置
    for (i = 0; i < question_count; i++) {//对每一道题目
        //初始化选项框坐标
        box_xy[0][0] = quiz[i].x + box_a_x;
        box_xy[0][1] = quiz[i].y + box_a_y;
        box_xy[0][2] = quiz[i].x + box_a_x + box_size;
        box_xy[0][3] = quiz[i].y + box_a_y + box_size;
        box_xy[1][0] = quiz[i].x + box_b_x;
        box_xy[1][1] = quiz[i].y + box_b_y;
        box_xy[1][2] = quiz[i].x + box_b_x + box_size;
        box_xy[1][3] = quiz[i].y + box_b_y + box_size;
        box_xy[2][0] = quiz[i].x + box_c_x;
        box_xy[2][1] = quiz[i].y + box_c_y;
        box_xy[2][2] = quiz[i].x + box_c_x + box_size;
        box_xy[2][3] = quiz[i].y + box_c_y + box_size;
        box_xy[3][0] = quiz[i].x + box_d_x;
        box_xy[3][1] = quiz[i].y + box_d_y;
        box_xy[3][2] = quiz[i].x + box_d_x + box_size;
        box_xy[3][3] = quiz[i].y + box_d_y + box_size;

        for (j = 0; j < 4; j++) {
            if (mouse_press(box_xy[j][0], box_xy[j][1], box_xy[j][2], box_xy[j][3]) == 1) {
                answer[i] == 'A' + j;//第i道题答案为A/B/C/D
                setfillstyle(SOLID_FILL, MY_WHITE);//去除本题选项框标记
                bar(box_xy[0][0] + 3, box_xy[0][1] + 3, box_xy[0][2] - 3, box_xy[0][3] - 3);
                bar(box_xy[1][0] + 3, box_xy[1][1] + 3, box_xy[1][2] - 3, box_xy[1][3] - 3);
                bar(box_xy[2][0] + 3, box_xy[2][1] + 3, box_xy[2][2] - 3, box_xy[2][3] - 3);
                bar(box_xy[3][0] + 3, box_xy[3][1] + 3, box_xy[3][2] - 3, box_xy[3][3] - 3);
                setfillstyle(SOLID_FILL,MY_BLACK);//涂黑所选选项框
                bar(box_xy[j][0] + 3, box_xy[j][1] + 3, box_xy[j][2] - 3, box_xy[j][3] - 3);
            }
        }


        //之后放到flush函数，应对鼠标刷新导致选项框上色不全
        /*for (j = 0; j < 4; j++) {
            if (answer[i]-'A' == j) {
                setfillstyle(SOLID_FILL, MY_BLACK);
                bar(box_xy[j][0] + 3, box_xy[j][1] + 3, box_xy[j][2] - 3, box_xy[j][3] - 3);
                setfillstyle(MY_WHITE)
            }
        }*/
    }
}

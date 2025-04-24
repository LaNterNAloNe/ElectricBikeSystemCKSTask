#include "QUIZ.H"


void draw_quiz(question quiz[],int question_count) {
    int i,j;  
    char abcd[4][2] = { "A","B","C","D" };
    int box_xy[4][4]; //选项框位置
    for(i=0;i<question_count;i++){
        //初始化选项框坐标
        init_box_xy(quiz[i], box_xy);

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

void generate_quiz(question quiz[][QUESTION_PER_PAGE], int page_count, int question_position_xy[][2]) {
    
    FILE* fp_QUESTION_read;
    question temp_question;
    int num_questions, rand_pos;
    int i, j, k;
    int current_id, is_duplicate;
    int selected_ids[40];
    for (i = 0; i < 40; i++) 
        selected_ids[i] = -1;  // 全部初始化为-1

    // 1. 打开题目文件（二进制读取）
    fp_QUESTION_read = fopen("C:\\EBS\\DATA\\QUIZ.DAT", "rb");
    if (fp_QUESTION_read == NULL) {
        fclose(fp_QUESTION_read);
        exit(0);
    }

    // 2. 计算文件中的题目总数
    fseek(fp_QUESTION_read, 0, SEEK_END);          // 移动文件指针到末尾
    num_questions = ftell(fp_QUESTION_read)/ sizeof(question);  // 计算题目数量
    rewind(fp_QUESTION_read);                      // 重置文件指针

    // 3. 初始化随机数种子
    srand((unsigned)time(NULL));

    // 4. 填充 quiz[][]
    for (i = 0; i < page_count; i++) {
        for (j = 0; j < QUESTION_PER_PAGE; j++) {
            // 随机选择一个题目
            do {
                rand_pos = rand() % num_questions;
                fseek(fp_QUESTION_read, rand_pos * sizeof(question), SEEK_SET);
                fread(&temp_question, sizeof(question), 1, fp_QUESTION_read);
                current_id = temp_question.id;

                is_duplicate = (current_id == 0);  // 直接跳过id=0的题目
                for (k = 0; k < i * QUESTION_PER_PAGE + j; k++) {
                    if (selected_ids[k] == current_id) {
                        is_duplicate = 1;
                        break;
                    }
                }
            } while (is_duplicate);
            // 记录已选题目ID
            selected_ids[i * QUESTION_PER_PAGE + j] = current_id;

            // 使用 strcpy 复制字符串字段
            strcpy(quiz[i][j].main_text, temp_question.main_text);
            for (k = 0; k < 4; k++) {
                strcpy(quiz[i][j].options[k], temp_question.options[k]);
            }

            // 复制非字符串字段
            quiz[i][j].correctAnswer = temp_question.correctAnswer;
            quiz[i][j].id = temp_question.id;

            // 设置坐标 (x, y)
            quiz[i][j].x = question_position_xy[j][0];
            quiz[i][j].y = question_position_xy[j][1];
        }
    }

    // 5. 关闭文件
    if (fclose(fp_QUESTION_read) != 0) getch(), exit(1);
    return;
 
}

void add_question_to_file(question* questions_to_add, int add_question_count) {
    int file_question_count;
    int i;
    FILE* fp_QUESTION_readndwrite = fopen("C:\\EBS\\DATA\\QUIZ.DAT", "rb+");
    if (fp_QUESTION_readndwrite == NULL) {
        fclose(fp_QUESTION_readndwrite);
        exit(0);
    }

    // 计算文件中已有的问题数量
    fseek(fp_QUESTION_readndwrite, 0, SEEK_END);
    file_question_count=ftell(fp_QUESTION_readndwrite)/ sizeof(question);

    // 设置id（序号）
    for (i= 0; i < add_question_count; i++) 
        questions_to_add[i].id = file_question_count+i+1;


    // 定位到文件末尾准备写入
    fseek(fp_QUESTION_readndwrite, 0, SEEK_END);
    //将信息写入文件
    fwrite(questions_to_add, sizeof(question), add_question_count, fp_QUESTION_readndwrite);  
    if (fclose(fp_QUESTION_readndwrite) != 0) 
        getch(), exit(1);
        return;
}

void delete_data_file() {
    FILE* fp = fopen("C:\\EBS\\DATA\\QUIZ.DAT", "wb");  // "wb" 二进制模式
    if (fp == NULL) {
        printf("Error opening file\n");
        getch();
        exit(1);
    }
    fclose(fp);
}

void handle_click_quiz(question* quiz, char* answer, int question_count) {
    int i, j;
    int box_xy[4][4]; //选项框位置
    for (i = 0; i < question_count; i++) {//对每一道题目
        //初始化选项框坐标
        init_box_xy(quiz[i], box_xy);

        for (j = 0; j < 4; j++) {
            if (mouse_press(box_xy[j][0], box_xy[j][1], box_xy[j][2], box_xy[j][3]) == 1) {
                answer[i] = 'A' + j;//第i道题答案为A/B/C/D
                setfillstyle(SOLID_FILL, MY_WHITE);//去除本题选项框标记
                bar(box_xy[0][0] + 3, box_xy[0][1] + 3, box_xy[0][2] - 3, box_xy[0][3] - 3);
                bar(box_xy[1][0] + 3, box_xy[1][1] + 3, box_xy[1][2] - 3, box_xy[1][3] - 3);
                bar(box_xy[2][0] + 3, box_xy[2][1] + 3, box_xy[2][2] - 3, box_xy[2][3] - 3);
                bar(box_xy[3][0] + 3, box_xy[3][1] + 3, box_xy[3][2] - 3, box_xy[3][3] - 3);
                setfillstyle(SOLID_FILL, MY_BLACK);//涂黑所选选项框
                bar(box_xy[j][0] + 3, box_xy[j][1] + 3, box_xy[j][2] - 3, box_xy[j][3] - 3);
            }
        }
    }
}

int judge_answer(question quiz[][QUESTION_PER_PAGE], char anwser[][QUESTION_PER_PAGE], int result[][QUESTION_PER_PAGE],int page_count) {
    int i, j;
    int correct_num=0;
    float correct_rate;
    for (i = 0; i < page_count; i++) {
        for (j = 0; j < QUESTION_PER_PAGE; j++) {
            if (quiz[i][j].correctAnswer == anwser[i][j]) {
                result[i][j] = 1;
                correct_num++;
            }   
            else
                result[i][j] = 0;
        }
    }
    correct_rate = (float)correct_num / (page_count * QUESTION_PER_PAGE);
    if (correct_rate >= PASSING_GRADE)
        return 1;
    else
		return 0;
}

void printbox(question quiz[], char answer[]) {
    int i, j;
    int box_xy[4][4]; //选项框位置
    for (i = 0; i < 3; i++) {//对每一道题目
       //初始化选项框坐标
        init_box_xy(quiz[i], box_xy);

        for (j = 0; j < 4; j++) {
            if (answer[i] - 'A' == j) {
                setfillstyle(SOLID_FILL, MY_WHITE);
                bar(box_xy[0][0] + 3, box_xy[0][1] + 3, box_xy[0][2] - 3, box_xy[0][3] - 3);
                bar(box_xy[1][0] + 3, box_xy[1][1] + 3, box_xy[1][2] - 3, box_xy[1][3] - 3);
                bar(box_xy[2][0] + 3, box_xy[2][1] + 3, box_xy[2][2] - 3, box_xy[2][3] - 3);
                bar(box_xy[3][0] + 3, box_xy[3][1] + 3, box_xy[3][2] - 3, box_xy[3][3] - 3);
                setfillstyle(SOLID_FILL, MY_BLACK);
                bar(box_xy[j][0] + 3, box_xy[j][1] + 3, box_xy[j][2] - 3, box_xy[j][3] - 3);
            }
        }
    }
}

int FlushQuiz(question quiz[],int question_count,int *box_tag) {
    int i, j;
    int box_xy[4][4]; //选项框位置
    int new_tag = 0;
    int ques_num, option_num;

    for (i = 0; i < question_count; i++) {//对每一道题目
       //初始化选项框坐标
        init_box_xy(quiz[i], box_xy);

        for (j = 0; j < 4; j++) {
            if (MouseX >= box_xy[j][0] && MouseX <= box_xy[j][2] && MouseY >= box_xy[j][1] && MouseY <= box_xy[j][3]) {
                new_tag=10*(i+1)+j;
                break;
            }
        }  
    } 

    if (*box_tag != new_tag) {
        if (*box_tag != 0) {
            ques_num = *box_tag / 10 - 1;
            option_num = *box_tag % 10;
            init_box_xy(quiz[ques_num], box_xy);
            setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
            setcolor(MY_WHITE);
            rectangle(box_xy[option_num][0] - 1, box_xy[option_num][1] - 1, box_xy[option_num][2] + 1, box_xy[option_num][3] + 1);
        }
        *box_tag = new_tag;

        if (new_tag != 0) {
            ques_num = new_tag / 10 - 1;
            option_num = new_tag % 10;
            init_box_xy(quiz[ques_num], box_xy);
            setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
            setcolor(MY_BLACK);
            rectangle(box_xy[option_num][0] - 1, box_xy[option_num][1] - 1, box_xy[option_num][2] + 1, box_xy[option_num][3] + 1);
            MouseS = 1;
            return 1;
        }
        else
            return 0;
    }
}


void init_box_xy(question quiz, int box_xy[4][4]) {
    box_xy[0][0] = quiz.x + box_a_x;
    box_xy[0][1] = quiz.y + box_a_y;
    box_xy[0][2] = quiz.x + box_a_x + box_size;
    box_xy[0][3] = quiz.y + box_a_y + box_size;
    box_xy[1][0] = quiz.x + box_b_x;
    box_xy[1][1] = quiz.y + box_b_y;
    box_xy[1][2] = quiz.x + box_b_x + box_size;
    box_xy[1][3] = quiz.y + box_b_y + box_size;
    box_xy[2][0] = quiz.x + box_c_x;
    box_xy[2][1] = quiz.y + box_c_y;
    box_xy[2][2] = quiz.x + box_c_x + box_size;
    box_xy[2][3] = quiz.y + box_c_y + box_size;
    box_xy[3][0] = quiz.x + box_d_x;
    box_xy[3][1] = quiz.y + box_d_y;
    box_xy[3][2] = quiz.x + box_d_x + box_size;
    box_xy[3][3] = quiz.y + box_d_y + box_size;
}


void draw_countdown(int remain_sec, int x, int y) {
    int minute, sec;
    char text[10];
    minute = remain_sec / 60;
    sec = remain_sec % 60;
    sprintf(text,"%02d:%02d", minute, sec);

    setfillstyle(SOLID_FILL,MY_LIGHTGRAY);
    bar(x, y-20, x + 100, y + 20);

    setcolor(MY_WHITE);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2); // 默认字体，水平方向，大小2
    outtextxy(x, y,text); 
}


void draw_quiz_answer(question quiz[], char answer[],int question_count) {
	int i, j;
	int correct_flag;//判断答案是否正确
	char abcd[4][2] = { "A","B","C","D" };
	int box_xy[4][4]; //选项框位置
	for (i = 0; i < question_count; i++) {
		//初始化选项框坐标
		init_box_xy(quiz[i], box_xy);

		//默认答案正确
		correct_flag = 1;

		setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
		settextstyle(DEFAULT_FONT, HORIZ_DIR, 2); // 默认字体，水平方向，大小2

		/* 绘制题干 */
		puthz(quiz[i].x, quiz[i].y, quiz[i].main_text, 16, 15, MY_BLACK);
		/* 绘制四个选项（两行两列） */
		for (j = 0; j < 4; j++)
		{
			//正确选项
			if (quiz[i].correctAnswer == 'A' + j) {
				puthz(
					quiz[i].x + OPTION_TEXT_SPACE + (j % 2) * OPTION_SPACING, 
					quiz[i].y + (j / 2 + 1) * LINE_HEIGHT,          
					quiz[i].options[j],
					16, 15, LIGHTGREEN);
				//选项字母
				setcolor(LIGHTGREEN);
				outtextxy(quiz[i].x + OPTION_LETTER_SPACE + (j % 2) * OPTION_SPACING,
					quiz[i].y + (j / 2 + 1) * LINE_HEIGHT,
					abcd[j]);
			}
			//被选择的错误选项
			else if (answer[i] == 'A' + j) {
				puthz(
					quiz[i].x + OPTION_TEXT_SPACE + (j % 2) * OPTION_SPACING,
					quiz[i].y + (j / 2 + 1) * LINE_HEIGHT,
					quiz[i].options[j],
					16, 15, MY_RED);
				//选项字母
				setcolor(MY_RED);
				outtextxy(quiz[i].x + OPTION_LETTER_SPACE + (j % 2) * OPTION_SPACING,
					quiz[i].y + (j / 2 + 1) * LINE_HEIGHT,
					abcd[j]);
				//答案错误
				correct_flag = 0;
			}
			//其余选项
			else {
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
			}
		}

		//答错的提示
		if (correct_flag == 0) {
			puthz(quiz[i].x, quiz[i].y + 420, "回答错误！", 24, 20, MY_RED);
		}
	}
}





void store_data() {
	question text[40];  // 扩展数组大小以容纳所有题目
// 题目1
	strcpy(text[0].main_text, "电动车遇到陡坡路段时应如何行驶");
	strcpy(text[0].options[0], "加速快速通过");
	strcpy(text[0].options[1], "减速缓慢行驶");
	strcpy(text[0].options[2], "绕行其他道路");
	strcpy(text[0].options[3], "停车等待协助");
	text[0].correctAnswer = 'B';
	text[0].id = 1;

	// 题目2
	strcpy(text[1].main_text, "学生电动车的通行证有效期如何确定");
	strcpy(text[1].options[0], "按照毕业剩余年限");
	strcpy(text[1].options[1], "固定为三年时间");
	strcpy(text[1].options[2], "固定为五年时间");
	strcpy(text[1].options[3], "长期永久有效");
	text[1].correctAnswer = 'A';
	text[1].id = 2;

	// 题目3
	strcpy(text[2].main_text, "申请校园通行证需通过哪个平台");
	strcpy(text[2].options[0], "智慧华中大系统");
	strcpy(text[2].options[1], "学校官方网站");
	strcpy(text[2].options[2], "微信公众号");
	strcpy(text[2].options[3], "所属二级单位");
	text[2].correctAnswer = 'A';
	text[2].id = 3;

	// 题目4
	strcpy(text[3].main_text, "道路未划非机动车道时应如何行驶");
	strcpy(text[3].options[0], "靠道路左侧行驶");
	strcpy(text[3].options[1], "靠道路右侧行驶");
	strcpy(text[3].options[2], "在道路中间行驶");
	strcpy(text[3].options[3], "随意选择车道");
	text[3].correctAnswer = 'B';
	text[3].id = 4;

	// 题目5
	strcpy(text[4].main_text, "禁止改装车辆的哪个外部结构");
	strcpy(text[4].options[0], "后视镜部件");
	strcpy(text[4].options[1], "车篷或车厢");
	strcpy(text[4].options[2], "车铃装置");
	strcpy(text[4].options[3], "脚踏板部分");
	text[4].correctAnswer = 'B';
	text[4].id = 5;

	// 题目6
	strcpy(text[5].main_text, "校园内电动车最高时速限制为");
	strcpy(text[5].options[0], "十五公里每小时");
	strcpy(text[5].options[1], "二十公里每小时");
	strcpy(text[5].options[2], "二十五公里每小时");
	strcpy(text[5].options[3], "三十公里每小时");
	text[5].correctAnswer = 'A';
	text[5].id = 6;

	// 题目7
	strcpy(text[6].main_text, "电动车转弯时应优先让行什么");
	strcpy(text[6].options[0], "直行车辆和行人");
	strcpy(text[6].options[1], "其他电动车");
	strcpy(text[6].options[2], "机动车辆");
	strcpy(text[6].options[3], "无需特别让行");
	text[6].correctAnswer = 'A';
	text[6].id = 7;

	// 题目8
	strcpy(text[7].main_text, "以下哪项属于禁止改装内容");
	strcpy(text[7].options[0], "车铃装置");
	strcpy(text[7].options[1], "电动机和蓄电池");
	strcpy(text[7].options[2], "刹车系统");
	strcpy(text[7].options[3], "轮胎规格");
	text[7].correctAnswer = 'B';
	text[7].id = 8;

	// 题目9
	strcpy(text[8].main_text, "电动车停放时应遵守的原则为");
	strcpy(text[8].options[0], "随意选择位置");
	strcpy(text[8].options[1], "入位整齐美观");
	strcpy(text[8].options[2], "靠近入口停放");
	strcpy(text[8].options[3], "避开监控区域");
	text[8].correctAnswer = 'B';
	text[8].id = 9;

	// 题目10
	strcpy(text[9].main_text, "电动车禁止停放的位置包括");
	strcpy(text[9].options[0], "消防通道区域");
	strcpy(text[9].options[1], "专用停车区域");
	strcpy(text[9].options[2], "充电桩旁边");
	strcpy(text[9].options[3], "树荫下方");
	text[9].correctAnswer = 'A';
	text[9].id = 10;

	// 题目11
	strcpy(text[10].main_text, "通行证损坏后，正确的处理方式应为");
	strcpy(text[10].options[0], "继续凑合使用");
	strcpy(text[10].options[1], "申请更换新证");
	strcpy(text[10].options[2], "自行修补处理");
	strcpy(text[10].options[3], "无需任何处理");
	text[10].correctAnswer = 'B';
	text[10].id = 11;

	// 题目12
	strcpy(text[11].main_text, "对于长期不使用的电动车，处理方式应为");
	strcpy(text[11].options[0], "申请注销通行证");
	strcpy(text[11].options[1], "继续停放校园");
	strcpy(text[11].options[2], "转让给他人");
	strcpy(text[11].options[3], "随意丢弃处理");
	text[11].correctAnswer = 'A';
	text[11].id = 12;

	// 题目13
	strcpy(text[12].main_text, "私拉电线充电的首次处罚是");
	strcpy(text[12].options[0], "移交警方处理");
	strcpy(text[12].options[1], "给予口头警告");
	strcpy(text[12].options[2], "锁车并拖移");
	strcpy(text[12].options[3], "注销通行证");
	text[12].correctAnswer = 'B';
	text[12].id = 13;

	// 题目14
	strcpy(text[13].main_text, "多次违规充电的严重后果是");
	strcpy(text[13].options[0], "口头批评教育");
	strcpy(text[13].options[1], "锁车并拖移");
	strcpy(text[13].options[2], "注销通行证");
	strcpy(text[13].options[3], "移交警方处理");
	text[13].correctAnswer = 'C';
	text[13].id = 14;

	// 题目15
	strcpy(text[14].main_text, "酒后驾驶电动车的处理方式为");
	strcpy(text[14].options[0], "批评教育处理");
	strcpy(text[14].options[1], "锁车并拖移");
	strcpy(text[14].options[2], "注销通行证");
	strcpy(text[14].options[3], "移交警方处理");
	text[14].correctAnswer = 'D';
	text[14].id = 15;

	// 题目16
	strcpy(text[15].main_text, "电动车正确的充电位置为");
	strcpy(text[15].options[0], "宿舍内的插座");
	strcpy(text[15].options[1], "专用充电桩");
	strcpy(text[15].options[2], "楼道内的插座");
	strcpy(text[15].options[3], "木质栈道或地板上");
	text[15].correctAnswer = 'B';
	text[15].id = 16;

	// 题目17
	strcpy(text[16].main_text, "以下属于电动车违规营运的行为是");
	strcpy(text[16].options[0], "载客并收取费用");
	strcpy(text[16].options[1], "进行快递配送服务");
	strcpy(text[16].options[2], "个人通勤使用");
	strcpy(text[16].options[3], "接送家人朋友");
	text[16].correctAnswer = 'A';
	text[16].id = 17;

	// 题目18
	strcpy(text[17].main_text, "我校电动车通行证是否可以转让");
	strcpy(text[17].options[0], "可以自由转让");
	strcpy(text[17].options[1], "可私下交易转让");
	strcpy(text[17].options[2], "严格禁止转让");
	strcpy(text[17].options[3], "仅限亲属转让");
	text[17].correctAnswer = 'C';
	text[17].id = 18;

	// 题目19
	strcpy(text[18].main_text, "对未悬挂通行证的电动车的处理为");
	strcpy(text[18].options[0], "禁止进入校园");
	strcpy(text[18].options[1], "罚款处理");
	strcpy(text[18].options[2], "扣押车辆");
	strcpy(text[18].options[3], "吊销执照");
	text[18].correctAnswer = 'A';
	text[18].id = 19;

	// 题目20
	strcpy(text[19].main_text, "下列可能导致电动车被暂扣的情况为");
	strcpy(text[19].options[0], "未悬挂校园车牌");
	strcpy(text[19].options[1], "后视镜有损坏");
	strcpy(text[19].options[2], "车灯亮度不足");
	strcpy(text[19].options[3], "轮胎出现磨损");
	text[19].correctAnswer = 'A';
	text[19].id = 20;

	// 题目21
	strcpy(text[20].main_text, "电动车充电时应避免的操作有");
	strcpy(text[20].options[0], "覆盖物品影响散热");
	strcpy(text[20].options[1], "使用原装充电器");
	strcpy(text[20].options[2], "保持通风环境");
	strcpy(text[20].options[3], "充满后及时断电");
	text[20].correctAnswer = 'A';
	text[20].id = 21;

	// 题目22
	strcpy(text[21].main_text, "电动车在夜间行驶时必须开启");
	strcpy(text[21].options[0], "转向指示灯");
	strcpy(text[21].options[1], "前照明大灯");
	strcpy(text[21].options[2], "危险警示灯");
	strcpy(text[21].options[3], "无需开启车灯");
	text[21].correctAnswer = 'B';
	text[21].id = 22;

	// 题目23
	strcpy(text[22].main_text, "长期不用的电动车电池应怎样保养");
	strcpy(text[22].options[0], "每三天充电");
	strcpy(text[22].options[1], "每十五天充电");
	strcpy(text[22].options[2], "每六十天充电");
	strcpy(text[22].options[3], "每半年充电");
	text[22].correctAnswer = 'B';
	text[22].id = 23;

	// 题目24
	strcpy(text[23].main_text, "禁止充电的危险区域包括");
	strcpy(text[23].options[0], "专用充电桩区");
	strcpy(text[23].options[1], "楼梯间内");
	strcpy(text[23].options[2], "停车场内");
	strcpy(text[23].options[3], "充电车棚内");
	text[23].correctAnswer = 'B';
	text[23].id = 24;

	// 题目25
	strcpy(text[24].main_text, "电动车通过人行横道时应");
	strcpy(text[24].options[0], "加速快速通过");
	strcpy(text[24].options[1], "停车礼让行人");
	strcpy(text[24].options[2], "鸣笛警示行人");
	strcpy(text[24].options[3], "绕行避开行人");
	text[24].correctAnswer = 'B';
	text[24].id = 25;

	// 题目26
	strcpy(text[25].main_text, "电动车合理充电时长建议为");
	strcpy(text[25].options[0], "不超过三小时");
	strcpy(text[25].options[1], "不超过八小时");
	strcpy(text[25].options[2], "不超过十二小时");
	strcpy(text[25].options[3], "不超过一整天");
	text[25].correctAnswer = 'B';
	text[25].id = 26;

	// 题目27
	strcpy(text[26].main_text, "保护电动车电池应避免下列哪种情况");
	strcpy(text[26].options[0], "频繁充电行为");
	strcpy(text[26].options[1], "大电流放电");
	strcpy(text[26].options[2], "定期检查维护");
	strcpy(text[26].options[3], "使用原装配件");
	text[26].correctAnswer = 'B';
	text[26].id = 27;

	// 题目28
	strcpy(text[27].main_text, "当无机动车专用车道时，电动车的行驶规则为");
	strcpy(text[27].options[0], "靠道路左侧");
	strcpy(text[27].options[1], "靠道路右侧");
	strcpy(text[27].options[2], "在道路中间");
	strcpy(text[27].options[3], "随意选择位置");
	text[27].correctAnswer = 'B';
	text[27].id = 28;

	// 题目29
	strcpy(text[28].main_text, "电动车电池亏电存放的主要危害为");
	strcpy(text[28].options[0], "容量会增大");
	strcpy(text[28].options[1], "导致盐化");
	strcpy(text[28].options[2], "电压会升高");
	strcpy(text[28].options[3], "充电更快");
	text[28].correctAnswer = 'B';
	text[28].id = 29;

	// 题目30
	strcpy(text[29].main_text, "电动车充电器应避免的使用环境有");
	strcpy(text[29].options[0], "干燥的环境");
	strcpy(text[29].options[1], "潮湿的环境");
	strcpy(text[29].options[2], "阴凉避光处");
	strcpy(text[29].options[3], "高温暴晒处");
	text[29].correctAnswer = 'B';
	text[29].id = 30;

	// 题目31
	strcpy(text[30].main_text, "电动车驾驶人应避免下列的哪些行为");
	strcpy(text[30].options[0], "佩戴安全头盔");
	strcpy(text[30].options[1], "手持电话骑行");
	strcpy(text[30].options[2], "遵守交通信号");
	strcpy(text[30].options[3], "礼让行人");
	text[30].correctAnswer = 'B';
	text[30].id = 31;

	// 题目32
	strcpy(text[31].main_text, "电动车电池定期保养的主要内容为");
	strcpy(text[31].options[0], "容量检测维护");
	strcpy(text[31].options[1], "外观清洁");
	strcpy(text[31].options[2], "更换轮胎");
	strcpy(text[31].options[3], "改装电机");
	text[31].correctAnswer = 'A';
	text[31].id = 32;

	// 题目33
	strcpy(text[32].main_text, "下列属于酒驾的违法行为是");
	strcpy(text[32].options[0], "饮用啤酒后驾驶");
	strcpy(text[32].options[1], "服用药后驾驶");
	strcpy(text[32].options[2], "饮用果汁后驾驶");
	strcpy(text[32].options[3], "未饮酒驾驶");
	text[32].correctAnswer = 'A';
	text[32].id = 33;

	// 题目34
	strcpy(text[33].main_text, "下列属于禁止停放电动车的区域的是");
	strcpy(text[33].options[0], "充电桩旁边");
	strcpy(text[33].options[1], "消防通道");
	strcpy(text[33].options[2], "停车位内");
	strcpy(text[33].options[3], "树荫下方");
	text[33].correctAnswer = 'B';
	text[33].id = 34;

	// 题目35
	strcpy(text[34].main_text, "混用充电器的主要危害有");
	strcpy(text[34].options[0], "充电速度加快");
	strcpy(text[34].options[1], "损坏电池");
	strcpy(text[34].options[2], "电压更稳定");
	strcpy(text[34].options[3], "延长寿命");
	text[34].correctAnswer = 'B';
	text[34].id = 35;

	// 题目36
	strcpy(text[35].main_text, "电动车通过人行横道时应");
	strcpy(text[35].options[0], "加速快速通过");
	strcpy(text[35].options[1], "减速礼让行人");
	strcpy(text[35].options[2], "连续鸣笛警示");
	strcpy(text[35].options[3], "穿插行驶通过");
	text[35].correctAnswer = 'B';
	text[35].id = 36;

	// 题目37
	strcpy(text[36].main_text, "下列属于违规载人的情况是");
	strcpy(text[36].options[0], "搭载一名儿童");
	strcpy(text[36].options[1], "搭载两名成人");
	strcpy(text[36].options[2], "搭载残疾人");
	strcpy(text[36].options[3], "搭载宠物");
	text[36].correctAnswer = 'B';
	text[36].id = 37;

	// 题目38
	strcpy(text[37].main_text, "禁止电动车进入的场所包括");
	strcpy(text[37].options[0], "非机动车道");
	strcpy(text[37].options[1], "人行天桥");
	strcpy(text[37].options[2], "地下车库");
	strcpy(text[37].options[3], "专用停车场");
	text[37].correctAnswer = 'B';
	text[37].id = 38;

	// 题目39
	strcpy(text[38].main_text, "遇到交警指挥时应如何做");
	strcpy(text[38].options[0], "按信号灯行驶");
	strcpy(text[38].options[1], "服从交警指挥");
	strcpy(text[38].options[2], "加速通过路口");
	strcpy(text[38].options[3], "靠边停车等待");
	text[38].correctAnswer = 'B';
	text[38].id = 39;

	// 题目40
	strcpy(text[39].main_text, "电动车载人的正确方式是");
	strcpy(text[39].options[0], "搭载一名儿童");
	strcpy(text[39].options[1], "搭载两名成人");
	strcpy(text[39].options[2], "搭载残疾人");
	strcpy(text[39].options[3], "禁止载人");
	text[39].correctAnswer = 'A';
	text[39].id = 40;

	add_question_to_file(text, 40);
}

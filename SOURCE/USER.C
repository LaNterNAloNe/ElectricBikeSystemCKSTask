#include"USER.H"

void user_main(int *page) {
	int tag = 0;
	int click = -1;
	int i;
	int mouse_flag;
	user_button UserButtons[] = {
{USER_BIKE_REGISTER_X1, USER_BIKE_REGISTER_X2,USER_BIKE_REGISTER_Y1, USER_BIKE_REGISTER_Y2,ACTIVE_USER_BIKE_REGISTER,USER_BIKE_REGISTER},
{USER_BIKE_LICENSE_X1, USER_BIKE_LICENSE_X2,USER_BIKE_LICENSE_Y1, USER_BIKE_LICENSE_Y2,ACTIVE_USER_BIKE_LICENSE,USER_BIKE_LICENSE},
{USER_BIKE_ANUAL_X1, USER_BIKE_ANUAL_X2,USER_BIKE_ANUAL_Y1, USER_BIKE_ANUAL_Y2,ACTIVE_USER_BIKE_ANUAL,USER_BIKE_ANUAL},
{USER_BIKE_WROTEOUT_X1, USER_BIKE_WROTEOUT_X2,USER_BIKE_WROTEOUT_Y1, USER_BIKE_WROTEOUT_Y2,ACTIVE_USER_BIKE_WROTEOUT,USER_BIKE_WROTEOUT},
{USER_INFO_X1, USER_INFO_X2,USER_INFO_Y1, USER_INFO_Y2,ACTIVE_USER_INFO,USER_INFO},
{USER_MESSAGE_X1, USER_MESSAGE_X2,USER_MESSAGE_Y1, USER_MESSAGE_Y2,ACTIVE_USER_MESSAGE,USER_MESSAGE},
{USER_DATAGRAPH_X1, USER_DATAGRAPH_X2,USER_DATAGRAPH_Y1, USER_DATAGRAPH_Y2,ACTIVE_USER_DATAGRAPH,USER_DATAGRAPH},
{USER_BACK_X1,USER_BACK_X2,USER_BACK_Y1,USER_BACK_Y2,ACTIVE_USER_BACK,LOGIN},
{USER_EXIT_X1,USER_EXIT_X2,USER_EXIT_Y1,USER_EXIT_Y2,ACTIVE_USER_EXIT,EXIT},
	};
	
	
	clrmous(MouseX, MouseY);
	save_bk_mou(MouseX, MouseY);
	drawgraph_user_main(page);
	

	while (1) {
			user_newmouse_data(&MouseX, &MouseY, &press, &mouse_flag);
			flushUserMain(&tag, STRUCT_LENGTH(UserButtons), UserButtons); // 刷新界面
			click = handle_click_main(STRUCT_LENGTH(UserButtons), UserButtons);
			if (click == LOGIN || click == EXIT||click==USER_BIKE_REGISTER||click==USER_BIKE_LICENSE||click==USER_BIKE_WROTEOUT) {          //其它页面做完后此处会改成click!=-1&&click!=USER_BIKE_REGISTER
				*page = click;
				return;
			}
			user_drawmouse(&MouseX, &MouseY, &press, &mouse_flag);
			delay(25);//
	}
}



void drawgraph_user_main(int *page) {
	char time_string[10] = { '\0' };
	unsigned long time = get_approx_time(time_string);
	
	initcolorpalette();
	setbkcolor(MY_LIGHTBLUE);//主界面
	setfillstyle(1, 0);
	setcolor(MY_LIGHTBLUE);
	bar(0, 0, 640, 480);
	puthz(120, 10, "校园电动车管理系统", 48, 45, MY_WHITE);
	setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
	setcolor(MY_WHITE);
	setfillstyle(1, MY_WHITE);
	bar(150, 60, 640, 480);
	setfillstyle(1, MY_LIGHTGRAY);//侧框
	setcolor(MY_LIGHTGRAY);
	bar(0, 60, 150, 480);
	setcolor(MY_LIGHTGRAY);
	setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
	rectangle(151, 61, 639, 479);

	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2); // 默认字体，水平方向，大小2
	setcolor(MY_WHITE);
	outtextxy(15, 450, time_string);

	setfillstyle(1, MY_YELLOW);//返回登录界面
	setcolor(MY_YELLOW);
	bar(USER_BACK_X1, USER_BACK_Y1, USER_BACK_X2, USER_BACK_Y2);

	setfillstyle(1, MY_RED);//退出
	setcolor(MY_RED);
	bar(USER_EXIT_X1,USER_EXIT_Y1,USER_EXIT_X2,USER_EXIT_Y2);
	setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
	setcolor(MY_WHITE);
	line(USER_EXIT_X1, USER_EXIT_Y1, USER_EXIT_X2-1, USER_EXIT_Y2-1);
	line(USER_EXIT_X2-1, USER_EXIT_Y1, USER_EXIT_X1, USER_EXIT_Y2-1);

	puthz(USER_BIKE_REGISTER_X1 + 15, (USER_BIKE_REGISTER_Y1 + USER_BIKE_REGISTER_Y2) / 2-5, "电动车登记",24,25,MY_WHITE);
	puthz(USER_BIKE_ANUAL_X1+ 15, (USER_BIKE_ANUAL_Y1 + USER_BIKE_ANUAL_Y2) / 2-5, "电动车年审", 24, 25, MY_WHITE);
	puthz(USER_BIKE_LICENSE_X1 + 5, (USER_BIKE_LICENSE_Y1 + USER_BIKE_LICENSE_Y2) / 2-5, "电动车通行证", 24, 22, MY_WHITE);
	puthz(USER_BIKE_WROTEOUT_X1 + 15, (USER_BIKE_WROTEOUT_Y1 + USER_BIKE_WROTEOUT_Y2) / 2 - 5, "电动车报废", 24, 25, MY_WHITE);
	puthz(USER_INFO_X1 + 5, (USER_INFO_Y1 + USER_INFO_Y2) / 2 - 5, "用户信息管理", 24, 22, MY_WHITE);
	puthz(USER_MESSAGE_X1 + 15, (USER_MESSAGE_Y1 + USER_MESSAGE_Y2) / 2 - 5, "信息中心", 24, 25, MY_WHITE);
	puthz(USER_DATAGRAPH_X1+ 15, (USER_DATAGRAPH_Y1 + USER_DATAGRAPH_Y2) / 2 - 5, "数据可视化", 24, 25, MY_WHITE);
	puthz(USER_BACK_X1 + 5, (USER_BACK_Y1 + USER_BACK_Y2) / 2 - 10, "返回", 24, 25, MY_WHITE);

	switch (*page) {
		case USER_BIKE_ANUAL:
			setcolor(MY_WHITE);
			setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
			setfillstyle(1, MY_WHITE);
			bar(USER_BIKE_ANUAL_X1, USER_BIKE_ANUAL_Y1, USER_BIKE_ANUAL_X2, USER_BIKE_ANUAL_Y2);
			puthz(USER_BIKE_ANUAL_X1 + 15, (USER_BIKE_ANUAL_Y1 + USER_BIKE_ANUAL_Y2) / 2 - 5, "电动车年审", 24, 25, MY_BLACK);
			break;
		case USER_BIKE_LICENSE:
			setcolor(MY_WHITE);
			setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
			setfillstyle(1, MY_WHITE);
			bar(USER_BIKE_LICENSE_X1, USER_BIKE_LICENSE_Y1, USER_BIKE_LICENSE_X2, USER_BIKE_LICENSE_Y2);
			puthz(USER_BIKE_LICENSE_X1 + 5, (USER_BIKE_LICENSE_Y1 + USER_BIKE_LICENSE_Y2) / 2 - 5, "电动车通行证", 24, 22, MY_BLACK);
			break;
		case USER_BIKE_REGISTER:
			setcolor(MY_WHITE);
			setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
			setfillstyle(1, MY_WHITE);
			bar(USER_BIKE_REGISTER_X1, USER_BIKE_REGISTER_Y1, USER_BIKE_REGISTER_X2, USER_BIKE_REGISTER_Y2);
			puthz(USER_BIKE_REGISTER_X1 + 15, (USER_BIKE_REGISTER_Y1 + USER_BIKE_REGISTER_Y2) / 2 - 5, "电动车登记", 24, 25, MY_BLACK);
			break;
		case USER_BIKE_WROTEOUT:
			setcolor(MY_WHITE);
			setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
			setfillstyle(1, MY_WHITE);
			bar(USER_BIKE_WROTEOUT_X1, USER_BIKE_WROTEOUT_Y1, USER_BIKE_WROTEOUT_X2, USER_BIKE_WROTEOUT_Y2);
			puthz(USER_BIKE_WROTEOUT_X1 + 15, (USER_BIKE_WROTEOUT_Y1 + USER_BIKE_WROTEOUT_Y2) / 2 - 5, "电动车报废", 24, 25, MY_BLACK);
			break;
		case USER_DATAGRAPH:
			setcolor(MY_WHITE);
			setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
			setfillstyle(1, MY_WHITE);
			bar(USER_DATAGRAPH_X1, USER_DATAGRAPH_Y1, USER_DATAGRAPH_X2, USER_DATAGRAPH_Y2);
			puthz(USER_DATAGRAPH_X1 + 15, (USER_DATAGRAPH_Y1 + USER_DATAGRAPH_Y2) / 2 - 5, "数据可视化", 24, 25, MY_BLACK);
			break;
		case USER_INFO:
			setcolor(MY_WHITE);
			setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
			setfillstyle(1, MY_WHITE);
			bar(USER_INFO_X1, USER_INFO_Y1, USER_INFO_X2, USER_INFO_Y2);
			puthz(USER_INFO_X1 + 15, (USER_INFO_Y1 + USER_INFO_Y2) / 2 - 5, "用户信息管理", 24, 22, MY_BLACK);
			break;
		case USER_MESSAGE:
			setcolor(MY_WHITE);
			setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
			setfillstyle(1, MY_WHITE);
			bar(USER_MESSAGE_X1, USER_MESSAGE_Y1, USER_MESSAGE_X2, USER_MESSAGE_Y2);
			puthz(USER_MESSAGE_X1 + 5, (USER_MESSAGE_Y1 + USER_MESSAGE_Y2) / 2 - 5, "消息中心", 24, 25, MY_WHITE);
			break;

	}
	
	
}



//刷新画面与鼠标激活状态
void flushUserMain(int *tag,int button_count,user_button UserButtons[]) { 
	int i = 0;
	int temp = 0;
	int new_tag = ACTIVE_USER_NONE;
	
	
	
for (i = 0; i < button_count; i++) {
	if (MouseX >= UserButtons[i].x1 && MouseX <= UserButtons[i].x2 &&
		MouseY >= UserButtons[i].y1 && MouseY <= UserButtons[i].y2) {
		new_tag = UserButtons[i].active_tag;
		temp = i; 
		break;
	}
}

if (*tag != new_tag) {
	if (*tag != ACTIVE_USER_NONE) {
		if (*tag <= ACTIVE_USER_DATAGRAPH) {
			setcolor(MY_LIGHTGRAY);
			setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
			rectangle(UserButtons[*tag-1].x1, UserButtons[*tag-1].y1, UserButtons[*tag-1].x2, UserButtons[*tag-1].y2);
			MouseS = 1;
		}
		else if (*tag == ACTIVE_USER_EXIT) {
			setcolor(MY_RED);
			setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
			rectangle(USER_EXIT_X1, USER_EXIT_Y1, USER_EXIT_X2, USER_EXIT_Y2);
			MouseS = 1;
		}
		else if (*tag == ACTIVE_USER_BACK) {
			setfillstyle(1, MY_YELLOW);//恢复“返回登录”
			setcolor(MY_YELLOW);
			bar(USER_BACK_X1, USER_BACK_Y1, USER_BACK_X2, USER_BACK_Y2);
			puthz(USER_BACK_X1 + 5, (USER_BACK_Y1 + USER_BACK_Y2) / 2 - 10, "返回", 24, 25, MY_WHITE);
			MouseS = 1;
		}
	}
	*tag = new_tag;
	if (new_tag != ACTIVE_USER_NONE && new_tag<=ACTIVE_USER_DATAGRAPH) {
		setfillstyle(1,MY_WHITE);
		setcolor(MY_WHITE);
		setlinestyle(SOLID_LINE,0,THICK_WIDTH);
		rectangle(UserButtons[temp].x1, UserButtons[temp].y1, UserButtons[temp].x2, UserButtons[temp].y2);
		MouseS = 1;
	}
	else if (new_tag == ACTIVE_USER_EXIT) {
		setfillstyle(1, MY_WHITE);
		setcolor(MY_WHITE);
		setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
		rectangle(UserButtons[temp].x1, UserButtons[temp].y1, UserButtons[temp].x2, UserButtons[temp].y2);
		MouseS = 1;
	}
	else if (new_tag == ACTIVE_USER_BACK) {
		setcolor(MY_RED);
		setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
		setfillstyle(1, MY_RED);
		bar(USER_BACK_X1, USER_BACK_Y1, USER_BACK_X2, USER_BACK_Y2);
		puthz(USER_BACK_X1 + 5, (USER_BACK_Y1 + USER_BACK_Y2) / 2 - 10, "返回", 24, 25, MY_WHITE);
		MouseS = 1;
	}
	else {
		/*清除提示
		setcolor(MY_LIGHTGRAY);
		setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
		for (i = 0; i < button_count-2; i++) {
			rectangle(UserButtons[i].x1, UserButtons[i].y1, UserButtons[i].x2, UserButtons[i].y2);
		}

		setfillstyle(1, MY_YELLOW);//恢复“返回登录”
		setcolor(MY_YELLOW);
		bar(USER_BACK_X1, USER_BACK_Y1, USER_BACK_X2, USER_BACK_Y2);
		puthz(USER_BACK_X1 + 5, (USER_BACK_Y1 + USER_BACK_Y2) / 2 - 10, "返回", 24, 25, MY_WHITE);

		setcolor(MY_RED);
		setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
		rectangle(USER_EXIT_X1,USER_EXIT_Y1,USER_EXIT_X2,USER_EXIT_Y2);
        */
		MouseS = 0;
	}
}
}



int handle_click_main(int button_num, user_button UserButtons[]){
	int i = 0;
	for (i = 0; i < button_num; i++) {
		if (mouse_press(UserButtons[i].x1, UserButtons[i].y1, UserButtons[i].x2, UserButtons[i].y2) == 1) 
			return UserButtons[i].page;
	}	
	return -1;
}






void user_bike_register(int* page, unsigned long* id)
{
	int tag = 0;
	int click = -1;
	int register_flag = 0;
	int mouse_flag;
	char usrn[16] = {'\0'}; // 初始化为空
	char e_bike_id[10] = {'\0'};
	user_button UserButtons[] = {
{USER_BIKE_REGISTER_X1, USER_BIKE_REGISTER_X2,USER_BIKE_REGISTER_Y1, USER_BIKE_REGISTER_Y2,ACTIVE_USER_BIKE_REGISTER,USER_BIKE_REGISTER},
{USER_BIKE_LICENSE_X1, USER_BIKE_LICENSE_X2,USER_BIKE_LICENSE_Y1, USER_BIKE_LICENSE_Y2,ACTIVE_USER_BIKE_LICENSE,USER_BIKE_LICENSE},
{USER_BIKE_ANUAL_X1, USER_BIKE_ANUAL_X2,USER_BIKE_ANUAL_Y1, USER_BIKE_ANUAL_Y2,ACTIVE_USER_BIKE_ANUAL,USER_BIKE_ANUAL},
{USER_BIKE_WROTEOUT_X1, USER_BIKE_WROTEOUT_X2,USER_BIKE_WROTEOUT_Y1, USER_BIKE_WROTEOUT_Y2,ACTIVE_USER_BIKE_WROTEOUT,USER_BIKE_WROTEOUT},
{USER_INFO_X1, USER_INFO_X2,USER_INFO_Y1, USER_INFO_Y2,ACTIVE_USER_INFO,USER_INFO},
{USER_MESSAGE_X1, USER_MESSAGE_X2,USER_MESSAGE_Y1, USER_MESSAGE_Y2,ACTIVE_USER_MESSAGE,USER_MESSAGE},
{USER_DATAGRAPH_X1, USER_DATAGRAPH_X2,USER_DATAGRAPH_Y1, USER_DATAGRAPH_Y2,ACTIVE_USER_DATAGRAPH,USER_DATAGRAPH},
{USER_BACK_X1,USER_BACK_X2,USER_BACK_Y1,USER_BACK_Y2,ACTIVE_USER_BACK,LOGIN},
{USER_EXIT_X1,USER_EXIT_X2,USER_EXIT_Y1,USER_EXIT_Y2,ACTIVE_USER_EXIT,EXIT},
	};
	clrmous(MouseX, MouseY);
	save_bk_mou(MouseX, MouseY);
	drawgraph_user_main(page);


	if (!ebike_user_register_judge(id)) {
		setfillstyle(SOLID_FILL, MY_WHITE);
		bar(150, 60, 640, 480);
		drawgraph_user_bike_register_info(id);
		clrmous(MouseX, MouseY);
		save_bk_mou(MouseX, MouseY);
		while (1) {
			user_newmouse_data(&MouseX, &MouseY, &press,&mouse_flag);
			flushUserMain(&tag, STRUCT_LENGTH(UserButtons), UserButtons); // 刷新界面
			click = handle_click_main(STRUCT_LENGTH(UserButtons), UserButtons);
			if (click == LOGIN || click == EXIT || click == USER_BIKE_LICENSE) {          //其它页面做完后此处会改成click!=-1&&click!=USER_BIKE_REGISTER
				*page = click;
				return;
			}
			user_drawmouse(&MouseX, &MouseY, &press, &mouse_flag);
			delay(25);
		}
	}
	drawgraph_user_bike_register_new();
	while (1) {
		flushUserMain(&tag, STRUCT_LENGTH(UserButtons), UserButtons); // 刷新界面
		flushUserRegister(&tag);
		newmouse(&MouseX, &MouseY, &press);
		click = handle_click_main(STRUCT_LENGTH(UserButtons), UserButtons);
		if (click == LOGIN || click==USER_BIKE_LICENSE ||click == USER_BIKE_WROTEOUT||click==EXIT) {          //其它页面做完后此处会改成click!=-1&&click!=USER_BIKE_REGISTER
			*page = click;
			return;
		}//菜单界面点击
		if (mouse_press(USER_BIKE_REGISTER_INPUT1_X1, USER_BIKE_REGISTER_INPUT1_Y1, USER_BIKE_REGISTER_INPUT1_X2, USER_BIKE_REGISTER_INPUT1_Y2) == 1) {
			ch_input(usrn, USER_BIKE_REGISTER_INPUT1_X1, USER_BIKE_REGISTER_INPUT1_Y1 + 5, 13, MY_WHITE, 0, 1);
		}
		if (mouse_press(USER_BIKE_REGISTER_INPUT2_X1, USER_BIKE_REGISTER_INPUT2_Y1, USER_BIKE_REGISTER_INPUT2_X2, USER_BIKE_REGISTER_INPUT2_Y2) == 1) {
			ch_input(e_bike_id, USER_BIKE_REGISTER_INPUT2_X1, USER_BIKE_REGISTER_INPUT2_Y1 + 5, 13, MY_WHITE, 0, 1);
		}

		if (mouse_press(USER_BIKE_REGISTER_BUTTON1_X1, USER_BIKE_REGISTER_BUTTON1_Y1, USER_BIKE_REGISTER_BUTTON1_X2, USER_BIKE_REGISTER_BUTTON1_Y2) == 1) {
			register_flag = EBIKE_INFO_judge(usrn, e_bike_id,id);
			if (register_flag == 0) {
				anime_login_success_user();
				setfillstyle(SOLID_FILL, MY_WHITE);
				bar(150, 60, 640, 480);
				ch_input(NULL, NULL, NULL, NULL, NULL, INPUTBAR_CLEAR, NULL);
				puthz(280, 260, "您已登记成功", 32, 40, MY_BLACK);
				puthz(320, 300, "请等待审核", 32, 40, MY_BLACK);
				delay(3000);
				*page = MAIN_USER;
				return;
			}
			else 
				anime_user_bike_register_fail(register_flag);
		}
		delay(25); // 50hz刷新率
	}
}



int ebike_user_register_judge(unsigned long *ID) {
	int i = 0;
	int bike_count = 0;
	int account_counts;
	EBIKE_INFO TEMP;
	FILE* fp_EBIKE_INFO_read = fopen("C:\\EBS\\DATA\\REGISTER.DAT", "r");

	if (fp_EBIKE_INFO_read == NULL) {
		fclose(fp_EBIKE_INFO_read);
		exit(0);
	}

	fseek(fp_EBIKE_INFO_read, 0, SEEK_END);
	account_counts = ftell(fp_EBIKE_INFO_read) / sizeof(EBIKE_INFO);//初始操作完成，接下来开始遍历数据

	for (i = 0; i < account_counts; i++) {
		fseek(fp_EBIKE_INFO_read, i * sizeof(EBIKE_INFO), SEEK_SET);
		fread(&TEMP, sizeof(EBIKE_INFO), 1, fp_EBIKE_INFO_read); //逐个读取信息，确认此id是否登记过电动车

		if (*ID==TEMP.ID) {
			if (fclose(fp_EBIKE_INFO_read) != 0) getch(), exit(0);
			return 0;
		}
	}
	
	if (fclose(fp_EBIKE_INFO_read) != 0) getch(), exit(0);
	return 1;
}



void flushUserRegister(int* tag) {
	if ((MouseX >= USER_BIKE_REGISTER_INPUT1_X1 && MouseX <= USER_BIKE_REGISTER_INPUT1_X2 && MouseY >= USER_BIKE_REGISTER_INPUT1_Y1 && MouseY <= USER_BIKE_REGISTER_INPUT1_Y2) ||
		(MouseX >= USER_BIKE_REGISTER_INPUT2_X1 && MouseX <= USER_BIKE_REGISTER_INPUT2_X2 && MouseY >= USER_BIKE_REGISTER_INPUT2_Y1 && MouseY <= USER_BIKE_REGISTER_INPUT2_Y2))
		MouseS = 2;
	else if ((MouseX >= USER_BIKE_REGISTER_BUTTON1_X1 && MouseX <= USER_BIKE_REGISTER_BUTTON1_X2 && MouseY >= USER_BIKE_REGISTER_BUTTON1_Y1 && MouseY <= USER_BIKE_REGISTER_BUTTON1_Y2) ||
		(MouseX >= USER_BIKE_REGISTER_BUTTON2_X1 && MouseX <= USER_BIKE_REGISTER_BUTTON2_X2 && MouseY >= USER_BIKE_REGISTER_BUTTON2_Y1 && MouseY <= USER_BIKE_REGISTER_BUTTON2_Y2))
		MouseS = 1;
	else
		MouseS = 0;
}



int EBIKE_INFO_judge(char* usrn, char* e_bike_id,unsigned long* id) {
	int i = 0;
	int account_counts;
	EBIKE_INFO TEMP ;
	FILE* fp_EBIKE_INFO_readndwrite = fopen("C:\\EBS\\DATA\\REGISTER.DAT", "rb+");
	if ( fp_EBIKE_INFO_readndwrite == NULL) {
		fclose(fp_EBIKE_INFO_readndwrite);
		exit(0);
	}
	if (usrn[0] == '\0') {
		if (fclose(fp_EBIKE_INFO_readndwrite) != 0) getch(), exit(1);
		return 3;
	}
	if (e_bike_id[0] == '\0') {
		if (fclose(fp_EBIKE_INFO_readndwrite) != 0) getch(), exit(1);
		return 4;
	}
	memset(&TEMP,0, sizeof(TEMP));
	fseek(fp_EBIKE_INFO_readndwrite, 0, SEEK_END);
	account_counts = ftell(fp_EBIKE_INFO_readndwrite) / sizeof(EBIKE_INFO);//初始操作完成，接下来开始遍历数据

	for (i = 0; i < account_counts; i++) {
		fseek(fp_EBIKE_INFO_readndwrite, i * sizeof(EBIKE_INFO), SEEK_SET);
		fread(&TEMP, sizeof(EBIKE_INFO), 1, fp_EBIKE_INFO_readndwrite); //逐个读取，每个用户信息

		if (strcmp(usrn, TEMP.rln) == 0) {
			if (fclose(fp_EBIKE_INFO_readndwrite) != 0) getch(), exit(1); //发现存在用户名相同的，则注册失败
			return 1;
		}
		if (strcmp(e_bike_id, TEMP.ebike_ID) == 0) {
			if (fclose(fp_EBIKE_INFO_readndwrite) != 0) getch(), exit(1); //发现存在车牌号相同的，则注册失败
			return 2;
		}
	}

	//若经过了for循环仍未经过return，则代表用户名未曾注册过，可以注册
	strcpy(TEMP.rln, usrn);			//获取账密和uid
	strcpy(TEMP.ebike_ID, e_bike_id);
	strcpy(TEMP.ebike_license, "-1");
	strcpy(TEMP.location, "-1");
	TEMP.ID =*id;
	TEMP.apply_time =get_approx_time(NULL);
	TEMP.conduct_time = -1;
	TEMP.result = -1;
	TEMP.anual_check = -1;
	TEMP.violations = -1;
	fseek(fp_EBIKE_INFO_readndwrite, 0, SEEK_END); // 确保写入位置在文件末尾
	fwrite(&TEMP, sizeof(EBIKE_INFO), 1, fp_EBIKE_INFO_readndwrite);  //将注册信息写入文件
	if (fclose(fp_EBIKE_INFO_readndwrite) != 0) getch(), exit(1);
	return 0;

}



void anime_login_success_user() {
	int blinkTick = 0;
	clrmous(MouseX, MouseY);

	setfillstyle(SOLID_FILL, MY_WHITE);
	bar(310,130,600,160); //覆盖原有的错误提示
	bar(310, 190, 600, 220);
	setcolor(LIGHTGREEN);
	setlinestyle(SOLID_LINE,0, THICK_WIDTH);
	rectangle(USER_BIKE_REGISTER_INPUT1_X1 + 2, USER_BIKE_REGISTER_INPUT1_Y1 + 2, USER_BIKE_REGISTER_INPUT1_X2 - 2, USER_BIKE_REGISTER_INPUT1_Y2 - 2);
	rectangle(USER_BIKE_REGISTER_INPUT2_X1 + 2, USER_BIKE_REGISTER_INPUT2_Y1 + 2, USER_BIKE_REGISTER_INPUT2_X2 - 2, USER_BIKE_REGISTER_INPUT2_Y2 - 2);

	while (blinkTick < 100) {
		if (blinkTick % 20 == 0 && blinkTick % 40 != 0) {
			setfillstyle(SOLID_FILL, MY_GREEN);
			bar(USER_BIKE_REGISTER_BUTTON1_X1, USER_BIKE_REGISTER_BUTTON1_Y1, USER_BIKE_REGISTER_BUTTON1_X2, USER_BIKE_REGISTER_BUTTON1_Y2);
			puthz(USER_BIKE_REGISTER_BUTTON1_X1 + 3, USER_BIKE_REGISTER_BUTTON1_Y1 + 9, "登记成功", 24, 18, MY_WHITE);
		}
		else if (blinkTick % 40 == 0) {
			setfillstyle(SOLID_FILL, MY_LIGHTBLUE);
			bar(USER_BIKE_REGISTER_BUTTON1_X1, USER_BIKE_REGISTER_BUTTON1_Y1, USER_BIKE_REGISTER_BUTTON1_X2, USER_BIKE_REGISTER_BUTTON1_Y2);
			puthz(USER_BIKE_REGISTER_BUTTON1_X1 + 3, USER_BIKE_REGISTER_BUTTON1_Y1 + 9, "登记成功", 24, 18, MY_WHITE);
		}
		blinkTick++;
		delay(25);
	}
}



void anime_user_bike_register_fail(int flag) {
	setcolor(MY_WHITE);
	setfillstyle(SOLID_FILL, MY_WHITE);
	setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
	rectangle(USER_BIKE_REGISTER_INPUT1_X1 + 1, USER_BIKE_REGISTER_INPUT1_Y1 + 1, USER_BIKE_REGISTER_INPUT1_X2 - 1, USER_BIKE_REGISTER_INPUT1_Y2 - 1);
	rectangle(USER_BIKE_REGISTER_INPUT2_X1 + 1, USER_BIKE_REGISTER_INPUT2_Y1 + 1, USER_BIKE_REGISTER_INPUT2_X2 - 1, USER_BIKE_REGISTER_INPUT2_Y2 - 1);
	bar(400, 130, 520, 156);
	bar(400, 193, 520, 219);
	setcolor(MY_LIGHTGRAY);
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	rectangle(USER_BIKE_REGISTER_INPUT1_X1, USER_BIKE_REGISTER_INPUT1_Y1, USER_BIKE_REGISTER_INPUT1_X2, USER_BIKE_REGISTER_INPUT1_Y2);
	rectangle(USER_BIKE_REGISTER_INPUT2_X1, USER_BIKE_REGISTER_INPUT2_Y1, USER_BIKE_REGISTER_INPUT2_X2, USER_BIKE_REGISTER_INPUT2_Y2);//清除错误提示，恢复初始状态

	setcolor(MY_RED);
	setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
	switch (flag) {
	case 1:
		rectangle(USER_BIKE_REGISTER_INPUT1_X1 + 1, USER_BIKE_REGISTER_INPUT1_Y1 + 1, USER_BIKE_REGISTER_INPUT1_X2 - 1, USER_BIKE_REGISTER_INPUT1_Y2 - 1);
		puthz(410, 140, "姓名重复", 16, 15, MY_RED);
		return;
	case 2:
		rectangle(USER_BIKE_REGISTER_INPUT2_X1 + 2, USER_BIKE_REGISTER_INPUT2_Y1 + 1, USER_BIKE_REGISTER_INPUT2_X2 - 1, USER_BIKE_REGISTER_INPUT2_Y2 - 1);
		puthz(410, 203, "车牌号重复", 16, 15, MY_RED);
		return;
	case 3:
		rectangle(USER_BIKE_REGISTER_INPUT1_X1 + 2, USER_BIKE_REGISTER_INPUT1_Y1 + 1, USER_BIKE_REGISTER_INPUT1_X2 - 1, USER_BIKE_REGISTER_INPUT1_Y2 - 1);
		puthz(410, 140, "请输入姓名", 16, 15, MY_RED);
		return;
	case 4:
		rectangle(USER_BIKE_REGISTER_INPUT2_X1 + 2, USER_BIKE_REGISTER_INPUT2_Y1 + 1, USER_BIKE_REGISTER_INPUT2_X2 - 1, USER_BIKE_REGISTER_INPUT2_Y2 - 1);
		puthz(410, 203, "请输入车牌号", 16, 15, MY_RED);
		return;
	}

}



void drawgraph_user_bike_register_new() {
	
	puthz(260, 80, "电动车登记", 32,40, MY_BLACK);
	setcolor(MY_BLACK);
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	setfillstyle(SOLID_FILL, MY_BLACK);
	bar(151, 120, 640, 123);
	setcolor(MY_LIGHTGRAY);
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	rectangle(USER_BIKE_REGISTER_INPUT1_X1, USER_BIKE_REGISTER_INPUT1_Y1, USER_BIKE_REGISTER_INPUT1_X2, USER_BIKE_REGISTER_INPUT1_Y2);
	rectangle(USER_BIKE_REGISTER_INPUT2_X1, USER_BIKE_REGISTER_INPUT2_Y1, USER_BIKE_REGISTER_INPUT2_X2, USER_BIKE_REGISTER_INPUT2_Y2);

	puthz(170, 170, "姓名",24,20,MY_BLACK);
	puthz(160, 235, "车牌号",24,20,MY_BLACK);

	setcolor(MY_RED);
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	setfillstyle(SOLID_FILL, MY_RED);
	bar(USER_BIKE_REGISTER_BUTTON1_X1, USER_BIKE_REGISTER_BUTTON1_Y1, USER_BIKE_REGISTER_BUTTON1_X2, USER_BIKE_REGISTER_BUTTON1_Y2);
	bar(USER_BIKE_REGISTER_BUTTON2_X1, USER_BIKE_REGISTER_BUTTON2_Y1, USER_BIKE_REGISTER_BUTTON2_X2, USER_BIKE_REGISTER_BUTTON2_Y2);
	puthz(USER_BIKE_REGISTER_BUTTON1_X1 + 10, USER_BIKE_REGISTER_BUTTON1_Y1 + 10, "登记", 24, 30, MY_WHITE);
	puthz(USER_BIKE_REGISTER_BUTTON2_X1 + 10, USER_BIKE_REGISTER_BUTTON2_Y1 + 10, "反馈", 24, 30, MY_WHITE);

	puthz(170, 290, "电动车座位数", 24, 20, MY_BLACK);
	puthz(170, 340, "电动车品牌", 24, 20, MY_BLACK);
	puthz(400, 290, "电动车购买时间", 24, 20, MY_BLACK);
	puthz(400, 340, "登记情况", 24, 20, MY_BLACK);
	puthz(520, 340, "未登记", 24, 20, MY_BLACK);
}



void drawgraph_user_bike_register_info(unsigned long *id) {
	EBIKE_INFO user_info;
	char id_string[20];
	char apply_time_string[20];//一定要给sprintf留出足够缓冲区
	char conduct_time_string[20];
	user_bike_register_getinfo(&user_info,id);
	sprintf(id_string, "%lu", *id);
	sprintf(apply_time_string, "%lu",user_info.apply_time);
	sprintf(conduct_time_string, "%lu", user_info.conduct_time);
	
	puthz(260, 80, "电动车信息", 32, 40, MY_BLACK);
	setcolor(MY_BLACK);
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	setfillstyle(SOLID_FILL, MY_BLACK);
	bar(151, 120, 640, 123);

	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2); // 默认字体，水平方向，大小2
	setcolor(MY_BLACK);
	
	puthz(170, 140, "姓名", 24, 20, MY_BLACK);
	outtextxy(260, 142, user_info.rln);
	puthz(170, 190, "车牌号", 24, 20, MY_BLACK);
	outtextxy(260, 192, user_info.ebike_ID);
	puthz(170, 240, "学号", 24, 20, MY_BLACK);
	outtextxy(260, 242, id_string);
	puthz(170, 290, "登记时间", 24, 20, MY_BLACK);
	outtextxy(260, 292, apply_time_string);
	puthz(390, 290, "处理时间", 24, 20, MY_BLACK);
	outtextxy(510, 292, conduct_time_string);
	puthz(170, 340, "登记情况", 24, 20, MY_BLACK);
	puthz(260, 340, "待定", 24, 20, MY_BLACK);
	puthz(390, 340, "电动车状态", 24, 20, MY_BLACK);
	puthz(510, 340, "待定", 24, 20, MY_BLACK);
}



void user_bike_register_getinfo(EBIKE_INFO* user_info,unsigned long *id) {
	int i = 0;
	int account_counts;
	EBIKE_INFO TEMP;
	FILE* fp_EBIKE_INFO_readndwrite = fopen("C:\\EBS\\DATA\\REGISTER.DAT", "rb");
	if (fp_EBIKE_INFO_readndwrite == NULL) {
		fclose(fp_EBIKE_INFO_readndwrite);
		exit(0);
	}
	
	memset(&TEMP, 0, sizeof(TEMP));
	fseek(fp_EBIKE_INFO_readndwrite, 0, SEEK_END);
	account_counts = ftell(fp_EBIKE_INFO_readndwrite) / sizeof(EBIKE_INFO);//初始操作完成，接下来开始遍历数据

	for (i = 0; i < account_counts; i++) {
		fseek(fp_EBIKE_INFO_readndwrite, i * sizeof(EBIKE_INFO), SEEK_SET);
		fread(&TEMP, sizeof(EBIKE_INFO), 1, fp_EBIKE_INFO_readndwrite); //逐个读取，每个用户信息

		if (*id==TEMP.ID) {
			strcpy(user_info->rln,TEMP.rln);			//获取账密和uid
			strcpy(user_info->ebike_ID,TEMP.ebike_ID);
			strcpy(user_info->ebike_license,TEMP.ebike_license);
			strcpy(user_info->location,TEMP.location);
			user_info->apply_time = TEMP.apply_time;
			user_info->anual_check = -1;
			user_info->violations = -1;
			user_info->conduct_time = TEMP.conduct_time;
			user_info->result = TEMP.result;
			if (fclose(fp_EBIKE_INFO_readndwrite) != 0) getch(), exit(1);
			return;
		}
	}
	if (fclose(fp_EBIKE_INFO_readndwrite) != 0) getch(), exit(1);
		return ;
}

void user_bike_license(int *page,unsigned long *id)
{
	int license_data[3] = {-1,-1,-1};
	int click = -1;
	int tag = 0;
	int register_flag = 0;
	int mouse_flag;
	user_button UserButtons[] = {
{USER_BIKE_REGISTER_X1, USER_BIKE_REGISTER_X2,USER_BIKE_REGISTER_Y1, USER_BIKE_REGISTER_Y2,ACTIVE_USER_BIKE_REGISTER,USER_BIKE_REGISTER},
{USER_BIKE_LICENSE_X1, USER_BIKE_LICENSE_X2,USER_BIKE_LICENSE_Y1, USER_BIKE_LICENSE_Y2,ACTIVE_USER_BIKE_LICENSE,USER_BIKE_LICENSE},
{USER_BIKE_ANUAL_X1, USER_BIKE_ANUAL_X2,USER_BIKE_ANUAL_Y1, USER_BIKE_ANUAL_Y2,ACTIVE_USER_BIKE_ANUAL,USER_BIKE_ANUAL},
{USER_BIKE_WROTEOUT_X1, USER_BIKE_WROTEOUT_X2,USER_BIKE_WROTEOUT_Y1, USER_BIKE_WROTEOUT_Y2,ACTIVE_USER_BIKE_WROTEOUT,USER_BIKE_WROTEOUT},
{USER_INFO_X1, USER_INFO_X2,USER_INFO_Y1, USER_INFO_Y2,ACTIVE_USER_INFO,USER_INFO},
{USER_MESSAGE_X1, USER_MESSAGE_X2,USER_MESSAGE_Y1, USER_MESSAGE_Y2,ACTIVE_USER_MESSAGE,USER_MESSAGE},
{USER_DATAGRAPH_X1, USER_DATAGRAPH_X2,USER_DATAGRAPH_Y1, USER_DATAGRAPH_Y2,ACTIVE_USER_DATAGRAPH,USER_DATAGRAPH},
{USER_BACK_X1,USER_BACK_X2,USER_BACK_Y1,USER_BACK_Y2,ACTIVE_USER_BACK,LOGIN},
{USER_EXIT_X1,USER_EXIT_X2,USER_EXIT_Y1,USER_EXIT_Y2,ACTIVE_USER_EXIT,EXIT},
	};
	user_box UserLicenseBox[3][3] = {
	{{ USER_BIKE_LICENSE_BOX1_1_X1, USER_BIKE_LICENSE_BOX1_1_X2, USER_BIKE_LICENSE_BOX1_1_Y1, USER_BIKE_LICENSE_BOX1_1_Y2 },
	{ USER_BIKE_LICENSE_BOX1_2_X1, USER_BIKE_LICENSE_BOX1_2_X2, USER_BIKE_LICENSE_BOX1_2_Y1, USER_BIKE_LICENSE_BOX1_2_Y2 },
	{ USER_BIKE_LICENSE_BOX1_3_X1, USER_BIKE_LICENSE_BOX1_3_X2, USER_BIKE_LICENSE_BOX1_3_Y1, USER_BIKE_LICENSE_BOX1_3_Y2 }},
	{{ USER_BIKE_LICENSE_BOX2_1_X1, USER_BIKE_LICENSE_BOX2_1_X2, USER_BIKE_LICENSE_BOX2_1_Y1, USER_BIKE_LICENSE_BOX2_1_Y2 },
	{ USER_BIKE_LICENSE_BOX2_2_X1, USER_BIKE_LICENSE_BOX2_2_X2, USER_BIKE_LICENSE_BOX2_2_Y1, USER_BIKE_LICENSE_BOX2_2_Y2 },
	{ USER_BIKE_LICENSE_BOX2_3_X1, USER_BIKE_LICENSE_BOX2_3_X2, USER_BIKE_LICENSE_BOX2_3_Y1, USER_BIKE_LICENSE_BOX2_3_Y2 }},
	{{ USER_BIKE_LICENSE_BOX3_1_X1, USER_BIKE_LICENSE_BOX3_1_X2, USER_BIKE_LICENSE_BOX3_1_Y1, USER_BIKE_LICENSE_BOX3_1_Y2 },
	{ USER_BIKE_LICENSE_BOX3_2_X1, USER_BIKE_LICENSE_BOX3_2_X2, USER_BIKE_LICENSE_BOX3_2_Y1, USER_BIKE_LICENSE_BOX3_2_Y2 },
	{ USER_BIKE_LICENSE_BOX3_3_X1, USER_BIKE_LICENSE_BOX3_3_X2, USER_BIKE_LICENSE_BOX3_3_Y1, USER_BIKE_LICENSE_BOX3_3_Y2 }}
	};//选项框
	clrmous(MouseX, MouseY);
	save_bk_mou(MouseX, MouseY);
	drawgraph_user_main(page);
	drawgraph_user_bike_license(id,UserLicenseBox);
	while (1) {
		user_newmouse_data(&MouseX, &MouseY, &press,&mouse_flag);
		flushUserMain(&tag, STRUCT_LENGTH(UserButtons), UserButtons); // 刷新界面
		flushUserLicense(UserLicenseBox,license_data);
		handle_click_user_license(UserLicenseBox,license_data);//处理选项框
		click = handle_click_main(STRUCT_LENGTH(UserButtons), UserButtons);
		if (click == LOGIN || click == USER_BIKE_REGISTER ||click==USER_BIKE_WROTEOUT|| click == EXIT) {          //其它页面做完后此处会改成click!=-1&&click!=USER_BIKE_LICENSE
			*page = click;
			return;
		}//菜单界面点击
		if (mouse_press(USER_BIKE_LICENSE_BUTTON1_X1, USER_BIKE_LICENSE_BUTTON1_Y1, USER_BIKE_LICENSE_BUTTON1_X2, USER_BIKE_LICENSE_BUTTON1_Y2) == 1) {
			user_license_data_judge(license_data);
		}
		user_drawmouse(&MouseX, &MouseY, &press, &mouse_flag);
		delay(25);
	}
}

void drawgraph_user_bike_license(unsigned long *id,user_box box[3][3]) {
	EBIKE_INFO user_info;
	char time_string[20];
	int i, j;

	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2); // 默认字体，水平方向，大小2
	setcolor(MY_BLACK);
	puthz(170, 80, "姓名", 24, 20, MY_BLACK);
	//outtextxy(260, 82, user_info.rln);
	puthz(360, 80, "车牌号", 24, 20, MY_BLACK);
	//outtextxy(260, 82, user_info.ebike_ID);
	puthz(170, 215, "选择预约时间", 24, 20, MY_BLACK);
	add_days_to_date(time_string, 0); outtextxy(170, 250, time_string); puthz(345, 250, "今日", 16,15, MY_BLACK);
	add_days_to_date(time_string, 3); outtextxy(170, 293, time_string);//3,4,5天后可预约
	add_days_to_date(time_string, 4); outtextxy(170, 328, time_string);
	add_days_to_date(time_string, 5); outtextxy(170, 363, time_string);
	outtextxy(410, 308, "08:30-12:00");
	outtextxy(410, 348, "14:00-18:30");
	puthz(170, 125, "选择预约地点", 24, 20, MY_BLACK);
	puthz(170, 160, "韵苑服务点", 24, 20, MY_BLACK);
	puthz(330, 160, "沁苑服务点", 24, 20, MY_BLACK);
	puthz(490, 160, "紫菘服务点", 24, 20, MY_BLACK);

	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	setcolor(MY_LIGHTGRAY);
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			rectangle(box[i][j].x1, box[i][j].y1, box[i][j].x2, box[i][j].y2);
	rectangle(USER_BIKE_LICENSE_BOX1_1_X1, USER_BIKE_LICENSE_BOX1_1_Y1, USER_BIKE_LICENSE_BOX1_1_X2, USER_BIKE_LICENSE_BOX1_1_Y2);
	rectangle(USER_BIKE_LICENSE_BOX2_1_X1, USER_BIKE_LICENSE_BOX2_1_Y1, USER_BIKE_LICENSE_BOX2_1_X2, USER_BIKE_LICENSE_BOX2_1_Y2);

	setcolor(MY_RED);
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	setfillstyle(SOLID_FILL, MY_RED);
	bar(USER_BIKE_LICENSE_BUTTON1_X1, USER_BIKE_LICENSE_BUTTON1_Y1, USER_BIKE_LICENSE_BUTTON1_X2, USER_BIKE_LICENSE_BUTTON1_Y2);
	puthz(USER_BIKE_LICENSE_BUTTON1_X1 + 13, USER_BIKE_LICENSE_BUTTON1_Y1 + 8, "申请", 24, 25, MY_WHITE);
	setfillstyle(SOLID_FILL, MY_YELLOW);
	bar(USER_BIKE_LICENSE_BUTTON2_X1, USER_BIKE_LICENSE_BUTTON2_Y1, USER_BIKE_LICENSE_BUTTON2_X2, USER_BIKE_LICENSE_BUTTON2_Y2);
	puthz(USER_BIKE_LICENSE_BUTTON2_X1 + 5, USER_BIKE_LICENSE_BUTTON2_Y1 + 7, "查看位置", 16, 18, MY_WHITE);
}

void flushUserLicense(user_box box[3][3],int data[3]) {
	int i, j;
	int flag = 0;
	setcolor(MY_BLACK);
	setlinestyle(SOLID_LINE,0, NORM_WIDTH);
	for (i = 0; i < 3; i++)//处理选项框鼠标样式
	for (j = 0; j < 3; j++)
		if (MouseX >= box[i][j].x1 && MouseX <= box[i][j].x2 && MouseY >=box[i][j].y1 && MouseY <=box[i][j].y2) {
			flag = 1; break;
		}
	if (MouseX >= USER_BIKE_LICENSE_BUTTON1_X1 && MouseX <= USER_BIKE_LICENSE_BUTTON1_X2 && MouseY >= USER_BIKE_LICENSE_BUTTON1_Y1 && MouseY <= USER_BIKE_LICENSE_BUTTON1_Y2) {
		setcolor(MY_BLACK);setlinestyle(SOLID_LINE,0,NORM_WIDTH);
		rectangle(USER_BIKE_LICENSE_BUTTON1_X1-1, USER_BIKE_LICENSE_BUTTON1_Y1-1, USER_BIKE_LICENSE_BUTTON1_X2+1, USER_BIKE_LICENSE_BUTTON1_Y2+1);
		MouseS = 1;
	}
	else if (MouseX >= USER_BIKE_LICENSE_BUTTON2_X1 && MouseX <= USER_BIKE_LICENSE_BUTTON2_X2 && MouseY >= USER_BIKE_LICENSE_BUTTON2_Y1 && MouseY <= USER_BIKE_LICENSE_BUTTON2_Y2) {
		setcolor(MY_BLACK); setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
		rectangle(USER_BIKE_LICENSE_BUTTON2_X1 - 1, USER_BIKE_LICENSE_BUTTON2_Y1 - 1, USER_BIKE_LICENSE_BUTTON2_X2 + 1, USER_BIKE_LICENSE_BUTTON2_Y2 + 1);
		MouseS = 1;
	}	
	else if (flag) {
		setcolor(MY_WHITE); setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
		rectangle(USER_BIKE_LICENSE_BUTTON1_X1 - 1, USER_BIKE_LICENSE_BUTTON1_Y1 - 1, USER_BIKE_LICENSE_BUTTON1_X2 + 1, USER_BIKE_LICENSE_BUTTON1_Y2 + 1);
		rectangle(USER_BIKE_LICENSE_BUTTON2_X1 - 1, USER_BIKE_LICENSE_BUTTON2_Y1 - 1, USER_BIKE_LICENSE_BUTTON2_X2 + 1, USER_BIKE_LICENSE_BUTTON2_Y2 + 1);
		MouseS = 1;
	}	
	else {
		setcolor(MY_WHITE); setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
		rectangle(USER_BIKE_LICENSE_BUTTON1_X1 - 1, USER_BIKE_LICENSE_BUTTON1_Y1 - 1, USER_BIKE_LICENSE_BUTTON1_X2 + 1, USER_BIKE_LICENSE_BUTTON1_Y2 + 1);
		rectangle(USER_BIKE_LICENSE_BUTTON2_X1 - 1, USER_BIKE_LICENSE_BUTTON2_Y1 - 1, USER_BIKE_LICENSE_BUTTON2_X2 + 1, USER_BIKE_LICENSE_BUTTON2_Y2 + 1);
		MouseS = 0;
	}	

	for (i = 0; i < 3; i++)
			if (data[i]!=-1) {
				setfillstyle(SOLID_FILL, MY_BLACK);
				bar(box[i][data[i]].x1 + 3, box[i][data[i]].y1 + 3, box[i][data[i]].x2 - 3, box[i][data[i]].y2 - 3);//解决鼠标更新导致选项框上色不全的问题
			}
}

void user_license_data_judge(int* data) {
	setfillstyle(SOLID_FILL, MY_WHITE);
	bar(425, 110, 600, 140);
	bar(425, 200, 600, 240);
	if (data[0] == -1) {
		puthz(440, 125, "请选择地点！", 24, 20, MY_RED);
		return;
	}
		
	if (data[1] == -1 || data[2] == -1) {
		puthz(440, 215, "请选择时间！", 24, 20, MY_RED);
		return;
	}
	//之后在此处加入数据写入操作	
}

void handle_click_user_license(user_box box[3][3], int data[3]) {
	int i, j;
	setfillstyle(SOLID_FILL, MY_WHITE);
	for (i = 0; i < 3; i++)
	for (j = 0; j < 3; j++)//处理选项框点击
		if (mouse_press(box[i][j].x1, box[i][j].y1, box[i][j].x2, box[i][j].y2) == 1) {
			bar(box[i][0].x1+3, box[i][0].y1+3, box[i][0].x2-3, box[i][0].y2-3);
			bar(box[i][1].x1+3, box[i][1].y1+3, box[i][1].x2-3, box[i][1].y2-3);
			bar(box[i][2].x1+3, box[i][2].y1+3, box[i][2].x2-3, box[i][2].y2-3);
			setfillstyle(SOLID_FILL, MY_BLACK);
			bar(box[i][j].x1+3, box[i][j].y1+3, box[i][j].x2-3, box[i][j].y2-3);
			data[i] = j; break;//data[0],[1],[2]分别对应申请地点，日期，上/下午
		}
}

//获取给定天数后的日期所对应的字符串
void add_days_to_date(char *date_string, int days_to_add) {
	int days_in_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	unsigned long current_date = get_approx_time(NULL);
	int year = current_date / 10000;
	int month = (current_date % 10000) / 100;
	int day = current_date % 100;
	day += days_to_add;
	while (day > days_in_month[month - 1]) {
		day -= days_in_month[month - 1];
		month += 1;

		if (month > 12) {
			month = 1;
			year += 1;
		}
	}
	sprintf(date_string, "%4d-%2d-%2d", year, month, day);
	return 0;
}

void user_bike_anual()
{

}

void user_bike_wroteout(int *page,unsigned long *id)
{
	int click = -1;
	int tag_main = 0;
	int tag_wroteout = -1;
	int flush_count = 0;
	int mouse_flag;
	char count[8];
	user_button UserButtons[] = {
{USER_BIKE_REGISTER_X1, USER_BIKE_REGISTER_X2,USER_BIKE_REGISTER_Y1, USER_BIKE_REGISTER_Y2,ACTIVE_USER_BIKE_REGISTER,USER_BIKE_REGISTER},
{USER_BIKE_LICENSE_X1, USER_BIKE_LICENSE_X2,USER_BIKE_LICENSE_Y1, USER_BIKE_LICENSE_Y2,ACTIVE_USER_BIKE_LICENSE,USER_BIKE_LICENSE},
{USER_BIKE_ANUAL_X1, USER_BIKE_ANUAL_X2,USER_BIKE_ANUAL_Y1, USER_BIKE_ANUAL_Y2,ACTIVE_USER_BIKE_ANUAL,USER_BIKE_ANUAL},
{USER_BIKE_WROTEOUT_X1, USER_BIKE_WROTEOUT_X2,USER_BIKE_WROTEOUT_Y1, USER_BIKE_WROTEOUT_Y2,ACTIVE_USER_BIKE_WROTEOUT,USER_BIKE_WROTEOUT},
{USER_INFO_X1, USER_INFO_X2,USER_INFO_Y1, USER_INFO_Y2,ACTIVE_USER_INFO,USER_INFO},
{USER_MESSAGE_X1, USER_MESSAGE_X2,USER_MESSAGE_Y1, USER_MESSAGE_Y2,ACTIVE_USER_MESSAGE,USER_MESSAGE},
{USER_DATAGRAPH_X1, USER_DATAGRAPH_X2,USER_DATAGRAPH_Y1, USER_DATAGRAPH_Y2,ACTIVE_USER_DATAGRAPH,USER_DATAGRAPH},
{USER_BACK_X1,USER_BACK_X2,USER_BACK_Y1,USER_BACK_Y2,ACTIVE_USER_BACK,LOGIN},
{USER_EXIT_X1,USER_EXIT_X2,USER_EXIT_Y1,USER_EXIT_Y2,ACTIVE_USER_EXIT,EXIT},
	};
	user_button WroteoutButtons[] = {
		{USER_BIKE_WROTEOUT_BUTTON1_X1,USER_BIKE_WROTEOUT_BUTTON1_X2,USER_BIKE_WROTEOUT_BUTTON1_Y1, USER_BIKE_WROTEOUT_BUTTON1_Y2,11},
		{USER_BIKE_WROTEOUT_BUTTON2_X1,USER_BIKE_WROTEOUT_BUTTON2_X2,USER_BIKE_WROTEOUT_BUTTON2_Y1, USER_BIKE_WROTEOUT_BUTTON2_Y2,12},
		{USER_BIKE_WROTEOUT_INPUT1_X1,USER_BIKE_WROTEOUT_INPUT1_X2,USER_BIKE_WROTEOUT_INPUT1_Y1, USER_BIKE_WROTEOUT_INPUT1_Y2,21},
		{USER_BIKE_WROTEOUT_INPUT2_X1,USER_BIKE_WROTEOUT_INPUT2_X2,USER_BIKE_WROTEOUT_INPUT2_Y1, USER_BIKE_WROTEOUT_INPUT2_Y2,22},
		{USER_BIKE_WROTEOUT_INPUT3_X1,USER_BIKE_WROTEOUT_INPUT3_X2,USER_BIKE_WROTEOUT_INPUT3_Y1, USER_BIKE_WROTEOUT_INPUT3_Y2,23}
	};
	clrmous(MouseX, MouseY);
	save_bk_mou(MouseX, MouseY);
	drawgraph_user_main(page);
	drawgraph_user_bike_wroteout_warning();
	//进入电动车报废功能界面前的警告页面
	while (1) {
		user_newmouse_data(&MouseX, &MouseY, &press,&mouse_flag);//刷新鼠标数据
		flushUserMain(&tag_main, STRUCT_LENGTH(UserButtons), UserButtons); // 刷新界面
		flushUserWroteoutWarning();
		click = handle_click_main(STRUCT_LENGTH(UserButtons), UserButtons);
		if (click == LOGIN || click == USER_BIKE_REGISTER ||click==USER_BIKE_LICENSE|| click == EXIT) {          //其它页面做完后此处会改成click!=-1&&click!=USER_BIKE_LICENSE
			*page = click;
			return;
		}//菜单界面点击
		if (mouse_press(USER_BIKE_WROTEOUT_BUTTON1_X1, USER_BIKE_WROTEOUT_BUTTON1_Y1, USER_BIKE_WROTEOUT_BUTTON1_X2, USER_BIKE_WROTEOUT_BUTTON1_Y2) == 1 && flush_count > 200) {
			setfillstyle(SOLID_FILL, MY_WHITE);
			bar(150, 60, 640, 480);
			break;
		}//5秒后点击确认，结束while循环，进入电动车报废功能界面
		if (mouse_press(USER_BIKE_WROTEOUT_BUTTON2_X1, USER_BIKE_WROTEOUT_BUTTON2_Y1, USER_BIKE_WROTEOUT_BUTTON2_X2, USER_BIKE_WROTEOUT_BUTTON2_Y2) == 1) {
			*page = MAIN_USER;
			return;
		}
		if ((flush_count % 40) == 0) {
			sprintf(count, "(%d)", 5 - flush_count / 40);
			setfillstyle(SOLID_FILL, MY_WHITE);
			bar(USER_BIKE_WROTEOUT_BUTTON1_X1 + 85, USER_BIKE_WROTEOUT_BUTTON1_Y1 + 5, USER_BIKE_WROTEOUT_BUTTON1_X1 + 135, USER_BIKE_WROTEOUT_BUTTON1_Y1 + 35);
			settextstyle(DEFAULT_FONT, HORIZ_DIR, 2); // 默认字体，水平方向，大小2
			setcolor(MY_LIGHTGRAY);
			outtextxy(USER_BIKE_WROTEOUT_BUTTON1_X1 + 85, USER_BIKE_WROTEOUT_BUTTON1_Y1 + 15, count);//整数秒时重新绘制倒计时
		}
		if (flush_count == 201) {
			setfillstyle(SOLID_FILL, MY_WHITE);
			bar(USER_BIKE_WROTEOUT_BUTTON1_X1 + 85, USER_BIKE_WROTEOUT_BUTTON1_Y1 + 5, USER_BIKE_WROTEOUT_BUTTON1_X1 + 135, USER_BIKE_WROTEOUT_BUTTON1_Y1 + 35);
			setfillstyle(SOLID_FILL, MY_RED);
			bar(USER_BIKE_WROTEOUT_BUTTON1_X1, USER_BIKE_WROTEOUT_BUTTON1_Y1, USER_BIKE_WROTEOUT_BUTTON1_X2, USER_BIKE_WROTEOUT_BUTTON1_Y2);
			puthz(USER_BIKE_WROTEOUT_BUTTON1_X1 + 15, USER_BIKE_WROTEOUT_BUTTON1_Y1 + 8, "确认", 24, 20, MY_WHITE);//五秒过后激活“确认”按钮
		}
		if (flush_count <= 201)
			flush_count++;
		user_drawmouse(&MouseX, &MouseY, &press, &mouse_flag);//在可能改变背景的操作后绘制鼠标
		delay(25);
	}
	drawgraph_user_wroteout();
	//电动车报废功能界面
	while (1) {
		user_newmouse_data(&MouseX, &MouseY, &press, &mouse_flag);
		flushUserMain(&tag_main, STRUCT_LENGTH(UserButtons), UserButtons); // 刷新界面
		flushUserWroteout(&tag_wroteout,WroteoutButtons);
		click = handle_click_main(STRUCT_LENGTH(UserButtons), UserButtons);
		if (click == LOGIN || click == USER_BIKE_REGISTER || click == USER_BIKE_LICENSE || click == EXIT) {          //其它页面做完后此处会改成click!=-1&&click!=USER_BIKE_LICENSE
			*page = click;
			return;
		}
		user_drawmouse(&MouseX, &MouseY, &press, &mouse_flag);
		delay(25);
	}
}

void drawgraph_user_bike_wroteout_warning() {
	int i;
	puthz(260, 80, "电动车报废说明", 32, 30, MY_BLACK);
	setcolor(MY_BLACK);
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	setfillstyle(SOLID_FILL, MY_BLACK);
	bar(151, 120, 640, 123);
	puthz(180, 150, "尊敬的用户：", 24, 20, MY_BLACK);
	puthz(180, 210, "在您提交电动车报废申请前，请注意：报废操作将永久清除该车辆的", 24, 20, MY_BLACK);
	puthz(347, 245, "所有数据", 24, 20, MY_RED);
	puthz(438, 245, "包括骑行记录、绑定", 24, 20, MY_BLACK);
	puthz(180, 280, "信息等，且", 24, 20, MY_BLACK);
	puthz(283, 280, "无法恢复",24, 20, MY_RED);
	puthz(363, 280, "。车辆报废后，将无法继续在", 24, 20, MY_BLACK);
	puthz(180,315,"校园内骑行，相关权限同步失效。请确保已妥善处理车辆及个人事务后再确认操作。", 24, 20, MY_BLACK);

	setcolor(MY_RED);
	setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
	bar(USER_BIKE_WROTEOUT_BUTTON1_X1, USER_BIKE_WROTEOUT_BUTTON1_Y1, USER_BIKE_WROTEOUT_BUTTON1_X2, USER_BIKE_WROTEOUT_BUTTON1_Y2);
	puthz(USER_BIKE_WROTEOUT_BUTTON1_X1 + 15, USER_BIKE_WROTEOUT_BUTTON1_Y1 + 8, "确认", 24, 20, MY_WHITE);
	setfillstyle(SOLID_FILL, MY_RED);
	bar(USER_BIKE_WROTEOUT_BUTTON2_X1, USER_BIKE_WROTEOUT_BUTTON2_Y1, USER_BIKE_WROTEOUT_BUTTON2_X2, USER_BIKE_WROTEOUT_BUTTON2_Y2);
	puthz(USER_BIKE_WROTEOUT_BUTTON2_X1 + 15, USER_BIKE_WROTEOUT_BUTTON2_Y1 + 8, "返回", 24, 20, MY_WHITE);

}


void drawgraph_user_wroteout() {
	setcolor(MY_LIGHTGRAY);
	setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
	rectangle(USER_BIKE_WROTEOUT_INPUT1_X1+2, USER_BIKE_WROTEOUT_INPUT1_Y1+2, USER_BIKE_WROTEOUT_INPUT1_X2-2, USER_BIKE_WROTEOUT_INPUT1_Y2-2);
	rectangle(USER_BIKE_WROTEOUT_INPUT2_X1+2, USER_BIKE_WROTEOUT_INPUT2_Y1+2, USER_BIKE_WROTEOUT_INPUT2_X2-2, USER_BIKE_WROTEOUT_INPUT2_Y2-2);
	rectangle(USER_BIKE_WROTEOUT_INPUT3_X1+2, USER_BIKE_WROTEOUT_INPUT3_Y1+2, USER_BIKE_WROTEOUT_INPUT3_X2-2, USER_BIKE_WROTEOUT_INPUT3_Y2-2);
	puthz(220, 90, "请输入姓名，学号与账号密码以确认身份", 24, 20, MY_BLACK);
	puthz(170, 155, "姓名", 24, 20, MY_BLACK);
	puthz(170, 225, "学号",24, 20, MY_BLACK);
	puthz(170, 295, "密码", 24, 20, MY_BLACK);

	setcolor(MY_RED);
	setfillstyle(SOLID_FILL, MY_RED);
	bar(USER_BIKE_WROTEOUT_BUTTON1_X1, USER_BIKE_WROTEOUT_BUTTON1_Y1, USER_BIKE_WROTEOUT_BUTTON1_X2, USER_BIKE_WROTEOUT_BUTTON1_Y2);
	puthz(USER_BIKE_WROTEOUT_BUTTON1_X1 + 15, USER_BIKE_WROTEOUT_BUTTON1_Y1 + 8, "确认", 24, 20, MY_WHITE);
	
	bar(USER_BIKE_WROTEOUT_BUTTON2_X1, USER_BIKE_WROTEOUT_BUTTON2_Y1, USER_BIKE_WROTEOUT_BUTTON2_X2, USER_BIKE_WROTEOUT_BUTTON2_Y2);
	puthz(USER_BIKE_WROTEOUT_BUTTON2_X1 + 15, USER_BIKE_WROTEOUT_BUTTON2_Y1 + 8, "返回", 24, 20, MY_WHITE);
}

void flushUserWroteoutWarning() {
	if(MouseX >= USER_BIKE_WROTEOUT_BUTTON1_X1 && MouseX <= USER_BIKE_WROTEOUT_BUTTON1_X2 && MouseY >= USER_BIKE_WROTEOUT_BUTTON1_Y1 && MouseY <= USER_BIKE_WROTEOUT_BUTTON1_Y2) {
		setcolor(MY_BLACK); setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
		rectangle(USER_BIKE_WROTEOUT_BUTTON1_X1 - 1, USER_BIKE_WROTEOUT_BUTTON1_Y1 - 1, USER_BIKE_WROTEOUT_BUTTON1_X2 + 1, USER_BIKE_WROTEOUT_BUTTON1_Y2 + 1);
		MouseS = 1;
	}
	else if (MouseX >= USER_BIKE_WROTEOUT_BUTTON2_X1 && MouseX <= USER_BIKE_WROTEOUT_BUTTON2_X2 && MouseY >= USER_BIKE_WROTEOUT_BUTTON2_Y1 && MouseY <= USER_BIKE_WROTEOUT_BUTTON2_Y2) {
	setcolor(MY_BLACK); setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	rectangle(USER_BIKE_WROTEOUT_BUTTON2_X1 - 1, USER_BIKE_WROTEOUT_BUTTON2_Y1 - 1, USER_BIKE_WROTEOUT_BUTTON2_X2 + 1, USER_BIKE_WROTEOUT_BUTTON2_Y2 + 1);
	MouseS = 1;
	}
	else {
	setcolor(MY_WHITE); setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	rectangle(USER_BIKE_WROTEOUT_BUTTON1_X1 - 1, USER_BIKE_WROTEOUT_BUTTON1_Y1 - 1, USER_BIKE_WROTEOUT_BUTTON1_X2 + 1, USER_BIKE_WROTEOUT_BUTTON1_Y2 + 1);
	rectangle(USER_BIKE_WROTEOUT_BUTTON2_X1 - 1, USER_BIKE_WROTEOUT_BUTTON2_Y1 - 1, USER_BIKE_WROTEOUT_BUTTON2_X2 + 1, USER_BIKE_WROTEOUT_BUTTON2_Y2 + 1);
	MouseS = 0;
	}
}
void flushUserWroteout(int* tag, user_button WroteoutButtons[]) {
	int i = 0;
	int temp = 0;
	int new_tag = ACTIVE_USER_NONE;
	for (i = 0; i < 5; i++) {
		if (MouseX >= WroteoutButtons[i].x1 && MouseX <= WroteoutButtons[i].x2 &&
			MouseY >= WroteoutButtons[i].y1 && MouseY <= WroteoutButtons[i].y2){
			new_tag = WroteoutButtons[i].active_tag;
			temp = i;
			break;
		}
	}

	for (i = 0; i <5; i++) {
		if (MouseX >= WroteoutButtons[i].x1 && MouseX <= WroteoutButtons[i].x2 &&
			MouseY >= WroteoutButtons[i].y1 && MouseY <= WroteoutButtons[i].y2){
			new_tag = WroteoutButtons[i].active_tag;
			temp = i;
			break;
		}
	}

	if (*tag != new_tag) {
		*tag = new_tag;
		if (new_tag != ACTIVE_USER_NONE) {
			setcolor(MY_BLACK);
			setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
			rectangle(WroteoutButtons[temp].x1, WroteoutButtons[temp].y1, WroteoutButtons[temp].x2, WroteoutButtons[temp].y2);
			MouseS = 1;
		}
		else {
			// 清除提示
			setcolor(MY_WHITE);
			setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
			for (i = 0; i < 5; i++) {
				rectangle(WroteoutButtons[i].x1, WroteoutButtons[i].y1, WroteoutButtons[i].x2, WroteoutButtons[i].y2);
			}
			MouseS = 0;
		}
	}

}

void user_quiz(int* page, unsigned long* id) {
	int i, j, k;
	int tag = -1;
	int box_tag = -1;
	int quiz_page = 1;
	char start_time[8];
	int remain_sec = LASTING_TIME;
	int tick=0;

	question test[QUIZ_PAGE_COUNT][QUESTION_PER_PAGE];
	char answer[QUIZ_PAGE_COUNT][QUESTION_PER_PAGE] = { '\0' };
	int result[QUIZ_PAGE_COUNT][QUESTION_PER_PAGE] = {'\0'};

	user_button quiz_buttons[] = {
		{USER_QUIZ_BUTTON1_X1, USER_QUIZ_BUTTON1_X2, USER_QUIZ_BUTTON1_Y1, USER_QUIZ_BUTTON1_Y2,1},
		{USER_QUIZ_BUTTON2_X1, USER_QUIZ_BUTTON2_X2, USER_QUIZ_BUTTON2_Y1, USER_QUIZ_BUTTON2_Y2,2},
		{USER_QUIZ_BUTTON3_X1, USER_QUIZ_BUTTON3_X2, USER_QUIZ_BUTTON3_Y1, USER_QUIZ_BUTTON3_Y2,3},
		{USER_QUIZ_EXIT_X1, USER_QUIZ_EXIT_X2, USER_QUIZ_EXIT_Y1, USER_QUIZ_EXIT_Y2,4},
		{USER_QUIZ_BACK_X1,USER_QUIZ_BACK_X2,USER_QUIZ_BACK_Y1,USER_QUIZ_BACK_Y2,5}
	};
	int mouse_flag = 1;

	for (i = 0; i < QUIZ_PAGE_COUNT; i++) {
		for (j = 0; j < 3; j++) {
			strcpy(test[i][j].main_text, "题干一二三四五六七八九十共十六字");
			for (k = 0; k < 4; k++) {
				strcpy(test[i][j].options[k], "选项一共七个字");
			}
			test[i][j].correctAnswer = 'A';
			test[i][j].id = 0;
			test[i][j].x = 60;
			test[i][j].y = 70 + 120 * j;
		}
	}

	//考试界面
	get_exact_time(start_time);
	clrmous(MouseX, MouseY);
	save_bk_mou(MouseX, MouseY);
	drawgraph_user_quiz(&quiz_page, QUIZ_PAGE_COUNT);
	draw_quiz(test[quiz_page-1], QUESTION_PER_PAGE);
	while (1) {
		user_newmouse_data(&MouseX, &MouseY, &press,&mouse_flag);
		flushUserQuiz(&tag,&box_tag,quiz_buttons,test[quiz_page-1],answer[quiz_page-1]);
		handle_click_quiz(test[quiz_page - 1], answer[quiz_page - 1], QUESTION_PER_PAGE);
		if (mouse_press(USER_QUIZ_BACK_X1, USER_QUIZ_BACK_Y1, USER_QUIZ_BACK_X2, USER_QUIZ_BACK_Y2) == 1) {
			delay(1000);
			*page = MAIN_USER;
			return;
		}
		if (mouse_press(USER_QUIZ_EXIT_X1, USER_QUIZ_EXIT_Y1, USER_QUIZ_EXIT_X2, USER_QUIZ_EXIT_Y2) == 1) {
			*page = EXIT;
			return;
		}
		//上一页
		if (mouse_press(USER_QUIZ_BUTTON1_X1, USER_QUIZ_BUTTON1_Y1, USER_QUIZ_BUTTON1_X2, USER_QUIZ_BUTTON1_Y2) == 1 && quiz_page != 1) {
			quiz_page -= 1;
			drawgraph_user_quiz(&quiz_page, QUIZ_PAGE_COUNT);
			draw_quiz(test[quiz_page-1], QUESTION_PER_PAGE);
			printbox(test[quiz_page - 1], answer[quiz_page - 1]);
		}
		//下一页
		if (mouse_press(USER_QUIZ_BUTTON2_X1, USER_QUIZ_BUTTON2_Y1, USER_QUIZ_BUTTON2_X2, USER_QUIZ_BUTTON2_Y2) == 1 && quiz_page != QUIZ_PAGE_COUNT) {
			quiz_page += 1;
			drawgraph_user_quiz(&quiz_page, QUIZ_PAGE_COUNT);
			draw_quiz(test[quiz_page-1], QUESTION_PER_PAGE);
			printbox(test[quiz_page - 1], answer[quiz_page - 1]);
		}
		//交卷
		if (mouse_press(USER_QUIZ_BUTTON3_X1, USER_QUIZ_BUTTON3_Y1, USER_QUIZ_BUTTON3_X2, USER_QUIZ_BUTTON3_Y2) == 1 || remain_sec == 0) {
			break;
		}
		//计时器
		if (tick % 20 == 0 && remain_sec!=0) 
			draw_countdown(remain_sec, 20, 450);
		if (tick % 40 == 0 && remain_sec!= 0) {
			tick = 0;
			remain_sec--;
		}
		tick++;
		user_drawmouse(&MouseX, &MouseY, &press, &mouse_flag);
		delay(25);
	}
	//结果界面
	if (judge_answer(test, answer, result, QUIZ_PAGE_COUNT)) {
		drawgraph_user_quiz_pass(result, QUIZ_PAGE_COUNT);
		//printf("%d%d%d%d%d%d", result[0][0], result[0][1], result[0][2], result[1][0], result[1][1], result[1][2]);
		while (1) {
			user_newmouse_data(&MouseX, &MouseY, &press, &mouse_flag);

			user_drawmouse(&MouseX, &MouseY, &press, &mouse_flag);
			delay(25);
		}
	}
	else
		return;
}
	

void drawgraph_user_quiz(int *quiz_page,int page_count) {
	char question_serial[8][8];//按页码储存题目序号，最多8页，不想在这malloc
	char quiz_page_string[10];//页码字符串
	int i;

	setfillstyle(SOLID_FILL,MY_LIGHTGRAY);
	bar(0, 0, 640, 480);
	setcolor(MY_WHITE);
	setfillstyle(1, MY_WHITE);
	bar(10,50,630,420);
	puthz(200, 12, "电动车法规测试", 32, 30, MY_WHITE);//边框

	for (i = 0; i < 3; i++) {                 //为题目序号赋值
		sprintf(question_serial[i], "%d", i + 1 + 3*(*quiz_page-1));
	}
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2); //输出题目序号
	setcolor(MY_BLACK);
	outtextxy(20, 70, question_serial[0]);
	outtextxy(20, 190,question_serial[1]);
	outtextxy(20, 310,question_serial[2]);

	setfillstyle(1, MY_RED);//退出红叉
	setcolor(MY_RED);
	bar(USER_QUIZ_EXIT_X1, USER_QUIZ_EXIT_Y1, USER_QUIZ_EXIT_X2, USER_QUIZ_EXIT_Y2);
	setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
	setcolor(MY_WHITE);
	line(USER_QUIZ_EXIT_X1, USER_QUIZ_EXIT_Y1, USER_QUIZ_EXIT_X2 - 1, USER_QUIZ_EXIT_Y2 - 1);
	line(USER_QUIZ_EXIT_X2 - 1, USER_QUIZ_EXIT_Y1, USER_QUIZ_EXIT_X1, USER_QUIZ_EXIT_Y2 - 1);

	setfillstyle(SOLID_FILL, MY_YELLOW);//离场
	bar(USER_QUIZ_BACK_X1, USER_QUIZ_BACK_Y1, USER_QUIZ_BACK_X2, USER_QUIZ_BACK_Y2);
	puthz(USER_QUIZ_BACK_X1 + 7, USER_QUIZ_BACK_Y1+5, "离场", 24, 25, MY_WHITE);

	setfillstyle(SOLID_FILL, MY_CREAM);//翻页
	if (*quiz_page != 1) {
		bar(USER_QUIZ_BUTTON1_X1, USER_QUIZ_BUTTON1_Y1, USER_QUIZ_BUTTON1_X2, USER_QUIZ_BUTTON1_Y2);
		puthz(USER_QUIZ_BUTTON1_X1 + 5, USER_QUIZ_BUTTON1_Y1 + 8, "上一页", 24, 20, MY_BLACK);
	}
	if (*quiz_page != page_count) {
		bar(USER_QUIZ_BUTTON2_X1, USER_QUIZ_BUTTON2_Y1, USER_QUIZ_BUTTON2_X2, USER_QUIZ_BUTTON2_Y2);
		puthz(USER_QUIZ_BUTTON2_X1 + 5, USER_QUIZ_BUTTON2_Y1 + 8, "下一页", 24, 20, MY_BLACK);
	}
	
	setcolor(MY_WHITE);//页码
	sprintf(quiz_page_string, "%d/%d", *quiz_page, page_count);
	outtextxy(260, 450, quiz_page_string);
	puthz(235, 443, "第", 24, 20, MY_WHITE);
	puthz(310, 443, "页", 24, 20, MY_WHITE);

	setfillstyle(SOLID_FILL, MY_RED);//交卷
	bar(USER_QUIZ_BUTTON3_X1, USER_QUIZ_BUTTON3_Y1, USER_QUIZ_BUTTON3_X2, USER_QUIZ_BUTTON3_Y2);
	puthz(USER_QUIZ_BUTTON3_X1 + 13, USER_QUIZ_BUTTON3_Y1 + 8, "交卷", 24, 20, MY_WHITE);
	
}



void flushUserQuiz(int* tag,int *box_tag, user_button UserButtons[], question quiz[], char* answer) {
	int i = 0;
	int temp = 0;
	int new_tag = ACTIVE_USER_NONE;
	int box_flag = FlushQuiz(quiz, 3,box_tag);//鼠标是否在选项框位置

	if (box_flag)
		new_tag = 6;//选项框活跃标签
	for (i = 0; i < 5; i++) {
		if (MouseX >= UserButtons[i].x1 && MouseX <= UserButtons[i].x2 &&
			MouseY >= UserButtons[i].y1 && MouseY <= UserButtons[i].y2) {
			new_tag = UserButtons[i].active_tag;
			temp = i;
			break;
		}
	}
	
	if (*tag != new_tag) {
		*tag = new_tag;
		if (new_tag != ACTIVE_USER_NONE && new_tag <= 3) {//上一页，下一页，交卷按钮
			setfillstyle(1, MY_WHITE);
			setcolor(MY_BLACK);
			setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
			rectangle(UserButtons[temp].x1+1, UserButtons[temp].y1+1, UserButtons[temp].x2+1, UserButtons[temp].y2+1);
			MouseS = 1;
		}
		else if (new_tag == 4) {//退出程序
			setfillstyle(1, MY_WHITE);
			setcolor(MY_WHITE);
			setlinestyle(SOLID_LINE, 0,THICK_WIDTH);
			rectangle(UserButtons[temp].x1, UserButtons[temp].y1, UserButtons[temp].x2, UserButtons[temp].y2);
			MouseS = 1;
		}
		else if (new_tag == 5) {//返回主界面（离场）
			setcolor(MY_RED);
			setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
			setfillstyle(1, MY_RED);
			bar(USER_QUIZ_BACK_X1, USER_QUIZ_BACK_Y1, USER_QUIZ_BACK_X2, USER_QUIZ_BACK_Y2);
			puthz(USER_QUIZ_BACK_X1 + 7, USER_QUIZ_BACK_Y1 + 6, "离场", 24, 25, MY_WHITE);
			MouseS = 1;
		}
		else if (new_tag==6||new_tag==0) {//鼠标不在按钮上（在选项框或空白）
			// 清除提示
			setcolor(MY_LIGHTGRAY);
			setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
			for (i = 0; i < 3; i++) {
				rectangle(UserButtons[i].x1+1, UserButtons[i].y1+1, UserButtons[i].x2+1, UserButtons[i].y2+1);
			}

			setfillstyle(1, MY_YELLOW);//恢复“返回登录”
			setcolor(MY_YELLOW);
			bar(USER_QUIZ_BACK_X1, USER_QUIZ_BACK_Y1, USER_QUIZ_BACK_X2, USER_QUIZ_BACK_Y2);
			puthz(USER_QUIZ_BACK_X1 + 7, USER_QUIZ_BACK_Y1 + 6, "离场", 24, 25, MY_WHITE);

			setcolor(MY_RED);
			setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
			rectangle(USER_QUIZ_EXIT_X1, USER_QUIZ_EXIT_Y1, USER_QUIZ_EXIT_X2, USER_QUIZ_EXIT_Y2);
			if(new_tag==0)
				MouseS = 0;//空白处鼠标为箭头；选项框处鼠标形式在FlushQuiz中已处理，此处无须赋值
		}
	}
	
}

void drawgraph_user_quiz_pass(int result[][QUESTION_PER_PAGE],int page_count) {
	int i,j;
	int correct_num=0;
	float correct_rate;
	char correct_num_string[16];
	char correct_rate_string[16];

	for (i = 0; i < page_count; i++) {
		for (j = 0; j < QUESTION_PER_PAGE; j++) {
			if (result[i][j] == 1)
				correct_num++;
		}
	}
	correct_rate = (float)correct_num / (page_count * QUESTION_PER_PAGE);
	sprintf(correct_num_string, "%d/%d", correct_num, page_count * QUESTION_PER_PAGE);
	sprintf(correct_rate_string, "%.2f%%", correct_rate);

	setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
	bar(0, 0, 640, 480);
	setcolor(MY_WHITE);
	setfillstyle(1, MY_WHITE);
	bar(10, 50, 630, 470);
	puthz(200, 12, "电动车法规测试", 32, 30, MY_WHITE);//边框

	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2); //输出题目序号
	setcolor(MY_BLACK);
	puthz(100, 100, "答对了：", 24, 20, MY_BLACK);
	outtextxy(200, 100, correct_num_string);
	outtextxy(300, 100, correct_rate_string);
}


/*
之前的newmouse函数中更新鼠标数据与保存鼠标目前位置的背景同时进行，因此在flush函数们改变背景时，鼠标保存的背景没有改变，导致按钮边框缺失一小块或有一小块颜色不对
现在先使用user_newmouse_data更新鼠标数据，在运行flush函数改变背景后，用user_drawmouse保存背景并绘制鼠标，保证在user_drawmouse时*buffer中保存的背景正确。
*/


void user_newmouse_data(int* nx, int* ny, int* nbuttons,int *flag)//更新鼠标数据并判断鼠标位置是否改变
{
	int xn, yn, buttonsn;
	int x0 = *nx, y0 = *ny, buttons0 = *nbuttons;
	mread(&xn, &yn, &buttonsn);
	*nx = xn;
	*ny = yn;
	*nbuttons = buttonsn;
	if (buttons0 == *nbuttons)
		*nbuttons = 0;    //使得能连续按键
	if (xn == x0 && yn == y0 && buttonsn == buttons0) {
		*flag = 0;//不变
		return;
	}
	clrmous(x0, y0);
	*flag = 1;//改变
	return ;
}


void user_drawmouse(int* nx, int* ny, int* nbuttons,int* flag) //若鼠标位置改变，保存背景，绘制鼠标
{
	if (*flag) {
		save_bk_mou(*nx, *ny);
		drawmous(*nx, *ny);
	}	
}

void user_info()
{
	
}

void user_message()
{
	
}

void user_datagraph()
{

}


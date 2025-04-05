#include"USER.H"

void user_main(int *page) {
	int tag = 0;
	int click = -1;
	user_button UserButtons[] = {
{USER_BIKE_REGISTER_X1, USER_BIKE_REGISTER_X2,
USER_BIKE_REGISTER_Y1, USER_BIKE_REGISTER_Y2,
ACTIVE_USER_BIKE_REGISTER,USER_BIKE_REGISTER},

{USER_BIKE_LICENSE_X1, USER_BIKE_LICENSE_X2,
		USER_BIKE_LICENSE_Y1, USER_BIKE_LICENSE_Y2,
		ACTIVE_USER_BIKE_LICENSE,USER_BIKE_LICENSE},

{USER_BIKE_ANUAL_X1, USER_BIKE_ANUAL_X2,
USER_BIKE_ANUAL_Y1, USER_BIKE_ANUAL_Y2,
ACTIVE_USER_BIKE_ANUAL,USER_BIKE_ANUAL},

{USER_BIKE_WROTEOUT_X1, USER_BIKE_WROTEOUT_X2,
USER_BIKE_WROTEOUT_Y1, USER_BIKE_WROTEOUT_Y2,
ACTIVE_USER_BIKE_WROTEOUT,USER_BIKE_WROTEOUT},

{USER_INFO_X1, USER_INFO_X2,
USER_INFO_Y1, USER_INFO_Y2,
ACTIVE_USER_INFO,USER_INFO},

{USER_MESSAGE_X1, USER_MESSAGE_X2,
USER_MESSAGE_Y1, USER_MESSAGE_Y2,
ACTIVE_USER_MESSAGE,USER_MESSAGE},

{USER_DATAGRAPH_X1, USER_DATAGRAPH_X2,
USER_DATAGRAPH_Y1, USER_DATAGRAPH_Y2,
ACTIVE_USER_DATAGRAPH,USER_DATAGRAPH},

{USER_BACK_X1,USER_BACK_X2,USER_BACK_Y1,USER_BACK_Y2,ACTIVE_USER_BACK,LOGIN},
{USER_EXIT_X1,USER_EXIT_X2,USER_EXIT_Y1,USER_EXIT_Y2,ACTIVE_USER_EXIT,EXIT},
};
	clrmous(MouseX, MouseY);
	save_bk_mou(MouseX, MouseY);
	drawgraph_user_main(page);
	
	while (1) {
			flushUserMain(&tag, STRUCT_LENGTH(UserButtons), UserButtons); // 刷新界面
			newmouse(&MouseX, &MouseY, &press); // 刷新鼠标
			click = handle_click_main(STRUCT_LENGTH(UserButtons), UserButtons);
			if (click == LOGIN || click == EXIT||click==USER_BIKE_REGISTER) {          //其它页面做完后此处会改成click!=-1&&click!=USER_BIKE_REGISTER
				*page = click;
				return;
			}
			/*if (mouse_press(USER_BACK_X1, USER_BACK_Y1, USER_BACK_X2, USER_BACK_Y2) == 1) {
				*page = LOGIN;
				clrmous(MouseX, MouseY);
				return;
			}
			else if (mouse_press(USER_EXIT_X1, USER_EXIT_Y1, USER_EXIT_X2, USER_EXIT_Y2) == 1) {
				*page = EXIT;
				clrmous(MouseX, MouseY);
				return;
			}
			else if (mouse_press(USER_BIKE_REGISTER_X1, USER_BIKE_REGISTER_Y1, USER_BIKE_REGISTER_X2, USER_BIKE_REGISTER_Y2) == 1) {
				*page = USER_BIKE_REGISTER;
				//clrmous(MouseX, MouseY);
				return;
			}*/
			delay(25);//
	}
}

void drawgraph_user_main(int *page) {
	setrgbpalette(MY_LIGHTBLUE, 12, 158, 245);//浅蓝背景-1
	setrgbpalette(MY_LIGHTGRAY, 235, 235, 235);//浅灰框-1
	setrgbpalette(MY_BLACK, 0, 0, 0);//黑色
	setrgbpalette(MY_YELLOW, 240, 230, 75);//黄色
	setrgbpalette(MY_RED, 255, 0, 0);//红色
	setrgbpalette(MY_WHITE, 255, 255, 255);//白色
	

	setbkcolor(MY_LIGHTBLUE);//主界面
	setfillstyle(1, 0);
	setcolor(MY_LIGHTBLUE);
	bar(0, 0, 640, 480);
	puthz(120, 10, "校园自行车管理系统", 48, 45, MY_WHITE);
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

	/*setcolor(MY_WHITE);//功能按钮
	rectangle(USER_BIKE_REGISTER_X1, USER_BIKE_REGISTER_Y1, USER_BIKE_REGISTER_X2, USER_BIKE_REGISTER_Y2);
	rectangle(USER_BIKE_LICENSE_X1, USER_BIKE_LICENSE_Y1, USER_BIKE_LICENSE_X2, USER_BIKE_LICENSE_Y2);
	rectangle(USER_BIKE_ANUAL_X1, USER_BIKE_ANUAL_Y1, USER_BIKE_ANUAL_X2, USER_BIKE_ANUAL_Y2);
	rectangle(USER_BIKE_WROTEOUT_X1, USER_BIKE_WROTEOUT_Y1, USER_BIKE_WROTEOUT_X2, USER_BIKE_WROTEOUT_Y2);
	rectangle(USER_BIKE_ANUAL_X1, USER_BIKE_ANUAL_Y1, USER_BIKE_ANUAL_X2, USER_BIKE_ANUAL_Y2);
	rectangle(USER_DATAGRAPH_X1, USER_DATAGRAPH_Y1, USER_DATAGRAPH_X2, USER_DATAGRAPH_Y2);
	rectangle(USER_INFO_X1, USER_INFO_Y1, USER_INFO_X2, USER_INFO_Y2);
	rectangle(USER_MESSAGE_X1, USER_MESSAGE_Y1, USER_MESSAGE_X2,USER_MESSAGE_Y2);*/

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
	puthz(USER_BIKE_LICENSE_X1 + 15, (USER_BIKE_LICENSE_Y1 + USER_BIKE_LICENSE_Y2) / 2-5, "电动车牌照", 24, 25, MY_WHITE);
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
			puthz(USER_BIKE_LICENSE_X1 + 15, (USER_BIKE_LICENSE_Y1 + USER_BIKE_LICENSE_Y2) / 2 - 5, "电动车通行证", 24, 25, MY_BLACK);
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
			puthz(USER_INFO_X1 + 15, (USER_INFO_Y1 + USER_INFO_Y2) / 2 - 5, "用户信息管理", 24, 25, MY_BLACK);
			break;
		case USER_MESSAGE:
			setcolor(MY_WHITE);
			setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
			setfillstyle(1, MY_WHITE);
			bar(USER_MESSAGE_X1, USER_MESSAGE_Y1, USER_MESSAGE_X2, USER_MESSAGE_Y2);
			puthz(USER_MESSAGE_X1 + 15, (USER_MESSAGE_Y1 + USER_MESSAGE_Y2) / 2 - 5, "消息中心", 24, 25, MY_WHITE);
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
		// 清除提示
		setcolor(MY_LIGHTGRAY);
		setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
		for (i = 0; i < button_count-2; i++) {
			rectangle(UserButtons[i].x1, UserButtons[i].y1, UserButtons[i].x2, UserButtons[i].y2);
		}

		/*setcolor(MY_LIGHTBLUE); //恢复退出红叉
		setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
		setfillstyle(1, MY_LIGHTBLUE);
		bar(0, 0, 79, 59);
		setcolor(MY_RED);
		setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
		setfillstyle(1, MY_RED);
		bar(USER_EXIT_X1, USER_EXIT_Y1, USER_EXIT_X2, USER_EXIT_Y2);
		setcolor(MY_WHITE);
		line(USER_EXIT_X1, USER_EXIT_Y1, USER_EXIT_X2 - 1, USER_EXIT_Y2 - 1);
		line(USER_EXIT_X2 - 1, USER_EXIT_Y1, USER_EXIT_X1, USER_EXIT_Y2 - 1);*/

		setfillstyle(1, MY_YELLOW);//恢复“返回登录”
		setcolor(MY_YELLOW);
		bar(USER_BACK_X1, USER_BACK_Y1, USER_BACK_X2, USER_BACK_Y2);
		puthz(USER_BACK_X1 + 5, (USER_BACK_Y1 + USER_BACK_Y2) / 2 - 10, "返回", 24, 25, MY_WHITE);

		setcolor(MY_RED);
		setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
		rectangle(USER_EXIT_X1,USER_EXIT_Y1,USER_EXIT_X2,USER_EXIT_Y2);

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
	char usrn[16] = {'\0'}; // 初始化为空
	char e_bike_id[10] = {'\0'};
	user_button UserButtons[] = {
{USER_BIKE_REGISTER_X1, USER_BIKE_REGISTER_X2,
USER_BIKE_REGISTER_Y1, USER_BIKE_REGISTER_Y2,
ACTIVE_USER_BIKE_REGISTER},

{USER_BIKE_LICENSE_X1, USER_BIKE_LICENSE_X2,
		USER_BIKE_LICENSE_Y1, USER_BIKE_LICENSE_Y2,
		ACTIVE_USER_BIKE_LICENSE},

{USER_BIKE_ANUAL_X1, USER_BIKE_ANUAL_X2,
USER_BIKE_ANUAL_Y1, USER_BIKE_ANUAL_Y2,
ACTIVE_USER_BIKE_ANUAL},

{USER_BIKE_WROTEOUT_X1, USER_BIKE_WROTEOUT_X2,
USER_BIKE_WROTEOUT_Y1, USER_BIKE_WROTEOUT_Y2,
ACTIVE_USER_BIKE_WROTEOUT},

{USER_INFO_X1, USER_INFO_X2,
USER_INFO_Y1, USER_INFO_Y2,
ACTIVE_USER_INFO},

{USER_MESSAGE_X1, USER_MESSAGE_X2,
USER_MESSAGE_Y1, USER_MESSAGE_Y2,
ACTIVE_USER_MESSAGE},

{USER_DATAGRAPH_X1, USER_DATAGRAPH_X2,
USER_DATAGRAPH_Y1, USER_DATAGRAPH_Y2,
ACTIVE_USER_DATAGRAPH},

{USER_BACK_X1,USER_BACK_X2,USER_BACK_Y1,USER_BACK_Y2,ACTIVE_USER_BACK,LOGIN},
{USER_EXIT_X1,USER_EXIT_X2,USER_EXIT_Y1,USER_EXIT_Y2,ACTIVE_USER_EXIT,EXIT},
	};
	clrmous(MouseX, MouseY);
	save_bk_mou(MouseX, MouseY);
	drawgraph_user_main(page);

	if (!ebike_user_judge(id)){
		setfillstyle(SOLID_FILL, MY_WHITE);
		bar(150, 60, 640, 480);
		puthz(280, 260, "您已注册过电动车", 32, 40, MY_BLACK);
		delay(3000);
		*page = MAIN_USER;
		return;
	}
	drawgraph_user_bike_register();
	while (1) {
		flushUserMain(&tag, STRUCT_LENGTH(UserButtons), UserButtons); // 刷新界面
		flushUserRegister(&tag);
		newmouse(&MouseX, &MouseY, &press);
		click = handle_click_main(STRUCT_LENGTH(UserButtons), UserButtons);
		if (click == LOGIN || click==EXIT) {          //其它页面做完后此处会改成click!=-1&&click!=USER_BIKE_REGISTER
			*page = click;
			return;
		}//菜单界面点击
		if (mouse_press(USER_BIKE_REGISTER_INPUT1_X1, USER_BIKE_REGISTER_INPUT1_Y1, USER_BIKE_REGISTER_INPUT1_X2, USER_BIKE_REGISTER_INPUT1_Y2) == 1) {
			Input_Bar(usrn, USER_BIKE_REGISTER_INPUT1_X1, USER_BIKE_REGISTER_INPUT1_Y1 + 5, 13, MY_WHITE, 0, 1);
		}
		if (mouse_press(USER_BIKE_REGISTER_INPUT2_X1, USER_BIKE_REGISTER_INPUT2_Y1, USER_BIKE_REGISTER_INPUT2_X2, USER_BIKE_REGISTER_INPUT2_Y2) == 1) {
			Input_Bar(e_bike_id, USER_BIKE_REGISTER_INPUT2_X1, USER_BIKE_REGISTER_INPUT2_Y1 + 5, 13, MY_WHITE, 0, 1);
		}

		if (mouse_press(USER_BIKE_REGISTER_BUTTON1_X1, USER_BIKE_REGISTER_BUTTON1_Y1, USER_BIKE_REGISTER_BUTTON1_X2, USER_BIKE_REGISTER_BUTTON1_Y2) == 1) {
			register_flag = EBIKE_INFO_judge(usrn, e_bike_id,id);
			if (register_flag == 0) {
				anime_login_success_user();
				setfillstyle(SOLID_FILL, MY_WHITE);
				bar(150, 60, 640, 480);
				Input_Bar(NULL, NULL, NULL, NULL, NULL, 1, NULL);
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
int ebike_user_judge(unsigned long *ID) {
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
	strcpy(TEMP.ebike_license, "license");
	strcpy(TEMP.location, "location");
	TEMP.ID =*id;
	TEMP.apply_time =43;
	TEMP.conduct_time = -1;
	TEMP.result = -1;
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

void drawgraph_user_bike_register() {
	
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

void user_bike_license()
{
	
}

void user_bike_anual()
{

}

void user_bike_wroteout()
{

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


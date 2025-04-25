#include"USER.H"


//用户主界面

void user_main(int *page) {
	int tag = 0;
	int click = -99;
	int i;
	int mouse_flag;
	user_button UserButtons[] = {
{USER_BIKE_REGISTER_X1, USER_BIKE_REGISTER_X2,USER_BIKE_REGISTER_Y1, USER_BIKE_REGISTER_Y2,ACTIVE_USER_BIKE_REGISTER,USER_BIKE_REGISTER},
{USER_BIKE_LICENSE_X1, USER_BIKE_LICENSE_X2,USER_BIKE_LICENSE_Y1, USER_BIKE_LICENSE_Y2,ACTIVE_USER_BIKE_LICENSE,USER_BIKE_LICENSE_NOTICE},
{USER_ANNUAL_X1, USER_ANNUAL_X2,USER_ANNUAL_Y1, USER_ANNUAL_Y2,ACTIVE_USER_ANNUAL,USER_ANNUAL},
{USER_BIKE_WROTEOUT_X1, USER_BIKE_WROTEOUT_X2,USER_BIKE_WROTEOUT_Y1, USER_BIKE_WROTEOUT_Y2,ACTIVE_USER_BIKE_WROTEOUT,USER_BIKE_WROTEOUT},
{USER_INFO_X1, USER_INFO_X2,USER_INFO_Y1, USER_INFO_Y2,ACTIVE_USER_INFO,USER_INFO},
{USER_MESSAGE_X1, USER_MESSAGE_X2,USER_MESSAGE_Y1, USER_MESSAGE_Y2,ACTIVE_USER_MESSAGE,USER_MESSAGE},
{USER_HELP_X1, USER_HELP_X2,USER_HELP_Y1, USER_HELP_Y2,ACTIVE_USER_HELP,USER_HELP},
{USER_BACK_X1,USER_BACK_X2,USER_BACK_Y1,USER_BACK_Y2,ACTIVE_USER_BACK,LOGIN},
{USER_EXIT_X1,USER_EXIT_X2,USER_EXIT_Y1,USER_EXIT_Y2,ACTIVE_USER_EXIT,EXIT},
	};
	
	
	clrmous(MouseX, MouseY);
	save_bk_mou(MouseX, MouseY);

	drawgraph_user_main(page);
	

	while (1) {
			newmouse_data(&MouseX, &MouseY, &press, &mouse_flag);
			flushUserMain(&tag, STRUCT_LENGTH(UserButtons), UserButtons); // 刷新界面
			click = handle_click_main(STRUCT_LENGTH(UserButtons), UserButtons);
			if (click!=-99) {          //其它页面做完后此处会改成click!=-1&&click!=USER_BIKE_REGISTER
				*page = click;
				newmouse(&MouseX, &MouseY, &press, &mouse_flag);
				return;
			}
			newmouse(&MouseX, &MouseY, &press, &mouse_flag);
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
	puthz(USER_ANNUAL_X1+ 15, (USER_ANNUAL_Y1 + USER_ANNUAL_Y2) / 2-5, "电动车年审", 24, 25, MY_WHITE);
	puthz(USER_BIKE_LICENSE_X1 + 5, (USER_BIKE_LICENSE_Y1 + USER_BIKE_LICENSE_Y2) / 2-5, "电动车通行证", 24, 22, MY_WHITE);
	puthz(USER_BIKE_WROTEOUT_X1 + 15, (USER_BIKE_WROTEOUT_Y1 + USER_BIKE_WROTEOUT_Y2) / 2 - 5, "电动车报废", 24, 25, MY_WHITE);
	puthz(USER_INFO_X1 + 5, (USER_INFO_Y1 + USER_INFO_Y2) / 2 - 5, "用户信息管理", 24, 22, MY_WHITE);
	puthz(USER_MESSAGE_X1 + 15, (USER_MESSAGE_Y1 + USER_MESSAGE_Y2) / 2 - 5, "信息中心", 24, 25, MY_WHITE);
	puthz(USER_HELP_X1+ 15, (USER_HELP_Y1 + USER_HELP_Y2) / 2 - 5, "公告与帮助", 24, 25, MY_WHITE);
	puthz(USER_BACK_X1 + 5, (USER_BACK_Y1 + USER_BACK_Y2) / 2 - 10, "返回", 24, 25, MY_WHITE);

	switch (*page) {
		case USER_ANNUAL:
			setcolor(MY_WHITE);
			setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
			setfillstyle(1, MY_WHITE);
			bar(USER_ANNUAL_X1, USER_ANNUAL_Y1, USER_ANNUAL_X2, USER_ANNUAL_Y2);
			puthz(USER_ANNUAL_X1 + 15, (USER_ANNUAL_Y1 + USER_ANNUAL_Y2) / 2 - 5, "电动车年审", 24, 25, MY_BLACK);
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
		case USER_HELP:
			setcolor(MY_WHITE);
			setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
			setfillstyle(1, MY_WHITE);
			bar(USER_HELP_X1, USER_HELP_Y1, USER_HELP_X2, USER_HELP_Y2);
			puthz(USER_HELP_X1 + 15, (USER_HELP_Y1 + USER_HELP_Y2) / 2 - 5, "公告与帮助", 24, 25, MY_BLACK);
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
			puthz(USER_MESSAGE_X1 + 5, (USER_MESSAGE_Y1 + USER_MESSAGE_Y2) / 2 - 5, "消息中心", 24, 25, MY_BLACK);
			break;
		case USER_MESSAGE_OUT:
			setcolor(MY_WHITE);
			setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
			setfillstyle(1, MY_WHITE);
			bar(USER_MESSAGE_X1, USER_MESSAGE_Y1, USER_MESSAGE_X2, USER_MESSAGE_Y2);
			puthz(USER_MESSAGE_X1 + 5, (USER_MESSAGE_Y1 + USER_MESSAGE_Y2) / 2 - 5, "消息中心", 24, 25, MY_BLACK);
		break;
		case USER_BIKE_LICENSE_NOTICE:
			setcolor(MY_WHITE);
			setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
			setfillstyle(1, MY_WHITE);
			bar(USER_BIKE_LICENSE_X1, USER_BIKE_LICENSE_Y1, USER_BIKE_LICENSE_X2, USER_BIKE_LICENSE_Y2);
			puthz(USER_BIKE_LICENSE_X1 + 5, (USER_BIKE_LICENSE_Y1 + USER_BIKE_LICENSE_Y2) / 2 - 5, "电动车通行证", 24, 22, MY_BLACK);
			break;
		case USER_INFO_ACCOUNT:
			setcolor(MY_WHITE);
			setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
			setfillstyle(1, MY_WHITE);
			bar(USER_INFO_X1, USER_INFO_Y1, USER_INFO_X2, USER_INFO_Y2);
			puthz(USER_INFO_X1 + 15, (USER_INFO_Y1 + USER_INFO_Y2) / 2 - 5, "用户信息管理", 24, 22, MY_BLACK);
			break;
		case USER_INFO_BIKEINFO:
			setcolor(MY_WHITE);
			setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
			setfillstyle(1, MY_WHITE);
			bar(USER_INFO_X1, USER_INFO_Y1, USER_INFO_X2, USER_INFO_Y2);
			puthz(USER_INFO_X1 + 15, (USER_INFO_Y1 + USER_INFO_Y2) / 2 - 5, "用户信息管理", 24, 22, MY_BLACK);
			break;
		case USER_INFO_BIKEDATA:
			setcolor(MY_WHITE);
			setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
			setfillstyle(1, MY_WHITE);
			bar(USER_INFO_X1, USER_INFO_Y1, USER_INFO_X2, USER_INFO_Y2);
			puthz(USER_INFO_X1 + 15, (USER_INFO_Y1 + USER_INFO_Y2) / 2 - 5, "用户信息管理", 24, 22, MY_BLACK);
			break;
		
	}
	
	
}


//刷新主界面鼠标激活状态
void flushUserMain(int *tag,int button_count,user_button UserButtons[]) { 
	int i = 0;
	int temp = 0;
	int new_tag = ACTIVE_USER_NONE;
	
	
	
for (i = 0; i < button_count; i++) {
	if (MouseX >= UserButtons[i].x1 && MouseX <= UserButtons[i].x2 &&
		MouseY >= UserButtons[i].y1 && MouseY <= UserButtons[i].y2) {
		new_tag = UserButtons[i].active_tag;
		MouseS = 1;
		temp = i; 
		break;
	}
}

if (*tag != new_tag) {
	if (*tag != ACTIVE_USER_NONE) {
		if (*tag <= ACTIVE_USER_HELP) {
			setcolor(MY_LIGHTGRAY);
			setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
			rectangle(UserButtons[*tag-1].x1, UserButtons[*tag-1].y1, UserButtons[*tag-1].x2, UserButtons[*tag-1].y2);
			
		}
		else if (*tag == ACTIVE_USER_EXIT) {
			setcolor(MY_RED);
			setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
			rectangle(USER_EXIT_X1, USER_EXIT_Y1, USER_EXIT_X2, USER_EXIT_Y2);
			
		}
		else if (*tag == ACTIVE_USER_BACK) {
			setfillstyle(1, MY_YELLOW);//恢复“返回登录”
			setcolor(MY_YELLOW);
			bar(USER_BACK_X1, USER_BACK_Y1, USER_BACK_X2, USER_BACK_Y2);
			puthz(USER_BACK_X1 + 5, (USER_BACK_Y1 + USER_BACK_Y2) / 2 - 10, "返回", 24, 25, MY_WHITE);
			
		}
	}
	*tag = new_tag;
	if (new_tag != ACTIVE_USER_NONE && new_tag<=ACTIVE_USER_HELP) {
		setfillstyle(1,MY_WHITE);
		setcolor(MY_WHITE);
		setlinestyle(SOLID_LINE,0,THICK_WIDTH);
		rectangle(UserButtons[temp].x1, UserButtons[temp].y1, UserButtons[temp].x2, UserButtons[temp].y2);
		
	}
	else if (new_tag == ACTIVE_USER_EXIT) {
		setfillstyle(1, MY_WHITE);
		setcolor(MY_WHITE);
		setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
		rectangle(UserButtons[temp].x1, UserButtons[temp].y1, UserButtons[temp].x2, UserButtons[temp].y2);
		
	}
	else if (new_tag == ACTIVE_USER_BACK) {
		setcolor(MY_RED);
		setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
		setfillstyle(1, MY_RED);
		bar(USER_BACK_X1, USER_BACK_Y1, USER_BACK_X2, USER_BACK_Y2);
		puthz(USER_BACK_X1 + 5, USER_BACK_Y1 + 5, "返回", 24, 25, MY_WHITE);
		
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


//处理主界面鼠标点击
int handle_click_main(int button_num, user_button UserButtons[]){
	int i = 0;
	for (i = 0; i < button_num; i++) {
		if (mouse_press(UserButtons[i].x1, UserButtons[i].y1, UserButtons[i].x2, UserButtons[i].y2) == 1) 
			return UserButtons[i].page;
	}	
	return -99;
}











//电动车注册界面

void user_bike_register(LINKLIST *LIST,int* page, unsigned long* id)
{
	int tag = 0;
	int register_flag ;
	int click = -1;
	int mouse_flag;
	char usrn[16] = {'\0'}; // 初始化为空
	int hz_input_len[2] = {0,0};//汉字输入框的汉字数量
	char e_bike_id[10] = {'\0'};
	char color[10] = {'-','\0'};
	char length[10]= { '-','\0' };
	char weight[10]= { '-','\0' };
	char battery[10]= { '-','\0' };
	user_button UserButtons[] = {
{USER_BIKE_REGISTER_X1, USER_BIKE_REGISTER_X2,USER_BIKE_REGISTER_Y1, USER_BIKE_REGISTER_Y2,ACTIVE_USER_BIKE_REGISTER,USER_BIKE_REGISTER},
{USER_BIKE_LICENSE_X1, USER_BIKE_LICENSE_X2,USER_BIKE_LICENSE_Y1, USER_BIKE_LICENSE_Y2,ACTIVE_USER_BIKE_LICENSE,USER_BIKE_LICENSE_NOTICE},
{USER_ANNUAL_X1, USER_ANNUAL_X2,USER_ANNUAL_Y1, USER_ANNUAL_Y2,ACTIVE_USER_ANNUAL,USER_ANNUAL},
{USER_BIKE_WROTEOUT_X1, USER_BIKE_WROTEOUT_X2,USER_BIKE_WROTEOUT_Y1, USER_BIKE_WROTEOUT_Y2,ACTIVE_USER_BIKE_WROTEOUT,USER_BIKE_WROTEOUT},
{USER_INFO_X1, USER_INFO_X2,USER_INFO_Y1, USER_INFO_Y2,ACTIVE_USER_INFO,USER_INFO},
{USER_MESSAGE_X1, USER_MESSAGE_X2,USER_MESSAGE_Y1, USER_MESSAGE_Y2,ACTIVE_USER_MESSAGE,USER_MESSAGE},
{USER_HELP_X1, USER_HELP_X2,USER_HELP_Y1, USER_HELP_Y2,ACTIVE_USER_HELP,USER_HELP},
{USER_BACK_X1,USER_BACK_X2,USER_BACK_Y1,USER_BACK_Y2,ACTIVE_USER_BACK,LOGIN},
{USER_EXIT_X1,USER_EXIT_X2,USER_EXIT_Y1,USER_EXIT_Y2,ACTIVE_USER_EXIT,EXIT},
	};
	clrmous(MouseX, MouseY);
	save_bk_mou(MouseX, MouseY);
	drawgraph_user_main(page);


	if (!user_ebike_register_judge(LIST,id)) {
		setfillstyle(SOLID_FILL, MY_WHITE);
		bar(150, 60, 640, 480);
		drawgraph_user_bike_register_info(LIST,id);
		clrmous(MouseX, MouseY);
		save_bk_mou(MouseX, MouseY);
		while (1) {
			newmouse_data(&MouseX, &MouseY, &press,&mouse_flag);
			flushUserMain(&tag, STRUCT_LENGTH(UserButtons), UserButtons); // 刷新界面
			click = handle_click_main(STRUCT_LENGTH(UserButtons), UserButtons);
			if (click != -99 && click!= USER_BIKE_REGISTER){          
				*page = click;
				newmouse(&MouseX, &MouseY, &press, &mouse_flag);
				return;
			}
			newmouse(&MouseX, &MouseY, &press, &mouse_flag);
			delay(25);
		}
	}
	drawgraph_user_bike_register_new();
	while (1) {
		newmouse_data(&MouseX, &MouseY, &press, &mouse_flag);
		flushUserMain(&tag, STRUCT_LENGTH(UserButtons), UserButtons); // 刷新界面
		flushUserRegister(&tag);
		click = handle_click_main(STRUCT_LENGTH(UserButtons), UserButtons);
		if (click !=USER_BIKE_REGISTER && click !=-99) {          //其它页面做完后此处会改成click!=-1&&click!=USER_BIKE_REGISTER
			*page = click;
			return;
		}//菜单界面点击
		if (mouse_press(USER_BIKE_REGISTER_INPUT1_X1, USER_BIKE_REGISTER_INPUT1_Y1, USER_BIKE_REGISTER_INPUT1_X2, USER_BIKE_REGISTER_INPUT1_Y2) == 1) {
			hz_input_len[0] = hz_input(USER_BIKE_REGISTER_INPUT1_X1 + 3, USER_BIKE_REGISTER_INPUT1_Y1 + 3, USER_BIKE_REGISTER_INPUT1_X2, USER_BIKE_REGISTER_INPUT1_Y2, usrn, hz_input_len[0], MY_WHITE, MY_BLACK, 24);
		}
		if (mouse_press(USER_BIKE_REGISTER_INPUT2_X1, USER_BIKE_REGISTER_INPUT2_Y1, USER_BIKE_REGISTER_INPUT2_X2, USER_BIKE_REGISTER_INPUT2_Y2) == 1) {
			ch_input(e_bike_id, USER_BIKE_REGISTER_INPUT2_X1, USER_BIKE_REGISTER_INPUT2_Y1 + 5, 13, MY_WHITE, 0, 1);
		}
		if (mouse_press(USER_BIKE_REGISTER_INPUT4_X1, USER_BIKE_REGISTER_INPUT4_Y1, USER_BIKE_REGISTER_INPUT4_X2, USER_BIKE_REGISTER_INPUT4_Y2) == 1) {
			ch_input(weight, USER_BIKE_REGISTER_INPUT4_X1, USER_BIKE_REGISTER_INPUT4_Y1+5, 4, MY_WHITE, 0, 1);
		}
		if (mouse_press(USER_BIKE_REGISTER_INPUT3_X1, USER_BIKE_REGISTER_INPUT3_Y1, USER_BIKE_REGISTER_INPUT3_X2, USER_BIKE_REGISTER_INPUT3_Y2)  == 1) {
			hz_input_len[1] = hz_input(USER_BIKE_REGISTER_INPUT3_X1 + 3, USER_BIKE_REGISTER_INPUT3_Y1 + 3, USER_BIKE_REGISTER_INPUT3_X2, USER_BIKE_REGISTER_INPUT3_Y2, color, hz_input_len[1], MY_WHITE, MY_BLACK, 24);
		}
		if (mouse_press(USER_BIKE_REGISTER_INPUT5_X1, USER_BIKE_REGISTER_INPUT5_Y1, USER_BIKE_REGISTER_INPUT5_X2, USER_BIKE_REGISTER_INPUT5_Y2) == 1) {
			ch_input(length,USER_BIKE_REGISTER_INPUT5_X1 , USER_BIKE_REGISTER_INPUT5_Y1+5 , 4 ,MY_WHITE, 0,1);
		}
		if (mouse_press(USER_BIKE_REGISTER_INPUT6_X1, USER_BIKE_REGISTER_INPUT6_Y1, USER_BIKE_REGISTER_INPUT6_X2, USER_BIKE_REGISTER_INPUT6_Y2) == 1) {
			ch_input(battery, USER_BIKE_REGISTER_INPUT6_X1, USER_BIKE_REGISTER_INPUT6_Y1+5, 4, MY_WHITE, 0, 1);
		}
		if (mouse_press(USER_BIKE_REGISTER_BUTTON1_X1, USER_BIKE_REGISTER_BUTTON1_Y1, USER_BIKE_REGISTER_BUTTON1_X2, USER_BIKE_REGISTER_BUTTON1_Y2) == 1) {
			register_flag = EBIKE_INFO_judge(usrn, e_bike_id,id);
			if (register_flag == 0) {
				write_user_register_moreinfo(id, color, length, battery, weight);
				anime_login_success_user(USER_BIKE_REGISTER_BUTTON1_X1, USER_BIKE_REGISTER_BUTTON1_Y1, USER_BIKE_REGISTER_BUTTON1_X2, USER_BIKE_REGISTER_BUTTON1_Y2);
				setfillstyle(SOLID_FILL, MY_WHITE);
				bar(150, 60, 640, 480);
				ch_input(NULL, NULL, NULL, NULL, NULL, INPUTBAR_CLEAR, NULL);
				puthz(280, 200, "您已登记成功", 32, 40, MY_BLACK);
				puthz(245, 260, "即将返回主界面", 32, 40, MY_BLACK);
				delay(3000);
				*page = MAIN_USER;
				return;
			}
			else 
				anime_user_bike_register_fail(register_flag);
		}
		newmouse(&MouseX, &MouseY, &press, &mouse_flag);
		delay(25); // 50hz刷新率
	}
}


//是否注册过电动车判断
int user_ebike_register_judge(LINKLIST *LIST,unsigned long *ID) {
	/*int i = 0;
	int bike_count = 0;
	int account_counts;
	EBIKE_INFO TEMP;
	FILE* fp_EBIKE_INFO_read = fopen("DATA\\REGISTER.DAT", "rb");

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
			return 0;//已登记
		}
	}
	
	if (fclose(fp_EBIKE_INFO_read) != 0) getch(), exit(0);
	return 1;//未登记*/
	char id_string[10];
	int index;
	LINKLIST_NODE *temp;
	sprintf(id_string, "%ld", *ID);
	index=linklist_find_data(LIST, id_string, "id");
	show_num(10, 300, index,MY_BLACK);
	if (index == -1)
		return 1;
	linklist_get_to_node(LIST, index, &temp);
	if (strcmp(temp->USER_DATA.ebike_ID,"0")==0)
		return 1;
	return 0;
}

void write_user_register_moreinfo(unsigned long* id, char* color, char* length, char* battery, char* weight) {
	int i = 0;
	int account_counts;
	EBIKE_MOREINFO TEMP;
	FILE* fp_EBIKE_MOREINFO_readndwrite = fopen("DATA\\MOREINFO.DAT", "rb+");
	if (fp_EBIKE_MOREINFO_readndwrite == NULL) {
		fclose(fp_EBIKE_MOREINFO_readndwrite);
		exit(0);
	}
	
	memset(&TEMP, 0, sizeof(TEMP));
	fseek(fp_EBIKE_MOREINFO_readndwrite, 0, SEEK_END);
	account_counts = ftell(fp_EBIKE_MOREINFO_readndwrite) / sizeof(EBIKE_MOREINFO);//初始操作完成，接下来开始遍历数据


	
	strcpy(TEMP.color, color);			
	strcpy(TEMP.battery, battery);
	strcpy(TEMP.length,length);
	strcpy(TEMP.weight, weight);
	TEMP.id = *id;
	TEMP.is_quiz = 0;
	fseek(fp_EBIKE_MOREINFO_readndwrite, 0, SEEK_END); // 确保写入位置在文件末尾
	fwrite(&TEMP, sizeof(EBIKE_MOREINFO), 1, fp_EBIKE_MOREINFO_readndwrite);  //将注册信息写入文件
	if (fclose(fp_EBIKE_MOREINFO_readndwrite) != 0) getch(), exit(1);
	return 0;

}

int user_get_ebike_moreinfo(EBIKE_MOREINFO *moreinfo,unsigned long* id) {
	int i = 0;
	int account_counts;
	EBIKE_MOREINFO TEMP;
	FILE* fp_EBIKE_MOREINFO_read = fopen("DATA\\MOREINFO.DAT", "rb");
	if (fp_EBIKE_MOREINFO_read == NULL) {
		fclose(fp_EBIKE_MOREINFO_read);
		exit(0);
	}

	memset(&TEMP, 0, sizeof(TEMP));
	fseek(fp_EBIKE_MOREINFO_read, 0, SEEK_END);
	account_counts = ftell(fp_EBIKE_MOREINFO_read) / sizeof(EBIKE_MOREINFO);//初始操作完成，接下来开始遍历数据

	for (i = 0; i < account_counts; i++) {
		fseek(fp_EBIKE_MOREINFO_read, i * sizeof(EBIKE_MOREINFO), SEEK_SET);
		fread(&TEMP, sizeof(EBIKE_MOREINFO), 1, fp_EBIKE_MOREINFO_read); //逐个读取，每个用户信息

		if (TEMP.id == *id) {
			strcpy(moreinfo->color, TEMP.color);			
			strcpy(moreinfo->battery, TEMP.battery);
			strcpy(moreinfo->length, TEMP.length);
			strcpy(moreinfo->weight, TEMP.weight);
			moreinfo->id = *id;
			moreinfo->is_quiz = TEMP.is_quiz;
			if (fclose(fp_EBIKE_MOREINFO_read) != 0) getch(), exit(1); 
			return 1;
		}
	}
	
	if (fclose(fp_EBIKE_MOREINFO_read) != 0) getch(), exit(1);
	return 0;

}

void flushUserRegister(int* tag) {
	if ((MouseX >= USER_BIKE_REGISTER_INPUT1_X1 && MouseX <= USER_BIKE_REGISTER_INPUT1_X2 && MouseY >= USER_BIKE_REGISTER_INPUT1_Y1 && MouseY <= USER_BIKE_REGISTER_INPUT1_Y2) ||
		(MouseX >= USER_BIKE_REGISTER_INPUT2_X1 && MouseX <= USER_BIKE_REGISTER_INPUT2_X2 && MouseY >= USER_BIKE_REGISTER_INPUT2_Y1 && MouseY <= USER_BIKE_REGISTER_INPUT2_Y2))
		MouseS = 2;
	else if ((MouseX >= USER_BIKE_REGISTER_BUTTON1_X1 && MouseX <= USER_BIKE_REGISTER_BUTTON1_X2 && MouseY >= USER_BIKE_REGISTER_BUTTON1_Y1 && MouseY <= USER_BIKE_REGISTER_BUTTON1_Y2) ||
		(MouseX >= USER_BIKE_REGISTER_BUTTON2_X1 && MouseX <= USER_BIKE_REGISTER_BUTTON2_X2 && MouseY >= USER_BIKE_REGISTER_BUTTON2_Y1 && MouseY <= USER_BIKE_REGISTER_BUTTON2_Y2))
		MouseS = 1;
	else if (*tag==ACTIVE_USER_NONE)
		MouseS = 0;
}


//电动车注册信息写入
int EBIKE_INFO_judge(char* usrn, char* e_bike_id,unsigned long* id) {
	int i = 0;
	int account_counts;
	EBIKE_INFO TEMP ;
	FILE* fp_EBIKE_INFO_readndwrite = fopen("DATA\\REGISTER.DAT", "rb+");
	
	
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

		/*if (strcmp(usrn, TEMP.rln) == 0) {
			if (fclose(fp_EBIKE_INFO_readndwrite) != 0) getch(), exit(1); //发现存在用户名相同的，则注册失败
			return 1;
		}*/
		if (strcmp(e_bike_id, TEMP.ebike_ID) == 0) {
			if (fclose(fp_EBIKE_INFO_readndwrite) != 0) getch(), exit(1); //发现存在车牌号相同的，则注册失败
			return 2;
		}
	}

	//若经过了for循环仍未经过return，则代表用户名未曾注册过，可以注册
	strcpy(TEMP.rln, usrn);			//获取账密和uid
	strcpy(TEMP.ebike_ID, e_bike_id);
	strcpy(TEMP.ebike_license, "0");
	strcpy(TEMP.location, "0");
	TEMP.ID =*id;
	TEMP.apply_time =get_approx_time(NULL);
	TEMP.conduct_time = 0;
	TEMP.result = PENDING;
	TEMP.anual_check = 0;
	TEMP.violations = 0;
	fseek(fp_EBIKE_INFO_readndwrite, 0, SEEK_END); // 确保写入位置在文件末尾
	fwrite(&TEMP, sizeof(EBIKE_INFO), 1, fp_EBIKE_INFO_readndwrite);  //将注册信息写入文件
	if (fclose(fp_EBIKE_INFO_readndwrite) != 0) getch(), exit(1);
	return 0;

}



void anime_login_success_user(int x1,int y1,int x2,int y2) {
	int blinkTick = 0;
	clrmous(MouseX, MouseY);

	setfillstyle(SOLID_FILL, MY_WHITE);
	//bar(310,130,600,160); //覆盖原有的错误提示
	//bar(310, 190, 600, 220);
	setcolor(LIGHTGREEN);
	setlinestyle(SOLID_LINE,0, THICK_WIDTH);
	rectangle(x1 + 2, y1 + 2, x2 - 2, y2 - 2);
	rectangle(x1 + 2, y1 + 2, x2 - 2, y2 - 2);

	while (blinkTick < 100) {
		if (blinkTick % 20 == 0 && blinkTick % 40 != 0) {
			setfillstyle(SOLID_FILL, MY_GREEN);
			bar(x1, y1, x2, y2);
			puthz(x1 + 3, y1 + 9, "登记成功", 24, 18, MY_WHITE);
		}
		else if (blinkTick % 40 == 0) {
			setfillstyle(SOLID_FILL, MY_LIGHTBLUE);
			bar(x1, y1, x2, y2);
			puthz(x1 + 3, y1 + 9, "登记成功", 24, 18, MY_WHITE);
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
	rectangle(USER_BIKE_REGISTER_INPUT3_X1, USER_BIKE_REGISTER_INPUT3_Y1, USER_BIKE_REGISTER_INPUT3_X2, USER_BIKE_REGISTER_INPUT3_Y2);
	rectangle(USER_BIKE_REGISTER_INPUT4_X1, USER_BIKE_REGISTER_INPUT4_Y1, USER_BIKE_REGISTER_INPUT4_X2, USER_BIKE_REGISTER_INPUT4_Y2);
	rectangle(USER_BIKE_REGISTER_INPUT5_X1, USER_BIKE_REGISTER_INPUT5_Y1, USER_BIKE_REGISTER_INPUT5_X2, USER_BIKE_REGISTER_INPUT5_Y2);
	rectangle(USER_BIKE_REGISTER_INPUT6_X1, USER_BIKE_REGISTER_INPUT6_Y1, USER_BIKE_REGISTER_INPUT6_X2, USER_BIKE_REGISTER_INPUT6_Y2);

	puthz(170, 170, "姓名",24,20,MY_BLACK);
	puthz(160, 235, "车牌号",24,20,MY_BLACK);

	setcolor(MY_RED);
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	setfillstyle(SOLID_FILL, MY_RED);
	bar(USER_BIKE_REGISTER_BUTTON1_X1, USER_BIKE_REGISTER_BUTTON1_Y1, USER_BIKE_REGISTER_BUTTON1_X2, USER_BIKE_REGISTER_BUTTON1_Y2);
	bar(USER_BIKE_REGISTER_BUTTON2_X1, USER_BIKE_REGISTER_BUTTON2_Y1, USER_BIKE_REGISTER_BUTTON2_X2, USER_BIKE_REGISTER_BUTTON2_Y2);
	puthz(USER_BIKE_REGISTER_BUTTON1_X1 + 10, USER_BIKE_REGISTER_BUTTON1_Y1 + 10, "登记", 24, 30, MY_WHITE);
	puthz(USER_BIKE_REGISTER_BUTTON2_X1 + 10, USER_BIKE_REGISTER_BUTTON2_Y1 + 10, "反馈", 24, 30, MY_WHITE);

	puthz(170, 290, "电动车颜色", 24, 20, MY_LIGHTGRAY);
	puthz(170, 355, "车重（千克）", 24, 20, MY_LIGHTGRAY);
	puthz(400, 290, "车长（厘米）", 24, 20, MY_LIGHTGRAY);
	puthz(400, 355, "电池（千瓦时）", 24, 20, MY_LIGHTGRAY);
	
}



void drawgraph_user_bike_register_info(LINKLIST *LIST,unsigned long *id) {
	EBIKE_INFO user_info;
	EBIKE_MOREINFO moreinfo;
	char id_string[20];
	char apply_time_string[20];//一定要给sprintf留出足够缓冲区
	char conduct_time_string[20];
	user_bike_register_getinfo(LIST,&user_info,id);
	user_get_ebike_moreinfo(&moreinfo, id);
	sprintf(id_string, "%lu", *id);
	sprintf(apply_time_string, "%lu",user_info.apply_time);
	sprintf(conduct_time_string, "%lu", user_info.conduct_time);
	
	puthz(260, 80, "电动车信息", 32, 40, MY_BLACK);
	setcolor(MY_BLACK);
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	setfillstyle(SOLID_FILL, MY_BLACK);
	bar(151, 120, 640, 123);

	puthz(170, 170, "姓名", 24, 20, MY_BLACK);
	puthz(280, 170, user_info.rln, 24, 20, MY_BLACK);
	puthz(170, 220, "车牌号", 24, 20, MY_BLACK);
	outtextxy(280, 225, user_info.ebike_ID);

	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2); // 默认字体，水平方向，大小2
	setcolor(MY_BLACK);
	
	puthz(170, 290, "电动车颜色", 24, 20, MY_LIGHTGRAY);
	puthz(310, 290, moreinfo.color, 24, 20, MY_BLACK);
	puthz(170, 355, "车重（千克）", 24, 20, MY_LIGHTGRAY);
	outtextxy(310, 362, moreinfo.weight);
	puthz(400, 290, "车长（厘米）", 24, 20, MY_LIGHTGRAY);
	outtextxy(545, 297, moreinfo.length);
	puthz(400, 355, "电池（千瓦时）", 24, 20, MY_LIGHTGRAY);
	outtextxy(545, 362, moreinfo.battery);
}



void user_bike_register_getinfo(LINKLIST *LIST,struct _EBIKE_INFO_ * user_info,unsigned long *id) {
	/*int i = 0;
	int account_counts;
	EBIKE_INFO TEMP;
	FILE* fp_EBIKE_INFO_readndwrite = fopen("DATA\\REGISTER.DAT", "rb");
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
		return ;*/
	char id_string[10];
	int index;
	LINKLIST_NODE* temp;
	sprintf(id_string, "%ld", *id);
	index = linklist_find_data(LIST, id_string, "id");
	if (index == -1)
		return;
	linklist_get_to_node(LIST, index, &temp);
	strcpy(user_info->rln, temp->USER_DATA.rln);
	strcpy(user_info->ebike_ID, temp->USER_DATA.ebike_ID);
	strcpy(user_info->ebike_license, temp->USER_DATA.ebike_license);
	user_info->anual_check = temp->USER_DATA.anual_check;
	user_info->violations = temp->USER_DATA.violations;
}










// 通行证须知页面

void user_bike_license_notice(LINKLIST *LIST,int* page, unsigned long* id)
{
	int click = -99;
	int tag = 0;
	int mouse_flag;
	int register_flag;
	int license_flag;
	int quiz_flag;
	int tick=0;
	char second[][2] = { "5","4","3","2","1","0" };

	user_button UserButtons[] = {
{USER_BIKE_REGISTER_X1, USER_BIKE_REGISTER_X2,USER_BIKE_REGISTER_Y1, USER_BIKE_REGISTER_Y2,ACTIVE_USER_BIKE_REGISTER,USER_BIKE_REGISTER},
{USER_BIKE_LICENSE_X1, USER_BIKE_LICENSE_X2,USER_BIKE_LICENSE_Y1, USER_BIKE_LICENSE_Y2,ACTIVE_USER_BIKE_LICENSE,USER_BIKE_LICENSE_NOTICE},
{USER_ANNUAL_X1, USER_ANNUAL_X2,USER_ANNUAL_Y1, USER_ANNUAL_Y2,ACTIVE_USER_ANNUAL,USER_ANNUAL},
{USER_BIKE_WROTEOUT_X1, USER_BIKE_WROTEOUT_X2,USER_BIKE_WROTEOUT_Y1, USER_BIKE_WROTEOUT_Y2,ACTIVE_USER_BIKE_WROTEOUT,USER_BIKE_WROTEOUT},
{USER_INFO_X1, USER_INFO_X2,USER_INFO_Y1, USER_INFO_Y2,ACTIVE_USER_INFO,USER_INFO},
{USER_MESSAGE_X1, USER_MESSAGE_X2,USER_MESSAGE_Y1, USER_MESSAGE_Y2,ACTIVE_USER_MESSAGE,USER_MESSAGE},
{USER_HELP_X1, USER_HELP_X2,USER_HELP_Y1, USER_HELP_Y2,ACTIVE_USER_HELP,USER_HELP},
{USER_BACK_X1,USER_BACK_X2,USER_BACK_Y1,USER_BACK_Y2,ACTIVE_USER_BACK,LOGIN},
{USER_EXIT_X1,USER_EXIT_X2,USER_EXIT_Y1,USER_EXIT_Y2,ACTIVE_USER_EXIT,EXIT},
	};

	clrmous(MouseX, MouseY);
	save_bk_mou(MouseX, MouseY);
	drawgraph_user_main(page);

	license_flag = ebike_license_judge(id);
	register_flag = user_ebike_register_judge(LIST,id);
	quiz_flag = quiz_judge(id);

	
	if (register_flag==1 ) {
		puthz(180, 200, "您未注册电动车，请前往注册！", 32, 32, MY_BLACK);
		puthz(280, 300, "秒后转到电动车注册界面", 24, 22, MY_BLACK);
		while (tick <= 202) {
			newmouse_data(&MouseX, &MouseY, &press, &mouse_flag);
			flushUserMain(&tag, STRUCT_LENGTH(UserButtons), UserButtons);
			click = handle_click_main(STRUCT_LENGTH(UserButtons), UserButtons);
			if (click != -99 && click != USER_BIKE_LICENSE_NOTICE) {          
				*page = click;
				return;
			}
			if (tick % 40 == 0) {
				setfillstyle(SOLID_FILL, MY_WHITE);
				bar(245, 280, 275, 330);
				settextstyle(DEFAULT_FONT, HORIZ_DIR, 2); // 默认字体，水平方向，大小2
				setcolor(MY_BLACK);
				outtextxy(250, 305, second[tick / 40]);
			}
			newmouse(&MouseX, &MouseY, &press, &mouse_flag);
			delay(25);
			tick++;
		}
		*page = USER_BIKE_REGISTER;
		return;
	}
	else if (license_flag == 0) {
		puthz(220, 200, "您已申领电动车通行证！", 32, 32, MY_BLACK);
		puthz(280, 300, "秒后返回主页面", 24, 22, MY_BLACK);
		while (tick <= 202) {
			newmouse_data(&MouseX, &MouseY, &press, &mouse_flag);
			flushUserMain(&tag, STRUCT_LENGTH(UserButtons), UserButtons);
			click = handle_click_main(STRUCT_LENGTH(UserButtons), UserButtons);
			if (click != -99 && click != USER_BIKE_LICENSE_NOTICE) {          //其它页面做完后此处会改成click!=-1&&click!=USER_BIKE_LICENSE_NOTICE
				*page = click;
				return;
			}
			if (mouse_press(USER_LICENSE_NOTICE_BUTTON1_X1, USER_LICENSE_NOTICE_BUTTON1_Y1, USER_LICENSE_NOTICE_BUTTON1_X2, USER_LICENSE_NOTICE_BUTTON1_Y2) == 1) {
				*page = USER_QUIZ;
				return;
			}
			if (tick % 40 == 0) {
				setfillstyle(SOLID_FILL, MY_WHITE);
				bar(245, 280, 275, 330);
				settextstyle(DEFAULT_FONT, HORIZ_DIR, 2); // 默认字体，水平方向，大小2
				setcolor(MY_BLACK);
				outtextxy(250, 305, second[tick / 40]);
			}
			newmouse(&MouseX, &MouseY, &press, &mouse_flag);
			delay(25);
			tick++;
		}
		*page = MAIN_USER;
		return;
	}
	else if(quiz_flag==1){
		puthz(250, 200, "您已通过电动车规范测试！", 32, 32, MY_BLACK);
		puthz(280, 300, "即将前往通行证预约", 24, 22, MY_BLACK);
		while (tick <= 80) {
			newmouse_data(&MouseX, &MouseY, &press, &mouse_flag);
			flushUserMain(&tag, STRUCT_LENGTH(UserButtons), UserButtons);
			click = handle_click_main(STRUCT_LENGTH(UserButtons), UserButtons);
			if (click != -99 && click != USER_BIKE_LICENSE_NOTICE) {          //其它页面做完后此处会改成click!=-1&&click!=USER_BIKE_LICENSE_NOTICE
				*page = click;
				return;
			}
			newmouse(&MouseX, &MouseY, &press, &mouse_flag);
			delay(25);
			tick++;
		}
		*page = USER_BIKE_LICENSE;
		return;
	}
	else {
		drawgraph_user_license_notice(id);
		while (1) {
			newmouse_data(&MouseX, &MouseY, &press, &mouse_flag);
			flushUserMain(&tag, STRUCT_LENGTH(UserButtons), UserButtons);
			flushUserLicenseNotice(&tag);
			click = handle_click_main(STRUCT_LENGTH(UserButtons), UserButtons);
			if (click != -99 && click != USER_BIKE_LICENSE_NOTICE) {          //其它页面做完后此处会改成click!=-1&&click!=USER_BIKE_LICENSE_NOTICE
				*page = click;
				return;
			}
			if (mouse_press(USER_LICENSE_NOTICE_BUTTON1_X1, USER_LICENSE_NOTICE_BUTTON1_Y1, USER_LICENSE_NOTICE_BUTTON1_X2, USER_LICENSE_NOTICE_BUTTON1_Y2) == 1) {
				*page = USER_QUIZ;
				return;
			}
			newmouse(&MouseX, &MouseY, &press, &mouse_flag);
			delay(25);
		}
	}

	
}

void drawgraph_user_license_notice(unsigned long* id){
	puthz(220, 80, "校园电动车通行证办理须知", 32,30, MY_BLACK);

	// 绘制通知内容
	puthz(170, 150, "一、办理校园通行证需提前三天预约，可从韵苑", 24,22, MY_BLACK);
	puthz(200, 190, "沁苑，紫菘选择一处办理", 24, 22, MY_BLACK);
	puthz(170, 240, "二、办理校园通行证需先通过电动车知识测试", 24,22, MY_BLACK);
	puthz(170, 290, "三、测试前请仔细阅读电动车管理规范",24,22,MY_BLACK);

	// 绘制按钮
	setcolor(MY_RED);
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	setfillstyle(SOLID_FILL, MY_RED);
	bar(USER_LICENSE_NOTICE_BUTTON1_X1, USER_LICENSE_NOTICE_BUTTON1_Y1,
		USER_LICENSE_NOTICE_BUTTON1_X2, USER_LICENSE_NOTICE_BUTTON1_Y2);
	puthz(USER_LICENSE_NOTICE_BUTTON1_X1 + 6, USER_LICENSE_NOTICE_BUTTON1_Y1 + 10,
		"进入测试", 24,22, MY_WHITE);

	setfillstyle(SOLID_FILL, MY_GREEN);
	bar(USER_LICENSE_NOTICE_BUTTON2_X1, USER_LICENSE_NOTICE_BUTTON2_Y1,
		USER_LICENSE_NOTICE_BUTTON2_X2, USER_LICENSE_NOTICE_BUTTON2_Y2);
	puthz(USER_LICENSE_NOTICE_BUTTON2_X1 + 6, USER_LICENSE_NOTICE_BUTTON2_Y1 + 10,
		"查看法规", 24,22, MY_WHITE);

}

void flushUserLicenseNotice(int* tag)
{
	// 刷新按钮状态
	if (MouseX >= USER_LICENSE_NOTICE_BUTTON1_X1 && MouseX <= USER_LICENSE_NOTICE_BUTTON1_X2 &&
		MouseY >= USER_LICENSE_NOTICE_BUTTON1_Y1 && MouseY <= USER_LICENSE_NOTICE_BUTTON1_Y2) {
		setcolor(MY_BLACK);
		setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
		rectangle(USER_LICENSE_NOTICE_BUTTON1_X1 - 1, USER_LICENSE_NOTICE_BUTTON1_Y1 - 1,
			USER_LICENSE_NOTICE_BUTTON1_X2 + 1, USER_LICENSE_NOTICE_BUTTON1_Y2 + 1);
		MouseS = 1;
	}
	else if (MouseX >= USER_LICENSE_NOTICE_BUTTON2_X1 && MouseX <= USER_LICENSE_NOTICE_BUTTON2_X2 &&
		MouseY >= USER_LICENSE_NOTICE_BUTTON2_Y1 && MouseY <= USER_LICENSE_NOTICE_BUTTON2_Y2) {
		setcolor(MY_BLACK);
		setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
		rectangle(USER_LICENSE_NOTICE_BUTTON2_X1 - 1, USER_LICENSE_NOTICE_BUTTON2_Y1 - 1,
			USER_LICENSE_NOTICE_BUTTON2_X2 + 1, USER_LICENSE_NOTICE_BUTTON2_Y2 + 1);
		MouseS = 1;
	}
	else {
		setcolor(MY_WHITE);
		setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
		rectangle(USER_LICENSE_NOTICE_BUTTON1_X1 - 1, USER_LICENSE_NOTICE_BUTTON1_Y1 - 1,
			USER_LICENSE_NOTICE_BUTTON1_X2 + 1, USER_LICENSE_NOTICE_BUTTON1_Y2 + 1);
		rectangle(USER_LICENSE_NOTICE_BUTTON2_X1 - 1, USER_LICENSE_NOTICE_BUTTON2_Y1 - 1,
			USER_LICENSE_NOTICE_BUTTON2_X2 + 1, USER_LICENSE_NOTICE_BUTTON2_Y2 + 1);
	}
}



//预约办理通行证界面
void user_bike_license(LINKLIST *LIST,int *page,unsigned long *id)
{
	int license_data[3] = {-1,-1,-1};
	int click = -99;
	int tag = 0;
	int register_flag = 0;
	int mouse_flag;
	int success_flag=0;
	user_button UserButtons[] = {
{USER_BIKE_REGISTER_X1, USER_BIKE_REGISTER_X2,USER_BIKE_REGISTER_Y1, USER_BIKE_REGISTER_Y2,ACTIVE_USER_BIKE_REGISTER,USER_BIKE_REGISTER},
{USER_BIKE_LICENSE_X1, USER_BIKE_LICENSE_X2,USER_BIKE_LICENSE_Y1, USER_BIKE_LICENSE_Y2,ACTIVE_USER_BIKE_LICENSE,USER_BIKE_LICENSE_NOTICE},
{USER_ANNUAL_X1, USER_ANNUAL_X2,USER_ANNUAL_Y1, USER_ANNUAL_Y2,ACTIVE_USER_ANNUAL,USER_ANNUAL},
{USER_BIKE_WROTEOUT_X1, USER_BIKE_WROTEOUT_X2,USER_BIKE_WROTEOUT_Y1, USER_BIKE_WROTEOUT_Y2,ACTIVE_USER_BIKE_WROTEOUT,USER_BIKE_WROTEOUT},
{USER_INFO_X1, USER_INFO_X2,USER_INFO_Y1, USER_INFO_Y2,ACTIVE_USER_INFO,USER_INFO},
{USER_MESSAGE_X1, USER_MESSAGE_X2,USER_MESSAGE_Y1, USER_MESSAGE_Y2,ACTIVE_USER_MESSAGE,USER_MESSAGE},
{USER_HELP_X1, USER_HELP_X2,USER_HELP_Y1, USER_HELP_Y2,ACTIVE_USER_HELP,USER_HELP},
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
	drawgraph_user_bike_license(LIST,id,UserLicenseBox);
	while (1) {
		newmouse_data(&MouseX, &MouseY, &press,&mouse_flag);
		flushUserMain(&tag, STRUCT_LENGTH(UserButtons), UserButtons); // 刷新界面
		flushUserLicense(UserLicenseBox,license_data);
		handle_click_user_license(UserLicenseBox,license_data);//处理选项框
		click = handle_click_main(STRUCT_LENGTH(UserButtons), UserButtons);
		if (click !=-99 && click != USER_BIKE_LICENSE_NOTICE) {          //其它页面做完后此处会改成click!=-1&&click!=USER_BIKE_LICENSE
			*page = click;
			return;
		}//菜单界面点击
		if (mouse_press(USER_BIKE_LICENSE_BUTTON1_X1, USER_BIKE_LICENSE_BUTTON1_Y1, USER_BIKE_LICENSE_BUTTON1_X2, USER_BIKE_LICENSE_BUTTON1_Y2) == 1) {
			success_flag=user_license_data_judge(LIST,license_data,id);
			if (success_flag) {
				anime_login_success_user(USER_BIKE_LICENSE_BUTTON1_X1, USER_BIKE_LICENSE_BUTTON1_Y1, USER_BIKE_LICENSE_BUTTON1_X2, USER_BIKE_LICENSE_BUTTON1_Y2);
				setfillstyle(SOLID_FILL, MY_WHITE);
				bar(150, 60, 640, 480);
				puthz(280, 200, "您已预约成功", 32, 40, MY_BLACK);
				puthz(245, 260, "即将返回主界面", 32, 40, MY_BLACK);
				delay(3000);
				*page = MAIN_USER;
				return;
			}
		}
		if (mouse_press(USER_BIKE_LICENSE_BUTTON2_X1, USER_BIKE_LICENSE_BUTTON2_Y1, USER_BIKE_LICENSE_BUTTON2_X2, USER_BIKE_LICENSE_BUTTON2_Y2) == 1) {
			*page = USER_HELP;
			return;
		}
		newmouse(&MouseX, &MouseY, &press, &mouse_flag);
		delay(25);
	}
}

void drawgraph_user_bike_license(LINKLIST *LIST,unsigned long *id,user_box box[3][3]) {
	EBIKE_INFO user_info;
	char time_string[20];
	int i, j;

	user_bike_register_getinfo(LIST,&user_info, id);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2); // 默认字体，水平方向，大小2
	setcolor(MY_BLACK);
	puthz(170, 80, "姓名", 24, 20, MY_BLACK);
	puthz(250, 80, user_info.rln,24,22,MY_BLACK);
	puthz(360, 80, "车牌号", 24, 20, MY_BLACK);
	outtextxy(460, 82, user_info.ebike_ID);
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
}

int user_license_data_judge(LINKLIST *LIST,int* data,unsigned long *id) {
	int i = 0;
	char e_bike_license[10];
	int account_counts;
	EBIKE_INFO TEMP,USER;
	FILE* fp_EBIKE_INFO_LICENSE_readndwrite = fopen("DATA\\LICENSE.DAT", "rb+");
	if (fp_EBIKE_INFO_LICENSE_readndwrite == NULL) {
		fclose(fp_EBIKE_INFO_LICENSE_readndwrite);
		exit(0);
	}

	setfillstyle(SOLID_FILL, MY_WHITE);
	bar(425, 110, 600, 140);
	bar(425, 200, 600, 240);
	if (data[0] == -1) {
		setfillstyle(SOLID_FILL, MY_WHITE);
		bar(425, 200, 520, 230);
		puthz(440, 125, "请选择地点！", 24, 20, MY_RED);
		if (fclose(fp_EBIKE_INFO_LICENSE_readndwrite) != 0) getch(), exit(1);
		return 0;
	}

	if (data[1] == -1 || data[2] == -1) {
		setfillstyle(SOLID_FILL, MY_WHITE);
		bar(425, 110, 520, 145);
		puthz(440, 215, "请选择时间！", 24, 20, MY_RED);
		if (fclose(fp_EBIKE_INFO_LICENSE_readndwrite) != 0) getch(), exit(1);
		return 0;
	}
	setfillstyle(SOLID_FILL, MY_WHITE);
	bar(425, 110, 520, 145);
	setfillstyle(SOLID_FILL, MY_WHITE);
	bar(425, 200, 520, 230);
	user_bike_register_getinfo(LIST,&USER, id);

	memset(&TEMP, 0, sizeof(TEMP));
	fseek(fp_EBIKE_INFO_LICENSE_readndwrite, 0, SEEK_END);
	account_counts = ftell(fp_EBIKE_INFO_LICENSE_readndwrite) / sizeof(EBIKE_INFO);//初始操作完成，接下来开始遍历数据

	for (i = 0; i < account_counts; i++) {
		fseek(fp_EBIKE_INFO_LICENSE_readndwrite, i * sizeof(EBIKE_INFO), SEEK_SET);
		fread(&TEMP, sizeof(EBIKE_INFO), 1, fp_EBIKE_INFO_LICENSE_readndwrite); //逐个读取，每个用户信息

		if (strcmp(USER.rln, TEMP.rln) == 0) {
			if (fclose(fp_EBIKE_INFO_LICENSE_readndwrite) != 0) getch(), exit(1); //发现存在用户名相同的，则注册失败
			puthz(440, 428, "您已申请过通行证！", 24, 22, MY_RED);
			if (fclose(fp_EBIKE_INFO_LICENSE_readndwrite) != 0) getch(), exit(1);
			return 0;
		}
		if (strcmp(USER.ebike_ID, TEMP.ebike_ID) == 0) {
			if (fclose(fp_EBIKE_INFO_LICENSE_readndwrite) != 0) getch(), exit(1); //发现存在车牌号相同的，则注册失败
			puthz(440, 428, "车牌申请过通行证！", 24, 22, MY_RED);
			if (fclose(fp_EBIKE_INFO_LICENSE_readndwrite) != 0) getch(), exit(1);
			return 0;
		}
	}
	
	//若经过了for循环仍未经过return，则代表用户名未曾注册过，可以注册
	strcpy(TEMP.rln, USER.rln);			//获取账密和uid
	strcpy(TEMP.ebike_ID, USER.ebike_ID);
	strcpy(TEMP.ebike_license, "0");
	strcpy(TEMP.location, "0");
	TEMP.ID = *id;
	TEMP.apply_time = get_approx_time(NULL);
	TEMP.conduct_time = 0;
	TEMP.result = PENDING;
	TEMP.anual_check = 0;
	TEMP.violations = 0;
	fseek(fp_EBIKE_INFO_LICENSE_readndwrite, 0, SEEK_END); // 确保写入位置在文件末尾
	fwrite(&TEMP, sizeof(EBIKE_INFO), 1, fp_EBIKE_INFO_LICENSE_readndwrite);  //将注册信息写入文件
	if (fclose(fp_EBIKE_INFO_LICENSE_readndwrite) != 0) getch(), exit(1);
	return 1;

}

int ebike_license_judge(unsigned long* id) {
	/*int i = 0;
	char e_bike_license[10];
	int account_counts;
	EBIKE_INFO TEMP;
	FILE* fp_EBIKE_INFO_LICENSE_readndwrite = fopen("DATA\\LICENSE.DAT", "rb+");

	if (fp_EBIKE_INFO_LICENSE_readndwrite == NULL) {
		fclose(fp_EBIKE_INFO_LICENSE_readndwrite);
		exit(0);
	}


	memset(&TEMP, 0, sizeof(TEMP));
	fseek(fp_EBIKE_INFO_LICENSE_readndwrite, 0, SEEK_END);
	account_counts = ftell(fp_EBIKE_INFO_LICENSE_readndwrite) / sizeof(EBIKE_INFO);//初始操作完成，接下来开始遍历数据

	for (i = 0; i < account_counts; i++) {
		fseek(fp_EBIKE_INFO_LICENSE_readndwrite, i * sizeof(EBIKE_INFO), SEEK_SET);
		fread(&TEMP, sizeof(EBIKE_INFO), 1, fp_EBIKE_INFO_LICENSE_readndwrite); //逐个读取，每个用户信息

		if (TEMP.ID==*id) {
			if (fclose(fp_EBIKE_INFO_LICENSE_readndwrite) != 0) getch(), exit(1); //发现存在用户名相同的，则注册失败
			return 0;
		}
	}

	if (fclose(fp_EBIKE_INFO_LICENSE_readndwrite) != 0) getch(), exit(1);
	return 1;*/

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
	return;
}











void user_help(int* page, unsigned long* id)
{
	int tag_help;
	int tag_main;
	int click=-99;
	int announce = -1;
	int mouse_flag;

	user_button UserButtons[] = {
{USER_BIKE_REGISTER_X1, USER_BIKE_REGISTER_X2,USER_BIKE_REGISTER_Y1, USER_BIKE_REGISTER_Y2,ACTIVE_USER_BIKE_REGISTER,USER_BIKE_REGISTER},
{USER_BIKE_LICENSE_X1, USER_BIKE_LICENSE_X2,USER_BIKE_LICENSE_Y1, USER_BIKE_LICENSE_Y2,ACTIVE_USER_BIKE_LICENSE,USER_BIKE_LICENSE_NOTICE},
{USER_ANNUAL_X1, USER_ANNUAL_X2,USER_ANNUAL_Y1, USER_ANNUAL_Y2,ACTIVE_USER_ANNUAL,USER_ANNUAL},
{USER_BIKE_WROTEOUT_X1, USER_BIKE_WROTEOUT_X2,USER_BIKE_WROTEOUT_Y1, USER_BIKE_WROTEOUT_Y2,ACTIVE_USER_BIKE_WROTEOUT,USER_BIKE_WROTEOUT},
{USER_INFO_X1, USER_INFO_X2,USER_INFO_Y1, USER_INFO_Y2,ACTIVE_USER_INFO,USER_INFO},
{USER_MESSAGE_X1, USER_MESSAGE_X2,USER_MESSAGE_Y1, USER_MESSAGE_Y2,ACTIVE_USER_MESSAGE,USER_MESSAGE},
{USER_HELP_X1, USER_HELP_X2,USER_HELP_Y1, USER_HELP_Y2,ACTIVE_USER_HELP,USER_HELP},
{USER_BACK_X1,USER_BACK_X2,USER_BACK_Y1,USER_BACK_Y2,ACTIVE_USER_BACK,LOGIN},
{USER_EXIT_X1,USER_EXIT_X2,USER_EXIT_Y1,USER_EXIT_Y2,ACTIVE_USER_EXIT,EXIT},
	};
	user_button HelpButtons[] = {
{USER_BIKE_REGISTER_X1, USER_BIKE_REGISTER_X2,USER_BIKE_REGISTER_Y1, USER_BIKE_REGISTER_Y2,ACTIVE_USER_BIKE_REGISTER,USER_BIKE_REGISTER},
{USER_BIKE_LICENSE_X1, USER_BIKE_LICENSE_X2,USER_BIKE_LICENSE_Y1, USER_BIKE_LICENSE_Y2,ACTIVE_USER_BIKE_LICENSE,USER_BIKE_LICENSE_NOTICE},
{USER_ANNUAL_X1, USER_ANNUAL_X2,USER_ANNUAL_Y1, USER_ANNUAL_Y2,ACTIVE_USER_ANNUAL,USER_ANNUAL},
{USER_BIKE_WROTEOUT_X1, USER_BIKE_WROTEOUT_X2,USER_BIKE_WROTEOUT_Y1, USER_BIKE_WROTEOUT_Y2,ACTIVE_USER_BIKE_WROTEOUT,USER_BIKE_WROTEOUT},
{USER_INFO_X1, USER_INFO_X2,USER_INFO_Y1, USER_INFO_Y2,ACTIVE_USER_INFO,USER_INFO},
{USER_MESSAGE_X1, USER_MESSAGE_X2,USER_MESSAGE_Y1, USER_MESSAGE_Y2,ACTIVE_USER_MESSAGE,USER_MESSAGE},
{USER_HELP_X1, USER_HELP_X2,USER_HELP_Y1, USER_HELP_Y2,ACTIVE_USER_HELP,USER_HELP},
{USER_BACK_X1,USER_BACK_X2,USER_BACK_Y1,USER_BACK_Y2,ACTIVE_USER_BACK,LOGIN},
{USER_EXIT_X1,USER_EXIT_X2,USER_EXIT_Y1,USER_EXIT_Y2,ACTIVE_USER_EXIT,EXIT},
{HELP_ANNOUNCE1_X1, HELP_ANNOUNCE1_X2, HELP_ANNOUNCE1_Y1, HELP_ANNOUNCE1_Y2, 311, HELP_ANNOUNCE + 1},
{HELP_ANNOUNCE2_X1, HELP_ANNOUNCE2_X2, HELP_ANNOUNCE2_Y1, HELP_ANNOUNCE2_Y2, 312, HELP_ANNOUNCE + 2},
{HELP_ANNOUNCE3_X1, HELP_ANNOUNCE3_X2, HELP_ANNOUNCE3_Y1, HELP_ANNOUNCE3_Y2, 313, HELP_ANNOUNCE + 3},
{HELP_BUTTON1_X1, HELP_BUTTON1_X2, HELP_BUTTON1_Y1, HELP_BUTTON1_Y2, 321, USER_INFO_BIKEINFO},
{HELP_BUTTON2_X1, HELP_BUTTON2_X2, HELP_BUTTON2_Y1, HELP_BUTTON2_Y2, 322, USER_INFO_PASSWORD},
{HELP_BUTTON3_X1, HELP_BUTTON3_X2, HELP_BUTTON3_Y1, HELP_BUTTON3_Y2, 323, USER_INFO_BIKEDATA}
	};
	clrmous(MouseX, MouseY);
	save_bk_mou(MouseX, MouseY);
	drawgraph_user_main(page);
	drawgraph_user_help();
	
	while (1) {
		newmouse_data(&MouseX, &MouseY, &press, &mouse_flag);//刷新鼠标数据
		FlushUserHelp(&tag_help, STRUCT_LENGTH(HelpButtons), HelpButtons); // 刷新界面
		click = handle_click_user_help(STRUCT_LENGTH(HelpButtons), HelpButtons);
		if (click !=USER_HELP && click!=-99) {          //其它页面做完后此处会改成click!=-1&&click!=USER_BIKE_LICENSE
			*page = click;
			return;
		}//菜单界面点击
		else if (click >= HELP_ANNOUNCE) {
			announce = click - HELP_ANNOUNCE;
			break;
		}
		newmouse(&MouseX, &MouseY, &press, &mouse_flag);//在可能改变背景的操作后绘制鼠标
		delay(25);
	}

	drawgraph_user_main(page);
	drawgraph_user_help_announce(announce);

	while (1) {
		newmouse_data(&MouseX, &MouseY, &press, &mouse_flag);//刷新鼠标数据
		flushUserMain(&tag_main, STRUCT_LENGTH(UserButtons), UserButtons);
		click = handle_click_main(STRUCT_LENGTH(UserButtons), UserButtons);
		if (click != -99 && click != USER_HELP) {          //其它页面做完后此处会改成click!=-1&&click!=USER_BIKE_REGISTER
			*page = click;
			newmouse(&MouseX, &MouseY, &press, &mouse_flag);
			return;
		}
		if (mouse_press(HELP_ANNOUNCE_BACK_X1, HELP_ANNOUNCE_BACK_Y1, HELP_ANNOUNCE_BACK_X2, HELP_ANNOUNCE_BACK_Y2) == 1) {
			*page = USER_HELP;
			return;
		}
		if (MouseX >= HELP_ANNOUNCE_BACK_X1 && MouseX <= HELP_ANNOUNCE_BACK_X2 && MouseY >= HELP_ANNOUNCE_BACK_Y1 && MouseY <= HELP_ANNOUNCE_BACK_Y2) {
			MouseS = 1;
		}
		newmouse(&MouseX, &MouseY, &press, &mouse_flag);//在可能改变背景的操作后绘制鼠标
		delay(25);
	}
}

void FlushUserHelp(int* tag, int button_count, user_button UserButtons[]) {
	int i = 0;
	int temp = 0;
	int new_tag = ACTIVE_USER_NONE;


	for (i = 0; i < button_count; i++) {
		if (MouseX >= UserButtons[i].x1 && MouseX <= UserButtons[i].x2 &&
			MouseY >= UserButtons[i].y1 && MouseY <= UserButtons[i].y2) {
			new_tag = UserButtons[i].active_tag;
			MouseS = 1;
			temp = i;
			break;
		}
	}

	if (*tag != new_tag) {
		if (*tag != ACTIVE_USER_NONE) {
			if (*tag <= ACTIVE_USER_HELP) {
				setcolor(MY_LIGHTGRAY);
				setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
				rectangle(UserButtons[*tag - 1].x1, UserButtons[*tag - 1].y1, UserButtons[*tag - 1].x2, UserButtons[*tag - 1].y2);

			}
			else if (*tag == ACTIVE_USER_EXIT) {
				setcolor(MY_RED);
				setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
				rectangle(USER_EXIT_X1, USER_EXIT_Y1, USER_EXIT_X2, USER_EXIT_Y2);

			}
			else if (*tag == ACTIVE_USER_BACK) {
				setfillstyle(1, MY_YELLOW);//恢复“返回登录”
				setcolor(MY_YELLOW);
				bar(USER_BACK_X1, USER_BACK_Y1, USER_BACK_X2, USER_BACK_Y2);
				puthz(USER_BACK_X1 + 5, (USER_BACK_Y1 + USER_BACK_Y2) / 2 - 10, "返回", 24, 25, MY_WHITE);

			}
			else if(310< *tag && *tag <315){//公告
				setcolor(MY_CREAM);
				setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
				rectangle(UserButtons[*tag - 302].x1 - 1, UserButtons[*tag - 302].y1 - 1, UserButtons[*tag - 302].x2 + 1, UserButtons[*tag - 302].y2 + 1);//处理3个公告按钮，tag为311，312，313，在数组[9][10][11]位
			}
			else {
				setcolor(MY_CREAM);
				setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
				rectangle(UserButtons[*tag - 309].x1 - 1, UserButtons[*tag - 309].y1 - 1, UserButtons[*tag - 309].x2 + 1, UserButtons[*tag - 309].y2 + 1);//处理3个按钮，tag为321，322，323,在数组[12][13][14]位
			}
				
		}
		*tag = new_tag;
		if (new_tag != ACTIVE_USER_NONE && new_tag <= ACTIVE_USER_HELP) {
			setfillstyle(1, MY_WHITE);
			setcolor(MY_WHITE);
			setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
			rectangle(UserButtons[temp].x1, UserButtons[temp].y1, UserButtons[temp].x2, UserButtons[temp].y2);

		}
		else if (new_tag == ACTIVE_USER_EXIT) {
			setfillstyle(1, MY_WHITE);
			setcolor(MY_WHITE);
			setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
			rectangle(UserButtons[temp].x1, UserButtons[temp].y1, UserButtons[temp].x2, UserButtons[temp].y2);

		}
		else if (new_tag == ACTIVE_USER_BACK) {
			setcolor(MY_RED);
			setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
			setfillstyle(1, MY_RED);
			bar(USER_BACK_X1, USER_BACK_Y1, USER_BACK_X2, USER_BACK_Y2);
			puthz(USER_BACK_X1 + 5, (USER_BACK_Y1 + USER_BACK_Y2) / 2 - 10, "返回", 24, 25, MY_WHITE);

		}
		else if (310 < new_tag && new_tag < 315) {//公告
			setcolor(MY_BLACK);
			setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
			rectangle(UserButtons[new_tag - 302].x1 - 1, UserButtons[new_tag - 302].y1 - 1, UserButtons[new_tag - 302].x2 + 1, UserButtons[new_tag - 302].y2 + 1);//处理四个公告按钮，tag为311，312，313，在数组[9][10][11]位
		}
		else if(320<new_tag && new_tag < 325){
			setcolor(MY_BLACK);
			setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
			rectangle(UserButtons[*tag - 309].x1 - 1, UserButtons[*tag - 309].y1 - 1, UserButtons[*tag - 309].x2 + 1, UserButtons[*tag - 309].y2 + 1);//处理专属USER_INFO的四个按钮，tag为321，322，323,在数组[12][13][14]位
		}
		else {
			MouseS = 0;
		}
	}
}

int handle_click_user_help(int button_num, user_button UserButtons[]) {
	int i = 0;
	for (i = 0; i < button_num; i++) {
		if (mouse_press(UserButtons[i].x1, UserButtons[i].y1, UserButtons[i].x2, UserButtons[i].y2) == 1)
			return UserButtons[i].page;
	}
	return -99;
}

void drawgraph_user_help() {
	setfillstyle(SOLID_FILL, MY_CREAM);
	bar(180, 110, 380, 460);
	bar(400, 110, 620, 460);
	puthz(210, 75, "公告法规", 32, 40, MY_BLACK);
	puthz(430, 75, "常见问题", 32, 40, MY_BLACK);
	setfillstyle(SOLID_FILL, MY_YELLOW);
	bar(HELP_ANNOUNCE1_X1, HELP_ANNOUNCE1_Y1, HELP_ANNOUNCE1_X2, HELP_ANNOUNCE1_Y2);
	bar(HELP_ANNOUNCE2_X1, HELP_ANNOUNCE2_Y1, HELP_ANNOUNCE2_X2, HELP_ANNOUNCE2_Y2);
	bar(HELP_ANNOUNCE3_X1, HELP_ANNOUNCE3_Y1, HELP_ANNOUNCE3_X2, HELP_ANNOUNCE3_Y2);
	puthz(HELP_ANNOUNCE1_X1 + 6, HELP_ANNOUNCE1_Y1 + 7, "查看", 24, 22, MY_WHITE);
	puthz(HELP_ANNOUNCE2_X1 + 6, HELP_ANNOUNCE2_Y1 + 7, "查看", 24, 22, MY_WHITE);
	puthz(HELP_ANNOUNCE3_X1 + 6, HELP_ANNOUNCE3_Y1 + 7, "查看", 24, 22, MY_WHITE);
	puthz(200, 130, "电动车管理规范", 24, 22, MY_BLACK);
	puthz(210, 220, "电动车通行证", 24, 22, MY_BLACK);
	puthz(240, 250, "办理须知", 24, 22, MY_BLACK);
	puthz(200, 350, "官方联系方式", 24, 22, MY_BLACK);

	setfillstyle(SOLID_FILL, MY_YELLOW);
	bar(HELP_BUTTON1_X1, HELP_BUTTON1_Y1, HELP_BUTTON1_X2, HELP_BUTTON1_Y2);
	bar(HELP_BUTTON2_X1, HELP_BUTTON2_Y1, HELP_BUTTON2_X2, HELP_BUTTON2_Y2);
	bar(HELP_BUTTON3_X1, HELP_BUTTON3_Y1, HELP_BUTTON3_X2, HELP_BUTTON3_Y2);
	puthz(HELP_BUTTON1_X1 + 6, HELP_BUTTON1_Y1 + 7, "前往", 24, 22, MY_WHITE);
	puthz(HELP_BUTTON2_X1 + 6, HELP_BUTTON2_Y1 + 7, "前往", 24, 22, MY_WHITE);
	puthz(HELP_BUTTON3_X1 + 6, HELP_BUTTON3_Y1 + 7, "前往", 24, 22, MY_WHITE);
	puthz(435, 130, "修改电动车信息", 24, 22, MY_BLACK);
	puthz(435,240,"修改密码", 24, 22, MY_BLACK);
	puthz(435, 350, "查看违章", 24, 22, MY_BLACK);
}

void drawgraph_user_help_announce(int announce) {
	switch (announce) {
	case 1:
		puthz(250, 70, "电动车管理规范", 32, 40, MY_BLACK);
		puthz(170, 120, "一、登记注册：电动车须实名登记，核发校园通行证，有效期依身份类别设定，不得转让。学生通行证有效期不超过毕业剩余年限，外来人员需审批。鼓励购买保险。", 16, 18, MY_BLACK);
		puthz(170, 200, "二、行驶要求：持有效通行证方可进校，时速不超过十五公里，避让行人，禁改装、营运，须佩戴头盔。", 16, 18, MY_BLACK);
		puthz(170, 260, "三、停放与充电：车辆须停放在指定区域，禁入宿舍、楼道等场所；充电仅限充电桩，禁私拉电线。", 16, 18, MY_BLACK);
		puthz(170, 320, "四、违规处理：首次违规批评教育，再次通报，第三次注销通行证；涉及改装、充电安全等行为直接拖移；伪造证件、酒后驾驶等情节严重者移交公安机关。", 16, 18, MY_BLACK);
		puthz(170, 405, "五、闲置处理：超六个月未使用的车辆需注销，逾期按无主车处理。", 16, 20, MY_BLACK);
		break;
	case 2:
		puthz(210, 70, "电动车通行证办理通知", 32, 40, MY_BLACK);
		puthz(170, 130, "一、登记方式：师生员工通过用户主页——电动车通行证进入登记系统，按流程完成登记。", 16, 18, MY_BLACK);
		puthz(170, 200, "二、通行证申请前需阅读电动车管理规范，并通过电动车规则测试", 16, 18, MY_BLACK);
		puthz(170, 270, "三、通行证发放：二零二三年十月十二日起，车主可通过登记渠道预约时间和地点（紫菘、韵苑、沁苑）领取通行证。", 16, 18, MY_BLACK);
		puthz(170, 340, "四、注意事项：请在登记期限内完成登记，逾期将影响通行证核发。", 16, 18, MY_BLACK);
		puthz(170, 410, "五、咨询方式：如有疑问，请联系保卫处交通管理科咨询。", 16, 20, MY_BLACK);
		break;
	case 3:
		puthz(250, 70, "电动车管理服务信息", 32, 40, MY_BLACK);
		puthz(170, 120, "【官方平台】", 16, 18, MY_BLACK);
		puthz(170, 150, "微信公众号：华科电动车服务", 16, 18, MY_BLACK);
		puthz(170, 180, "官方微博：华中科技大学保卫处", 16, 18, MY_BLACK);

		settextstyle(DEFAULT_FONT, HORIZ_DIR, 1); //输出题目序号
		setcolor(MY_BLACK);
		puthz(170, 230, "【保卫处服务点】", 16, 18, MY_BLACK);
		puthz(170, 260, "东校区：韵苑公寓十八栋一楼，电话：", 16, 18, MY_BLACK);
		outtextxy(485, 267, "027-87541110");
		puthz(170, 290, "西校区：紫菘公寓三栋一楼，电话：", 16, 18, MY_BLACK);
		outtextxy(465, 297, "027-87542210");

		puthz(170, 340, "【业务办理时间】", 16, 18, MY_BLACK);
		puthz(170, 370, "工作日：八点三十至十二点，十四点至十八点", 16, 18, MY_BLACK);
		puthz(170, 400, "周末及节假日值班电话：", 16, 18, MY_BLACK);
		outtextxy(375, 407, "027-87549999");
		break;
	}
	setfillstyle(SOLID_FILL, MY_RED);
	bar(HELP_ANNOUNCE_BACK_X1, HELP_ANNOUNCE_BACK_Y1, HELP_ANNOUNCE_BACK_X2, HELP_ANNOUNCE_BACK_Y2);
	puthz(HELP_ANNOUNCE_BACK_X1 + 5, HELP_ANNOUNCE_BACK_Y1 + 5, "返回", 16, 18, MY_WHITE);
}





//电动车报废界面

void user_bike_wroteout(LINKLIST *LIST,int *page,unsigned long *id)
{
	int click = -99;
	int tag_main = 0;
	int tag_wroteout = -1;
	int flush_count = 0;
	int mouse_flag;
	int user_flag;
	int wroteout_flag;
	char count[8];
	char usrn[16]={ '\0' };
	char ebike_id_input[10]= { '\0' };
	char password_input[16] = {'\0'};
	int input_len=0;
	int tick;
	char second[][2] = { "5","4","3","2","1","0" };

	user_button UserButtons[] = {
{USER_BIKE_REGISTER_X1, USER_BIKE_REGISTER_X2,USER_BIKE_REGISTER_Y1, USER_BIKE_REGISTER_Y2,ACTIVE_USER_BIKE_REGISTER,USER_BIKE_REGISTER},
{USER_BIKE_LICENSE_X1, USER_BIKE_LICENSE_X2,USER_BIKE_LICENSE_Y1, USER_BIKE_LICENSE_Y2,ACTIVE_USER_BIKE_LICENSE,USER_BIKE_LICENSE_NOTICE},
{USER_ANNUAL_X1, USER_ANNUAL_X2,USER_ANNUAL_Y1, USER_ANNUAL_Y2,ACTIVE_USER_ANNUAL,USER_ANNUAL},
{USER_BIKE_WROTEOUT_X1, USER_BIKE_WROTEOUT_X2,USER_BIKE_WROTEOUT_Y1, USER_BIKE_WROTEOUT_Y2,ACTIVE_USER_BIKE_WROTEOUT,USER_BIKE_WROTEOUT},
{USER_INFO_X1, USER_INFO_X2,USER_INFO_Y1, USER_INFO_Y2,ACTIVE_USER_INFO,USER_INFO},
{USER_MESSAGE_X1, USER_MESSAGE_X2,USER_MESSAGE_Y1, USER_MESSAGE_Y2,ACTIVE_USER_MESSAGE,USER_MESSAGE},
{USER_HELP_X1, USER_HELP_X2,USER_HELP_Y1, USER_HELP_Y2,ACTIVE_USER_HELP,USER_HELP},
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

	//是否登记过电动车
	user_flag = user_ebike_register_judge(LIST,id);
	if (user_flag == 1) {
		puthz(180, 200, "您未注册电动车，请前往注册！", 32, 32, MY_BLACK);
		puthz(280, 300, "秒后转到电动车注册界面", 24, 22, MY_BLACK);
		while (tick <= 202) {
			newmouse_data(&MouseX, &MouseY, &press, &mouse_flag);
			flushUserMain(&tag_main, STRUCT_LENGTH(UserButtons), UserButtons);
			click = handle_click_main(STRUCT_LENGTH(UserButtons), UserButtons);
			if (click != -99 && click !=USER_BIKE_WROTEOUT) {          //其它页面做完后此处会改成click!=-1&&click!=USER_BIKE_LICENSE_NOTICE
				*page = click;
				return;
			}

			if (tick % 40 == 0) {
				setfillstyle(SOLID_FILL, MY_WHITE);
				bar(245, 280, 275, 330);
				settextstyle(DEFAULT_FONT, HORIZ_DIR, 2); // 默认字体，水平方向，大小2
				setcolor(MY_BLACK);
				outtextxy(250, 305, second[tick / 40]);
			}
			newmouse(&MouseX, &MouseY, &press, &mouse_flag);
			delay(25);
			tick++;
		}
		*page = USER_BIKE_REGISTER;
		return;
	}
	drawgraph_user_bike_wroteout_warning();
	//进入电动车报废功能界面前的警告页面
	while (1) {
		newmouse_data(&MouseX, &MouseY, &press,&mouse_flag);//刷新鼠标数据
		flushUserMain(&tag_main, STRUCT_LENGTH(UserButtons), UserButtons); // 刷新界面
		flushUserWroteoutWarning();
		click = handle_click_main(STRUCT_LENGTH(UserButtons), UserButtons);
		if (click != -99 && click != USER_BIKE_WROTEOUT) {          //其它页面做完后此处会改成click!=-1&&click!=USER_BIKE_LICENSE
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
		newmouse(&MouseX, &MouseY, &press, &mouse_flag);//在可能改变背景的操作后绘制鼠标
		delay(25);
	}
	drawgraph_user_wroteout();
	//电动车报废功能界面
	while (1) {
		newmouse_data(&MouseX, &MouseY, &press, &mouse_flag);
		flushUserMain(&tag_main, STRUCT_LENGTH(UserButtons), UserButtons); // 刷新界面
		flushUserWroteout(&tag_wroteout,WroteoutButtons);
		click = handle_click_main(STRUCT_LENGTH(UserButtons), UserButtons);
		if (click != -99 && click != USER_BIKE_WROTEOUT) {          //其它页面做完后此处会改成click!=-1&&click!=USER_BIKE_LICENSE
			*page = click;
			ch_input(NULL, NULL, NULL, NULL, NULL, INPUTBAR_CLEAR, NULL);
			return;
		}
		if (mouse_press(USER_BIKE_WROTEOUT_INPUT1_X1, USER_BIKE_WROTEOUT_INPUT1_Y1, USER_BIKE_WROTEOUT_INPUT1_X2, USER_BIKE_WROTEOUT_INPUT1_Y2) == 1) {
			input_len = hz_input(USER_BIKE_WROTEOUT_INPUT1_X1+5, USER_BIKE_WROTEOUT_INPUT1_Y1+5, USER_BIKE_WROTEOUT_INPUT1_X2-3, USER_BIKE_WROTEOUT_INPUT1_Y2-3, usrn, input_len, MY_WHITE, MY_BLACK, 24);
		}
		if (mouse_press(USER_BIKE_WROTEOUT_INPUT2_X1, USER_BIKE_WROTEOUT_INPUT2_Y1, USER_BIKE_WROTEOUT_INPUT2_X2, USER_BIKE_WROTEOUT_INPUT2_Y2) == 1) {
			ch_input(ebike_id_input,USER_BIKE_WROTEOUT_INPUT2_X1+2, USER_BIKE_WROTEOUT_INPUT2_Y1+2,10, MY_WHITE,0,1);
		}
		if (mouse_press(USER_BIKE_WROTEOUT_INPUT3_X1, USER_BIKE_WROTEOUT_INPUT3_Y1, USER_BIKE_WROTEOUT_INPUT3_X2, USER_BIKE_WROTEOUT_INPUT3_Y2) == 1) {
			ch_input(password_input,USER_BIKE_WROTEOUT_INPUT3_X1+2, USER_BIKE_WROTEOUT_INPUT3_Y1+2,14, MY_WHITE, 0,0);
		}
		if (mouse_press(USER_BIKE_WROTEOUT_BUTTON1_X1, USER_BIKE_WROTEOUT_BUTTON1_Y1, USER_BIKE_WROTEOUT_BUTTON1_X2, USER_BIKE_WROTEOUT_BUTTON1_Y2) == 1) {
			wroteout_flag = wroteout_info_judge(LIST,usrn, ebike_id_input, password_input, id);
			if (wroteout_flag == 0) {
				wroteout_delete_data(id);
				anime_login_success_user(USER_BIKE_WROTEOUT_BUTTON1_X1, USER_BIKE_WROTEOUT_BUTTON1_Y1, USER_BIKE_WROTEOUT_BUTTON1_X2, USER_BIKE_WROTEOUT_BUTTON1_Y2);
				setfillstyle(SOLID_FILL, MY_WHITE);
				bar(150, 60, 640, 480);
				puthz(280, 200, "您已申请成功", 32, 40, MY_BLACK);
				puthz(245, 260, "即将返回主界面", 32, 40, MY_BLACK);
				delay(3000);
				*page = MAIN_USER;
				ch_input(NULL, NULL, NULL, NULL, NULL, INPUTBAR_CLEAR, NULL);
				return;
			}
			else
				draw_user_wroteout_fail(wroteout_flag);
		}
		if (mouse_press(USER_BIKE_WROTEOUT_BUTTON2_X1, USER_BIKE_WROTEOUT_BUTTON2_Y1, USER_BIKE_WROTEOUT_BUTTON2_X2, USER_BIKE_WROTEOUT_BUTTON2_Y2) == 1) {
			*page = USER_MESSAGE;
			return;
		}
        newmouse(&MouseX, &MouseY, &press, &mouse_flag);
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
	setfillstyle(SOLID_FILL, MY_YELLOW);
	bar(USER_BIKE_WROTEOUT_BUTTON2_X1, USER_BIKE_WROTEOUT_BUTTON2_Y1, USER_BIKE_WROTEOUT_BUTTON2_X2, USER_BIKE_WROTEOUT_BUTTON2_Y2);
	puthz(USER_BIKE_WROTEOUT_BUTTON2_X1 + 15, USER_BIKE_WROTEOUT_BUTTON2_Y1 + 8, "反馈", 24, 20, MY_WHITE);

}


void drawgraph_user_wroteout() {
	setcolor(MY_LIGHTGRAY);
	setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
	rectangle(USER_BIKE_WROTEOUT_INPUT1_X1+2, USER_BIKE_WROTEOUT_INPUT1_Y1+2, USER_BIKE_WROTEOUT_INPUT1_X2-2, USER_BIKE_WROTEOUT_INPUT1_Y2-2);
	rectangle(USER_BIKE_WROTEOUT_INPUT2_X1+2, USER_BIKE_WROTEOUT_INPUT2_Y1+2, USER_BIKE_WROTEOUT_INPUT2_X2-2, USER_BIKE_WROTEOUT_INPUT2_Y2-2);
	rectangle(USER_BIKE_WROTEOUT_INPUT3_X1+2, USER_BIKE_WROTEOUT_INPUT3_Y1+2, USER_BIKE_WROTEOUT_INPUT3_X2-2, USER_BIKE_WROTEOUT_INPUT3_Y2-2);
	puthz(220, 85, "请输入姓名，车牌号与账号密码以确认身份", 24, 20, MY_BLACK);
	puthz(170, 155, "姓名", 24, 20, MY_BLACK);
	puthz(170, 230, "车牌号",24, 20, MY_BLACK);
	puthz(170, 300, "密码", 24, 20, MY_BLACK);

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

int wroteout_info_judge(LINKLIST *LIST,char* usrn, char* ebike_id, char* password, unsigned long *id) {
	int i = 0;
	char e_bike_license[10];
	int account_counts_password;
	int account_counts_wroteout;
	
	EBIKE_INFO TEMP, USER;
	USER_LOGIN_DATA TEMP_LOGIN;
	FILE* fp_EBIKE_INFO_WROTEOUT_readndwrite = fopen("DATA\\BROKEN.DAT", "rb+");
	FILE* fp_LOGIN_DATA_WROTEOUT_read = fopen("DATA\\USER.DAT", "rb");
	if (fp_EBIKE_INFO_WROTEOUT_readndwrite == NULL) {
		fclose(fp_EBIKE_INFO_WROTEOUT_readndwrite);
		exit(0);
	}
	if (fp_LOGIN_DATA_WROTEOUT_read == NULL) {
		fclose(fp_LOGIN_DATA_WROTEOUT_read);
		exit(0);
	}
	
	user_bike_register_getinfo(LIST,&USER, id);

	if (strcmp(USER.ebike_ID, ebike_id) != 0) {//车牌号与ID不匹配
		if (fclose(fp_EBIKE_INFO_WROTEOUT_readndwrite) != 0) getch(), exit(1);
		if (fclose(fp_LOGIN_DATA_WROTEOUT_read) != 0)getch(), exit(1);
		return 1;
	}
	if (strcmp(USER.rln, usrn) != 0) {//姓名与ID不匹配
		if (fclose(fp_EBIKE_INFO_WROTEOUT_readndwrite) != 0) getch(), exit(1);
		if (fclose(fp_LOGIN_DATA_WROTEOUT_read) != 0)getch(), exit(1);
		return 2;
	}

	fseek(fp_LOGIN_DATA_WROTEOUT_read, 0, SEEK_END);
	account_counts_password = ftell(fp_LOGIN_DATA_WROTEOUT_read) / sizeof(USER_LOGIN_DATA);//初始操作完成，接下来开始遍历数据

	for (i = 0; i < account_counts_password; i++) {
		fseek(fp_LOGIN_DATA_WROTEOUT_read, i * sizeof(USER_LOGIN_DATA), SEEK_SET);
		fread(&TEMP_LOGIN, sizeof(USER_LOGIN_DATA), 1, fp_LOGIN_DATA_WROTEOUT_read); //逐个读取，每个用户信息，直到用户名与密码均匹配

		if (TEMP_LOGIN.ID==*id) {
			if (strcmp(TEMP_LOGIN.psw,password)!=0) {//密码与ID不匹配
				if (fclose(fp_EBIKE_INFO_WROTEOUT_readndwrite) != 0) getch(), exit(1);
				if (fclose(fp_LOGIN_DATA_WROTEOUT_read) != 0)getch(), exit(1);
				return 3;
			}
			break;
		}

	}
	if (fclose(fp_LOGIN_DATA_WROTEOUT_read) != 0)getch(), exit(1);
	
	memset(&TEMP, 0, sizeof(TEMP));
	fseek(fp_EBIKE_INFO_WROTEOUT_readndwrite, 0, SEEK_END);
	account_counts_wroteout = ftell(fp_EBIKE_INFO_WROTEOUT_readndwrite) / sizeof(EBIKE_INFO);//初始操作完成，接下来开始遍历数据

	for (i = 0; i < account_counts_wroteout; i++) {
		fseek(fp_EBIKE_INFO_WROTEOUT_readndwrite, i * sizeof(EBIKE_INFO), SEEK_SET);
		fread(&TEMP, sizeof(EBIKE_INFO), 1, fp_EBIKE_INFO_WROTEOUT_readndwrite); //逐个读取，每个用户信息

		if (TEMP.ID == *id) {
			if (strcmp(USER.ebike_ID, TEMP.ebike_ID) == 0) {
				if (fclose(fp_EBIKE_INFO_WROTEOUT_readndwrite) != 0) getch(), exit(1); //发现ID和车牌号均相同的，说明此车申请过报废，不能再申请
				return 4;
			}
		}	
	}

	//若经过了for循环仍未经过return，则代表电动车未申请报废，可申请
	strcpy(TEMP.rln, USER.rln);			//获取账密和uid
	strcpy(TEMP.ebike_ID, USER.ebike_ID);
	strcpy(TEMP.ebike_license, "0");
	strcpy(TEMP.location, "0");
	TEMP.ID = *id;
	TEMP.apply_time = get_approx_time(NULL);
	TEMP.conduct_time = 0;
	TEMP.result = PENDING;
	TEMP.anual_check = 0;
	TEMP.violations = 0;
	fseek(fp_EBIKE_INFO_WROTEOUT_readndwrite, 0, SEEK_END); // 确保写入位置在文件末尾
	fwrite(&TEMP, sizeof(EBIKE_INFO), 1, fp_EBIKE_INFO_WROTEOUT_readndwrite);  //将注册信息写入文件
	if (fclose(fp_EBIKE_INFO_WROTEOUT_readndwrite) != 0) getch(), exit(1);
	return 0;

}

void wroteout_delete_data(unsigned long* id) {
	int i = 0;
	int account_counts;
	int position;
	EBIKE_INFO TEMP;
	EBIKE_MOREINFO moreinfo;

	FILE* fp_EBIKE_INFO_readndwrite = fopen("DATA\\REGISTER.DAT", "rb+");
	FILE* fp_EBIKE_MOREINFO_readndwrite = fopen("DATA\\MOREINFO.DAT", "rb+");
	if (fp_EBIKE_INFO_readndwrite == NULL) {
		fclose(fp_EBIKE_INFO_readndwrite);
		exit(0);
	}
	if (fp_EBIKE_MOREINFO_readndwrite == NULL) {
		fclose(fp_EBIKE_INFO_readndwrite);
		exit(0);
	}
	
	/*memset(&TEMP, 0, sizeof(TEMP));
	fseek(fp_EBIKE_INFO_readndwrite, 0, SEEK_END);
	account_counts = ftell(fp_EBIKE_INFO_readndwrite) / sizeof(EBIKE_INFO);//初始操作完成，接下来开始遍历数据

	for (i = 0; i < account_counts; i++) {
		fseek(fp_EBIKE_INFO_readndwrite, i * sizeof(EBIKE_INFO), SEEK_SET);
		fread(&TEMP, sizeof(EBIKE_INFO), 1, fp_EBIKE_INFO_readndwrite); //逐个读取，每个用户信息
		if (TEMP.ID == *id) {
			position = i;
			break;
		}
	}
	strcpy(TEMP.rln, "0");			//获取账密和uid
	strcpy(TEMP.ebike_ID, "0");
	strcpy(TEMP.ebike_license, "0");
	strcpy(TEMP.location, "0");
	TEMP.ID = 0;
	TEMP.apply_time = 0;
	TEMP.conduct_time = 0;
	TEMP.result = 0;
	TEMP.anual_check = 0;
	TEMP.violations = 0;
	fseek(fp_EBIKE_INFO_readndwrite, position * sizeof(EBIKE_INFO), SEEK_SET);
	fwrite(&TEMP, sizeof(EBIKE_INFO), 1, fp_EBIKE_INFO_readndwrite);*/



	memset(&moreinfo, 0, sizeof(moreinfo));
	fseek(fp_EBIKE_MOREINFO_readndwrite, 0, SEEK_END);
	account_counts = ftell(fp_EBIKE_MOREINFO_readndwrite) / sizeof(EBIKE_MOREINFO);//初始操作完成，接下来开始遍历数据
	position = account_counts;
	for (i = 0; i < account_counts; i++) {
		fseek(fp_EBIKE_MOREINFO_readndwrite, i * sizeof(EBIKE_MOREINFO), SEEK_SET);
		fread(&moreinfo, sizeof(EBIKE_MOREINFO), 1, fp_EBIKE_MOREINFO_readndwrite); //逐个读取，每个用户信息
		if (moreinfo.id == *id) {
			position = i;
			break;
		}
	}
	strcpy(moreinfo.battery, "0");			//获取账密和uid
	strcpy(moreinfo.color, "0");
	strcpy(moreinfo.length, "0");
	strcpy(moreinfo.weight, "0");
	moreinfo.id = 0;
	moreinfo.is_quiz = 0;
	//moreinfo.is_broken = 1;
	fseek(fp_EBIKE_MOREINFO_readndwrite, position * sizeof(EBIKE_MOREINFO), SEEK_SET);
	fwrite(&TEMP, sizeof(EBIKE_INFO), 1, fp_EBIKE_INFO_readndwrite);


	if (fclose(fp_EBIKE_MOREINFO_readndwrite) != 0) getch(), exit(1);
	if (fclose(fp_EBIKE_INFO_readndwrite) != 0) getch(), exit(1);
	return 0;

}


void draw_user_wroteout_fail(int wroteout_flag) {
	setfillstyle(SOLID_FILL, MY_WHITE);
	bar(295, 195, 500, 225);
	bar(295, 115, 500, 145);
	bar(295, 275, 500, 305);
	bar(195, 370, 550, 405);
	switch (wroteout_flag) {
	case 1:
		puthz(300, 205, "车牌号错误", 24, 22, MY_RED);
		break;
	case 2:
		puthz(300, 125, "姓名错误", 24, 22, MY_RED);
		break;
	case 3:
		puthz(300, 285, "密码错误", 24, 22, MY_RED);
		break;
	case 4:
		puthz(200, 385, "此电动车报废正在申请或已申请成功", 24, 22, MY_RED);
		break;
	}
}












void user_annual(LINKLIST *LIST,int* page, unsigned long* id) {
	int tag = 0;
	int register_flag;
	int click = -1;
	int mouse_flag;
	int annual_flag;
	int active_button = 0;
	char usrn[16] = { '\0' }; // 初始化为空
	int hz_input_len = 0;//汉字输入框的汉字数量
	char e_bike_id[10] = { '\0' };
	int tick=0;
	char second[][2] = { "5","4","3","2","1","0" };
	user_button UserButtons[] = {
{USER_BIKE_REGISTER_X1, USER_BIKE_REGISTER_X2,USER_BIKE_REGISTER_Y1, USER_BIKE_REGISTER_Y2,ACTIVE_USER_BIKE_REGISTER,USER_BIKE_REGISTER},
{USER_BIKE_LICENSE_X1, USER_BIKE_LICENSE_X2,USER_BIKE_LICENSE_Y1, USER_BIKE_LICENSE_Y2,ACTIVE_USER_BIKE_LICENSE,USER_BIKE_LICENSE_NOTICE},
{USER_ANNUAL_X1, USER_ANNUAL_X2,USER_ANNUAL_Y1, USER_ANNUAL_Y2,ACTIVE_USER_ANNUAL,USER_ANNUAL},
{USER_BIKE_WROTEOUT_X1, USER_BIKE_WROTEOUT_X2,USER_BIKE_WROTEOUT_Y1, USER_BIKE_WROTEOUT_Y2,ACTIVE_USER_BIKE_WROTEOUT,USER_BIKE_WROTEOUT},
{USER_INFO_X1, USER_INFO_X2,USER_INFO_Y1, USER_INFO_Y2,ACTIVE_USER_INFO,USER_INFO},
{USER_MESSAGE_X1, USER_MESSAGE_X2,USER_MESSAGE_Y1, USER_MESSAGE_Y2,ACTIVE_USER_MESSAGE,USER_MESSAGE},
{USER_HELP_X1, USER_HELP_X2,USER_HELP_Y1, USER_HELP_Y2,ACTIVE_USER_HELP,USER_HELP},
{USER_BACK_X1,USER_BACK_X2,USER_BACK_Y1,USER_BACK_Y2,ACTIVE_USER_BACK,LOGIN},
{USER_EXIT_X1,USER_EXIT_X2,USER_EXIT_Y1,USER_EXIT_Y2,ACTIVE_USER_EXIT,EXIT},
	};
	clrmous(MouseX, MouseY);
	save_bk_mou(MouseX, MouseY);
	drawgraph_user_main(page);

	register_flag = user_ebike_register_judge(LIST,id);
	if (register_flag==1) {
		puthz(180, 200, "您未注册电动车，请前往注册！", 32, 32, MY_BLACK);
		puthz(280, 300, "秒后转到电动车注册界面", 24, 22, MY_BLACK);
		while (tick <= 202) {
			newmouse_data(&MouseX, &MouseY, &press, &mouse_flag);
			flushUserMain(&tag, STRUCT_LENGTH(UserButtons), UserButtons);
			click = handle_click_main(STRUCT_LENGTH(UserButtons), UserButtons);
			if (click == LOGIN || click == EXIT || click == USER_BIKE_REGISTER || click == USER_BIKE_LICENSE_NOTICE || click == USER_BIKE_WROTEOUT || click == USER_INFO || click == USER_HELP) {          //其它页面做完后此处会改成click!=-1&&click!=USER_BIKE_LICENSE_NOTICE
				*page = click;
				return;
			}
			if (tick % 40 == 0) {
				setfillstyle(SOLID_FILL, MY_WHITE);
				bar(245, 280, 275, 330);
				settextstyle(DEFAULT_FONT, HORIZ_DIR, 2); // 默认字体，水平方向，大小2
				setcolor(MY_BLACK);
				outtextxy(250, 305, second[tick / 40]);
			}
			newmouse(&MouseX, &MouseY, &press, &mouse_flag);
			delay(25);
			tick++;
		}
		*page = USER_BIKE_REGISTER;
		return;
	}
	annual_flag = ebike_annual_judge(LIST,id);

	drawgraph_user_bike_annual(annual_flag);
	while (1) {
		newmouse_data(&MouseX, &MouseY, &press, &mouse_flag);
		flushUserMain(&tag, STRUCT_LENGTH(UserButtons), UserButtons);
		click = handle_click_main(STRUCT_LENGTH(UserButtons), UserButtons);
		if (click == LOGIN || click == EXIT || click == USER_BIKE_REGISTER || click == USER_BIKE_LICENSE_NOTICE || click == USER_BIKE_WROTEOUT || click == USER_INFO || click == USER_HELP) {          //其它页面做完后此处会改成click!=-1&&click!=USER_BIKE_LICENSE_NOTICE
			*page = click;
			return;
		}
		if (mouse_press(USER_ANNUAL_BUTTON1_X1, USER_ANNUAL_BUTTON1_Y1, USER_ANNUAL_BUTTON1_X2, USER_ANNUAL_BUTTON1_Y2) == 1 && annual_flag==0) {//未年审
			user_annual_write(LIST,id);
			setfillstyle(SOLID_FILL, MY_WHITE);
			bar(150, 60, 640, 480);
			puthz(280, 200, "您已提交成功", 32, 40, MY_BLACK);
			puthz(245, 260, "即将返回主界面", 32, 40, MY_BLACK);
			delay(3000);
			*page = MAIN_USER;
			return;
		}
		if (mouse_press(USER_ANNUAL_BUTTON1_X1, USER_ANNUAL_BUTTON1_Y1, USER_ANNUAL_BUTTON1_X2, USER_ANNUAL_BUTTON1_Y2) == 1 && annual_flag == 1) {//已经年审
			setfillstyle(SOLID_FILL, MY_WHITE);
			bar(150, 60, 640, 480);
			puthz(220, 200, "您已提交过年审信息", 32, 40, MY_BLACK);
			puthz(245, 260, "即将前往反馈", 32, 40, MY_BLACK);
			delay(3000);
			*page = USER_MESSAGE_OUT;
			return;
		}
		if (MouseX >= USER_ANNUAL_BUTTON1_X1 && MouseX <= USER_ANNUAL_BUTTON1_X2 && MouseY >= USER_ANNUAL_BUTTON1_Y1 && MouseY <= USER_ANNUAL_BUTTON1_Y2 ) {
			MouseS = 1;
			if (active_button !=1) {
				setcolor(MY_BLACK);
				rectangle(USER_ANNUAL_BUTTON1_X1 - 1, USER_ANNUAL_BUTTON1_Y1 - 1, USER_ANNUAL_BUTTON1_X2 + 1, USER_ANNUAL_BUTTON1_Y2 + 1);
			}
			active_button = 1;
		}
		else if (active_button == 1 ) {
			setcolor(MY_WHITE);
			rectangle(USER_ANNUAL_BUTTON1_X1 - 1, USER_ANNUAL_BUTTON1_Y1 - 1, USER_ANNUAL_BUTTON1_X2 + 1, USER_ANNUAL_BUTTON1_Y2 + 1);
			active_button = 0;
		}
		newmouse(&MouseX, &MouseY, &press, &mouse_flag);
		delay(25);
	}
}

void drawgraph_user_bike_annual(int flag) {
	puthz(250, 70, "电动车年审流程说明", 32, 35, MY_BLACK);
	puthz(180, 115, "准备材料：包括身份证原件、购车发票、车辆合格证以及电动车行驶证（如有），部分车型还需提供交强险凭证。", 16, 18, MY_BLACK);
	puthz(180, 175, "办理方式：前往车管所或指定检测站办理，也可在武汉交警小程序线上提交部分业务，建议提前电话咨询确认办理地点和线上可办范围。", 16, 18, MY_BLACK);
	puthz(180, 255, "注意：若您的电动车属于旧国标，需注意武汉的过渡期政策，部分旧标车需在规定期限内更换牌照或淘汰，具体规定可向车管所咨询确认。", 16, 18, MY_BLACK);
	puthz(180, 335, "提示：办理时建议提前预约，避开高峰期，尤其是学生群体可选择工作日早间前往以提高效率。", 16, 18, MY_BLACK);
	setfillstyle(SOLID_FILL, MY_RED);
	bar(USER_ANNUAL_BUTTON1_X1, USER_ANNUAL_BUTTON1_Y1, USER_ANNUAL_BUTTON1_X2, USER_ANNUAL_BUTTON1_Y2);
	if(flag==0){
		puthz(240, 410, "若您的电动车今年已参与年审，请点击按钮", 16, 18, MY_GREEN);
		puthz(USER_ANNUAL_BUTTON1_X1 + 10, USER_ANNUAL_BUTTON1_Y1 + 5, "已参与", 16, 18, MY_WHITE);
	}
	else {
		puthz(180, 410, "您已确认电动车参与年审，若未参与，点击按钮前往反馈", 16, 18, MY_GREEN);
		puthz(USER_ANNUAL_BUTTON1_X1 + 10, USER_ANNUAL_BUTTON1_Y1 + 5, "去反馈", 16, 18, MY_WHITE);
	}
	
	
}

void user_annual_write(LINKLIST *LIST,unsigned long* id) {
	int i ;

	EBIKE_INFO TEMP,INFO;
	FILE* fp_EBIKE_ANNUAL_readndwrite = fopen("DATA\\ANUAL.DAT", "rb+");
	if (fp_EBIKE_ANNUAL_readndwrite == NULL) {
		fclose(fp_EBIKE_ANNUAL_readndwrite);
		exit(0);
	}
	user_bike_register_getinfo(LIST,&INFO, id);
	INFO.result= PENDING;
    INFO.conduct_time = 0;
	INFO.ID = *id;
	INFO.apply_time = get_approx_time(NULL);
	INFO.anual_check = get_approx_time(NULL);
	
	fseek(fp_EBIKE_ANNUAL_readndwrite, 0, SEEK_END); // 确保写入位置在文件末尾
	fwrite(&INFO, sizeof(EBIKE_INFO), 1, fp_EBIKE_ANNUAL_readndwrite);
		
	if (fclose(fp_EBIKE_ANNUAL_readndwrite) != 0) getch(), exit(1);
	return;
}

int ebike_annual_judge(LINKLIST *LIST,unsigned long* id) {
	/*int i;
	int account_counts;

	EBIKE_INFO TEMP;
	FILE* fp_EBIKE_ANNUAL_read = fopen("DATA\\ANUAL.DAT", "rb");
	if (fp_EBIKE_ANNUAL_read == NULL) {
		fclose(fp_EBIKE_ANNUAL_read);
		exit(0);
	}

	memset(&TEMP, 0, sizeof(TEMP));
	fseek(fp_EBIKE_ANNUAL_read, 0, SEEK_END);
	account_counts = ftell(fp_EBIKE_ANNUAL_read) / sizeof(EBIKE_INFO);//初始操作完成，接下来开始遍历数据

	for (i = 0; i < account_counts; i++) {
		fseek(fp_EBIKE_ANNUAL_read, i * sizeof(EBIKE_INFO), SEEK_SET);
		fread(&TEMP, sizeof(EBIKE_INFO), 1, fp_EBIKE_ANNUAL_read); //逐个读取，每个用户信息

		if (*id == TEMP.ID) {
			fclose(fp_EBIKE_ANNUAL_read);
			return 1;
		}
	}
	fclose(fp_EBIKE_ANNUAL_read);
	return 0;*/
	EBIKE_INFO TEMP;
	user_bike_register_getinfo(LIST, &TEMP, id);
	if (TEMP.anual_check != 0) {
		return 1;
	}
	return 0;
}






















//电动车规则测试界面

void user_quiz(int* page, unsigned long* id) {
	int i, j, k;
	int tag = -1;
	int box_tag = -1;
	int quiz_page = 1;
	char start_time[8];
	int remain_sec = LASTING_TIME;
	int tick=0;
	int mouse_flag = 1;
	int pass_flag;

	question quiz[QUIZ_PAGE_COUNT][QUESTION_PER_PAGE];
	char answer[QUIZ_PAGE_COUNT][QUESTION_PER_PAGE] = { '\0' };
	int result[QUIZ_PAGE_COUNT][QUESTION_PER_PAGE] = {'\0'};
	int position_xy[QUESTION_PER_PAGE][2] = {
		{60,70},{60,190},{60,310}
	};

	user_button quiz_buttons[] = {
		{USER_QUIZ_BUTTON1_X1, USER_QUIZ_BUTTON1_X2, USER_QUIZ_BUTTON1_Y1, USER_QUIZ_BUTTON1_Y2,1},
		{USER_QUIZ_BUTTON2_X1, USER_QUIZ_BUTTON2_X2, USER_QUIZ_BUTTON2_Y1, USER_QUIZ_BUTTON2_Y2,2},
		{USER_QUIZ_BUTTON3_X1, USER_QUIZ_BUTTON3_X2, USER_QUIZ_BUTTON3_Y1, USER_QUIZ_BUTTON3_Y2,3},
		{USER_QUIZ_EXIT_X1, USER_QUIZ_EXIT_X2, USER_QUIZ_EXIT_Y1, USER_QUIZ_EXIT_Y2,4},
		{USER_QUIZ_BACK_X1,USER_QUIZ_BACK_X2,USER_QUIZ_BACK_Y1,USER_QUIZ_BACK_Y2,5}
	};
	user_button result_buttons[] = {
		{USER_QUIZ_RESULT_BUTTON1_X1, USER_QUIZ_RESULT_BUTTON1_X2, USER_QUIZ_RESULT_BUTTON1_Y1, USER_QUIZ_RESULT_BUTTON1_Y2, 1},
		{USER_QUIZ_RESULT_BUTTON2_X1, USER_QUIZ_RESULT_BUTTON2_X2, USER_QUIZ_RESULT_BUTTON2_Y1, USER_QUIZ_RESULT_BUTTON2_Y2, 2},
		{USER_QUIZ_EXIT_X1, USER_QUIZ_EXIT_X2, USER_QUIZ_EXIT_Y1, USER_QUIZ_EXIT_Y2,3},
		{USER_QUIZ_BACK_X1,USER_QUIZ_BACK_X2,USER_QUIZ_BACK_Y1,USER_QUIZ_BACK_Y2,4}
	};

	//store_data();
    generate_quiz(quiz, QUIZ_PAGE_COUNT, position_xy);//根据题库生成测试题
	
	//须知页面
	drawgraph_quiz_notice();
	tick = 800;
	while (tick>=0) {
		newmouse_data(&MouseX, &MouseY, &press, &mouse_flag);
		if (tick % 20 == 0) {
			sprintf(start_time, "%02d", tick / 40);
			setfillstyle(SOLID_FILL, MY_WHITE);
			bar(290, 290, 330, 330);
			settextstyle(DEFAULT_FONT, HORIZ_DIR, 2); //输出题目序号
			setcolor(MY_GREEN);
			outtextxy(300, 303,start_time);
		}	
		tick--;
		newmouse(&MouseX, &MouseY, &press, &mouse_flag);
		delay(25);
	}

	//考试界面
	clrmous(MouseX, MouseY);
	save_bk_mou(MouseX, MouseY);
	drawgraph_user_quiz(&quiz_page, QUIZ_PAGE_COUNT);
	draw_quiz(quiz[quiz_page - 1], QUESTION_PER_PAGE);

	while (1) {
		newmouse_data(&MouseX, &MouseY, &press,&mouse_flag);
		flushUserQuiz(&tag,&box_tag,quiz_buttons,quiz[quiz_page-1],answer[quiz_page-1],quiz_page,1);
		handle_click_quiz(quiz[quiz_page - 1], answer[quiz_page - 1], QUESTION_PER_PAGE);
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
			draw_quiz(quiz[quiz_page-1], QUESTION_PER_PAGE);
			printbox(quiz[quiz_page - 1], answer[quiz_page - 1]);
		}
		//下一页
		if (mouse_press(USER_QUIZ_BUTTON2_X1, USER_QUIZ_BUTTON2_Y1, USER_QUIZ_BUTTON2_X2, USER_QUIZ_BUTTON2_Y2) == 1 && quiz_page != QUIZ_PAGE_COUNT) {
			quiz_page += 1;
			drawgraph_user_quiz(&quiz_page, QUIZ_PAGE_COUNT);
			draw_quiz(quiz[quiz_page-1], QUESTION_PER_PAGE);
			printbox(quiz[quiz_page - 1], answer[quiz_page - 1]);
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

		newmouse(&MouseX, &MouseY, &press, &mouse_flag);
		delay(25);
	}

	//结果界面
	pass_flag = judge_answer(quiz, answer, result, QUIZ_PAGE_COUNT);
	if (pass_flag != 0) {
		drawgraph_user_quiz_pass(result, QUIZ_PAGE_COUNT);
		write_quiz_result_to_file(id);
	}	
	else 
		drawgraph_user_quiz_fail(result, QUIZ_PAGE_COUNT);

	while (1) {
		newmouse_data(&MouseX, &MouseY, &press, &mouse_flag);
		FlushQuizResult(&tag, result_buttons);

		if (mouse_press(USER_QUIZ_RESULT_BUTTON1_X1, USER_QUIZ_RESULT_BUTTON1_Y1, USER_QUIZ_RESULT_BUTTON1_X2, USER_QUIZ_RESULT_BUTTON1_Y2) == 1) //点击“回顾”，跳出循环，进入试卷回顾
		{
			break;
		}
		if (mouse_press(USER_QUIZ_RESULT_BUTTON2_X1, USER_QUIZ_RESULT_BUTTON2_Y1, USER_QUIZ_RESULT_BUTTON2_X2, USER_QUIZ_RESULT_BUTTON2_Y2) == 1 && pass_flag) //通过测试，点击“继续”按钮前往预约通行证界面
		{
			*page = USER_BIKE_LICENSE;
			return;
		}
		if (mouse_press(USER_QUIZ_RESULT_BUTTON2_X1, USER_QUIZ_RESULT_BUTTON2_Y1, USER_QUIZ_RESULT_BUTTON2_X2, USER_QUIZ_RESULT_BUTTON2_Y2) == 1 && (!pass_flag))//未通过测试，点击“重试”重新测试 
		{
			*page = USER_QUIZ;
			return;
		}
		if (mouse_press(USER_QUIZ_BACK_X1, USER_QUIZ_BACK_Y1, USER_QUIZ_BACK_X2, USER_QUIZ_BACK_Y2) == 1) {
			delay(1000);
			*page = MAIN_USER;
			return;
		}
		if (mouse_press(USER_QUIZ_EXIT_X1, USER_QUIZ_EXIT_Y1, USER_QUIZ_EXIT_X2, USER_QUIZ_EXIT_Y2) == 1) {
			*page = EXIT;
			return;
		}
		newmouse(&MouseX, &MouseY, &press, &mouse_flag);
		delay(25);
	}

	//试卷回顾页面
	quiz_page = 1;
	drawgraph_quiz_review(&quiz_page, QUIZ_PAGE_COUNT, pass_flag);
	draw_quiz_answer(quiz[quiz_page - 1], answer[quiz_page - 1], QUESTION_PER_PAGE);

	while (1) {
		newmouse_data(&MouseX, &MouseY, &press, &mouse_flag);
		flushUserQuiz(&tag, &box_tag, quiz_buttons, quiz[quiz_page - 1], answer[quiz_page - 1], quiz_page,0);
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
			drawgraph_quiz_review(&quiz_page, QUIZ_PAGE_COUNT, pass_flag);
			draw_quiz_answer(quiz[quiz_page - 1], answer[quiz_page - 1], QUESTION_PER_PAGE);
		}
		//下一页
		if (mouse_press(USER_QUIZ_BUTTON2_X1, USER_QUIZ_BUTTON2_Y1, USER_QUIZ_BUTTON2_X2, USER_QUIZ_BUTTON2_Y2) == 1 && quiz_page != QUIZ_PAGE_COUNT) {
			quiz_page += 1;
			drawgraph_quiz_review(&quiz_page, QUIZ_PAGE_COUNT, pass_flag);
			draw_quiz_answer(quiz[quiz_page - 1], answer[quiz_page - 1], QUESTION_PER_PAGE);
		}
		//前往通行证预约
		if (mouse_press(USER_QUIZ_BUTTON3_X1, USER_QUIZ_BUTTON3_Y1, USER_QUIZ_BUTTON3_X2, USER_QUIZ_BUTTON3_Y2) == 1 && pass_flag) {
			*page = USER_BIKE_LICENSE;
			return;
		}
		//重新测试
		if (mouse_press(USER_QUIZ_BUTTON3_X1, USER_QUIZ_BUTTON3_Y1, USER_QUIZ_BUTTON3_X2, USER_QUIZ_BUTTON3_Y2) == 1 && (!pass_flag)) {
			*page = USER_QUIZ;
			return;
		}
		newmouse(&MouseX, &MouseY, &press, &mouse_flag);
		delay(25);
	}

}
	
void drawgraph_quiz_notice() {

	setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
	bar(0, 0, 640, 480);
	setcolor(MY_WHITE);
	setfillstyle(1, MY_WHITE);
	bar(10, 50, 630, 420);
	puthz(200, 12, "电动车法规测试", 32, 30, MY_GREEN);//边框
	puthz(220, 90, "测试须知", 32, 40, MY_BLACK);
	puthz(30, 170, "测试共十二题，每题仅有一个正确选项，答对八题及以上即", 24, 22, MY_BLACK);
	puthz(30, 210,"通过测试。答题时间共十分钟，中途离场需再次进行测试", 24, 22, MY_BLACK);
	puthz(180, 300, "测试将在", 24, 22, MY_BLACK);
	puthz(350, 300, "秒后开始", 24, 22, MY_BLACK);
}
	
void drawgraph_user_quiz(int *quiz_page,int page_count) {
	char question_serial[8][8];//按页码储存题目序号，最多8页，不想在这malloc
	char quiz_page_string[10];//页码字符串
	char id[8];
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
	puthz(USER_QUIZ_BUTTON3_X1 + 16, USER_QUIZ_BUTTON3_Y1 + 8, "交卷", 24, 35, MY_WHITE);
}



void flushUserQuiz(int* tag,int *box_tag, user_button UserButtons[], question quiz[], char* answer,int quiz_page ,int review_flag) {
	int i = 0;
	int temp = 0;
	int new_tag = ACTIVE_USER_NONE;
	int box_flag;//鼠标是否在选项框位置

	if (review_flag) {
		box_flag = FlushQuiz(quiz, 3, box_tag);
		if (box_flag)
			new_tag = 6;//选项框活跃标签
	}
	

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
		if (new_tag != ACTIVE_USER_NONE && new_tag <= 3 &&!(new_tag == 1 && quiz_page == 1)&&!(new_tag == 2 && quiz_page == QUIZ_PAGE_COUNT)) {//上一页，下一页，交卷按钮
			setcolor(MY_BLACK);
			setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
			rectangle(UserButtons[temp].x1-1, UserButtons[temp].y1-1, UserButtons[temp].x2+1, UserButtons[temp].y2+1);
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
				rectangle(UserButtons[i].x1-1, UserButtons[i].y1-1, UserButtons[i].x2+1, UserButtons[i].y2+1);
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
	correct_rate = 100*(float)correct_num / (page_count * QUESTION_PER_PAGE);
	sprintf(correct_num_string, "%d", correct_num);
	sprintf(correct_rate_string, "%.2f%%", correct_rate);

	//主页面
	setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
	bar(0, 0, 640, 480);
	setfillstyle(1, MY_CREAM);
	bar(10, 50, 630, 470);
	setfillstyle(1, MY_WHITE);
	bar(120, 160, 520, 440);
	puthz(200, 12, "电动车法规测试", 32, 30, MY_WHITE);//边框
	setcolor(MY_GREEN);
	setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
	rectangle(117, 157, 523, 443);

	//显示测试结果
	puthz(210, 90, "恭喜通过！", 48,45, MY_GREEN);
	puthz(180, 190, "您在本次测试中答对", 24, 22, MY_BLACK);
	puthz(422, 190, "题", 24, 22, MY_BLACK);
	puthz(210, 235, "正确率为", 24, 22, MY_BLACK);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
	setcolor(MY_GREEN);
	outtextxy(390, 195, correct_num_string);
	outtextxy(320, 230, correct_rate_string);

	puthz(140, 300, "您可以选择回顾测试中的错题，或", 24, 24, MY_BLACK);
	puthz(150, 340, "前往预约办理校内通行证", 24, 24, MY_BLACK);

	//绘制按钮
	setfillstyle(1, MY_RED);//退出红叉
	setcolor(MY_RED);
	bar(USER_QUIZ_EXIT_X1, USER_QUIZ_EXIT_Y1, USER_QUIZ_EXIT_X2, USER_QUIZ_EXIT_Y2);
	setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
	setcolor(MY_WHITE);
	line(USER_QUIZ_EXIT_X1, USER_QUIZ_EXIT_Y1, USER_QUIZ_EXIT_X2 - 1, USER_QUIZ_EXIT_Y2 - 1);
	line(USER_QUIZ_EXIT_X2 - 1, USER_QUIZ_EXIT_Y1, USER_QUIZ_EXIT_X1, USER_QUIZ_EXIT_Y2 - 1);

	setfillstyle(SOLID_FILL, MY_YELLOW);//离开
	bar(USER_QUIZ_BACK_X1, USER_QUIZ_BACK_Y1, USER_QUIZ_BACK_X2, USER_QUIZ_BACK_Y2);
	puthz(USER_QUIZ_BACK_X1 + 7, USER_QUIZ_BACK_Y1 + 5, "离开", 24, 25, MY_WHITE);

	setfillstyle(SOLID_FILL, MY_RED);
	bar(USER_QUIZ_RESULT_BUTTON1_X1, USER_QUIZ_RESULT_BUTTON1_Y1, USER_QUIZ_RESULT_BUTTON1_X2, USER_QUIZ_RESULT_BUTTON1_Y2);
	puthz(USER_QUIZ_RESULT_BUTTON1_X1 + 5, USER_QUIZ_RESULT_BUTTON1_Y1 + 5, "回顾", 24, 20, MY_WHITE);
	bar(USER_QUIZ_RESULT_BUTTON2_X1, USER_QUIZ_RESULT_BUTTON2_Y1, USER_QUIZ_RESULT_BUTTON2_X2, USER_QUIZ_RESULT_BUTTON2_Y2);
	puthz(USER_QUIZ_RESULT_BUTTON2_X1 + 5, USER_QUIZ_RESULT_BUTTON2_Y1 + 5, "继续", 24, 20, MY_WHITE);
		
}

void drawgraph_user_quiz_fail(int result[][QUESTION_PER_PAGE], int page_count) {
	int i, j;
	int correct_num = 0;
	float correct_rate;
	char correct_num_string[16];
	char correct_rate_string[16];

	for (i = 0; i < page_count; i++) {
		for (j = 0; j < QUESTION_PER_PAGE; j++) {
			if (result[i][j] == 1)
				correct_num++;
		}
	}
	correct_rate = 100 * (float)correct_num / (page_count * QUESTION_PER_PAGE);
	sprintf(correct_num_string, "%d", correct_num);
	sprintf(correct_rate_string, "%.2f%%", correct_rate);

	//主页面
	setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
	bar(0, 0, 640, 480);
	setfillstyle(1, MY_CREAM);
	bar(10, 50, 630, 470);
	setfillstyle(1, MY_WHITE);
	bar(120, 160, 520, 440);
	puthz(200, 12, "电动车法规测试", 32, 30, MY_WHITE);//边框
	setcolor(MY_GREEN);
	setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
	rectangle(117, 157, 523, 443);

	//显示测试结果
	puthz(210, 90, "再接再厉", 48, 45, MY_GREEN);
	puthz(180, 190, "您在本次测试中答对", 24, 22, MY_BLACK);
	puthz(415, 190, "题", 24, 22, MY_BLACK);
	puthz(210, 235, "正确率为", 24, 22, MY_BLACK);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
	setcolor(MY_RED);
	outtextxy(390, 195, correct_num_string);
	outtextxy(330, 240, correct_rate_string);

	puthz(140, 300, "您可以选择回顾测试中的错题，或重新", 24, 22, MY_BLACK);
	puthz(140, 340, "进行测试", 24, 22, MY_BLACK);

	//绘制按钮
	setfillstyle(1, MY_RED);//退出红叉
	setcolor(MY_RED);
	bar(USER_QUIZ_EXIT_X1, USER_QUIZ_EXIT_Y1, USER_QUIZ_EXIT_X2, USER_QUIZ_EXIT_Y2);
	setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
	setcolor(MY_WHITE);
	line(USER_QUIZ_EXIT_X1, USER_QUIZ_EXIT_Y1, USER_QUIZ_EXIT_X2 - 1, USER_QUIZ_EXIT_Y2 - 1);
	line(USER_QUIZ_EXIT_X2 - 1, USER_QUIZ_EXIT_Y1, USER_QUIZ_EXIT_X1, USER_QUIZ_EXIT_Y2 - 1);

	setfillstyle(SOLID_FILL, MY_YELLOW);//离开
	bar(USER_QUIZ_BACK_X1, USER_QUIZ_BACK_Y1, USER_QUIZ_BACK_X2, USER_QUIZ_BACK_Y2);
	puthz(USER_QUIZ_BACK_X1 + 7, USER_QUIZ_BACK_Y1 + 5, "离开", 24, 25, MY_WHITE);

	setfillstyle(SOLID_FILL, MY_RED);
	bar(USER_QUIZ_RESULT_BUTTON1_X1, USER_QUIZ_RESULT_BUTTON1_Y1, USER_QUIZ_RESULT_BUTTON1_X2, USER_QUIZ_RESULT_BUTTON1_Y2);
	puthz(USER_QUIZ_RESULT_BUTTON1_X1 + 7, USER_QUIZ_RESULT_BUTTON1_Y1 + 9, "回顾", 24, 20, MY_WHITE);
	bar(USER_QUIZ_RESULT_BUTTON2_X1, USER_QUIZ_RESULT_BUTTON2_Y1, USER_QUIZ_RESULT_BUTTON2_X2, USER_QUIZ_RESULT_BUTTON2_Y2);
	puthz(USER_QUIZ_RESULT_BUTTON2_X1 + 7, USER_QUIZ_RESULT_BUTTON2_Y1 + 9, "重试", 24, 20, MY_WHITE);
}


void drawgraph_quiz_review(int* quiz_page, int page_count,int pass_flag) {
	char question_serial[8][8];//按页码储存题目序号，最多8页，不想在这malloc
	char quiz_page_string[10];//页码字符串
	char id[8];
	int i;

	setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
	bar(0, 0, 640, 480);
	setcolor(MY_WHITE);
	setfillstyle(1, MY_WHITE);
	bar(10, 50, 630, 420);
	puthz(200, 12, "电动车法规测试", 32, 30, MY_WHITE);//边框

	for (i = 0; i < 3; i++) {                 //为题目序号赋值
		sprintf(question_serial[i], "%d", i + 1 + 3 * (*quiz_page - 1));
	}
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2); //输出题目序号
	setcolor(MY_BLACK);
	outtextxy(20, 70, question_serial[0]);
	outtextxy(20, 190, question_serial[1]);
	outtextxy(20, 310, question_serial[2]);

	setfillstyle(1, MY_RED);//退出红叉
	setcolor(MY_RED);
	bar(USER_QUIZ_EXIT_X1, USER_QUIZ_EXIT_Y1, USER_QUIZ_EXIT_X2, USER_QUIZ_EXIT_Y2);
	setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
	setcolor(MY_WHITE);
	line(USER_QUIZ_EXIT_X1, USER_QUIZ_EXIT_Y1, USER_QUIZ_EXIT_X2 - 1, USER_QUIZ_EXIT_Y2 - 1);
	line(USER_QUIZ_EXIT_X2 - 1, USER_QUIZ_EXIT_Y1, USER_QUIZ_EXIT_X1, USER_QUIZ_EXIT_Y2 - 1);

	setfillstyle(SOLID_FILL, MY_YELLOW);//离开
	bar(USER_QUIZ_BACK_X1, USER_QUIZ_BACK_Y1, USER_QUIZ_BACK_X2, USER_QUIZ_BACK_Y2);
	puthz(USER_QUIZ_BACK_X1 + 7, USER_QUIZ_BACK_Y1 + 5, "离开", 24, 25, MY_WHITE);

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

	if (pass_flag == 0) {
		setfillstyle(SOLID_FILL, MY_RED);//交卷
		bar(USER_QUIZ_BUTTON3_X1, USER_QUIZ_BUTTON3_Y1, USER_QUIZ_BUTTON3_X2, USER_QUIZ_BUTTON3_Y2);
		puthz(USER_QUIZ_BUTTON3_X1 + 3, USER_QUIZ_BUTTON3_Y1 + 8, "重新测试", 24, 20, MY_WHITE);
	}
	else {
		setfillstyle(SOLID_FILL, MY_RED);//交卷
		bar(USER_QUIZ_BUTTON3_X1, USER_QUIZ_BUTTON3_Y1, USER_QUIZ_BUTTON3_X2, USER_QUIZ_BUTTON3_Y2);
		puthz(USER_QUIZ_BUTTON3_X1 + 3, USER_QUIZ_BUTTON3_Y1 + 8, "前往预约", 24, 20, MY_WHITE);
	}
}

void FlushQuizResult(int* tag, user_button UserButtons[]) {
	int i = 0;
	int temp = 0;
	int new_tag = ACTIVE_USER_NONE;
	
	for (i = 0; i < 4; i++) {
		if (MouseX >= UserButtons[i].x1 && MouseX <= UserButtons[i].x2 &&
			MouseY >= UserButtons[i].y1 && MouseY <= UserButtons[i].y2) {
			new_tag = UserButtons[i].active_tag;
			temp = i;
			break;
		}
	}

	if (*tag != new_tag) {
		*tag = new_tag;
		if (new_tag != ACTIVE_USER_NONE && new_tag <= 2) {
			setcolor(MY_BLACK);
			setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
			rectangle(UserButtons[temp].x1 - 1, UserButtons[temp].y1 - 1, UserButtons[temp].x2 + 1, UserButtons[temp].y2 + 1);
			MouseS = 1;
		}
		else if (new_tag == 3) {//退出程序
			setfillstyle(1, MY_WHITE);
			setcolor(MY_WHITE);
			setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
			rectangle(UserButtons[temp].x1, UserButtons[temp].y1, UserButtons[temp].x2, UserButtons[temp].y2);
			MouseS = 1;
		}
		else if (new_tag == 4) {//返回主界面（离开）
			setcolor(MY_RED);
			setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
			setfillstyle(1, MY_RED);
			bar(USER_QUIZ_BACK_X1, USER_QUIZ_BACK_Y1, USER_QUIZ_BACK_X2, USER_QUIZ_BACK_Y2);
			puthz(USER_QUIZ_BACK_X1 + 7, USER_QUIZ_BACK_Y1 + 6, "离开", 24, 25, MY_WHITE);
			MouseS = 1;
		}
		else {
			// 清除提示
			setcolor(MY_WHITE);
			setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
			for (i = 0; i < 2; i++) {
				rectangle(UserButtons[i].x1 - 1, UserButtons[i].y1 - 1, UserButtons[i].x2 + 1, UserButtons[i].y2 + 1);
			}

			setfillstyle(1, MY_YELLOW);//恢复“离开”
			setcolor(MY_YELLOW);
			bar(USER_QUIZ_BACK_X1, USER_QUIZ_BACK_Y1, USER_QUIZ_BACK_X2, USER_QUIZ_BACK_Y2);
			puthz(USER_QUIZ_BACK_X1 + 7, USER_QUIZ_BACK_Y1 + 6, "离开", 24, 25, MY_WHITE);

			setcolor(MY_RED);
			setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
			rectangle(USER_QUIZ_EXIT_X1, USER_QUIZ_EXIT_Y1, USER_QUIZ_EXIT_X2, USER_QUIZ_EXIT_Y2);
			MouseS = 0;
		}
			
	}

}

void write_quiz_result_to_file(unsigned long* id) {
	int i = 0;
	int account_counts;
	int position;
	EBIKE_MOREINFO TEMP,moreinfo;
	FILE* fp_EBIKE_MOREINFO_isquiz_readndwrite = fopen("DATA\\MOREINFO.DAT", "rb+");
	if (fp_EBIKE_MOREINFO_isquiz_readndwrite == NULL) {
		fclose(fp_EBIKE_MOREINFO_isquiz_readndwrite);
		exit(0);
	}

	memset(&TEMP, 0, sizeof(TEMP));
	fseek(fp_EBIKE_MOREINFO_isquiz_readndwrite, 0, SEEK_END);
	account_counts = ftell(fp_EBIKE_MOREINFO_isquiz_readndwrite) / sizeof(EBIKE_MOREINFO);//初始操作完成，接下来开始遍历数据

	for (i = 0; i < account_counts; i++) {
		fseek(fp_EBIKE_MOREINFO_isquiz_readndwrite, i * sizeof(EBIKE_MOREINFO), SEEK_SET);
		fread(&TEMP, sizeof(EBIKE_MOREINFO), 1, fp_EBIKE_MOREINFO_isquiz_readndwrite); //逐个读取，每个用户信息

		if (TEMP.id == *id) {
			strcpy(moreinfo.color, TEMP.color);
			strcpy(moreinfo.battery, TEMP.battery);
			strcpy(moreinfo.length, TEMP.length);
			strcpy(moreinfo.weight, TEMP.weight);
			moreinfo.id = *id;
			moreinfo.is_quiz = 1;
			position = i;
		}
	}
	fseek(fp_EBIKE_MOREINFO_isquiz_readndwrite, position* sizeof(EBIKE_MOREINFO), SEEK_SET);
	fwrite(&moreinfo, sizeof(EBIKE_MOREINFO), 1, fp_EBIKE_MOREINFO_isquiz_readndwrite);
	if (fclose(fp_EBIKE_MOREINFO_isquiz_readndwrite) != 0) getch(), exit(1);
	return ;
}
int quiz_judge(unsigned long* id) {
	int i = 0;
	int account_counts;
	EBIKE_MOREINFO TEMP;
	FILE* fp_EBIKE_MOREINFO_read = fopen("DATA\\MOREINFO.DAT", "rb");
	if (fp_EBIKE_MOREINFO_read == NULL) {
		fclose(fp_EBIKE_MOREINFO_read);
		exit(0);
	}

	memset(&TEMP, 0, sizeof(TEMP));
	fseek(fp_EBIKE_MOREINFO_read, 0, SEEK_END);
	account_counts = ftell(fp_EBIKE_MOREINFO_read) / sizeof(EBIKE_MOREINFO);//初始操作完成，接下来开始遍历数据

	for (i = 0; i < account_counts; i++) {
		fseek(fp_EBIKE_MOREINFO_read, i * sizeof(EBIKE_MOREINFO), SEEK_SET);
		fread(&TEMP, sizeof(EBIKE_MOREINFO), 1, fp_EBIKE_MOREINFO_read); //逐个读取，每个用户信息

		if (TEMP.id == *id) {
			if (TEMP.is_quiz == 1) {
				if (fclose(fp_EBIKE_MOREINFO_read) != 0) getch(), exit(1);
				return 1;
			}
			else {
				if (fclose(fp_EBIKE_MOREINFO_read) != 0) getch(), exit(1); 
				return 0;
			}
				
		}
	}

	if (fclose(fp_EBIKE_MOREINFO_read) != 0) getch(), exit(1);
	return -1;
}















void user_info(int* page, unsigned long* id) {
	int tag = 0;
	int click = -99;
	int mouse_flag;

	user_button UserButtons[] = {
{USER_BIKE_REGISTER_X1, USER_BIKE_REGISTER_X2,USER_BIKE_REGISTER_Y1, USER_BIKE_REGISTER_Y2,ACTIVE_USER_BIKE_REGISTER,USER_BIKE_REGISTER},
{USER_BIKE_LICENSE_X1, USER_BIKE_LICENSE_X2,USER_BIKE_LICENSE_Y1, USER_BIKE_LICENSE_Y2,ACTIVE_USER_BIKE_LICENSE,USER_BIKE_LICENSE_NOTICE},
{USER_ANNUAL_X1, USER_ANNUAL_X2,USER_ANNUAL_Y1, USER_ANNUAL_Y2,ACTIVE_USER_ANNUAL,USER_ANNUAL},
{USER_BIKE_WROTEOUT_X1, USER_BIKE_WROTEOUT_X2,USER_BIKE_WROTEOUT_Y1, USER_BIKE_WROTEOUT_Y2,ACTIVE_USER_BIKE_WROTEOUT,USER_BIKE_WROTEOUT},
{USER_INFO_X1, USER_INFO_X2,USER_INFO_Y1, USER_INFO_Y2,ACTIVE_USER_INFO,USER_INFO},
{USER_MESSAGE_X1, USER_MESSAGE_X2,USER_MESSAGE_Y1, USER_MESSAGE_Y2,ACTIVE_USER_MESSAGE,USER_MESSAGE},
{USER_HELP_X1, USER_HELP_X2,USER_HELP_Y1, USER_HELP_Y2,ACTIVE_USER_HELP,USER_HELP},
{USER_BACK_X1,USER_BACK_X2,USER_BACK_Y1,USER_BACK_Y2,ACTIVE_USER_BACK,LOGIN},
{USER_EXIT_X1,USER_EXIT_X2,USER_EXIT_Y1,USER_EXIT_Y2,ACTIVE_USER_EXIT,EXIT},
{USER_INFO_ACCOUNT_X1, USER_INFO_ACCOUNT_X2, USER_INFO_ACCOUNT_Y1, USER_INFO_ACCOUNT_Y2, ACTIVE_USER_INFO_ACCOUNT, USER_MESSAGE},
{USER_INFO_BIKEINFO_X1, USER_INFO_BIKEINFO_X2, USER_INFO_BIKEINFO_Y1, USER_INFO_BIKEINFO_Y2, ACTIVE_USER_INFO_BIKEINFO, USER_INFO_BIKEINFO},
{USER_INFO_BIKEDATA_X1, USER_INFO_BIKEDATA_X2, USER_INFO_BIKEDATA_Y1, USER_INFO_BIKEDATA_Y2, ACTIVE_USER_INFO_BIKEDATA, USER_INFO_BIKEDATA},
{USER_INFO_PASSWORD_X1, USER_INFO_PASSWORD_X2, USER_INFO_PASSWORD_Y1, USER_INFO_PASSWORD_Y2, ACTIVE_USER_INFO_PASSWORD, USER_INFO_PASSWORD},
};


	// 初始化界面
	clrmous(MouseX, MouseY);
	save_bk_mou(MouseX, MouseY);
	drawgraph_user_main(page);
	drawgraph_user_info(); // 绘制背景和静态元素

	while (1) {
		newmouse_data(&MouseX, &MouseY, &press, &mouse_flag);

		flushUserInfo(&tag, STRUCT_LENGTH(UserButtons), UserButtons);

		click = handle_click_info(STRUCT_LENGTH(UserButtons), UserButtons);
		if (click !=USER_INFO && click!=-99) {
			*page = click;
			return;
		}
		newmouse(&MouseX, &MouseY, &press, &mouse_flag);
		delay(25); // 维持刷新率
	}
}

int handle_click_info(int button_num, user_button UserButtons[]) {
	int i = 0;
	for (i = 0; i < button_num; i++) {
		if (mouse_press(UserButtons[i].x1, UserButtons[i].y1, UserButtons[i].x2, UserButtons[i].y2) == 1)
			return UserButtons[i].page;
	}
	return -99;
}

void drawgraph_user_info() {
	puthz(270, 80, "用户信息管理", 32, 40, MY_BLACK);
	setfillstyle(SOLID_FILL, MY_CREAM);
	bar(190, 120, 390, 270);
	bar(190, 290, 390, 440);
	bar(410, 120, 610, 270);
	bar(410, 290, 610, 440);
	puthz(240, 140, "账号消息",24, 22, MY_BLACK);
	puthz(240, 310, "修改密码", 24, 22, MY_BLACK);
	puthz(450, 140, "修改电动车信息", 24, 22, MY_BLACK);
	puthz(450, 310, "查看电动车情况", 24, 22, MY_BLACK);
	setlinestyle(SOLID_LINE, 1, THICK_WIDTH);
	setcolor(MY_LIGHTGRAY);
	rectangle(190, 120, 390, 270);
	rectangle(190, 290, 390, 440);
	rectangle(410, 120, 610, 270);
	rectangle(410, 290, 610, 440);

	setfillstyle(SOLID_FILL, MY_GREEN);
	
	bar(USER_INFO_ACCOUNT_X1, USER_INFO_ACCOUNT_Y1, USER_INFO_ACCOUNT_X2, USER_INFO_ACCOUNT_Y2);
	bar(USER_INFO_BIKEINFO_X1, USER_INFO_BIKEINFO_Y1, USER_INFO_BIKEINFO_X2, USER_INFO_BIKEINFO_Y2);
	bar(USER_INFO_BIKEDATA_X1, USER_INFO_BIKEDATA_Y1, USER_INFO_BIKEDATA_X2, USER_INFO_BIKEDATA_Y2);
	bar(USER_INFO_PASSWORD_X1, USER_INFO_PASSWORD_Y1, USER_INFO_PASSWORD_X2, USER_INFO_PASSWORD_Y2);
	//按钮的文字
	puthz(USER_INFO_ACCOUNT_X1 + 7, USER_INFO_ACCOUNT_Y1 + 6, "前往", 24, 22, MY_WHITE);
	puthz(USER_INFO_BIKEINFO_X1 + 7, USER_INFO_BIKEINFO_Y1 + 6, "前往", 24, 22, MY_WHITE);
	puthz(USER_INFO_BIKEDATA_X1 + 7, USER_INFO_BIKEDATA_Y1 + 6, "前往", 24, 22, MY_WHITE);
	puthz(USER_INFO_PASSWORD_X1 + 7, USER_INFO_PASSWORD_Y1 + 6, "前往", 24, 22, MY_WHITE);

}

// 专用交互逻辑实现
void flushUserInfo(int* tag, int button_count, user_button UserButtons[]) {
	int i = 0;
	int temp = 0;
	int new_tag = ACTIVE_USER_NONE;


	for (i = 0; i < button_count; i++) {
		if (MouseX >= UserButtons[i].x1 && MouseX <= UserButtons[i].x2 &&
			MouseY >= UserButtons[i].y1 && MouseY <= UserButtons[i].y2) {
			new_tag = UserButtons[i].active_tag;
			MouseS = 1;
			temp = i;
			break;
		}
	}

	if (*tag != new_tag) {
		if (*tag != ACTIVE_USER_NONE) {
			if (*tag <= ACTIVE_USER_HELP) {
				setcolor(MY_LIGHTGRAY);
				setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
				rectangle(UserButtons[*tag - 1].x1, UserButtons[*tag - 1].y1, UserButtons[*tag - 1].x2, UserButtons[*tag - 1].y2);

			}
			else if (*tag == ACTIVE_USER_EXIT) {
				setcolor(MY_RED);
				setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
				rectangle(USER_EXIT_X1, USER_EXIT_Y1, USER_EXIT_X2, USER_EXIT_Y2);

			}
			else if (*tag == ACTIVE_USER_BACK) {
				setfillstyle(1, MY_YELLOW);//恢复“返回登录”
				setcolor(MY_YELLOW);
				bar(USER_BACK_X1, USER_BACK_Y1, USER_BACK_X2, USER_BACK_Y2);
				puthz(USER_BACK_X1 + 5, (USER_BACK_Y1 + USER_BACK_Y2) / 2 - 10, "返回", 24, 25, MY_WHITE);

			}
			else {
				setcolor(MY_WHITE);
				setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
				rectangle(UserButtons[*tag - 42].x1-1, UserButtons[*tag - 42].y1-1, UserButtons[*tag - 42].x2+1, UserButtons[*tag - 42].y2+1);//处理专属USER_INFO的四个按钮，tag为51，52，53，54在数组[9][10][11][12]位
			}
		}
		*tag = new_tag;
		if (new_tag != ACTIVE_USER_NONE && new_tag <= ACTIVE_USER_HELP) {
			setfillstyle(1, MY_WHITE);
			setcolor(MY_WHITE);
			setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
			rectangle(UserButtons[temp].x1, UserButtons[temp].y1, UserButtons[temp].x2, UserButtons[temp].y2);

		}
		else if (new_tag == ACTIVE_USER_EXIT) {
			setfillstyle(1, MY_WHITE);
			setcolor(MY_WHITE);
			setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
			rectangle(UserButtons[temp].x1, UserButtons[temp].y1, UserButtons[temp].x2, UserButtons[temp].y2);

		}
		else if (new_tag == ACTIVE_USER_BACK) {
			setcolor(MY_RED);
			setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
			setfillstyle(1, MY_RED);
			bar(USER_BACK_X1, USER_BACK_Y1, USER_BACK_X2, USER_BACK_Y2);
			puthz(USER_BACK_X1 + 5, (USER_BACK_Y1 + USER_BACK_Y2) / 2 - 10, "返回", 24, 25, MY_WHITE);

		}
		else if (new_tag == ACTIVE_USER_INFO_ACCOUNT || new_tag == ACTIVE_USER_INFO_BIKEINFO || new_tag == ACTIVE_USER_INFO_BIKEDATA||new_tag==ACTIVE_USER_INFO_PASSWORD) {
			setcolor(MY_BLACK);
			setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
			rectangle(UserButtons[*tag - 42].x1 - 1, UserButtons[*tag - 42].y1 - 1, UserButtons[*tag - 42].x2 + 1, UserButtons[*tag - 42].y2 + 1);
		}
		else {
			MouseS = 0;
		}
	}
}

void user_bikeinfo(LINKLIST *LIST,int* page, unsigned long* id) {
	char new_text[4][10] = { 0 }; // 存储输入的新内容
	int button_state[4] = {0,0,0,0}; // 是否正在编辑
	int tick[4] = { 0,0,0,0 };
	int hz_input_len = 0;
	int tag = -99;
	int change_tag;
	int register_flag;
	int click = -99;
	int mouse_flag;
	int pos_xy[4][2] = { {340,210},{340,270},{340,330},{340,390} };
	int len;
	int active_button;
	char second[][2] = { "5","4","3","2","1","0" };
	int tick_sec=0;

	EBIKE_MOREINFO ebike_moreinfo;
	
	user_button UserButtons[] = {
{USER_BIKE_REGISTER_X1, USER_BIKE_REGISTER_X2,USER_BIKE_REGISTER_Y1, USER_BIKE_REGISTER_Y2,ACTIVE_USER_BIKE_REGISTER,USER_BIKE_REGISTER},
{USER_BIKE_LICENSE_X1, USER_BIKE_LICENSE_X2,USER_BIKE_LICENSE_Y1, USER_BIKE_LICENSE_Y2,ACTIVE_USER_BIKE_LICENSE,USER_BIKE_LICENSE_NOTICE},
{USER_ANNUAL_X1, USER_ANNUAL_X2,USER_ANNUAL_Y1, USER_ANNUAL_Y2,ACTIVE_USER_ANNUAL,USER_ANNUAL},
{USER_BIKE_WROTEOUT_X1, USER_BIKE_WROTEOUT_X2,USER_BIKE_WROTEOUT_Y1, USER_BIKE_WROTEOUT_Y2,ACTIVE_USER_BIKE_WROTEOUT,USER_BIKE_WROTEOUT},
{USER_INFO_X1, USER_INFO_X2,USER_INFO_Y1, USER_INFO_Y2,ACTIVE_USER_INFO,USER_INFO},
{USER_MESSAGE_X1, USER_MESSAGE_X2,USER_MESSAGE_Y1, USER_MESSAGE_Y2,ACTIVE_USER_MESSAGE,USER_MESSAGE},
{USER_HELP_X1, USER_HELP_X2,USER_HELP_Y1, USER_HELP_Y2,ACTIVE_USER_HELP,USER_HELP},
{USER_BACK_X1,USER_BACK_X2,USER_BACK_Y1,USER_BACK_Y2,ACTIVE_USER_BACK,LOGIN},
{USER_EXIT_X1,USER_EXIT_X2,USER_EXIT_Y1,USER_EXIT_Y2,ACTIVE_USER_EXIT,EXIT},
};
	register_flag = user_ebike_register_judge(LIST, id);
	if (register_flag == 1) {
		puthz(180, 200, "您未注册电动车，请前往注册！", 32, 32, MY_BLACK);
		puthz(280, 300, "秒后转到电动车注册界面", 24, 22, MY_BLACK);
		while (tick_sec <= 202) {
			newmouse_data(&MouseX, &MouseY, &press, &mouse_flag);
			flushUserMain(&tag, STRUCT_LENGTH(UserButtons), UserButtons);
			click = handle_click_main(STRUCT_LENGTH(UserButtons), UserButtons);
			if (click == LOGIN || click == EXIT || click == USER_BIKE_REGISTER || click == USER_BIKE_LICENSE_NOTICE || click == USER_BIKE_WROTEOUT || click == USER_INFO || click == USER_HELP) {          //其它页面做完后此处会改成click!=-1&&click!=USER_BIKE_LICENSE_NOTICE
				*page = click;
				return;
			}
			if (tick_sec % 40 == 0) {
				setfillstyle(SOLID_FILL, MY_WHITE);
				bar(245, 280, 275, 330);
				settextstyle(DEFAULT_FONT, HORIZ_DIR, 2); // 默认字体，水平方向，大小2
				setcolor(MY_BLACK);
				outtextxy(250, 305, second[tick_sec / 40]);
			}
			newmouse(&MouseX, &MouseY, &press, &mouse_flag);
			delay(25);
			tick_sec++;
		}
		*page = USER_BIKE_REGISTER;
		return;
	}
	user_get_ebike_moreinfo(&ebike_moreinfo,id);


	
	clrmous(MouseX, MouseY);
	save_bk_mou(MouseX, MouseY);
	drawgraph_user_main(page);
	setfillstyle(SOLID_FILL, MY_RED);
	drawgraph_user_bike_moreinfo(LIST,id,pos_xy,4,200);

	while (1) {
		newmouse_data(&MouseX, &MouseY, &press, &mouse_flag);
		flushUserMain(&tag, STRUCT_LENGTH(UserButtons), UserButtons); // 刷新界面
		flushChangeButton(&tag,&change_tag, pos_xy, 200, 4,button_state);
		click = handle_click_main(STRUCT_LENGTH(UserButtons), UserButtons);
		if (click == LOGIN || click == EXIT || click == USER_BIKE_REGISTER || click == USER_BIKE_LICENSE_NOTICE || click == USER_BIKE_WROTEOUT || click == USER_INFO || click == USER_HELP) {          //其它页面做完后此处会改成click!=-1&&click!=USER_BIKE_REGISTER
			*page = click;
			return;
		}
		if (mouse_press(BIKEINFO_BUTTON1_X1, BIKEINFO_BUTTON1_Y1, BIKEINFO_BUTTON1_X2, BIKEINFO_BUTTON1_Y2) == 1) {
			change_user_info_moreinfo(new_text, button_state, *id);
			setfillstyle(SOLID_FILL, MY_WHITE);
			bar(150, 60, 640, 480);
			puthz(280, 200, "您已修改成功", 32, 40, MY_BLACK);
			puthz(325, 260, "即将返回", 32, 40, MY_BLACK);
			delay(3000);
			*page = USER_INFO;
			return;
		}
		if (MouseX >= BIKEINFO_BUTTON1_X1 && MouseX <= BIKEINFO_BUTTON1_X2 && MouseY >= BIKEINFO_BUTTON1_Y1 && MouseY <= BIKEINFO_BUTTON1_Y2) {
			MouseS = 1;
			if (active_button != 1) {
				setcolor(MY_BLACK);
				rectangle(BIKEINFO_BUTTON1_X1 - 1, BIKEINFO_BUTTON1_Y1 - 1, BIKEINFO_BUTTON1_X2 + 1, BIKEINFO_BUTTON1_Y2 + 1);
			}
			active_button = 1;
		}
		else if (active_button == 1) {
			setcolor(MY_WHITE);
			rectangle(BIKEINFO_BUTTON1_X1 - 1, BIKEINFO_BUTTON1_Y1 - 1, BIKEINFO_BUTTON1_X2 + 1, BIKEINFO_BUTTON1_Y2 + 1);
			active_button = 0;
		}

		handle_button_and_hzinput(new_text[0], ebike_moreinfo.color, &button_state[0], &hz_input_len, 340, 210, 200,&tick[0]);
		handle_button_and_chinput(new_text[1], ebike_moreinfo.length, &button_state[1], 4, 340, 270, 200,&tick[1]);
		handle_button_and_chinput(new_text[2], ebike_moreinfo.weight, &button_state[2], 4, 340, 330, 200, &tick[2]);
		handle_button_and_chinput(new_text[3], ebike_moreinfo.battery, &button_state[3], 4, 340,390, 200,&tick[3]);

		newmouse(&MouseX, &MouseY, &press, &mouse_flag);

		delay(25);
	}
}

void drawgraph_user_bike_moreinfo(LINKLIST *LIST,unsigned long* id,int pos_xy[][2],int count,int len) {
	EBIKE_INFO user_info;
	EBIKE_MOREINFO moreinfo;
	char id_string[20];
	char apply_time_string[20];//一定要给sprintf留出足够缓冲区
	char conduct_time_string[20];
	int button_x1, button_x2, button_y1, button_y2;
	int bar_x1, bar_x2, bar_y1, bar_y2;
	int i;

	user_bike_register_getinfo(LIST,&user_info, id);
	user_get_ebike_moreinfo(&moreinfo, id);
	sprintf(id_string, "%lu", *id);
	sprintf(apply_time_string, "%lu", user_info.apply_time);
	sprintf(conduct_time_string, "%lu", user_info.conduct_time);

	puthz(260, 80, "电动车信息修改", 32, 40, MY_BLACK);
	setcolor(MY_BLACK);
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	setfillstyle(SOLID_FILL, MY_BLACK);
	bar(151, 120, 640, 123);

	puthz(170, 150, "姓名", 24, 20, MY_BLACK);
	puthz(230, 150, user_info.rln, 24, 20, MY_BLACK);
	puthz(360, 150, "车牌号", 24, 20, MY_BLACK);
	setcolor(MY_BLACK);
	outtextxy(480, 155, user_info.ebike_ID);

	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2); // 默认字体，水平方向，大小2
	setcolor(MY_BLACK);

	puthz(170, 210, "电动车颜色", 24, 20, MY_BLACK);
	puthz(340, 210, moreinfo.color, 24, 20, MY_BLACK);
	puthz(170, 270, "车重（千克）", 24, 20, MY_BLACK);
	outtextxy(340, 275, moreinfo.weight);
	puthz(170, 330, "车长（厘米）", 24, 20, MY_BLACK);
	outtextxy(340, 338, moreinfo.length);
	puthz(170, 390, "电池（千瓦时）", 24, 20, MY_BLACK);
	outtextxy(340, 398, moreinfo.battery);

	for (i = 0; i < count; i++) {
		bar_x1 = pos_xy[i][0] - 5;
		bar_y1 = pos_xy[i][1] - 5;
		bar_x2 = pos_xy[i][0] + len + 5;
		bar_y2 = pos_xy[i][1] + 35;
		/* 按钮坐标 */
		button_x1 = pos_xy[i][0] + len + 25;
		button_y1 = pos_xy[i][1] + 2;
		button_x2 = button_x1 + 62;
		button_y2 = pos_xy[i][1] + 32;
		setfillstyle(SOLID_FILL, MY_RED);
		bar(pos_xy[i][0] + len + 20, pos_xy[i][1], pos_xy[i][0] + len + 80, pos_xy[i][1] + 30);
		puthz(pos_xy[i][0] + len + 28, pos_xy[i][1] + 5, "修改", 24, 22, MY_WHITE);
	}

	setfillstyle(SOLID_FILL, MY_YELLOW);
	bar(BIKEINFO_BUTTON1_X1, BIKEINFO_BUTTON1_Y1, BIKEINFO_BUTTON1_X2, BIKEINFO_BUTTON1_Y2);
	puthz(BIKEINFO_BUTTON1_X1 + 8, BIKEINFO_BUTTON1_Y1 + 5, "提交", 24, 22, MY_WHITE);
}

void change_user_info_moreinfo(char input_text[][10], int state[],unsigned long id) {
	int i;
	int account_counts;
	int position;
	EBIKE_MOREINFO TEMP, data_to_write;
	FILE* fp_EBIKE_MOREINFO_readndwrite = fopen("DATA\\MOREINFO.DAT", "rb+");
	if (fp_EBIKE_MOREINFO_readndwrite == NULL) {
		fclose(fp_EBIKE_MOREINFO_readndwrite);
		exit(0);
	}

	memset(&TEMP, 0, sizeof(TEMP));
	fseek(fp_EBIKE_MOREINFO_readndwrite, 0, SEEK_END);
	account_counts = ftell(fp_EBIKE_MOREINFO_readndwrite) / sizeof(EBIKE_MOREINFO);//初始操作完成，接下来开始遍历数据

	for (i = 0; i < account_counts; i++) {
		fseek(fp_EBIKE_MOREINFO_readndwrite, i * sizeof(EBIKE_MOREINFO), SEEK_SET);
		fread(&TEMP, sizeof(EBIKE_MOREINFO), 1, fp_EBIKE_MOREINFO_readndwrite); //逐个读取，每个用户信息
		if (TEMP.id == id) {
			strcpy(data_to_write.color, TEMP.color);
			strcpy(data_to_write.battery, TEMP.battery);
			strcpy(data_to_write.length, TEMP.length);
			strcpy(data_to_write.weight, TEMP.weight);
			position = i;
			break;
		}
	}
	if (state[0] == 1) 
		strcpy(data_to_write.color, input_text[0]);
	if (state[1] == 1)
		strcpy(data_to_write.length, input_text[1]);
	if (state[2] == 1)
		strcpy(data_to_write.weight, input_text[2]);
	if (state[3] == 1)
		strcpy(data_to_write.battery, input_text[3]);
	data_to_write.id = id;

	fseek(fp_EBIKE_MOREINFO_readndwrite, position* sizeof(EBIKE_MOREINFO), SEEK_SET); // 确保写入位置在文件末尾
	fwrite(&data_to_write, sizeof(EBIKE_MOREINFO), 1, fp_EBIKE_MOREINFO_readndwrite);  //将注册信息写入文件
	if (fclose(fp_EBIKE_MOREINFO_readndwrite) != 0) getch(), exit(1);
	return 0;

}


// 处理按钮和输入框逻辑的函数
void handle_button_and_hzinput(char *new_text,char* old_text,int* button_state, int* hz_input_len,int x,int y,int len,int* tick) {
	
	// 判断鼠标点击
	if (*tick == 0) {
		if ((*button_state == 0) && mouse_press(x + len + 20, y, x + len + 80, y + 30) == 1) {
			// 进入编辑模式
			setcolor(MY_LIGHTGRAY);
			setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
			rectangle(x - 3, y -3, x + len + 3, y + 33);
			*hz_input_len = hz_input(x, y, x + len, y + 30, new_text, *hz_input_len, MY_WHITE, MY_BLACK, 24);
			setfillstyle(SOLID_FILL, MY_RED);
			bar(x + len + 20, y, x + len + 80, y + 30);
			puthz(x + len + 28, y + 5, "取消", 24, 22, MY_WHITE);
			*button_state = 1;
			*tick += 5;
			return;
		}
		if (mouse_press(x, y, x + len, y + 35) == 1 && (*button_state == 1)) {
			//继续编辑
			*hz_input_len = hz_input(x, y, x + len, y + 30, new_text, *hz_input_len, MY_WHITE, MY_BLACK, 24);
			return;
		}
		if (mouse_press(x + len + 20, y, x + len + 80, y + 30) == 1 && (*button_state == 1)) {
			// 退出编辑模式
			*button_state = 0;
			// 显示旧内容
			setfillstyle(SOLID_FILL, MY_WHITE);
			bar(x - 5, y - 5, x + len + 10, y + 40);
			puthz(x , y, old_text, 24, 22, MY_BLACK);
			setfillstyle(SOLID_FILL, MY_RED);
			bar(x + len + 20, y, x + len + 80, y + 30);
			puthz(x + len + 28, y + 5, "修改", 24, 22, MY_WHITE);
			*tick += 5;

			return;
		}
	}
	else
		*tick -= 1;//防止鼠标短时间内连续点击
	
}

void handle_button_and_chinput(char* new_text, char* old_text, int* button_state, int max_input, int x, int y, int len, int* tick){
	// 判断鼠标点击
	if (*tick == 0) {
		if ((*button_state == 0) && mouse_press(x + len + 20, y, x + len + 80, y + 30) == 1) {
			// 进入编辑模式
			setfillstyle(SOLID_FILL, MY_WHITE);
			bar(x - 5, y - 5, x + len + 10, y + 40);
			setcolor(MY_LIGHTGRAY);
			setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
			rectangle(x - 3, y - 3, x + len + 3, y + 33);
			ch_input(new_text,x, y+3, max_input, MY_WHITE,0,1);
			setfillstyle(SOLID_FILL, MY_RED);
			bar(x + len + 20, y, x + len + 80, y + 30);
			puthz(x + len + 28, y + 5, "取消", 24, 22, MY_WHITE);
			*button_state = 1;
			*tick += 5;
			return;
		}
		if (mouse_press(x, y, x + len, y + 35) == 1 && (*button_state == 1)) {
			//继续编辑
			ch_input(new_text, x, y+3, max_input, MY_WHITE, 0, 1);
			return;
		}
		if (mouse_press(x + len + 20, y, x + len + 80, y + 30) == 1 && (*button_state == 1)) {
			// 退出编辑模式
			*button_state = 0;
			// 显示旧内容
			setfillstyle(SOLID_FILL, MY_WHITE);
			bar(x - 5, y - 5, x + len + 10, y + 40);

			settextstyle(DEFAULT_FONT, HORIZ_DIR, 2); // 默认字体，水平方向，大小2
			setcolor(MY_BLACK);
			outtextxy(x + 8, y+5, old_text);//恢复旧内容

			setfillstyle(SOLID_FILL, MY_RED);
			bar(x + len + 20, y, x + len + 80, y + 30);
			puthz(x + len + 28, y + 5, "修改", 24, 22, MY_WHITE);
			*tick += 5;
			ch_input(NULL, NULL, NULL, NULL, NULL, INPUTBAR_CLEAR, NULL);
			return;
		}
	}
	else
		*tick -= 1;//防止鼠标短时间内连续点击

}

void flushChangeButton(int *tag_main,int* tag, int pos_xy[][2], int len, int count,int button_state[]) {
	int i;
	int button_x1, button_x2, button_y1, button_y2;
	int bar_x1, bar_x2, bar_y1, bar_y2;
	int new_tag = 0;

	for (i = 0; i < count; i++) {
		bar_x1 = pos_xy[i][0] - 5;
		bar_y1 = pos_xy[i][1] - 5;                     
		bar_x2 = pos_xy[i][0] + len + 5;
		bar_y2 = pos_xy[i][1] + 35;
		/* 按钮坐标 */
		button_x1 = pos_xy[i][0] + len + 25;
		button_y1 = pos_xy[i][1]+2;
		button_x2 = button_x1 + 62;         
		button_y2 = pos_xy[i][1] + 32;

		// 先检测输入框区域（bar）
		if (MouseX >= bar_x1 && MouseX <= bar_x2 && MouseY >= bar_y1 && MouseY <= bar_y2 && button_state[i]==1) {
			MouseS = 2;
			new_tag = 10 * (i + 1) + 2;
			break;
		}

		// 再检测按钮区域
		else if (MouseX >= button_x1 && MouseX <= button_x2 && MouseY >= button_y1 && MouseY <= button_y2) {
			MouseS = 1;
			new_tag = 10 * (i + 1) + 1;
			break;
		}
		else if (*tag_main==ACTIVE_USER_NONE)
			MouseS = 0;
	}
	if (new_tag != *tag) {
		if (*tag != 0) {
			bar_x1 = pos_xy[*tag / 10 - 1][0] - 3;
			bar_y1 = pos_xy[*tag / 10 - 1][1] - 3;
			bar_x2 = pos_xy[*tag / 10 - 1][0] + len + 3;
			bar_y2 = pos_xy[*tag / 10 - 1][1] + 33;
			/* 按钮坐标 */
			button_x1 = pos_xy[*tag / 10 - 1][0] + len + 20;
			button_y1 = pos_xy[*tag / 10 - 1][1];
			button_x2 = button_x1 + 60;
			button_y2 = pos_xy[*tag / 10 - 1][1] + 30;
			if (*tag % 10 == 1) {
				setcolor(MY_WHITE);
				setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
				rectangle(button_x1-2, button_y1-2, button_x2+2, button_y2+2);
			}
			else {
				setcolor(MY_WHITE);
				setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
				rectangle(bar_x1-2, bar_y1-2, bar_x2+2, bar_y2+2);
			}
		}
		*tag = new_tag;
		if (new_tag !=0) {
			bar_x1 = pos_xy[new_tag / 10 - 1][0] - 3;
			bar_y1 = pos_xy[new_tag / 10 - 1][1] - 3;
			bar_x2 = pos_xy[new_tag / 10 - 1][0] + len + 3;
			bar_y2 = pos_xy[new_tag / 10 - 1][1] + 33;
			/* 按钮坐标 */
			button_x1 = pos_xy[new_tag / 10 - 1][0] + len + 20;
			button_y1 = pos_xy[new_tag / 10 - 1][1];
			button_x2 = button_x1 + 60;
			button_y2 = button_y1 + 30;
			if (new_tag % 10 == 1) {
				setcolor(MY_BLACK);
				setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
				rectangle(button_x1-2, button_y1-2, button_x2+2, button_y2+2);
			}
			else {
				setcolor(MY_BLACK);
				setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
				rectangle(bar_x1-2, bar_y1-2, bar_x2+2, bar_y2+2);
			}
		}
	}
}




void user_bikedata(LINKLIST *LIST,int* page, unsigned long* id) {
	int tag = 0;
	int click = -99;
	int mouse_flag;
	int active_button;
	int register_flag;
	int tick;
	char second[][2] = { "5","4","3","2","1","0"};

	user_button UserButtons[] = {
{USER_BIKE_REGISTER_X1, USER_BIKE_REGISTER_X2,USER_BIKE_REGISTER_Y1, USER_BIKE_REGISTER_Y2,ACTIVE_USER_BIKE_REGISTER,USER_BIKE_REGISTER},
{USER_BIKE_LICENSE_X1, USER_BIKE_LICENSE_X2,USER_BIKE_LICENSE_Y1, USER_BIKE_LICENSE_Y2,ACTIVE_USER_BIKE_LICENSE,USER_BIKE_LICENSE_NOTICE},
{USER_ANNUAL_X1, USER_ANNUAL_X2,USER_ANNUAL_Y1, USER_ANNUAL_Y2,ACTIVE_USER_ANNUAL,USER_ANNUAL},
{USER_BIKE_WROTEOUT_X1, USER_BIKE_WROTEOUT_X2,USER_BIKE_WROTEOUT_Y1, USER_BIKE_WROTEOUT_Y2,ACTIVE_USER_BIKE_WROTEOUT,USER_BIKE_WROTEOUT},
{USER_INFO_X1, USER_INFO_X2,USER_INFO_Y1, USER_INFO_Y2,ACTIVE_USER_INFO,USER_INFO},
{USER_MESSAGE_X1, USER_MESSAGE_X2,USER_MESSAGE_Y1, USER_MESSAGE_Y2,ACTIVE_USER_MESSAGE,USER_MESSAGE},
{USER_HELP_X1, USER_HELP_X2,USER_HELP_Y1, USER_HELP_Y2,ACTIVE_USER_HELP,USER_HELP},
{USER_BACK_X1,USER_BACK_X2,USER_BACK_Y1,USER_BACK_Y2,ACTIVE_USER_BACK,LOGIN},
{USER_EXIT_X1,USER_EXIT_X2,USER_EXIT_Y1,USER_EXIT_Y2,ACTIVE_USER_EXIT,EXIT}
	};


	// 初始化界面
	clrmous(MouseX, MouseY);
	save_bk_mou(MouseX, MouseY);
	drawgraph_user_main(page);

	register_flag = user_ebike_register_judge(LIST,id);
	if (register_flag) {
		puthz(180, 200, "您未注册电动车，请前往注册！", 32, 32, MY_BLACK);
		puthz(280, 300, "秒后转到电动车注册界面", 24, 22, MY_BLACK);
		while (tick <= 202) {
			newmouse_data(&MouseX, &MouseY, &press, &mouse_flag);
			flushUserMain(&tag, STRUCT_LENGTH(UserButtons), UserButtons);
			click = handle_click_main(STRUCT_LENGTH(UserButtons), UserButtons);
			if (click != -99 && click != USER_BIKE_LICENSE_NOTICE) {          //其它页面做完后此处会改成click!=-1&&click!=USER_BIKE_LICENSE_NOTICE
				*page = click;
				return;
			}
			if (tick % 40 == 0) {
				setfillstyle(SOLID_FILL, MY_WHITE);
				bar(245, 280, 275, 330);
				settextstyle(DEFAULT_FONT, HORIZ_DIR, 2); // 默认字体，水平方向，大小2
				setcolor(MY_BLACK);
				outtextxy(250, 305, second[tick / 40]);
			}
			newmouse(&MouseX, &MouseY, &press, &mouse_flag);
			delay(25);
			tick++;
		}
		*page = USER_BIKE_REGISTER;
		return;
	}

	drawgraph_user_bikedata(LIST,id); 
	while (1) {
		newmouse_data(&MouseX, &MouseY, &press, &mouse_flag);
		flushUserMain(&tag, STRUCT_LENGTH(UserButtons), UserButtons);
		click = handle_click_info(STRUCT_LENGTH(UserButtons), UserButtons);
		if (click != USER_INFO && click != USER_MESSAGE && click != -99) {
			*page = click;
			return;
		}
		if (mouse_press(BIKEDATA_BUTTON1_X1, BIKEDATA_BUTTON1_Y1, BIKEDATA_BUTTON1_X2, BIKEDATA_BUTTON1_Y2) == 1) {
			*page = USER_INFO;
			return;
		}
		if (MouseX >= BIKEDATA_BUTTON1_X1 && MouseX <= BIKEDATA_BUTTON1_X2 && MouseY >= BIKEDATA_BUTTON1_Y1 && MouseY <= BIKEDATA_BUTTON1_Y2) {
			MouseS = 1;
			if (active_button != 1) {
				setcolor(MY_BLACK);
				rectangle(BIKEDATA_BUTTON1_X1 - 1, BIKEDATA_BUTTON1_Y1 - 1, BIKEDATA_BUTTON1_X2 + 1, BIKEDATA_BUTTON1_Y2 + 1);
			}
			active_button = 1;
		}
		else if (active_button == 1) {
			setcolor(MY_WHITE);
			rectangle(BIKEDATA_BUTTON1_X1 - 1, BIKEDATA_BUTTON1_Y1 - 1, BIKEDATA_BUTTON1_X2 + 1, BIKEDATA_BUTTON1_Y2 + 1);
			active_button = 0;
		}
		
		newmouse(&MouseX, &MouseY, &press, &mouse_flag);
		delay(25); // 维持刷新率
	}
}

void drawgraph_user_bikedata(LINKLIST *LIST,unsigned long* id) {
	int anual_flag;
	int license_flag;
	int license_data[3] = { 1,1,1 };
	EBIKE_INFO data;

	user_bike_register_getinfo(LIST,&data, id);
	anual_flag = ebike_annual_judge(LIST,id);
	license_flag = ebike_license_judge(id);

	puthz(260, 80, "电动车状态", 32, 40, MY_BLACK);
	setcolor(MY_BLACK);
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	setfillstyle(SOLID_FILL, MY_BLACK);
	bar(151, 120, 640, 123);

	puthz(170, 170, "姓名", 24, 20, MY_BLACK);
	puthz(380, 170, data.rln, 24, 20, MY_BLACK);
	puthz(170, 220, "车牌号", 24, 20, MY_BLACK);
	outtextxy(380, 225, data.ebike_ID);

	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2); // 默认字体，水平方向，大小2
	puthz(170, 270, "年审情况", 24, 22, MY_BLACK);
	if (anual_flag)
		puthz(380, 270, "已年审", 24, 22, MY_BLACK);
	else
		puthz(380, 270, "未年审", 24, 22, MY_BLACK);

	puthz(170, 320, "通行证", 24, 22, MY_BLACK);
	if (!license_flag)
		puthz(380, 320, "已申请", 24, 22, MY_BLACK);
	else
		puthz(380, 320, "未申请", 24, 22, MY_BLACK);

	puthz(170, 370, "违规情况", 24, 22, MY_BLACK);
	puthz(380, 370, "待做", 24, 22, MY_BLACK);
	
	setfillstyle(SOLID_FILL, MY_RED);
	bar(BIKEDATA_BUTTON1_X1, BIKEDATA_BUTTON1_Y1, BIKEDATA_BUTTON1_X2, BIKEDATA_BUTTON1_Y2);
	puthz(BIKEDATA_BUTTON1_X1 + 10, BIKEDATA_BUTTON1_Y1 + 5, "返回", 24, 22, MY_WHITE);
}



void user_info_password(int* page, int* id) {
	int click = -99;
	int tag_main = 0;
	int tag_wroteout = -1;
	int flush_count = 0;
	int mouse_flag;
	int user_flag;
	int password_change_flag;
	char count[8];
	char usrn[16] = { '\0' };
	char old_password_input[16] = { '\0' };
	char new_password_input[16] = { '\0' };
	int input_len = 0;
	int tick;

	user_button UserButtons[] = {
{USER_BIKE_REGISTER_X1, USER_BIKE_REGISTER_X2,USER_BIKE_REGISTER_Y1, USER_BIKE_REGISTER_Y2,ACTIVE_USER_BIKE_REGISTER,USER_BIKE_REGISTER},
{USER_BIKE_LICENSE_X1, USER_BIKE_LICENSE_X2,USER_BIKE_LICENSE_Y1, USER_BIKE_LICENSE_Y2,ACTIVE_USER_BIKE_LICENSE,USER_BIKE_LICENSE_NOTICE},
{USER_ANNUAL_X1, USER_ANNUAL_X2,USER_ANNUAL_Y1, USER_ANNUAL_Y2,ACTIVE_USER_ANNUAL,USER_ANNUAL},
{USER_BIKE_WROTEOUT_X1, USER_BIKE_WROTEOUT_X2,USER_BIKE_WROTEOUT_Y1, USER_BIKE_WROTEOUT_Y2,ACTIVE_USER_BIKE_WROTEOUT,USER_BIKE_WROTEOUT},
{USER_INFO_X1, USER_INFO_X2,USER_INFO_Y1, USER_INFO_Y2,ACTIVE_USER_INFO,USER_INFO},
{USER_MESSAGE_X1, USER_MESSAGE_X2,USER_MESSAGE_Y1, USER_MESSAGE_Y2,ACTIVE_USER_MESSAGE,USER_MESSAGE},
{USER_HELP_X1, USER_HELP_X2,USER_HELP_Y1, USER_HELP_Y2,ACTIVE_USER_HELP,USER_HELP},
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
	drawgraph_user_password();
	while (1) {
		newmouse_data(&MouseX, &MouseY, &press, &mouse_flag);
		flushUserMain(&tag_main, STRUCT_LENGTH(UserButtons), UserButtons); // 刷新界面
		flushUserWroteout(&tag_wroteout, WroteoutButtons);
		click = handle_click_main(STRUCT_LENGTH(UserButtons), UserButtons);
		if (click != -99 && click != USER_INFO) {          //其它页面做完后此处会改成click!=-1&&click!=USER_BIKE_LICENSE
			*page = click;
			ch_input(NULL, NULL, NULL, NULL, NULL, INPUTBAR_CLEAR, NULL);
			return;
		}
		if (mouse_press(USER_BIKE_WROTEOUT_INPUT1_X1, USER_BIKE_WROTEOUT_INPUT1_Y1, USER_BIKE_WROTEOUT_INPUT1_X2, USER_BIKE_WROTEOUT_INPUT1_Y2) == 1) {
			input_len = hz_input(USER_BIKE_WROTEOUT_INPUT1_X1 + 5, USER_BIKE_WROTEOUT_INPUT1_Y1 + 5, USER_BIKE_WROTEOUT_INPUT1_X2 - 3, USER_BIKE_WROTEOUT_INPUT1_Y2 - 3, usrn, input_len, MY_WHITE, MY_BLACK, 24);
		}
		if (mouse_press(USER_BIKE_WROTEOUT_INPUT2_X1, USER_BIKE_WROTEOUT_INPUT2_Y1, USER_BIKE_WROTEOUT_INPUT2_X2, USER_BIKE_WROTEOUT_INPUT2_Y2) == 1) {
			ch_input(old_password_input, USER_BIKE_WROTEOUT_INPUT2_X1 + 2, USER_BIKE_WROTEOUT_INPUT2_Y1 + 2, 10, MY_WHITE, 0, 0);
		}
		if (mouse_press(USER_BIKE_WROTEOUT_INPUT3_X1, USER_BIKE_WROTEOUT_INPUT3_Y1, USER_BIKE_WROTEOUT_INPUT3_X2, USER_BIKE_WROTEOUT_INPUT3_Y2) == 1) {
			ch_input(new_password_input, USER_BIKE_WROTEOUT_INPUT3_X1 + 2, USER_BIKE_WROTEOUT_INPUT3_Y1 + 2, 14, MY_WHITE, 0, 0);
		}
		if (mouse_press(USER_BIKE_WROTEOUT_BUTTON1_X1, USER_BIKE_WROTEOUT_BUTTON1_Y1, USER_BIKE_WROTEOUT_BUTTON1_X2, USER_BIKE_WROTEOUT_BUTTON1_Y2) == 1) {
			password_change_flag = user_password_change(id, old_password_input, new_password_input);
			if (password_change_flag == 0) {
				anime_login_success_user(USER_BIKE_WROTEOUT_BUTTON1_X1, USER_BIKE_WROTEOUT_BUTTON1_Y1, USER_BIKE_WROTEOUT_BUTTON1_X2, USER_BIKE_WROTEOUT_BUTTON1_Y2);
				setfillstyle(SOLID_FILL, MY_WHITE);
				bar(150, 60, 640, 480);
				puthz(280, 200, "您已修改成功", 32, 40, MY_BLACK);
				puthz(245, 260, "即将返回主界面", 32, 40, MY_BLACK);
				delay(3000);
				*page = MAIN_USER;
				ch_input(NULL, NULL, NULL, NULL, NULL, INPUTBAR_CLEAR, NULL);
				return;
			}
			else if (password_change_flag == 1) {
				puthz(300, 205, "密码错误", 24, 22, MY_RED);
				setfillstyle(SOLID_FILL, MY_WHITE);
				bar(195, 370, 400, 410);
				
			}
			else if (password_change_flag == 2) {
				setfillstyle(SOLID_FILL, MY_WHITE);
				bar(295, 195, 500, 225);
				puthz(200, 385, "找不到对应账号", 24, 22, MY_RED);
			}
		}
		newmouse(&MouseX, &MouseY, &press, &mouse_flag);
		delay(25);
	}
}

void drawgraph_user_password() {
	setcolor(MY_LIGHTGRAY);
	setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
	rectangle(USER_BIKE_WROTEOUT_INPUT1_X1 + 2, USER_BIKE_WROTEOUT_INPUT1_Y1 + 2, USER_BIKE_WROTEOUT_INPUT1_X2 - 2, USER_BIKE_WROTEOUT_INPUT1_Y2 - 2);
	rectangle(USER_BIKE_WROTEOUT_INPUT2_X1 + 2, USER_BIKE_WROTEOUT_INPUT2_Y1 + 2, USER_BIKE_WROTEOUT_INPUT2_X2 - 2, USER_BIKE_WROTEOUT_INPUT2_Y2 - 2);
	rectangle(USER_BIKE_WROTEOUT_INPUT3_X1 + 2, USER_BIKE_WROTEOUT_INPUT3_Y1 + 2, USER_BIKE_WROTEOUT_INPUT3_X2 - 2, USER_BIKE_WROTEOUT_INPUT3_Y2 - 2);
	puthz(220, 85, "请输入姓名，与密码以确认身份", 24, 20, MY_BLACK);
	puthz(170, 155, "姓名", 24, 20, MY_BLACK);
	puthz(170, 230, "旧密码", 24, 20, MY_BLACK);
	puthz(170, 300, "新密码", 24, 20, MY_BLACK);

	setcolor(MY_RED);
	setfillstyle(SOLID_FILL, MY_RED);
	bar(USER_BIKE_WROTEOUT_BUTTON1_X1, USER_BIKE_WROTEOUT_BUTTON1_Y1, USER_BIKE_WROTEOUT_BUTTON1_X2, USER_BIKE_WROTEOUT_BUTTON1_Y2);
	puthz(USER_BIKE_WROTEOUT_BUTTON1_X1 + 15, USER_BIKE_WROTEOUT_BUTTON1_Y1 + 8, "确认", 24, 20, MY_WHITE);

	bar(USER_BIKE_WROTEOUT_BUTTON2_X1, USER_BIKE_WROTEOUT_BUTTON2_Y1, USER_BIKE_WROTEOUT_BUTTON2_X2, USER_BIKE_WROTEOUT_BUTTON2_Y2);
	puthz(USER_BIKE_WROTEOUT_BUTTON2_X1 + 15, USER_BIKE_WROTEOUT_BUTTON2_Y1 + 8, "返回", 24, 20, MY_WHITE);
}

int user_password_change(unsigned long* id, char* old_password,char* new_password) {
	int i;
	int account_counts;
	int position=-1;

	USER_LOGIN_DATA TEMP, data_to_write;
	FILE* fp_USER_PASSWORD_CHANGE_readndwrite = fopen("DATA\\USER.DAT", "rb+");
	if (fp_USER_PASSWORD_CHANGE_readndwrite == NULL) {
		fclose(fp_USER_PASSWORD_CHANGE_readndwrite);
		exit(0);
	}

	memset(&TEMP, 0, sizeof(TEMP));
	fseek(fp_USER_PASSWORD_CHANGE_readndwrite, 0, SEEK_END);
	account_counts = ftell(fp_USER_PASSWORD_CHANGE_readndwrite) / sizeof(USER_LOGIN_DATA);//初始操作完成，接下来开始遍历数据
	rewind(fp_USER_PASSWORD_CHANGE_readndwrite);
	for (i = 0; i < account_counts; i++) {
		fseek(fp_USER_PASSWORD_CHANGE_readndwrite, i * sizeof(USER_LOGIN_DATA), SEEK_SET);
		fread(&TEMP, sizeof(USER_LOGIN_DATA), 1, fp_USER_PASSWORD_CHANGE_readndwrite); //逐个读取，每个用户信息
		if (TEMP.ID == *id) {
			if (strcmp(TEMP.psw, old_password) == 0) {
				data_to_write.ID = *id;
				strcpy(data_to_write.usrn, TEMP.usrn);
				data_to_write.state=TEMP.state;
				data_to_write.register_time=TEMP.register_time;
				strcpy(data_to_write.psw, new_password);
				position = i;
				break;
			}
			else {
				if (fclose(fp_USER_PASSWORD_CHANGE_readndwrite) != 0) getch(), exit(1);
				return 1;//密码错误
			}	
		}
	}
	if (position == -1) {
		if (fclose(fp_USER_PASSWORD_CHANGE_readndwrite) != 0) getch(), exit(1);
		return 2; //找不到ID对应的账号
	}
		
	fseek(fp_USER_PASSWORD_CHANGE_readndwrite, position * sizeof(USER_LOGIN_DATA), SEEK_SET); // 确保写入位置为之前的数据所在位置
	fwrite(&data_to_write, sizeof(USER_LOGIN_DATA), 1, fp_USER_PASSWORD_CHANGE_readndwrite);  //将信息写入文件
	if (fclose(fp_USER_PASSWORD_CHANGE_readndwrite) != 0) getch(), exit(1);
	return 0;

}








void user_message_out(LINKLIST *LIST,int* page, unsigned long* id) {
	

	int hz_input_len = 0;
	int tag = -99;
	int message_tag;
	int click = -99;
	int mouse_flag;
	int len;
	int active_button;
	int topic;
	char topic_text[30] = { '\0' };
	char content[120]= { '\0' };
	int topic_len=0;
	int content_len=0;

	user_button UserButtons[] = {
{USER_BIKE_REGISTER_X1, USER_BIKE_REGISTER_X2,USER_BIKE_REGISTER_Y1, USER_BIKE_REGISTER_Y2,ACTIVE_USER_BIKE_REGISTER,USER_BIKE_REGISTER},
{USER_BIKE_LICENSE_X1, USER_BIKE_LICENSE_X2,USER_BIKE_LICENSE_Y1, USER_BIKE_LICENSE_Y2,ACTIVE_USER_BIKE_LICENSE,USER_BIKE_LICENSE_NOTICE},
{USER_ANNUAL_X1, USER_ANNUAL_X2,USER_ANNUAL_Y1, USER_ANNUAL_Y2,ACTIVE_USER_ANNUAL,USER_ANNUAL},
{USER_BIKE_WROTEOUT_X1, USER_BIKE_WROTEOUT_X2,USER_BIKE_WROTEOUT_Y1, USER_BIKE_WROTEOUT_Y2,ACTIVE_USER_BIKE_WROTEOUT,USER_BIKE_WROTEOUT},
{USER_INFO_X1, USER_INFO_X2,USER_INFO_Y1, USER_INFO_Y2,ACTIVE_USER_INFO,USER_INFO},
{USER_MESSAGE_X1, USER_MESSAGE_X2,USER_MESSAGE_Y1, USER_MESSAGE_Y2,ACTIVE_USER_MESSAGE,USER_MESSAGE},
{USER_HELP_X1, USER_HELP_X2,USER_HELP_Y1, USER_HELP_Y2,ACTIVE_USER_HELP,USER_HELP},
{USER_BACK_X1,USER_BACK_X2,USER_BACK_Y1,USER_BACK_Y2,ACTIVE_USER_BACK,LOGIN},
{USER_EXIT_X1,USER_EXIT_X2,USER_EXIT_Y1,USER_EXIT_Y2,ACTIVE_USER_EXIT,EXIT},
	};
	user_button MessageOutButtons[] = {
{USER_MESSAGE_OUT_BUTTON1_X1, USER_MESSAGE_OUT_BUTTON1_X2,USER_MESSAGE_OUT_BUTTON1_Y1, USER_MESSAGE_OUT_BUTTON1_Y2, 11},
{USER_MESSAGE_OUT_BUTTON2_X1, USER_MESSAGE_OUT_BUTTON2_X2, USER_MESSAGE_OUT_BUTTON2_Y1, USER_MESSAGE_OUT_BUTTON2_Y2, 12},
{USER_MESSAGE_OUT_BUTTON3_X1, USER_MESSAGE_OUT_BUTTON3_X2,USER_MESSAGE_OUT_BUTTON3_Y1, USER_MESSAGE_OUT_BUTTON3_Y2, 13},
{USER_MESSAGE_OUT_BUTTON4_X1, USER_MESSAGE_OUT_BUTTON4_X2,USER_MESSAGE_OUT_BUTTON4_Y1, USER_MESSAGE_OUT_BUTTON4_Y2, 14},
{USER_MESSAGE_OUT_BUTTON5_X1, USER_MESSAGE_OUT_BUTTON5_X2,USER_MESSAGE_OUT_BUTTON5_Y1, USER_MESSAGE_OUT_BUTTON5_Y2, 15},
{USER_MESSAGE_OUT_BUTTON6_X1, USER_MESSAGE_OUT_BUTTON6_X2,USER_MESSAGE_OUT_BUTTON6_Y1, USER_MESSAGE_OUT_BUTTON6_Y2, 16},
{USER_MESSAGE_OUT_BUTTON7_X1, USER_MESSAGE_OUT_BUTTON7_X2, USER_MESSAGE_OUT_BUTTON7_Y1, USER_MESSAGE_OUT_BUTTON7_Y2, 16}, 
{USER_MESSAGE_OUT_INPUT1_X1, USER_MESSAGE_OUT_INPUT1_X2, USER_MESSAGE_OUT_INPUT1_Y1, USER_MESSAGE_OUT_INPUT1_Y2, 21},
{ USER_MESSAGE_OUT_INPUT2_X1, USER_MESSAGE_OUT_INPUT2_X2, USER_MESSAGE_OUT_INPUT2_Y1, USER_MESSAGE_OUT_INPUT2_Y2, 22 },
	};
	

	clrmous(MouseX, MouseY);
	save_bk_mou(MouseX, MouseY);
	drawgraph_user_main(page);
	setfillstyle(SOLID_FILL, MY_RED);
	drawgraph_user_message_out(MessageOutButtons);

	while (1) {
		newmouse_data(&MouseX, &MouseY, &press, &mouse_flag);
		flushUserMain(&tag, STRUCT_LENGTH(UserButtons), UserButtons); // 刷新界面
		flushMessageOut(&message_tag,MessageOutButtons,9);
		handle_message_out_click(MessageOutButtons, &topic);
		click = handle_click_main(STRUCT_LENGTH(UserButtons), UserButtons);
		if (click == LOGIN || click == EXIT || click == USER_BIKE_REGISTER || click == USER_BIKE_LICENSE_NOTICE || click == USER_BIKE_WROTEOUT || click == USER_INFO || click == USER_HELP) {          //其它页面做完后此处会改成click!=-1&&click!=USER_BIKE_REGISTER
			*page = click;
			return;
		}
		if (mouse_press(USER_MESSAGE_OUT_INPUT1_X1, USER_MESSAGE_OUT_INPUT1_Y1, USER_MESSAGE_OUT_INPUT1_X2, USER_MESSAGE_OUT_INPUT1_Y2) == 1 && topic == 4) {
			topic_len = hz_input(USER_MESSAGE_OUT_INPUT1_X1 + 5, USER_MESSAGE_OUT_INPUT1_Y1 + 3, USER_MESSAGE_OUT_INPUT1_X2, USER_MESSAGE_OUT_INPUT1_Y2, topic_text, topic_len, MY_WHITE, MY_BLACK, 16);
		}
		if (mouse_press(USER_MESSAGE_OUT_INPUT2_X1, USER_MESSAGE_OUT_INPUT2_Y1, USER_MESSAGE_OUT_INPUT2_X2, USER_MESSAGE_OUT_INPUT2_Y2) == 1) {
			content_len = hz_input(USER_MESSAGE_OUT_INPUT2_X1 + 5, USER_MESSAGE_OUT_INPUT2_Y1 + 3, USER_MESSAGE_OUT_INPUT2_X2, USER_MESSAGE_OUT_INPUT2_Y2, content,content_len, MY_WHITE, MY_BLACK, 16);
		}
		if (mouse_press(USER_MESSAGE_OUT_BUTTON6_X1, USER_MESSAGE_OUT_BUTTON6_X2, USER_MESSAGE_OUT_BUTTON6_Y1, USER_MESSAGE_OUT_BUTTON6_Y2) == 1 ) {
			if ((topic != 4 || topic_text[0] != '\0') && content[0] != '\0') {
				user_message_send(LIST,topic, topic_text, content, id);
				setfillstyle(SOLID_FILL, MY_WHITE);
				bar(150, 60, 640, 480);
				puthz(280, 200, "您已发送成功", 32, 40, MY_BLACK);
				puthz(245, 260, "即将返回主界面", 32, 40, MY_BLACK);
				delay(2000);
				*page = MAIN_USER;
				return;
			}
			else
				puthz(220, 410, "不能发送空消息", 24, 22, MY_RED);
		}
		newmouse(&MouseX, &MouseY, &press, &mouse_flag);
		delay(25);
	}
}

void drawgraph_user_message_out(user_button *UserButtons) {
	int i = 0;
	for (i = 0; i < 9; i++) {
		setcolor(MY_LIGHTGRAY);
		setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
		rectangle(UserButtons[i].x1, UserButtons[i].y1, UserButtons[i].x2, UserButtons[i].y2);
	}
	puthz(280, 80, "问题反馈", 32, 40, MY_BLACK);
	puthz(180, 125, "登记问题", 24, 22, MY_BLACK);
	puthz(400, 125, "通行证问题", 24, 22, MY_BLACK);
	puthz(180, 165, "年审问题", 24, 22, MY_BLACK);
	puthz(400, 165, "报废问题", 24, 22, MY_BLACK);
	puthz(200, 215, "其它", 24, 22, MY_BLACK);
	puthz(185, 270, "具体内容", 24, 22, MY_BLACK);
	setfillstyle(SOLID_FILL, MY_RED);
	bar(UserButtons[5].x1, UserButtons[5].y1, UserButtons[5].x2, UserButtons[5].y2);
	puthz(UserButtons[5].x1 + 7, UserButtons[5].y1 + 5, "提交", 24, 22, MY_WHITE);
	bar(UserButtons[6].x1, UserButtons[6].y1, UserButtons[6].x2, UserButtons[6].y2);
	puthz(UserButtons[6].x1 + 7, UserButtons[6].y1 + 5, "返回", 24, 22, MY_WHITE);
}

void flushMessageOut(int* change_tag, user_button *UserButtons, int button_count) {
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

	if (*change_tag != new_tag) {
		*change_tag = new_tag;
		if (new_tag != ACTIVE_USER_NONE) {
			setcolor(MY_BLACK);
			setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
			rectangle(UserButtons[temp].x1-2, UserButtons[temp].y1-2, UserButtons[temp].x2+2, UserButtons[temp].y2+2);
			MouseS = 1;
		}
		else {
			// 清除提示
			setcolor(MY_WHITE);
			setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
			for (i = 0; i < button_count; i++) {
				rectangle(UserButtons[i].x1-2, UserButtons[i].y1-2, UserButtons[i].x2+2, UserButtons[i].y2+2);
			}
		}
	}
}

void handle_message_out_click(user_button* UserButtons,int* topic) {
	int i, j = 0;
	for (i = 0; i < 5; i++) {
		if (mouse_press(UserButtons[i].x1, UserButtons[i].y1, UserButtons[i].x2, UserButtons[i].y2) == 1) {
			for (j = 0; j < 5; j++) {
				setfillstyle(SOLID_FILL, MY_WHITE);
				bar(UserButtons[j].x1 + 3, UserButtons[j].y1 + 3, UserButtons[j].x2 - 3, UserButtons[j].y2 - 3);
			}
			setfillstyle(SOLID_FILL, MY_BLACK);
			bar(UserButtons[i].x1 + 3, UserButtons[i].y1 + 3, UserButtons[i].x2 - 3, UserButtons[i].y2 - 3);
			*topic = i;
		}
	}
	
}

void user_message_send(LINKLIST *LIST,int topic, char* topic_text, char* content_text, unsigned long* id) {
	char topic_choice[][15] = { "电动车登记", "电动车通行证", "电动车年审", "电动车报废" };
	char buffer[20];
	EBIKE_INFO sender_info;
	MESSAGE message_to_send;
	int i;
	int account_counts;
	FILE* fp_USER_MESSAGE_SEND_read = fopen("DATA\\MESSAGE.DAT", "rb+");
	if (fp_USER_MESSAGE_SEND_read == NULL) {
		fclose(fp_USER_MESSAGE_SEND_read);
		exit(0);
	}
	user_bike_register_getinfo(LIST,&sender_info, id);

	if (topic != 4) {
		strcpy(message_to_send.title, topic_choice[topic]);
	}
	else {
		strcpy(message_to_send.title, topic_text);
	}
	rand_id(buffer); // 生成随机id
	message_to_send.message_id = atol(buffer);
	message_to_send.sender_id = *id;
	strcpy(message_to_send.sender_username, sender_info.rln);
	strcpy(message_to_send.message, content_text);
	message_to_send.time = get_approx_time(NULL);
	message_to_send.is_read = 0;
	message_to_send.is_replied = 0;
	message_to_send.receiver_id = 0;
	message_to_send.message_type = ANNOUNCEMENT;
	strcpy(message_to_send.receiver_username, "all_admin");

	fseek(fp_USER_MESSAGE_SEND_read, 0, SEEK_END);
	fwrite(&message_to_send, sizeof(MESSAGE), 1, fp_USER_MESSAGE_SEND_read);
	fclose(fp_USER_MESSAGE_SEND_read);
	return 0;

}


/*
void user_message(int* page, unsigned long* ID) {
	int mouse_flag;
	int tag = ACTIVE_ADMIN_NULL;
	unsigned long id_list[8] = { 0,0,0,0,0,0,0,0 }; // 记录当前显示的列表每行对应的ID
	unsigned long selected_id = 0; // 选中行的ID
	char search_str[20] = "\0"; // 搜索框输入信息储存
	char search_needed[10] = "\0";
	ADMIN_BUTTONS AdminButtons[7]= {
		{ADMIN_FEATURE1_X1, ADMIN_FEATURE1_X2,
		 ADMIN_FEATURE1_Y1, ADMIN_FEATURE1_Y2,
		 ACTIVE_ADMIN_FEATURE1, &draw_rectangle, &clear_rectangle},
		{ADMIN_FEATURE6_X1, ADMIN_FEATURE6_X2,
		 ADMIN_FEATURE6_Y1, ADMIN_FEATURE6_Y2,
		 ACTIVE_ADMIN_FEATURE6, &draw_rectangle, &clear_rectangle},
		{ADMIN_FEATURE_EXIT_X1, ADMIN_FEATURE_EXIT_X2,
		 ADMIN_FEATURE_EXIT_Y1, ADMIN_FEATURE_EXIT_Y2,
		 ACTIVE_ADMIN_FEATURE_EXIT, &draw_exit, &clear_exit},
		{ADMIN_FEATURE_UP_X1, ADMIN_FEATURE_UP_X2,
		 ADMIN_FEATURE_UP_Y1, ADMIN_FEATURE_UP_Y2,
		 ACTIVE_ADMIN_FEATURE_UP, &draw_flip_up, &clear_flip_up},
		{ADMIN_FEATURE_DOWN_X1, ADMIN_FEATURE_DOWN_X2,
		 ADMIN_FEATURE_DOWN_Y1, ADMIN_FEATURE_DOWN_Y2,
		 ACTIVE_ADMIN_FEATURE_DOWN, &draw_flip_down, &clear_flip_down},
		 // 31
		 // 以下为消息按钮
		 {ADMIN_MESSAGE_REPLY_X1, ADMIN_MESSAGE_REPLY_X2,
		  ADMIN_MESSAGE_REPLY_Y1, ADMIN_MESSAGE_REPLY_Y2,
		  ACTIVE_ADMIN_MESSAGE_REPLY, &draw_rectangle, &clear_rectangle},
		 {ADMIN_MESSAGE_EXIT_X1, ADMIN_MESSAGE_EXIT_X2,
		  ADMIN_MESSAGE_EXIT_Y1, ADMIN_MESSAGE_EXIT_Y2,
		  ACTIVE_ADMIN_MESSAGE_EXIT, &draw_exit, &clear_exit},
	};
	FILE* fp = fopen("DATA\\MESSAGE.DAT", "rb+"); // 打开消息数据文件
	if (!fp)
		getch(), exit(1);

	//define_user_message_buttons(AdminButtons, *page); // 定义按钮
	clrmous(MouseX, MouseY);

	//drawgraph_admin_menu(); // 初始化界面
	drawgraph_user_message_center(); // 绘制界面
	admin_list_info(NULL, LIST_LIMIT, LIST_INTERVAL, id_list, fp, "message", NULL, NULL, LIST_STAY, LIST_CLEAR_CONTINUE, search_str, search_needed); // 清除列表


	while (1) {
		newmouse_data(&MouseX, &MouseY, &press, &mouse_flag);
		admin_flush_buttons(&tag, STRUCT_LENGTH(AdminButtons), AdminButtons);
		user_handle_message_click_event(fp, page, id_list, &selected_id, search_str, search_needed);
		message_list_click(ADMIN_INTERFACE_X1, ADMIN_INTERFACE_Y1, LIST_LIMIT, LIST_INTERVAL, id_list, &selected_id); // 处理点击事件

		newmouse(&MouseX, &MouseY, &press, &mouse_flag);
		delay(25);
	}

	fclose(fp);
}

void drawgraph_user_message_center()
{
	setfillstyle(SOLID_FILL, MY_YELLOW);
	bar(ADMIN_FEATURE1_X1, ADMIN_FEATURE1_Y1, ADMIN_FEATURE1_X2, ADMIN_FEATURE1_Y2);
	
	puthz(ADMIN_FEATURE1_X1 + 4, ADMIN_FEATURE1_Y1 + 7, "查看信息", 16, 16, MY_WHITE);
	setfillstyle(SOLID_FILL, MY_RED);
	bar(ADMIN_FEATURE6_X1, ADMIN_FEATURE6_Y1, ADMIN_FEATURE6_X2, ADMIN_FEATURE6_Y2);
	puthz(ADMIN_FEATURE6_X1 + 4, ADMIN_FEATURE6_Y1 + 7, "发送消息", 16, 16, MY_WHITE);


	clear_flip_up(ADMIN_FEATURE_UP_X1, ADMIN_FEATURE_UP_Y1, ADMIN_FEATURE_UP_X2, ADMIN_FEATURE_UP_Y2);
	clear_flip_down(ADMIN_FEATURE_DOWN_X1, ADMIN_FEATURE_DOWN_Y1, ADMIN_FEATURE_DOWN_X2, ADMIN_FEATURE_DOWN_Y2);
}

*/

void user_handle_message_click_event(FILE* fp, int* page, unsigned long id_list[], unsigned long* selected_id,
	char* search_str, char* search_needed)
{
	long pos = -1;
	char buffer[20];
	MESSAGE msg;

	
	if (mouse_press(USER_MESSAGE_FEATURE_EXIT_X1, USER_MESSAGE_FEATURE_EXIT_Y1,
		USER_MESSAGE_FEATURE_EXIT_X2, USER_MESSAGE_FEATURE_EXIT_Y2) == 1) // 点击返回
	{
		*page = USER_MESSAGE;
	}

	
	if (mouse_press(USER_MESSAGE_FEATURE1_X1, USER_MESSAGE_FEATURE1_Y1,
		USER_MESSAGE_FEATURE1_X2, USER_MESSAGE_FEATURE1_Y2) == 1) // 点击查看信息
	{
		if (*selected_id != 0) // 未选中
		{
			ltoa(*selected_id, buffer, 10);
			pos = find_file_info(fp, "message", buffer, "message_id"); // 查找信息
			if (pos != -1)                                                 // 找到信息
			{
				ltoa(*selected_id, buffer, 10);
				if (message_get(fp, &msg, buffer, "message_id") != 1) // 读取选中的消息
				{
					puthz(10, 10, "未找到信息！", 16, 16, MY_RED); // 显示未找到信息
					return;
				}
				message_display(&msg);                       // 显示选中的消息，这玩意在vscode里为什么报错我不得而知

				msg.is_read = 1;                                   // 将消息标记为已读
				message_overwrite(fp, &msg, buffer, "message_id"); // 将选中的消息标记为已读
				admin_list_info(NULL, LIST_LIMIT, LIST_INTERVAL, id_list, fp, "message", NULL, NULL, LIST_STAY, LIST_CLEAR_CONTINUE, "\0", "\0"); // 清除列表
				*selected_id = 0;
			}
		}
	}

	
	if (mouse_press(USER_MESSAGE_FEATURE_UP_X1, USER_MESSAGE_FEATURE_UP_Y1,
		USER_MESSAGE_FEATURE_UP_X2, USER_MESSAGE_FEATURE_UP_Y2) == 1) // 点击上一页
	{
		admin_list_info(NULL, LIST_LIMIT, LIST_INTERVAL, id_list, fp, "message", NULL, NULL, LIST_PAGEUP, LIST_NO_CLEAR, search_str, "message_id"); // 清除列表
	}
	if (mouse_press(USER_MESSAGE_FEATURE_DOWN_X1, USER_MESSAGE_FEATURE_DOWN_Y1,
		USER_MESSAGE_FEATURE_DOWN_X2, USER_MESSAGE_FEATURE_DOWN_Y2) == 1) // 点击下一页
	{
		admin_list_info(NULL, LIST_LIMIT, LIST_INTERVAL, id_list, fp, "message", NULL, NULL, LIST_PAGEDOWN, LIST_NO_CLEAR, search_str, "message_id"); // 清除列表
	}
}


void user_message(int* page, unsigned long* ID) {
	int mouse_flag;
	int user_tag;
	int click = -99;
	int tag = ACTIVE_ADMIN_NULL;
	unsigned long id_list[8] = { 0,0,0,0,0,0,0,0 }; // 记录当前显示的列表每行对应的ID
	unsigned long selected_id = 0; // 选中行的ID
	char search_str[20] = "\0"; // 搜索框输入信息储存
	char search_needed[20] = "user_receiver_id";

	user_button UserButtons[] = {
{USER_BIKE_REGISTER_X1, 120,USER_BIKE_REGISTER_Y1, USER_BIKE_REGISTER_Y2,ACTIVE_USER_BIKE_REGISTER,USER_BIKE_REGISTER},
{USER_BIKE_LICENSE_X1, 120,USER_BIKE_LICENSE_Y1, USER_BIKE_LICENSE_Y2,ACTIVE_USER_BIKE_LICENSE,USER_BIKE_LICENSE_NOTICE},
{USER_ANNUAL_X1, 120,USER_ANNUAL_Y1, USER_ANNUAL_Y2,ACTIVE_USER_ANNUAL,USER_ANNUAL},
{USER_BIKE_WROTEOUT_X1, 120,USER_BIKE_WROTEOUT_Y1, USER_BIKE_WROTEOUT_Y2,ACTIVE_USER_BIKE_WROTEOUT,USER_BIKE_WROTEOUT},
{USER_INFO_X1, 120,USER_INFO_Y1, USER_INFO_Y2,ACTIVE_USER_INFO,USER_INFO},
{USER_MESSAGE_X1, 120,USER_MESSAGE_Y1, USER_MESSAGE_Y2,ACTIVE_USER_MESSAGE,USER_MESSAGE},
{USER_HELP_X1,120,USER_HELP_Y1, USER_HELP_Y2,ACTIVE_USER_HELP,USER_HELP},
{USER_BACK_X1,USER_BACK_X2,USER_BACK_Y1,USER_BACK_Y2,ACTIVE_USER_BACK,LOGIN},
{5,25,5,25,ACTIVE_USER_EXIT,EXIT},
	};
	
	
	ADMIN_BUTTONS AdminButtons[7] = {
		{USER_MESSAGE_FEATURE1_X1, USER_MESSAGE_FEATURE1_X2,
		 USER_MESSAGE_FEATURE1_Y1, USER_MESSAGE_FEATURE1_Y2,
		 ACTIVE_ADMIN_FEATURE1, &draw_rectangle, &clear_rectangle},
		{USER_MESSAGE_FEATURE6_X1, USER_MESSAGE_FEATURE6_X2,
		 USER_MESSAGE_FEATURE6_Y1, USER_MESSAGE_FEATURE6_Y2,
		 ACTIVE_ADMIN_FEATURE6, &draw_rectangle, &clear_rectangle},
		{USER_MESSAGE_FEATURE_EXIT_X1, USER_MESSAGE_FEATURE_EXIT_X2,
		 USER_MESSAGE_FEATURE_EXIT_Y1, USER_MESSAGE_FEATURE_EXIT_Y2,
		 ACTIVE_ADMIN_FEATURE_EXIT, &draw_exit, &clear_exit},
		{USER_MESSAGE_FEATURE_UP_X1, USER_MESSAGE_FEATURE_UP_X2,
		 USER_MESSAGE_FEATURE_UP_Y1, USER_MESSAGE_FEATURE_UP_Y2,
		 ACTIVE_ADMIN_FEATURE_UP,& draw_rectangle,& clear_rectangle},
		{USER_MESSAGE_FEATURE_DOWN_X1, USER_MESSAGE_FEATURE_DOWN_X2,
		 USER_MESSAGE_FEATURE_DOWN_Y1, USER_MESSAGE_FEATURE_DOWN_Y2,
		 ACTIVE_ADMIN_FEATURE_DOWN,& draw_rectangle,& clear_rectangle},
		 // 31
		 // 以下为消息按钮
		 {USER_MESSAGE_REPLY_X1, USER_MESSAGE_REPLY_X2,
		  USER_MESSAGE_REPLY_Y1, USER_MESSAGE_REPLY_Y2,
		  ACTIVE_ADMIN_MESSAGE_REPLY, &draw_rectangle, &clear_rectangle},
		 /*{USER_MESSAGE_EXIT_X1, USER_MESSAGE_EXIT_X2,
		  USER_MESSAGE_EXIT_Y1, USER_MESSAGE_EXIT_Y2,
		  ACTIVE_ADMIN_MESSAGE_EXIT, &draw_exit, &clear_exit},*/
	};
	FILE* fp = fopen("DATA\\MESSAGE.DAT", "rb+"); // 打开消息数据文件
	if (!fp)
		getch(), exit(1);

	


	clrmous(MouseX, MouseY);

	
	//drawgraph_admin_menu(); // 初始化界面
	drawgraph_user_main_message();
	drawgraph_user_message_center(); // 绘制界面

	setfillstyle(SOLID_FILL, MY_WHITE);
	bar(130, 335, 630, 350);
	sprintf(search_str, "%ld", *ID);
	admin_list_info(NULL, LIST_LIMIT, LIST_INTERVAL, id_list, fp, "message", NULL, NULL, LIST_STAY, LIST_CLEAR_CONTINUE, search_str, search_needed); // 清除列表
	

	while (1) {
		newmouse_data(&MouseX, &MouseY, &press, &mouse_flag);
		flushUserMessageMain(&user_tag, STRUCT_LENGTH(UserButtons), UserButtons);
		click = handle_click_main(STRUCT_LENGTH(UserButtons), UserButtons);
		if (click != -99 && click != USER_BIKE_LICENSE_NOTICE) {          //其它页面做完后此处会改成click!=-1&&click!=USER_BIKE_LICENSE_NOTICE
			*page = click;
			return;
		}
		if (mouse_press(USER_MESSAGE_FEATURE6_X1, USER_MESSAGE_FEATURE6_Y1, USER_MESSAGE_FEATURE6_X2, USER_MESSAGE_FEATURE6_Y2) == 1) {
			*page = USER_MESSAGE_OUT;
			return;
		}
		admin_flush_buttons(&tag, STRUCT_LENGTH(AdminButtons), AdminButtons);
		user_handle_message_click_event(fp, page, id_list, &selected_id, search_str, search_needed);
		message_list_click(ADMIN_INTERFACE_X1, ADMIN_INTERFACE_Y1, LIST_LIMIT, LIST_INTERVAL, id_list, &selected_id); // 处理点击事件

		newmouse(&MouseX, &MouseY, &press, &mouse_flag);
		delay(25);
	}

	fclose(fp);
}

void drawgraph_user_message_center()
{
	setfillstyle(SOLID_FILL, MY_YELLOW);
	bar(USER_MESSAGE_FEATURE1_X1, USER_MESSAGE_FEATURE1_Y1, USER_MESSAGE_FEATURE1_X2, USER_MESSAGE_FEATURE1_Y2);

	puthz(USER_MESSAGE_FEATURE1_X1 + 7, USER_MESSAGE_FEATURE1_Y1 + 7, "查看信息", 16, 16, MY_WHITE);
	setfillstyle(SOLID_FILL, MY_RED);
	bar(USER_MESSAGE_FEATURE6_X1, USER_MESSAGE_FEATURE6_Y1, USER_MESSAGE_FEATURE6_X2, USER_MESSAGE_FEATURE6_Y2);
	puthz(USER_MESSAGE_FEATURE6_X1 + 7, USER_MESSAGE_FEATURE6_Y1 + 7, "发送消息", 16, 16, MY_WHITE);

	
	puthz(140, 50, "消息主题", 16, 16, MY_BLACK);
	puthz(440, 50, "发送者", 16, 16, MY_BLACK);
	puthz(560, 50, "状态", 16, 16, MY_BLACK);
	
	//clear_flip_up(USER_MESSAGE_FEATURE_UP_X1, USER_MESSAGE_FEATURE_UP_Y1, USER_MESSAGE_FEATURE_UP_X2, USER_MESSAGE_FEATURE_UP_Y2);
	//clear_flip_down(USER_MESSAGE_FEATURE_DOWN_X1, USER_MESSAGE_FEATURE_DOWN_Y1, USER_MESSAGE_FEATURE_DOWN_X2, USER_MESSAGE_FEATURE_DOWN_Y2);
	setfillstyle(SOLID_FILL, MY_CREAM);
	bar(USER_MESSAGE_FEATURE_UP_X1, USER_MESSAGE_FEATURE_UP_Y1, USER_MESSAGE_FEATURE_UP_X2, USER_MESSAGE_FEATURE_UP_Y2);
	bar(USER_MESSAGE_FEATURE_DOWN_X1, USER_MESSAGE_FEATURE_DOWN_Y1, USER_MESSAGE_FEATURE_DOWN_X2, USER_MESSAGE_FEATURE_DOWN_Y2);
	puthz(USER_MESSAGE_FEATURE_UP_X1 + 4, USER_MESSAGE_FEATURE_UP_Y1 + 7, "上一页", 16, 16, MY_BLACK);
	puthz(USER_MESSAGE_FEATURE_DOWN_X1 + 4, USER_MESSAGE_FEATURE_DOWN_Y1 + 7, "下一页", 16, 16, MY_BLACK);
}

void user_message_display(struct _MESSAGE_ *msg)
{
	int tag = ACTIVE_ADMIN_NULL; // 定义标签变量
	int is_return = 0;
	int mouse_flag;
	char buffer1[10];
	char buffer2[10];
	ADMIN_BUTTONS btn[2];                     // 定义按钮变量
	define_admin_buttons(btn, ADMIN_MESSAGE_DISPLAY); // 定义按钮
	if (msg->message_type != PRIVATE_MESSAGE)
	{
		memset(&btn[1], '\0', sizeof(btn[1])); // 清空按钮变量
	}

	clrmous(MouseX, MouseY); // 清除鼠标
	message_display_draw_bg();

	if (msg == NULL)
	{
		message_topic_display(120, 35, 400, "信息错误", MY_RED, 24, 3, 0); // 显示消息的主题
	}
	else
	{
		message_topic_display(120, 35, 400, msg->title, MY_BLACK, 24, 3, 0); // 显示消息的主题
		message_text_display(160, 80, 400, msg->sender_username, MY_BLACK);  // 显示消息的发送者
		ltoa(msg->time, buffer1, 10);
		sprintf(buffer2, "%.4s.%.2s.%.2s", buffer1, buffer1 + 4, buffer1 + 6);
		message_text_display(390, 80, 400, buffer2, MY_BLACK);         // 显示消息的发时间
		message_text_display(120, 110, 400, msg->message, MY_BLACK);         // 显示消息的内容
	}

	while (is_return == 0)
	{
		newmouse_data(&MouseX, &MouseY, &press, &mouse_flag);

		admin_flush_buttons(&tag, 3, btn); // 刷新按钮
		message_handle_click_event(&is_return, msg); // 处理点击事件

		newmouse(&MouseX, &MouseY, &press, &mouse_flag);
	}
	drawgraph_admin_menu();
	drawgraph_admin_message_center();
}

void drawgraph_user_main_message() {
	char time_string[10] = { '\0' };
	unsigned long time = get_approx_time(time_string);

	initcolorpalette();
	setbkcolor(MY_LIGHTBLUE);//主界面
	setfillstyle(1, 0);
	setcolor(MY_LIGHTBLUE);
	bar(0, 0, 640, 480);
	//puthz(120, 10, "校园电动车管理系统", 32, 40, MY_WHITE);
	setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
	setcolor(MY_WHITE);
	setfillstyle(1, MY_WHITE);
	bar(120,30, 640, 480);
	setfillstyle(1, MY_LIGHTGRAY);//侧框
	setcolor(MY_LIGHTGRAY);
	bar(0, 30, 120, 480);
	setcolor(MY_LIGHTGRAY);
	//setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
	//rectangle(151, 61, 639, 479);

	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2); // 默认字体，水平方向，大小2
	setcolor(MY_WHITE);
	//outtextxy(5, 450, time_string);

	setfillstyle(1, MY_YELLOW);//返回登录界面
	setcolor(MY_YELLOW);
	bar(USER_BACK_X1, USER_BACK_Y1, USER_BACK_X2, USER_BACK_Y2);

	setfillstyle(1, MY_RED);//退出
	setcolor(MY_RED);
	bar(5,25,5,25);
	setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
	setcolor(MY_WHITE);
	line(5,5,24,24);
	line(4,4,25,24);

	puthz(USER_BIKE_REGISTER_X1 + 15, (USER_BIKE_REGISTER_Y1 + USER_BIKE_REGISTER_Y2) / 2 - 5, "登记", 24, 22, MY_WHITE);
	puthz(USER_ANNUAL_X1 + 15, (USER_ANNUAL_Y1 + USER_ANNUAL_Y2) / 2 - 5, "年审", 24, 22, MY_WHITE);
	puthz(USER_BIKE_LICENSE_X1 + 15, (USER_BIKE_LICENSE_Y1 + USER_BIKE_LICENSE_Y2) / 2 - 5, "通行证", 24, 22, MY_WHITE);
	puthz(USER_BIKE_WROTEOUT_X1 + 15, (USER_BIKE_WROTEOUT_Y1 + USER_BIKE_WROTEOUT_Y2) / 2 - 5, "报废", 24, 22, MY_WHITE);
	puthz(USER_INFO_X1 + 15, (USER_INFO_Y1 + USER_INFO_Y2) / 2 - 5, "信息管理", 24, 22, MY_WHITE);
	puthz(USER_MESSAGE_X1 + 15, (USER_MESSAGE_Y1 + USER_MESSAGE_Y2) / 2 - 5, "消息中心", 24, 22, MY_WHITE);
	puthz(USER_HELP_X1 + 15, (USER_HELP_Y1 + USER_HELP_Y2) / 2 - 5, "帮助", 24, 22, MY_WHITE);
	puthz(USER_BACK_X1 + 10, (USER_BACK_Y1 + USER_BACK_Y2) / 2 - 10, "返回", 24, 25, MY_WHITE);
}

void flushUserMessageMain(int* tag, int button_count, user_button UserButtons[]) {
	int i = 0;
	int temp = 0;
	int new_tag = ACTIVE_USER_NONE;



	for (i = 0; i < button_count; i++) {
		if (MouseX >= UserButtons[i].x1 && MouseX <= UserButtons[i].x2 &&
			MouseY >= UserButtons[i].y1 && MouseY <= UserButtons[i].y2) {
			new_tag = UserButtons[i].active_tag;
			MouseS = 1;
			temp = i;
			break;
		}
	}

	if (*tag != new_tag) {
		if (*tag != ACTIVE_USER_NONE) {
			if (*tag <= ACTIVE_USER_HELP) {
				setcolor(MY_LIGHTGRAY);
				setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
				rectangle(UserButtons[*tag - 1].x1, UserButtons[*tag - 1].y1, UserButtons[*tag - 1].x2, UserButtons[*tag - 1].y2);

			}
			else if (*tag == ACTIVE_USER_EXIT) {
				setcolor(MY_RED);
				setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
				rectangle(UserButtons[*tag - 1].x1, UserButtons[*tag - 1].y1, UserButtons[*tag - 1].x2, UserButtons[*tag - 1].y2);

			}
			else if (*tag == ACTIVE_USER_BACK) {
				setcolor(MY_LIGHTBLUE);
				setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
				rectangle(UserButtons[*tag - 1].x1, UserButtons[*tag - 1].y1, UserButtons[*tag - 1].x2, UserButtons[*tag - 1].y2);

			}
		}
		*tag = new_tag;
		if (new_tag != ACTIVE_USER_NONE && new_tag <= ACTIVE_USER_HELP) {
			setfillstyle(1, MY_WHITE);
			setcolor(MY_WHITE);
			setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
			rectangle(UserButtons[temp].x1, UserButtons[temp].y1, UserButtons[temp].x2, UserButtons[temp].y2);

		}
		else if (new_tag == ACTIVE_USER_EXIT) {
			setfillstyle(1, MY_WHITE);
			setcolor(MY_WHITE);
			setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
			rectangle(UserButtons[temp].x1, UserButtons[temp].y1, UserButtons[temp].x2, UserButtons[temp].y2);

		}
		else if (new_tag == ACTIVE_USER_BACK) {
			setcolor(MY_BLACK);
			setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
			rectangle(UserButtons[temp].x1, UserButtons[temp].y1, UserButtons[temp].x2, UserButtons[temp].y2);
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


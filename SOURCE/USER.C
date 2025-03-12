#include"USER.H"
void user_main() {
	int tag = 0;
	int page = 0;
	clrmous(MouseX, MouseY);
	save_bk_mou(MouseX, MouseY);
	drawgraph_user_main();
	
	while (1) {
		flushUserGraph(&tag,&page); // 刷新界面
		newmouse(&MouseX, &MouseY, &press); // 刷新鼠标
		delay(25); // 50hz刷新率
	}
}

void drawgraph_user_main() {
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

	setcolor(MY_WHITE);//功能按钮
	rectangle(BIKE_REGISTER_X1, BIKE_REGISTER_Y1, BIKE_REGISTER_X2, BIKE_REGISTER_Y2);
	rectangle(BIKE_LICENSE_X1, BIKE_LICENSE_Y1, BIKE_LICENSE_X2, BIKE_LICENSE_Y2);
	rectangle(BIKE_ANUAL_X1, BIKE_ANUAL_Y1, BIKE_ANUAL_X2, BIKE_ANUAL_Y2);
	rectangle(BIKE_WROTEOUT_X1, BIKE_WROTEOUT_Y1, BIKE_WROTEOUT_X2, BIKE_WROTEOUT_Y2);
	rectangle(BIKE_ANUAL_X1, BIKE_ANUAL_Y1, BIKE_ANUAL_X2, BIKE_ANUAL_Y2);
	rectangle(USER_DATAGRAPH_X1, USER_DATAGRAPH_Y1, USER_DATAGRAPH_X2, USER_DATAGRAPH_Y2);
	rectangle(USER_INFO_X1, USER_INFO_Y1, USER_INFO_X2, USER_INFO_Y2);
	rectangle(USER_MESSAGE_X1, USER_MESSAGE_Y1, USER_MESSAGE_X2,USER_MESSAGE_Y2);

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

	puthz(BIKE_REGISTER_X1 + 15, (BIKE_REGISTER_Y1 + BIKE_REGISTER_Y2) / 2-5, "电动车注册",24,25,MY_WHITE);
	puthz(BIKE_ANUAL_X1+ 15, (BIKE_ANUAL_Y1 + BIKE_ANUAL_Y2) / 2-5, "电动车年审", 24, 25, MY_WHITE);
	puthz(BIKE_LICENSE_X1 + 15, (BIKE_LICENSE_Y1 + BIKE_LICENSE_Y2) / 2-5, "电动车证件", 24, 25, MY_WHITE);
	puthz(BIKE_WROTEOUT_X1 + 15, (BIKE_WROTEOUT_Y1 + BIKE_WROTEOUT_Y2) / 2 - 5, "电动车报废", 24, 25, MY_WHITE);
	puthz(USER_INFO_X1 + 5, (USER_INFO_Y1 + USER_INFO_Y2) / 2 - 5, "用户信息管理", 24, 22, MY_WHITE);
	puthz(USER_MESSAGE_X1 + 15, (USER_MESSAGE_Y1 + USER_MESSAGE_Y2) / 2 - 5, "信息中心", 24, 25, MY_WHITE);
	puthz(USER_DATAGRAPH_X1+ 15, (USER_DATAGRAPH_Y1 + USER_DATAGRAPH_Y2) / 2 - 5, "数据可视化", 24, 25, MY_WHITE);
	puthz(USER_BACK_X1 + 5, (USER_BACK_Y1 + USER_BACK_Y2) / 2 - 10, "返回", 24, 25, MY_WHITE);
}
void flushUserGraph(int *tag,int *page) {
	if ((MouseX >= BIKE_ANUAL_X1 && MouseX <= BIKE_ANUAL_X2 && MouseY >= BIKE_ANUAL_Y1 && MouseY <= BIKE_ANUAL_Y2) ||
		(MouseX >= BIKE_LICENSE_X1 && MouseX <= BIKE_LICENSE_X2 && MouseY >=BIKE_LICENSE_Y1 && MouseY <= BIKE_LICENSE_Y2)||
		(MouseX >= BIKE_REGISTER_X1 && MouseX <= BIKE_REGISTER_X2 && MouseY >= BIKE_REGISTER_Y1 && MouseY <= BIKE_REGISTER_Y2)||
		(MouseX >= BIKE_WROTEOUT_X1 && MouseX <= BIKE_WROTEOUT_X2 && MouseY >= BIKE_WROTEOUT_Y1 && MouseY <= BIKE_WROTEOUT_Y2)||
		(MouseX >= USER_DATAGRAPH_X1 && MouseX <= USER_DATAGRAPH_X2 && MouseY >=USER_DATAGRAPH_Y1 && MouseY <= USER_DATAGRAPH_Y2) ||
		(MouseX >= USER_INFO_X1 && MouseX <= USER_INFO_X2 && MouseY >= USER_INFO_Y1 && MouseY <= USER_INFO_Y2) ||
		(MouseX >= USER_MESSAGE_X1 && MouseX <= USER_MESSAGE_X2 && MouseY >=USER_INFO_Y1 && MouseY <= USER_INFO_Y2) ||
		(MouseX >= USER_BACK_X1 && MouseX <= USER_BACK_X2 && MouseY >= USER_BACK_Y1 && MouseY <= USER_BACK_Y2) ||
		(MouseX >= USER_EXIT_X1 && MouseX <= USER_EXIT_X2 && MouseY >= USER_EXIT_Y1 && MouseY <= USER_EXIT_Y2))
		MouseS = 1; // 假设设置为手形图标
	else
	    MouseS = 0; // 恢复默认箭头


	//恢复未激活状态
	if ((MouseX < BIKE_REGISTER_X1 || MouseX > BIKE_REGISTER_X2 || MouseY < BIKE_REGISTER_Y1 || MouseY > BIKE_REGISTER_Y2) && (*tag == ACTIVE_BIKE_REGISTER)) {
		*tag = ACTIVE_NONE;
		setcolor(MY_WHITE);
		setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
		rectangle(BIKE_REGISTER_X1, BIKE_REGISTER_Y1, BIKE_REGISTER_X2, BIKE_REGISTER_Y2);
	}

	if ((MouseX < BIKE_LICENSE_X1 || MouseX > BIKE_LICENSE_X2 || MouseY < BIKE_LICENSE_Y1 || MouseY > BIKE_LICENSE_Y2) && (*tag == ACTIVE_BIKE_LICENSE)) {
		*tag = ACTIVE_NONE;
		setcolor(MY_WHITE);
		setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
		rectangle(BIKE_LICENSE_X1, BIKE_LICENSE_Y1, BIKE_LICENSE_X2, BIKE_LICENSE_Y2);
	}

	if ((MouseX < BIKE_ANUAL_X1 || MouseX > BIKE_ANUAL_X2 || MouseY < BIKE_ANUAL_Y1 || MouseY > BIKE_ANUAL_Y2) && (*tag == ACTIVE_BIKE_ANUAL)) {
		*tag = ACTIVE_NONE;
		setcolor(MY_WHITE);
		setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
		rectangle(BIKE_ANUAL_X1, BIKE_ANUAL_Y1, BIKE_ANUAL_X2, BIKE_ANUAL_Y2);
	}

	if ((MouseX < BIKE_WROTEOUT_X1 || MouseX > BIKE_WROTEOUT_X2 || MouseY < BIKE_WROTEOUT_Y1 || MouseY > BIKE_WROTEOUT_Y2) && (*tag == ACTIVE_BIKE_WROTEOUT)) {
		*tag = ACTIVE_NONE;
		setcolor(MY_WHITE);
		rectangle(BIKE_WROTEOUT_X1, BIKE_WROTEOUT_Y1, BIKE_WROTEOUT_X2, BIKE_WROTEOUT_Y2);
		setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
	}

	if ((MouseX < USER_INFO_X1 || MouseX > USER_INFO_X2 || MouseY < USER_INFO_Y1 || MouseY > USER_INFO_Y2) && (*tag == ACTIVE_USER_INFO)) {
		*tag = ACTIVE_NONE;
		setcolor(MY_WHITE);
		setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
		rectangle(USER_INFO_X1, USER_INFO_Y1, USER_INFO_X2, USER_INFO_Y2);
	}

	if ((MouseX < USER_MESSAGE_X1 || MouseX > USER_MESSAGE_X2 || MouseY < USER_MESSAGE_Y1 || MouseY > USER_MESSAGE_Y2) && (*tag == ACTIVE_USER_MESSAGE)) {
		*tag = ACTIVE_NONE;
		setcolor(MY_WHITE);
		setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
		rectangle(USER_MESSAGE_X1, USER_MESSAGE_Y1, USER_MESSAGE_X2, USER_MESSAGE_Y2);
	}

	if ((MouseX < USER_DATAGRAPH_X1 || MouseX > USER_DATAGRAPH_X2 || MouseY < USER_DATAGRAPH_Y1 || MouseY > USER_DATAGRAPH_Y2) && (*tag == ACTIVE_USER_DATAGRAPH)) {
		*tag = ACTIVE_NONE;
		setcolor(MY_WHITE);
		setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
		rectangle(USER_DATAGRAPH_X1, USER_DATAGRAPH_Y1, USER_DATAGRAPH_X2, USER_DATAGRAPH_Y2);
	}



	//激活
	if (MouseX >= BIKE_REGISTER_X1 && MouseX <= BIKE_REGISTER_X2 && MouseY >= BIKE_REGISTER_Y1 && MouseY <= BIKE_REGISTER_Y2) {
		*tag = ACTIVE_BIKE_REGISTER;
		setcolor(MY_BLACK);
		setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
		rectangle(BIKE_REGISTER_X1, BIKE_REGISTER_Y1, BIKE_REGISTER_X2, BIKE_REGISTER_Y2);
	}

	if (MouseX >= BIKE_LICENSE_X1 && MouseX <= BIKE_LICENSE_X2 && MouseY >= BIKE_LICENSE_Y1 && MouseY <= BIKE_LICENSE_Y2) {
		*tag = ACTIVE_BIKE_LICENSE;
		setcolor(MY_BLACK);
		setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
		rectangle(BIKE_LICENSE_X1, BIKE_LICENSE_Y1, BIKE_LICENSE_X2, BIKE_LICENSE_Y2);
	}

	if (MouseX >= BIKE_ANUAL_X1 && MouseX <= BIKE_ANUAL_X2 && MouseY >= BIKE_ANUAL_Y1 && MouseY <= BIKE_ANUAL_Y2) {
		*tag = ACTIVE_BIKE_ANUAL;
		setcolor(MY_BLACK);
		setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
		rectangle(BIKE_ANUAL_X1, BIKE_ANUAL_Y1, BIKE_ANUAL_X2, BIKE_ANUAL_Y2);
	}

	if (MouseX >= BIKE_WROTEOUT_X1 && MouseX <= BIKE_WROTEOUT_X2 && MouseY >= BIKE_WROTEOUT_Y1 && MouseY <= BIKE_WROTEOUT_Y2) {
		*tag = ACTIVE_BIKE_WROTEOUT;
		setcolor(MY_BLACK);
		setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
		rectangle(BIKE_WROTEOUT_X1, BIKE_WROTEOUT_Y1, BIKE_WROTEOUT_X2, BIKE_WROTEOUT_Y2);
	}

	if (MouseX >= USER_INFO_X1 && MouseX <= USER_INFO_X2 && MouseY >= USER_INFO_Y1 && MouseY <= USER_INFO_Y2) {
		*tag = ACTIVE_USER_INFO;
		setcolor(MY_BLACK);
		setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
		rectangle(USER_INFO_X1, USER_INFO_Y1, USER_INFO_X2, USER_INFO_Y2);
	}

	if (MouseX >= USER_MESSAGE_X1 && MouseX <= USER_MESSAGE_X2 && MouseY >= USER_MESSAGE_Y1 && MouseY <= USER_MESSAGE_Y2) {
		*tag = ACTIVE_USER_MESSAGE;
		setcolor(MY_BLACK);
		setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
		rectangle(USER_MESSAGE_X1, USER_MESSAGE_Y1, USER_MESSAGE_X2, USER_MESSAGE_Y2);
	}

	if (MouseX >= USER_DATAGRAPH_X1 && MouseX <= USER_DATAGRAPH_X2 && MouseY >= USER_DATAGRAPH_Y1 && MouseY <= USER_DATAGRAPH_Y2) {
		*tag = ACTIVE_USER_DATAGRAPH;
		setcolor(MY_BLACK);
		setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
		rectangle(USER_DATAGRAPH_X1, USER_DATAGRAPH_Y1, USER_DATAGRAPH_X2, USER_DATAGRAPH_Y2);
	}
}


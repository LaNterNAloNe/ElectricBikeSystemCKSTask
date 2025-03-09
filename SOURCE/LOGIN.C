#include"LOGIN.H"

// 登录界面
void login(int *page, int *num) {
	
    char a[10] = {0}; // 初始化为空
    char b[10] = {0};
    int tag = 0;
    clrmous(MouseX, MouseY);
    save_bk_mou(MouseX, MouseY);
    drawgraph_login();

    while (1) {
		flushLoginGraph(&tag); // 刷新界面
		newmouse(&MouseX, &MouseY, &press); // 刷新鼠标

        // 处理鼠标点击事件
        if (mouse_press(USERNAME_X1, USERNAME_Y1, USERNAME_X2, USERNAME_Y2)==1) {
            Input_Vis(a, 220, 170, 13, WHITE);
        }

        if (mouse_press(PASSWORD_X1, PASSWORD_Y1, PASSWORD_X2, PASSWORD_Y2)==1) {
            Input_Invis(b, 220, 260, 13, WHITE);
        }

        if (mouse_press(LOGIN_X1, LOGIN_Y1, LOGIN_X2, LOGIN_Y2)==1) {
            // 检查输入是否非空且正确
            if (a[0] != '\0' && b[0] != '\0' && 
                strcmp(a, "123") == 0 && strcmp(b, "123") == 0) {
                *page = 0; // 跳转到主页
				puthz(300, 300, "哼哼哼哼",24,50,BLACK);
                break; // 退出循环
            }
        }
		if (mouse_press(REGISTER_X1,REGISTER_Y1,REGISTER_X2,REGISTER_Y2)==1) {
			exit(0);//仅做测试
        }
		if (mouse_press(ADMIN_X1,ADMIN_Y1,ADMIN_X2,ADMIN_Y2)==1) {
			*page = 2; // LOGIN_ADMIN : 2 跳转到管理员登录界面
			break;
		}
		if (mouse_press(EXITPROGRAM_X1,EXITPROGRAM_Y1,EXITPROGRAM_X2,EXITPROGRAM_Y2)==1) {
			*page=0; // EXIT : 0，退出程序
			break;
		}

        delay(30);
    } 
}

// 绘制登录界面
void drawgraph_login(void){
	
    setrgbpalette(0, 12,158,245);//浅蓝背景-1
	setrgbpalette(1, 235,235,235);//浅灰框-1
	setrgbpalette(2, 0, 0, 0);//黑色
	setrgbpalette(3, 240, 230,75);//黄色
	setrgbpalette(4, 255, 0, 0);//红色
	setrgbpalette(5, 255, 255, 255);//白色
	setfillstyle(1,0);
	setcolor(BLUE);
	bar(0,0,640,480);

	setlinestyle(0,0,3);//大框
	setfillstyle(1,WHITE);
	bar(120,120,520,390);

	setcolor(2);
	setlinestyle(0, 0, 3);
	setfillstyle(1,2);
	pieslice(160,175,0,360,10);//人头
	pieslice(160,205,0,180,20);
	pieslice(160,250,0,360,12);//钥匙

	bar(156,254,164,300);
	bar(164, 276, 170, 282);
	bar(163, 288,170, 294);
	setcolor(1);
	setlinestyle(0, 0, 3);
	setfillstyle(1, 1);
	//bar(220, 170, 480, 205);//用户名框
	line(USERNAME_X1, USERNAME_Y1, USERNAME_X2, USERNAME_Y1);
	line(USERNAME_X1, USERNAME_Y1, USERNAME_X1, USERNAME_Y2);
	line(USERNAME_X1, USERNAME_Y2, USERNAME_X2, USERNAME_Y2);
	line(USERNAME_X2, USERNAME_Y1, USERNAME_X2, USERNAME_Y2);
	//bar(220, 260, 480, 295);//密码框
	line(PASSWORD_X1, PASSWORD_Y1, PASSWORD_X2, PASSWORD_Y1);
	line(PASSWORD_X1, PASSWORD_Y1, PASSWORD_X1, PASSWORD_Y2);
	line(PASSWORD_X1, PASSWORD_Y2, PASSWORD_X2, PASSWORD_Y2);
	line(PASSWORD_X2, PASSWORD_Y1, PASSWORD_X2, PASSWORD_Y2);
	setcolor(4);
	setlinestyle(0, 0, 3);
	setfillstyle(1, 4);
	bar(230, 320, 330, 370);//分别为登录，注册
	bar(360, 320, 460, 370);

	setcolor(3);
	setlinestyle(0, 0, 3);
	setfillstyle(1, 3);
	bar(160, 330, 200, 360);//管理员模式
	puthz(220, 140, "用户名",24,50,BLACK);// 输出文本
	puthz(220, 230, "密码",24,50,BLACK);
	puthz(255, 330, "登录",24,30,WHITE);
	puthz(380, 330, "注册",24,30,WHITE);

	setcolor(4);
	setlinestyle(0, 0, 4);
	line(EXITPROGRAM_X1, EXITPROGRAM_Y1, EXITPROGRAM_X2, EXITPROGRAM_Y2);
	line(EXITPROGRAM_X2, EXITPROGRAM_Y1, EXITPROGRAM_X1, EXITPROGRAM_Y2);

	// setcolor(2); // 文本颜色为黑色
	// settextstyle(1, HORIZ_DIR, 3);// 设置文本大小
	// outtextxy(220,140, "Name");// 输出文本
	// outtextxy(220, 230, "Password");
	// setcolor(WHITE);
	// settextstyle(1, HORIZ_DIR, 2);
	// outtextxy(255, 330, "Log in");
	// outtextxy(380, 330, "Register");
}

void flushLoginGraph(int *tag){
	if ((MouseX >= USERNAME_X1 && MouseX <= USERNAME_X2 && MouseY >= USERNAME_Y1 && MouseY <= USERNAME_Y2) ||
		(MouseX >= PASSWORD_X1 && MouseX <= PASSWORD_X2 && MouseY >= PASSWORD_Y1 && MouseY <= PASSWORD_Y2)) 
		MouseS=2; // 假设设置为手形图标
	else if ((MouseX >= LOGIN_X1 && MouseX <= LOGIN_X2 && MouseY >= LOGIN_Y1 && MouseY <= LOGIN_Y2) ||
		(MouseX >= REGISTER_X1 && MouseX <= REGISTER_X2 && MouseY >= REGISTER_Y1 && MouseY <= REGISTER_Y2) ||
		(MouseX >= ADMIN_X1 && MouseX <= ADMIN_X2 && MouseY >= ADMIN_Y1 && MouseY <= ADMIN_Y2) ||
		(MouseX >= EXITPROGRAM_X1 && MouseX <= EXITPROGRAM_X2 && MouseY >= EXITPROGRAM_Y1 && MouseY <= EXITPROGRAM_Y2))
		MouseS=1; // 假设设置为手形图标
	else 
		MouseS=0; // 恢复默认箭头

	// 处理可交互窗口的鼠标移动事件 **显示激活状态**
	if (MouseX >= USERNAME_X1 && MouseX <= USERNAME_X2 && MouseY >= USERNAME_Y1 && MouseY <= USERNAME_Y2) {
		*tag=ACTIVE_USERNAME;
		setcolor(GREEN);
		setlinestyle(0, 0, 2);
		line(USERNAME_X1-2, USERNAME_Y1-2, USERNAME_X2+2, USERNAME_Y1-2);
		line(USERNAME_X1-2, USERNAME_Y1-2, USERNAME_X1-2, USERNAME_Y2+2);
		line(USERNAME_X1-2, USERNAME_Y2+2, USERNAME_X2+2, USERNAME_Y2+2);
		line(USERNAME_X2+2, USERNAME_Y1-2, USERNAME_X2+2, USERNAME_Y2+2);
	}
	else if (MouseX >= PASSWORD_X1 && MouseX <= PASSWORD_X2 && MouseY >= PASSWORD_Y1 && MouseY <= PASSWORD_Y2) {
		*tag=ACTIVE_PASSWORD;
		setcolor(GREEN);
		setlinestyle(0, 0, 2);
		line(PASSWORD_X1-2, PASSWORD_Y1-2, PASSWORD_X2+2, PASSWORD_Y1-2);
		line(PASSWORD_X1-2, PASSWORD_Y1-2, PASSWORD_X1-2, PASSWORD_Y2+2);
		line(PASSWORD_X1-2, PASSWORD_Y2+2, PASSWORD_X2+2, PASSWORD_Y2+2);
		line(PASSWORD_X2+2, PASSWORD_Y1-2, PASSWORD_X2+2, PASSWORD_Y2+2);
	}
	else if (MouseX >= LOGIN_X1 && MouseX <= LOGIN_X2 && MouseY >= LOGIN_Y1 && MouseY <= LOGIN_Y2) {
		*tag=ACTIVE_LOGIN;
		setcolor(GREEN);
		setlinestyle(0, 0, 2);
		line(LOGIN_X1-2, LOGIN_Y1-2, LOGIN_X2+2, LOGIN_Y1-2);
		line(LOGIN_X1-2, LOGIN_Y1-2, LOGIN_X1-2, LOGIN_Y2+2);
		line(LOGIN_X1-2, LOGIN_Y2+2, LOGIN_X2+2, LOGIN_Y2+2);
		line(LOGIN_X2+2, LOGIN_Y1-2, LOGIN_X2+2, LOGIN_Y2+2);
	}
	else if (MouseX >= REGISTER_X1 && MouseX <= REGISTER_X2 && MouseY >= REGISTER_Y1 && MouseY <= REGISTER_Y2) {
		*tag=ACTIVE_REGISTER;
		setcolor(GREEN);
		setlinestyle(0, 0, 2);
		line(REGISTER_X1-2, REGISTER_Y1-2, REGISTER_X2+2, REGISTER_Y1-2);
		line(REGISTER_X1-2, REGISTER_Y1-2, REGISTER_X1-2, REGISTER_Y2+2);
		line(REGISTER_X1-2, REGISTER_Y2+2, REGISTER_X2+2, REGISTER_Y2+2);
		line(REGISTER_X2+2, REGISTER_Y1-2, REGISTER_X2+2, REGISTER_Y2+2);
	}
	else if (MouseX >= ADMIN_X1 && MouseX <= ADMIN_X2 && MouseY >= ADMIN_Y1 && MouseY <= ADMIN_Y2) {
		*tag=ACTIVE_ADMIN;
		setcolor(GREEN);
		setlinestyle(0, 0, 2);
		line(ADMIN_X1-2, ADMIN_Y1-2, ADMIN_X2+2, ADMIN_Y1-2);
		line(ADMIN_X1-2, ADMIN_Y1-2, ADMIN_X1-2, ADMIN_Y2+2);
		line(ADMIN_X1-2, ADMIN_Y2+2, ADMIN_X2+2, ADMIN_Y2+2);
		line(ADMIN_X2+2, ADMIN_Y1-2, ADMIN_X2+2, ADMIN_Y2+2);
	}

	// 处理可交互窗口的鼠标移动事件 **取消激活状态**
	if ((MouseX < USERNAME_X1 || MouseX > USERNAME_X2 || MouseY < USERNAME_Y1 || MouseY > USERNAME_Y2) && (*tag==ACTIVE_USERNAME)) {
		*tag=ACTIVE_NONE;
		setcolor(WHITE);
		setlinestyle(0, 0, 2);
		line(USERNAME_X1-2, USERNAME_Y1-2, USERNAME_X2+2, USERNAME_Y1-2);
		line(USERNAME_X1-2, USERNAME_Y1-2, USERNAME_X1-2, USERNAME_Y2+2);
		line(USERNAME_X1-2, USERNAME_Y2+2, USERNAME_X2+2, USERNAME_Y2+2);
		line(USERNAME_X2+2, USERNAME_Y1-2, USERNAME_X2+2, USERNAME_Y2+2);
	}
	else if ((MouseX < PASSWORD_X1 || MouseX > PASSWORD_X2 || MouseY < PASSWORD_Y1 || MouseY > PASSWORD_Y2) && (*tag==ACTIVE_PASSWORD)) {
		*tag=ACTIVE_NONE;
		setcolor(WHITE);
		setlinestyle(0, 0, 2);
		line(PASSWORD_X1-2, PASSWORD_Y1-2, PASSWORD_X2+2, PASSWORD_Y1-2);
		line(PASSWORD_X1-2, PASSWORD_Y1-2, PASSWORD_X1-2, PASSWORD_Y2+2);
		line(PASSWORD_X1-2, PASSWORD_Y2+2, PASSWORD_X2+2, PASSWORD_Y2+2);
		line(PASSWORD_X2+2, PASSWORD_Y1-2, PASSWORD_X2+2, PASSWORD_Y2+2);
	}
	else if ((MouseX < LOGIN_X1 || MouseX > LOGIN_X2 || MouseY < LOGIN_Y1 || MouseY > LOGIN_Y2) && (*tag==ACTIVE_LOGIN)) {
		*tag=ACTIVE_NONE;
		setcolor(WHITE);
		setlinestyle(0, 0, 2);
		line(LOGIN_X1-2, LOGIN_Y1-2, LOGIN_X2+2, LOGIN_Y1-2);
		line(LOGIN_X1-2, LOGIN_Y1-2, LOGIN_X1-2, LOGIN_Y2+2);
		line(LOGIN_X1-2, LOGIN_Y2+2, LOGIN_X2+2, LOGIN_Y2+2);
		line(LOGIN_X2+2, LOGIN_Y1-2, LOGIN_X2+2, LOGIN_Y2+2);
	}
	else if ((MouseX < REGISTER_X1 || MouseX > REGISTER_X2 || MouseY < REGISTER_Y1 || MouseY > REGISTER_Y2) && (*tag==ACTIVE_REGISTER)) {
		*tag=ACTIVE_NONE;
		setcolor(WHITE);
		setlinestyle(0, 0, 2);
		line(REGISTER_X1-2, REGISTER_Y1-2, REGISTER_X2+2, REGISTER_Y1-2);
		line(REGISTER_X1-2, REGISTER_Y1-2, REGISTER_X1-2, REGISTER_Y2+2);
		line(REGISTER_X1-2, REGISTER_Y2+2, REGISTER_X2+2, REGISTER_Y2+2);
		line(REGISTER_X2+2, REGISTER_Y1-2, REGISTER_X2+2, REGISTER_Y2+2);
	}
	else if ((MouseX < ADMIN_X1 || MouseX > ADMIN_X2 || MouseY < ADMIN_Y1 || MouseY > ADMIN_Y2) && (*tag==ACTIVE_ADMIN)) {
		*tag=ACTIVE_NONE;
		setcolor(WHITE);
		setlinestyle(0, 0, 2);
		line(ADMIN_X1-2, ADMIN_Y1-2, ADMIN_X2+2, ADMIN_Y1-2);
		line(ADMIN_X1-2, ADMIN_Y1-2, ADMIN_X1-2, ADMIN_Y2+2);
		line(ADMIN_X1-2, ADMIN_Y2+2, ADMIN_X2+2, ADMIN_Y2+2);
		line(ADMIN_X2+2, ADMIN_Y1-2, ADMIN_X2+2, ADMIN_Y2+2);
	}
}
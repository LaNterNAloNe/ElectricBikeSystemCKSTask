#include"LOGIN.H"


// 登录界面
void login(int *page, unsigned long *ID) {

    
    char usrn[13] = {'\0'}; // 初始化为空
    char psw[13] = {'\0'};
    int tag = 0;

    *ID = 0; // 初始化用户ID

    clrmous(MouseX, MouseY);
    save_bk_mou(MouseX, MouseY);
    drawgraph_login();

	if(debug_mode == 1) display_memory_usage(400, 10); // 显示调试参数 
    while (1) {
		flushLoginGraph(&tag,page); // 刷新界面
		newmouse(&MouseX, &MouseY, &press); // 刷新鼠标

        // 处理鼠标点击事件
        if (mouse_press(USERNAME_X1, USERNAME_Y1, USERNAME_X2, USERNAME_Y2)==1) {
            Input_Bar(usrn, USERNAME_X1, USERNAME_Y1+5, 13, MY_WHITE,0,1);
        }

        if (mouse_press(PASSWORD_X1, PASSWORD_Y1, PASSWORD_X2, PASSWORD_Y2)==1) {
            Input_Bar(psw, PASSWORD_X1, PASSWORD_Y1+5, 13, MY_WHITE,0,0);
        }

        if (mouse_press(LOGIN_X1, LOGIN_Y1, LOGIN_X2, LOGIN_Y2)==1) {
            // 检查输入是否非空且正确
            if (usrn[0] != '\0' && psw[0] != '\0') {
				userlogin_judge(usrn,psw,ID);
				if(*ID != -1){
					anime_login_success();
					switchPage();
					*page = MAIN_USER; // MAIN_USER : 10 跳转到用户主界面
					Input_Bar(NULL, NULL, NULL, NULL, NULL,1,NULL);  // 清除输入框记忆
                	return; // 退出循环
				}
				else{
					anime_login_fail();
				}
            }else 
				anime_login_fail();
        }
		if (mouse_press(ADMIN_X1,ADMIN_Y1,ADMIN_X2,ADMIN_Y2)==1) {
			clrmous(MouseX, MouseY);
			switchPage();
			*page = LOGIN_ADMIN; // LOGIN_ADMIN : 2 跳转到管理员登录界面
			Input_Bar(NULL, NULL, NULL, NULL, NULL,1,NULL);
			return;
		}
		else if (mouse_press(REGISTER_X1,REGISTER_Y1,REGISTER_X2,REGISTER_Y2)==1) {
			clrmous(MouseX, MouseY);
			switchPage();
            *page = REGISTER_ID_INPUT; // REGISTER_ID_INPUT : 4 跳转到注册界面，先输入ID
            Input_Bar(NULL, NULL, NULL, NULL, NULL,1,NULL);
			return;
        }
		else if (mouse_press(EXITPROGRAM_X1,EXITPROGRAM_Y1,EXITPROGRAM_X2,EXITPROGRAM_Y2)==1) {
			clrmous(MouseX, MouseY);
			switchPage();
			*page = EXIT; // EXIT : 0，退出程序
			return;
		}

        delay(25); // 50hz刷新率
	
    } 
}

// 绘制登录界面
void drawgraph_login(void){
	setfillstyle(1,0);
	setcolor(MY_LIGHTBLUE);
	bar(0,0,640,480);

	setlinestyle(SOLID_LINE,0,THICK_WIDTH);//大框
	setfillstyle(SOLID_FILL,MY_WHITE);
	bar(120,120,520,390);

	setcolor(MY_BLACK);
	setlinestyle(0, 0, 3);
	setfillstyle(SOLID_FILL,MY_BLACK);
	pieslice(160,175,0,360,10);//人头
	pieslice(160,205,0,180,20);
	pieslice(160,250,0,360,12);//钥匙
	bar(156,254,164,300);
	bar(164, 276, 170, 282);
	bar(163, 288,170, 294);

	setcolor(MY_LIGHTGRAY);//用户名框和密码框
	setlinestyle(0, 0, THICK_WIDTH);
	line(USERNAME_X1, USERNAME_Y1, USERNAME_X2, USERNAME_Y1);
	line(USERNAME_X1, USERNAME_Y1, USERNAME_X1, USERNAME_Y2);
	line(USERNAME_X1, USERNAME_Y2, USERNAME_X2, USERNAME_Y2);
	line(USERNAME_X2, USERNAME_Y1, USERNAME_X2, USERNAME_Y2);
	line(PASSWORD_X1, PASSWORD_Y1, PASSWORD_X2, PASSWORD_Y1);
	line(PASSWORD_X1, PASSWORD_Y1, PASSWORD_X1, PASSWORD_Y2);
	line(PASSWORD_X1, PASSWORD_Y2, PASSWORD_X2, PASSWORD_Y2);
	line(PASSWORD_X2, PASSWORD_Y1, PASSWORD_X2, PASSWORD_Y2);
	setcolor(4);
	setlinestyle(0, 0, THICK_WIDTH);
	setfillstyle(1, 4);
	bar(230, 320, 330, 370);//分别为登录，注册
	bar(360, 320, 460, 370);

	setcolor(3);
	setlinestyle(0, 0, THICK_WIDTH);
	setfillstyle(1, 3);
	bar(ADMIN_X1, ADMIN_Y1, ADMIN_X2, ADMIN_Y2);//管理员模式

	puthz(94, 50, "校园电动车管理系统",48,50,MY_WHITE);// 输出文本
	puthz(220, 140, "用户名",24,50,MY_BLACK);// 输出文本
	puthz(220, 230, "密码",24,50,MY_BLACK);
	puthz(LOGIN_X1+24, LOGIN_Y1+12, "登录",24,30,MY_WHITE);
	puthz(REGISTER_X1+24, REGISTER_Y1+12, "注册",24,30,MY_WHITE);
	puthz(ADMIN_X1+2, ADMIN_Y1+2, "管理员模式",16,15,MY_WHITE);

	setcolor(4);
	setlinestyle(0, 0, NORM_WIDTH);
	line(EXITPROGRAM_X1, EXITPROGRAM_Y1, EXITPROGRAM_X2, EXITPROGRAM_Y2);
	line(EXITPROGRAM_X2, EXITPROGRAM_Y1, EXITPROGRAM_X1, EXITPROGRAM_Y2);
}

//管理员登录界面
void login_admin(int* page,unsigned long *ID) {
    char usrn[10] = {'\0'}; // 初始化为空
    char psw[10] = {'\0'};
    int tag = 0;

    *ID = 0; // 初始化用户ID

    clrmous(MouseX, MouseY);
	save_bk_mou(MouseX, MouseY);
	drawgraph_admin_login();

	if(debug_mode == 1) display_memory_usage(400, 10); // 显示调试参数 

	while (1) {
		flushLoginGraph(&tag,page); // 刷新界面
        newmouse(&MouseX, &MouseY, &press); // 刷新鼠标

		// 处理鼠标点击事件
		if (mouse_press(USERNAME_X1, USERNAME_Y1, USERNAME_X2, USERNAME_Y2) == 1) {
			Input_Bar(usrn, USERNAME_X1, USERNAME_Y1 + 5, 13, MY_WHITE,0,1);
		}

		if (mouse_press(PASSWORD_X1, PASSWORD_Y1, PASSWORD_X2, PASSWORD_Y2) == 1) {
			Input_Bar(psw, PASSWORD_X1, PASSWORD_Y1 + 5, 13, MY_WHITE,0,0);
		}

		if (mouse_press(ADMIN_LOGIN_X1, ADMIN_LOGIN_Y1, ADMIN_LOGIN_X2, ADMIN_LOGIN_Y2) == 1) {
			// 检查输入是否非空且正确
			if (usrn[0] != '\0' && psw[0] != '\0'){
                adminlogin_judge(usrn, psw, ID);
                if (*ID != -1)
                {
                    anime_admin_login_success();
					switchPage();
					*page = MAIN_ADMIN; // MAIN_USER : 10 跳转到用户主界面
					Input_Bar(NULL, NULL, NULL, NULL, NULL,1,NULL);  // 清除输入框记忆
                	return; // 退出循环
                }
                else{
					anime_admin_login_fail();
				}
			}else 
			anime_admin_login_fail();
		}
		if (mouse_press(ADMIN_X1, ADMIN_Y1, ADMIN_X2, ADMIN_Y2) == 1) {
			clrmous(MouseX, MouseY);
			switchPage();
			*page = LOGIN; // LOGIN_ADMIN : 2 跳转到用户登录界面
			Input_Bar(NULL, NULL, NULL, NULL, NULL,1,NULL);
			//fclose(fp_LOGIN_ADMIN_read);
			return;
		}
		else if (mouse_press(EXITPROGRAM_X1, EXITPROGRAM_Y1, EXITPROGRAM_X2, EXITPROGRAM_Y2) == 1) {
			clrmous(MouseX, MouseY);
			switchPage();
			*page = EXIT; // EXIT : 0，退出程序
			//fclose(fp_LOGIN_ADMIN_read);
			return;
		}

		delay(25); // 50hz刷新率

	}
}
	
//绘制管理员登录界面
void drawgraph_admin_login(){
	setfillstyle(1, 0);
	setcolor(MY_LIGHTBLUE);
	bar(0, 0, 640, 480);

	//管理员模式边框
	setfillstyle(1, MY_BLACK);
	setcolor(MY_BLACK);
	bar(115, 110, 525, 430);
	puthz(255, 400, "管理员模式", 24, 30, MY_WHITE);
	
	setlinestyle(SOLID_LINE, 0, THICK_WIDTH);//大框
	setfillstyle(SOLID_FILL, MY_WHITE);
	bar(120, 120, 520, 390);

	setcolor(MY_BLACK);
	setlinestyle(0, 0, 3);
	setfillstyle(SOLID_FILL, MY_BLACK);
	pieslice(160, 175, 0, 360, 10);//人头
	pieslice(160, 205, 0, 180, 20);
	pieslice(160, 250, 0, 360, 12);//钥匙
	bar(156, 254, 164, 300);
	bar(164, 276, 170, 282);
	bar(163, 288, 170, 294);

	setcolor(MY_LIGHTGRAY);//用户名框和密码框
	setlinestyle(0, 0, THICK_WIDTH);
	line(USERNAME_X1, USERNAME_Y1, USERNAME_X2, USERNAME_Y1);
	line(USERNAME_X1, USERNAME_Y1, USERNAME_X1, USERNAME_Y2);
	line(USERNAME_X1, USERNAME_Y2, USERNAME_X2, USERNAME_Y2);
	line(USERNAME_X2, USERNAME_Y1, USERNAME_X2, USERNAME_Y2);
	line(PASSWORD_X1, PASSWORD_Y1, PASSWORD_X2, PASSWORD_Y1);
	line(PASSWORD_X1, PASSWORD_Y1, PASSWORD_X1, PASSWORD_Y2);
	line(PASSWORD_X1, PASSWORD_Y2, PASSWORD_X2, PASSWORD_Y2);
	line(PASSWORD_X2, PASSWORD_Y1, PASSWORD_X2, PASSWORD_Y2);
	setcolor(4);
	setlinestyle(0, 0, THICK_WIDTH);
	setfillstyle(1, 4);
	bar(ADMIN_LOGIN_X1, ADMIN_LOGIN_Y1,ADMIN_LOGIN_X2, ADMIN_LOGIN_Y2);//登录按钮

	setcolor(3);
	setlinestyle(0, 0, THICK_WIDTH);
	setfillstyle(1, 3);
	bar(ADMIN_X1, ADMIN_Y1, ADMIN_X2, ADMIN_Y2);//管理员模式

	puthz(94, 50, "校园电动车管理系统", 48, 50, MY_WHITE);// 输出文本
	puthz(220, 140, "用户名", 24, 50, MY_BLACK);// 输出文本
	puthz(220, 230, "密码", 24, 50, MY_BLACK);
	puthz(ADMIN_LOGIN_X1+24, ADMIN_LOGIN_Y1+12, "登录",24,30,MY_WHITE);
	puthz(ADMIN_X1 + 5, ADMIN_Y1 + 2, "用户模式", 16, 15, MY_WHITE);
	setcolor(4);
	setlinestyle(0, 0, NORM_WIDTH);
	line(EXITPROGRAM_X1, EXITPROGRAM_Y1, EXITPROGRAM_X2, EXITPROGRAM_Y2);
	line(EXITPROGRAM_X2, EXITPROGRAM_Y1, EXITPROGRAM_X1, EXITPROGRAM_Y2);
}

void register_id_input(int* page, unsigned long* ID) {
	char id_input[10]; // 用于存储输入的ID
	unsigned long id=0; // 用于存储检测通过的ID
	int id_flag = -1; // 标明输入的ID是否合法
	int tag=ACTIVE_NONE; // 用于记录鼠标点击状态;

    *ID = 0; // 初始化用户ID

    clrmous(MouseX, MouseY);
	save_bk_mou(MouseX, MouseY);
	drawgraph_register_id_input();
	while (1) {
		flushRegisterIdGraph(&tag);
		newmouse(&MouseX, &MouseY, &press); // 刷新鼠标

		if (mouse_press(PASSWORD_X1, PASSWORD_Y1, PASSWORD_X2, PASSWORD_Y2) == 1) {
			Input_Bar(id_input, PASSWORD_X1, PASSWORD_Y1 + 5, 9, MY_WHITE, 0, 1);
		}
		if (mouse_press(LOGIN_X1, LOGIN_Y1, LOGIN_X2, LOGIN_Y2) == 1) {
			id = atol(id_input);
            id_flag = register_id_judge(id);

            switch (id_flag) {
                case 0: // 转换成功，学号格式正确，未被注册
                    *ID = id;
                    clrmous(MouseX, MouseY);
                    *page = REGISTER; // REGISTER : 3，进入正常注册功能
					anime_id_input_success();
					Input_Bar(NULL, NULL, NULL, NULL, NULL, INPUTBAR_CLEAR, NULL);
					switchPage();
                    return;
                case 1: // 转换失败，学号格式错误
                    setcolor(MY_RED);
                    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
                    rectangle(PASSWORD_X1 + 2, PASSWORD_Y1 + 2, PASSWORD_X2 - 2, PASSWORD_Y2 - 2);
                    setcolor(MY_WHITE);
                    setfillstyle(SOLID_FILL, MY_WHITE);
                    bar(330, 210, 500, 250);
                    puthz(220, 230, "学号格式错误", 24, 30, MY_RED);
                    break;
                case 2: // 学号重复
                    setcolor(MY_RED);
                    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
                    rectangle(PASSWORD_X1 + 2, PASSWORD_Y1 + 2, PASSWORD_X2 - 2, PASSWORD_Y2 - 2);
                    setcolor(MY_WHITE);
                    setfillstyle(SOLID_FILL, MY_WHITE);
                    bar(330, 210, 500, 250);
                    puthz(340, 230, "学号已被注册", 24, 30, MY_RED);
                    break;
			}
		}
		else if (mouse_press(REGISTER_X1, REGISTER_Y1, REGISTER_X2, REGISTER_Y2) == 1) {
			clrmous(MouseX, MouseY);
			switchPage();
			*page = LOGIN; 
			Input_Bar(NULL, NULL, NULL, NULL, NULL, INPUTBAR_CLEAR, NULL);
			return;
		}
		else if (mouse_press(EXITPROGRAM_X1, EXITPROGRAM_Y1, EXITPROGRAM_X2, EXITPROGRAM_Y2) == 1) {
			clrmous(MouseX, MouseY);
			switchPage();
			*page = EXIT; // EXIT : 0，退出程序
			return;
		}

		delay(25); // 50hz刷新率
	}
}

int register_id_judge(unsigned long id) {
	int i = 0;
	int account_counts;
	USER_LOGIN_DATA TEMP;
	FILE* fp_LOGIN_USER_readndwrite = fopen("C:\\EBS\\DATA\\USER.DAT", "rb");

    if (fp_LOGIN_USER_readndwrite == NULL) {
		fclose(fp_LOGIN_USER_readndwrite);
		exit(0);
	}

	if (id <= 0 ||id<100000000||id>999999999) {
		if (fclose(fp_LOGIN_USER_readndwrite) != 0) getch(), exit(0);
		return 1;//转换失败，学号格式错误
	}

    fseek(fp_LOGIN_USER_readndwrite, 0, SEEK_END);
	account_counts = ftell(fp_LOGIN_USER_readndwrite) / sizeof(USER_LOGIN_DATA);//初始操作完成，接下来开始遍历数据

    for (i = 0; i < account_counts; i++) {
		fseek(fp_LOGIN_USER_readndwrite, i * sizeof(USER_LOGIN_DATA), SEEK_SET);
		fread(&TEMP, sizeof(USER_LOGIN_DATA), 1, fp_LOGIN_USER_readndwrite); //逐个读取，每个用户信息，直到用户名与密码均匹配
		if (TEMP.ID==id) {
            if (fclose(fp_LOGIN_USER_readndwrite) != 0) getch(), exit(0);
            return 2;//学号重复
		}

	}
    // 为什么要写入信息？在输入账密后还有一次写入信息，且当时也把ID正确赋值了，没必要在这写啊，会出问题的 -- LaNterN
	if (fclose(fp_LOGIN_USER_readndwrite) != 0) getch(), exit(0);

    return 0;
}

void drawgraph_register_id_input() {
	setfillstyle(1, 0);
	setcolor(MY_LIGHTBLUE);
	bar(0, 0, 640, 480);
	setlinestyle(SOLID_LINE, 0, THICK_WIDTH);//大框
	setfillstyle(SOLID_FILL, MY_WHITE);
	bar(120, 120, 520, 390);
	setcolor(MY_BLACK);
	setfillstyle(SOLID_FILL, MY_BLACK);
	bar(121, 169, 519, 171);

	setcolor(MY_LIGHTGRAY);//输入框
	setlinestyle(0, 0, THICK_WIDTH);
	line(PASSWORD_X1, PASSWORD_Y1, PASSWORD_X2, PASSWORD_Y1);
	line(PASSWORD_X1, PASSWORD_Y1, PASSWORD_X1, PASSWORD_Y2);
	line(PASSWORD_X1, PASSWORD_Y2, PASSWORD_X2, PASSWORD_Y2);
	line(PASSWORD_X2, PASSWORD_Y1, PASSWORD_X2, PASSWORD_Y2);
	setcolor(4);
	setlinestyle(0, 0, THICK_WIDTH);
	setfillstyle(1, 4);
	bar(230, 320, 330, 370);//分别为登录，注册
	bar(360, 320, 460, 370);
	puthz(94, 50, "校园电动车管理系统", 48, 50, MY_WHITE);
	puthz(240, 135, "身份认证", 32, 45, MY_BLACK);
	puthz(140, 258, "学号", 24, 30, MY_BLACK);
	puthz(LOGIN_X1 + 24, LOGIN_Y1 + 12, "确认", 24, 30, MY_WHITE);
	puthz(REGISTER_X1 + 24, REGISTER_Y1 + 12, "返回", 24, 30, MY_WHITE);
	
	setcolor(4);
	setlinestyle(0, 0, NORM_WIDTH);
	line(EXITPROGRAM_X1, EXITPROGRAM_Y1, EXITPROGRAM_X2, EXITPROGRAM_Y2);
	line(EXITPROGRAM_X2, EXITPROGRAM_Y1, EXITPROGRAM_X1, EXITPROGRAM_Y2);
}

void flushRegisterIdGraph(int* tag) {
	if (MouseX >= PASSWORD_X1 && MouseX <= PASSWORD_X2 && MouseY >= PASSWORD_Y1 && MouseY <= PASSWORD_Y2)
		MouseS = 2; // 假设设置为手形图标
	else if ((MouseX >= LOGIN_X1 && MouseX <= LOGIN_X2 && MouseY >= LOGIN_Y1 && MouseY <= LOGIN_Y2 ) ||
		(MouseX >= REGISTER_X1 && MouseX <= REGISTER_X2 && MouseY >= REGISTER_Y1 && MouseY <= REGISTER_Y2 ) ||
		(MouseX >= EXITPROGRAM_X1 && MouseX <= EXITPROGRAM_X2 && MouseY >= EXITPROGRAM_Y1 && MouseY <= EXITPROGRAM_Y2))
		MouseS = 1; // 假设设置为手形图标
	else
		MouseS = 0; // 恢复默认箭头

	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	// 处理可交互窗口的鼠标移动事件 **显示激活状态**
	
	if (MouseX >= PASSWORD_X1 && MouseX <= PASSWORD_X2 && MouseY >= PASSWORD_Y1 && MouseY <= PASSWORD_Y2) {
		*tag = ACTIVE_PASSWORD;
		setcolor(GREEN);
		rectangle(PASSWORD_X1 - 2, PASSWORD_Y1 - 2, PASSWORD_X2 + 2, PASSWORD_Y2 + 2);
	}
	else if (MouseX >= LOGIN_X1 && MouseX <= LOGIN_X2 && MouseY >= LOGIN_Y1 && MouseY <= LOGIN_Y2) {
		*tag = ACTIVE_LOGIN;
		setcolor(GREEN);
		rectangle(LOGIN_X1 - 2, LOGIN_Y1 - 2, LOGIN_X2 + 2, LOGIN_Y2 + 2);
	}
	else if (MouseX >= REGISTER_X1 && MouseX <= REGISTER_X2 && MouseY >= REGISTER_Y1 && MouseY <= REGISTER_Y2) {
		*tag = ACTIVE_REGISTER;
		setcolor(GREEN);
		rectangle(REGISTER_X1 - 2, REGISTER_Y1 - 2, REGISTER_X2 + 2, REGISTER_Y2 + 2);
	}
	else if ((MouseX >= EXITPROGRAM_X1 && MouseX <= EXITPROGRAM_X2 && MouseY >= EXITPROGRAM_Y1 && MouseY <= EXITPROGRAM_Y2) && *tag == ACTIVE_NONE) {
		*tag = EXIT_PROGRAM;
		setcolor(RED);
		setlinestyle(0, 0, THICK_WIDTH);
		line(EXITPROGRAM_X1, EXITPROGRAM_Y1, EXITPROGRAM_X2, EXITPROGRAM_Y2);
		line(EXITPROGRAM_X2, EXITPROGRAM_Y1, EXITPROGRAM_X1, EXITPROGRAM_Y2); // 使叉变粗

		setcolor(BLACK);
		setlinestyle(0, 0, 2);
		line(EXITPROGRAM_X2 + 20, EXITPROGRAM_Y1, EXITPROGRAM_X2 + 100, EXITPROGRAM_Y1);
		line(EXITPROGRAM_X2 + 20, EXITPROGRAM_Y1, EXITPROGRAM_X2 + 20, EXITPROGRAM_Y1 + 40);
		line(EXITPROGRAM_X2 + 20, EXITPROGRAM_Y1 + 40, EXITPROGRAM_X2 + 100, EXITPROGRAM_Y1 + 40);
		line(EXITPROGRAM_X2 + 100, EXITPROGRAM_Y1, EXITPROGRAM_X2 + 100, EXITPROGRAM_Y1 + 40);
		setfillstyle(SOLID_FILL, BLUE);
		bar(EXITPROGRAM_X2 + 20, EXITPROGRAM_Y1, EXITPROGRAM_X2 + 120, EXITPROGRAM_Y2);
		puthz(EXITPROGRAM_X2 + 20, EXITPROGRAM_Y1 + 8, "退出程序", 24, 25, WHITE); // 输出提示文本和背景
	}

	//***  处理可交互窗口的鼠标移动事件 **取消激活状态**  ***//
	if ((MouseX < PASSWORD_X1 || MouseX > PASSWORD_X2 || MouseY < PASSWORD_Y1 || MouseY > PASSWORD_Y2) && (*tag == ACTIVE_PASSWORD)) {
		*tag = ACTIVE_NONE;
		setcolor(WHITE);
		rectangle(PASSWORD_X1 - 2, PASSWORD_Y1 - 2, PASSWORD_X2 + 2, PASSWORD_Y2 + 2);
	}
	//登录预注册的两个红色按钮共用一个else if语句
	else if ((MouseX < LOGIN_X1 || MouseX > LOGIN_X2 || MouseY < LOGIN_Y1 || MouseY > LOGIN_Y2)
		&& (*tag == ACTIVE_LOGIN)) {
		*tag = ACTIVE_NONE;
		setcolor(WHITE);
		rectangle(LOGIN_X1 - 2, LOGIN_Y1 - 2, LOGIN_X2 + 2, LOGIN_Y2 + 2);
	}
	else if ((MouseX < REGISTER_X1 || MouseX > REGISTER_X2 || MouseY < REGISTER_Y1 || MouseY > REGISTER_Y2)
		&& *tag == ACTIVE_REGISTER) {
		*tag = ACTIVE_NONE;
		setcolor(WHITE);
		rectangle(REGISTER_X1 - 2, REGISTER_Y1 - 2, REGISTER_X2 + 2, REGISTER_Y2 + 2);
	}
	else if ((MouseX < EXITPROGRAM_X1 || MouseX > EXITPROGRAM_X2 || MouseY < EXITPROGRAM_Y1 || MouseY > EXITPROGRAM_Y2) && (*tag == EXIT_PROGRAM)) {
		*tag = ACTIVE_NONE;
		setfillstyle(SOLID_FILL, 0);
		bar(EXITPROGRAM_X1, EXITPROGRAM_Y1, EXITPROGRAM_X2, EXITPROGRAM_Y2); // 清理叉

		setcolor(RED);
		setlinestyle(0, 0, NORM_WIDTH);
		line(EXITPROGRAM_X1, EXITPROGRAM_Y1, EXITPROGRAM_X2, EXITPROGRAM_Y2);
		line(EXITPROGRAM_X2, EXITPROGRAM_Y1, EXITPROGRAM_X1, EXITPROGRAM_Y2); // 重新画叉

		setfillstyle(SOLID_FILL, 0);
		bar(EXITPROGRAM_X2 + 20, EXITPROGRAM_Y1, EXITPROGRAM_X2 + 120, EXITPROGRAM_Y2); // 清理提示文本
	}

}



// 注册界面
void _register(int* page,unsigned long *ID) {
    char usrn[10] = {'\0'}; // 初始化为空
    char psw[10] = {'\0'};
	char time_string[10] = { '\0' };
	unsigned long time=0;//系统时间
    int tag = 0;
	int is_register_invalid=0;

    // 成功进入注册界面后，以记录第一层界面的ID，此时无需清理ID

	clrmous(MouseX, MouseY);
	save_bk_mou(MouseX, MouseY);
	drawgraph_register();

	if(debug_mode == 1) display_memory_usage(400, 10); // 显示调试参数 
	
	while (1) {
		flushLoginGraph(&tag,page); // 刷新界面
		newmouse(&MouseX, &MouseY, &press); // 刷新鼠标

		// 处理鼠标点击事件
		if (mouse_press(USERNAME_X1, USERNAME_Y1, USERNAME_X2, USERNAME_Y2) == 1) {
			Input_Bar(usrn, USERNAME_X1, USERNAME_Y1 + 5, 13, MY_WHITE,0,1);
		}

		if (mouse_press(PASSWORD_X1, PASSWORD_Y1, PASSWORD_X2, PASSWORD_Y2) == 1) {
			Input_Bar(psw, PASSWORD_X1, PASSWORD_Y1 + 5, 13, MY_WHITE,0,0);
		}

		if (mouse_press(LOGIN_X1, LOGIN_Y1, LOGIN_X2, LOGIN_Y2) == 1) {
			// 检查输入是否非空且正确
			if (usrn[0] != '\0' && psw[0] != '\0'){
				time=get_approx_time(time_string); // 获取系统时间
				is_register_invalid = userregister_judge(usrn,psw,ID,time);
				if(!is_register_invalid){
					anime_register_success();
					*page = LOGIN;
					*ID = -1;
					Input_Bar(NULL, NULL, NULL, NULL, NULL,1,NULL);  // 清除输入框记忆
					return;
				}
				if(is_register_invalid){
					anime_register_fail(1); //1意味是因为用户名已被注册而无法再利用此用户名注册
				}
			}else if(usrn[0] == '\0' && psw[0] != '\0'){
				anime_register_fail(2);
			}else if(usrn[0] != '\0' && psw[0] == '\0'){
				anime_register_fail(3);
			}else if(usrn[0] == '\0' && psw[0] == '\0'){
				anime_register_fail(4);
			}
		}
		else if (mouse_press(REGISTER_X1, REGISTER_Y1, REGISTER_X2, REGISTER_Y2) == 1) {
			clrmous(MouseX, MouseY);
			switchPage();
			*page = LOGIN; //此时这个键是“返回登录”，跳转到登录界面
			*ID = -1;
			Input_Bar(NULL, NULL, NULL, NULL, NULL,1,NULL);
			return;
		}
		else if (mouse_press(EXITPROGRAM_X1, EXITPROGRAM_Y1, EXITPROGRAM_X2, EXITPROGRAM_Y2) == 1) {
			clrmous(MouseX, MouseY);
			switchPage();
			*page = EXIT; // EXIT : 0，退出程序
			return;
		}

		delay(25); // 50hz刷新率

	}
}
		

//绘制注册界面
void drawgraph_register() {
	setfillstyle(1, 0);
	setcolor(MY_LIGHTBLUE);
	bar(0, 0, 640, 480);

	setlinestyle(SOLID_LINE, 0, THICK_WIDTH);//大框
	setfillstyle(SOLID_FILL, MY_WHITE);
	bar(120, 120, 520, 390);

	setcolor(MY_BLACK);
	setlinestyle(0, 0, 3);
	setfillstyle(SOLID_FILL, MY_BLACK);
	pieslice(160, 175, 0, 360, 10);//人头
	pieslice(160, 205, 0, 180, 20);
	pieslice(160, 250, 0, 360, 12);//钥匙
	bar(156, 254, 164, 300);
	bar(164, 276, 170, 282);
	bar(163, 288, 170, 294);

	setcolor(MY_LIGHTGRAY);//用户名框和密码框
	setlinestyle(0, 0, THICK_WIDTH);
	line(USERNAME_X1, USERNAME_Y1, USERNAME_X2, USERNAME_Y1);
	line(USERNAME_X1, USERNAME_Y1, USERNAME_X1, USERNAME_Y2);
	line(USERNAME_X1, USERNAME_Y2, USERNAME_X2, USERNAME_Y2);
	line(USERNAME_X2, USERNAME_Y1, USERNAME_X2, USERNAME_Y2);
	line(PASSWORD_X1, PASSWORD_Y1, PASSWORD_X2, PASSWORD_Y1);
	line(PASSWORD_X1, PASSWORD_Y1, PASSWORD_X1, PASSWORD_Y2);
	line(PASSWORD_X1, PASSWORD_Y2, PASSWORD_X2, PASSWORD_Y2);
	line(PASSWORD_X2, PASSWORD_Y1, PASSWORD_X2, PASSWORD_Y2);
	setcolor(4);
	setlinestyle(0, 0, THICK_WIDTH);
	setfillstyle(1, 4);
	bar(230, 320, 330, 370);//分别为注册,返回登录
	bar(360, 320, 460, 370);

	puthz(94, 50, "校园电动车管理系统", 48, 50, MY_WHITE);// 输出文本
	puthz(220, 140, "输入用户名", 24, 20, MY_BLACK);// 输出文本
	puthz(220, 230, "输入密码", 24, 20, MY_BLACK);
	puthz(LOGIN_X1+8, LOGIN_Y1+12, "确认注册", 24, 20, MY_WHITE);
	puthz(REGISTER_X1+8, REGISTER_Y1+12, "返回登录", 24, 20, MY_WHITE);
	setcolor(4);
	setlinestyle(0, 0, NORM_WIDTH);
	line(EXITPROGRAM_X1, EXITPROGRAM_Y1, EXITPROGRAM_X2, EXITPROGRAM_Y2);
	line(EXITPROGRAM_X2, EXITPROGRAM_Y1, EXITPROGRAM_X1, EXITPROGRAM_Y2);
}

//用户登录检测
void userlogin_judge(char *usrn,char *psw,unsigned long *ID){
	int i=0;
	int account_counts;
	USER_LOGIN_DATA *TEMP;
	FILE *fp_LOGIN_USER_read = fopen("C:\\EBS\\DATA\\USER.DAT","rb");

	if (fp_LOGIN_USER_read == NULL) {
        fclose(fp_LOGIN_USER_read);
        exit(0);
    }
	
	fseek(fp_LOGIN_USER_read,0,SEEK_END);
	account_counts = ftell(fp_LOGIN_USER_read)/sizeof(USER_LOGIN_DATA);//初始操作完成，接下来开始遍历数据

	for(i=0;i<account_counts;i++){
		fseek(fp_LOGIN_USER_read,i*sizeof(USER_LOGIN_DATA),SEEK_SET);
		fread(TEMP,sizeof(USER_LOGIN_DATA),1,fp_LOGIN_USER_read); //逐个读取，每个用户信息，直到用户名与密码均匹配

		if(strcmp(usrn,TEMP->usrn) == 0){
			if(strcmp(psw,TEMP->psw) == 0){
				//登陆成功
				*ID = TEMP->ID;
				if(fclose(fp_LOGIN_USER_read)!=0) getch(),exit(0);
				return;
			}
		}
		
	}
	//若完成for循环仍未经过return函数，则说明账号不存在或账号存在，密码错误
	if(fclose(fp_LOGIN_USER_read)!=0) getch(),exit(0);
	return;
}

//管理员登录检测
void adminlogin_judge(char *usrn,char *psw,unsigned long *id){
	int i=0;
	int account_counts;
	ADMIN_LOGIN_DATA *TEMP;
	FILE *fp_LOGIN_ADMIN_read = fopen("C:\\EBS\\DATA\\ADMIN.DAT","rb");

	if (fp_LOGIN_ADMIN_read == NULL) {
        fclose(fp_LOGIN_ADMIN_read);
        exit(0);
    }

	fseek(fp_LOGIN_ADMIN_read,0,SEEK_END);
	account_counts = ftell(fp_LOGIN_ADMIN_read)/sizeof(ADMIN_LOGIN_DATA);//初始操作完成，接下来开始遍历数据

	for(i=0;i<account_counts;i++){
		fseek(fp_LOGIN_ADMIN_read,i*sizeof(ADMIN_LOGIN_DATA),SEEK_SET);
		fread(TEMP,sizeof(ADMIN_LOGIN_DATA),1,fp_LOGIN_ADMIN_read); //逐个读取，每个用户信息，直到用户名与密码均匹配

		if(strcmp(usrn,TEMP->usrn) == 0){
			if(strcmp(psw,TEMP->psw) == 0){
				//登陆成功
				*id = TEMP->uid;
				if(fclose(fp_LOGIN_ADMIN_read)!=0) getch(),exit(0);
				return;
			}
		}
		
	}

	if(fclose(fp_LOGIN_ADMIN_read)!=0) getch(),exit(0);
	return;
}

//用户注册检测
int userregister_judge(char *usrn,char *psw,unsigned long *ID,unsigned long time){
	int i=0;
	int account_counts;
	USER_LOGIN_DATA TEMP;
	FILE *fp_LOGIN_USER_readndwrite = fopen("C:\\EBS\\DATA\\USER.DAT","rb+");
	
	if (fp_LOGIN_USER_readndwrite == NULL) {
        // fclose(fp_LOGIN_USER_readndwrite);
        getch();
        exit(0);
    }

	fseek(fp_LOGIN_USER_readndwrite,0,SEEK_END);
	account_counts = ftell(fp_LOGIN_USER_readndwrite)/sizeof(USER_LOGIN_DATA);//初始操作完成，接下来开始遍历数据

	for(i=0;i<account_counts;i++){
		fseek(fp_LOGIN_USER_readndwrite,i*sizeof(USER_LOGIN_DATA),SEEK_SET);
		fread(&TEMP,sizeof(USER_LOGIN_DATA),1,fp_LOGIN_USER_readndwrite); //逐个读取，每个用户信息

		if(strcmp(usrn,TEMP.usrn) == 0){
			if(fclose(fp_LOGIN_USER_readndwrite)!=0) {
                getch();
                exit(1); // 发现存在用户名相同的，则注册失败
            }
            
			return 1;
		}
	}

	//若经过了for循环仍未经过return，则代表用户名未曾注册过，可以注册
	strcpy(TEMP.usrn,usrn);			//获取账密和uid
	strcpy(TEMP.psw,psw);
	TEMP.ID = *ID;
	TEMP.state = ACTIVE;
	TEMP.register_time = time;
    fseek(fp_LOGIN_USER_readndwrite,0,SEEK_END); // 定位到文件末尾
	fwrite(&TEMP,sizeof(USER_LOGIN_DATA),1,fp_LOGIN_USER_readndwrite);  //将注册信息写入文件
	if(fclose(fp_LOGIN_USER_readndwrite)!=0) getch(),exit(1);
	return 0;
}
 


/*
时刻刷新画面
*/
void flushLoginGraph(int *tag,int *page){
	if ((MouseX >= USERNAME_X1 && MouseX <= USERNAME_X2 && MouseY >= USERNAME_Y1 && MouseY <= USERNAME_Y2) ||
		(MouseX >= PASSWORD_X1 && MouseX <= PASSWORD_X2 && MouseY >= PASSWORD_Y1 && MouseY <= PASSWORD_Y2)) 
		MouseS=2; // 假设设置为手形图标
	else if ((MouseX >= LOGIN_X1 && MouseX <= LOGIN_X2 && MouseY >= LOGIN_Y1 && MouseY <= LOGIN_Y2 && *page != LOGIN_ADMIN) ||
		(MouseX >= REGISTER_X1 && MouseX <= REGISTER_X2 && MouseY >= REGISTER_Y1 && MouseY <= REGISTER_Y2 && *page != LOGIN_ADMIN) ||
		(MouseX >= ADMIN_X1 && MouseX <= ADMIN_X2 && MouseY >= ADMIN_Y1 && MouseY <= ADMIN_Y2 && *page != REGISTER) ||
		(MouseX >= ADMIN_LOGIN_X1 && MouseX <= ADMIN_LOGIN_X2 && MouseY >= ADMIN_LOGIN_Y1 && MouseY <= ADMIN_LOGIN_Y2 && *page == LOGIN_ADMIN) ||
		(MouseX >= EXITPROGRAM_X1 && MouseX <= EXITPROGRAM_X2 && MouseY >= EXITPROGRAM_Y1 && MouseY <= EXITPROGRAM_Y2))
		MouseS=1; // 假设设置为手形图标
	else 
		MouseS=0; // 恢复默认箭头

	setlinestyle(SOLID_LINE,0,NORM_WIDTH);
	// 处理可交互窗口的鼠标移动事件 **显示激活状态**
	if (MouseX >= USERNAME_X1 && MouseX <= USERNAME_X2 && MouseY >= USERNAME_Y1 && MouseY <= USERNAME_Y2) {
		*tag=ACTIVE_USERNAME;
		setcolor(GREEN);
		rectangle(USERNAME_X1-2, USERNAME_Y1-2, USERNAME_X2+2, USERNAME_Y2+2);
	}
	else if (MouseX >= PASSWORD_X1 && MouseX <= PASSWORD_X2 && MouseY >= PASSWORD_Y1 && MouseY <= PASSWORD_Y2) {
		*tag=ACTIVE_PASSWORD;
		setcolor(GREEN);
		rectangle(PASSWORD_X1-2, PASSWORD_Y1-2, PASSWORD_X2+2, PASSWORD_Y2+2);
	}
	else if (MouseX >= LOGIN_X1 && MouseX <= LOGIN_X2 && MouseY >= LOGIN_Y1 && MouseY <= LOGIN_Y2 && *page != LOGIN_ADMIN) {
		*tag=ACTIVE_LOGIN;
		setcolor(GREEN);
		rectangle(LOGIN_X1-2, LOGIN_Y1-2, LOGIN_X2+2, LOGIN_Y2+2);
	}
	else if (MouseX >= REGISTER_X1 && MouseX <= REGISTER_X2 && MouseY >= REGISTER_Y1 && MouseY <= REGISTER_Y2 && *page != LOGIN_ADMIN) {
		*tag=ACTIVE_REGISTER;
		setcolor(GREEN);
		rectangle(REGISTER_X1-2, REGISTER_Y1-2, REGISTER_X2+2, REGISTER_Y2+2);
	}
	else if (MouseX >= ADMIN_X1 && MouseX <= ADMIN_X2 && MouseY >= ADMIN_Y1 && MouseY <= ADMIN_Y2 && *page != REGISTER) {
		*tag=ACTIVE_ADMIN;
		setcolor(GREEN);
		rectangle(ADMIN_X1-2, ADMIN_Y1-2, ADMIN_X2+2, ADMIN_Y2+2);
	}
	else if (MouseX >= ADMIN_LOGIN_X1 && MouseX <= ADMIN_LOGIN_X2 && MouseY >= ADMIN_LOGIN_Y1 && MouseY <= ADMIN_LOGIN_Y2 && *page == LOGIN_ADMIN) {
		*tag=ACTIVE_ADMIN_LOGIN;
		setcolor(GREEN);
		rectangle(ADMIN_LOGIN_X1-2, ADMIN_LOGIN_Y1-2, ADMIN_LOGIN_X2+2, ADMIN_LOGIN_Y2+2);
	}
	else if ((MouseX >= EXITPROGRAM_X1 && MouseX <= EXITPROGRAM_X2 && MouseY >= EXITPROGRAM_Y1 && MouseY <= EXITPROGRAM_Y2) && *tag==ACTIVE_NONE) {
		*tag=EXIT_PROGRAM;
		setcolor(RED);
		setlinestyle(0, 0, THICK_WIDTH);
		line(EXITPROGRAM_X1, EXITPROGRAM_Y1, EXITPROGRAM_X2, EXITPROGRAM_Y2);
		line(EXITPROGRAM_X2, EXITPROGRAM_Y1, EXITPROGRAM_X1, EXITPROGRAM_Y2); // 使叉变粗

		setcolor(BLACK);
		setlinestyle(0, 0, 2);
		line(EXITPROGRAM_X2+20, EXITPROGRAM_Y1, EXITPROGRAM_X2+100, EXITPROGRAM_Y1);
		line(EXITPROGRAM_X2+20, EXITPROGRAM_Y1, EXITPROGRAM_X2+20, EXITPROGRAM_Y1+40);
		line(EXITPROGRAM_X2+20, EXITPROGRAM_Y1+40, EXITPROGRAM_X2+100, EXITPROGRAM_Y1+40);
		line(EXITPROGRAM_X2+100, EXITPROGRAM_Y1, EXITPROGRAM_X2+100, EXITPROGRAM_Y1+40);
		setfillstyle(SOLID_FILL,BLUE);
		bar(EXITPROGRAM_X2+20, EXITPROGRAM_Y1, EXITPROGRAM_X2+120, EXITPROGRAM_Y2);
		puthz(EXITPROGRAM_X2+20, EXITPROGRAM_Y1+8, "退出程序",24,25,WHITE); // 输出提示文本和背景
	}

	//***  处理可交互窗口的鼠标移动事件 **取消激活状态**  ***//
	if ((MouseX < USERNAME_X1 || MouseX > USERNAME_X2 || MouseY < USERNAME_Y1 || MouseY > USERNAME_Y2) && (*tag==ACTIVE_USERNAME)) {
		*tag=ACTIVE_NONE;
		setcolor(WHITE);
		rectangle(USERNAME_X1-2, USERNAME_Y1-2, USERNAME_X2+2, USERNAME_Y2+2);
	}
	else if ((MouseX < PASSWORD_X1 || MouseX > PASSWORD_X2 || MouseY < PASSWORD_Y1 || MouseY > PASSWORD_Y2) && (*tag==ACTIVE_PASSWORD)) {
		*tag=ACTIVE_NONE;
		setcolor(WHITE);
		rectangle(PASSWORD_X1-2, PASSWORD_Y1-2, PASSWORD_X2+2, PASSWORD_Y2+2);
	}
	//登录预注册的两个红色按钮共用一个else if语句
	else if ((MouseX < LOGIN_X1 || MouseX > LOGIN_X2 || MouseY < LOGIN_Y1 || MouseY > LOGIN_Y2) 
		&& (*tag==ACTIVE_LOGIN) && *page != LOGIN_ADMIN) {
		*tag=ACTIVE_NONE;
		setcolor(WHITE);
		rectangle(LOGIN_X1-2, LOGIN_Y1-2, LOGIN_X2+2, LOGIN_Y2+2);
	}
	else if ((MouseX < REGISTER_X1 || MouseX > REGISTER_X2 || MouseY < REGISTER_Y1 || MouseY > REGISTER_Y2) 
		&& *tag==ACTIVE_REGISTER && *page != LOGIN_ADMIN) {
		*tag=ACTIVE_NONE;
		setcolor(WHITE);
		rectangle(REGISTER_X1-2, REGISTER_Y1-2, REGISTER_X2+2, REGISTER_Y2+2);
	}
	//管理员模式和用户模式共用一个else if语句
	else if ((MouseX < ADMIN_X1 || MouseX > ADMIN_X2 || MouseY < ADMIN_Y1 || MouseY > ADMIN_Y2) && *tag==ACTIVE_ADMIN && *page != REGISTER) {
		*tag=ACTIVE_NONE;
		setcolor(WHITE);
		rectangle(ADMIN_X1-2, ADMIN_Y1-2, ADMIN_X2+2, ADMIN_Y2+2);
	}
	else if ((MouseX < ADMIN_LOGIN_X1 || MouseX > ADMIN_LOGIN_X2 || MouseY < ADMIN_LOGIN_Y1 || MouseY > ADMIN_LOGIN_Y2) 
		&& *tag==ACTIVE_ADMIN_LOGIN && *page == LOGIN_ADMIN) {
		*tag=ACTIVE_NONE;
		setcolor(WHITE);
		rectangle(ADMIN_LOGIN_X1-2, ADMIN_LOGIN_Y1-2, ADMIN_LOGIN_X2+2, ADMIN_LOGIN_Y2+2);

	}
	else if ((MouseX < EXITPROGRAM_X1 || MouseX > EXITPROGRAM_X2 || MouseY < EXITPROGRAM_Y1 || MouseY > EXITPROGRAM_Y2) && (*tag==EXIT_PROGRAM)) {
		*tag=ACTIVE_NONE;
		setfillstyle(SOLID_FILL,0);
		bar(EXITPROGRAM_X1, EXITPROGRAM_Y1, EXITPROGRAM_X2, EXITPROGRAM_Y2); // 清理叉

		setcolor(RED);
		setlinestyle(0, 0, NORM_WIDTH);
		line(EXITPROGRAM_X1, EXITPROGRAM_Y1, EXITPROGRAM_X2, EXITPROGRAM_Y2);
		line(EXITPROGRAM_X2, EXITPROGRAM_Y1, EXITPROGRAM_X1, EXITPROGRAM_Y2); // 重新画叉

		setfillstyle(SOLID_FILL,0);
		bar(EXITPROGRAM_X2+20, EXITPROGRAM_Y1, EXITPROGRAM_X2+120, EXITPROGRAM_Y2); // 清理提示文本
	}
	
}

//切换页面时的过场
void switchPage(){
	int i,j,k;
	setfillstyle(SOLID_FILL,MY_LIGHTGRAY);
	for(i=0;i<16;i++)
		for(j=0;j<12;j++)
			for(k=0;k<=5;k++)
			{
				bar(i*40+20-k*4,j*40+20-k*4,i*40+20+k*4,j*40+20+k*4);
				delay(1);
			}
}

//以下为登录或注册的成功与失败的动画
void anime_login_success(){
	int blinkTick=0;
	clrmous(MouseX,MouseY);

	setfillstyle(SOLID_FILL,MY_LIGHTBLUE);
	bar(120, 395, 520, 430); //覆盖原有的错误提示

	setcolor(LIGHTGREEN);
	rectangle(USERNAME_X1+2,USERNAME_Y1+2,USERNAME_X2-2,USERNAME_Y2-2);
	rectangle(PASSWORD_X1+2,PASSWORD_Y1+2,PASSWORD_X2-2,PASSWORD_Y2-2);
	
	while(blinkTick < 100){
		if(blinkTick % 20 == 0 && blinkTick % 40 != 0){
			setfillstyle(SOLID_FILL,MY_GREEN);
			bar(LOGIN_X1,LOGIN_Y1,LOGIN_X2,LOGIN_Y2);
			puthz(LOGIN_X1+8, LOGIN_Y1+12, "登录成功", 24, 20, MY_WHITE);
		}else if(blinkTick % 40 == 0){
			setfillstyle(SOLID_FILL,MY_LIGHTBLUE);
			bar(LOGIN_X1,LOGIN_Y1,LOGIN_X2,LOGIN_Y2);
			puthz(LOGIN_X1+8, LOGIN_Y1+12, "登录成功", 24, 20, MY_WHITE);
		}
		blinkTick++;
		delay(25);
	}
}

void anime_login_fail(){
	int blinkTick=0;
	clrmous(MouseX,MouseY);

	setcolor(WHITE);
	setlinestyle(SOLID_LINE,0,NORM_WIDTH);
	rectangle(USERNAME_X1+2,USERNAME_Y1+2,USERNAME_X2-2,USERNAME_Y2-2);
	rectangle(PASSWORD_X1+2,PASSWORD_Y1+2,PASSWORD_X2-2,PASSWORD_Y2-2);
	setfillstyle(SOLID_FILL,MY_LIGHTBLUE);//先覆盖原先的错误提示

	puthz(165,400,"错误：账号或密码错误！",24,30,MY_WHITE);

	setcolor(RED);
	setlinestyle(SOLID_LINE,0,NORM_WIDTH);
	rectangle(USERNAME_X1+2,USERNAME_Y1+2,USERNAME_X2-2,USERNAME_Y2-2);
	rectangle(PASSWORD_X1+2,PASSWORD_Y1+2,PASSWORD_X2-2,PASSWORD_Y2-2);//后判断应该高亮提示那个输入框输入错误
	
	while(blinkTick < 100){
		if(blinkTick % 20 == 0 && blinkTick % 40 != 0){
			setfillstyle(SOLID_FILL,MY_RED);
			bar(LOGIN_X1,LOGIN_Y1,LOGIN_X2,LOGIN_Y2);
			puthz(LOGIN_X1+8, LOGIN_Y1+12, "登录失败", 24, 20, MY_WHITE);
		}else if(blinkTick % 40 == 0){
			setfillstyle(SOLID_FILL,MY_LIGHTBLUE);
			bar(LOGIN_X1,LOGIN_Y1,LOGIN_X2,LOGIN_Y2);
			puthz(LOGIN_X1+8, LOGIN_Y1+12, "登录失败", 24, 20, MY_WHITE);
		}
		blinkTick++;
		delay(25);
	}

	setfillstyle(SOLID_FILL,MY_RED);
	bar(LOGIN_X1, LOGIN_Y1, LOGIN_X2, LOGIN_Y2);

	puthz(LOGIN_X1+24, LOGIN_Y1+12, "登录",24,30,MY_WHITE);
	
}

void anime_admin_login_success(){
	int blinkTick=0;
	clrmous(MouseX,MouseY);

	setfillstyle(SOLID_FILL,MY_LIGHTBLUE);
	bar(120, 435, 520, 480); //覆盖原有的错误提示

	setcolor(LIGHTGREEN);
	rectangle(USERNAME_X1+2,USERNAME_Y1+2,USERNAME_X2-2,USERNAME_Y2-2);
	rectangle(PASSWORD_X1+2,PASSWORD_Y1+2,PASSWORD_X2-2,PASSWORD_Y2-2);
	
	while(blinkTick < 100){
		if(blinkTick % 20 == 0 && blinkTick % 40 != 0){
			setfillstyle(SOLID_FILL,MY_GREEN);
			bar(ADMIN_LOGIN_X1,ADMIN_LOGIN_Y1,ADMIN_LOGIN_X2,ADMIN_LOGIN_Y2);
			puthz(ADMIN_LOGIN_X1+8, ADMIN_LOGIN_Y1+12, "登录成功", 24, 20, MY_WHITE);
		}else if(blinkTick % 40 == 0){
			setfillstyle(SOLID_FILL,MY_LIGHTBLUE);
			bar(ADMIN_LOGIN_X1,ADMIN_LOGIN_Y1,ADMIN_LOGIN_X2,ADMIN_LOGIN_Y2);
			puthz(ADMIN_LOGIN_X1+8, ADMIN_LOGIN_Y1+12, "登录成功", 24, 20, MY_WHITE);
		}
		blinkTick++;
		delay(25);
	}
}

void anime_admin_login_fail(){
	int blinkTick=0;
	clrmous(MouseX,MouseY);

	setcolor(WHITE);
	setlinestyle(SOLID_LINE,0,NORM_WIDTH);
	rectangle(USERNAME_X1+2,USERNAME_Y1+2,USERNAME_X2-2,USERNAME_Y2-2);
	rectangle(PASSWORD_X1+2,PASSWORD_Y1+2,PASSWORD_X2-2,PASSWORD_Y2-2);
	setfillstyle(SOLID_FILL,MY_LIGHTBLUE);
	bar(120, 435, 520, 480); //覆盖原有的错误提示

	puthz(165,440,"错误：账号或密码错误！",24,30,MY_WHITE);

	setcolor(RED);
	setlinestyle(SOLID_LINE,0,NORM_WIDTH);
	rectangle(USERNAME_X1+2,USERNAME_Y1+2,USERNAME_X2-2,USERNAME_Y2-2);
	rectangle(PASSWORD_X1+2,PASSWORD_Y1+2,PASSWORD_X2-2,PASSWORD_Y2-2);//后判断应该高亮提示那个输入框输入错误
	
	while(blinkTick < 100){
		if(blinkTick % 20 == 0 && blinkTick % 40 != 0){
			setfillstyle(SOLID_FILL,MY_RED);
			bar(ADMIN_LOGIN_X1,ADMIN_LOGIN_Y1,ADMIN_LOGIN_X2,ADMIN_LOGIN_Y2);
			puthz(ADMIN_LOGIN_X1+8, ADMIN_LOGIN_Y1+12, "登录失败", 24, 20, MY_WHITE);
		}else if(blinkTick % 40 == 0){
			setfillstyle(SOLID_FILL,MY_LIGHTBLUE);
			bar(ADMIN_LOGIN_X1,ADMIN_LOGIN_Y1,ADMIN_LOGIN_X2,LOGIN_Y2);
			puthz(ADMIN_LOGIN_X1+8, ADMIN_LOGIN_Y1+12, "登录失败", 24, 20, MY_WHITE);
		}
		blinkTick++;
		delay(25);
	}

	setfillstyle(SOLID_FILL,MY_RED);
	bar(ADMIN_LOGIN_X1, ADMIN_LOGIN_Y1, ADMIN_LOGIN_X2, ADMIN_LOGIN_Y2);

	puthz(ADMIN_LOGIN_X1+24, ADMIN_LOGIN_Y1+12, "登录",24,30,MY_WHITE);
	
}

void anime_register_success(){
	int blinkTick=0;
	clrmous(MouseX,MouseY);

	setfillstyle(SOLID_FILL,MY_LIGHTBLUE);
	bar(120, 395, 520, 430); //覆盖原有的错误提示

	setcolor(LIGHTGREEN);
	rectangle(USERNAME_X1+2,USERNAME_Y1+2,USERNAME_X2-2,USERNAME_Y2-2);
	rectangle(PASSWORD_X1+2,PASSWORD_Y1+2,PASSWORD_X2-2,PASSWORD_Y2-2);
	
	while(blinkTick < 100){
		if(blinkTick % 20 == 0 && blinkTick % 40 != 0){
			setfillstyle(SOLID_FILL,MY_GREEN);
			bar(LOGIN_X1,LOGIN_Y1,LOGIN_X2,LOGIN_Y2);
			puthz(LOGIN_X1+8, LOGIN_Y1+12, "注册成功", 24, 20, MY_WHITE);
		}else if(blinkTick % 40 == 0){
			setfillstyle(SOLID_FILL,MY_LIGHTBLUE);
			bar(LOGIN_X1,LOGIN_Y1,LOGIN_X2,LOGIN_Y2);
			puthz(LOGIN_X1+8, LOGIN_Y1+12, "注册成功", 24, 20, MY_WHITE);
		}
		blinkTick++;
		delay(25);
	}
}


void anime_register_fail(int err){
	int blinkTick=0;
	clrmous(MouseX,MouseY);

	setcolor(WHITE);
	setlinestyle(SOLID_LINE,0,NORM_WIDTH);
	rectangle(USERNAME_X1+2,USERNAME_Y1+2,USERNAME_X2-2,USERNAME_Y2-2);
	rectangle(PASSWORD_X1+2,PASSWORD_Y1+2,PASSWORD_X2-2,PASSWORD_Y2-2);
	setfillstyle(SOLID_FILL,MY_LIGHTBLUE);
	bar(120, 395, 520, 430);//先覆盖原先的错误提示

	if(err == 1) puthz(165,400,"错误：该账号已被注册！",24,30,MY_WHITE);
	if(err >= 2 && err <=4) puthz(137,400,"错误：用户名或密码未填写！",24,30,MY_WHITE);

	setcolor(RED);
	setlinestyle(SOLID_LINE,0,NORM_WIDTH);
	if(err == 1 || err == 2 || err == 4) 
		rectangle(USERNAME_X1+2,USERNAME_Y1+2,USERNAME_X2-2,USERNAME_Y2-2);
	if(err == 3 || err == 4) 
		rectangle(PASSWORD_X1+2,PASSWORD_Y1+2,PASSWORD_X2-2,PASSWORD_Y2-2);//后判断应该高亮提示那个输入框输入错误
	
	while(blinkTick < 100){
		if(blinkTick % 20 == 0 && blinkTick % 40 != 0){
			setfillstyle(SOLID_FILL,MY_RED);
			bar(LOGIN_X1,LOGIN_Y1,LOGIN_X2,LOGIN_Y2);
			puthz(LOGIN_X1+8, LOGIN_Y1+12, "注册失败", 24, 20, MY_WHITE);
		}else if(blinkTick % 40 == 0){
			setfillstyle(SOLID_FILL,MY_LIGHTBLUE);
			bar(LOGIN_X1,LOGIN_Y1,LOGIN_X2,LOGIN_Y2);
			puthz(LOGIN_X1+8, LOGIN_Y1+12, "注册失败", 24, 20, MY_WHITE);
		}
		blinkTick++;
		delay(25);
	}

	setfillstyle(SOLID_FILL,MY_RED);
	bar(LOGIN_X1, LOGIN_Y1, LOGIN_X2, LOGIN_Y2);

	puthz(LOGIN_X1+8, LOGIN_Y1+12, "确认注册", 24, 20, MY_WHITE);
	
}

void anime_id_input_success() {
	int blinkTick = 0;
	clrmous(MouseX, MouseY);

	setfillstyle(SOLID_FILL, MY_WHITE);
	bar(330, 210, 500, 250);//覆盖原先错误提示

	setcolor(LIGHTGREEN);
	setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
	rectangle(PASSWORD_X1 + 2, PASSWORD_Y1 + 2, PASSWORD_X2 - 2, PASSWORD_Y2 - 2);

	while (blinkTick < 100) {
		if (blinkTick % 20 == 0 && blinkTick % 40 != 0) {
			setfillstyle(SOLID_FILL, MY_GREEN);
			bar(LOGIN_X1, LOGIN_Y1, LOGIN_X2, LOGIN_Y2);
			puthz(LOGIN_X1 + 8, LOGIN_Y1 + 12, "认证成功", 24, 20, MY_WHITE);
		}
		else if (blinkTick % 40 == 0) {
			setfillstyle(SOLID_FILL, MY_LIGHTBLUE);
			bar(LOGIN_X1, LOGIN_Y1, LOGIN_X2, LOGIN_Y2);
			puthz(LOGIN_X1 + 8, LOGIN_Y1 + 12, "认证成功", 24, 20, MY_WHITE);
		}
		blinkTick++;
		delay(25);
	}
}



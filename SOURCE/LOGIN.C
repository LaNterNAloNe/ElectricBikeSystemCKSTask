#include"LOGIN.H"

// 登录界面
void login(int *page,int *uid) {
	
    char usrn[13] = {0}; // 初始化为空
    char psw[13] = {0};
    int tag = 0;
	
    clrmous(MouseX, MouseY);
    save_bk_mou(MouseX, MouseY);
    drawgraph_login();

    while (1) {
		flushLoginGraph(&tag,page); // 刷新界面
		newmouse(&MouseX, &MouseY, &press); // 刷新鼠标

        // 处理鼠标点击事件
        if (mouse_press(USERNAME_X1, USERNAME_Y1, USERNAME_X2, USERNAME_Y2)==1) {
            Input_Vis(usrn, USERNAME_X1, USERNAME_Y1+5, 13, MY_WHITE,page);
        }

        if (mouse_press(PASSWORD_X1, PASSWORD_Y1, PASSWORD_X2, PASSWORD_Y2)==1) {
            Input_Invis(psw, PASSWORD_X1, PASSWORD_Y1+5, 13, MY_WHITE,page);
        }

        if (mouse_press(LOGIN_X1, LOGIN_Y1, LOGIN_X2, LOGIN_Y2)==1) {
            // 检查输入是否非空且正确
            if (usrn[0] != '\0' && psw[0] != '\0') {
				userlogin_judge(usrn,psw,uid);
				if(*uid != -1){
					//switchPage();
					*page = MAIN_ADMIN; // MAIN_USER : 10 跳转到用户主界面
                	return; // 退出循环
				}else{
					puthz(230,400,"账号或密码错误！",24,30,MY_WHITE);
				}
            }
        }
		if (mouse_press(ADMIN_X1,ADMIN_Y1,ADMIN_X2,ADMIN_Y2)==1) {
			clrmous(MouseX, MouseY);
			switchPage();
			*page = LOGIN_ADMIN; // LOGIN_ADMIN : 2 跳转到管理员登录界面
			return;
		}
		else if (mouse_press(REGISTER_X1,REGISTER_Y1,REGISTER_X2,REGISTER_Y2)==1) {
			clrmous(MouseX, MouseY);
			switchPage();
			*page = REGISTER; // REGISTER : 3 跳转到注册界面
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
    setrgbpalette(MY_LIGHTBLUE, 12,158,245);//浅蓝背景-1
	setrgbpalette(MY_LIGHTGRAY, 235,235,235);//浅灰框-1
	setrgbpalette(MY_BLACK, 0, 0, 0);//黑色
	setrgbpalette(MY_YELLOW, 240, 230,75);//黄色
	setrgbpalette(MY_RED, 255, 0, 0);//红色
	setrgbpalette(MY_WHITE, 255, 255, 255);//白色
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

	puthz(94, 50, "校园自行车管理系统",48,50,MY_WHITE);// 输出文本
	puthz(220, 140, "用户名",24,50,MY_BLACK);// 输出文本
	puthz(220, 230, "密码",24,50,MY_BLACK);
	puthz(255, 330, "登录",24,30,MY_WHITE);
	puthz(380, 330, "注册",24,30,MY_WHITE);
	puthz(ADMIN_X1+2, ADMIN_Y1+2, "管理员模式",16,15,MY_WHITE);

	setcolor(4);
	setlinestyle(0, 0, NORM_WIDTH);
	line(EXITPROGRAM_X1, EXITPROGRAM_Y1, EXITPROGRAM_X2, EXITPROGRAM_Y2);
	line(EXITPROGRAM_X2, EXITPROGRAM_Y1, EXITPROGRAM_X1, EXITPROGRAM_Y2);
}

//管理员登录界面
void login_admin(int* page,int *uid) {
	char a[10] = { 0 }; // 初始化为空
	char b[10] = { 0 };
	int tag = 0;
	FILE *fp_LOGIN_ADMIN_read = fopen("C:\\EBS\\DATA\\ADMIN.csv","r");
	if(fp_LOGIN_ADMIN_read == NULL) *page=-1,getch(),exit(0);
	clrmous(MouseX, MouseY);
	save_bk_mou(MouseX, MouseY);
	drawgraph_admin_login();
	while (1) {
		flushLoginGraph(&tag,page); // 刷新界面
		newmouse(&MouseX, &MouseY, &press); // 刷新鼠标

		// 处理鼠标点击事件
		if (mouse_press(USERNAME_X1, USERNAME_Y1, USERNAME_X2, USERNAME_Y2) == 1) {
			Input_Vis(a, USERNAME_X1, USERNAME_Y1 + 5, 13, MY_WHITE,page);
		}

		if (mouse_press(PASSWORD_X1, PASSWORD_Y1, PASSWORD_X2, PASSWORD_Y2) == 1) {
			Input_Invis(b, PASSWORD_X1, PASSWORD_Y1 + 5, 13, MY_WHITE,page);
		}

		if (mouse_press(ADMIN_LOGIN_X1, ADMIN_LOGIN_Y1, ADMIN_LOGIN_X2, ADMIN_LOGIN_Y2) == 1) {
			// 检查输入是否非空且正确
			if (a[0] != '\0' && b[0] != '\0' &&
				strcmp(a, "cks666") == 0 && strcmp(b, "cks666") == 0) {
				switchPage();
				*page = MAIN_ADMIN; // MAIN_USER : 10 跳转到用户主界面
				return; // 退出循环
			}
		}
		if (mouse_press(ADMIN_X1, ADMIN_Y1, ADMIN_X2, ADMIN_Y2) == 1) {
			clrmous(MouseX, MouseY);
			switchPage();
			*page = LOGIN; // LOGIN_ADMIN : 2 跳转到用户登录界面
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
	
//绘制管理员登录界面
void drawgraph_admin_login(){
	setrgbpalette(MY_LIGHTBLUE, 12, 158, 245);//浅蓝背景-1
	setrgbpalette(MY_LIGHTGRAY, 235, 235, 235);//浅灰框-1
	setrgbpalette(MY_BLACK, 0, 0, 0);//黑色
	setrgbpalette(MY_YELLOW, 240, 230, 75);//黄色
	setrgbpalette(MY_RED, 255, 0, 0);//红色
	setrgbpalette(MY_WHITE, 255, 255, 255);//白色
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

	puthz(94, 50, "校园自行车管理系统", 48, 50, MY_WHITE);// 输出文本
	puthz(220, 140, "用户名", 24, 50, MY_BLACK);// 输出文本
	puthz(220, 230, "密码", 24, 50, MY_BLACK);
	puthz(310, 330, "登录", 24, 30, MY_WHITE);
	puthz(ADMIN_X1 + 5, ADMIN_Y1 + 2, "用户模式", 16, 15, MY_WHITE);
	setcolor(4);
	setlinestyle(0, 0, NORM_WIDTH);
	line(EXITPROGRAM_X1, EXITPROGRAM_Y1, EXITPROGRAM_X2, EXITPROGRAM_Y2);
	line(EXITPROGRAM_X2, EXITPROGRAM_Y1, EXITPROGRAM_X1, EXITPROGRAM_Y2);
}

	

// 注册界面
void _register(int* page) {
	char usrn[10] = { 0 }; // 初始化为空
	char psw[10] = { 0 };
	int tag = 0;
	FILE *fp_LOGIN_USER_write = fopen("C:\\EBS\\DATA\\ADMIN.csv","w+");
	if(fp_LOGIN_USER_write == NULL) *page=-1,getch(),exit(0);
	clrmous(MouseX, MouseY);
	save_bk_mou(MouseX, MouseY);
	drawgraph_register();
	while (1) {
		flushLoginGraph(&tag,page); // 刷新界面
		newmouse(&MouseX, &MouseY, &press); // 刷新鼠标

		// 处理鼠标点击事件
		if (mouse_press(USERNAME_X1, USERNAME_Y1, USERNAME_X2, USERNAME_Y2) == 1) {
			Input_Vis(usrn, USERNAME_X1, USERNAME_Y1 + 5, 13, MY_WHITE,page);
		}

		if (mouse_press(PASSWORD_X1, PASSWORD_Y1, PASSWORD_X2, PASSWORD_Y2) == 1) {
			Input_Invis(psw, PASSWORD_X1, PASSWORD_Y1 + 5, 13, MY_WHITE,page);
		}

		if (mouse_press(LOGIN_X1, LOGIN_Y1, LOGIN_X2, LOGIN_Y2) == 1) {
			// 检查输入是否非空且正确
			if (usrn[0] != '\0' && psw[0] != '\0'){
				if(userregister_judge(usrn,psw) == 0){
					anime_register_success();
					*page = LOGIN;
					return;
				}

			}
		}
		else if (mouse_press(REGISTER_X1, REGISTER_Y1, REGISTER_X2, REGISTER_Y2) == 1) {
			clrmous(MouseX, MouseY);
			switchPage();
			*page = LOGIN; //此时这个键是“返回登录”，跳转到登录界面
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
	setrgbpalette(MY_LIGHTBLUE, 12, 158, 245);//浅蓝背景-1
	setrgbpalette(MY_LIGHTGRAY, 235, 235, 235);//浅灰框-1
	setrgbpalette(MY_BLACK, 0, 0, 0);//黑色
	setrgbpalette(MY_YELLOW, 240, 230, 75);//黄色
	setrgbpalette(MY_RED, 255, 0, 0);//红色
	setrgbpalette(MY_WHITE, 255, 255, 255);//白色

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

	puthz(94, 50, "校园自行车管理系统", 48, 50, MY_WHITE);// 输出文本
	puthz(220, 140, "输入用户名", 24, 20, MY_BLACK);// 输出文本
	puthz(220, 230, "输入密码", 24, 20, MY_BLACK);
	puthz(245, 330, "确认注册", 24, 20, MY_WHITE);
	puthz(370, 330, "返回登录", 24, 20, MY_WHITE);
	setcolor(4);
	setlinestyle(0, 0, NORM_WIDTH);
	line(EXITPROGRAM_X1, EXITPROGRAM_Y1, EXITPROGRAM_X2, EXITPROGRAM_Y2);
	line(EXITPROGRAM_X2, EXITPROGRAM_Y1, EXITPROGRAM_X1, EXITPROGRAM_Y2);
}


void userlogin_judge(char *usrn,char *psw,int *uid){
	int i=0;
	int file_lenth;
	USER_LOGIN_DATA *TEMP=malloc(sizeof(USER_LOGIN_DATA));
	FILE *fp_LOGIN_USER_read = fopen("C:\\EBS\\DATA\\USER.dat","rb");
	if(TEMP=NULL) getch(),exit(0);
	if(fp_LOGIN_USER_read == NULL) getch(),exit(0);
	fseek(fp_LOGIN_USER_read,0,SEEK_END);
	file_lenth = ftell(fp_LOGIN_USER_read)/sizeof(USER_LOGIN_DATA);//初始操作完成，接下来开始遍历数据

	for(i=0;i<file_lenth;i++){
		fseek(fp_LOGIN_USER_read,i*sizeof(USER_LOGIN_DATA),SEEK_SET);
		fread(TEMP,sizeof(USER_LOGIN_DATA),1,fp_LOGIN_USER_read); //逐个读取，每个用户信息，直到用户名与密码均匹配

		if(strcmp(usrn,TEMP->usrn) == 0){
			if(strcmp(psw,TEMP->psw) == 0){
				//登陆成功
				*uid = TEMP->uid;
				free(TEMP);
				if(fclose(fp_LOGIN_USER_read)!=0) getch(),exit(0);
				return;
			}
		}
		
	}
	//若完成for循环仍未经过return函数，则说明账号不存在或账号存在，密码错误
	if(fclose(fp_LOGIN_USER_read)!=0) getch(),exit(0);
	free(TEMP);
	return;
}

int userregister_judge(char *usrn,char *psw){
	int i=0;
	int file_lenth;
	USER_LOGIN_DATA *TEMP=malloc(sizeof(USER_LOGIN_DATA));
	FILE *fp_LOGIN_USER_readndwrite = fopen("C:\\EBS\\DATA\\USER.dat","rb+");
	if(TEMP=NULL) getch(),exit(0);
	if(fp_LOGIN_USER_readndwrite == NULL) getch(),exit(0);
	fseek(fp_LOGIN_USER_readndwrite,0,SEEK_END);
	file_lenth = ftell(fp_LOGIN_USER_readndwrite)/sizeof(USER_LOGIN_DATA);//初始操作完成，接下来开始遍历数据

	for(i=0;i<=file_lenth;i++){
		fseek(fp_LOGIN_USER_readndwrite,i*sizeof(USER_LOGIN_DATA),SEEK_SET);
		fread(TEMP,sizeof(USER_LOGIN_DATA),1,fp_LOGIN_USER_readndwrite); //逐个读取，每个用户信息

		if(strcmp(usrn,TEMP->usrn) == 0){
			free(TEMP);
			if(fclose(fp_LOGIN_USER_readndwrite)!=0) getch(),exit(0); //发现存在用户名相同的，则注册失败
			return 1;
		}else{
			strcpy(TEMP->usrn,usrn);			//获取账密和uid
			strcpy(TEMP->psw,psw);
			TEMP->uid = file_lenth;
			TEMP->state = ACTIVE;
			fwrite(TEMP,sizeof(USER_LOGIN_DATA),1,fp_LOGIN_USER_readndwrite);  //将注册信息写入文件
			free(TEMP);
			if(fclose(fp_LOGIN_USER_readndwrite)!=0) getch(),exit(0); //无相同用户名，可以注册
			return 0;
		}
	}

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
	else if (MouseX >= LOGIN_X1 && MouseX <= LOGIN_X2 && MouseY >= LOGIN_Y1 && MouseY <= LOGIN_Y2 && *page != LOGIN_ADMIN) {
		*tag=ACTIVE_LOGIN;
		setcolor(GREEN);
		setlinestyle(0, 0, 2);
		line(LOGIN_X1-2, LOGIN_Y1-2, LOGIN_X2+2, LOGIN_Y1-2);
		line(LOGIN_X1-2, LOGIN_Y1-2, LOGIN_X1-2, LOGIN_Y2+2);
		line(LOGIN_X1-2, LOGIN_Y2+2, LOGIN_X2+2, LOGIN_Y2+2);
		line(LOGIN_X2+2, LOGIN_Y1-2, LOGIN_X2+2, LOGIN_Y2+2);
	}
	else if (MouseX >= REGISTER_X1 && MouseX <= REGISTER_X2 && MouseY >= REGISTER_Y1 && MouseY <= REGISTER_Y2 && *page != LOGIN_ADMIN) {
		*tag=ACTIVE_REGISTER;
		setcolor(GREEN);
		setlinestyle(0, 0, 2);
		line(REGISTER_X1-2, REGISTER_Y1-2, REGISTER_X2+2, REGISTER_Y1-2);
		line(REGISTER_X1-2, REGISTER_Y1-2, REGISTER_X1-2, REGISTER_Y2+2);
		line(REGISTER_X1-2, REGISTER_Y2+2, REGISTER_X2+2, REGISTER_Y2+2);
		line(REGISTER_X2+2, REGISTER_Y1-2, REGISTER_X2+2, REGISTER_Y2+2);
	}
	else if (MouseX >= ADMIN_X1 && MouseX <= ADMIN_X2 && MouseY >= ADMIN_Y1 && MouseY <= ADMIN_Y2 && *page != REGISTER) {
		*tag=ACTIVE_ADMIN;
		setcolor(GREEN);
		setlinestyle(0, 0, 2);
		line(ADMIN_X1-2, ADMIN_Y1-2, ADMIN_X2+2, ADMIN_Y1-2);
		line(ADMIN_X1-2, ADMIN_Y1-2, ADMIN_X1-2, ADMIN_Y2+2);
		line(ADMIN_X1-2, ADMIN_Y2+2, ADMIN_X2+2, ADMIN_Y2+2);
		line(ADMIN_X2+2, ADMIN_Y1-2, ADMIN_X2+2, ADMIN_Y2+2);
	}
	else if (MouseX >= ADMIN_LOGIN_X1 && MouseX <= ADMIN_LOGIN_X2 && MouseY >= ADMIN_LOGIN_Y1 && MouseY <= ADMIN_LOGIN_Y2 && *page == LOGIN_ADMIN) {
		*tag=ACTIVE_ADMIN_LOGIN;
		setcolor(GREEN);
		setlinestyle(0, 0, 2);
		line(ADMIN_LOGIN_X1-2, ADMIN_LOGIN_Y1-2, ADMIN_LOGIN_X2+2, ADMIN_LOGIN_Y1-2);
		line(ADMIN_LOGIN_X1-2, ADMIN_LOGIN_Y1-2, ADMIN_LOGIN_X1-2, ADMIN_LOGIN_Y2+2);
		line(ADMIN_LOGIN_X1-2, ADMIN_LOGIN_Y2+2, ADMIN_LOGIN_X2+2, ADMIN_LOGIN_Y2+2);
		line(ADMIN_LOGIN_X2+2, ADMIN_LOGIN_Y1-2, ADMIN_LOGIN_X2+2, ADMIN_LOGIN_Y2+2);
	}
	else if ((MouseX >= EXITPROGRAM_X1 && MouseX <= EXITPROGRAM_X2 && MouseY >= EXITPROGRAM_Y1 && MouseY <= EXITPROGRAM_Y2) && *tag==ACTIVE_NONE) {
		*tag=EXIT_PROGRAM;
		setcolor(RED);
		setlinestyle(0, 0, THICK_WIDTH);
		line(EXITPROGRAM_X1, EXITPROGRAM_Y1, EXITPROGRAM_X2, EXITPROGRAM_Y2);
		line(EXITPROGRAM_X2, EXITPROGRAM_Y1, EXITPROGRAM_X1, EXITPROGRAM_Y2); // 使叉变粗

		setcolor(BLACK);
		setlinestyle(0, 0, 2);
		line(EXITPROGRAM_X2+10, EXITPROGRAM_Y1, EXITPROGRAM_X2+100, EXITPROGRAM_Y1);
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
	//登录预注册的两个红色按钮共用一个else if语句
	else if ((MouseX < LOGIN_X1 || MouseX > LOGIN_X2 || MouseY < LOGIN_Y1 || MouseY > LOGIN_Y2) 
		&& (*tag==ACTIVE_LOGIN) && *page != LOGIN_ADMIN) {
		*tag=ACTIVE_NONE;
		setcolor(WHITE);
		setlinestyle(0, 0, 2);
		line(LOGIN_X1-2, LOGIN_Y1-2, LOGIN_X2+2, LOGIN_Y1-2);
		line(LOGIN_X1-2, LOGIN_Y1-2, LOGIN_X1-2, LOGIN_Y2+2);
		line(LOGIN_X1-2, LOGIN_Y2+2, LOGIN_X2+2, LOGIN_Y2+2);
		line(LOGIN_X2+2, LOGIN_Y1-2, LOGIN_X2+2, LOGIN_Y2+2);
	}
	else if ((MouseX < REGISTER_X1 || MouseX > REGISTER_X2 || MouseY < REGISTER_Y1 || MouseY > REGISTER_Y2) 
		&& *tag==ACTIVE_REGISTER && *page != LOGIN_ADMIN) {
		*tag=ACTIVE_NONE;
		setcolor(WHITE);
		setlinestyle(0, 0, 2);
		line(REGISTER_X1-2, REGISTER_Y1-2, REGISTER_X2+2, REGISTER_Y1-2);
		line(REGISTER_X1-2, REGISTER_Y1-2, REGISTER_X1-2, REGISTER_Y2+2);
		line(REGISTER_X1-2, REGISTER_Y2+2, REGISTER_X2+2, REGISTER_Y2+2);
		line(REGISTER_X2+2, REGISTER_Y1-2, REGISTER_X2+2, REGISTER_Y2+2);
	}
	//管理员模式和用户模式共用一个else if语句
	else if ((MouseX < ADMIN_X1 || MouseX > ADMIN_X2 || MouseY < ADMIN_Y1 || MouseY > ADMIN_Y2) && *tag==ACTIVE_ADMIN && *page != REGISTER) {
		*tag=ACTIVE_NONE;
		setcolor(WHITE);
		setlinestyle(0, 0, 2);
		line(ADMIN_X1-2, ADMIN_Y1-2, ADMIN_X2+2, ADMIN_Y1-2);
		line(ADMIN_X1-2, ADMIN_Y1-2, ADMIN_X1-2, ADMIN_Y2+2);
		line(ADMIN_X1-2, ADMIN_Y2+2, ADMIN_X2+2, ADMIN_Y2+2);
		line(ADMIN_X2+2, ADMIN_Y1-2, ADMIN_X2+2, ADMIN_Y2+2);
	}
	else if ((MouseX < ADMIN_LOGIN_X1 || MouseX > ADMIN_LOGIN_X2 || MouseY < ADMIN_LOGIN_Y1 || MouseY > ADMIN_LOGIN_Y2) 
		&& *tag==ACTIVE_ADMIN_LOGIN && *page == LOGIN_ADMIN) {
		*tag=ACTIVE_NONE;
		setcolor(WHITE);
		setlinestyle(0, 0, 2);
		line(ADMIN_LOGIN_X1-2, ADMIN_LOGIN_Y1-2, ADMIN_LOGIN_X2+2, ADMIN_LOGIN_Y1-2);
		line(ADMIN_LOGIN_X1-2, ADMIN_LOGIN_Y1-2, ADMIN_LOGIN_X1-2, ADMIN_LOGIN_Y2+2);
		line(ADMIN_LOGIN_X1-2, ADMIN_LOGIN_Y2+2, ADMIN_LOGIN_X2+2, ADMIN_LOGIN_Y2+2);
		line(ADMIN_LOGIN_X2+2, ADMIN_LOGIN_Y1-2, ADMIN_LOGIN_X2+2, ADMIN_LOGIN_Y2+2);
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

void anime_register_success(){
	int blinkTick=0;
	clrmous(MouseX,MouseY);
	setfillstyle(SOLID_FILL,CYAN);
	
	while(blinkTick < 200){
		if(blinkTick % 40 == 0 && blinkTick % 80 != 0){
			setfillstyle(SOLID_FILL,GREEN);
			bar(LOGIN_X1,LOGIN_X2,LOGIN_Y1,LOGIN_Y2);
			puthz(245, 330, "注册成功", 24, 20, MY_WHITE);
		}else if(blinkTick % 80 == 0){
			setfillstyle(SOLID_FILL,YELLOW);
			bar(LOGIN_X1,LOGIN_X2,LOGIN_Y1,LOGIN_Y2);
			puthz(245, 330, "注册成功", 24, 20, MY_WHITE);
		}
		blinkTick++;
		delay(25);
	}
}
#include"GLOBAL.H"

int main(void){
    int page = MAIN_ADMIN; // 主页面
    // int page=NULL; // 副页面
    unsigned long ID=0;//记录登录用户的ID
    int driver=VGA,mode=VGAHI;
    LINKLIST *LIST = (LINKLIST *)malloc(sizeof(LINKLIST));

    initgraph(&driver, &mode, "C:\\BORLANDC\\BGI");
    cleardevice();
    mouseinit();
    initcolorpalette();

    linklist_get_user_data(LIST); // 生成链表

    while(page != EXIT){   //循环直到page = EXIT ( 0 )
        // cleardevice();
        switch (page){
            // LOGIN.C
            case LOGIN:
                login(&page,&ID);
                break;
            case LOGIN_ADMIN:
                login_admin(&page,&ID);
                break;
            case REGISTER:
                _register(&page,&ID);
                break;
            case REGISTER_ID_INPUT:
                register_id_input(&page, &ID);
                break;

            // USER.C
            case MAIN_USER:
                user_main(&page);break;
            case USER_BIKE_REGISTER:
                user_bike_register(&page, &ID); break;

            //ADMIN.C
            case MAIN_ADMIN:
                main_admin(&page,&ID);
                break;
            case ADMIN_BIKE_REGISTER:
                admin_manage_bike_module(&page, &ID, LIST,"DATA\\REGISTER.DAT","register");
                break;
            case ADMIN_BIKE_LICENSE:
                admin_manage_bike_module(&page, &ID, LIST,"DATA\\LICENSE.DAT","license");
                break;
            case ADMIN_BIKE_ANUAL:
                admin_manage_bike_module(&page, &ID, LIST,"DATA\\ANUAL.DAT","anual");
                break;
            case ADMIN_BIKE_VIOLATION:
                admin_manage_bike_module(&page, &ID, LIST,"DATA\\VIOLA.DAT","violation");
                break;
            case ADMIN_BIKE_BROKEN:
                admin_manage_bike_module(&page, &ID, LIST,"DATA\\BROKEN.DAT","broken");
                break;
            case ADMIN_DATABASE:
                admin_database(&page, &ID, LIST);
                break;
            case ADMIN_INFO:
                admin_info(&page, &ID);
                break;
        }
    }
    drawExittingProgram(page);

    linklist_clear(LIST); // 清理链表
    getch(); //按任意键结束
    closegraph();
    return 0;
}

void initcolorpalette(){
    setrgbpalette(MY_LIGHTBLUE, 12,158,245);//浅蓝背景-1
	setrgbpalette(MY_LIGHTGRAY, 235,235,235);//浅灰框-1
	setrgbpalette(MY_BLACK, 0, 0, 0);//黑色
	setrgbpalette(MY_YELLOW, 240, 230,75);//黄色
	setrgbpalette(MY_RED, 255, 0, 0);//红色
	setrgbpalette(MY_WHITE, 255, 255, 255);//白色
    setrgbpalette(MY_GREEN, 0, 255, 0);//绿色
}

void drawExittingProgram(int err){
    clrmous(MouseX, MouseY); // 隐藏鼠标
    setfillstyle(SOLID_FILL, CYAN);
    bar(120,120,520,390);
    if(err == 0) puthz(180, 200, "你正在退出程序，按任意键退出", 24, 20, MY_WHITE);
    if(err == 1) puthz(180, 200, "无法打开用户数据库", 24, 20, MY_RED);
}


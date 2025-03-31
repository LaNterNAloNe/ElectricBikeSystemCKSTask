#include"GLOBAL.H"

int main(void){
    int page=MAIN_ADMIN; // 主页面
    // int page=NULL; // 副页面
    int ID=-1;//记录登录用户的ID
    int driver=VGA,mode=VGAHI;
    LINKLIST *LIST = (LINKLIST *)malloc(sizeof(LINKLIST));

    initgraph(&driver, &mode, "C:\\BORLANDC\\BGI");
    cleardevice();
    mouseinit();
    initcolorpalette();

    get_user_data(LIST); // 生成链表

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
                _register(&page);
                break;
            
            // USER_MAIN_GRAPH.C
            case MAIN_USER:
                user_main(&page);break;
            case USER_BIKE_REGISTER:
                user_bike_register(&page, &ID); break;

            //ADMIN_MAIN_GRAPH.C
            case MAIN_ADMIN:
                main_admin(&page,&ID);
                break;
            case ADMIN_BIKE_REGISTER:
                admin_bike_register(&page,&ID,LIST);
                break;
            case ADMIN_BIKE_LICENSE:
                admin_bike_license(&page, &ID, LIST);
                break;
        }
    }
    clrmous(MouseX,MouseY);
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
    setfillstyle(SOLID_FILL, CYAN);
    bar(120,120,520,390);
    if(err == 0) puthz(180, 200, "你正在退出程序，按任意键退出", 24, 20, MY_WHITE);
    if(err == 1) puthz(180, 200, "无法打开用户数据库", 24, 20, MY_RED);
}

// 开始特性功能前先将储存信息传递到链表
void get_user_data(LINKLIST *LIST)
{
    char buffer[100];        // 定义缓冲区
    char *token;             // 定义获取截断字符串的token
    LINKLIST_USER LIST_USER; // 定义结构体，准备加入链表

    FILE *fp_USER_DATA_read = fopen("C:\\EBS\\DATA\\USRDAT.TXT", "r");
    if (fp_USER_DATA_read == NULL)
        getch(), exit(1);
    fseek(fp_USER_DATA_read, 0, SEEK_SET); // 将文件指针置于开头，开始遍历文件

    while (fgets(buffer, sizeof(buffer), fp_USER_DATA_read))
    {
        if (!strcmp(buffer, "\0"))
            break;
        if (!strcmp(buffer, "\n"))
            continue;

        token = strtok(buffer, ",");
        LIST_USER.ID = token ? atoi(token) : 0;

        strncpy(LIST_USER.usrn, strtok(NULL, ","), sizeof(LIST_USER.usrn));
        strncpy(LIST_USER.rln, strtok(NULL, ","), sizeof(LIST_USER.rln));
        strncpy(LIST_USER.location, strtok(NULL, ","), sizeof(LIST_USER.location));
        strncpy(LIST_USER.ebike_ID, strtok(NULL, ","), sizeof(LIST_USER.ebike_ID));
        strncpy(LIST_USER.ebike_license, strtok(NULL, ","), sizeof(LIST_USER.ebike_license));

        token = strtok(NULL, ",");
        LIST_USER.anual_check = token ? atoi(token) : 0;

        token = strtok(NULL, ",");
        LIST_USER.violations = token ? atoi(token) : 0;

        token = strtok(NULL, ",");
        LIST_USER.account_state = (token && *token) ? *token : ACTIVE;

        token = strtok(NULL, ",\n");
        LIST_USER.ebike_state = (token && *token) ? *token : ACTIVE;

        linklist_add_data(LIST, LIST_USER);

        memset(buffer, 0, sizeof(buffer));
        memset(&LIST_USER, 0, sizeof(LINKLIST_USER)); // 确保结构体清零
    }
}
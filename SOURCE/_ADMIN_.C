#include"_ADMIN_.H"

/*****************************************************************
MODULE:管理员主菜单
*****************************************************************/
void main_admin(int *page,unsigned long *ID){
    int tag=ACTIVE_ADMIN_NULL;
    ADMIN_BUTTONS AdminButtons[9];
    define_admin_buttons(AdminButtons, STRUCT_LENGTH(AdminButtons)); // 定义按钮

    clrmous(MouseX, MouseY);
    drawgraph_admin_menu(); // 初始化界面
    mouseinit();

    if(debug_mode == 1) display_memory_usage(400, 10); // 显示调试参数 

    while(*page == MAIN_ADMIN){
        admin_flush_buttons(&tag,STRUCT_LENGTH(AdminButtons),AdminButtons);
        admin_handle_buttons_event(page);
        //应该在传入AdminButtons前计算其长度，传入函数后，使用sizeof计算其长度则会退化为指针长度，导致功能失效
        newmouse(&MouseX, &MouseY, &press);

        delay(25);
    }
    
}

/*****************************************************************
MODULE:管理员车辆管理模块
*****************************************************************/
void admin_manage_bike_module(int *page, unsigned long *ID, LINKLIST *LIST, char *file_path, char *list_mode){
    int mode = 0; // 搜索模式，列出已处理清单或待处理清单，主动清除该页面时重设为0（默认列出待处理清单）
    // static int visited=0; // 是否进入乐该页面，主动清除该页面时重设为0
    char search_str[20]; // 搜索框输入信息储存
    int selected_id = -1;
    unsigned long id_list[8] = {0,0,0,0,0,0,0,0}; // 记录当前显示的列表每行对应的ID
    int tag = ACTIVE_ADMIN_NULL;
    int temp_page = *page; // 记录当前页面
    ADMIN_BUTTONS AdminButtons[19];
    FILE *fp_EBIKE_INFO_read = fopen(file_path, "rb+");
    if (!fp_EBIKE_INFO_read)
        exit(1);

    define_admin_buttons(AdminButtons, STRUCT_LENGTH(AdminButtons)); // 定义按钮

    fseek(fp_EBIKE_INFO_read, 0, SEEK_SET);
    drawgraph_admin_menu();
    drawgraph_admin_feature(*page);

    // 列出数据
    admin_list_info(LIST, id_list, fp_EBIKE_INFO_read, "ebike_manage", list_mode, mode, LIST_PAGEDOWN, LIST_CLEAR_CONTINUE, "\0", "\0");

    if (debug_mode == 1)
        display_memory_usage(400, 10); // 显示调试参数

    while (*page == temp_page)
    {
        admin_flush_buttons(&tag, STRUCT_LENGTH(AdminButtons), AdminButtons);
        admin_handle_buttons_event(page);
        selected_id = handle_list_select_line_admin(id_list);
        newmouse(&MouseX, &MouseY, &press);

        admin_handle_manage_feature_event(LIST, page, search_str, id_list, fp_EBIKE_INFO_read, &mode, selected_id); // 处理点击事件

        delay(25);
    }

    admin_list_info(NULL, NULL, NULL, NULL, NULL, NULL, NULL, 1, NULL, NULL);
    Input_Bar(NULL, NULL, NULL, NULL, NULL, INPUTBAR_CLEAR, NULL);
    fclose(fp_EBIKE_INFO_read);
    return;
}

/*****************************************************************
MODULE:查看管理员信息
*****************************************************************/
void admin_info(int *page, unsigned long *ID){
    int tag = ACTIVE_ADMIN_NULL;
    ADMIN_BUTTONS AdminButtons[9];
    define_admin_buttons(AdminButtons, STRUCT_LENGTH(AdminButtons)); // 定义按钮
    clrmous(MouseX, MouseY);
    drawgraph_admin_menu(); // 初始化界面

    if (debug_mode == 1)
        display_memory_usage(400, 10); // 显示调试参数

    while(*page == ADMIN_INFO){
        admin_flush_buttons(&tag,STRUCT_LENGTH(AdminButtons),AdminButtons);
        admin_handle_buttons_event(page);
        newmouse(&MouseX, &MouseY, &press);

        drawgraph_admin_info(*ID); // 显示管理员信息

        delay(25);
    }
}

/*****************************************************************
MODULE:数据一览界面
*****************************************************************/
void admin_database(int *page, unsigned long *ID , LINKLIST *LIST){
    int tag = ACTIVE_ADMIN_NULL;
    int flag = ADMIN_DATABASE_NULL; // 数据一览视图代号
    unsigned long id_list[8] = {0,0,0,0,0,0,0,0}; // 记录当前显示的列表每行对应的ID
    char search_str[20] = "\0"; // 搜索框输入信息储存
    ADMIN_BUTTONS AdminButtons[19];
    FILE *fp_USER_LOGIN_DATA_read = fopen("DATA\\USER.DAT", "rb+"); // 打开用户登录数据文件
    if (!fp_USER_LOGIN_DATA_read){
        getch(), exit(1);
    }
    // 列出车辆信息时，通过链表获取数据，因此不定义文件指针

    define_admin_buttons(AdminButtons, STRUCT_LENGTH(AdminButtons)); // 定义按钮 
    clrmous(MouseX, MouseY);
    drawgraph_admin_menu(); // 绘制界面
    drawgraph_admin_database();

    if (debug_mode == 1)
        display_memory_usage(400, 10); // 显示调试参数

    while (*page == ADMIN_DATABASE){
        admin_flush_buttons(&tag, STRUCT_LENGTH(AdminButtons), AdminButtons);
        admin_handle_buttons_event(page);
        admin_handle_database_event(LIST, &flag, page, id_list, fp_USER_LOGIN_DATA_read,search_str); // 处理点击事件
        newmouse(&MouseX, &MouseY, &press);

        delay(25);
    }

    admin_list_info(NULL, NULL, NULL, NULL, NULL, NULL, NULL, 1, NULL, NULL); // 清除列表
    Input_Bar(NULL, NULL, NULL, NULL, NULL, INPUTBAR_CLEAR, NULL);
    fclose(fp_USER_LOGIN_DATA_read);
}

/*****************************************************************
MODULE:绘制画面、刷新画面和处理鼠标点击的画图函数
*****************************************************************/

void drawgraph_admin_menu(void)
{
    int i;

    /*** 绘制菜单 ***/
    setfillstyle(SOLID_FILL, MY_YELLOW);
    bar(ADMIN_MENU_X1, ADMIN_MENU_Y1, ADMIN_MENU_X2, ADMIN_MENU_Y2);
    setcolor(BLUE);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    rectangle(ADMIN_MENU_X1 + 2, ADMIN_MENU_Y1 + 2, ADMIN_MENU_X2 - 2, ADMIN_MENU_Y2 - 2);
    setcolor(MY_BLACK);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    rectangle(ADMIN_MENU_X1 + 2, ADMIN_MENU_Y1 + 2, ADMIN_MENU_X2 - 2, ADMIN_MENU_Y2 - 2);

    /*** 绘制交互界面（暂为空白） ***/
    setfillstyle(SOLID_FILL, BLUE);
    bar(ADMIN_INTERFACE_X1, ADMIN_INTERFACE_Y1, ADMIN_INTERFACE_X2, ADMIN_INTERFACE_Y2);
    setcolor(CYAN);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    rectangle(ADMIN_INTERFACE_X1 + 2, ADMIN_INTERFACE_Y1 + 2, ADMIN_INTERFACE_X2 - 2, ADMIN_INTERFACE_Y2 - 2);
    setcolor(MY_LIGHTGRAY);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    rectangle(ADMIN_INTERFACE_X1 + 2, ADMIN_INTERFACE_Y1 + 2, ADMIN_INTERFACE_X2 - 2, ADMIN_INTERFACE_Y2 - 2);

    // /*** 绘制交互界面B（暂为空白） ***/
    // setfillstyle(SOLID_FILL, BLUE);
    // bar(INTERFACE_B_X1, INTERFACE_B_Y1, INTERFACE_B_X2, INTERFACE_B_Y2);
    // setcolor(CYAN);
    // setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    // rectangle(INTERFACE_B_X1+2, INTERFACE_B_Y1+2, INTERFACE_B_X2-2, INTERFACE_B_Y2-2);
    // setcolor(MY_LIGHTGRAY);
    // setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    // rectangle(INTERFACE_B_X1+2, INTERFACE_B_Y1+2, INTERFACE_B_X2-2, INTERFACE_B_Y2-2);

    setcolor(MY_WHITE);
    for (i = 0; i < 7; i++)
    {
        setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
        line(ADMIN_MENU_X1 + 10, ADMIN_MENU_Y1 + 45 + i * 40, ADMIN_MENU_X2 - 10, ADMIN_MENU_Y1 + 45 + i * 40);
        setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
        line(ADMIN_MENU_X1 + 6, ADMIN_MENU_Y1 + 45 + i * 40, ADMIN_MENU_X2 - 6, ADMIN_MENU_Y1 + 45 + i * 40);
        delay(10);
    }
    puthz(ADMIN_MENU_X1 + 25, ADMIN_MENU_Y1 + 25, "车辆注册", 16, 18, MY_WHITE);  // 输出文本
    puthz(ADMIN_MENU_X1 + 25, ADMIN_MENU_Y1 + 65, "上牌管理", 16, 18, MY_WHITE);  // 输出文本
    puthz(ADMIN_MENU_X1 + 25, ADMIN_MENU_Y1 + 105, "车辆报废", 16, 18, MY_WHITE); // 输出文本
    puthz(ADMIN_MENU_X1 + 25, ADMIN_MENU_Y1 + 145, "违规车辆", 16, 18, MY_WHITE); // 输出文本
    puthz(ADMIN_MENU_X1 + 25, ADMIN_MENU_Y1 + 185, "车辆年审", 16, 18, MY_WHITE); // 输出文本
    puthz(ADMIN_MENU_X1 + 25, ADMIN_MENU_Y1 + 225, "数据一览", 16, 18, MY_WHITE); // 输出文本
    puthz(ADMIN_MENU_X1 + 25, ADMIN_MENU_Y1 + 265, "信息中心", 16, 18, MY_WHITE); // 输出文本

    setcolor(MY_WHITE);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    line(ADMIN_MENU_X1 + 6, ADMIN_MENU_Y2 - 170, ADMIN_MENU_X1 + 6, ADMIN_MENU_Y2 - 144); // 绘制直线
    setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
    bar(ADMIN_MENU_X1 + 8, ADMIN_MENU_Y2 - 170, ADMIN_MENU_X1 + 90, ADMIN_MENU_Y2 - 144); // 绘制填充矩形

    setcolor(MY_GREEN);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    outtextxy(ADMIN_MENU_X1 + 10, ADMIN_MENU_Y2 - 170, "ELECTRONIC"); // 输出文本
    outtextxy(ADMIN_MENU_X1 + 10, ADMIN_MENU_Y2 - 160, "BIKE");      // 输出文本
    outtextxy(ADMIN_MENU_X1 + 10, ADMIN_MENU_Y2 - 150, "SYSTEM"); // 输出文本

    clear_person(ADMIN_INFO_X1, ADMIN_INFO_Y1, ADMIN_INFO_X2, ADMIN_INFO_Y2);

    clear_exit(ADMIN_EXIT_X1, ADMIN_EXIT_Y1, ADMIN_EXIT_X2, ADMIN_EXIT_Y2);
}

void drawgraph_admin_feature(int page)
{
    switch (page)
    {
    case ADMIN_BIKE_REGISTER: // 车辆注册
        puthz(ADMIN_INTERFACE_X1 + 5, ADMIN_INTERFACE_Y1 + 5, "车辆注册审核", 24, 20, MY_WHITE);
        draw_cues(ADMIN_BUTTON1_X2+10, ADMIN_BUTTON1_Y1, NULL, NULL); // 绘制箭头，标明当前打开页面为此
        break;
    case ADMIN_BIKE_LICENSE: // 车辆上牌
        puthz(ADMIN_INTERFACE_X1 + 5, ADMIN_INTERFACE_Y1 + 5, "车辆上牌审核", 24, 20, MY_WHITE);
        draw_cues(ADMIN_BUTTON2_X2+10, ADMIN_BUTTON2_Y1, NULL, NULL); // 绘制箭头，标明当前打开页面为此
        break;
    case ADMIN_BIKE_BROKEN: // 车辆报废
        puthz(ADMIN_INTERFACE_X1 + 5, ADMIN_INTERFACE_Y1 + 5, "车辆报废审核", 24, 20, MY_WHITE);
        draw_cues(ADMIN_BUTTON3_X2 + 10, ADMIN_BUTTON3_Y1, NULL, NULL); // 绘制箭头，标明当前打开页面为此
        break;
    case ADMIN_BIKE_VIOLATION: // 车辆违规
        puthz(ADMIN_INTERFACE_X1 + 5, ADMIN_INTERFACE_Y1 + 5, "车辆违规审核", 24, 20, MY_WHITE);
        draw_cues(ADMIN_BUTTON4_X2 + 10, ADMIN_BUTTON4_Y1, NULL, NULL); // 绘制箭头，标明当前打开页面为此
        break;
    case ADMIN_BIKE_ANUAL: // 车辆年审
        puthz(ADMIN_INTERFACE_X1 + 5, ADMIN_INTERFACE_Y1 + 5, "车辆年审审核", 24, 20, MY_WHITE);
        draw_cues(ADMIN_BUTTON5_X2+10, ADMIN_BUTTON5_Y1, NULL, NULL); // 绘制箭头，标明当前打开页面为此
        break;
    }


    puthz(ADMIN_INTERFACE_X1 + 140, ADMIN_INTERFACE_Y1 + 10, "待处理项目", 16, 16, MY_WHITE);
    setcolor(MY_RED);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    outtextxy(ADMIN_INTERFACE_X1 + 130, ADMIN_INTERFACE_Y1 + 15, "-");

    if (page == ADMIN_BIKE_REGISTER || page == ADMIN_BIKE_LICENSE || page == ADMIN_BIKE_ANUAL)
    { // 车辆注册，车辆上牌，车辆年审
        puthz(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 40, "姓名", 16, 16, MY_WHITE);
        puthz(ADMIN_INTERFACE_X1 + 100, ADMIN_INTERFACE_Y1 + 40, "学号", 16, 16, MY_WHITE);
        puthz(ADMIN_INTERFACE_X1 + 200, ADMIN_INTERFACE_Y1 + 40, "车辆车牌号", 16, 16, MY_WHITE);
    }
    else if (page == ADMIN_BIKE_VIOLATION || page == ADMIN_BIKE_BROKEN)
    { // 车辆违规，车辆报废
        puthz(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 40, "学号", 16, 16, MY_WHITE);
        puthz(ADMIN_INTERFACE_X1 + 100, ADMIN_INTERFACE_Y1 + 40, "车辆车牌号", 16, 16, MY_WHITE);
        puthz(ADMIN_INTERFACE_X1 + 200, ADMIN_INTERFACE_Y1 + 40, "地点", 16, 16, MY_WHITE);
    }

    puthz(ADMIN_INTERFACE_X1 + 300, ADMIN_INTERFACE_Y1 + 40, "申请日期", 16, 16, MY_WHITE);
    puthz(ADMIN_INTERFACE_X1 + 400, ADMIN_INTERFACE_Y1 + 40, "处理情况", 16, 16, MY_WHITE);

    setfillstyle(SOLID_FILL, MY_YELLOW);
    bar(ADMIN_FEATURE1_X1, ADMIN_FEATURE1_Y1, ADMIN_FEATURE1_X2, ADMIN_FEATURE1_Y2);
    bar(ADMIN_FEATURE2_X1, ADMIN_FEATURE2_Y1, ADMIN_FEATURE2_X2, ADMIN_FEATURE2_Y2);
    bar(ADMIN_FEATURE3_X1, ADMIN_FEATURE3_Y1, ADMIN_FEATURE3_X2, ADMIN_FEATURE3_Y2);
    bar(ADMIN_FEATURE4_X1, ADMIN_FEATURE4_Y1, ADMIN_FEATURE4_X2, ADMIN_FEATURE4_Y2);
    bar(ADMIN_FEATURE5_X1, ADMIN_FEATURE5_Y1, ADMIN_FEATURE5_X2, ADMIN_FEATURE5_Y2);
    bar(ADMIN_FEATURE6_X1, ADMIN_FEATURE6_Y1, ADMIN_FEATURE6_X2, ADMIN_FEATURE6_Y2);
    puthz(ADMIN_FEATURE1_X1 + 4, ADMIN_FEATURE1_Y1 + 8, "同意申请", 16, 16, MY_WHITE);
    puthz(ADMIN_FEATURE2_X1 + 4, ADMIN_FEATURE2_Y1 + 8, "驳回申请", 16, 16, MY_WHITE);
    puthz(ADMIN_FEATURE3_X1 + 11, ADMIN_FEATURE3_Y1 + 8, "已处理", 16, 16, MY_WHITE);
    puthz(ADMIN_FEATURE4_X1 + 11, ADMIN_FEATURE4_Y1 + 8, "待处理", 16, 16, MY_WHITE);

    setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
    bar(ADMIN_FEATURE_SEARCH_X1, ADMIN_FEATURE_SEARCH_Y1, ADMIN_FEATURE_SEARCH_X2, ADMIN_FEATURE_SEARCH_Y2);
    setcolor(MY_BLACK);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    rectangle(ADMIN_FEATURE_SEARCH_X1, ADMIN_FEATURE_SEARCH_Y1, ADMIN_FEATURE_SEARCH_X2, ADMIN_FEATURE_SEARCH_Y2);

    setlinestyle(SOLID_LINE, 0, THICK_WIDTH); // 小放大镜，提示为搜索框
    line(ADMIN_FEATURE_SEARCH_X1 + 5, ADMIN_FEATURE_SEARCH_Y2 - 7, ADMIN_FEATURE_SEARCH_X1 + 12, ADMIN_FEATURE_SEARCH_Y2 - 14);
    circle(ADMIN_FEATURE_SEARCH_X1 + 16, ADMIN_FEATURE_SEARCH_Y2 - 18, 5);

    // setfillstyle(SOLID_FILL,MY_GREEN);
    // bar(ADMIN_INTERFACE_X1+10,ADMIN_INTERFACE_Y1+70,ADMIN_INTERFACE_X1+500,ADMIN_INTERFACE_Y1+390); // 清理列表
    clear_exit(ADMIN_FEATURE_EXIT_X1, ADMIN_FEATURE_EXIT_Y1, ADMIN_FEATURE_EXIT_X2, ADMIN_FEATURE_EXIT_Y2);
    clear_flip_up(ADMIN_FEATURE_UP_X1, ADMIN_FEATURE_UP_Y1, ADMIN_FEATURE_UP_X2, ADMIN_FEATURE_UP_Y2);
    clear_flip_down(ADMIN_FEATURE_DOWN_X1, ADMIN_FEATURE_DOWN_Y1, ADMIN_FEATURE_DOWN_X2, ADMIN_FEATURE_DOWN_Y2);
}

void drawgraph_admin_database(void)
{
    puthz(ADMIN_INTERFACE_X1 + 15, ADMIN_INTERFACE_Y1 + 5, "数据一览", 24, 20, MY_WHITE);
    draw_cues(ADMIN_BUTTON6_X2 + 10, ADMIN_BUTTON6_Y1, NULL, NULL); // 绘制箭头，标明当前打开页面为此

    setfillstyle(SOLID_FILL, MY_YELLOW);
    bar(ADMIN_FEATURE1_X1, ADMIN_FEATURE1_Y1, ADMIN_FEATURE1_X2, ADMIN_FEATURE1_Y2);
    bar(ADMIN_FEATURE2_X1, ADMIN_FEATURE2_Y1, ADMIN_FEATURE2_X2, ADMIN_FEATURE2_Y2);
    bar(ADMIN_FEATURE3_X1, ADMIN_FEATURE3_Y1, ADMIN_FEATURE3_X2, ADMIN_FEATURE3_Y2);
    bar(ADMIN_FEATURE4_X1, ADMIN_FEATURE4_Y1, ADMIN_FEATURE4_X2, ADMIN_FEATURE4_Y2);
    bar(ADMIN_FEATURE5_X1, ADMIN_FEATURE5_Y1, ADMIN_FEATURE5_X2, ADMIN_FEATURE5_Y2);
    bar(ADMIN_FEATURE6_X1, ADMIN_FEATURE6_Y1, ADMIN_FEATURE6_X2, ADMIN_FEATURE6_Y2);
    puthz(ADMIN_FEATURE1_X1 + 4, ADMIN_FEATURE1_Y1 + 8, "用户信息", 16, 16, MY_WHITE);
    puthz(ADMIN_FEATURE2_X1 + 4, ADMIN_FEATURE2_Y1 + 8, "车辆信息", 16, 16, MY_WHITE);
    puthz(ADMIN_FEATURE3_X1 + 4, ADMIN_FEATURE3_Y1 + 8, "出入统计", 16, 16, MY_WHITE);

    setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
    bar(ADMIN_FEATURE_SEARCH_X1, ADMIN_FEATURE_SEARCH_Y1, ADMIN_FEATURE_SEARCH_X2, ADMIN_FEATURE_SEARCH_Y2);
    setcolor(MY_BLACK);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    rectangle(ADMIN_FEATURE_SEARCH_X1, ADMIN_FEATURE_SEARCH_Y1, ADMIN_FEATURE_SEARCH_X2, ADMIN_FEATURE_SEARCH_Y2);

    setlinestyle(SOLID_LINE, 0, THICK_WIDTH); // 小放大镜，提示为搜索框
    line(ADMIN_FEATURE_SEARCH_X1 + 5, ADMIN_FEATURE_SEARCH_Y2 - 7, ADMIN_FEATURE_SEARCH_X1 + 12, ADMIN_FEATURE_SEARCH_Y2 - 14);
    circle(ADMIN_FEATURE_SEARCH_X1 + 16, ADMIN_FEATURE_SEARCH_Y2 - 18, 5);

    // setfillstyle(SOLID_FILL,MY_GREEN);
    // bar(ADMIN_INTERFACE_X1+10,ADMIN_INTERFACE_Y1+70,ADMIN_INTERFACE_X1+500,ADMIN_INTERFACE_Y1+390); // 清理列表
    clear_exit(ADMIN_FEATURE_EXIT_X1, ADMIN_FEATURE_EXIT_Y1, ADMIN_FEATURE_EXIT_X2, ADMIN_FEATURE_EXIT_Y2);
    clear_flip_up(ADMIN_FEATURE_UP_X1, ADMIN_FEATURE_UP_Y1, ADMIN_FEATURE_UP_X2, ADMIN_FEATURE_UP_Y2);
    clear_flip_down(ADMIN_FEATURE_DOWN_X1, ADMIN_FEATURE_DOWN_Y1, ADMIN_FEATURE_DOWN_X2, ADMIN_FEATURE_DOWN_Y2);
}

void drawgraph_admin_database_user_info(void)
{
    settextstyle(SCRIPT_FONT, HORIZ_DIR, 1);
    setcolor(MY_RED);
    outtextxy(ADMIN_INTERFACE_X1 + 100, ADMIN_INTERFACE_Y1,"-");
    puthz(ADMIN_INTERFACE_X1 + 115, ADMIN_INTERFACE_Y1 + 10, "用户信息", 16, 16, MY_WHITE);

    setfillstyle(SOLID_FILL, MY_YELLOW);
    bar(ADMIN_FEATURE6_X1, ADMIN_FEATURE6_Y1, ADMIN_FEATURE6_X2, ADMIN_FEATURE6_Y2);
    puthz(ADMIN_FEATURE6_X1 + 4, ADMIN_FEATURE6_Y1 + 8, "修改信息", 16, 16, MY_WHITE); // 显示新按钮

    puthz(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 40, "学号", 16, 16, MY_WHITE);
    puthz(ADMIN_INTERFACE_X1 + 120, ADMIN_INTERFACE_Y1 + 40, "账号", 16, 16, MY_WHITE);
    puthz(ADMIN_INTERFACE_X1 + 240, ADMIN_INTERFACE_Y1 + 40, "密码", 16, 16, MY_WHITE);
    puthz(ADMIN_INTERFACE_X1 + 360, ADMIN_INTERFACE_Y1 + 40, "注册时间", 16, 16, MY_WHITE);
    puthz(ADMIN_INTERFACE_X1 + 460, ADMIN_INTERFACE_Y1 + 40, "状态", 16, 16, MY_WHITE);
}

void drawgraph_admin_info(unsigned long ID)
{
    char buffer[20]; // 用于存储格式化后的字符串

    puthz(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 20, "你好！", 24, 30, MY_WHITE); // 输出文本

    sprintf(buffer, "%lu", ID); // 将 ID 转换为字符串
    setcolor(MY_WHITE);
    settextstyle(SCRIPT_FONT, HORIZ_DIR, 2);
    outtextxy(ADMIN_INTERFACE_X1 + 110, ADMIN_INTERFACE_Y1 + 16, buffer); // 输出名称
}

void draw_person(int x1,int y1,int x2,int y2){
    setfillstyle(SOLID_FILL, MY_YELLOW);
    bar(x1 - 3, y1 - 3, x2 + 3, y2 + 3);
    setcolor(MY_BLACK);
    setfillstyle(SOLID_FILL, MY_BLACK);
    pieslice(x1+10, y1 +7, 0, 360, 6);   // 绘制人头
    pieslice(x1+10, y1 + 22, 0, 180, 11); // 绘制身体
}
void clear_person(int x1,int y1,int x2,int y2){
    setfillstyle(SOLID_FILL, MY_YELLOW);
    bar(x1 - 3, y1 - 3, x2 + 3, y2 + 3);
    setcolor(MY_BLACK);
    setfillstyle(SOLID_FILL, MY_BLACK);
    pieslice(x1+10, y1 +7, 0, 360, 5);   // 绘制人头
    pieslice(x1+10, y1 + 22, 0, 180, 10); // 绘制身体
}

void draw_cues(int x, int y,int null1,int null2){
    setcolor(MY_GREEN);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    line(x-10,y+23,x,y+23);
    line(x-5,y+18,x,y+23);
    line(x-5,y+28,x,y+23);
}
void clear_cues(int x1, int y1, int x2, int y2){
    setfillstyle(SOLID_FILL, MY_YELLOW);
    bar(x1-13,y1+6,x2-79,y2);
}

void draw_rectangle(int x1,int y1,int x2,int y2){
    setcolor(MY_WHITE);
    setlinestyle(SOLID_LINE,0,NORM_WIDTH);
    rectangle(x1-2,y1-2,x2+2,y2+2);
}

void clear_rectangle(int x1,int y1,int x2,int y2){
    setcolor(MY_LIGHTGRAY);
    setlinestyle(SOLID_LINE,0,NORM_WIDTH);
    rectangle(x1-2,y1-2,x2+2,y2+2);
}

void draw_exit(int x1,int y1,int x2,int y2){
    setcolor(MY_RED);
    setlinestyle(SOLID_LINE,0,THICK_WIDTH);
    line(x1,y1,x2,y2);
    line(x2,y1,x1,y2);
}
void clear_exit(int x1,int y1,int x2,int y2){
    setfillstyle(SOLID_FILL,MY_YELLOW);
    bar(x1-1,y1-1,x2+1,y2+1);

    setcolor(MY_RED);
    setlinestyle(SOLID_LINE,0,NORM_WIDTH);
    line(x1,y1,x2,y2);
    line(x2,y1,x1,y2);
}

void draw_exit_menu(int x1,int y1,int x2,int y2){
    setcolor(MY_BLACK);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    rectangle(x1,y1,x2,y2);
    puthz(x1+2,y1+7,"退出登录",16,16,MY_WHITE);
    puthz(x1+2,y1+29,"退出程序",16,16,MY_WHITE);
}
void clear_exit_menu(int x1,int y1,int x2,int y2){
    setfillstyle(SOLID_FILL,MY_YELLOW);
    bar(x1,y1,x2,y2);
}

void draw_flip_up(int x1, int y1, int x2, int y2)
{
    setcolor(BLACK);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    line(ADMIN_FEATURE_UP_X1, ADMIN_FEATURE_UP_Y1 + 10, ADMIN_FEATURE_UP_X2, ADMIN_FEATURE_UP_Y1);
    line(ADMIN_FEATURE_UP_X1, ADMIN_FEATURE_UP_Y1 + 10, ADMIN_FEATURE_UP_X2, ADMIN_FEATURE_UP_Y2); // 切换页面 <
}
void draw_flip_down(int x1, int y1, int x2, int y2)
{
    setcolor(BLACK);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    line(ADMIN_FEATURE_DOWN_X2, ADMIN_FEATURE_DOWN_Y1 + 10, ADMIN_FEATURE_DOWN_X1, ADMIN_FEATURE_DOWN_Y1);
    line(ADMIN_FEATURE_DOWN_X2, ADMIN_FEATURE_DOWN_Y1 + 10, ADMIN_FEATURE_DOWN_X1, ADMIN_FEATURE_DOWN_Y2); // 切换页面 >
}
void clear_flip_up(int x1, int y1, int x2, int y2)
{
    setcolor(MY_YELLOW);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    line(ADMIN_FEATURE_UP_X1, ADMIN_FEATURE_UP_Y1 + 10, ADMIN_FEATURE_UP_X2, ADMIN_FEATURE_UP_Y1);
    line(ADMIN_FEATURE_UP_X1, ADMIN_FEATURE_UP_Y1 + 10, ADMIN_FEATURE_UP_X2, ADMIN_FEATURE_UP_Y2); // 切换页面 <
}
void clear_flip_down(int x1, int y1, int x2, int y2)
{
    setcolor(MY_YELLOW);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    line(ADMIN_FEATURE_DOWN_X2, ADMIN_FEATURE_DOWN_Y1 + 10, ADMIN_FEATURE_DOWN_X1, ADMIN_FEATURE_DOWN_Y1);
    line(ADMIN_FEATURE_DOWN_X2, ADMIN_FEATURE_DOWN_Y1 + 10, ADMIN_FEATURE_DOWN_X1, ADMIN_FEATURE_DOWN_Y2); // 切换页面 >
}



// 这个函数可能还需要进一步优化，若之后出现画面抽搐的问题尚不能解决，就干这个函数
// 2025.3.19 出错：连个静态变量索引导入结构体数组导致越界。通过将其定义值改为0暂时解
// 2025.4.4 将按钮初始化模块化后，又出现了类似问题。交给AI处理后，该函数添加了一些防指针越界的语句，暂时解决了问题
void admin_flush_buttons(int *tag, int button_counts, ADMIN_BUTTONS AdminButtons[])
{
    int i;
    int new_tag = ACTIVE_ADMIN_NULL;
    static int last_active_index = 0;
    static int current_active_index = 0;

    // 检查按钮数量是否合法
    if (button_counts <= 0 || !AdminButtons)
    {
        return;
    }

    // 检查鼠标是否在任一按钮区域内
    for (i = 0; i < button_counts; i++)
    {
        if (MouseX >= AdminButtons[i].x1 && MouseX <= AdminButtons[i].x2 &&
            MouseY >= AdminButtons[i].y1 && MouseY <= AdminButtons[i].y2)
        {
            new_tag = AdminButtons[i].active_tag;
            last_active_index = current_active_index;
            current_active_index = i;
            break;
        }
    }

    // 状态变化时更新
    if (*tag != new_tag)
    {
        *tag = new_tag;
        if (new_tag != ACTIVE_ADMIN_NULL)
        {
            // 绘制提示（同时清除上一次高光提示）
            if (last_active_index >= 0 && last_active_index < button_counts)
            {
                AdminButtons[last_active_index].clearfunc(
                    AdminButtons[last_active_index].x1,
                    AdminButtons[last_active_index].y1,
                    AdminButtons[last_active_index].x2,
                    AdminButtons[last_active_index].y2);
            }
            if (current_active_index >= 0 && current_active_index < button_counts)
            {
                AdminButtons[current_active_index].drawfunc(
                    AdminButtons[current_active_index].x1,
                    AdminButtons[current_active_index].y1,
                    AdminButtons[current_active_index].x2,
                    AdminButtons[current_active_index].y2);
            }
            last_active_index = current_active_index;
            MouseS = 1;
        }
        else
        {
            // 清除提示
            if (last_active_index >= 0 && last_active_index < button_counts)
            {
                AdminButtons[last_active_index].clearfunc(
                    AdminButtons[last_active_index].x1,
                    AdminButtons[last_active_index].y1,
                    AdminButtons[last_active_index].x2,
                    AdminButtons[last_active_index].y2);
                last_active_index = -1;
            }
            MouseS = 0;
        }
    }
}

/*****************************************************************
MODULE:该源文件全局可使用的函数模块
*****************************************************************/
// 列表函数，用于列出相应
void admin_list_info(LINKLIST *LIST, unsigned long id_list[8], FILE *fp, char *file_type, char *list_mode, int search_mode,
                                  int page_change, int is_clear, char *search_str, char *search_needed)
{
    // file_type指明文件类型
    // page_change为1，向下列表，为-1，向上列表，为0，不翻页
    // mode为0，查找未处理，为1，查找已处理
    // is_clear为0，不做任何操作，为1，清理列表状态并不做任何操作，为2，清理列表状态并继续列表（重新开始列表）
    //         为3，从记录的start开始扫描重新列表（需搭配page_change=1使用）
    // list_mode为列表依据，"register"为列出注册请求，"license"为列出上牌请求, "broken"为列出报废请求， "violation"为列出违规请求
    // search_mode为搜过模式，0代表搜索未处理，1代表搜索已处理
    // search_str为搜索字符串，search_needed为搜索依据

    /* 1.定义变量 */
    int i;
    int listed_item = 0;  // 列出的数量
    static unsigned int start = 0; // 储存当前列表第一个所在的位置
    static unsigned int end = 0;   // 储存当前列表最后一个所在的位置
    unsigned int temp_start = 0;
    unsigned int temp_end = 0;  // 储存临时的列表第一个和最后一个位置
    int counts = 0; // 记录文件长度
    int valid_counts = 0;
    int flag = -1; // 记录文件类型，值>=0
    unsigned int page_count = 0;  // 记录页面数量，值>=0
    static unsigned int page_index = 0; // 记录搜索开始的位置
    char buffer[10];
    EBIKE_INFO ebike_temp;
    USER_LOGIN_DATA user_temp;

    if(debug_mode == 1){
        bar(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 40, ADMIN_INTERFACE_X1 + 100, ADMIN_INTERFACE_Y1 + 140); // 清理列表
        puthz(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 40, "检查一", 16, 16, MY_RED);
    }
        
    /* 2.判断数据类型 */
    if(strcmp(file_type,"ebike_manage")==0){
        flag = ADMIN_DATABASE_EBIKE_MANAGE;
    }else if(strcmp(file_type,"user_data")==0){
        flag = ADMIN_DATABASE_USER_INFO;
    }else if(strcmp(file_type,"ebike_info")==0){
        flag = ADMIN_DATABASE_EBIKE_INFO;
    }else if(strcmp(file_type,"ebike_pass_in_out")==0){
        flag = ADMIN_DATABASE_EBIKE_PASS_IN_OUT; 
    }else {
        return; // 若指明文件类型错误，则不做任何操作 
    }

    if (debug_mode == 1)
        puthz(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 60, "检查二", 16, 16, MY_RED);

    /* 3.获取文件长度 */
    fseek(fp, 0, SEEK_END);
    if (flag == ADMIN_DATABASE_EBIKE_MANAGE)
        counts = ftell(fp) / sizeof(EBIKE_INFO);
    else if (flag == ADMIN_DATABASE_USER_INFO)
        counts = ftell(fp) / sizeof(USER_LOGIN_DATA);

    // 计算有效数据量 valid_counts
    valid_counts = counts;
    if ((strcmp(search_str, "\0") != 0 || strcmp(search_needed, "\0") != 0)){
        valid_counts = 0;
        fseek(fp, 0, SEEK_SET);
        switch (flag){
            case ADMIN_DATABASE_EBIKE_MANAGE:
            {
                for (i = 0; i < counts; i++)
                {
                    fread(&ebike_temp, sizeof(EBIKE_INFO), 1, fp);
                    if (list_ebike_manage_is_valid(ebike_temp, list_mode, search_str, search_needed, search_mode))
                    {
                        valid_counts++;
                    }
                }
            }
            case ADMIN_DATABASE_USER_INFO:
            {
                for (i = 0; i < counts; i++)
                {
                    fread(&user_temp, sizeof(USER_LOGIN_DATA), 1, fp);
                    if (list_user_data_is_valid(user_temp, search_str, search_needed))
                    {
                        valid_counts++;
                    }
                } 
            }
        }
    }

    // 计算页面数量时使用 valid_counts
    page_count = valid_counts / 8 + (valid_counts % 8 ? 1 : 0);
    if (page_count < 1)
        page_index = 0;


    /* 4.初始化列表记录 */
    for (i = 0; i < 8; i++)
    {
        id_list[i] = 0;
    }
    
    /* 5.判断是否需要清理或刷新列表 */
    switch (is_clear)
    {
    case 1:
        setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
        bar(ADMIN_INTERFACE_X1 + 10, ADMIN_INTERFACE_Y1 + 70, ADMIN_INTERFACE_X1 + 500, ADMIN_INTERFACE_Y1 + 300); // 清理列表
        start = 0;
        end = 0;
        page_index = 1;
        return;
    case 2:
        setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
        bar(ADMIN_INTERFACE_X1 + 10, ADMIN_INTERFACE_Y1 + 70, ADMIN_INTERFACE_X1 + 500, ADMIN_INTERFACE_Y1 + 300); // 清理列表
        start = 0;
        end = 0;
        page_index = 1;
        break;
    case 3:
        setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
        bar(ADMIN_INTERFACE_X1 + 10, ADMIN_INTERFACE_Y1 + 70, ADMIN_INTERFACE_X1 + 500, ADMIN_INTERFACE_Y1 + 300); // 清理列表
        end = start;                                                                                               // 从start开始扫描重新列表
        break;
    default:
        break;
    }

    if (debug_mode == 1)
        puthz(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 80, "检查三", 16, 16, MY_RED);

    /* 6.前置操作完成，正式开始列表 */
    if (valid_counts > 0 && page_change == LIST_PAGEDOWN)
    { // 收到下翻指令，或改变当前列表状态后从起点开始重新刷新列表

        if (debug_mode == 1)
            puthz(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 100, "检查四", 16, 16, MY_RED);

        /* 条件判断 */
        if (end >= valid_counts - 1)
        {
            return; // 如果end指向结尾的数据，则不做任何操作
        }


        if (flag == ADMIN_DATABASE_EBIKE_MANAGE)
            fseek(fp, (end + 1) * sizeof(ebike_temp), SEEK_SET);
        else if (flag == ADMIN_DATABASE_USER_INFO)
            fseek(fp, (end + 1) * sizeof(user_temp), SEEK_SET); // 先判断接下来是否有可以列出的数据
            
        while (1)
        {
            if (flag == ADMIN_DATABASE_EBIKE_MANAGE)
            {
                if (!fread(&ebike_temp, sizeof(ebike_temp), 1, fp)) // 读取下一个数据块
                {
                    return; // 到文件末尾都没有发现可列表的，则不执行下翻列表操作
                }
                if (list_ebike_manage_is_valid(ebike_temp, list_mode, search_str, search_needed, search_mode)){
                    break; // 下翻查找是一旦读到可以被列出的，则可以执行下翻列表操作
                }
            }
            else if (flag == ADMIN_DATABASE_USER_INFO)
            {
                // 读取下一个数据块
                if (!fread(&user_temp, sizeof(user_temp), 1, fp))
                {
                    return; // 到文件末尾都没有发现可列表的，则不执行下翻列表操作
                }
                if (list_user_data_is_valid(user_temp, search_str, search_needed))
                {
                    break; // 下翻查找是一旦读到可以被列出的，则可以执行下翻列表操作}
                }
            }
        }

        if (debug_mode == 1)
            puthz(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 120, "检查五", 16, 16, MY_RED);

        /* 列表操作 */
        start = ++end;
        setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
        bar(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 70, ADMIN_INTERFACE_X1 + 500, ADMIN_INTERFACE_Y1 + 300); // 清理列表
        list_show_page_index(++page_index, page_count); // 显示页码

        while (listed_item < 8)
        {
            if (flag == ADMIN_DATABASE_EBIKE_MANAGE)
            {
                fseek(fp, (end) * sizeof(ebike_temp), SEEK_SET);
                if (!fread(&ebike_temp, sizeof(ebike_temp), 1, fp)){
                    end--; // 若读取到文件末尾，则将end指向文件末尾的前一个数据块，防止越界
                    puthz(ADMIN_INTERFACE_X1 + 190, ADMIN_INTERFACE_Y1 + 70 + listed_item * LIST_INTERVAL, "没有更多数据了哦！", 16, 16, MY_RED);
                    break; // 读取数据，直到达到文件末尾
                }
                if (!list_ebike_manage_is_valid(ebike_temp, list_mode, search_str, search_needed, search_mode)){
                    end++;
                    continue; // 如果下翻读取时读到的数据不符条件，则进行下一轮循环
                }
                    
                admin_show_ebike_manage_info(ebike_temp, listed_item, list_mode, ASCENDING); // 输出数据
                id_list[listed_item] = ebike_temp.ID;
            }

            else if (flag == ADMIN_DATABASE_USER_INFO)
            {
                fseek(fp, (end) * sizeof(user_temp), SEEK_SET);
                if (!fread(&user_temp, sizeof(user_temp), 1, fp)){
                    end--; // 若读取到文件末尾，则将end指向文件末尾的前一个数据块，防止越界
                    puthz(ADMIN_INTERFACE_X1 + 190, ADMIN_INTERFACE_Y1 + 70 + listed_item * LIST_INTERVAL, "没有更多数据了哦！", 16, 16, MY_RED);
                    break; // 读取数据，直到达到文件末尾
                }
                if (!list_user_data_is_valid(user_temp, search_str, search_needed)){
                    end++;
                    continue; // 如果下翻读取时读到的数据不符条件，则进行下一轮循环 
                }
                    
                admin_show_user_info(user_temp, listed_item, list_mode, ASCENDING); // 输出数据
                id_list[listed_item] = user_temp.ID;
            }
            
            listed_item++;
            if(listed_item < 8 || end < counts) end++; // 将end指向读取的数据的头部
            
        }
        return;
    }
    else if (valid_counts > 0 && page_change == LIST_PAGEUP)
    { // 收到上翻指令

        if (debug_mode == 1)
            puthz(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 100, "检查四", 16, 16, MY_RED);

        /*条件判断*/
        if (start <= 0)
        {
            return; // 如果start指向开头的数据，则不做任何操作
        }
        temp_start = start;
        temp_end = start - 1;
        
        while (1)
        { // 当能进入这个循环，说明列表上页有可列出数据且溢出
            if (flag == ADMIN_DATABASE_EBIKE_MANAGE)
            {
                if(fseek(fp, (--temp_start) * sizeof(ebike_temp), SEEK_SET)){
                    return; // 到文件开头都没有发现可列表的，则不执行上翻列表操作
                }
                fread(&ebike_temp, sizeof(ebike_temp), 1, fp); // 读取上一个数据块
                
                if (list_ebike_manage_is_valid(ebike_temp, list_mode, search_str, search_needed, search_mode)){
                    break; // 上翻查找到一个可列出数据，则可以上翻
                }
                temp_end = --temp_start;
            }
            else if (flag == ADMIN_DATABASE_USER_INFO)
            {
                if (fseek(fp, (--temp_start) * sizeof(user_temp), SEEK_SET)) // 读取上一个数据块，当文件指针尝试移动到负数时，fseek会返回非零数
                {
                    return; // 到文件开头都没有发现可列表的，则不执行上翻列表操作
                }
                fread(&user_temp, sizeof(user_temp), 1, fp); // 读取上一个数据块
                
                if (list_user_data_is_valid(user_temp, search_str, search_needed))
                {
                    break;
                }
                temp_end = --temp_start;
            }
        }

        // 此处 temp_start 和 temp_end 都应为 start - 1 或更小//
        if(debug_mode == 1)
            puthz(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 120, "检查五", 16, 16, MY_RED);

        /*列表操作*/
        start = temp_start; // 查找到首个可以读取的数据，将实际的标记指向该数据
        end = temp_end;
        setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
        bar(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 70, ADMIN_INTERFACE_X1 + 500, ADMIN_INTERFACE_Y1 + 300); // 清理列表
        list_show_page_index(--page_index, page_count); // 更新页面索引

        while (listed_item < 8)
        { // 由于此时是从后往前读取数据，因此是从下往上列表
            if (flag == ADMIN_DATABASE_EBIKE_MANAGE)
            {
                fseek(fp, (start) * sizeof(ebike_temp), SEEK_SET);
                fread(&ebike_temp, sizeof(ebike_temp), 1, fp); // 读取数据，直到查找到未被处理的注册请求
                if (!list_ebike_manage_is_valid(ebike_temp, list_mode, search_str, search_needed, search_mode)){
                    start--;
                    continue; // 如果下翻读取时读到的数据不符条件，则进行下一轮循环
                }
                    
                admin_show_ebike_manage_info(ebike_temp, listed_item, list_mode, DESCENDING); // 输出数据
                id_list[7 - listed_item] = ebike_temp.ID;                                     // 记录ID
            }
            else if (flag == ADMIN_DATABASE_USER_INFO)
            {
                fseek(fp, (start) * sizeof(user_temp), SEEK_SET);
                fread(&user_temp, sizeof(user_temp), 1, fp);
                if (!list_user_data_is_valid(user_temp, search_str, search_needed)){
                    start--;
                    continue; // 如果下翻读取时读到的数据不符条件，则进行下一轮循环 
                }

                admin_show_user_info(user_temp, listed_item, list_mode, DESCENDING); // 输出数据
                id_list[7 - listed_item] = user_temp.ID;                             // 记录ID
            }
            
            listed_item++;
            if (listed_item < 8 || start > 0) start--; // start在后面条件自减，防止start越界
            else if(start == 0)
                break; // 若start指向开头，则不执行上翻列表操作，防止start越界
        }
        return;
    }
    else if (valid_counts > 0 && page_change == LIST_STAY)
    { // 不翻页，输出原内容

        if (debug_mode == 1)
            puthz(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 100, "检查四", 16, 16, MY_RED);

        end = start; // end不能赋为负数，因为end为无符号整形数

        setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
        bar(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 70, ADMIN_INTERFACE_X1 + 500, ADMIN_INTERFACE_Y1 + 300); // 清理列表
        list_show_page_index(page_index, page_count); // 显示页码

        while (listed_item < 8)
        {
            if (flag == ADMIN_DATABASE_EBIKE_MANAGE)
            {
                fseek(fp, (start + listed_item) * sizeof(ebike_temp), SEEK_SET);
                if (!fread(&ebike_temp, sizeof(ebike_temp), 1, fp)){
                    end--; // 若读取到文件末尾，则将end指向文件末尾的前一个数据块，防止越界
                    puthz(ADMIN_INTERFACE_X1 + 190, ADMIN_INTERFACE_Y1 + 70 + listed_item * LIST_INTERVAL, "没有更多数据了哦！", 16, 16, MY_RED);
                    return; // 读取数据，直到达到文件末尾
                } // 读取数据，直到查找到八个可列出数据

                if (!list_ebike_manage_is_valid(ebike_temp, list_mode, search_str, search_needed, search_mode)){
                    end++; // end指数+1
                    continue; // 如果下翻读取时读到的数据不符条件，则进行下一轮循环
                }
                    
                admin_show_ebike_manage_info(ebike_temp, listed_item, list_mode, ASCENDING); // 输出数据

                id_list[listed_item] = ebike_temp.ID;
            }
            else if (flag == ADMIN_DATABASE_USER_INFO)
            {
                fseek(fp, (end) * sizeof(user_temp), SEEK_SET); 
                // 此处不要传入start + listed_item，因为listed_item可能一直不会改变，导致读取的数据不会改变，进入死循环 2025.4.8
                if (!fread(&user_temp, sizeof(user_temp), 1, fp)){
                    end--; // 若读取到文件末尾，则将end指向文件末尾的前一个数据块，防止越界
                    puthz(ADMIN_INTERFACE_X1 + 190, ADMIN_INTERFACE_Y1 + 70 + listed_item * LIST_INTERVAL, "没有更多数据了哦！", 16, 16, MY_RED);
                    return;
                } // 读取数据，直到查找到八个可列出数据

                if (!list_user_data_is_valid(user_temp, search_str, search_needed)){
                    end++; // end指数+1
                    continue; // 如果下翻读取时读到的数据不符条件，则进行下一轮循环 
                }

                admin_show_user_info(user_temp, listed_item, list_mode, ASCENDING); // 输出数据

                id_list[listed_item] = user_temp.ID;
            }
            
            listed_item++;
            if(listed_item < 8) end++; // 将end指向读取的数据的头部
        }
        return;
    }
    else
    {
        list_show_page_index(0, 0);
        puthz(ADMIN_INTERFACE_X1 + 120, ADMIN_INTERFACE_Y1 + 70, "未找到对应数据或传入参数错误", 16, 16, MY_RED);
        return;
    }
    
    // 到函数末尾都还没返回，则出现异常，则输出异常信息
    puthz(ADMIN_INTERFACE_X1 + 120, ADMIN_INTERFACE_Y1 + 70, "函数执行异常", 16, 16, MY_RED);
}

/// 输出数据函数
void admin_show_ebike_manage_info(EBIKE_INFO TEMP, int listed_item, char *list_mode, int list_sequence)
{
    char buffer[50];
    itoa(TEMP.ID, buffer, 10); // 将ID转换为字符串

    if (list_sequence == ASCENDING)
    {
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

        if (strcmp(list_mode, "register") == 0 || strcmp(list_mode, "license") || strcmp(list_mode,"anual")){
            puthz(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 70 + listed_item * 20, TEMP.rln, 16, 16, MY_WHITE); // 输出姓名
            outtextxy(ADMIN_INTERFACE_X1 + 100, ADMIN_INTERFACE_Y1 + 70 + listed_item * LIST_INTERVAL, buffer);        // 输出ID
            outtextxy(ADMIN_INTERFACE_X1 + 200, ADMIN_INTERFACE_Y1 + 70 + listed_item * LIST_INTERVAL, TEMP.ebike_ID); // 输出电动车车牌号
        }else if (strcmp(list_mode, "broken") == 0 || strcmp(list_mode, "violation") == 0){
            outtextxy(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 70 + listed_item * LIST_INTERVAL, buffer);        // 输出ID
            outtextxy(ADMIN_INTERFACE_X1 + 100, ADMIN_INTERFACE_Y1 + 70 + listed_item * LIST_INTERVAL, TEMP.ebike_ID); // 输出电动车车牌号
            outtextxy(ADMIN_INTERFACE_X1 + 200, ADMIN_INTERFACE_Y1 + 70 + listed_item * LIST_INTERVAL, TEMP.location); // 输出地址
        }

        outtextxy(ADMIN_INTERFACE_X1 + 300, ADMIN_INTERFACE_Y1 + 70 + listed_item * LIST_INTERVAL, buffer); // 输出请求时间

        if (TEMP.conduct_time == -1)
        { // 输出处理状态
            puthz(ADMIN_INTERFACE_X1 + 400, ADMIN_INTERFACE_Y1 + 70 + listed_item * LIST_INTERVAL, "未处理", 16, 16, MY_RED);
        }
        else
        {
            puthz(ADMIN_INTERFACE_X1 + 400, ADMIN_INTERFACE_Y1 + 70 + listed_item * LIST_INTERVAL, "已处理", 16, 16, MY_GREEN);
        }
    }
    else if (list_sequence == DESCENDING)
    {
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

        if (strcmp(list_mode, "register") == 0 || strcmp(list_mode, "license") == 0 || strcmp(list_mode,"anual")){
            puthz(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 310 - listed_item * LIST_INTERVAL, TEMP.rln, 16, 16, MY_WHITE); // 输出姓名
            outtextxy(ADMIN_INTERFACE_X1 + 100, ADMIN_INTERFACE_Y1 + 310 - listed_item * LIST_INTERVAL, buffer);        // 输出ID
            outtextxy(ADMIN_INTERFACE_X1 + 200, ADMIN_INTERFACE_Y1 + 310 - listed_item * LIST_INTERVAL, TEMP.ebike_ID); 
        }else if(strcmp(list_mode, "broken") == 0 || strcmp(list_mode, "violation") == 0){
            outtextxy(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 310 - listed_item * LIST_INTERVAL, buffer);        // 输出ID
            outtextxy(ADMIN_INTERFACE_X1 + 200, ADMIN_INTERFACE_Y1 + 310 - listed_item * LIST_INTERVAL, TEMP.ebike_ID); // 输出电动车车牌号
            outtextxy(ADMIN_INTERFACE_X1 + 300, ADMIN_INTERFACE_Y1 + 310 - listed_item * LIST_INTERVAL, TEMP.location); // 输出地址
        }

        outtextxy(ADMIN_INTERFACE_X1 + 300, ADMIN_INTERFACE_Y1 + 310 - listed_item * LIST_INTERVAL, buffer);        // 输出请求时间

        if (TEMP.conduct_time == -1)
        { // 输出处理状态
            puthz(ADMIN_INTERFACE_X1 + 400, ADMIN_INTERFACE_Y1 + 310 - listed_item * LIST_INTERVAL, "未处理", 16, 16, MY_RED);
        }
        else
        {
            puthz(ADMIN_INTERFACE_X1 + 400, ADMIN_INTERFACE_Y1 + 310 - listed_item * LIST_INTERVAL, "已处理", 16, 16, MY_GREEN);
        }
    }
    else
        return; // 如果传入参数错误，则不做任何操作
}

void admin_show_user_info(USER_LOGIN_DATA TEMP, int listed_item, char *list_mode, int list_sequence){
    char buffer1[20];
    char buffer2[20];

    setcolor(MY_WHITE);
    if (list_sequence == ASCENDING){
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
        ltoa(TEMP.ID, buffer1, 10);                                                              // 将ID转换为字符串
        outtextxy(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 74 + listed_item * LIST_INTERVAL, buffer1); // 输出ID
        outtextxy(ADMIN_INTERFACE_X1 + 120, ADMIN_INTERFACE_Y1 + 74 + listed_item * LIST_INTERVAL, TEMP.usrn); // 输出用户名
        outtextxy(ADMIN_INTERFACE_X1 + 240, ADMIN_INTERFACE_Y1 + 74 + listed_item * LIST_INTERVAL, TEMP.psw);  // 输出密码
        ltoa(TEMP.register_time, buffer1, 10);
        sprintf(buffer2, "%.4s.%.2s.%.2s", buffer1, buffer1 + 4, buffer1 + 6);                                 // 将注册时间转换为字符串
        outtextxy(ADMIN_INTERFACE_X1 + 360, ADMIN_INTERFACE_Y1 + 74 + listed_item * LIST_INTERVAL, buffer2); // 输出注册时间
        if (TEMP.state == ACTIVE){
            puthz(ADMIN_INTERFACE_X1 + 460, ADMIN_INTERFACE_Y1 + 70 + listed_item * LIST_INTERVAL, "活跃", 16, 16, MY_GREEN);
        }
        else if(TEMP.state == FROZEN){
            puthz(ADMIN_INTERFACE_X1 + 460, ADMIN_INTERFACE_Y1 + 70 + listed_item * LIST_INTERVAL, "冻结", 16, 16, MY_LIGHTBLUE);
        }
        else if (TEMP.state == BANNED){
            puthz(ADMIN_INTERFACE_X1 + 460, ADMIN_INTERFACE_Y1 + 70 + listed_item * LIST_INTERVAL, "封禁", 16, 16, MY_RED);
        }
        delay(25); // 延时25ms，使列表的动画更有动感
    }
    else if (list_sequence == DESCENDING){
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
        ltoa(TEMP.ID, buffer1, 10);                                                               // 将ID转换为字符串
        outtextxy(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 284 - listed_item * LIST_INTERVAL, buffer1); // 输出ID
        outtextxy(ADMIN_INTERFACE_X1 + 120, ADMIN_INTERFACE_Y1 + 284 - listed_item * LIST_INTERVAL, TEMP.usrn); // 输出用户名
        outtextxy(ADMIN_INTERFACE_X1 + 240, ADMIN_INTERFACE_Y1 + 284 - listed_item * LIST_INTERVAL, TEMP.psw);  // 输出密码
        ltoa(TEMP.register_time, buffer1, 10);
        sprintf(buffer2, "%.4s.%.2s.%.2s", buffer1, buffer1+4, buffer1+6);                                        // 将注册时间转换为字符串
        outtextxy(ADMIN_INTERFACE_X1 + 360, ADMIN_INTERFACE_Y1 + 284 - listed_item * LIST_INTERVAL, buffer2); // 输出注册时间
        if (TEMP.state == ACTIVE){
            puthz(ADMIN_INTERFACE_X1 + 460, ADMIN_INTERFACE_Y1 + 280 - listed_item * LIST_INTERVAL, "活跃", 16, 16, MY_GREEN);
        }
        else if(TEMP.state == FROZEN){
            puthz(ADMIN_INTERFACE_X1 + 460, ADMIN_INTERFACE_Y1 + 280 - listed_item * LIST_INTERVAL, "冻结", 16, 16, MY_LIGHTBLUE);
        }
        else if (TEMP.state == BANNED){
            puthz(ADMIN_INTERFACE_X1 + 460, ADMIN_INTERFACE_Y1 + 280 - listed_item * LIST_INTERVAL, "封禁", 16, 16, MY_RED);
        }
        delay(25); // 延时25ms，使列表的动画更有动感
    }
}


// 判断一个数据块是否应该列出
int list_ebike_manage_is_valid(EBIKE_INFO TEMP, char *list_mode, char *search_str, char *search_needed, int search_mode)
{
    if (
        (TEMP.conduct_time != -1 && search_mode == 0 || TEMP.conduct_time > 0 && search_mode == 1) &&
        (!strcmp(list_mode, "register") || !strcmp(list_mode, "license") || !strcmp(list_mode, "anual") ||
         !strcmp(list_mode, "broken") || !strcmp(list_mode, "violation")) &&
        (!strcmp(search_str, "\0") || TEMP.ID == atol(search_str) && !strcmp(search_needed, "ID"))
    )
        return 1;
    else
        return 0;
}
int list_user_data_is_valid(USER_LOGIN_DATA TEMP, char *search_str, char *search_needed)
{
    if (
        ((!strcmp(search_str, "\0") || TEMP.ID == atol(search_str) && !strcmp(search_needed, "ID")))
    )
        return 1;
    else
        return 0;
}

void list_show_page_index(unsigned int page_index, unsigned int page_count){
    char buffer[20];

    setcolor(MY_WHITE);
    setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
    bar(ADMIN_INTERFACE_X1 + 460, ADMIN_INTERFACE_Y1 + 300, ADMIN_INTERFACE_X1 + 500, ADMIN_INTERFACE_Y1 + 320); // 清理页码
    sprintf(buffer, "<%d/%d>", page_index, page_count);                                                          // 格式化页码
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    outtextxy(ADMIN_INTERFACE_X1 + 460, ADMIN_INTERFACE_Y1 + 310, buffer); // 输出页码
}

//绘制选中的行的图形动画，同时返回选中行对应数据的id
unsigned long handle_list_select_line_admin(unsigned long *id_list)
{
    int i;
    for (i = 0; i < LIST_LIMIT; i++)
    {
        if (mouse_press(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 70 + i * LIST_INTERVAL,
                        ADMIN_INTERFACE_X1 + 400, ADMIN_INTERFACE_Y1 + 70 + (i + 1) * LIST_INTERVAL - 1) == 1 &&
            id_list[i] != 0)
        {
            setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
            bar(ADMIN_INTERFACE_X1 + 10, ADMIN_INTERFACE_Y1 + 70, ADMIN_INTERFACE_X1 + 18, ADMIN_INTERFACE_Y1 + 310); // 清理所有高亮
            setfillstyle(SOLID_FILL, MY_YELLOW);
            bar(ADMIN_INTERFACE_X1 + 10, ADMIN_INTERFACE_Y1 + 70 + i * LIST_INTERVAL,
                ADMIN_INTERFACE_X1 + 18, ADMIN_INTERFACE_Y1 + 70 + (i + 1) * LIST_INTERVAL - 1); // 生成当前高亮

            setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
            bar(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 70 + 8 * LIST_INTERVAL,
                ADMIN_INTERFACE_X1 + 400, ADMIN_INTERFACE_Y1 + 70 + 8 * LIST_INTERVAL + 20); // 清理选中行具体信息
            
            return id_list[i];
        }
    }
    return NULL;
}


// 查找文件中是否存在指定内容，并返回该数据块位置
unsigned long int find_ebike_info(FILE *fp,char *search_str,char *search_needed){
    int counts;
    unsigned long int pos;
    unsigned long int search_pos = 0;
    EBIKE_INFO TEMP;

    pos = ftell(fp); // 记录当前文件指针位置，以便后续返回

    fseek(fp,0,SEEK_END);
    counts = ftell(fp) / sizeof(EBIKE_INFO);
    fseek(fp,0,SEEK_SET); // 获取文件长度
    
    while(fread(&TEMP,sizeof(EBIKE_INFO),1,fp)){
        if(TEMP.ID == NULL){
            fseek(fp, pos, SEEK_SET); // 将文件指针移回原先位置
            return 0;
        } // 查找到文件结束时仍未找到，则返回0
            

        if ((strcmp(search_needed, "realname") == 0 && strcmp(TEMP.rln, search_str) == 0) ||
            (strcmp(search_needed, "id") == 0 && TEMP.ID == atol(search_str)) ||
            (strcmp(search_needed, "ebike_id") == 0 && strcmp(TEMP.ebike_ID, search_str) == 0) ||
            (strcmp(search_needed, "ebike_license") == 0 && strcmp(TEMP.ebike_license, search_str) == 0) ||
            (strcmp(search_needed, "location") == 0 && strcmp(TEMP.location, search_str) == 0) ||
            (strcmp(search_needed, "apply_time") == 0 && TEMP.apply_time == atol(search_str)) ||
            (strcmp(search_needed, "conduct_time") == 0 && TEMP.conduct_time == atol(search_str)) ||
            (strcmp(search_needed, "result") == 0 && TEMP.result == atoi(search_str))
            )
        {
            fseek(fp, -sizeof(EBIKE_INFO), SEEK_CUR); // 将文件指针移动到对应数据前
            search_pos = ftell(fp);                   // 记录数据块位置
            fseek(fp, pos, SEEK_SET);                 // 将文件指针移回原先位置
            break;
        } // 查找到后，跳出循环
    }

    return search_pos; // 文件指针位置返回到原先位置
}

// 点击按钮后，若能成功操作，则执行该显示动画
void admin_pass_failed_anime(int button_x1, int button_y1, int button_x2, int button_y2,int result)
{
    int tick = 0;
    clrmous(MouseX, MouseY); // 清除鼠标

    for (tick = 0; tick <= 80; tick++)
    {
        if (tick % 40 == 0)
        {
            setfillstyle(SOLID_FILL, GREEN);
            bar(button_x1, button_y1, button_x2, button_y2);
            if(result == PASSED)
                puthz(button_x1 + 4, button_y1 + 8, "通过成功", 16, 16, MY_WHITE); // 绘制按钮
            else if(result == FAILED)
                puthz(button_x1 + 4, button_y1 + 8, "驳回成功", 16, 16, MY_WHITE); // 绘制按钮
        }
        else if (tick % 40 == 20)
        {
            setfillstyle(SOLID_FILL, MY_YELLOW);
            bar(button_x1, button_y1, button_x2, button_y2);
            if(result == PASSED)
                puthz(button_x1 + 4, button_y1 + 8, "通过成功", 16, 16, MY_WHITE); // 绘制按钮
            else if(result == FAILED)
                puthz(button_x1 + 4, button_y1 + 8, "通过成功", 16, 16, MY_WHITE); // 绘制按钮
        }
        delay(25);
    }
    setfillstyle(SOLID_FILL, MY_YELLOW);
    bar(button_x1, button_y1, button_x2, button_y2);                  // 重绘按钮
    puthz(button_x1 + 4, button_y1 + 8, "同意申请", 16, 16, MY_WHITE); // 重新绘制按钮        

    newmouse(&MouseX, &MouseY, &press); // 重新绘制
}

void define_admin_buttons(ADMIN_BUTTONS AdminButtons[], int button_counts)
{
    ADMIN_BUTTONS Examples[] = {
        {ADMIN_BUTTON1_X1, ADMIN_BUTTON1_X2,
         ADMIN_BUTTON1_Y1, ADMIN_BUTTON1_Y2,
         ACTIVE_ADMIN_BUTTON1, &draw_cues, &clear_cues},
        {ADMIN_BUTTON2_X1, ADMIN_BUTTON2_X2,
         ADMIN_BUTTON2_Y1, ADMIN_BUTTON2_Y2,
         ACTIVE_ADMIN_BUTTON2, &draw_cues, &clear_cues},
        {ADMIN_BUTTON3_X1, ADMIN_BUTTON3_X2,
         ADMIN_BUTTON3_Y1, ADMIN_BUTTON3_Y2,
         ACTIVE_ADMIN_BUTTON3, &draw_cues, &clear_cues},
        {ADMIN_BUTTON4_X1, ADMIN_BUTTON4_X2,
         ADMIN_BUTTON4_Y1, ADMIN_BUTTON4_Y2,
         ACTIVE_ADMIN_BUTTON4, &draw_cues, &clear_cues},
        {ADMIN_BUTTON5_X1, ADMIN_BUTTON5_X2,
         ADMIN_BUTTON5_Y1, ADMIN_BUTTON5_Y2,
         ACTIVE_ADMIN_BUTTON5, &draw_cues, &clear_cues},
        {ADMIN_BUTTON6_X1, ADMIN_BUTTON6_X2,
         ADMIN_BUTTON6_Y1, ADMIN_BUTTON6_Y2,
         ACTIVE_ADMIN_BUTTON6, &draw_cues, &clear_cues},
        {ADMIN_BUTTON7_X1, ADMIN_BUTTON7_X2,
         ADMIN_BUTTON7_Y1, ADMIN_BUTTON7_Y2,
         ACTIVE_ADMIN_BUTTON7, &draw_cues, &clear_cues},
        {ADMIN_EXIT_X1, ADMIN_EXIT_X2,
         ADMIN_EXIT_Y1, ADMIN_EXIT_Y2,
         ACTIVE_ADMIN_EXIT, &draw_exit, &clear_exit},
        {ADMIN_INFO_X1, ADMIN_INFO_X2,
         ADMIN_INFO_Y1, ADMIN_INFO_Y2,
         ACTIVE_ADMIN_INFO, &draw_person, &clear_person},
        {ADMIN_FEATURE1_X1, ADMIN_FEATURE1_X2,
         ADMIN_FEATURE1_Y1, ADMIN_FEATURE1_Y2,
         ACTIVE_ADMIN_FEATURE1, &draw_rectangle, &clear_rectangle},
        {ADMIN_FEATURE2_X1, ADMIN_FEATURE2_X2,
         ADMIN_FEATURE2_Y1, ADMIN_FEATURE2_Y2,
         ACTIVE_ADMIN_FEATURE2, &draw_rectangle, &clear_rectangle},
        {ADMIN_FEATURE3_X1, ADMIN_FEATURE3_X2,
         ADMIN_FEATURE3_Y1, ADMIN_FEATURE3_Y2,
         ACTIVE_ADMIN_FEATURE3, &draw_rectangle, &clear_rectangle},
        {ADMIN_FEATURE4_X1, ADMIN_FEATURE4_X2,
         ADMIN_FEATURE4_Y1, ADMIN_FEATURE4_Y2,
         ACTIVE_ADMIN_FEATURE4, &draw_rectangle, &clear_rectangle},
        {ADMIN_FEATURE5_X1, ADMIN_FEATURE5_X2,
         ADMIN_FEATURE5_Y1, ADMIN_FEATURE5_Y2,
         ACTIVE_ADMIN_FEATURE5, &draw_rectangle, &clear_rectangle},
        {ADMIN_FEATURE6_X1, ADMIN_FEATURE6_X2,
         ADMIN_FEATURE6_Y1, ADMIN_FEATURE6_Y2,
         ACTIVE_ADMIN_FEATURE6, &draw_rectangle, &clear_rectangle},
        {ADMIN_FEATURE_EXIT_X1, ADMIN_FEATURE_EXIT_X2,
         ADMIN_FEATURE_EXIT_Y1, ADMIN_FEATURE_EXIT_Y2,
         ACTIVE_ADMIN_FEATURE_EXIT, &draw_exit, &clear_exit},
        {ADMIN_FEATURE_SEARCH_X1, ADMIN_FEATURE_SEARCH_X2,
         ADMIN_FEATURE_SEARCH_Y1, ADMIN_FEATURE_SEARCH_Y2,
         ACTIVE_ADMIN_FEATURE_SEARCH, &draw_rectangle, &clear_rectangle},
        {ADMIN_FEATURE_UP_X1, ADMIN_FEATURE_UP_X2,
         ADMIN_FEATURE_UP_Y1, ADMIN_FEATURE_UP_Y2,
         ACTIVE_ADMIN_FEATURE_UP, &draw_flip_up, &clear_flip_up},
        {ADMIN_FEATURE_DOWN_X1, ADMIN_FEATURE_DOWN_X2,
         ADMIN_FEATURE_DOWN_Y1, ADMIN_FEATURE_DOWN_Y2,
         ACTIVE_ADMIN_FEATURE_DOWN, &draw_flip_down, &clear_flip_down}};
    int i;
    for (i = 0; i < button_counts; i++)
    {
        if(i >= STRUCT_LENGTH(Examples))
            break;
        AdminButtons[i].x1 = Examples[i].x1;
        AdminButtons[i].x2 = Examples[i].x2;
        AdminButtons[i].y1 = Examples[i].y1;
        AdminButtons[i].y2 = Examples[i].y2;
        AdminButtons[i].active_tag = Examples[i].active_tag;
        AdminButtons[i].drawfunc = Examples[i].drawfunc;
        AdminButtons[i].clearfunc = Examples[i].clearfunc;
    }
}

void admin_handle_buttons_event(int *page)
{
    /*返回主界面或退出程序*/
    if (mouse_press(ADMIN_EXIT_X1, ADMIN_EXIT_Y1, ADMIN_EXIT_X2, ADMIN_EXIT_Y2) == 1)
    {
        if (!admin_exitting(page))
        {
            AdminswitchPage();
            return;
        }
    }
    /*查看个人信息*/
    if (mouse_press(ADMIN_INFO_X1, ADMIN_INFO_Y1, ADMIN_INFO_X2, ADMIN_INFO_Y2) == 1)
    {
        if (*page != ADMIN_INFO)
        {
            *page = ADMIN_INFO;
            return;
        }
    }

    /*车辆注册*/
    if (mouse_press(ADMIN_BUTTON1_X1, ADMIN_BUTTON1_Y1, ADMIN_BUTTON1_X2, ADMIN_BUTTON1_Y2) == 1 &&
        *page != ADMIN_BIKE_REGISTER)
    {
        *page = ADMIN_BIKE_REGISTER;
        return;
    }
    /*车辆上牌*/
    if (mouse_press(ADMIN_BUTTON2_X1, ADMIN_BUTTON2_Y1, ADMIN_BUTTON2_X2, ADMIN_BUTTON2_Y2) == 1 &&
        *page != ADMIN_BIKE_LICENSE)
    {
        *page = ADMIN_BIKE_LICENSE;
        return;
    }
    /*车辆报废*/
    if (mouse_press(ADMIN_BUTTON3_X1, ADMIN_BUTTON3_Y1, ADMIN_BUTTON3_X2, ADMIN_BUTTON3_Y2) == 1 &&
        *page != ADMIN_BIKE_BROKEN)
    {
        *page = ADMIN_BIKE_BROKEN;
        return;
    }
    /*车辆违规*/
    if (mouse_press(ADMIN_BUTTON4_X1, ADMIN_BUTTON4_Y1, ADMIN_BUTTON4_X2, ADMIN_BUTTON4_Y2) == 1 &&
        *page != ADMIN_BIKE_VIOLATION)
    {
        *page = ADMIN_BIKE_VIOLATION;
        return;
    }
    /*车辆年审*/
    if (mouse_press(ADMIN_BUTTON5_X1, ADMIN_BUTTON5_Y1, ADMIN_BUTTON5_X2, ADMIN_BUTTON5_Y2) == 1 &&
        *page != ADMIN_BIKE_ANUAL)
    {
        *page = ADMIN_BIKE_ANUAL;
        return;
    }

    /*数据一揽*/
    if (mouse_press(ADMIN_BUTTON6_X1, ADMIN_BUTTON6_Y1, ADMIN_BUTTON6_X2, ADMIN_BUTTON6_Y2) == 1 &&
        *page!= ADMIN_DATABASE)
    {
        *page = ADMIN_DATABASE;
        return; 
    }
}

void admin_handle_manage_feature_event(LINKLIST *LIST, int *page, char *search_str, unsigned long *id_list, FILE *fp_EBIKE_INFO_read, int *mode, int selected_id)
{
    int i;
    char list_mode[10]; // 列表依据
    char buffer[50];
    EBIKE_INFO temp_info;
    LINKLIST_NODE *temp_node = LIST->HEAD; // LAST_NODE要找到链表中特定节点，先指向头结点
    int chain_pos = -1;                    // 链表位置

    unsigned long int search_pos = 0; // 查找数据得到的位置

    // 根据不同的页面，以不同的方式调用列表函数
    switch (*page)
    {
    case ADMIN_BIKE_REGISTER:
        strcpy(list_mode, "register");
        break;
    case ADMIN_BIKE_LICENSE:
        strcpy(list_mode, "license");
        break;
    case ADMIN_BIKE_VIOLATION:
        strcpy(list_mode, "violation");
        break;
    case ADMIN_BIKE_ANUAL:
        strcpy(list_mode, "annual");
        break;
    case ADMIN_BIKE_BROKEN:
        strcpy(list_mode, "broken");
        break;
    }

    if (mouse_press(ADMIN_FEATURE_EXIT_X1, ADMIN_FEATURE_EXIT_Y1, ADMIN_FEATURE_EXIT_X2, ADMIN_FEATURE_EXIT_Y2) == 1)
    {
        *page = MAIN_ADMIN;
    } // 当在功能界面点击叉，退出功能界面

    if (mouse_press(ADMIN_FEATURE_SEARCH_X1, ADMIN_FEATURE_SEARCH_Y1, ADMIN_FEATURE_SEARCH_X2, ADMIN_FEATURE_SEARCH_Y2) == 1)
    {
        Input_Bar(search_str, ADMIN_FEATURE_SEARCH_X1 + 25, ADMIN_FEATURE_SEARCH_Y1 + 2, 9, MY_LIGHTGRAY, 0, 1);

        selected_id = -1; // 清除选中行
        setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
        bar(ADMIN_INTERFACE_X1 + 10, ADMIN_INTERFACE_Y1 + 70, ADMIN_INTERFACE_X1 + 18, ADMIN_INTERFACE_Y1 + 310); // 清理所有选中行高亮

        admin_list_info(LIST, id_list, fp_EBIKE_INFO_read, "ebike_manage", list_mode, *mode, 0, 2, search_str, "ID"); // 搜索后刷新列表

    } // 点击输入框后退回

    if (mouse_press(ADMIN_FEATURE3_X1, ADMIN_FEATURE3_Y1, ADMIN_FEATURE3_X2, ADMIN_FEATURE3_Y2) == 1 &&
        *mode == 0)
    {
        *mode = 1;
        setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
        bar(ADMIN_INTERFACE_X1 + 140, ADMIN_INTERFACE_Y1 + 10, ADMIN_INTERFACE_X1 + 230, ADMIN_INTERFACE_Y1 + 30);
        puthz(ADMIN_INTERFACE_X1 + 140, ADMIN_INTERFACE_Y1 + 10, "已处理项目", 16, 16, MY_WHITE);
        admin_list_info(LIST, id_list, fp_EBIKE_INFO_read, "ebike_manage", list_mode, *mode, LIST_STAY, LIST_CLEAR_CONTINUE, search_str, "ID");
    } // 点击已处理后显示已处理

    if (mouse_press(ADMIN_FEATURE4_X1, ADMIN_FEATURE4_Y1, ADMIN_FEATURE4_X2, ADMIN_FEATURE4_Y2) == 1 &&
        *mode == 1)
    {
        *mode = 0;
        setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
        bar(ADMIN_INTERFACE_X1 + 140, ADMIN_INTERFACE_Y1 + 10, ADMIN_INTERFACE_X1 + 230, ADMIN_INTERFACE_Y1 + 30);
        puthz(ADMIN_INTERFACE_X1 + 140, ADMIN_INTERFACE_Y1 + 10, "未处理项目", 16, 16, MY_WHITE);
        admin_list_info(LIST, id_list, fp_EBIKE_INFO_read, "ebike_manage", list_mode, *mode, LIST_STAY, LIST_CLEAR_CONTINUE, search_str, "ID");
    } // 点击未处理后显示未处理

    // 点击同意申请
    if (mouse_press(ADMIN_FEATURE1_X1, ADMIN_FEATURE1_Y1, ADMIN_FEATURE1_X2, ADMIN_FEATURE1_Y2) == 1 && selected_id != -1)
    {
        itoa(selected_id, buffer, 10);                                  // 将选中行的ID转化为字符串
        if ((chain_pos = linklist_find_data(LIST, buffer, "id")) == -1) // 查找链表中是否存在该ID，若找不到，则不进行任何操作
            return;

        search_pos = find_ebike_info(fp_EBIKE_INFO_read, buffer, "id"); // 查找数据块
        if (search_pos == 0)
            return; // 如果没有找到数据块，则不进行任何操作，若能找到，则进一步处理数据

        // 修改数据块
        
        fread(&temp_info, sizeof(EBIKE_INFO), 1, fp_EBIKE_INFO_read);                     // 读取数据块
        temp_info.conduct_time = get_approx_time(NULL);                                   // 将时间字符串转化为int型数据，并赋值给conduct_time
        temp_info.result = PASSED;                                                        // 将result赋值为已处理

        fseek(fp_EBIKE_INFO_read, search_pos, SEEK_SET);               // 定位到数据块
        fwrite(&temp_info, sizeof(EBIKE_INFO), 1, fp_EBIKE_INFO_read); // 将新数据写入数据块

        // 修改链表数据
        for (i = 0; i < chain_pos; i++)
        {
            temp_node = temp_node->NEXT; // 遍历链表，找到对应节点
        }
        // 根据不同的页面，修改链表中对应节点的特定数据
        switch (*page)
        {
        case ADMIN_BIKE_REGISTER:
            strcpy(temp_node->USER_DATA.ebike_ID, temp_info.ebike_ID); // 将链表中对应节点的ebike_ID修改为新数据
            break;
        case ADMIN_BIKE_LICENSE:
            strcpy(temp_node->USER_DATA.ebike_license, temp_info.ebike_license); // 将链表中对应节点的ebike_license修改为新数据
            break;
        case ADMIN_BIKE_VIOLATION:
            temp_node->USER_DATA.violations++;
            ; // 将链表中对应节点的violations加1
            break;
        case ADMIN_BIKE_ANUAL:
            temp_node->USER_DATA.anual_check += 10000; // 将链表中对应节点的annual加10000(10000表示数字中表示年的部分加1)
            break;
        case ADMIN_BIKE_BROKEN:
            temp_node->USER_DATA.ebike_state = BROKEN; // 将链表中对应节点的ebike_state修改为BROKEN
            break;
        }
        linklist_write_user_data(LIST); // 将链表数据写入文件

        admin_pass_failed_anime(ADMIN_FEATURE1_X1, ADMIN_FEATURE1_Y1, ADMIN_FEATURE1_X2, ADMIN_FEATURE1_Y2, PASSED); // 操作成功后的动画

        admin_list_info(LIST, id_list, fp_EBIKE_INFO_read, "ebike_manage", list_mode, *mode, LIST_PAGEDOWN, LIST_FLUSH, "\0", "\0"); // 操作结束后刷新列表
    }

    // 点击拒绝申请
    if (mouse_press(ADMIN_FEATURE2_X1, ADMIN_FEATURE2_Y1, ADMIN_FEATURE2_X2, ADMIN_FEATURE2_Y2) == 1 && selected_id != -1)
    {
        itoa(selected_id, buffer, 10);
        if (!(chain_pos = linklist_find_data(LIST, buffer, "id")))
            return; // 选中行，点击同意申请，若出现未能找到数据的情况，则不进行任何操作

        search_pos = find_ebike_info(fp_EBIKE_INFO_read, buffer, "id"); // 查找数据块
        if (search_pos == 0)
            return; // 如果没有找到数据块，则不进行任何操作，若能找到，则进一步处理数据

        // 修改数据块
        fread(&temp_info, sizeof(EBIKE_INFO), 1, fp_EBIKE_INFO_read);                     // 读取数据块
        temp_info.conduct_time = get_approx_time(NULL);                                              // 将时间字符串转化为int型数据，并赋值给conduct_time
        temp_info.result = FAILED;                                                        // 将result赋值为已处理

        fseek(fp_EBIKE_INFO_read, search_pos, SEEK_SET);               // 定位到数据块
        fwrite(&temp_info, sizeof(EBIKE_INFO), 1, fp_EBIKE_INFO_read); // 将新数据写入数据块

        // 申请失败，不修改链表数据

        admin_pass_failed_anime(ADMIN_FEATURE1_X1, ADMIN_FEATURE1_Y1, ADMIN_FEATURE1_X2, ADMIN_FEATURE1_Y2, FAILED); // 操作成功后的动画

        admin_list_info(LIST, id_list, fp_EBIKE_INFO_read, "ebike_manage", list_mode, *mode, LIST_PAGEDOWN, LIST_FLUSH, "\0", "\0"); // 操作结束后刷新列表
    }
    temp_node = NULL; // 释放指针
}

void admin_handle_database_event(LINKLIST *LIST, int *flag , int *page, unsigned long *id_list, FILE *fp, char *search_str)
{
    char file_type[20];

    switch (*flag){ // 枚举情况，在数据库中不会单独打开五个特性功能的文件，所以不列举ebike_manage
        case ADMIN_DATABASE_USER_INFO:
            strcpy(file_type, "user_data");
            break;
        case ADMIN_DATABASE_EBIKE_INFO:
            strcpy(file_type, "ebike_data");
            break;
        case ADMIN_DATABASE_EBIKE_PASS_IN_OUT:
            strcpy(file_type, "ebike_pass_in_out");
            break;
        case ADMIN_DATABASE_NULL:
            break;
        default:
            return; // 不正确的文件类型标志，不做任何操作
    }

    /*点击退出按钮*/
    if (mouse_press(ADMIN_FEATURE_EXIT_X1, ADMIN_FEATURE_EXIT_Y1, ADMIN_FEATURE_EXIT_X2, ADMIN_FEATURE_EXIT_Y2) == 1)
    {
        *page = MAIN_ADMIN;
        return;
    }
    /*点击用户信息*/
    if (mouse_press(ADMIN_FEATURE1_X1, ADMIN_FEATURE1_Y1, ADMIN_FEATURE1_X2, ADMIN_FEATURE1_Y2) == 1 &&
        *flag != ADMIN_DATABASE_USER_INFO)
    {
        drawgraph_admin_database_user_info();
        *flag = ADMIN_DATABASE_USER_INFO;
        strcpy(file_type, "user_data");
        admin_list_info(LIST, id_list, fp, file_type, NULL, NULL, LIST_STAY, LIST_CLEAR_CONTINUE, search_str, "ID");
        return;
    }
    /*点击车辆信息*/
    if (mouse_press(ADMIN_FEATURE2_X1, ADMIN_FEATURE2_Y1, ADMIN_FEATURE2_X2, ADMIN_FEATURE2_Y2) == 1 &&
        *flag != ADMIN_DATABASE_EBIKE_INFO)
    {
        *flag = ADMIN_DATABASE_EBIKE_INFO;
        return;
    }
    /*点击车辆出入信息*/
    if (mouse_press(ADMIN_FEATURE3_X1, ADMIN_FEATURE3_Y1, ADMIN_FEATURE3_X2, ADMIN_FEATURE3_Y2) == 1 &&
        *flag != ADMIN_DATABASE_EBIKE_PASS_IN_OUT)
    {
        *flag = ADMIN_DATABASE_EBIKE_PASS_IN_OUT;
        return;
    }
    /*点击翻页*/
    if (mouse_press(ADMIN_FEATURE_UP_X1, ADMIN_FEATURE_UP_Y1, ADMIN_FEATURE_UP_X2, ADMIN_FEATURE_UP_Y2) == 1){
        admin_list_info(LIST, id_list, fp, file_type, NULL, NULL, LIST_PAGEUP, LIST_NO_CLEAR, search_str, "ID");
        return;
    }
    if (mouse_press(ADMIN_FEATURE_DOWN_X1, ADMIN_FEATURE_DOWN_Y1, ADMIN_FEATURE_DOWN_X2, ADMIN_FEATURE_DOWN_Y2) == 1){
        admin_list_info(LIST, id_list, fp, file_type, NULL, NULL, LIST_PAGEDOWN, LIST_NO_CLEAR, search_str, "ID");
        return;
    }
    /*点击搜索框*/
    if (mouse_press(ADMIN_FEATURE_SEARCH_X1, ADMIN_FEATURE_SEARCH_Y1, ADMIN_FEATURE_SEARCH_X2, ADMIN_FEATURE_SEARCH_Y2) == 1)
    {
        Input_Bar(search_str, ADMIN_FEATURE_SEARCH_X1 + 25, ADMIN_FEATURE_SEARCH_Y1 + 2, 9, MY_LIGHTGRAY, 0, 1);

        admin_list_info(LIST, id_list, fp, file_type, NULL, NULL, LIST_STAY, LIST_CLEAR_CONTINUE, search_str, "ID"); // 搜索后刷新列表
        return;
    }
}

int admin_exitting(int *page)
{
    draw_exit_menu(ADMIN_EXIT_MENU_X1, ADMIN_EXIT_MENU_Y1, ADMIN_EXIT_MENU_X2, ADMIN_EXIT_MENU_Y2);
    while (1)
    {
        newmouse(&MouseX, &MouseY, &press);
        if (mouse_press(ADMIN_EXIT_MENU_X1 + 2, ADMIN_EXIT_MENU_Y1 + 5, ADMIN_EXIT_MENU_X1 + 60, ADMIN_EXIT_MENU_Y1 + 21) == 1)
        {
            *page = LOGIN_ADMIN;
            admin_list_info(NULL, NULL, NULL, NULL, NULL, NULL, NULL, LIST_CLEAR, NULL, NULL);
            Input_Bar(NULL, NULL, NULL, NULL, NULL, INPUTBAR_CLEAR, NULL);
            return 0;
        }
        else if (mouse_press(ADMIN_EXIT_MENU_X1 + 2, ADMIN_EXIT_MENU_Y1 + 30, ADMIN_EXIT_MENU_X1 + 60, ADMIN_EXIT_MENU_Y1 + 46) == 1)
        {
            *page = EXIT;
            admin_list_info(NULL, NULL, NULL, NULL, NULL, NULL, NULL, LIST_CLEAR, NULL, NULL);
            Input_Bar(NULL, NULL, NULL, NULL, NULL, INPUTBAR_CLEAR, NULL);
            return 0;
        }
        else if (mouse_press(0, 0, 640, 480) == 1 && mouse_press(ADMIN_EXIT_X1, ADMIN_EXIT_Y1, ADMIN_EXIT_X2, ADMIN_EXIT_Y2) == -1)
        {
            clear_exit_menu(ADMIN_EXIT_MENU_X1, ADMIN_EXIT_MENU_Y1, ADMIN_EXIT_MENU_X2, ADMIN_EXIT_MENU_Y2);
            return 1;
        }
    }
}

void AdminswitchPage()
{
    int i, j, k;
    setfillstyle(SOLID_FILL, MY_LIGHTBLUE);
    for (i = 0; i < 16; i++)
        for (j = 0; j < 12; j++)
            for (k = 0; k <= 5; k++)
            {
                bar(i * 40 + 20 - k * 4, j * 40 + 20 - k * 4, i * 40 + 20 + k * 4, j * 40 + 20 + k * 4);
                delay(1);
            }
}
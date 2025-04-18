#include"_ADMIN_.H"

/*****************************************************************
MODULE:管理员主菜单
*****************************************************************/
void main_admin(int *page,unsigned long *ID){
    int mouse_flag;
    int tag=ACTIVE_ADMIN_NULL;
    ADMIN_BUTTONS AdminButtons[9];
    define_admin_buttons(AdminButtons, MAIN_ADMIN); // 定义按钮

    clrmous(MouseX, MouseY);
    drawgraph_admin_menu(); // 初始化界面
    mouseinit();

    if(debug_mode == 1) display_memory_usage(400, 10); // 显示调试参数

    while(*page == MAIN_ADMIN){
        newmouse_data(&MouseX, &MouseY, &press, &mouse_flag);

        admin_flush_buttons(&tag,STRUCT_LENGTH(AdminButtons),AdminButtons);
        admin_handle_buttons_event(page);
        //应该在传入AdminButtons前计算其长度，传入函数后，使用sizeof计算其长度则会退化为指针长度，导致功能失效

        newmouse(&MouseX, &MouseY, &press, &mouse_flag);

        delay(25);
    }
    
}

/*****************************************************************
MODULE:管理员车辆管理模块
*****************************************************************/
void admin_manage_bike_module(int *page, unsigned long *ID, LINKLIST *LIST, char *file_path, char *list_mode){
    int mouse_flag;
    int mode = 0; // 搜索模式，列出已处理清单或待处理清单，主动清除该页面时重设为0（默认列出待处理清单）
    // static int visited=0; // 是否进入乐该页面，主动清除该页面时重设为0
    char search_str[20]; // 搜索框输入信息储存
    unsigned long selected_id = 0;
    unsigned long id_list[8] = {0,0,0,0,0,0,0,0}; // 记录当前显示的列表每行对应的ID
    int tag = ACTIVE_ADMIN_NULL;
    int temp_page = *page; // 记录当前页面
    ADMIN_BUTTONS AdminButtons[19];
    FILE *fp_EBIKE_INFO_read = fopen(file_path, "rb+");
    if (!fp_EBIKE_INFO_read)
        exit(1);

    define_admin_buttons(AdminButtons, *page); // 定义按钮

    fseek(fp_EBIKE_INFO_read, 0, SEEK_SET);
    drawgraph_admin_menu();
    drawgraph_admin_feature(*page);

    // 列出数据
    admin_list_info(LIST, LIST_LIMIT, LIST_INTERVAL, id_list, fp_EBIKE_INFO_read, "ebike_manage", 
                    list_mode, mode, LIST_PAGEDOWN, LIST_CLEAR_CONTINUE, "\0", "\0");

    if (debug_mode == 1)
        display_memory_usage(400, 10); // 显示调试参数

    while (*page == temp_page)
    {
        newmouse_data(&MouseX, &MouseY, &press, &mouse_flag);

        admin_flush_buttons(&tag, STRUCT_LENGTH(AdminButtons), AdminButtons);
        admin_handle_buttons_event(page);
        handle_list_select_line_admin(LIST, id_list, &selected_id, LIST_LIMIT, LIST_INTERVAL);
        admin_handle_manage_feature_event(LIST, page, search_str, id_list, fp_EBIKE_INFO_read, &mode, &selected_id); // 处理点击事件

        newmouse(&MouseX, &MouseY, &press, &mouse_flag);

        delay(25);
    }

    admin_list_info(NULL, LIST_LIMIT, LIST_INTERVAL, NULL, NULL, NULL, NULL, NULL, NULL, LIST_CLEAR, NULL, NULL);
    ch_input(NULL, NULL, NULL, NULL, NULL, INPUTBAR_CLEAR, NULL);
    fclose(fp_EBIKE_INFO_read);
    return;
}

/*****************************************************************
MODULE:查看管理员信息
*****************************************************************/
void admin_info(int *page, unsigned long *ID){
    int mouse_flag;
    int tag = ACTIVE_ADMIN_NULL;
    ADMIN_BUTTONS AdminButtons[9];
    define_admin_buttons(AdminButtons, *page); // 定义按钮
    clrmous(MouseX, MouseY);
    drawgraph_admin_menu(); // 初始化界面

    if (debug_mode == 1)
        display_memory_usage(400, 10); // 显示调试参数

    while(*page == ADMIN_INFO){
        newmouse_data(&MouseX, &MouseY, &press, &mouse_flag);

        admin_flush_buttons(&tag,STRUCT_LENGTH(AdminButtons),AdminButtons);
        admin_handle_buttons_event(page);
        newmouse(&MouseX, &MouseY, &press, &mouse_flag);

        drawgraph_admin_info(*ID); // 显示管理员信息

        delay(25);
    }
}

/*****************************************************************
MODULE:数据一览界面
*****************************************************************/
void admin_database(int *page, unsigned long *ID , LINKLIST *LIST){
    int mouse_flag;
    int tag = ACTIVE_ADMIN_NULL;
    int flag = ADMIN_DATABASE_NULL; // 数据一览视图代号
    unsigned long selected_id = 0;
    unsigned long id_list[8] = {0,0,0,0,0,0,0,0}; // 记录当前显示的列表每行对应的ID
    char search_str[20] = "\0"; // 搜索框输入信息储存
    ADMIN_BUTTONS AdminButtons[19];
    FILE *fp_USER_LOGIN_DATA_read = fopen("DATA\\USER.DAT", "rb+"); // 打开用户登录数据文件
    if (!fp_USER_LOGIN_DATA_read){
        getch(), exit(1);
    }
    // 列出车辆信息时，通过链表获取数据，因此不定义文件指针

    define_admin_buttons(AdminButtons, *page); // 定义按钮 
    clrmous(MouseX, MouseY);
    drawgraph_admin_menu(); // 绘制界面
    drawgraph_admin_database();

    if (debug_mode == 1)
        display_memory_usage(400, 10); // 显示调试参数

    while (*page == ADMIN_DATABASE){
        newmouse_data(&MouseX, &MouseY, &press, &mouse_flag);

        admin_flush_buttons(&tag, STRUCT_LENGTH(AdminButtons), AdminButtons);
        admin_handle_buttons_event(page);
        admin_handle_database_event(LIST, &flag, page, id_list, fp_USER_LOGIN_DATA_read,search_str, &selected_id); // 处理点击事件
        handle_list_select_line_admin(LIST, id_list, &selected_id, LIST_LIMIT, LIST_INTERVAL);

        newmouse(&MouseX, &MouseY, &press, &mouse_flag);

        delay(25);
    }

    admin_list_info(NULL, LIST_LIMIT, LIST_INTERVAL, NULL, NULL, NULL, NULL, NULL, NULL, LIST_CLEAR, NULL, NULL); // 清除列表
    ch_input(NULL, NULL, NULL, NULL, NULL, INPUTBAR_CLEAR, NULL);
    fclose(fp_USER_LOGIN_DATA_read);
}

void admin_modify_data(LINKLIST *LIST, FILE *fp, char *file_type, unsigned long *user_id)
{
    int mouse_flag;
    int tag = ACTIVE_ADMIN_NULL;
    int flag = -1;
    int isReturn = 0; // 是否返回;
    ADMIN_BUTTONS AdminButtons[12];

    define_admin_buttons(AdminButtons, ADMIN_MODIFY_DATA_USER_INFO); // 定义按钮

    if(strcmp(file_type, "user_data") == 0){ // 修改用户信息
        flag = ADMIN_DATABASE_USER_INFO;
    }else if(strcmp(file_type, "ebike_data") == 0){ // 修改车辆信息
        flag = ADMIN_DATABASE_EBIKE_INFO;
    }else { // 错误
        return;
    }

    clrmous(MouseX, MouseY);
    if (drawgraph_admin_modify_data(fp, LIST, flag, *user_id) == 0) // 绘制界面
    {
        delay(1000);
        clrmous(MouseX, MouseY);
        drawgraph_admin_menu(); // 绘制界面
        drawgraph_admin_database();
        drawgraph_admin_database_user_info();
        return;
    }
    newmouse(&MouseX, &MouseY, &press, &mouse_flag);

    if (debug_mode == 1)
        display_memory_usage(400, 10); // 显示调试参数

    while (!isReturn){
        newmouse_data(&MouseX, &MouseY, &press, &mouse_flag);

        if(flag = ADMIN_DATABASE_USER_INFO){ // 修改用户信息
            admin_flush_buttons(&tag, 6, AdminButtons);
            admin_handle_modify_user_data_event(fp, user_id, &isReturn); // 处理点击事件
        }
        else if(flag = ADMIN_DATABASE_EBIKE_INFO){ // 修改车辆信息
            admin_flush_buttons(&tag, 6, AdminButtons);
            admin_handle_modify_ebike_data_event(LIST, user_id, &isReturn); // 处理点击事件
        }

        newmouse(&MouseX, &MouseY, &press, &mouse_flag);
        delay(25);
    }
    clrmous(MouseX, MouseY);
    drawgraph_admin_menu(); // 绘制界面
    drawgraph_admin_database();
    drawgraph_admin_database_user_info();
}


/*****************************************************************
MODULE:管理员消息中心
*****************************************************************/
void admin_message_center(int *page, unsigned long *ID){
    int mouse_flag;
    int tag = ACTIVE_ADMIN_NULL;
    ADMIN_BUTTONS AdminButtons[12];
    define_admin_buttons(AdminButtons, *page); // 定义按钮
    clrmous(MouseX, MouseY);

    drawgraph_admin_menu(); // 初始化界面
    drawgraph_admin_message_center(); // 绘制界面
    while(*page == ADMIN_MESSAGE){
        newmouse_data(&MouseX, &MouseY, &press, &mouse_flag);

        admin_handle_buttons_event(page);
        admin_flush_buttons(&tag, STRUCT_LENGTH(AdminButtons), AdminButtons);

        if (mouse_press(ADMIN_FEATURE_EXIT_X1, ADMIN_FEATURE_EXIT_Y1,
                        ADMIN_FEATURE_EXIT_X2, ADMIN_FEATURE_EXIT_Y2) == 1) // 点击返回
        {
            *page = MAIN_ADMIN;
        }
        newmouse(&MouseX, &MouseY, &press, &mouse_flag);
        delay(25);
    }
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
    setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
    bar(ADMIN_INTERFACE_X1 + 115, ADMIN_INTERFACE_Y1 + 10, ADMIN_INTERFACE_X1 + 180, ADMIN_INTERFACE_Y1 + 30);
    bar(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 40, ADMIN_INTERFACE_X1 + 520, ADMIN_INTERFACE_Y1 + 60); // 清理画面

    settextstyle(SCRIPT_FONT, HORIZ_DIR, 1);
    setcolor(MY_RED);
    outtextxy(ADMIN_INTERFACE_X1 + 100, ADMIN_INTERFACE_Y1,"-");
    puthz(ADMIN_INTERFACE_X1 + 115, ADMIN_INTERFACE_Y1 + 10, "用户信息", 16, 16, MY_WHITE);

    setfillstyle(SOLID_FILL, MY_YELLOW);
    bar(ADMIN_FEATURE5_X1, ADMIN_FEATURE5_Y1, ADMIN_FEATURE5_X2, ADMIN_FEATURE5_Y2);
    bar(ADMIN_FEATURE6_X1, ADMIN_FEATURE6_Y1, ADMIN_FEATURE6_X2, ADMIN_FEATURE6_Y2);
    puthz(ADMIN_FEATURE6_X1 + 4, ADMIN_FEATURE6_Y1 + 8, "修改信息", 16, 16, MY_WHITE); // 显示新按钮

    puthz(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 40, "学号", 16, 16, MY_WHITE);
    puthz(ADMIN_INTERFACE_X1 + 120, ADMIN_INTERFACE_Y1 + 40, "账号", 16, 16, MY_WHITE);
    puthz(ADMIN_INTERFACE_X1 + 240, ADMIN_INTERFACE_Y1 + 40, "密码", 16, 16, MY_WHITE);
    puthz(ADMIN_INTERFACE_X1 + 360, ADMIN_INTERFACE_Y1 + 40, "注册时间", 16, 16, MY_WHITE);
    puthz(ADMIN_INTERFACE_X1 + 460, ADMIN_INTERFACE_Y1 + 40, "状态", 16, 16, MY_WHITE);
}

void drawgraph_admin_database_ebike_info(void)
{
    setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
    bar(ADMIN_INTERFACE_X1 + 115, ADMIN_INTERFACE_Y1 + 10, ADMIN_INTERFACE_X1 + 180, ADMIN_INTERFACE_Y1 + 30);
    bar(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 40, ADMIN_INTERFACE_X1 + 520, ADMIN_INTERFACE_Y1 + 60); // 清理画面

    settextstyle(SCRIPT_FONT, HORIZ_DIR, 1);
    setcolor(MY_RED);
    outtextxy(ADMIN_INTERFACE_X1 + 100, ADMIN_INTERFACE_Y1,"-");
    puthz(ADMIN_INTERFACE_X1 + 115, ADMIN_INTERFACE_Y1 + 10, "车辆信息", 16, 16, MY_WHITE);

    setfillstyle(SOLID_FILL, MY_YELLOW);
    bar(ADMIN_FEATURE5_X1, ADMIN_FEATURE5_Y1, ADMIN_FEATURE5_X2, ADMIN_FEATURE5_Y2);
    bar(ADMIN_FEATURE6_X1, ADMIN_FEATURE6_Y1, ADMIN_FEATURE6_X2, ADMIN_FEATURE6_Y2);
    puthz(ADMIN_FEATURE6_X1 + 4, ADMIN_FEATURE6_Y1 + 8, "修改信息", 16, 16, MY_WHITE); // 显示新按钮

    puthz(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 40, "学号", 16, 16, MY_WHITE);
    puthz(ADMIN_INTERFACE_X1 + 120, ADMIN_INTERFACE_Y1 + 40, "车辆车牌号", 16, 16, MY_WHITE);
    puthz(ADMIN_INTERFACE_X1 + 240, ADMIN_INTERFACE_Y1 + 40, "车辆证号", 16, 16, MY_WHITE);
    puthz(ADMIN_INTERFACE_X1 + 360, ADMIN_INTERFACE_Y1 + 40, "车辆地址", 16, 16, MY_WHITE);
    puthz(ADMIN_INTERFACE_X1 + 460, ADMIN_INTERFACE_Y1 + 40, "状态", 16, 16, MY_WHITE);
}

void drawgraph_admin_database_ebike_pass_in_out(void)
{
    setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
    bar(ADMIN_INTERFACE_X1 + 115, ADMIN_INTERFACE_Y1 + 10, ADMIN_INTERFACE_X1 + 180, ADMIN_INTERFACE_Y1 + 30);
    bar(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 40, ADMIN_INTERFACE_X1 + 520, ADMIN_INTERFACE_Y1 + 60); // 清理画面

    settextstyle(SCRIPT_FONT, HORIZ_DIR, 1);
    setcolor(MY_RED);
    outtextxy(ADMIN_INTERFACE_X1 + 100, ADMIN_INTERFACE_Y1, "-");
    puthz(ADMIN_INTERFACE_X1 + 115, ADMIN_INTERFACE_Y1 + 10, "车辆进出", 16, 16, MY_WHITE);

    setfillstyle(SOLID_FILL, MY_YELLOW);
    bar(ADMIN_FEATURE5_X1, ADMIN_FEATURE5_Y1, ADMIN_FEATURE5_X2, ADMIN_FEATURE5_Y2);
    bar(ADMIN_FEATURE6_X1, ADMIN_FEATURE6_Y1, ADMIN_FEATURE6_X2, ADMIN_FEATURE6_Y2);
    puthz(ADMIN_FEATURE5_X1 + 4, ADMIN_FEATURE5_Y1 + 8, "通过审核", 16, 16, MY_WHITE); // 显示新按钮
    puthz(ADMIN_FEATURE6_X1 + 4, ADMIN_FEATURE6_Y1 + 8, "拒绝申请", 16, 16, MY_WHITE); // 显示新按钮

    puthz(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 40, "车牌号", 16, 16, MY_WHITE);
    puthz(ADMIN_INTERFACE_X1 + 100, ADMIN_INTERFACE_Y1 + 40, "时间", 16, 16, MY_WHITE);
    puthz(ADMIN_INTERFACE_X1 + 220, ADMIN_INTERFACE_Y1 + 40, "出或入地点", 16, 16, MY_WHITE);
    puthz(ADMIN_INTERFACE_X1 + 340, ADMIN_INTERFACE_Y1 + 40, "申请理由", 16, 16, MY_WHITE);
    puthz(ADMIN_INTERFACE_X1 + 440, ADMIN_INTERFACE_Y1 + 40, "状态", 16, 16, MY_WHITE);
}

int drawgraph_admin_modify_data(FILE *fp, LINKLIST *LIST, int flag, unsigned long user_id)
{
    USER_LOGIN_DATA user_temp;
    LINKLIST_NODE *node = NULL;
    unsigned long pos;
    char buffer1[20]; // 用于存储格式化后的字符串
    char buffer2[20]; // 用于存储格式化后的字符串
    
    setwritemode(XOR_PUT);
    setfillstyle(LTBKSLASH_FILL, MY_GREEN); // 设置填充样式为实心
    bar(0, 0, 640, 480);                    // 清除整个屏幕

    setwritemode(COPY_PUT);
    setfillstyle(SOLID_FILL, MY_BLACK);
    bar(ADMIN_LIST_DATA_INTERFACE_X1+5, ADMIN_LIST_DATA_INTERFACE_Y1+5,
        ADMIN_LIST_DATA_INTERFACE_X2+5, ADMIN_LIST_DATA_INTERFACE_Y2+5); // 绘制列出数据的背景矩形框
    setfillstyle(SOLID_FILL, MY_BLACK);
    bar(ADMIN_MODIFY_DATA_INTERFACE_X1+5, ADMIN_MODIFY_DATA_INTERFACE_Y1+5,
        ADMIN_MODIFY_DATA_INTERFACE_X2+5, ADMIN_MODIFY_DATA_INTERFACE_Y2+5); // 绘制操作空间的背景矩形框
    setfillstyle(SOLID_FILL, MY_YELLOW);
    bar(ADMIN_LIST_DATA_INTERFACE_X1, ADMIN_LIST_DATA_INTERFACE_Y1,
        ADMIN_LIST_DATA_INTERFACE_X2, ADMIN_LIST_DATA_INTERFACE_Y2); // 绘制列出数据的矩形框
    setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
    bar(ADMIN_MODIFY_DATA_INTERFACE_X1, ADMIN_MODIFY_DATA_INTERFACE_Y1,
        ADMIN_MODIFY_DATA_INTERFACE_X2, ADMIN_MODIFY_DATA_INTERFACE_Y2); // 绘制操作空间的矩形框
    setcolor(MY_BLACK);
    setlinestyle(DASHED_LINE, 0, NORM_WIDTH); // 设置线宽为1
    rectangle(ADMIN_LIST_DATA_INTERFACE_X1+2, ADMIN_LIST_DATA_INTERFACE_Y1+2,
              ADMIN_MODIFY_DATA_INTERFACE_X2-2, ADMIN_MODIFY_DATA_INTERFACE_Y2-2); // 绘制列出数据的矩形框
    puthz(255, 10, "修改数据", 24, 35, MY_WHITE);                        // 绘制标题

    clear_exit(ADMIN_MODIFY_DATA_EXIT_X1, ADMIN_MODIFY_DATA_EXIT_Y1,
               ADMIN_MODIFY_DATA_EXIT_X2, ADMIN_MODIFY_DATA_EXIT_Y2); // 绘制退出按钮
    clear_accept(ADMIN_MODIFY_DATA_SAVE_X1, ADMIN_MODIFY_DATA_SAVE_Y1,
                 ADMIN_MODIFY_DATA_SAVE_X2, ADMIN_MODIFY_DATA_SAVE_Y2); // 绘制保存按钮

    puthz(ADMIN_LIST_DATA_INTERFACE_X1 + 10, ADMIN_LIST_DATA_INTERFACE_Y1 + 10, "原先数据", 16, 16, MY_WHITE);
    puthz(ADMIN_MODIFY_DATA_INTERFACE_X1 + 10, ADMIN_MODIFY_DATA_INTERFACE_Y1 + 10, "你将修改为", 16, 16, MY_WHITE);


    // 显示数据
    if (flag == ADMIN_DATABASE_USER_INFO) // 修改用户信息
    {
        /* 前置画面处理 */
        puthz(ADMIN_LIST_DATA_INTERFACE_X1 + 10, ADMIN_MODIFY_DATA_INPUTBAR1_Y1 + 7, "学号", 16, 16, MY_WHITE);
        puthz(ADMIN_LIST_DATA_INTERFACE_X1 + 10, ADMIN_MODIFY_DATA_INPUTBAR2_Y1 + 7, "用户名", 16, 16, MY_WHITE);
        puthz(ADMIN_LIST_DATA_INTERFACE_X1 + 10, ADMIN_MODIFY_DATA_INPUTBAR3_Y1 + 7, "密码", 16, 16, MY_WHITE);
        puthz(ADMIN_LIST_DATA_INTERFACE_X1 + 10, ADMIN_MODIFY_DATA_INPUTBAR4_Y1 + 7, "注册时间", 16, 16, MY_WHITE);
        puthz(ADMIN_LIST_DATA_INTERFACE_X1 + 10, ADMIN_MODIFY_DATA_INPUTBAR5_Y1 + 7, "状态", 16, 16, MY_WHITE);

        /* 操作信息展示处理 */
        ltoa(user_id, buffer1, 10); // 将 ID 转换为字符串
        pos = find_file_info(fp, "user_info", buffer1, "id");
        if (pos == 0)
        {
            puthz(ADMIN_LIST_DATA_INTERFACE_X1 + 100, ADMIN_LIST_DATA_INTERFACE_Y1 + 50, "无此用户", 16, 16, MY_RED); // 显示错误提示
            return 0;
        } // 查找用户信息
        fseek(fp, pos, SEEK_SET);
        fread(&user_temp, sizeof(USER_LOGIN_DATA), 1, fp);

        setcolor(MY_WHITE);
        outtextxy(ADMIN_LIST_DATA_INTERFACE_X1 + 80, ADMIN_MODIFY_DATA_INPUTBAR1_Y1 + 11, buffer1);        // 显示学号
        outtextxy(ADMIN_LIST_DATA_INTERFACE_X1 + 80, ADMIN_MODIFY_DATA_INPUTBAR2_Y1 + 11, user_temp.usrn); // 显示用户名
        outtextxy(ADMIN_LIST_DATA_INTERFACE_X1 + 80, ADMIN_MODIFY_DATA_INPUTBAR3_Y1 + 11, user_temp.psw);  // 显示密码
        ltoa(user_temp.register_time, buffer2, 10);                                                        // 将注册时间转换为字符串
        sprintf(buffer1, "%.4s.%.2s.%.2s", buffer2, buffer2 + 4, buffer2 + 6);
        outtextxy(ADMIN_LIST_DATA_INTERFACE_X1 + 80, ADMIN_MODIFY_DATA_INPUTBAR4_Y1 + 11, buffer1); // 显示注册时间

        if (user_temp.state == ACTIVE)
        {
            puthz(ADMIN_LIST_DATA_INTERFACE_X1 + 80, ADMIN_MODIFY_DATA_INPUTBAR5_Y1 + 8, "正常", 16, 16, MY_GREEN); // 显示状态
        }
        else if (user_temp.state == FROZEN)
        {
            puthz(ADMIN_LIST_DATA_INTERFACE_X1 + 80, ADMIN_MODIFY_DATA_INPUTBAR5_Y1 + 8, "冻结", 16, 16, MY_LIGHTBLUE); // 显示状态
        }
        else if (user_temp.state == BANNED)
        {
            puthz(ADMIN_LIST_DATA_INTERFACE_X1 + 80, ADMIN_MODIFY_DATA_INPUTBAR5_Y1 + 8, "封禁", 16, 16, MY_RED); // 显示状态
        }

        /* 后期输入框绘制处理 */
        setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
        bar(ADMIN_MODIFY_DATA_INPUTBAR3_X1, ADMIN_MODIFY_DATA_INPUTBAR3_Y1,
            ADMIN_MODIFY_DATA_INPUTBAR3_X2, ADMIN_MODIFY_DATA_INPUTBAR3_Y2); // 密码输入框
        setcolor(MY_BLACK);
        setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
        rectangle(ADMIN_MODIFY_DATA_INPUTBAR3_X1, ADMIN_MODIFY_DATA_INPUTBAR3_Y1,
                  ADMIN_MODIFY_DATA_INPUTBAR3_X2, ADMIN_MODIFY_DATA_INPUTBAR3_Y2); // 绘制密码输入框边框

        setfillstyle(SLASH_FILL, MY_LIGHTGRAY);
        bar(ADMIN_MODIFY_DATA_INPUTBAR1_X1, ADMIN_MODIFY_DATA_INPUTBAR1_Y1,
            ADMIN_MODIFY_DATA_INPUTBAR1_X2, ADMIN_MODIFY_DATA_INPUTBAR1_Y2); // 学号输入框
        bar(ADMIN_MODIFY_DATA_INPUTBAR2_X1, ADMIN_MODIFY_DATA_INPUTBAR2_Y1,
            ADMIN_MODIFY_DATA_INPUTBAR2_X2, ADMIN_MODIFY_DATA_INPUTBAR2_Y2); // 用户名输入框
        bar(ADMIN_MODIFY_DATA_INPUTBAR4_X1, ADMIN_MODIFY_DATA_INPUTBAR4_Y1,
            ADMIN_MODIFY_DATA_INPUTBAR4_X2, ADMIN_MODIFY_DATA_INPUTBAR4_Y2); // 注册时间输入框
        puthz(ADMIN_MODIFY_DATA_INPUTBAR1_X1 + 10, ADMIN_MODIFY_DATA_INPUTBAR1_Y1 + 7, "不可修改", 16, 16, MY_WHITE);
        puthz(ADMIN_MODIFY_DATA_INPUTBAR2_X1 + 10, ADMIN_MODIFY_DATA_INPUTBAR2_Y1 + 7, "不可修改", 16, 16, MY_WHITE);
        puthz(ADMIN_MODIFY_DATA_INPUTBAR4_X1 + 10, ADMIN_MODIFY_DATA_INPUTBAR4_Y1 + 7, "不可修改", 16, 16, MY_WHITE);

        setfillstyle(SOLID_FILL, MY_YELLOW); // 显示改变用户状态按钮
        bar(ADMIN_MODIFY_DATA_INPUTBAR5_X1, ADMIN_MODIFY_DATA_INPUTBAR5_Y1,
            ADMIN_MODIFY_DATA_INPUTBAR5_X1 + 80, ADMIN_MODIFY_DATA_INPUTBAR5_Y2);
        bar(ADMIN_MODIFY_DATA_INPUTBAR5_X1 + 100, ADMIN_MODIFY_DATA_INPUTBAR5_Y1,
            ADMIN_MODIFY_DATA_INPUTBAR5_X1 + 180, ADMIN_MODIFY_DATA_INPUTBAR5_Y2);
        bar(ADMIN_MODIFY_DATA_INPUTBAR5_X1 + 200, ADMIN_MODIFY_DATA_INPUTBAR5_Y1,
            ADMIN_MODIFY_DATA_INPUTBAR5_X1 + 280, ADMIN_MODIFY_DATA_INPUTBAR5_Y2);

        puthz(ADMIN_MODIFY_DATA_INPUTBAR5_X1 + 10, ADMIN_MODIFY_DATA_INPUTBAR5_Y1 + 7, "冻结账号", 16, 16, MY_LIGHTBLUE);
        puthz(ADMIN_MODIFY_DATA_INPUTBAR5_X1 + 110, ADMIN_MODIFY_DATA_INPUTBAR5_Y1 + 7, "封禁账号", 16, 16, MY_RED);
        puthz(ADMIN_MODIFY_DATA_INPUTBAR5_X1 + 210, ADMIN_MODIFY_DATA_INPUTBAR5_Y1 + 7, "恢复账号", 16, 16, MY_WHITE);
    }
    else if (flag == ADMIN_DATABASE_EBIKE_INFO) // 修改车辆信息
    {
        /* 前置画面处理 */
        puthz(ADMIN_LIST_DATA_INTERFACE_X1 + 10, ADMIN_MODIFY_DATA_INPUTBAR1_Y1 + 7, "学号", 16, 16, MY_WHITE);
        puthz(ADMIN_LIST_DATA_INTERFACE_X1 + 10, ADMIN_MODIFY_DATA_INPUTBAR2_Y1 + 7, "用户名", 16, 16, MY_WHITE);
        puthz(ADMIN_LIST_DATA_INTERFACE_X1 + 10, ADMIN_MODIFY_DATA_INPUTBAR3_Y1 + 7, "电动车牌", 16, 16, MY_WHITE);
        puthz(ADMIN_LIST_DATA_INTERFACE_X1 + 10, ADMIN_MODIFY_DATA_INPUTBAR4_Y1 + 7, "牌证号码", 16, 16, MY_WHITE);
        puthz(ADMIN_LIST_DATA_INTERFACE_X1 + 10, ADMIN_MODIFY_DATA_INPUTBAR5_Y1 + 7, "年审日期", 16, 16, MY_WHITE);
        puthz(ADMIN_LIST_DATA_INTERFACE_X1 + 10, ADMIN_MODIFY_DATA_INPUTBAR6_Y1 + 7, "车辆地址", 16, 16, MY_WHITE);
        puthz(ADMIN_LIST_DATA_INTERFACE_X1 + 10, ADMIN_MODIFY_DATA_INPUTBAR7_Y1 + 7, "车辆状态", 16, 16, MY_WHITE);

        /* 操作信息展示处理 */
        ltoa(user_id, buffer1, 10);
        pos = linklist_find_data(LIST, buffer1, "id"); // 查找车辆信息
        if (pos == 0){
            puthz(ADMIN_LIST_DATA_INTERFACE_X1 + 100, ADMIN_LIST_DATA_INTERFACE_Y1 + 50, "无此车辆", 16, 16, MY_RED); // 显示错误提示
            return 0;
        }
        linklist_get_to_node(LIST, pos, &node); // 获取用户信息，同时初始化指针

        setcolor(MY_WHITE);
        outtextxy(ADMIN_LIST_DATA_INTERFACE_X1 + 80, ADMIN_MODIFY_DATA_INPUTBAR1_Y1 + 11, buffer1);        // 显示学号
        outtextxy(ADMIN_LIST_DATA_INTERFACE_X1 + 80, ADMIN_MODIFY_DATA_INPUTBAR2_Y1 + 11, node->USER_DATA.usrn); // 显示用户名
        outtextxy(ADMIN_LIST_DATA_INTERFACE_X1 + 80, ADMIN_MODIFY_DATA_INPUTBAR3_Y1 + 11, node->USER_DATA.ebike_ID); // 显示电动车牌
        outtextxy(ADMIN_LIST_DATA_INTERFACE_X1 + 80, ADMIN_MODIFY_DATA_INPUTBAR4_Y1 + 11, node->USER_DATA.ebike_license); // 显示牌证号码
        ltoa(node->USER_DATA.anual_check, buffer2, 10);                                                        // 将注册时间转换为字符串
        sprintf(buffer1, "%.4s.%.2s.%.2s", buffer2, buffer2 + 4, buffer2 + 6);
        outtextxy(ADMIN_LIST_DATA_INTERFACE_X1 + 80, ADMIN_MODIFY_DATA_INPUTBAR5_Y1 + 11, buffer1); // 显示年审日期
        outtextxy(ADMIN_LIST_DATA_INTERFACE_X1 + 80, ADMIN_MODIFY_DATA_INPUTBAR6_Y1 + 11, node->USER_DATA.location); // 显示车辆地址
        if (node->USER_DATA.ebike_state == ACTIVE)
        {
            puthz(ADMIN_LIST_DATA_INTERFACE_X1 + 80, ADMIN_MODIFY_DATA_INPUTBAR7_Y1 + 8, "正常", 16, 16, MY_GREEN); // 显示车辆状态
        }
        else if (node->USER_DATA.ebike_state == BROKEN)
        {
            puthz(ADMIN_LIST_DATA_INTERFACE_X1 + 80, ADMIN_MODIFY_DATA_INPUTBAR7_Y1 + 8, "损坏", 16, 16, MY_RED); // 显示车辆状态
        }

        /* 后期输入框绘制处理 */
        setfillstyle(SLASH_FILL, MY_LIGHTGRAY);
        bar(ADMIN_MODIFY_DATA_INPUTBAR1_X1, ADMIN_MODIFY_DATA_INPUTBAR1_Y1,
            ADMIN_MODIFY_DATA_INPUTBAR1_X2, ADMIN_MODIFY_DATA_INPUTBAR1_Y2); // 学号输入框
        bar(ADMIN_MODIFY_DATA_INPUTBAR2_X1, ADMIN_MODIFY_DATA_INPUTBAR2_Y1,
            ADMIN_MODIFY_DATA_INPUTBAR2_X2, ADMIN_MODIFY_DATA_INPUTBAR2_Y2); // 用户名输入框
        bar(ADMIN_MODIFY_DATA_INPUTBAR7_X1, ADMIN_MODIFY_DATA_INPUTBAR7_Y1,
            ADMIN_MODIFY_DATA_INPUTBAR7_X2, ADMIN_MODIFY_DATA_INPUTBAR7_Y2); // 车辆状态输入框
        
        setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
        bar(ADMIN_MODIFY_DATA_INPUTBAR3_X1, ADMIN_MODIFY_DATA_INPUTBAR3_Y1,
            ADMIN_MODIFY_DATA_INPUTBAR3_X2, ADMIN_MODIFY_DATA_INPUTBAR3_Y2); // 电动车牌输入框
        bar(ADMIN_MODIFY_DATA_INPUTBAR4_X1, ADMIN_MODIFY_DATA_INPUTBAR4_Y1,
            ADMIN_MODIFY_DATA_INPUTBAR4_X2, ADMIN_MODIFY_DATA_INPUTBAR4_Y2); // 牌证号码输入框
        bar(ADMIN_MODIFY_DATA_INPUTBAR5_X1, ADMIN_MODIFY_DATA_INPUTBAR5_Y1,
            ADMIN_MODIFY_DATA_INPUTBAR5_X2, ADMIN_MODIFY_DATA_INPUTBAR5_Y2); // 年审日期输入框
        bar(ADMIN_MODIFY_DATA_INPUTBAR6_X1, ADMIN_MODIFY_DATA_INPUTBAR6_Y1,
            ADMIN_MODIFY_DATA_INPUTBAR6_X2, ADMIN_MODIFY_DATA_INPUTBAR6_Y2); // 车辆地址输入框

        setcolor(MY_BLACK);
        setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
        rectangle(ADMIN_MODIFY_DATA_INPUTBAR3_X1, ADMIN_MODIFY_DATA_INPUTBAR3_Y1,
                  ADMIN_MODIFY_DATA_INPUTBAR3_X2, ADMIN_MODIFY_DATA_INPUTBAR3_Y2); // 绘制电动车牌输入框边框
        rectangle(ADMIN_MODIFY_DATA_INPUTBAR4_X1, ADMIN_MODIFY_DATA_INPUTBAR4_Y1,
                  ADMIN_MODIFY_DATA_INPUTBAR4_X2, ADMIN_MODIFY_DATA_INPUTBAR4_Y2); // 绘制牌证号码输入框边框
        rectangle(ADMIN_MODIFY_DATA_INPUTBAR5_X1, ADMIN_MODIFY_DATA_INPUTBAR5_Y1,
                  ADMIN_MODIFY_DATA_INPUTBAR5_X2, ADMIN_MODIFY_DATA_INPUTBAR5_Y2); // 绘制年审日期输入框边框
        rectangle(ADMIN_MODIFY_DATA_INPUTBAR6_X1, ADMIN_MODIFY_DATA_INPUTBAR6_Y1,
                  ADMIN_MODIFY_DATA_INPUTBAR6_X2, ADMIN_MODIFY_DATA_INPUTBAR6_Y2); // 绘制车辆地址输入框边框

        puthz(ADMIN_MODIFY_DATA_INPUTBAR1_X1 + 10, ADMIN_MODIFY_DATA_INPUTBAR1_Y1 + 7, "不可修改", 16, 16, MY_WHITE);
        puthz(ADMIN_MODIFY_DATA_INPUTBAR2_X1 + 10, ADMIN_MODIFY_DATA_INPUTBAR2_Y1 + 7, "请到用户信息中修改", 16, 16, MY_WHITE);
        puthz(ADMIN_MODIFY_DATA_INPUTBAR7_X1 + 10, ADMIN_MODIFY_DATA_INPUTBAR7_Y1 + 7, "不可修改", 16, 16, MY_WHITE);
    }

    return 1;
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

void drawgraph_admin_message_center()
{
    puthz(ADMIN_INTERFACE_X1 + 15, ADMIN_INTERFACE_Y1 + 5, "消息中心", 24, 20, MY_WHITE); // 输出文本

    draw_cues(ADMIN_BUTTON7_X2 + 10, ADMIN_BUTTON7_Y1, NULL, NULL); // 绘制箭头，标明当前打开页面为此
    clear_exit(ADMIN_FEATURE_EXIT_X1, ADMIN_FEATURE_EXIT_Y1, ADMIN_FEATURE_EXIT_X2, ADMIN_FEATURE_EXIT_Y2);
}

/*****************************************************************
MODULE: 读写数据函数
*****************************************************************/

// 查找文件中是否存在指定内容，并返回该数据块位置
long find_file_info(FILE *fp, char *file_type,char *search_str,char *search_needed){
    long counts = 0;
    EBIKE_INFO ebike_temp;
    USER_LOGIN_DATA USER_TEMP;
    EBIKE_IN_OUT ebike_in_out_temp;

    fseek(fp,0,SEEK_SET); // 获取文件长度

    if(strcmp(file_type,"user_info") == 0){ // 查找用户信息
        while (fread(&USER_TEMP, sizeof(USER_LOGIN_DATA), 1, fp)) // 遍历文件中的所有数据块，当读取到文件末尾时，fread返回0，退出循环
        {
            if ((strcmp(search_needed, "id") == 0 && USER_TEMP.ID == atol(search_str)) ||
                (strcmp(search_needed, "usrn") == 0 && strcmp(USER_TEMP.usrn, search_str) == 0) ||
                (strcmp(search_needed, "psw") == 0 && strcmp(USER_TEMP.psw, search_str) == 0) ||
                (strcmp(search_needed, "register_time") == 0 && USER_TEMP.register_time == atol(search_str)) ||
                (strcmp(search_needed, "state") == 0 && USER_TEMP.state == (char)atoi(search_str)))
            {
                return counts * sizeof(USER_LOGIN_DATA);
            }
            counts++;
        }
    }
    else if(strcmp(file_type,"ebike_manage") == 0){ // 查找车辆管理信息
        while (fread(&ebike_temp, sizeof(EBIKE_INFO), 1, fp)) // 遍历文件中的所有数据块，当读取到文件末尾时，fread返回0，退出循环
        {
            if ((strcmp(search_needed, "realname") == 0 && strcmp(ebike_temp.rln, search_str) == 0) ||
                (strcmp(search_needed, "id") == 0 && ebike_temp.ID == atol(search_str)) ||
                (strcmp(search_needed, "ebike_id") == 0 && strcmp(ebike_temp.ebike_ID, search_str) == 0) ||
                (strcmp(search_needed, "ebike_license") == 0 && strcmp(ebike_temp.ebike_license, search_str) == 0) ||
                (strcmp(search_needed, "location") == 0 && strcmp(ebike_temp.location, search_str) == 0) ||
                (strcmp(search_needed, "apply_time") == 0 && ebike_temp.apply_time == atol(search_str)) ||
                (strcmp(search_needed, "conduct_time") == 0 && ebike_temp.conduct_time == atol(search_str)) ||
                (strcmp(search_needed, "result") == 0 && ebike_temp.result == atoi(search_str)))
            {
                return counts * sizeof(EBIKE_INFO);
            }
            counts++;
        }
    }
    else if(strcmp(file_type,"ebike_in_out") == 0){ // 查找车辆出入信息
        while (fread(&ebike_in_out_temp, sizeof(EBIKE_IN_OUT), 1, fp)) // 遍历文件中的所有数据块，当读取到文件末尾时，fread返回0，退出循环
        {
            if (ebike_in_out_temp.apply_id == atol(search_str) && strcmp(search_needed, "apply_id") == 0)
            {
                return counts * sizeof(EBIKE_IN_OUT);
            }
            counts++; 
        }
    }
    return -1; // 文件指针位置返回到原先位置
}

int modify_user_info(FILE *fp , unsigned long user_id, char *modify_str,char *modify_needed){
    long pos = -1;
    char buffer[20];
    USER_LOGIN_DATA user_temp;

    ltoa(user_id, buffer, 10); // 将用户ID转换为字符串

    pos = find_file_info(fp, "user_info", buffer, "id");
    if (pos == -1)
    {
        puthz(ADMIN_MODIFY_DATA_INTERFACE_X1 + 100, ADMIN_MODIFY_DATA_INTERFACE_Y1 + 10, 
              "尝试修改用户数据时发生错误：未找到用户数据", 16, 16, MY_RED); // 显示状态
        return 0;
    }

    fseek(fp, pos, SEEK_SET); // 获取文件长度
    fread(&user_temp, sizeof(USER_LOGIN_DATA), 1, fp); // 读取用户信息

    // 每一次调用函数都只修改一次数据，因此以下判断结构用if - else
    if (strcmp(modify_needed, "password") == 0 && strcmp(modify_str, "\0") != 0) // 修改密码
    {
        strcpy(user_temp.psw, modify_str); // 修改用户名
        puthz(ADMIN_MODIFY_DATA_INPUTBAR3_X2 + 10, ADMIN_MODIFY_DATA_INPUTBAR3_Y1 + 7, "修改成功", 16, 16, MY_GREEN); // 显示状态
    }
    else if (strcmp(modify_needed, "state") == 0 && strcmp(modify_str, "\0") != 0) // 修改状态
    {
        if (user_temp.state == (char)atoi(modify_str)) // 若状态未改变，则不进行修改
        {
            return 1; // 不算重大错误，只是没有修改账户状态，因此返回1
        }
        user_temp.state = (char)atoi(modify_str); // 修改状态
        puthz(ADMIN_MODIFY_DATA_INPUTBAR5_X2 + 10, ADMIN_MODIFY_DATA_INPUTBAR5_Y1 + 7, "修改成功", 16, 16, MY_GREEN); // 显示状态
    }

    fseek(fp, pos, SEEK_SET); // 获取文件长度
    fwrite(&user_temp, sizeof(USER_LOGIN_DATA), 1, fp); // 写入用户信息
    return 1;
}

void modify_ebike_info(LINKLIST *LIST, unsigned long user_id, char *modify_str,char *modify_needed){
    long pos = -1;
    char buffer1[20];
    char buffer2[20];
    LINKLIST_NODE *node;

    ltoa(user_id, buffer1, 10); // 将用户ID转换为字符串
    pos = linklist_find_data(LIST, buffer1, "id"); // 将用户ID转换为字符串
    // 检验是否存在用户信息操作在admin_check_ebike_info函数中已经完成，这里不再重复
    linklist_get_to_node(LIST, pos, &node); // 获取用户信息

    // 每一次调用函数都只修改一次数据，因此以下判断结构用if - else
    if (strcmp(modify_needed, "ebike_id") == 0 && strcmp(modify_str, "\0") != 0) // 修改电动车ID
    {
        strcpy(node->USER_DATA.ebike_ID, modify_str); // 修改电动车ID
        puthz(ADMIN_MODIFY_DATA_INPUTBAR3_X2 + 10, ADMIN_MODIFY_DATA_INPUTBAR3_Y1 + 7, "修改成功", 16, 16, MY_GREEN); // 显示状态
    }
    else if (strcmp(modify_needed, "ebike_license") == 0 && strcmp(modify_str, "\0")!= 0) // 修改电动车牌
    {
        strcpy(node->USER_DATA.ebike_license, modify_str); // 修改电动车牌
        puthz(ADMIN_MODIFY_DATA_INPUTBAR4_X2 + 10, ADMIN_MODIFY_DATA_INPUTBAR4_Y1 + 7, "修改成功", 16, 16, MY_GREEN); // 显示状态
    }
    else if (strcmp(modify_needed, "location") == 0 && strcmp(modify_str, "\0")!= 0) // 修改车辆地址
    {
        strcpy(node->USER_DATA.location, modify_str); // 修改车辆地址
        puthz(ADMIN_MODIFY_DATA_INPUTBAR6_X2 + 10, ADMIN_MODIFY_DATA_INPUTBAR6_Y1 + 7, "修改成功", 16, 16, MY_GREEN); // 显示状态
    }
    else if (strcmp(modify_needed, "anual_check") == 0 && strcmp(modify_str, "\0")!= 0) // 修改年审日期
    {
        sprintf(buffer1, "%0.4s%0.2s%0.2s", modify_str, modify_str + 5, modify_str + 8); // 将用户ID转换为字符串
        node->USER_DATA.anual_check = atol(buffer1); // 修改年审日期
        puthz(ADMIN_MODIFY_DATA_INPUTBAR5_X2 + 10, ADMIN_MODIFY_DATA_INPUTBAR5_Y1 + 7, "修改成功", 16, 16, MY_GREEN); // 显示状态
    }
}

/*****************************************************************
MODULE: 判断输入合理性函数
*****************************************************************/
int admin_check_ebike_info(LINKLIST *LIST, MODIFY_EBIKE_DATA_BUFFER temp, unsigned long user_id)
{
    LINKLIST_NODE *node;
    char buffer1[15];
    long pos = -1;
    int fail = 0;

    ltoa(user_id, buffer1, 10);                    // 将用户ID转换为字符串
    pos = linklist_find_data(LIST, buffer1, "id"); // 查找用户信息
    if (pos == -1)                                 // 查找用户信息
    {
        puthz(ADMIN_MODIFY_DATA_INTERFACE_X1 + 100, ADMIN_MODIFY_DATA_INTERFACE_Y1 + 10,
              "尝试修改用户数据时发生错误：未找到用户数据", 16, 16, MY_RED); // 显示状态
        return 0;
    }
    
    if(strcmp(temp.ebike_id_buffer, "\0") != 0)
    {
        if(admin_check_ebike_id(temp.ebike_id_buffer) == 0) // 检查电动车ID
        {
            puthz(ADMIN_MODIFY_DATA_INPUTBAR3_X1 + 10, ADMIN_MODIFY_DATA_INPUTBAR3_Y1 + 7,"格式错误", 16, 16, MY_RED);
            fail++;
        }
    }
    if(strcmp(temp.ebike_license_buffer, "\0")!= 0)
    {
        if(admin_check_license(temp.ebike_license_buffer) == 0) // 检查电动车ID
        {
            puthz(ADMIN_MODIFY_DATA_INPUTBAR4_X1 + 10, ADMIN_MODIFY_DATA_INPUTBAR4_Y1 + 7,"格式错误", 16, 16, MY_RED);
            fail++;
        }
    }
    if (strcmp(temp.anual_check_buffer, "\0") != 0)
    {

        linklist_get_to_node(LIST, pos, &node); // 获取用户信息

        if (admin_check_anual_check(temp.anual_check_buffer, node->USER_DATA.anual_check) == 0) // 检查电动车ID
        {
            puthz(ADMIN_MODIFY_DATA_INPUTBAR5_X1 + 10, ADMIN_MODIFY_DATA_INPUTBAR5_Y1 + 7,"格式错误", 16, 16, MY_RED);
            fail++;
        }
    }
    if(fail == 0)
        return 1;
    else
        return 0;
}

int admin_check_ebike_id(char *ebike_id){
    int i;
    if (strlen(ebike_id) != 6) // 检查电动车ID长度是否为10
    {
        return 0;
    }

    for (i = 0; i < 2; i++) // 检查电动车ID
    {
        if (ebike_id[i] < 'A' || ebike_id[i] > 'Z') // 检查电动车ID前两位是否为大写字母
        {
            
            return 0;
        }
    }
    for (i = 2; i < 5; i++) // 检查电动车ID
    {
        if (ebike_id[i] < '0' || ebike_id[i] > '9') // 检查电动车ID后三位是否为数字
        {
            
            return 0;
        }
    }
    return 1;
}
int admin_check_license(char *ebike_license){
    int i;
    if (strlen(ebike_license) != 8) // 检查电动车ID长度是否为10
    {
        return 0;
    }

    if (ebike_license[0] < 'A' || ebike_license[0] > 'Z') // 检查电动车ID前两位是否为大写字母
    {
        return 0;
    }
    for (i = 1; i < 8; i++) // 检查电动车ID
    {
        if (ebike_license[i] < '0' || ebike_license[i] > '9') // 检查电动车ID后三位是否为数字
        {
            return 0;
        }
    }
    return 1;
}
int admin_check_anual_check(char *now, unsigned long prev){ // 传入的now是带有'.'分割的字符串，传入的prev是无符号长整型
    int i;
    char buffer1[12];
    sprintf(buffer1, "%0.4s%0.2s%0.2s", now, now + 5, now + 8); // 将用户ID转换为字符串
    if (strlen(now) != 10)                                         // 检查电动车ID长度是否为10
    {
        return 0;
    }

    if(atol(buffer1) < prev){
        return 0;
    }

    if(now[4] == '.' && now[7] == '.'){ // 检查电动车ID
        return 0;
    }

    return 1;
}


/*****************************************************************
MODULE: 处理鼠标点击事件的函数
*****************************************************************/
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

    /*信息中心*/
    if (mouse_press(ADMIN_BUTTON7_X1, ADMIN_BUTTON7_Y1, ADMIN_BUTTON7_X2, ADMIN_BUTTON7_Y2) == 1 &&
        *page!= ADMIN_MESSAGE)
    {
        *page = ADMIN_MESSAGE;
        return;
    }
}

void admin_handle_manage_feature_event(LINKLIST *LIST, int *page, char *search_str, unsigned long *id_list, FILE *fp_EBIKE_INFO_read, int *mode, unsigned long *selected_id)
{
    int i;
    char list_mode[15]; // 列表依据
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
        ch_input(search_str, ADMIN_FEATURE_SEARCH_X1 + 25, ADMIN_FEATURE_SEARCH_Y1 + 2, 9, MY_LIGHTGRAY, 0, 1);

        *selected_id = 0; // 清除选中行
        setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
        bar(ADMIN_INTERFACE_X1 + 10, ADMIN_INTERFACE_Y1 + 70, ADMIN_INTERFACE_X1 + 18, ADMIN_INTERFACE_Y1 + 310); // 清理所有选中行高亮

        admin_list_info(LIST, LIST_LIMIT, LIST_INTERVAL, id_list, fp_EBIKE_INFO_read, "ebike_manage",
                        list_mode, *mode, 0, 2, search_str, "ID"); // 搜索后刷新列表

    } // 点击输入框后退回

    if (mouse_press(ADMIN_FEATURE3_X1, ADMIN_FEATURE3_Y1, ADMIN_FEATURE3_X2, ADMIN_FEATURE3_Y2) == 1 &&
        *mode == 0)
    {
        *mode = 1;
        setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
        bar(ADMIN_INTERFACE_X1 + 140, ADMIN_INTERFACE_Y1 + 10, ADMIN_INTERFACE_X1 + 230, ADMIN_INTERFACE_Y1 + 30);
        puthz(ADMIN_INTERFACE_X1 + 140, ADMIN_INTERFACE_Y1 + 10, "已处理项目", 16, 16, MY_WHITE);
        admin_list_info(LIST, LIST_LIMIT, LIST_INTERVAL, id_list, fp_EBIKE_INFO_read, "ebike_manage",
                        list_mode, *mode, LIST_STAY, LIST_CLEAR_CONTINUE, search_str, "ID");
    } // 点击已处理后显示已处理

    if (mouse_press(ADMIN_FEATURE4_X1, ADMIN_FEATURE4_Y1, ADMIN_FEATURE4_X2, ADMIN_FEATURE4_Y2) == 1 &&
        *mode == 1)
    {
        *mode = 0;
        setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
        bar(ADMIN_INTERFACE_X1 + 140, ADMIN_INTERFACE_Y1 + 10, ADMIN_INTERFACE_X1 + 230, ADMIN_INTERFACE_Y1 + 30);
        puthz(ADMIN_INTERFACE_X1 + 140, ADMIN_INTERFACE_Y1 + 10, "未处理项目", 16, 16, MY_WHITE);
        admin_list_info(LIST, LIST_LIMIT, LIST_INTERVAL, id_list, fp_EBIKE_INFO_read, "ebike_manage",
                        list_mode, *mode, LIST_STAY, LIST_CLEAR_CONTINUE, search_str, "ID");
    } // 点击未处理后显示未处理

    // 点击同意申请
    if (mouse_press(ADMIN_FEATURE1_X1, ADMIN_FEATURE1_Y1, ADMIN_FEATURE1_X2, ADMIN_FEATURE1_Y2) == 1 && *selected_id != 0)
    {
        ltoa(*selected_id, buffer, 10);                                  // 将选中行的ID转化为字符串
        if ((chain_pos = linklist_find_data(LIST, buffer, "id")) == 0) // 查找链表中是否存在该ID，若找不到，则不进行任何操作
            return;

        if (find_file_info(fp_EBIKE_INFO_read, "ebike_manage", buffer, "id") == 0)
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

        admin_list_info(LIST, LIST_LIMIT, LIST_INTERVAL, id_list, fp_EBIKE_INFO_read, "ebike_manage",
                        list_mode, *mode, LIST_PAGEDOWN, LIST_FLUSH, "\0", "\0"); // 操作结束后刷新列表
    }

    // 点击拒绝申请
    if (mouse_press(ADMIN_FEATURE2_X1, ADMIN_FEATURE2_Y1, ADMIN_FEATURE2_X2, ADMIN_FEATURE2_Y2) == 1 && *selected_id != 0)
    {
        ltoa(*selected_id, buffer, 10);
        if (chain_pos = linklist_find_data(LIST, buffer, "id") == 0)
            return; // 选中行，点击同意申请，若出现未能找到数据的情况，则不进行任何操作

        if (find_file_info(fp_EBIKE_INFO_read, "ebike_manage", buffer, "id") == 0)
            return; // 如果没有找到数据块，则不进行任何操作，若能找到，则进一步处理数据

        // 修改数据块
        fread(&temp_info, sizeof(EBIKE_INFO), 1, fp_EBIKE_INFO_read);                     // 读取数据块
        temp_info.conduct_time = get_approx_time(NULL);                                              // 将时间字符串转化为int型数据，并赋值给conduct_time
        temp_info.result = FAILED;                                                        // 将result赋值为已处理

        fseek(fp_EBIKE_INFO_read, search_pos, SEEK_SET);               // 定位到数据块
        fwrite(&temp_info, sizeof(EBIKE_INFO), 1, fp_EBIKE_INFO_read); // 将新数据写入数据块

        // 申请失败，不修改链表数据

        admin_pass_failed_anime(ADMIN_FEATURE1_X1, ADMIN_FEATURE1_Y1, ADMIN_FEATURE1_X2, ADMIN_FEATURE1_Y2, FAILED); // 操作后的动画

        admin_list_info(LIST, LIST_LIMIT, LIST_INTERVAL, id_list, fp_EBIKE_INFO_read, "ebike_manage",
                        list_mode, *mode, LIST_PAGEDOWN, LIST_FLUSH, "\0", "\0"); // 操作结束后刷新列表
    }
    temp_node = NULL; // 释放指针
}

void admin_handle_database_event(LINKLIST *LIST, int *flag, int *page, unsigned long *id_list, 
                                 FILE *fp, char *search_str, unsigned long *selected_id)
{
    long pos = -1; // 查找数据得到的位置
    EBIKE_IN_OUT ebike_in_out_temp;
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
        admin_list_info(LIST, LIST_LIMIT, LIST_INTERVAL, id_list, fp, file_type, NULL, NULL, LIST_STAY, LIST_CLEAR_CONTINUE, search_str, "ID");
        return;
    }
    /*点击车辆信息*/
    if (mouse_press(ADMIN_FEATURE2_X1, ADMIN_FEATURE2_Y1, ADMIN_FEATURE2_X2, ADMIN_FEATURE2_Y2) == 1 &&
        *flag != ADMIN_DATABASE_EBIKE_INFO)
    {
        drawgraph_admin_database_ebike_info();
        *flag = ADMIN_DATABASE_EBIKE_INFO;
        strcpy(file_type, "ebike_data");
        admin_list_info(LIST, LIST_LIMIT, LIST_INTERVAL, id_list, NULL, file_type, NULL, NULL, LIST_STAY, LIST_CLEAR_CONTINUE, search_str, "ID");
        return;
    }
    /*点击车辆出入信息*/
    if (mouse_press(ADMIN_FEATURE3_X1, ADMIN_FEATURE3_Y1, ADMIN_FEATURE3_X2, ADMIN_FEATURE3_Y2) == 1 &&
        *flag != ADMIN_DATABASE_EBIKE_PASS_IN_OUT)
    {
        drawgraph_admin_database_ebike_pass_in_out();
        *flag = ADMIN_DATABASE_EBIKE_PASS_IN_OUT;
        strcpy(file_type, "ebike_pass_in_out");
        admin_list_info(LIST, LIST_LIMIT, LIST_INTERVAL, id_list, NULL, file_type, NULL, NULL, LIST_STAY, LIST_CLEAR_CONTINUE, search_str, "ID");
        return;
    }

    /*点击翻页*/
    if (mouse_press(ADMIN_FEATURE_UP_X1, ADMIN_FEATURE_UP_Y1, ADMIN_FEATURE_UP_X2, ADMIN_FEATURE_UP_Y2) == 1){
        if (*flag != ADMIN_DATABASE_EBIKE_INFO){
            admin_list_info(LIST, LIST_LIMIT, LIST_INTERVAL, id_list, fp, file_type, NULL, NULL, LIST_PAGEUP, LIST_NO_CLEAR, search_str, "ID");
        }
        else if (*flag == ADMIN_DATABASE_EBIKE_INFO){
            admin_list_info(LIST, LIST_LIMIT, LIST_INTERVAL, id_list, fp, file_type, NULL, NULL, LIST_PAGEUP, LIST_NO_CLEAR, search_str, "ID");
        }
        return;
    }
    if (mouse_press(ADMIN_FEATURE_DOWN_X1, ADMIN_FEATURE_DOWN_Y1, ADMIN_FEATURE_DOWN_X2, ADMIN_FEATURE_DOWN_Y2) == 1){
        if (*flag != ADMIN_DATABASE_EBIKE_INFO){
            admin_list_info(LIST, LIST_LIMIT, LIST_INTERVAL, id_list, fp, file_type, NULL, NULL, LIST_PAGEDOWN, LIST_NO_CLEAR, search_str, "ID"); 
        }
        else if (*flag == ADMIN_DATABASE_EBIKE_INFO){
            admin_list_info(LIST, LIST_LIMIT, LIST_INTERVAL, id_list, fp, file_type, NULL, NULL, LIST_PAGEDOWN, LIST_NO_CLEAR, search_str, "ID");
        }
        return;
    }
    /*点击搜索框*/
    if (mouse_press(ADMIN_FEATURE_SEARCH_X1, ADMIN_FEATURE_SEARCH_Y1, ADMIN_FEATURE_SEARCH_X2, ADMIN_FEATURE_SEARCH_Y2) == 1)
    {
        ch_input(search_str, ADMIN_FEATURE_SEARCH_X1 + 25, ADMIN_FEATURE_SEARCH_Y1 + 2, 9, MY_LIGHTGRAY, 0, 1);

        admin_list_info(LIST, LIST_LIMIT, LIST_INTERVAL, id_list, fp, file_type, NULL, NULL, LIST_STAY, LIST_CLEAR_CONTINUE, search_str, "ID"); // 搜索后刷新列表
        return;
    }
    /*点击修改信息*/
    if (mouse_press(ADMIN_FEATURE6_X1, ADMIN_FEATURE6_Y1, ADMIN_FEATURE6_X2, ADMIN_FEATURE6_Y2) == 1 &&
        *flag != ADMIN_DATABASE_EBIKE_PASS_IN_OUT)
    {
        if (*selected_id != 0){
            admin_modify_data(LIST, fp, "user_data", selected_id); 
            strcpy(search_str, "\0"); // 清除过滤依据以恢复正常列表，这一句很重要！
            admin_list_info(LIST, LIST_LIMIT, LIST_INTERVAL, id_list, fp, file_type, NULL, NULL, LIST_STAY, LIST_CLEAR_CONTINUE, search_str, "ID");
        }
        return;
    }
    /* 在车辆出入界面，点击拒绝申请 */
    if (mouse_press(ADMIN_FEATURE6_X1, ADMIN_FEATURE6_Y1, ADMIN_FEATURE6_X2, ADMIN_FEATURE6_Y2) == 1 &&
        *flag == ADMIN_DATABASE_EBIKE_PASS_IN_OUT)
    {
        if (*selected_id!= 0){
            pos = find_file_info(fp, file_type, (char *)selected_id, "apply_id"); // 查找数据块
            if (pos == -1)
                return; // 未找到数据块，不进行任何操作
            fseek (fp, -sizeof(EBIKE_IN_OUT), SEEK_CUR); // 定位到数据块
            fread (&ebike_in_out_temp, sizeof(EBIKE_IN_OUT), 1, fp); // 读取数据块
            ebike_in_out_temp.result = FAILED; // 修改数据块中的result字段为FAILED
            fseek (fp, -sizeof(EBIKE_IN_OUT), SEEK_CUR); // 定位到数据块
            fwrite (&ebike_in_out_temp, sizeof (EBIKE_IN_OUT), 1, fp); // 将修改后的数据块写入文件
            admin_pass_failed_anime(ADMIN_FEATURE6_X1, ADMIN_FEATURE6_Y1, ADMIN_FEATURE6_X2, ADMIN_FEATURE6_Y2, FAILED); // 操作后的动画
            admin_list_info(LIST, LIST_LIMIT, LIST_INTERVAL, id_list, fp, file_type, NULL, NULL, LIST_STAY, LIST_FLUSH, "\0", "\0"); // 操作结束后刷新列表
        }
    }
    /* 在车辆出入界面，点击同意申请 */
    if (mouse_press(ADMIN_FEATURE5_X1, ADMIN_FEATURE5_Y1, ADMIN_FEATURE5_X2, ADMIN_FEATURE5_Y2) == 1 &&
        *flag == ADMIN_DATABASE_EBIKE_PASS_IN_OUT)
    {
        if (*selected_id!= 0){
            pos = find_file_info(fp, file_type, (char *)selected_id, "apply_id"); // 查找数据块
            if (pos == -1)
                return; // 未找到数据块，不进行任何操作
            fseek (fp, -sizeof(EBIKE_IN_OUT), SEEK_CUR); // 定位
            fread (&ebike_in_out_temp, sizeof(EBIKE_IN_OUT), 1, fp); // 读取数据块
            ebike_in_out_temp.result = PASSED; // 修改数据块中的result字段为PASSED
            fseek (fp, -sizeof(EBIKE_IN_OUT), SEEK_CUR); // 定位到数据块
            fwrite (&ebike_in_out_temp, sizeof (EBIKE_IN_OUT), 1, fp); // 将修改后的数据块写入文件
            admin_pass_failed_anime(ADMIN_FEATURE5_X1, ADMIN_FEATURE5_Y1, ADMIN_FEATURE5_X2, ADMIN_FEATURE5_Y2, PASSED); // 操作后的动画
            admin_list_info(LIST, LIST_LIMIT, LIST_INTERVAL, id_list, fp, file_type, NULL, NULL, LIST_STAY, LIST_FLUSH, "\0", "\0"); // 操作结束后刷新列表
        }
    }
}

void admin_handle_modify_user_data_event(FILE *fp, unsigned long *user_id, int *isReturn)
{                                      // 函数将在返回时清理user_id
    static char psw_buffer[15] = "\0"; // 输入框输入信息储存
    static char state_buffer = '\0';
    char buffer[5];

    // 处理点击事件
    if (mouse_press(ADMIN_MODIFY_DATA_SAVE_X1, ADMIN_MODIFY_DATA_SAVE_Y1,
                    ADMIN_MODIFY_DATA_SAVE_X2, ADMIN_MODIFY_DATA_SAVE_Y2) == 1) // 点击保存
    {
        // 保存修改后的用户信息到文件中
        if (strcmp(psw_buffer, "\0") != 0)
        {                                                                    // 修改密码
            if (modify_user_info(fp, *user_id, psw_buffer, "password") == 0) // 修改密码
            {
                *user_id = 0;
                return;
            }
        }
        if (state_buffer != '\0')
        {                                                             // 修改状态
            itoa((int)state_buffer, buffer, 10);                      // 转换为字符串
            if (modify_user_info(fp, *user_id, buffer, "state") == 0) // 修改状态
            {
                *user_id = 0;
                return;
            }
        }

        puthz(ADMIN_MODIFY_DATA_INTERFACE_X1 + 100, ADMIN_MODIFY_DATA_INTERFACE_Y1 + 10, "成功保存修改信息！", 16, 16, MY_GREEN); // 显示保存成功
        ch_input(NULL, NULL, NULL, NULL, NULL, INPUTBAR_CLEAR, NULL);
        memset(psw_buffer, '\0', sizeof(psw_buffer)); // 清空密码输入框
        state_buffer = '\0';

        delay(500); // 延时
        *user_id = 0;
        *isReturn = 1; // 标记为返回
    }
    if (mouse_press(ADMIN_MODIFY_DATA_INPUTBAR3_X1, ADMIN_MODIFY_DATA_INPUTBAR3_Y1,
                    ADMIN_MODIFY_DATA_INPUTBAR3_X2, ADMIN_MODIFY_DATA_INPUTBAR3_Y2) == 1) // 点击密码框
    {
        // ch_input(psw_buffer, ADMIN_MODIFY_DATA_INPUTBAR3_X1, ADMIN_MODIFY_DATA_INPUTBAR3_Y1, 13, MY_LIGHTGRAY, INPUTBAR_NO_CLEAR, 1);
        hz_input(ADMIN_MODIFY_DATA_INPUTBAR3_X1, ADMIN_MODIFY_DATA_INPUTBAR3_Y2, 
                 ADMIN_MODIFY_DATA_INPUTBAR3_X1, ADMIN_MODIFY_DATA_INPUTBAR3_Y2, psw_buffer, 13, MY_LIGHTGRAY, MY_BLACK, 16);
    }
    if (mouse_press(ADMIN_MODIFY_DATA_FREEZE_X1, ADMIN_MODIFY_DATA_FREEZE_Y1,
                    ADMIN_MODIFY_DATA_FREEZE_X2, ADMIN_MODIFY_DATA_FREEZE_Y2) == 1 &&
        state_buffer != FROZEN) // 点击冻结
    {
        state_buffer = FROZEN;
        setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
        bar(ADMIN_MODIFY_DATA_INTERFACE_X1 + 10, ADMIN_MODIFY_DATA_INTERFACE_Y2 - 25,
            ADMIN_MODIFY_DATA_INTERFACE_X1 + 350, ADMIN_MODIFY_DATA_INTERFACE_Y2 - 5); // 显示冻结
        puthz(ADMIN_MODIFY_DATA_INTERFACE_X1 + 10, ADMIN_MODIFY_DATA_INTERFACE_Y2 - 25,
              "冻结账户：允许登陆，无法使用功能", 16, 16, MY_LIGHTBLUE); // 显示冻结
    }
    if (mouse_press(ADMIN_MODIFY_DATA_BAN_X1, ADMIN_MODIFY_DATA_BAN_Y1,
                    ADMIN_MODIFY_DATA_BAN_X2, ADMIN_MODIFY_DATA_BAN_Y2) == 1 &&
        state_buffer != BANNED) // 点击解冻
    {
        state_buffer = BANNED;
        setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
        bar(ADMIN_MODIFY_DATA_INTERFACE_X1 + 10, ADMIN_MODIFY_DATA_INTERFACE_Y2 - 25,
            ADMIN_MODIFY_DATA_INTERFACE_X1 + 350, ADMIN_MODIFY_DATA_INTERFACE_Y2 - 5); // 显示封禁
        puthz(ADMIN_MODIFY_DATA_INTERFACE_X1 + 10, ADMIN_MODIFY_DATA_INTERFACE_Y2 - 25,
              "封禁账户：禁止登陆，无法使用功能", 16, 16, MY_RED); // 显示封禁
    }
    if (mouse_press(ADMIN_MODIFY_DATA_RESTORE_X1, ADMIN_MODIFY_DATA_RESTORE_Y1,
                    ADMIN_MODIFY_DATA_RESTORE_X2, ADMIN_MODIFY_DATA_RESTORE_Y2) == 1 &&
        state_buffer != ACTIVE) // 点击解冻
    {
        state_buffer = ACTIVE;
        setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
        bar(ADMIN_MODIFY_DATA_INTERFACE_X1 + 10, ADMIN_MODIFY_DATA_INTERFACE_Y2 - 25,
            ADMIN_MODIFY_DATA_INTERFACE_X1 + 350, ADMIN_MODIFY_DATA_INTERFACE_Y2 - 5); // 显示解封
        puthz(ADMIN_MODIFY_DATA_INTERFACE_X1 + 10, ADMIN_MODIFY_DATA_INTERFACE_Y2 - 25,
              "恢复账户：允许登陆，正常使用功能", 16, 16, MY_WHITE); // 显示解封
    }
    if (mouse_press(ADMIN_MODIFY_DATA_EXIT_X1, ADMIN_MODIFY_DATA_EXIT_Y1,
                    ADMIN_MODIFY_DATA_EXIT_X2, ADMIN_MODIFY_DATA_EXIT_Y2) == 1) // 点击返回
    {
        ch_input(NULL, NULL, NULL, NULL, NULL, INPUTBAR_CLEAR, NULL);
        memset(psw_buffer, '\0', sizeof(psw_buffer)); // 清空密码输入框
        *user_id = 0;
        *isReturn = 1; // 标记为返回
    }
}

void admin_handle_modify_ebike_data_event(LINKLIST *LIST, unsigned long *user_id, int *isReturn)
{ // 函数将在返回时清理user_id
    MODIFY_EBIKE_DATA_BUFFER temp = {"\0", "\0", "\0", "\0"};
    char buffer1[15];
    char buffer2[15];

    if (mouse_press(ADMIN_MODIFY_DATA_INPUTBAR3_X1, ADMIN_MODIFY_DATA_INPUTBAR3_Y1,
                    ADMIN_MODIFY_DATA_INPUTBAR3_X2, ADMIN_MODIFY_DATA_INPUTBAR3_Y2) == 1) // 点击电动车牌框
    {
        ch_input(temp.ebike_id_buffer, ADMIN_MODIFY_DATA_INPUTBAR3_X1, ADMIN_MODIFY_DATA_INPUTBAR3_Y1, 6, MY_LIGHTGRAY, INPUTBAR_NO_CLEAR, 1);
    }
    if (mouse_press(ADMIN_MODIFY_DATA_INPUTBAR4_X1, ADMIN_MODIFY_DATA_INPUTBAR4_Y1,
                    ADMIN_MODIFY_DATA_INPUTBAR4_X2, ADMIN_MODIFY_DATA_INPUTBAR4_Y2) == 1) // 点击牌证号码框
    {
        ch_input(temp.ebike_license_buffer, ADMIN_MODIFY_DATA_INPUTBAR4_X1, ADMIN_MODIFY_DATA_INPUTBAR4_Y1, 8, MY_LIGHTGRAY, INPUTBAR_NO_CLEAR, 1);
    }
    if (mouse_press(ADMIN_MODIFY_DATA_INPUTBAR5_X1, ADMIN_MODIFY_DATA_INPUTBAR5_Y1,
                    ADMIN_MODIFY_DATA_INPUTBAR5_X2, ADMIN_MODIFY_DATA_INPUTBAR5_Y2) == 1) // 点击车辆年审框
    {
        ch_input(temp.anual_check_buffer, ADMIN_MODIFY_DATA_INPUTBAR5_X1, ADMIN_MODIFY_DATA_INPUTBAR5_Y1, 10, MY_LIGHTGRAY, INPUTBAR_NO_CLEAR, 1);
    }
    if (mouse_press(ADMIN_MODIFY_DATA_INPUTBAR5_X1, ADMIN_MODIFY_DATA_INPUTBAR5_Y1,
                    ADMIN_MODIFY_DATA_INPUTBAR5_X2, ADMIN_MODIFY_DATA_INPUTBAR5_Y2) == 1) // 点击位置框
    {
        ch_input(temp.location_buffer, ADMIN_MODIFY_DATA_INPUTBAR5_X1, ADMIN_MODIFY_DATA_INPUTBAR5_Y1, 14, MY_LIGHTGRAY, INPUTBAR_NO_CLEAR, 1);
    }

    if (mouse_press(ADMIN_MODIFY_DATA_SAVE_X1, ADMIN_MODIFY_DATA_SAVE_Y1,
                    ADMIN_MODIFY_DATA_SAVE_X2, ADMIN_MODIFY_DATA_SAVE_Y2) == 1) // 点击保存
    {
        if (admin_check_ebike_info(LIST, temp, *user_id) == 0) // 检查输入信息合理性，同时检查是否存在需要修改数据的目标
        {
            *user_id = 0;
            return;
        }
        // 保存修改后的用户信息到文件中
        if (strcmp(temp.ebike_id_buffer, "\0") != 0) // 修改电动车ID
        {
            modify_ebike_info(LIST, *user_id, temp.ebike_id_buffer, "ebike_id");
        }
        if (strcmp(temp.ebike_license_buffer, "\0") != 0) // 修改电动车牌
        {
            modify_ebike_info(LIST, *user_id, temp.ebike_license_buffer, "ebike_license");
        }
        if (strcmp(temp.anual_check_buffer, "\0") != 0) // 修改车辆年审
        {
            modify_ebike_info(LIST, *user_id, temp.anual_check_buffer, "anual_check");
        }
        if (strcmp(temp.location_buffer, "\0") != 0) // 修改车辆位置
        {
            modify_ebike_info(LIST, *user_id, temp.location_buffer, "location");
        }

        puthz(ADMIN_MODIFY_DATA_INTERFACE_X1 + 100, ADMIN_MODIFY_DATA_INTERFACE_Y1 + 10, "成功保存修改信息！", 16, 16, MY_GREEN); // 显示保存成功
        ch_input(NULL, NULL, NULL, NULL, NULL, INPUTBAR_CLEAR, NULL);
        memset(&temp, '\0', sizeof(temp)); // 清空缓冲区

        delay(500); // 延时
        *user_id = 0;
        *isReturn = 1; // 标记为返回
    }

    // 处理点击事件
    if (mouse_press(ADMIN_MODIFY_DATA_EXIT_X1, ADMIN_MODIFY_DATA_EXIT_Y1,
                    ADMIN_MODIFY_DATA_EXIT_X2, ADMIN_MODIFY_DATA_EXIT_Y2) == 1) // 点击返回
    {
        ch_input(NULL, NULL, NULL, NULL, NULL, INPUTBAR_CLEAR, NULL);
        memset(&temp, '\0', sizeof(temp)); // 清空缓冲区
        *user_id = 0;
        *isReturn = 1; // 标记为返回
    }
}

/**********************************************************
MODULE:其他杂项函数
***********************************************************/
// 点击按钮后，若能成功操作，则执行该显示动画
void admin_pass_failed_anime(int button_x1, int button_y1, int button_x2, int button_y2, int result)
{
    int mouse_flag;
    int tick = 0;
    clrmous(MouseX, MouseY); // 清除鼠标

    for (tick = 0; tick <= 80; tick++)
    {
        if (tick % 40 == 0)
        {
            setfillstyle(SOLID_FILL, GREEN);
            bar(button_x1, button_y1, button_x2, button_y2);
            if (result == PASSED)
                puthz(button_x1 + 4, button_y1 + 8, "通过成功", 16, 16, MY_WHITE); // 绘制按钮
            else if (result == FAILED)
                puthz(button_x1 + 4, button_y1 + 8, "驳回成功", 16, 16, MY_WHITE); // 绘制按钮
        }
        else if (tick % 40 == 20)
        {
            setfillstyle(SOLID_FILL, MY_YELLOW);
            bar(button_x1, button_y1, button_x2, button_y2);
            if (result == PASSED)
                puthz(button_x1 + 4, button_y1 + 8, "通过成功", 16, 16, MY_WHITE); // 绘制按钮
            else if (result == FAILED)
                puthz(button_x1 + 4, button_y1 + 8, "通过成功", 16, 16, MY_WHITE); // 绘制按钮
        }
        delay(25);
    }
    setfillstyle(SOLID_FILL, MY_YELLOW);
    bar(button_x1, button_y1, button_x2, button_y2);                   // 重绘按钮
    puthz(button_x1 + 4, button_y1 + 8, "同意申请", 16, 16, MY_WHITE); // 重新绘制按钮

    newmouse(&MouseX, &MouseY, &press, &mouse_flag); // 重新绘制
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

void define_admin_buttons(ADMIN_BUTTONS AdminButtons[], int page)
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
         ACTIVE_ADMIN_FEATURE_DOWN, &draw_flip_down, &clear_flip_down},
        {ADMIN_MODIFY_DATA_EXIT_X1, ADMIN_MODIFY_DATA_EXIT_X2,
         ADMIN_MODIFY_DATA_EXIT_Y1, ADMIN_MODIFY_DATA_EXIT_Y2,
         ACTIVE_ADMIN_MODIFY_EXIT, &draw_exit, &clear_exit},
        {ADMIN_MODIFY_DATA_SAVE_X1, ADMIN_MODIFY_DATA_SAVE_X2,
         ADMIN_MODIFY_DATA_SAVE_Y1, ADMIN_MODIFY_DATA_SAVE_Y2,
         ACTIVE_ADMIN_MODIFY_SAVE, &draw_accept, &clear_accept},
        {ADMIN_MODIFY_DATA_INPUTBAR1_X1, ADMIN_MODIFY_DATA_INPUTBAR1_X2,
         ADMIN_MODIFY_DATA_INPUTBAR1_Y1, ADMIN_MODIFY_DATA_INPUTBAR1_Y2,
         ACTIVE_ADMIN_MODIFY_INPUTBAR1, &draw_rectangle, &clear_rectangle},
        {ADMIN_MODIFY_DATA_INPUTBAR2_X1, ADMIN_MODIFY_DATA_INPUTBAR2_X2,
         ADMIN_MODIFY_DATA_INPUTBAR2_Y1, ADMIN_MODIFY_DATA_INPUTBAR2_Y2,
         ACTIVE_ADMIN_MODIFY_INPUTBAR2, &draw_rectangle, &clear_rectangle},
        {ADMIN_MODIFY_DATA_INPUTBAR3_X1, ADMIN_MODIFY_DATA_INPUTBAR3_X2,
         ADMIN_MODIFY_DATA_INPUTBAR3_Y1, ADMIN_MODIFY_DATA_INPUTBAR3_Y2,
         ACTIVE_ADMIN_MODIFY_INPUTBAR3, &draw_rectangle, &clear_rectangle},
        {ADMIN_MODIFY_DATA_INPUTBAR4_X1, ADMIN_MODIFY_DATA_INPUTBAR4_X2,
         ADMIN_MODIFY_DATA_INPUTBAR4_Y1, ADMIN_MODIFY_DATA_INPUTBAR4_Y2,
         ACTIVE_ADMIN_MODIFY_INPUTBAR4, &draw_rectangle, &clear_rectangle},
        {ADMIN_MODIFY_DATA_INPUTBAR5_X1, ADMIN_MODIFY_DATA_INPUTBAR5_X2,
         ADMIN_MODIFY_DATA_INPUTBAR5_Y1, ADMIN_MODIFY_DATA_INPUTBAR5_Y2,
         ACTIVE_ADMIN_MODIFY_INPUTBAR5, &draw_rectangle, &clear_rectangle},
        {ADMIN_MODIFY_DATA_INPUTBAR6_X1, ADMIN_MODIFY_DATA_INPUTBAR6_X2,
         ADMIN_MODIFY_DATA_INPUTBAR6_Y1, ADMIN_MODIFY_DATA_INPUTBAR6_Y2,
         ACTIVE_ADMIN_MODIFY_INPUTBAR6, &draw_rectangle, &clear_rectangle},
        {ADMIN_MODIFY_DATA_INPUTBAR7_X1, ADMIN_MODIFY_DATA_INPUTBAR7_X2,
         ADMIN_MODIFY_DATA_INPUTBAR7_Y1, ADMIN_MODIFY_DATA_INPUTBAR7_Y2,
         ACTIVE_ADMIN_MODIFY_INPUTBAR7, &draw_rectangle, &clear_rectangle},
        // 28
        // 以下为用户信息修改按钮
        {ADMIN_MODIFY_DATA_FREEZE_X1, ADMIN_MODIFY_DATA_FREEZE_X2,
         ADMIN_MODIFY_DATA_FREEZE_Y1, ADMIN_MODIFY_DATA_FREEZE_Y2,
         ACTIVE_ADMIN_MODIFY_FREEZE, &draw_rectangle, &clear_rectangle},
        {ADMIN_MODIFY_DATA_BAN_X1, ADMIN_MODIFY_DATA_BAN_X2,
         ADMIN_MODIFY_DATA_BAN_Y1, ADMIN_MODIFY_DATA_BAN_Y2,
         ACTIVE_ADMIN_MODIFY_BAN, &draw_rectangle, &clear_rectangle},
        {ADMIN_MODIFY_DATA_RESTORE_X1, ADMIN_MODIFY_DATA_RESTORE_X2,
         ADMIN_MODIFY_DATA_RESTORE_Y1, ADMIN_MODIFY_DATA_RESTORE_Y2,
         ACTIVE_ADMIN_MODIFY_RESTORE, &draw_rectangle, &clear_rectangle},
        // 31
        // 以下为消息按钮
        {ADMIN_MESSAGE_REPLY_X1, ADMIN_MESSAGE_REPLY_X2,
         ADMIN_MESSAGE_REPLY_Y1, ADMIN_MESSAGE_REPLY_Y2,
         ACTIVE_ADMIN_MESSAGE_REPLY, &draw_rectangle, &clear_rectangle},
        {ADMIN_MESSAGE_EXIT_X1, ADMIN_MESSAGE_EXIT_X2,
         ADMIN_MESSAGE_EXIT_Y1, ADMIN_MESSAGE_EXIT_Y2,
         ACTIVE_ADMIN_MESSAGE_EXIT, &draw_exit, &clear_exit},
    };
    int i;
    int j;

    if (page == MAIN_ADMIN)
    {
        for (i = 0, j = 0; i < 9; i++, j++)
        {
            admin_get_buttons(&AdminButtons[j], &Examples[i]);
        }
    }
    else if (
        page == ADMIN_BIKE_REGISTER ||
        page == ADMIN_BIKE_LICENSE ||
        page == ADMIN_BIKE_BROKEN ||
        page == ADMIN_BIKE_VIOLATION ||
        page == ADMIN_BIKE_ANUAL ||
        page == ADMIN_DATABASE)
    {
        for (i = 0, j = 0; i < 19; i++, j++)
        {
            admin_get_buttons(&AdminButtons[j], &Examples[i]);
        }
    }
    else if (page == ADMIN_MODIFY_DATA_USER_INFO)
    {
        for (i = 19, j = 0; i < 21; i++, j++)
        {
            admin_get_buttons(&AdminButtons[j], &Examples[i]);
        }
        admin_get_buttons(&AdminButtons[2], &Examples[23]);
        admin_get_buttons(&AdminButtons[3], &Examples[28]);
        admin_get_buttons(&AdminButtons[4], &Examples[29]);
        admin_get_buttons(&AdminButtons[5], &Examples[30]);
    }
    else if (page == ADMIN_MESSAGE)
    {
        admin_get_buttons(&AdminButtons[0], &Examples[19]);
        admin_get_buttons(&AdminButtons[1], &Examples[31]);
        admin_get_buttons(&AdminButtons[2], &Examples[32]);
    }
    else if (page == ADMIN_MESSAGE_REPLY)
    {
        admin_get_buttons(&AdminButtons[0], &Examples[19]);
        admin_get_buttons(&AdminButtons[1], &Examples[20]);
    }
}

void admin_get_buttons(ADMIN_BUTTONS *AdminButtons, ADMIN_BUTTONS *Examples)
{
    AdminButtons->x1 = Examples->x1;
    AdminButtons->x2 = Examples->x2;
    AdminButtons->y1 = Examples->y1;
    AdminButtons->y2 = Examples->y2;
    AdminButtons->active_tag = Examples->active_tag;
    AdminButtons->drawfunc = Examples->drawfunc;
    AdminButtons->clearfunc = Examples->clearfunc;
}

void draw_person(int x1, int y1, int x2, int y2)
{
    setfillstyle(SOLID_FILL, MY_YELLOW);
    bar(x1 - 3, y1 - 3, x2 + 3, y2 + 3);
    setcolor(MY_BLACK);
    setfillstyle(SOLID_FILL, MY_BLACK);
    pieslice(x1 + 10, y1 + 7, 0, 360, 6);   // 绘制人头
    pieslice(x1 + 10, y1 + 22, 0, 180, 11); // 绘制身体
}
void clear_person(int x1, int y1, int x2, int y2)
{
    setfillstyle(SOLID_FILL, MY_YELLOW);
    bar(x1 - 3, y1 - 3, x2 + 3, y2 + 3);
    setcolor(MY_BLACK);
    setfillstyle(SOLID_FILL, MY_BLACK);
    pieslice(x1 + 10, y1 + 7, 0, 360, 5);   // 绘制人头
    pieslice(x1 + 10, y1 + 22, 0, 180, 10); // 绘制身体
}

void draw_cues(int x, int y, int null1, int null2)
{
    setcolor(MY_GREEN);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    line(x - 10, y + 23, x, y + 23);
    line(x - 5, y + 18, x, y + 23);
    line(x - 5, y + 28, x, y + 23);
}
void clear_cues(int x1, int y1, int x2, int y2)
{
    setfillstyle(SOLID_FILL, MY_YELLOW);
    bar(x1 - 13, y1 + 6, x2 - 79, y2);
}

void draw_accept(int x1, int y1, int x2, int y2)
{
    setfillstyle(SOLID_FILL, MY_YELLOW);
    bar(x1 - 1, y1 - 1, x2 + 1, y2 + 1);

    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    setcolor(MY_GREEN);
    line(x1, y1 + 10, x1 + 10, y2);
    line(x1 + 10, y2, x2, y1);
}
void clear_accept(int x1, int y1, int x2, int y2)
{
    setfillstyle(SOLID_FILL, MY_YELLOW);
    bar(x1 - 1, y1 - 1, x2 + 1, y2 + 1);

    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    setcolor(MY_GREEN);
    line(x1, y1 + 10, x1 + 10, y2);
    line(x1 + 10, y2, x2, y1);
}

void draw_rectangle(int x1, int y1, int x2, int y2)
{
    setcolor(MY_WHITE);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    rectangle(x1 - 2, y1 - 2, x2 + 2, y2 + 2);
}
void clear_rectangle(int x1, int y1, int x2, int y2)
{
    setcolor(MY_LIGHTGRAY);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    rectangle(x1 - 2, y1 - 2, x2 + 2, y2 + 2);
}

void draw_exit(int x1, int y1, int x2, int y2)
{
    setcolor(MY_RED);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    line(x1, y1, x2, y2);
    line(x2, y1, x1, y2);
}
void clear_exit(int x1, int y1, int x2, int y2)
{
    setfillstyle(SOLID_FILL, MY_YELLOW);
    bar(x1 - 1, y1 - 1, x2 + 1, y2 + 1);

    setcolor(MY_RED);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    line(x1, y1, x2, y2);
    line(x2, y1, x1, y2);
}

void draw_exit_menu(int x1, int y1, int x2, int y2)
{
    setcolor(MY_BLACK);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    rectangle(x1, y1, x2, y2);
    puthz(x1 + 2, y1 + 7, "退出登录", 16, 16, MY_WHITE);
    puthz(x1 + 2, y1 + 29, "退出程序", 16, 16, MY_WHITE);
}
void clear_exit_menu(int x1, int y1, int x2, int y2)
{
    setfillstyle(SOLID_FILL, MY_YELLOW);
    bar(x1, y1, x2, y2);
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

int admin_exitting(int *page)
{
    int mouse_flag;
    draw_exit_menu(ADMIN_EXIT_MENU_X1, ADMIN_EXIT_MENU_Y1, ADMIN_EXIT_MENU_X2, ADMIN_EXIT_MENU_Y2);
    while (1)
    {
        newmouse(&MouseX, &MouseY, &press, &mouse_flag);
        if (mouse_press(ADMIN_EXIT_MENU_X1 + 2, ADMIN_EXIT_MENU_Y1 + 5, ADMIN_EXIT_MENU_X1 + 60, ADMIN_EXIT_MENU_Y1 + 21) == 1)
        {
            *page = LOGIN_ADMIN;
            clrmous(MouseX, MouseY);
            admin_list_info(NULL, LIST_LIMIT, LIST_INTERVAL, NULL, NULL, NULL, NULL, NULL, NULL, LIST_CLEAR, NULL, NULL);
            ch_input(NULL, NULL, NULL, NULL, NULL, INPUTBAR_CLEAR, NULL);
            return 0;
        }
        else if (mouse_press(ADMIN_EXIT_MENU_X1 + 2, ADMIN_EXIT_MENU_Y1 + 30, ADMIN_EXIT_MENU_X1 + 60, ADMIN_EXIT_MENU_Y1 + 46) == 1)
        {
            *page = EXIT;
            clrmous(MouseX, MouseY);
            admin_list_info(NULL, LIST_LIMIT, LIST_INTERVAL, NULL, NULL, NULL, NULL, NULL, NULL, LIST_CLEAR, NULL, NULL);
            ch_input(NULL, NULL, NULL, NULL, NULL, INPUTBAR_CLEAR, NULL);
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
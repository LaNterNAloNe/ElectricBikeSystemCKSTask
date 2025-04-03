#include"_ADMIN_.H"

/*****************************************************************
MODULE:管理员主菜单
*****************************************************************/
void main_admin(int *page,int *ID){
    int tag=ACTIVE_ADMIN_NULL;
    ADMIN_BUTTONS AdminButtons[7]={
        {ADMIN_BUTTON1_X1, ADMIN_BUTTON1_X2, 
         ADMIN_BUTTON1_Y1, ADMIN_BUTTON1_Y2, 
         ACTIVE_ADMIN_BUTTON1,&draw_cues,&clear_cues},
        {ADMIN_BUTTON2_X1, ADMIN_BUTTON2_X2, 
         ADMIN_BUTTON2_Y1, ADMIN_BUTTON2_Y2, 
         ACTIVE_ADMIN_BUTTON2,&draw_cues,&clear_cues},
        {ADMIN_BUTTON3_X1, ADMIN_BUTTON3_X2, 
         ADMIN_BUTTON3_Y1, ADMIN_BUTTON3_Y2, 
         ACTIVE_ADMIN_BUTTON3,&draw_cues,&clear_cues},
        {ADMIN_BUTTON4_X1, ADMIN_BUTTON4_X2, 
         ADMIN_BUTTON4_Y1, ADMIN_BUTTON4_Y2, 
         ACTIVE_ADMIN_BUTTON4,&draw_cues,&clear_cues},
        {ADMIN_BUTTON5_X1, ADMIN_BUTTON5_X2, 
         ADMIN_BUTTON5_Y1, ADMIN_BUTTON5_Y2, 
         ACTIVE_ADMIN_BUTTON5,&draw_cues,&clear_cues},
        {ADMIN_BUTTON6_X1, ADMIN_BUTTON6_X2, 
         ADMIN_BUTTON6_Y1, ADMIN_BUTTON6_Y2, 
         ACTIVE_ADMIN_BUTTON6,&draw_cues,&clear_cues},
        {ADMIN_EXIT_X1,ADMIN_EXIT_X2,
         ADMIN_EXIT_Y1,ADMIN_EXIT_Y2,
         ACTIVE_ADMIN_EXIT,&draw_exit,&clear_exit}
    };

    

    clrmous(MouseX, MouseY);
    drawgraph_admin_menu(); // 初始化界面
    mouseinit();

    if(debug_mode == 1) display_memory_usage(400, 10); // 左上角显示 

    while(*page == MAIN_ADMIN){
        admin_flush_graph(&tag,STRUCT_LENGTH(AdminButtons),AdminButtons);
        handle_click_event_admin_main(page);
        //应该在传入AdminButtons前计算其长度，传入函数后，使用sizeof计算其长度则会退化为指针长度，导致功能失效
        newmouse(&MouseX, &MouseY, &press);

        delay(25);
    }
    
}



void drawgraph_admin_menu(void){
    int i;

    /*** 绘制菜单 ***/
    setfillstyle(SOLID_FILL, MY_YELLOW);
    bar(ADMIN_MENU_X1, ADMIN_MENU_Y1, ADMIN_MENU_X2, ADMIN_MENU_Y2);
    setcolor(BLUE);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    rectangle(ADMIN_MENU_X1+2, ADMIN_MENU_Y1+2, ADMIN_MENU_X2-2, ADMIN_MENU_Y2-2);
    setcolor(MY_BLACK);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    rectangle(ADMIN_MENU_X1+2, ADMIN_MENU_Y1+2, ADMIN_MENU_X2-2, ADMIN_MENU_Y2-2);

    /*** 绘制交互界面（暂为空白） ***/
    setfillstyle(SOLID_FILL, BLUE);
    bar(ADMIN_INTERFACE_X1, ADMIN_INTERFACE_Y1, ADMIN_INTERFACE_X2, ADMIN_INTERFACE_Y2);
    setcolor(CYAN);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    rectangle(ADMIN_INTERFACE_X1+2, ADMIN_INTERFACE_Y1+2, ADMIN_INTERFACE_X2-2, ADMIN_INTERFACE_Y2-2);
    setcolor(MY_LIGHTGRAY);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    rectangle(ADMIN_INTERFACE_X1+2, ADMIN_INTERFACE_Y1+2, ADMIN_INTERFACE_X2-2, ADMIN_INTERFACE_Y2-2);

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
    for(i=0;i<6;i++) {
        setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
        line(ADMIN_MENU_X1+10,ADMIN_MENU_Y1+45+i*40,ADMIN_MENU_X2-10,ADMIN_MENU_Y1+45+i*40);
        setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
        line(ADMIN_MENU_X1+6,ADMIN_MENU_Y1+45+i*40,ADMIN_MENU_X2-6,ADMIN_MENU_Y1+45+i*40);
        delay(10);
    }
    puthz(ADMIN_MENU_X1+25, ADMIN_MENU_Y1+25, "车辆注册",16,18,MY_WHITE);// 输出文本
    puthz(ADMIN_MENU_X1+25, ADMIN_MENU_Y1+65, "上牌管理",16,18,MY_WHITE);// 输出文本
    puthz(ADMIN_MENU_X1+25, ADMIN_MENU_Y1+105, "车辆报废",16,18,MY_WHITE);// 输出文本
    puthz(ADMIN_MENU_X1+25, ADMIN_MENU_Y1+145, "违规车辆",16,18,MY_WHITE);// 输出文本
    puthz(ADMIN_MENU_X1+25, ADMIN_MENU_Y1+185, "数据一览",16,18,MY_WHITE);// 输出文本
    puthz(ADMIN_MENU_X1+25, ADMIN_MENU_Y1+225, "信息中心",16,18,MY_WHITE);// 输出文本


    clear_exit(ADMIN_EXIT_X1,ADMIN_EXIT_Y1,ADMIN_EXIT_X2,ADMIN_EXIT_Y2);

}

void handle_click_event_admin_main(int *page){
    if (mouse_press(ADMIN_EXIT_X1,ADMIN_EXIT_Y1,ADMIN_EXIT_X2,ADMIN_EXIT_Y2) == 1) {
        if(!admin_exitting(page)){
            AdminswitchPage();
            return;
        }
    }

    /*车辆注册*/
    if (mouse_press(ADMIN_BUTTON1_X1,ADMIN_BUTTON1_Y1,ADMIN_BUTTON1_X2,ADMIN_BUTTON1_Y2)==1 && 
        *page != ADMIN_BIKE_REGISTER) {
        *page = ADMIN_BIKE_REGISTER;
        return;
    }
    /*车辆上牌*/
    if (mouse_press(ADMIN_BUTTON2_X1, ADMIN_BUTTON2_Y1, ADMIN_BUTTON2_X2, ADMIN_BUTTON2_Y2) == 1 &&
        *page != ADMIN_BIKE_LICENSE){
        *page = ADMIN_BIKE_LICENSE;
        return;
    }
}



/*****************************************************************
MODULE:管理员车辆注册
*****************************************************************/
void admin_bike_register(int *page, int *ID, LINKLIST *LIST)
{
    int mode=0; // 搜索模式，列出已处理清单或待处理清单，主动清除该页面时重设为0（默认列出待处理清单）
    // static int visited=0; // 是否进入乐该页面，主动清除该页面时重设为0
    char search_str[10]; // 搜索框输入信息储存
    int selected_id = -1;
    int id_list[8] = {-1,-1,-1,-1,-1,-1,-1,-1}; // 记录当前显示的列表每行对应的ID
    int tag=ACTIVE_ADMIN_NULL;
    ADMIN_BUTTONS AdminButtons[17] = {
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
        {ADMIN_EXIT_X1, ADMIN_EXIT_X2,
         ADMIN_EXIT_Y1, ADMIN_EXIT_Y2,
         ACTIVE_ADMIN_EXIT, &draw_exit, &clear_exit},
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
         ACTIVE_ADMIN_FEATURE_DOWN, &draw_flip_down, &clear_flip_down}
    };

    FILE *fp_EBIKE_INFO_read = fopen("C:\\EBS\\DATA\\REGISTER.DAT","rb+");
    if(!fp_EBIKE_INFO_read) exit(1);
    fseek(fp_EBIKE_INFO_read,0,SEEK_SET);
    drawgraph_admin_menu();
    drawgraph_admin_bike_register();

    // 列出数据
    list_search_register_request(id_list, fp_EBIKE_INFO_read, "register", mode, 1, 2, "\0", "\0");

    if(debug_mode == 1) display_memory_usage(400, 10); // 左上角显示 

    while(*page == ADMIN_BIKE_REGISTER){
        admin_flush_graph(&tag,STRUCT_LENGTH(AdminButtons),AdminButtons);
        handle_click_event_admin_main(page);
        selected_id = handle_list_select_line_admin(page);
        newmouse(&MouseX,&MouseY,&press);

        handle_click_event_admin_bike_register(LIST, page, search_str, id_list, fp_EBIKE_INFO_read, &mode, selected_id); // 处理点击事件

        delay(25);
    }

    fclose(fp_EBIKE_INFO_read);
    list_search_register_request(NULL, NULL, NULL,NULL, NULL, 1, NULL, NULL);
    Input_Bar(NULL, NULL, NULL, NULL, NULL,1,NULL);
    return;
}

void handle_click_event_admin_bike_register(LINKLIST *LIST,int *page, char *search_str,int *id_list,FILE *fp_EBIKE_INFO_read,int *mode,int selected_id){
    int i;
    char buffer[50];
    EBIKE_INFO temp_info;
    LINKLIST_NODE *temp_node = LIST->HEAD; // LAST_NODE要找到链表中特定节点，先指向头结点
    int chain_pos = -1; // 链表位置
    time_t t = time(NULL);
    struct tm *tm = localtime(&t); // localtime和time都是time.h中的函数
    long int search_pos = 0; // 查找数据得到的位置

    
    if (mouse_press(ADMIN_FEATURE_EXIT_X1, ADMIN_FEATURE_EXIT_Y1, ADMIN_FEATURE_EXIT_X2, ADMIN_FEATURE_EXIT_Y2) == 1)
    {
        *page = MAIN_ADMIN;
    } // 当在功能界面点击叉，退出功能界面

    if (mouse_press(ADMIN_FEATURE_SEARCH_X1, ADMIN_FEATURE_SEARCH_Y1, ADMIN_FEATURE_SEARCH_X2, ADMIN_FEATURE_SEARCH_Y2) == 1 &&
        *page == ADMIN_BIKE_REGISTER)
    {
        Input_Bar(search_str, ADMIN_FEATURE_SEARCH_X1 + 25, ADMIN_FEATURE_SEARCH_Y1 + 2, 9, MY_LIGHTGRAY, 0, 1);

        selected_id = -1; // 清除选中行
        setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
        bar(ADMIN_INTERFACE_X1 + 10, ADMIN_INTERFACE_Y1 + 70, ADMIN_INTERFACE_X1 + 18, ADMIN_INTERFACE_Y1 + 310); // 清理所有选中行高亮

        list_search_register_request(id_list, fp_EBIKE_INFO_read, "register", *mode, 1, 0, search_str, "ID");
    } // 点击输入框后退回

    if (mouse_press(ADMIN_FEATURE3_X1, ADMIN_FEATURE3_Y1, ADMIN_FEATURE3_X2, ADMIN_FEATURE3_Y2) == 1 &&
        *mode == 0)
    {
        *mode = 1;
        setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
        bar(ADMIN_INTERFACE_X1 + 140, ADMIN_INTERFACE_Y1 + 10, ADMIN_INTERFACE_X1 + 230, ADMIN_INTERFACE_Y1 + 30);
        puthz(ADMIN_INTERFACE_X1 + 140, ADMIN_INTERFACE_Y1 + 10, "已处理项目", 16, 16, MY_WHITE);
        list_search_register_request(id_list, fp_EBIKE_INFO_read, "register", *mode, 1, 2, search_str, "ID");
    } // 点击已处理后显示已处理

    if (mouse_press(ADMIN_FEATURE4_X1, ADMIN_FEATURE4_Y1, ADMIN_FEATURE4_X2, ADMIN_FEATURE4_Y2) == 1 &&
        *mode == 1)
    {
        *mode = 0;
        setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
        bar(ADMIN_INTERFACE_X1 + 140, ADMIN_INTERFACE_Y1 + 10, ADMIN_INTERFACE_X1 + 230, ADMIN_INTERFACE_Y1 + 30);
        puthz(ADMIN_INTERFACE_X1 + 140, ADMIN_INTERFACE_Y1 + 10, "未处理项目", 16, 16, MY_WHITE);
        list_search_register_request(id_list, fp_EBIKE_INFO_read, "register", *mode, 1, 2, search_str, "ID");
    } // 点击未处理后显示未处理

    if (mouse_press(ADMIN_FEATURE1_X1, ADMIN_FEATURE1_Y1, ADMIN_FEATURE1_X2, ADMIN_FEATURE1_Y2) == 1 && selected_id != -1)
    {
        itoa(selected_id, buffer, 10);                                  // 将选中行的ID转化为字符串
        if ((chain_pos = linklist_find_data(LIST, buffer, "id")) == 0) // 查找链表中是否存在该ID
            return; // 选中行，点击同意申请，若出现未能找到数据的情况，则不进行任何操作

        search_pos = ebike_info_search(fp_EBIKE_INFO_read, buffer, "id"); // 查找数据块
        if (search_pos == 0)
            return; // 如果没有找到数据块，则不进行任何操作，若能找到，则进一步处理数据

        // 修改数据块
        sprintf(buffer, "%04d%02d%02d", tm->tm_year + 1900, tm->tm_mon+1,tm->tm_mday); // 格式化时间字符串
        fread(&temp_info, sizeof(EBIKE_INFO), 1, fp_EBIKE_INFO_read); // 读取数据块
        temp_info.conduct_time = atoi(buffer); // 将时间字符串转化为int型数据，并赋值给conduct_time
        temp_info.result = PASSED;          // 将result赋值为已处理

        fseek(fp_EBIKE_INFO_read, search_pos, SEEK_SET); // 定位到数据块
        fwrite(&temp_info, sizeof(EBIKE_INFO), 1, fp_EBIKE_INFO_read); // 将新数据写入数据块

        // 修改链表数据
        for (i = 0; i < chain_pos; i++){
            temp_node = temp_node->NEXT; // 遍历链表，找到对应节点
        }
        strcpy(temp_node->USER_DATA.ebike_ID, temp_info.ebike_ID); // 将链表中对应节点的ebike_ID修改为新数据
        

        AdminConductSuccess(ADMIN_FEATURE1_X1, ADMIN_FEATURE1_Y1, ADMIN_FEATURE1_X2, ADMIN_FEATURE1_Y2); // 操作成功后的动画
        // bar(200,200,300,300);
        // outtextxy(200,200,buffer); // 时间字符串调试

        list_search_register_request(id_list, fp_EBIKE_INFO_read, "register", *mode, 1, 3, "\0", "\0"); // 操作结束后刷新列表

    } // 点击同意申请
    if (mouse_press(ADMIN_FEATURE2_X1, ADMIN_FEATURE2_Y1, ADMIN_FEATURE2_X2, ADMIN_FEATURE2_Y2) == 1 && selected_id != -1)
    {
        itoa(selected_id, buffer, 10);
        if (!(chain_pos = linklist_find_data(LIST, buffer, "id")))
            return; // 选中行，点击同意申请，若出现未能找到数据的情况，则不进行任何操作

        search_pos = ebike_info_search(fp_EBIKE_INFO_read, buffer, "id"); // 查找数据块
        if (search_pos == 0)
            return; // 如果没有找到数据块，则不进行任何操作，若能找到，则进一步处理数据

        // 修改数据块
        sprintf(buffer, "%04d%02d%02d", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday); // 格式化时间字符串
        fread(&temp_info, sizeof(EBIKE_INFO), 1, fp_EBIKE_INFO_read);                     // 读取数据块
        temp_info.conduct_time = atoi(buffer);                                            // 将时间字符串转化为int型数据，并赋值给conduct_time
        temp_info.result = FAILED;                                                        // 将result赋值为已处理

        fseek(fp_EBIKE_INFO_read, search_pos, SEEK_SET);                                  // 定位到数据块
        fwrite(&temp_info, sizeof(EBIKE_INFO), 1, fp_EBIKE_INFO_read);                    // 将新数据写入数据块

        AdminConductSuccess(ADMIN_FEATURE1_X1, ADMIN_FEATURE1_Y1, ADMIN_FEATURE1_X2, ADMIN_FEATURE1_Y2); // 操作成功后的动画
        // bar(200,200,300,300);
        // outtextxy(200,200,buffer); // 时间字符串调试

        list_search_register_request(id_list, fp_EBIKE_INFO_read, "register", *mode, 1, 3, "\0", "\0"); // 操作结束后刷新列表
    }
}

void drawgraph_admin_bike_register(){
    puthz(ADMIN_INTERFACE_X1+5,ADMIN_INTERFACE_Y1+5,"车辆注册审核",24,20,MY_WHITE);
    puthz(ADMIN_INTERFACE_X1+140,ADMIN_INTERFACE_Y1+10,"待处理项目",16,16,MY_WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    outtextxy(ADMIN_INTERFACE_X1+130,ADMIN_INTERFACE_Y1+15,"-");
    puthz(ADMIN_INTERFACE_X1+20,ADMIN_INTERFACE_Y1+40,"姓名",16,16,MY_WHITE);
    puthz(ADMIN_INTERFACE_X1+100,ADMIN_INTERFACE_Y1+40,"学号",16,16,MY_WHITE);
    puthz(ADMIN_INTERFACE_X1+200,ADMIN_INTERFACE_Y1+40,"车辆车牌号",16,16,MY_WHITE);
    puthz(ADMIN_INTERFACE_X1+300,ADMIN_INTERFACE_Y1+40,"申请日期",16,16,MY_WHITE);
    puthz(ADMIN_INTERFACE_X1+400,ADMIN_INTERFACE_Y1+40,"处理情况",16,16,MY_WHITE);

    setfillstyle(SOLID_FILL,MY_YELLOW);
    bar(ADMIN_FEATURE1_X1,ADMIN_FEATURE1_Y1,ADMIN_FEATURE1_X2,ADMIN_FEATURE1_Y2);
    bar(ADMIN_FEATURE2_X1,ADMIN_FEATURE2_Y1,ADMIN_FEATURE2_X2,ADMIN_FEATURE2_Y2);
    bar(ADMIN_FEATURE3_X1,ADMIN_FEATURE3_Y1,ADMIN_FEATURE3_X2,ADMIN_FEATURE3_Y2);
    bar(ADMIN_FEATURE4_X1,ADMIN_FEATURE4_Y1,ADMIN_FEATURE4_X2,ADMIN_FEATURE4_Y2);
    bar(ADMIN_FEATURE5_X1,ADMIN_FEATURE5_Y1,ADMIN_FEATURE5_X2,ADMIN_FEATURE5_Y2);
    bar(ADMIN_FEATURE6_X1,ADMIN_FEATURE6_Y1,ADMIN_FEATURE6_X2,ADMIN_FEATURE6_Y2);
    puthz(ADMIN_FEATURE1_X1+4,ADMIN_FEATURE1_Y1+8,"同意申请",16,16,MY_WHITE);
    puthz(ADMIN_FEATURE2_X1+4,ADMIN_FEATURE2_Y1+8,"驳回申请",16,16,MY_WHITE);
    puthz(ADMIN_FEATURE3_X1+4,ADMIN_FEATURE3_Y1+8,"已处理",16,16,MY_WHITE);
    puthz(ADMIN_FEATURE4_X1+4,ADMIN_FEATURE4_Y1+8,"待处理",16,16,MY_WHITE);
    
    setfillstyle(SOLID_FILL,MY_LIGHTGRAY);
    bar(ADMIN_FEATURE_SEARCH_X1,ADMIN_FEATURE_SEARCH_Y1,ADMIN_FEATURE_SEARCH_X2,ADMIN_FEATURE_SEARCH_Y2);
    setcolor(MY_BLACK);
    setlinestyle(SOLID_LINE,0,NORM_WIDTH);
    rectangle(ADMIN_FEATURE_SEARCH_X1,ADMIN_FEATURE_SEARCH_Y1,ADMIN_FEATURE_SEARCH_X2,ADMIN_FEATURE_SEARCH_Y2);

    setlinestyle(SOLID_LINE,0,THICK_WIDTH); // 小放大镜，提示为搜索框
    line(ADMIN_FEATURE_SEARCH_X1+5,ADMIN_FEATURE_SEARCH_Y2-7,ADMIN_FEATURE_SEARCH_X1+12,ADMIN_FEATURE_SEARCH_Y2-14);
    circle(ADMIN_FEATURE_SEARCH_X1+16,ADMIN_FEATURE_SEARCH_Y2-18,5);

    // setfillstyle(SOLID_FILL,MY_GREEN);
    // bar(ADMIN_INTERFACE_X1+10,ADMIN_INTERFACE_Y1+70,ADMIN_INTERFACE_X1+500,ADMIN_INTERFACE_Y1+390); // 清理列表
    clear_exit(ADMIN_FEATURE_EXIT_X1,ADMIN_FEATURE_EXIT_Y1,ADMIN_FEATURE_EXIT_X2,ADMIN_FEATURE_EXIT_Y2);
    clear_flip_up(ADMIN_FEATURE_UP_X1, ADMIN_FEATURE_UP_Y1, ADMIN_FEATURE_UP_X2, ADMIN_FEATURE_UP_Y2);
    clear_flip_down(ADMIN_FEATURE_DOWN_X1, ADMIN_FEATURE_DOWN_Y1, ADMIN_FEATURE_DOWN_X2, ADMIN_FEATURE_DOWN_Y2);
}


//列表函数，用于列出注册请求
void list_search_register_request(int id_list[8],FILE *fp,char *list_mode,int search_mode,
    int page_change,int is_clear,char *search_str,char *search_needed){ 
    // page_change为1，向下列表，为-1，向上列表，为0，不翻页
    // mode为0，查找未处理，为1，查找已处理
    // is_clear为0，不做任何操作，为1，清理列表状态并不做任何操作，为2，清理列表状态并继续列表（重新开始列表）
    //         为3，从记录的start开始扫描重新列表（需搭配page_change=1使用）
    // list_mode为列表依据，"register"为列出注册请求，"license"为列出上牌请求, "broken"为列出报废请求， "violation"为列出违规请求
    // search_mode为搜过模式，0代表搜索未处理，1代表搜索已处理
    // search_str为搜索字符串，search_needed为搜索依据
    int i;
    int listed_item=0; // 列出的数量
    static int start=0; // 储存当前列表第一个所在的位置
    static int end=0; // 储存当前列表最后一个所在的位置
    int temp_start=0;
    int temp_end=0;
    int counts = 0;
    // int search_times = 0; // 记录搜索次数
    EBIKE_INFO TEMP;

    fseek(fp,0,SEEK_END); // 定位到文件末尾
    counts = ftell(fp)/sizeof(EBIKE_INFO);

    for (i = 0; i < 8; i++){
        id_list[i] = -1;
    } // 开始列表前一定清理列表记录

    switch (is_clear) { // 清理列表状态
        case 1:
            setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
            bar(ADMIN_INTERFACE_X1 + 10, ADMIN_INTERFACE_Y1 + 70, ADMIN_INTERFACE_X1 + 500, ADMIN_INTERFACE_Y1 + 350); // 清理列表
            start = 0;
            end = 0;
            return;
        case 2:
            setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
            bar(ADMIN_INTERFACE_X1 + 10, ADMIN_INTERFACE_Y1 + 70, ADMIN_INTERFACE_X1 + 500, ADMIN_INTERFACE_Y1 + 350); // 清理列表
            start = 0;
            end = 0;
            break;
        case 3:
            setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
            bar(ADMIN_INTERFACE_X1 + 10, ADMIN_INTERFACE_Y1 + 70, ADMIN_INTERFACE_X1 + 500, ADMIN_INTERFACE_Y1 + 350); // 清理列表
            end = start; // 从start开始扫描重新列表
            break;
    }

    if(counts && page_change == 1){ // 收到下翻指令，或改变当前列表状态后从七点开始重新刷新列表
        /*条件判断*/
        if(end >= counts-1) {
            return; // 如果end指向结尾的数据，则不做任何操作
        }
        fseek(fp,(end+1)*sizeof(TEMP),SEEK_SET); // 先判断接下来是否有可以列出的数据
        while(1){
            if(fread(&TEMP,sizeof(TEMP),1,fp)) { // 到文件末尾都没有发现可列表的，则不执行下翻列表操作
                return; 
            }
            if (list_admin_register_search_is_valid(TEMP, list_mode, search_str, search_needed, search_mode))
                break; // 下翻查找是一旦读到可以被列出的，则可以执行下翻列表操作
        }

        /*列表操作*/
        fseek(fp,(end+1)*sizeof(TEMP),SEEK_SET); // 经过while不返回到原函数则可移植性下翻列表操作
        start=++end;
        setfillstyle(SOLID_FILL,MY_LIGHTGRAY);
        bar(ADMIN_INTERFACE_X1+20,ADMIN_INTERFACE_Y1+70,ADMIN_INTERFACE_X1+500,ADMIN_INTERFACE_Y1+390); // 清理列表
        
        while(listed_item < 8){
            if(!fread(&TEMP,sizeof(TEMP),1,fp)) break; // 读取数据，直到达到文件末尾
            end++; // 先将end指向读取的数据的头部
            if (!list_admin_register_search_is_valid(TEMP, list_mode, search_str, search_needed, search_mode))
                continue; // 如果下翻读取时读到的数据不符条件，则进行下一轮循环

            list_info_admin(TEMP, listed_item, list_mode, ASCENDING); // 输出数据

            id_list[listed_item] = TEMP.ID;
            listed_item++;
        }
    }else if(counts && page_change == -1){ // 收到上翻指令
        /*条件判断*/
        if(start < 0) {
            return; // 如果start指向开头的数据，则不做任何操作
        }
        temp_start=start;
        temp_end=start;

        while (1){ // 当能进入这个循环，说明列表上页有可列出数据且溢出
            if(!temp_start) break; // 到文件开头都没有发现可列表的，则不执行上翻列表操作
            fseek(fp,(temp_start-1)*sizeof(TEMP),SEEK_SET);
            fread(&TEMP,sizeof(TEMP),1,fp); // 读取上一个数据块
            temp_end = --temp_start;
            if (list_admin_register_search_is_valid(TEMP, list_mode, search_str, search_needed, search_mode))
                break; // 上翻查找到一个可列出数据，则可以上翻
        }

        /*列表操作*/
        start = temp_start+1; // 查找到首个可以读取的数据，将实际的标记指向该数据，start另+1是要配合while中开头的fseek的语句
        end = temp_start;
        setfillstyle(SOLID_FILL,MY_LIGHTGRAY);
        bar(ADMIN_INTERFACE_X1+20,ADMIN_INTERFACE_Y1+70,ADMIN_INTERFACE_X1+500,ADMIN_INTERFACE_Y1+390); // 清理列表
        
        while(listed_item < 8){ // 由于此时是从后往前读取数据，因此是从下往上列表
            fseek(fp,(start-1)*sizeof(TEMP),SEEK_SET);
            fread(&TEMP,sizeof(TEMP),1,fp); // 读取数据，直到查找到未被处理的注册请求
            if (!list_admin_register_search_is_valid(TEMP, list_mode, search_str, search_needed, search_mode))
                continue; // 如果下翻读取时读到的数据不符条件，则进行下一轮循环

            list_info_admin(TEMP, listed_item, list_mode,DESCENDING); // 输出数据

            id_list[listed_item] = TEMP.ID;
            listed_item++;
        }
    }else if(counts && page_change == 0){ // 不翻页，输出原内容
        fseek(fp,(start)*sizeof(TEMP),SEEK_SET);
        while(listed_item < 8){
            if(!fread(&TEMP,sizeof(TEMP),1,fp)) { // 读取数据，直到查找到八个可列出数据
                return;
            }
            if (!list_admin_register_search_is_valid(TEMP, list_mode, search_str, search_needed, search_mode))
                continue; // 如果下翻读取时读到的数据不符条件，则进行下一轮循环

            list_info_admin(TEMP, listed_item, list_mode,ASCENDING); // 输出数据

            id_list[listed_item] = TEMP.ID;
            listed_item++;
        }

    }else{
        puthz(ADMIN_INTERFACE_X1+120,ADMIN_INTERFACE_Y1+70,"未找到对应数据或传入参数错误",16,16,MY_RED);
        return;
    }
}

void list_info_admin(EBIKE_INFO TEMP,int listed_item,char *list_mode,int list_sequence){
    char buffer[50];
    if(list_sequence == ASCENDING){
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
        puthz(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 70 + listed_item * 20, TEMP.rln, 16, 16, MY_WHITE); // 输出姓名
        itoa(TEMP.ID, buffer, 10);
        outtextxy(ADMIN_INTERFACE_X1 + 100, ADMIN_INTERFACE_Y1 + 70 + listed_item * LIST_INTERVAL, buffer);        // 输出ID
        outtextxy(ADMIN_INTERFACE_X1 + 200, ADMIN_INTERFACE_Y1 + 70 + listed_item * LIST_INTERVAL, TEMP.ebike_ID); // 输出电动车车牌号
        outtextxy(ADMIN_INTERFACE_X1 + 300, ADMIN_INTERFACE_Y1 + 70 + listed_item * LIST_INTERVAL, buffer);        // 输出请求时间

        if (TEMP.conduct_time == -1)
        { // 输出处理状态
            puthz(ADMIN_INTERFACE_X1 + 400, ADMIN_INTERFACE_Y1 + 70 + listed_item * LIST_INTERVAL, "未处理", 16, 16, MY_RED);
        }
        else
        {
            puthz(ADMIN_INTERFACE_X1 + 400, ADMIN_INTERFACE_Y1 + 70 + listed_item * LIST_INTERVAL, "已处理", 16, 16, MY_GREEN);
        }
    }
    else
    {
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
        puthz(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 310 - listed_item * LIST_INTERVAL, TEMP.rln, 16, 16, MY_WHITE); // 输出姓名
        itoa(TEMP.ID, buffer, 10);
        outtextxy(ADMIN_INTERFACE_X1 + 100, ADMIN_INTERFACE_Y1 + 310 - listed_item * LIST_INTERVAL, buffer);        // 输出ID
        outtextxy(ADMIN_INTERFACE_X1 + 200, ADMIN_INTERFACE_Y1 + 310 - listed_item * LIST_INTERVAL, TEMP.ebike_ID); // 输出电动车车牌号
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
}

int list_admin_register_search_is_valid(EBIKE_INFO TEMP,char *list_mode, char *search_str, char *search_needed, int search_mode)
{ // 判断一个数据块是否应该列出
    if (
        (TEMP.conduct_time != -1 && search_mode == 0 || TEMP.conduct_time > 0 && search_mode == 1) &&
        (!strcmp(list_mode,"register") || !strcmp(list_mode,"license")) &&
        (!strcmp(search_str, "\0") || TEMP.ID == atoi(search_str) && strcmp(search_needed, "ID"))
       )
        return 1;
    else return 0;
}

/*****************************************************************
MODULE:管理员车辆上牌
*****************************************************************/
void admin_bike_license(int *page, int *id, LINKLIST *LIST)
{
    char *search_str;
    int id_list[8];
    int mode = 0;
    int selected_id;
    int tag = ACTIVE_ADMIN_NULL;
    ADMIN_BUTTONS AdminButtons[17] = {
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
        {ADMIN_EXIT_X1, ADMIN_EXIT_X2,
         ADMIN_EXIT_Y1, ADMIN_EXIT_Y2,
         ACTIVE_ADMIN_EXIT, &draw_exit, &clear_exit},
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
         ACTIVE_ADMIN_FEATURE_DOWN, &draw_flip_down, &clear_flip_down}
    };
    FILE *fp_EBIKE_LICENSE_read = fopen("C:\\EBS\\DATA\\LICENSE.DAT", "rb+");
    if (!fp_EBIKE_LICENSE_read) exit(1);
    fseek(fp_EBIKE_LICENSE_read, 0, SEEK_SET);

    drawgraph_admin_menu();
    drawgraph_admin_bike_license(); // 画出界面

    if (debug_mode == 1)
        display_memory_usage(400, 10); // 左上角显示

    list_search_license_request(id_list, fp_EBIKE_LICENSE_read, mode, 1, 2, "\0", "\0");

    while(*page == ADMIN_BIKE_LICENSE)
    {
        admin_flush_graph(&tag, STRUCT_LENGTH(AdminButtons), AdminButtons);
        handle_click_event_admin_main(page);
        selected_id = handle_list_select_line_admin(id_list);
        newmouse(&MouseX, &MouseY, &press);

        if (mouse_press(ADMIN_FEATURE_EXIT_X1, ADMIN_FEATURE_EXIT_Y1, ADMIN_FEATURE_EXIT_X2, ADMIN_FEATURE_EXIT_Y2) == 1)
        {
            *page = MAIN_ADMIN;
        } // 当在功能界面点击叉，退出功能界面

        if (mouse_press(ADMIN_FEATURE_SEARCH_X1, ADMIN_FEATURE_SEARCH_Y1, ADMIN_FEATURE_SEARCH_X2, ADMIN_FEATURE_SEARCH_Y2) == 1 &&
            *page == ADMIN_BIKE_LICENSE)
        {
            Input_Bar(search_str, ADMIN_FEATURE_SEARCH_X1 + 25, ADMIN_FEATURE_SEARCH_Y1 + 2, 9, MY_LIGHTGRAY, 0, 1);
            list_search_license_request(id_list, fp_EBIKE_LICENSE_read, mode, 1, 0, search_str, "ID");
        } // 点击输入框后退回

        if (mouse_press(ADMIN_FEATURE3_X1, ADMIN_FEATURE3_Y1, ADMIN_FEATURE3_X2, ADMIN_FEATURE3_Y2) == 1 &&
            mode == 0)
        {
            mode = 1;
            setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
            bar(ADMIN_INTERFACE_X1 + 140, ADMIN_INTERFACE_Y1 + 10, ADMIN_INTERFACE_X1 + 230, ADMIN_INTERFACE_Y1 + 30);
            puthz(ADMIN_INTERFACE_X1 + 140, ADMIN_INTERFACE_Y1 + 10, "已处理项目", 16, 16, MY_WHITE);
            list_search_license_request(id_list, fp_EBIKE_LICENSE_read, mode, 1, 2, search_str, "ID");
        } // 点击已处理后显示已处理

        if (mouse_press(ADMIN_FEATURE4_X1, ADMIN_FEATURE4_Y1, ADMIN_FEATURE4_X2, ADMIN_FEATURE4_Y2) == 1 &&
            mode == 1)
        {
            mode = 0;
            setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
            bar(ADMIN_INTERFACE_X1 + 140, ADMIN_INTERFACE_Y1 + 10, ADMIN_INTERFACE_X1 + 230, ADMIN_INTERFACE_Y1 + 30);
            puthz(ADMIN_INTERFACE_X1 + 140, ADMIN_INTERFACE_Y1 + 10, "未处理项目", 16, 16, MY_WHITE);
            list_search_license_request(id_list, fp_EBIKE_LICENSE_read, mode, 1, 2, search_str, "ID");
        } // 点击未处理后显示未处理
    }
    fclose(fp_EBIKE_LICENSE_read);
}

void drawgraph_admin_bike_license()
{
    puthz(ADMIN_INTERFACE_X1 + 5, ADMIN_INTERFACE_Y1 + 5, "车辆上牌审核", 24, 20, MY_WHITE);
    puthz(ADMIN_INTERFACE_X1 + 140, ADMIN_INTERFACE_Y1 + 10, "待处理项目", 16, 16, MY_WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    outtextxy(ADMIN_INTERFACE_X1 + 130, ADMIN_INTERFACE_Y1 + 15, "-");
    puthz(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 40, "姓名", 16, 16, MY_WHITE);
    puthz(ADMIN_INTERFACE_X1 + 100, ADMIN_INTERFACE_Y1 + 40, "学号", 16, 16, MY_WHITE);
    puthz(ADMIN_INTERFACE_X1 + 200, ADMIN_INTERFACE_Y1 + 40, "车辆车牌号", 16, 16, MY_WHITE);
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
    puthz(ADMIN_FEATURE3_X1 + 4, ADMIN_FEATURE3_Y1 + 8, "已处理", 16, 16, MY_WHITE);
    puthz(ADMIN_FEATURE4_X1 + 4, ADMIN_FEATURE4_Y1 + 8, "待处理", 16, 16, MY_WHITE);

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

    clear_exit(ADMIN_FEATURE_EXIT_X1,ADMIN_FEATURE_EXIT_Y1,ADMIN_FEATURE_EXIT_X2,ADMIN_FEATURE_EXIT_Y2);
    clear_flip_up(ADMIN_FEATURE_UP_X1, ADMIN_FEATURE_UP_Y1, ADMIN_FEATURE_UP_X2, ADMIN_FEATURE_UP_Y2);
    clear_flip_down(ADMIN_FEATURE_DOWN_X1, ADMIN_FEATURE_DOWN_Y1, ADMIN_FEATURE_DOWN_X2, ADMIN_FEATURE_DOWN_Y2);
}

void list_search_license_request(int id_list[8], FILE *fp, int mode, int page_change, int is_clear, char *search_str, char *search_needed)
{
    // page_change为1，向下列表，为-1，向上列表，为0，不翻页
    // mode为0，查找未处理，为1，查找已处理
    // is_clear为0，不做任何操作，为1，清理列表状态并不做任何操作，为2，清理列表状态并继续列表（重新开始列表）
    int i;
    int listed_item = 0;  // 列出的数量
    static int start = 0; // 储存当前列表第一个所在的位置
    static int end = 0;   // 储存当前列表最后一个所在的位置
    int temp_start = 0;
    int temp_end = 0;
    int counts = 0;
    // int search_times = 0; // 记录搜索次数
    char buffer[50];
    EBIKE_INFO TEMP;
    counts = ftell(fp) / sizeof(EBIKE_INFO);

    for (i = 0; i < 8; i++)
    {
        id_list[i] = -1;
    } // 开始列表前一定清理列表记录

    if (is_clear)
    {
        bar(ADMIN_INTERFACE_X1 + 10, ADMIN_INTERFACE_Y1 + 70, ADMIN_INTERFACE_X1 + 500, ADMIN_INTERFACE_Y1 + 350); // 清理列表
        start = 0;
        end = 0;
        if (is_clear == 1)
            return;
    }

    if (counts && page_change == 1)
    { // 收到下翻指令
        /*条件判断*/
        if (end = counts - 1)
        {
            return; // 如果end指向结尾的数据，则不做任何操作
        }
        fseek(fp, (end + 1) * sizeof(TEMP), SEEK_SET); // 先判断接下来是否有可以列出的数据
        while (1)
        {
            if (fread(&TEMP, sizeof(TEMP), 1, fp))
            { // 到文件末尾都没有发现可列表的，则不执行下翻列表操作
                return;
            }
            if (list_admin_license_search_is_valid(TEMP, search_str, search_needed, mode))
                break; // 下翻查找是一旦读到可以被列出的，则可以执行下翻列表操作
        }

        /*列表操作*/
        fseek(fp, (end + 1) * sizeof(TEMP), SEEK_SET); // 经过while不返回到原函数则可移植性下翻列表操作
        start = ++end;
        setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
        bar(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 70, ADMIN_INTERFACE_X1 + 500, ADMIN_INTERFACE_Y1 + 390); // 清理列表

        while (listed_item < 8)
        {
            if (!fread(&TEMP, sizeof(TEMP), 1, fp))
                break; // 读取数据，直到达到文件末尾
            end++;     // 先将end指向读取的数据的头部
            if (!list_admin_license_search_is_valid(TEMP, search_str, search_needed, mode))
                continue; // 如果下翻读取时读到的数据不符条件，则进行下一轮循环

            settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
            puthz(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 70 + listed_item * 20, TEMP.rln, 16, 16, MY_WHITE); // 输出姓名
            itoa(TEMP.ID, buffer, 10);
            outtextxy(ADMIN_INTERFACE_X1 + 100, ADMIN_INTERFACE_Y1 + 70 + listed_item * LIST_INTERVAL, buffer);        // 输出ID
            outtextxy(ADMIN_INTERFACE_X1 + 200, ADMIN_INTERFACE_Y1 + 70 + listed_item * LIST_INTERVAL, TEMP.ebike_ID); // 输出电动车车牌号
            outtextxy(ADMIN_INTERFACE_X1 + 300, ADMIN_INTERFACE_Y1 + 70 + listed_item * LIST_INTERVAL, buffer);        // 输出请求时间

            if (TEMP.conduct_time == -1)
            { // 输出处理状态
                puthz(ADMIN_INTERFACE_X1 + 400, ADMIN_INTERFACE_Y1 + 70 + listed_item * LIST_INTERVAL, "未处理", 16, 16, MY_RED);
            }
            else
            {
                puthz(ADMIN_INTERFACE_X1 + 400, ADMIN_INTERFACE_Y1 + 70 + listed_item * LIST_INTERVAL, "已处理", 16, 16, MY_GREEN);
            }
            id_list[listed_item] = TEMP.ID;
            listed_item++;
        }
    }
    else if (counts && page_change == -1)
    { // 收到上翻指令
        /*条件判断*/
        if (!start)
        {
            return; // 如果start指向开头的数据，则不做任何操作
        }
        temp_start = start;
        temp_end = start;

        while (1)
        { // 当能进入这个循环，说明列表上页有可列出数据且溢出
            if (!temp_start)
                break; // 到文件开头都没有发现可列表的，则不执行下翻列表操作
            fseek(fp, (temp_start - 1) * sizeof(TEMP), SEEK_SET);
            fread(&TEMP, sizeof(TEMP), 1, fp); // 读取上一个数据块
            temp_end = --temp_start;
            if (list_admin_license_search_is_valid(TEMP, search_str, search_needed, mode))
                break; // 上翻查找到一个可列出数据，则可以上翻
        }

        /*列表操作*/
        start = temp_start + 1; // 查找到首个可以读取的数据，将实际的标记指向该数据，start另+1是要配合while中开头的fseek的语句
        end = temp_start;
        setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
        bar(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 70, ADMIN_INTERFACE_X1 + 500, ADMIN_INTERFACE_Y1 + 390); // 清理列表

        while (listed_item < 8)
        { // 由于此时是从后往前读取数据，因此是从下往上列表
            fseek(fp, (start - 1) * sizeof(TEMP), SEEK_SET);
            fread(&TEMP, sizeof(TEMP), 1, fp); // 读取数据，直到查找到未被处理的注册请求
            if (!list_admin_license_search_is_valid(TEMP, search_str, search_needed, mode))
                continue; // 如果下翻读取时读到的数据不符条件，则进行下一轮循环

            settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
            puthz(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 310 - listed_item * LIST_INTERVAL, TEMP.rln, 16, 16, MY_WHITE); // 输出姓名
            itoa(TEMP.ID, buffer, 10);
            outtextxy(ADMIN_INTERFACE_X1 + 100, ADMIN_INTERFACE_Y1 + 310 - listed_item * LIST_INTERVAL, buffer);        // 输出ID
            outtextxy(ADMIN_INTERFACE_X1 + 200, ADMIN_INTERFACE_Y1 + 310 - listed_item * LIST_INTERVAL, TEMP.ebike_ID); // 输出电动车车牌号
            outtextxy(ADMIN_INTERFACE_X1 + 300, ADMIN_INTERFACE_Y1 + 310 - listed_item * LIST_INTERVAL, buffer);        // 输出请求时间

            if (TEMP.conduct_time == -1)
            { // 输出处理状态
                puthz(ADMIN_INTERFACE_X1 + 400, ADMIN_INTERFACE_Y1 + 310 - listed_item * LIST_INTERVAL, "未处理", 16, 16, MY_RED);
            }
            else
            {
                puthz(ADMIN_INTERFACE_X1 + 400, ADMIN_INTERFACE_Y1 + 310 - listed_item * LIST_INTERVAL, "已处理", 16, 16, MY_GREEN);
            }
            id_list[listed_item] = TEMP.ID;
            listed_item++;
        }
    }
    else if (counts && page_change == 0)
    { // 不翻页，输出原内容
        fseek(fp, (start) * sizeof(TEMP), SEEK_SET);
        while (listed_item < 8)
        {
            if (!fread(&TEMP, sizeof(TEMP), 1, fp))
            { // 读取数据，直到查找到八个可列出数据
                return;
            }
            if (!list_admin_license_search_is_valid(TEMP, search_str, search_needed, mode))
                continue; // 如果下翻读取时读到的数据不符条件，则进行下一轮循环

            settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
            puthz(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 70 + listed_item * 20, TEMP.rln, 16, 16, MY_WHITE); // 输出姓名
            itoa(TEMP.ID, buffer, 10);
            outtextxy(ADMIN_INTERFACE_X1 + 100, ADMIN_INTERFACE_Y1 + 70 + listed_item * LIST_INTERVAL, buffer);        // 输出ID
            outtextxy(ADMIN_INTERFACE_X1 + 200, ADMIN_INTERFACE_Y1 + 70 + listed_item * LIST_INTERVAL, TEMP.ebike_ID); // 输出电动车车牌号
            outtextxy(ADMIN_INTERFACE_X1 + 300, ADMIN_INTERFACE_Y1 + 70 + listed_item * LIST_INTERVAL, buffer);        // 输出请求时间

            if (TEMP.conduct_time == -1)
            { // 输出处理状态
                puthz(ADMIN_INTERFACE_X1 + 400, ADMIN_INTERFACE_Y1 + 70 + listed_item * LIST_INTERVAL, "未处理", 16, 16, MY_RED);
            }
            else
            {
                puthz(ADMIN_INTERFACE_X1 + 400, ADMIN_INTERFACE_Y1 + 70 + listed_item * LIST_INTERVAL, "已处理", 16, 16, MY_GREEN);
            }
            id_list[listed_item] = TEMP.ID;
            listed_item++;
        }
    }
    else
    {
        puthz(ADMIN_INTERFACE_X1 + 120, ADMIN_INTERFACE_Y1 + 70, "未找到对应数据或传入参数错误", 16, 16, MY_RED);
        return;
    }
}

int list_admin_license_search_is_valid(EBIKE_INFO TEMP, char *search_str, char *search_needed, int mode)
{ // 判断一个数据块是否应该列出
    if ((TEMP.conduct_time != -1 && mode == 0 ||
         TEMP.conduct_time > 0 && mode == 1) &&
        (!strcmp(search_str, "\0") ||
         !strcmp(TEMP.rln, search_str) && strcmp(search_needed, "realname") ||
         TEMP.ID == atoi(search_str) && strcmp(search_needed, "ID") ||
         !strcmp(TEMP.ebike_ID, search_str) && strcmp(search_needed, "ebikeID")))
        return 1;
    else
        return 0;
}

/*****************************************************************
MODULE:刷新画面和处理鼠标点击的画图函数
*****************************************************************/
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

int admin_exitting(int *page){
    draw_exit_menu(ADMIN_EXIT_MENU_X1,ADMIN_EXIT_MENU_Y1,ADMIN_EXIT_MENU_X2,ADMIN_EXIT_MENU_Y2);
    while(1){
        newmouse(&MouseX, &MouseY, &press);
        if(mouse_press(ADMIN_EXIT_MENU_X1+2,ADMIN_EXIT_MENU_Y1+5,ADMIN_EXIT_MENU_X1+60,ADMIN_EXIT_MENU_Y1+21)==1){
            *page = LOGIN_ADMIN;
            return 0;
        }else if(mouse_press(ADMIN_EXIT_MENU_X1+2,ADMIN_EXIT_MENU_Y1+30,ADMIN_EXIT_MENU_X1+60,ADMIN_EXIT_MENU_Y1+46)==1){
            *page = EXIT;
            return 0;
        }else if(mouse_press(0,0,640,480)==1 && mouse_press(ADMIN_EXIT_X1,ADMIN_EXIT_Y1,ADMIN_EXIT_X2,ADMIN_EXIT_Y2)==-1){
            clear_exit_menu(ADMIN_EXIT_MENU_X1,ADMIN_EXIT_MENU_Y1,ADMIN_EXIT_MENU_X2,ADMIN_EXIT_MENU_Y2);
            return 1;
        }
    }
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
// 2025.3.19 出错：连个静态变量索引导入结构体数组导致越界。通过将其定义值改为0暂时解决
void admin_flush_graph(int *tag,int button_counts,ADMIN_BUTTONS AdminButtons[]){
    int i;
    int new_tag = ACTIVE_ADMIN_NULL;
    static int last_active_index = 0;
    static int current_active_index = 0;
    
    // 检查鼠标是否在任一按钮区域内
    for (i = 0; i < button_counts; i++) {
        if (MouseX >= AdminButtons[i].x1 && MouseX <= AdminButtons[i].x2 &&
            MouseY >= AdminButtons[i].y1 && MouseY <= AdminButtons[i].y2) {
            new_tag = AdminButtons[i].active_tag;
            last_active_index = current_active_index;
            current_active_index = i; 
            break;
        }
    }

    // 状态变化时更新
    if (*tag != new_tag) {
        *tag = new_tag;
        if (new_tag != ACTIVE_ADMIN_NULL) {
            // 绘制提示（同时清除上一次高光提示）
            if (last_active_index != -1 && last_active_index < button_counts) 
                AdminButtons[last_active_index].clearfunc(
                AdminButtons[last_active_index].x1,
                AdminButtons[last_active_index].y1,
                AdminButtons[last_active_index].x2,
                AdminButtons[last_active_index].y2);
            if (current_active_index != -1 && current_active_index < button_counts)
                AdminButtons[current_active_index].drawfunc(
                AdminButtons[current_active_index].x1, 
                AdminButtons[current_active_index].y1,
                AdminButtons[current_active_index].x2, 
                AdminButtons[current_active_index].y2);
            last_active_index = current_active_index;
            MouseS = 1;
        }
        else {
            // 清除提示
            if (last_active_index != -1 && last_active_index < button_counts)
                AdminButtons[last_active_index].clearfunc(
                AdminButtons[last_active_index].x1,
                AdminButtons[last_active_index].y1,
                AdminButtons[last_active_index].x2, 
                AdminButtons[last_active_index].y2),
                last_active_index = -1;
            MouseS = 0;
        }
    }
}


/*****************************************************************
MODULE:该源文件全局可使用的函数模块
*****************************************************************/
//绘制选中的行的图形动画，同时返回选中行对应数据的id
int handle_list_select_line_admin(int *id_list)
{
    int i;
    for (i = 0; i < LIST_LIMIT; i++)
    {
        if (mouse_press(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 70 + i * LIST_INTERVAL,
                        ADMIN_INTERFACE_X1 + 400, ADMIN_INTERFACE_Y1 + 70 + (i + 1) * LIST_INTERVAL - 1) == 1 &&
            id_list[i] != -1)
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

// 查找文件中是否存在指定内容，并返回该数据块位置
long int ebike_info_search(FILE *fp,char *search_str,char *search_needed){
    int counts;
    long int pos;
    long int search_pos = 0;
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
            (strcmp(search_needed, "id") == 0 && TEMP.ID == atoi(search_str)) ||
            (strcmp(search_needed, "ebike_id") == 0 && strcmp(TEMP.ebike_ID, search_str) == 0) ||
            (strcmp(search_needed, "ebike_license") == 0 && strcmp(TEMP.ebike_license, search_str) == 0) ||
            (strcmp(search_needed, "location") == 0 && strcmp(TEMP.location, search_str) == 0) ||
            (strcmp(search_needed, "apply_time") == 0 && TEMP.apply_time == atoi(search_str)) ||
            (strcmp(search_needed, "conduct_time") == 0 && TEMP.conduct_time == atoi(search_str)) ||
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
void AdminConductSuccess(int button_x1, int button_y1, int button_x2, int button_y2)
{
    int tick = 0;
    clrmous(MouseX, MouseY); // 清除鼠标

    for (tick = 0; tick <= 80; tick++){
        if(tick%40 == 0){
            setfillstyle(SOLID_FILL, GREEN);
            bar(button_x1, button_y1, button_x2, button_y2);
            puthz(button_x1 + 4, button_y1 + 8, "操作成功", 16, 16, MY_WHITE); // 绘制按钮
        }else if(tick%40 == 20){
            setfillstyle(SOLID_FILL, MY_YELLOW);
            bar(button_x1, button_y1, button_x2, button_y2);
            puthz(button_x1 + 4, button_y1 + 8, "操作成功", 16, 16, MY_WHITE); // 绘制按钮
        }
        delay(25);
    }
    setfillstyle(SOLID_FILL, MY_YELLOW);
    bar(button_x1, button_y1, button_x2, button_y2); // 重绘按钮
    puthz(button_x1 + 4, button_y1 + 8, "同意申请", 16, 16, MY_WHITE); // 重新绘制按钮

    newmouse(&MouseX, &MouseY, &press); // 重新绘制
}
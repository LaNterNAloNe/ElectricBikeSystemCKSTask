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
}



/*****************************************************************
MODULE:管理员车辆注册
*****************************************************************/
void admin_bike_register(int *page, int *ID, LINKLIST *LIST)
{
    static int mode=0; // 搜索模式，列出已处理清单或待处理清单，主动清除该页面时重设为0（默认列出待处理清单）
    static int visited=0; // 是否进入乐该页面，主动清除该页面时重设为0
    char search_str[10]; // 搜索框输入信息储存
    int id_list[8];
    int tag=ACTIVE_ADMIN_NULL;
    ADMIN_BUTTONS AdminButtons[15]={
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
         ACTIVE_ADMIN_EXIT,&draw_exit,&clear_exit},
        {ADMIN_FEATURE1_X1,ADMIN_FEATURE1_X2,
         ADMIN_FEATURE1_Y1,ADMIN_FEATURE1_Y2,
         ACTIVE_ADMIN_FEATURE1,&draw_rectangle,&clear_rectangle},
        {ADMIN_FEATURE2_X1,ADMIN_FEATURE2_X2,
         ADMIN_FEATURE2_Y1,ADMIN_FEATURE2_Y2,
         ACTIVE_ADMIN_FEATURE2,&draw_rectangle,&clear_rectangle},
        {ADMIN_FEATURE3_X1,ADMIN_FEATURE3_X2,
         ADMIN_FEATURE3_Y1,ADMIN_FEATURE3_Y2,
         ACTIVE_ADMIN_FEATURE3,&draw_rectangle,&clear_rectangle},
        {ADMIN_FEATURE4_X1,ADMIN_FEATURE4_X2,
         ADMIN_FEATURE4_Y1,ADMIN_FEATURE4_Y2,
         ACTIVE_ADMIN_FEATURE4,&draw_rectangle,&clear_rectangle},
        {ADMIN_FEATURE5_X1,ADMIN_FEATURE5_X2,
         ADMIN_FEATURE5_Y1,ADMIN_FEATURE5_Y2,
         ACTIVE_ADMIN_FEATURE5,&draw_rectangle,&clear_rectangle},
        {ADMIN_FEATURE6_X1,ADMIN_FEATURE6_X2,
         ADMIN_FEATURE6_Y1,ADMIN_FEATURE6_Y2,
         ACTIVE_ADMIN_FEATURE6,&draw_rectangle,&clear_rectangle},
        {ADMIN_FEATURE_EXIT_X1,ADMIN_FEATURE_EXIT_X2,
         ADMIN_FEATURE_EXIT_Y1,ADMIN_FEATURE_EXIT_Y2,
         ACTIVE_ADMIN_FEATURE_EXIT,&draw_exit,&clear_exit},
        {ADMIN_FEATURE_SEARCH_X1,ADMIN_FEATURE_SEARCH_X2,
         ADMIN_FEATURE_SEARCH_Y1,ADMIN_FEATURE_SEARCH_Y2,
         ACTIVE_ADMIN_FEATURE_SEARCH,&draw_rectangle,&clear_rectangle},
    };
        
    FILE *fp_EBIKE_REGISTER_read = fopen("C:\\EBS\\DATA\\REGISTER.DAT","rb+");
    if(!fp_EBIKE_REGISTER_read) exit(1);
    fseek(fp_EBIKE_REGISTER_read,0,SEEK_SET);
    drawgraph_admin_menu();
    drawgraph_admin_bike_register();

    
    if(visited == 1) 
        list_search_register_request(id_list,fp_EBIKE_REGISTER_read,mode,0,0,"\0","\0");
    else
        list_search_register_request(id_list,fp_EBIKE_REGISTER_read,mode,1,0,"\0","\0");

    if(debug_mode == 1) display_memory_usage(400, 10); // 左上角显示 

    while(*page == ADMIN_BIKE_REGISTER){
        admin_flush_graph(&tag,STRUCT_LENGTH(AdminButtons),AdminButtons);
        handle_click_event_admin_main(page);
        handle_select_line_admin_register(page);
        newmouse(&MouseX,&MouseY,&press);

        if (mouse_press(ADMIN_FEATURE_EXIT_X1,ADMIN_FEATURE_EXIT_Y1,ADMIN_FEATURE_EXIT_X2,ADMIN_FEATURE_EXIT_Y2) == 1) {
            *page = MAIN_ADMIN;
        } // 当在功能界面点击叉，退出功能界面

        if (mouse_press(ADMIN_FEATURE_SEARCH_X1,ADMIN_FEATURE_SEARCH_Y1,ADMIN_FEATURE_SEARCH_X2,ADMIN_FEATURE_SEARCH_Y2)==1 &&
            *page == ADMIN_BIKE_REGISTER) {
            Input_Bar(search_str,ADMIN_FEATURE_SEARCH_X1+25,ADMIN_FEATURE_SEARCH_Y1+2,9,MY_LIGHTGRAY,0,1);
            list_search_register_request(id_list,fp_EBIKE_REGISTER_read,mode,1,0,search_str,"ID");
        } // 点击输入框后退回

        delay(25);
    }

    list_search_register_request(NULL,NULL,NULL,NULL,1,NULL,NULL);
    fclose(fp_EBIKE_REGISTER_read);
    Input_Bar(NULL, NULL, NULL, NULL, NULL,1,NULL);
    visited = 0;
    mode = 0;
    return;
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
}

void list_search_register_request(int id_list[8],FILE *fp,int mode,int page_change,int is_clear,char *search_str,char *search_needed){ 
    // page_change为1，向下列表，为-1，向上列表，为0，不翻页
    // mode为0，查找未处理，为1，查找已处理
    // is_clear为0，不做任何操作，为1，清理列表状态并不做任何操作，为2，清理列表状态并继续列表（重新开始列表）
    int i;
    int listed_item=0; // 列出的数量
    static int start=0; // 储存当前列表第一个所在的位置
    static int end=0; // 储存当前列表最后一个所在的位置
    int temp_start=0;
    int temp_end=0;
    int counts = 0;
    // int search_times = 0; // 记录搜索次数
    char buffer[50];
    EBIKE_REGISTER TEMP;
    counts = ftell(fp)/sizeof(EBIKE_REGISTER);

    for (i = 0; i < 8; i++){
        id_list[i] = -1;
    } // 开始列表前一定清理列表记录

    if (is_clear)
    {
        start = 0;
        end = 0;
        if (is_clear == 1)
            return;
    }

    if(counts && page_change == 1){ // 收到下翻指令
        /*条件判断*/
        if(end = counts-1) {
            return; // 如果end指向结尾的数据，则不做任何操作
        }
        fseek(fp,(end+1)*sizeof(TEMP),SEEK_SET); // 先判断接下来是否有可以列出的数据
        while(1){
            if(fread(&TEMP,sizeof(TEMP),1,fp)) { // 到文件末尾都没有发现可列表的，则不执行下翻列表操作
                return; 
            }
            if (list_admin_register_search_is_valid(TEMP,search_str,search_needed,mode)) break;// 下翻查找是一旦读到可以被列出的，则可以执行下翻列表操作
        }

        /*列表操作*/
        fseek(fp,(end+1)*sizeof(TEMP),SEEK_SET); // 经过while不返回到原函数则可移植性下翻列表操作
        start=++end;
        setfillstyle(SOLID_FILL,MY_LIGHTGRAY);
        bar(ADMIN_INTERFACE_X1+20,ADMIN_INTERFACE_Y1+70,ADMIN_INTERFACE_X1+500,ADMIN_INTERFACE_Y1+390); // 清理列表
        
        while(listed_item < 8){
            if(!fread(&TEMP,sizeof(TEMP),1,fp)) break; // 读取数据，直到达到文件末尾
            end++; // 先将end指向读取的数据的头部
            if ( ! list_admin_register_search_is_valid(TEMP, search_str, search_needed, mode))
                continue; // 如果下翻读取时读到的数据不符条件，则进行下一轮循环

            settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
            puthz(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 70 + listed_item * 20, TEMP.rln, 16, 16, MY_WHITE); // 输出姓名
            itoa(TEMP.ID,buffer,10);
            outtextxy(ADMIN_INTERFACE_X1 + 100, ADMIN_INTERFACE_Y1 + 70 + listed_item * LIST_INTERVAL, buffer);        // 输出ID
            outtextxy(ADMIN_INTERFACE_X1 + 200, ADMIN_INTERFACE_Y1 + 70 + listed_item * LIST_INTERVAL, TEMP.ebike_ID); // 输出电动车车牌号
            outtextxy(ADMIN_INTERFACE_X1 + 300, ADMIN_INTERFACE_Y1 + 70 + listed_item * LIST_INTERVAL, buffer); // 输出请求时间

            if(TEMP.conduct_time == -1){ // 输出处理状态
                puthz(ADMIN_INTERFACE_X1 + 400, ADMIN_INTERFACE_Y1 + 70 + listed_item * LIST_INTERVAL, "未处理", 16, 16, MY_RED);
            }else{
                puthz(ADMIN_INTERFACE_X1 + 400, ADMIN_INTERFACE_Y1 + 70 + listed_item * LIST_INTERVAL, "已处理", 16, 16, MY_GREEN);
            }
            id_list[listed_item] = TEMP.ID;
            listed_item++;
        }
    }else if(counts && page_change == -1){ // 收到上翻指令
        /*条件判断*/
        if(!start) {
            return; // 如果start指向开头的数据，则不做任何操作
        }
        temp_start=start;
        temp_end=start;

        while (1){ // 当能进入这个循环，说明列表上页有可列出数据且溢出
            if(!temp_start) break; // 到文件开头都没有发现可列表的，则不执行下翻列表操作
            fseek(fp,(temp_start-1)*sizeof(TEMP),SEEK_SET);
            fread(&TEMP,sizeof(TEMP),1,fp); // 读取上一个数据块
            temp_end = --temp_start;
            if (list_admin_register_search_is_valid(TEMP, search_str, search_needed, mode))
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
            if ( ! list_admin_register_search_is_valid(TEMP, search_str, search_needed, mode))
                continue; // 如果下翻读取时读到的数据不符条件，则进行下一轮循环

            settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
            puthz(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 310 - listed_item * LIST_INTERVAL, TEMP.rln, 16, 16, MY_WHITE); // 输出姓名
            itoa(TEMP.ID,buffer,10);
            outtextxy(ADMIN_INTERFACE_X1 + 100, ADMIN_INTERFACE_Y1 + 310 - listed_item * LIST_INTERVAL, buffer); // 输出ID
            outtextxy(ADMIN_INTERFACE_X1 + 200, ADMIN_INTERFACE_Y1 + 310 - listed_item * LIST_INTERVAL, TEMP.ebike_ID); // 输出电动车车牌号
            outtextxy(ADMIN_INTERFACE_X1 + 300, ADMIN_INTERFACE_Y1 + 310 - listed_item * LIST_INTERVAL, buffer); // 输出请求时间

            if(TEMP.conduct_time == -1){ // 输出处理状态
                puthz(ADMIN_INTERFACE_X1 + 400, ADMIN_INTERFACE_Y1 + 310 - listed_item * LIST_INTERVAL, "未处理", 16, 16, MY_RED);
            }else{
                puthz(ADMIN_INTERFACE_X1 + 400, ADMIN_INTERFACE_Y1 + 310 - listed_item * LIST_INTERVAL, "已处理", 16, 16, MY_GREEN);
            }
            id_list[listed_item] = TEMP.ID;
            listed_item++;
        }
    }else if(counts && page_change == 0){ // 不翻页，输出原内容
        fseek(fp,(start)*sizeof(TEMP),SEEK_SET);
        while(listed_item < 8){
            if(!fread(&TEMP,sizeof(TEMP),1,fp)) { // 读取数据，直到查找到八个可列出数据
                return;
            }
            if ( ! list_admin_register_search_is_valid(TEMP, search_str, search_needed, mode))
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
            }else{
                puthz(ADMIN_INTERFACE_X1 + 400, ADMIN_INTERFACE_Y1 + 70 + listed_item * LIST_INTERVAL, "已处理", 16, 16, MY_GREEN);
            }
            id_list[listed_item] = TEMP.ID;
            listed_item++;
        }

    }else{
        puthz(ADMIN_INTERFACE_X1+120,ADMIN_INTERFACE_Y1+70,"未找到对应数据或传入参数错误",16,16,MY_RED);
        return;
    }
}

int list_admin_register_search_is_valid(EBIKE_REGISTER TEMP,char *search_str,char *search_needed,int mode){  // 判断一个数据块是否应该列出
    if ((TEMP.conduct_time != -1 && mode == 0 ||
        TEMP.conduct_time > 0 && mode == 1) && 
        (!strcmp(search_str,"\0") ||
        !strcmp(TEMP.rln,search_str) && strcmp(search_needed,"realname") ||
        TEMP.ID == atoi(search_str) && strcmp(search_needed,"ID") ||
        !strcmp(TEMP.ebike_ID,search_str) && strcmp(search_needed,"ebikeID"))) return 1;
    else return 0;
}

int handle_select_line_admin_register(int *id_list){
    int i;
    for (i = 0; i < LIST_LIMIT; i++){
        if (mouse_press(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 70 + i * 20,
            ADMIN_INTERFACE_X1 + 400, ADMIN_INTERFACE_Y1 + 70 + (i+1) * LIST_INTERVAL - 1) &&
            id_list[i] != -1)
            bar(); // 清理所有高亮
            bar(); // 生成当前高亮
            return i;
    }
    return NULL;
}


/*****************************************************************
MODULE:刷新画面和处理鼠标点击
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

// void admin_flush_graph(int *tag, int button_counts, ADMIN_BUTTONS AdminButtons[]) {
//     int i;
//     int new_tag = ACTIVE_ADMIN_NULL;
//     static int last_active_index = -1;  // 初始化为无效索引 
//     static int current_active_index = -1;
//     int found_index = -1;

//     if (!tag || button_counts <= 0 || !AdminButtons)
//         return; // 参数合法性检查
    
//     // 检测当前激活的按钮
//     for (i = 0; i < button_counts; i++) {
//         if (MouseX >= AdminButtons[i].x1 && MouseX <= AdminButtons[i].x2 &&
//             MouseY >= AdminButtons[i].y1 && MouseY <= AdminButtons[i].y2) {
//             new_tag = AdminButtons[i].active_tag;
//             found_index = i;
//             break;
//         }
//     }
 
//     // 更新当前激活索引 
//     if (found_index != -1) {
//         last_active_index = current_active_index;
//         current_active_index = found_index;
//     } else {
//         // 未找到激活按钮时，重置索引 
//         last_active_index = current_active_index;
//         current_active_index = -1;
//     }
 
//     // 状态变化时更新 
//     if (*tag != new_tag) {
//         *tag = new_tag;
 
//         // 清理上一次高亮提示（仅在旧索引有效时）
//         if (last_active_index != -1 && last_active_index < button_counts) {
//             AdminButtons[last_active_index].clearfunc(
//                 AdminButtons[last_active_index].x1,
//                 AdminButtons[last_active_index].y1,
//                 AdminButtons[last_active_index].x2,
//                 AdminButtons[last_active_index].y2 
//             );
//         }
 
//         // 绘制新提示（仅在当前索引有效时）
//         if (current_active_index != -1 && current_active_index < button_counts) {
//             AdminButtons[current_active_index].drawfunc(
//                 AdminButtons[current_active_index].x1,
//                 AdminButtons[current_active_index].y1,
//                 AdminButtons[current_active_index].x2,
//                 AdminButtons[current_active_index].y2 
//             );
//             MouseS = 1;
//         } else {
//             MouseS = 0; // 无激活按钮时重置鼠标状态 
//         }
//     }
// }




/*****************************************************************
MODULE:生成链表数据
*****************************************************************/
//开始特性功能前先将储存信息传递到链表
void get_user_data(LINKLIST *LIST){
    char buffer[100]; // 定义缓冲区
    char *token; // 定义获取截断字符串的token
    LINKLIST_USER LIST_USER; // 定义结构体，准备加入链表
    
    FILE *fp_USER_DATA_read = fopen("C:\\EBS\\DATA\\USRDAT.TXT","r");
    if(fp_USER_DATA_read == NULL) getch(),exit(1);
    fseek(fp_USER_DATA_read,0,SEEK_SET); // 将文件指针置于开头，开始遍历文件

    while(fgets(buffer, sizeof(buffer), fp_USER_DATA_read)){
        if(!strcmp(buffer,"\0")) break;
        if(!strcmp(buffer,"\n")) continue;

        token = strtok(buffer, ",");
        LIST_USER.ID = token ? atoi(token) : 0;

        strncpy(LIST_USER.usrn, strtok(NULL, ","), sizeof(LIST_USER.usrn));
        strncpy(LIST_USER.rln, strtok(NULL, ","), sizeof(LIST_USER.rln));
        strncpy(LIST_USER.location, strtok(NULL, ","), sizeof(LIST_USER.location));
        strncpy(LIST_USER.ebike_ID, strtok(NULL, ","), sizeof(LIST_USER.ebike_ID));
        strncpy(LIST_USER.ebike_license, strtok(NULL, ","), sizeof(LIST_USER.ebike_license));

        token = strtok(NULL, ",");
        LIST_USER.anual_check  = token ? atoi(token) : 0;

        token = strtok(NULL, ",");
        LIST_USER.violations  = token ? atoi(token) : 0;

        token = strtok(NULL, ",");
        LIST_USER.account_state  = (token && *token) ? *token : ACTIVE;

        token = strtok(NULL, ",\n");
        LIST_USER.ebike_state  = (token && *token) ? *token : ACTIVE;

        linklist_add_data(LIST,LIST_USER);

        memset(buffer, 0, sizeof(buffer));
        memset(&LIST_USER, 0, sizeof(LINKLIST_USER)); // 确保结构体清零 
    }
}


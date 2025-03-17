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
        flush_admin_main_menu(&tag,STRUCT_LENGTH(AdminButtons),AdminButtons);
        handle_click_event_main(page);
        //应该在传入AdminButtons前计算其长度，传入函数后，使用sizeof计算其长度则会退化为指针长度，导致功能失效
        newmouse(&MouseX, &MouseY, &press);

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
            *page = LOGIN;
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


void flush_admin_main_menu(int *tag,int button_counts,ADMIN_BUTTONS AdminButtons[]){
    int i;
    int new_tag = ACTIVE_ADMIN_NULL;
    static int last_active_index = 0;
    static int current_active_index = -1;
    
    // 检查鼠标是否在任一按钮区域内
    for (i = 0; i < button_counts; i++) {
        if (MouseX >= AdminButtons[i].x1 && MouseX <= AdminButtons[i].x2 &&
            MouseY >= AdminButtons[i].y1 && MouseY <= AdminButtons[i].y2) {
            new_tag = AdminButtons[i].active_tag;
            // last_active_index = current_active_index;
            current_active_index = i; 
            // break;
        }
    }

    // 状态变化时更新
    if (*tag != new_tag) {
        *tag = new_tag;
        if (new_tag != ACTIVE_ADMIN_NULL) {
            // 绘制提示（需根据按钮索引计算坐标）
            // AdminButtons[last_active_index].clearfunc(AdminButtons[last_active_index].x1,
            //     AdminButtons[last_active_index].y1,AdminButtons[last_active_index].x2,AdminButtons[last_active_index].y2);
            AdminButtons[current_active_index].drawfunc(AdminButtons[current_active_index].x1,AdminButtons[current_active_index].y1,
                AdminButtons[current_active_index].x2,AdminButtons[current_active_index].y2);
            last_active_index = current_active_index;
            MouseS = 1;
        } 
        else {
            // 清除提示
            AdminButtons[last_active_index].clearfunc(AdminButtons[last_active_index].x1,
                AdminButtons[last_active_index].y1,AdminButtons[last_active_index].x2,AdminButtons[last_active_index].y2);
            MouseS = 0;
        }
    }
}

void handle_click_event_main(int *page){
    if (mouse_press(ADMIN_EXIT_X1,ADMIN_EXIT_Y1,ADMIN_EXIT_X2,ADMIN_EXIT_Y2) == 1) {
        if(!admin_exitting(page)){
            AdminswitchPage();
            return;
        } 
    }

    if (mouse_press(ADMIN_FEATURE_EXIT_X1,ADMIN_FEATURE_EXIT_Y1,ADMIN_FEATURE_EXIT_X2,ADMIN_FEATURE_EXIT_Y2) == 1) {
        *page = MAIN_ADMIN;
        return;
    } // 当在功能界面点击叉，退出功能界面

    if (mouse_press(ADMIN_BUTTON1_X1,ADMIN_BUTTON1_Y1,ADMIN_BUTTON1_X2,ADMIN_BUTTON1_Y2)==1 && 
        *page != ADMIN_BIKE_REGISTER) {
        *page = ADMIN_BIKE_REGISTER;
        return;
    }
}


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

/*****************************************************************
MODULE:管理员车辆注册
*****************************************************************/
void admin_bike_register(int *page,int *ID){
    int mode=0;
    int tag=ACTIVE_ADMIN_NULL;
    ADMIN_BUTTONS AdminButtons[14]={
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
    };
        

    LINKLIST *LIST = (LINKLIST *)malloc(sizeof(LINKLIST));
    FILE *fp_EBIKE_REGISTER_read = fopen("C:\\EBS\\DATA\\REGISTER.DAT","rb+");
    if(!fp_EBIKE_REGISTER_read) exit(1);
    fseek(fp_EBIKE_REGISTER_read,0,SEEK_SET);
    drawgraph_admin_menu();
    drawgraph_admin_bike_register();

    delay(50);
    get_user_data(LIST);
    list_search_register_request(LIST,fp_EBIKE_REGISTER_read);

    if(debug_mode == 1) display_memory_usage(400, 10); // 左上角显示 

    while(*page == ADMIN_BIKE_REGISTER){
        flush_admin_main_menu(&tag,STRUCT_LENGTH(AdminButtons),AdminButtons);
        handle_click_event_main(page);
        newmouse(&MouseX,&MouseY,&press);
        handle_click_event_main(page);
        
    }
    fclose(fp_EBIKE_REGISTER_read);
    
    linklist_clear(LIST);
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
    puthz(ADMIN_FEATURE3_X1+4,ADMIN_FEATURE3_Y1+8,"同意全部",16,16,MY_WHITE);
    puthz(ADMIN_FEATURE4_X1+4,ADMIN_FEATURE4_Y1+8,"驳回全部",16,16,MY_WHITE);

    clear_exit(ADMIN_FEATURE_EXIT_X1,ADMIN_FEATURE_EXIT_Y1,ADMIN_FEATURE_EXIT_X2,ADMIN_FEATURE_EXIT_Y2);
}

void list_search_register_request(LINKLIST *pList,FILE *fp){
    int listed_item=0;
    int request_counts = 0;
    int search_times = 0;
    char *buffer;
    EBIKE_REGISTER *TEMP = (EBIKE_REGISTER*)malloc(sizeof(EBIKE_REGISTER));
    if(!TEMP) exit(1);
    request_counts = ftell(fp)/sizeof(EBIKE_REGISTER);
    
    if(request_counts = ftell(fp)/sizeof(EBIKE_REGISTER)){
        while(listed_item <= request_counts && listed_item <= 7 && search_times <= request_counts){
            search_times++;
            fread(TEMP,sizeof(TEMP),1,fp); // 读取数据，直到查找到未被处理的注册请求
            if (TEMP->conduct_time == -1) continue;

            settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
            puthz(ADMIN_INTERFACE_X1+20,ADMIN_INTERFACE_Y1+60+listed_item*20,TEMP->rln,16,16,MY_WHITE); // 输出姓名
            itoa(TEMP->ID,buffer,10);
            outtextxy(ADMIN_INTERFACE_X1+100,ADMIN_INTERFACE_Y1+60+listed_item*20,buffer); // 输出ID
            outtextxy(ADMIN_INTERFACE_X1+200,ADMIN_INTERFACE_Y1+60+listed_item*20,TEMP->ebike_ID); // 输出电动车车牌号
            outtextxy(ADMIN_INTERFACE_X1+300,ADMIN_INTERFACE_Y1+60+listed_item*20,buffer); // 输出请求时间
            
            if(TEMP->conduct_time == -1){ // 输出处理状态
                puthz(ADMIN_INTERFACE_X1+20,ADMIN_INTERFACE_Y1+60+listed_item*20,"未处理",16,16,MY_RED);
            }else{
                puthz(ADMIN_INTERFACE_X1+20,ADMIN_INTERFACE_Y1+60+listed_item*20,"已处理",16,16,MY_GREEN);
            }
        }
    }else{
        puthz(ADMIN_INTERFACE_X1+200,ADMIN_INTERFACE_Y1+60,"未找到对应数据",16,16,MY_RED);
        return;
    }
    free(TEMP);
    return;

}
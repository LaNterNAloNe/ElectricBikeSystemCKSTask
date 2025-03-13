#include"_ADMIN_.H"


void main_admin(int *page){
    int tag=ACTIVE_ADMIN_NULL;
    ADMIN_BUTTONS AdminButtons[]={
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
         ACTIVE_ADMIN_BUTTON6,&draw_cues,&clear_cues}
    };

    clrmous(MouseX, MouseY);
    drawgraph_admin_main();
    mouseinit();

    while(1){
        flush_admin_main_graph(&tag,STRUCT_LENGTH(AdminButtons),AdminButtons);
        //应该在传入AdminButtons前计算其长度，传入函数后，使用sizeof计算其长度则会退化为指针长度，导致功能失效
        newmouse(&MouseX, &MouseY, &press);

        if (mouse_press(0, 0, 640, 480) == 1) {
            *page = EXIT;
            return;
        }
    }   

    delay(25);
}


void drawgraph_admin_main(void){
    int i;

    /*** 绘制菜单 ***/
    setfillstyle(SOLID_FILL, MY_YELLOW);
    bar(MENU_X1, MENU_Y1, MENU_X2, MENU_Y2);
    setcolor(BLUE);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    rectangle(MENU_X1+2, MENU_Y1+2, MENU_X2-2, MENU_Y2-2);
    setcolor(MY_BLACK);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    rectangle(MENU_X1+2, MENU_Y1+2, MENU_X2-2, MENU_Y2-2);

    /*** 绘制交互界面A（暂为空白） ***/
    setfillstyle(SOLID_FILL, BLUE);
    bar(INTERFACE_A_X1, INTERFACE_A_Y1, INTERFACE_A_X2, INTERFACE_A_Y2);
    setcolor(CYAN);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    rectangle(INTERFACE_A_X1+2, INTERFACE_A_Y1+2, INTERFACE_A_X2-2, INTERFACE_A_Y2-2);
    setcolor(MY_LIGHTGRAY);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    rectangle(INTERFACE_A_X1+2, INTERFACE_A_Y1+2, INTERFACE_A_X2-2, INTERFACE_A_Y2-2);

    /*** 绘制交互界面B（暂为空白） ***/
    setfillstyle(SOLID_FILL, BLUE);
    bar(INTERFACE_B_X1, INTERFACE_B_Y1, INTERFACE_B_X2, INTERFACE_B_Y2);
    setcolor(CYAN);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    rectangle(INTERFACE_B_X1+2, INTERFACE_B_Y1+2, INTERFACE_B_X2-2, INTERFACE_B_Y2-2);
    setcolor(MY_LIGHTGRAY);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    rectangle(INTERFACE_B_X1+2, INTERFACE_B_Y1+2, INTERFACE_B_X2-2, INTERFACE_B_Y2-2);

    setcolor(MY_WHITE);
    for(i=0;i<6;i++) {
        setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
        line(MENU_X1+10,MENU_Y1+45+i*40,MENU_X2-10,MENU_Y1+45+i*40);
        setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
        line(MENU_X1+6,MENU_Y1+45+i*40,MENU_X2-6,MENU_Y1+45+i*40);
        delay(10);
    }
    puthz(MENU_X1+25, MENU_Y1+25, "车辆注册",16,18,MY_WHITE);// 输出文本
    puthz(MENU_X1+25, MENU_Y1+65, "上牌管理",16,18,MY_WHITE);// 输出文本
    puthz(MENU_X1+25, MENU_Y1+105, "车辆报废",16,18,MY_WHITE);// 输出文本
    puthz(MENU_X1+25, MENU_Y1+145, "违规车辆",16,18,MY_WHITE);// 输出文本
    puthz(MENU_X1+25, MENU_Y1+185, "数据一览",16,18,MY_WHITE);// 输出文本

}

void draw_cues(int x, int y,int null1,int null2){
    setcolor(MY_GREEN);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    line(x-10,y,x,y);
    line(x-5,y-5,x,y);
    line(x-5,y+5,x,y);
}
void clear_cues(int x1, int y1, int x2, int y2){
    setfillstyle(SOLID_FILL, MY_YELLOW);
    bar(x1-13,y1+6,x2-79,y2);
}



void flush_admin_main_graph(int *tag,int button_counts,ADMIN_BUTTONS AdminButtons[]){
    int i;
    int new_tag = ACTIVE_ADMIN_NULL;
    static int temp;
    
    // 检查鼠标是否在任一按钮区域内
    for (i = 0; i < button_counts; i++) {
        if (MouseX >= AdminButtons[i].x1 && MouseX <= AdminButtons[i].x2 &&
            MouseY >= AdminButtons[i].y1 && MouseY <= AdminButtons[i].y2) {
            new_tag = AdminButtons[i].active_tag;
            temp = i;
            break;
        }
    }

    // 状态变化时更新
    if (*tag != new_tag) {
        *tag = new_tag;
        if (new_tag != ACTIVE_ADMIN_NULL) {
            // 绘制提示（需根据按钮索引计算坐标）
            AdminButtons[temp].drawfunc(AdminButtons[temp].x1,AdminButtons[temp].y1+23,NULL,NULL);
            MouseS = 1;
        } 
        else {
            // 清除提示
            AdminButtons[temp].clearfunc(AdminButtons[temp].x1,AdminButtons[temp].y1,AdminButtons[temp].x2,AdminButtons[temp].y2);
            MouseS = 0;
        }
    }
}
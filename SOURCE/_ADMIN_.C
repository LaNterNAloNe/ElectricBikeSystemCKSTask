#include"_ADMIN_.H"


void main_admin(int *page){
    int tag=ACTIVE_ADMIN_NULL;

    clrmous(MouseX, MouseY);
    drawgraph_admin_main();
    mouseinit();

    while(1){
        flush_admin_main_graph(&tag);
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

void draw_cues(int x, int y){
    setcolor(MY_GREEN);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    line(x-10,y,x,y);
    line(x-5,y-5,x,y);
    line(x-5,y+5,x,y);
}

void flush_admin_main_graph(int *tag){
    if((MouseX >= ADMIN_BUTTON1_X1 && MouseX <= ADMIN_BUTTON1_X2 && MouseY >= ADMIN_BUTTON1_Y1 && MouseY <= ADMIN_BUTTON1_Y2) || 
    (MouseX >= ADMIN_BUTTON2_X1 && MouseX <= ADMIN_BUTTON2_X2 && MouseY >= ADMIN_BUTTON2_Y1 && MouseY <= ADMIN_BUTTON2_Y2) || 
    (MouseX >= ADMIN_BUTTON3_X1 && MouseX <= ADMIN_BUTTON3_X2 && MouseY >= ADMIN_BUTTON3_Y1 && MouseY <= ADMIN_BUTTON3_Y2) || 
    (MouseX >= ADMIN_BUTTON4_X1 && MouseX <= ADMIN_BUTTON4_X2 && MouseY >= ADMIN_BUTTON4_Y1 && MouseY <= ADMIN_BUTTON4_Y2) || 
    (MouseX >= ADMIN_BUTTON5_X1 && MouseX <= ADMIN_BUTTON5_X2 && MouseY >= ADMIN_BUTTON5_Y1 && MouseY <= ADMIN_BUTTON5_Y2) || 
    (MouseX >= ADMIN_BUTTON6_X1 && MouseX <= ADMIN_BUTTON6_X2 && MouseY >= ADMIN_BUTTON6_Y1 && MouseY <= ADMIN_BUTTON6_Y2))
        MouseS = 1;
    else
        MouseS = 0;


    if(MouseX >= ADMIN_BUTTON1_X1 && MouseX <= ADMIN_BUTTON1_X2 && MouseY >= ADMIN_BUTTON1_Y1 && MouseY <= ADMIN_BUTTON1_Y2 && *tag !=ACTIVE_ADMIN_BUTTON1){
        *tag = ACTIVE_ADMIN_BUTTON1;
        draw_cues(ADMIN_BUTTON1_X1,ADMIN_BUTTON1_Y1+23);
    }else if(MouseX >= ADMIN_BUTTON2_X1 && MouseX <= ADMIN_BUTTON2_X2 && MouseY >= ADMIN_BUTTON2_Y1 && MouseY <= ADMIN_BUTTON2_Y2 && *tag !=ACTIVE_ADMIN_BUTTON2){
        *tag = ACTIVE_ADMIN_BUTTON2;
        draw_cues(ADMIN_BUTTON2_X1,ADMIN_BUTTON2_Y1+23);
    }else if(MouseX >= ADMIN_BUTTON3_X1 && MouseX <= ADMIN_BUTTON3_X2 && MouseY >= ADMIN_BUTTON3_Y1 && MouseY <= ADMIN_BUTTON3_Y2 && *tag !=ACTIVE_ADMIN_BUTTON3){
        *tag = ACTIVE_ADMIN_BUTTON3;
        draw_cues(ADMIN_BUTTON3_X1,ADMIN_BUTTON3_Y1+23);
    }else if(MouseX >= ADMIN_BUTTON4_X1 && MouseX <= ADMIN_BUTTON4_X2 && MouseY >= ADMIN_BUTTON4_Y1 && MouseY <= ADMIN_BUTTON4_Y2 && *tag !=ACTIVE_ADMIN_BUTTON4){
        *tag = ACTIVE_ADMIN_BUTTON4;
        draw_cues(ADMIN_BUTTON4_X1,ADMIN_BUTTON4_Y1+23);
    }else if(MouseX >= ADMIN_BUTTON5_X1 && MouseX <= ADMIN_BUTTON5_X2 && MouseY >= ADMIN_BUTTON5_Y1 && MouseY <= ADMIN_BUTTON5_Y2 && *tag !=ACTIVE_ADMIN_BUTTON5){
        *tag = ACTIVE_ADMIN_BUTTON5;
        draw_cues(ADMIN_BUTTON5_X1,ADMIN_BUTTON5_Y1+23);
    }else if(MouseX >= ADMIN_BUTTON6_X1 && MouseX <= ADMIN_BUTTON6_X2 && MouseY >= ADMIN_BUTTON6_Y1 && MouseY <= ADMIN_BUTTON6_Y2 && *tag !=ACTIVE_ADMIN_BUTTON6){
        *tag = ACTIVE_ADMIN_BUTTON6;
        draw_cues(ADMIN_BUTTON6_X1,ADMIN_BUTTON6_Y1+23);
    }
    
    if((MouseX < ADMIN_BUTTON1_X1 || MouseX > ADMIN_BUTTON1_X2 || MouseY < ADMIN_BUTTON1_Y1 || MouseY > ADMIN_BUTTON1_Y2) && *tag == ACTIVE_ADMIN_BUTTON1){
        *tag = ACTIVE_ADMIN_NULL;
        setfillstyle(SOLID_FILL,MY_YELLOW);
        bar(ADMIN_BUTTON1_X1-13,ADMIN_BUTTON1_Y1+6,ADMIN_BUTTON1_X1+1,ADMIN_BUTTON1_Y2);
    }
    if((MouseX < ADMIN_BUTTON2_X1 || MouseX > ADMIN_BUTTON2_X2 || MouseY < ADMIN_BUTTON2_Y1 || MouseY > ADMIN_BUTTON2_Y2) && *tag == ACTIVE_ADMIN_BUTTON2){
        *tag = ACTIVE_ADMIN_NULL;
        setfillstyle(SOLID_FILL,MY_YELLOW);
        bar(ADMIN_BUTTON2_X1-13,ADMIN_BUTTON2_Y1+6,ADMIN_BUTTON2_X1+1,ADMIN_BUTTON2_Y2);
    }
    if((MouseX < ADMIN_BUTTON3_X1 || MouseX > ADMIN_BUTTON3_X2 || MouseY < ADMIN_BUTTON3_Y1 || MouseY > ADMIN_BUTTON3_Y2) && *tag == ACTIVE_ADMIN_BUTTON3){
        *tag = ACTIVE_ADMIN_NULL;
        setfillstyle(SOLID_FILL,MY_YELLOW);
        bar(ADMIN_BUTTON3_X1-13,ADMIN_BUTTON3_Y1+6,ADMIN_BUTTON3_X1+1,ADMIN_BUTTON3_Y2);
    }
    if((MouseX < ADMIN_BUTTON4_X1 || MouseX > ADMIN_BUTTON4_X2 || MouseY < ADMIN_BUTTON4_Y1 || MouseY > ADMIN_BUTTON4_Y2) && *tag == ACTIVE_ADMIN_BUTTON4){
        *tag = ACTIVE_ADMIN_NULL;
        setfillstyle(SOLID_FILL,MY_YELLOW);
        bar(ADMIN_BUTTON4_X1-13,ADMIN_BUTTON4_Y1+6,ADMIN_BUTTON4_X1+1,ADMIN_BUTTON4_Y2);
    }
    if((MouseX < ADMIN_BUTTON5_X1 || MouseX > ADMIN_BUTTON5_X2 || MouseY < ADMIN_BUTTON5_Y1 || MouseY > ADMIN_BUTTON5_Y2) && *tag == ACTIVE_ADMIN_BUTTON5){
        *tag = ACTIVE_ADMIN_NULL;
        setfillstyle(SOLID_FILL,MY_YELLOW);
        bar(ADMIN_BUTTON5_X1-13,ADMIN_BUTTON5_Y1+6,ADMIN_BUTTON5_X1+1,ADMIN_BUTTON5_Y2);
    }
    if((MouseX < ADMIN_BUTTON6_X1 || MouseX > ADMIN_BUTTON6_X2 || MouseY < ADMIN_BUTTON6_Y1 || MouseY > ADMIN_BUTTON6_Y2) && *tag == ACTIVE_ADMIN_BUTTON6){
        *tag = ACTIVE_ADMIN_NULL;
        setfillstyle(SOLID_FILL,MY_YELLOW);
        bar(ADMIN_BUTTON6_X1-13,ADMIN_BUTTON6_Y1+6,ADMIN_BUTTON6_X1+1,ADMIN_BUTTON6_Y2);
    }


    

}
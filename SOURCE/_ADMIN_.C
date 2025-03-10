#include"_ADMIN_.H"


void main_admin(int *page){
    clrmous(MouseX, MouseY);
    drawgraph_admin_main();
    mouseinit();

    while(1){
        newmouse(&MouseX, &MouseY, &press);
        if (mouse_press(0, 0, 640, 480) == 1) {
            *page = EXIT;
            return;
        }
    }   

}


void drawgraph_admin_main(void){
    /*** 绘制菜单 ***/
    setfillstyle(SOLID_FILL, CYAN);
    bar(MENU_X1, MENU_Y1, MENU_X2, MENU_Y2);
    setcolor(BLUE);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    line(MENU_X1+2, MENU_Y1+2, MENU_X2-2, MENU_Y1+2);
    line(MENU_X1+2, MENU_Y1+2, MENU_X1+2, MENU_Y2-2);
    line(MENU_X1+2, MENU_Y2-2, MENU_X2-2, MENU_Y2-2);
    line(MENU_X2-2, MENU_Y1+2, MENU_X2-2, MENU_Y2-2);
    setcolor(MY_BLACK);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    line(MENU_X1+2, MENU_Y1+2, MENU_X2-2, MENU_Y1+2);
    line(MENU_X1+2, MENU_Y1+2, MENU_X1+2, MENU_Y2-2);
    line(MENU_X1+2, MENU_Y2-2, MENU_X2-2, MENU_Y2-2);
    line(MENU_X2-2, MENU_Y1+2, MENU_X2-2, MENU_Y2-2);

    /*** 绘制交互界面A（暂为空白） ***/
    setfillstyle(SOLID_FILL, BLUE);
    bar(INTERFACE_A_X1, INTERFACE_A_Y1, INTERFACE_A_X2, INTERFACE_A_Y2);
    setcolor(CYAN);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    line(INTERFACE_A_X1+2, INTERFACE_A_Y1+2, INTERFACE_A_X2-2, INTERFACE_A_Y1+2);
    line(INTERFACE_A_X1+2, INTERFACE_A_Y1+2, INTERFACE_A_X1+2, INTERFACE_A_Y2-2);
    line(INTERFACE_A_X1+2, INTERFACE_A_Y2-2, INTERFACE_A_X2-2, INTERFACE_A_Y2-2);
    line(INTERFACE_A_X2-2, INTERFACE_A_Y1+2, INTERFACE_A_X2-2, INTERFACE_A_Y2-2);
    setcolor(MY_LIGHTGRAY);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    line(INTERFACE_A_X1+2, INTERFACE_A_Y1+2, INTERFACE_A_X2-2, INTERFACE_A_Y1+2);
    line(INTERFACE_A_X1+2, INTERFACE_A_Y1+2, INTERFACE_A_X1+2, INTERFACE_A_Y2-2);
    line(INTERFACE_A_X1+2, INTERFACE_A_Y2-2, INTERFACE_A_X2-2, INTERFACE_A_Y2-2);
    line(INTERFACE_A_X2-2, INTERFACE_A_Y1+2, INTERFACE_A_X2-2, INTERFACE_A_Y2-2);

    /*** 绘制交互界面B（暂为空白） ***/
    setfillstyle(SOLID_FILL, BLUE);
    bar(INTERFACE_B_X1, INTERFACE_B_Y1, INTERFACE_B_X2, INTERFACE_B_Y2);
    setcolor(CYAN);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    line(INTERFACE_B_X1+2, INTERFACE_B_Y1+2, INTERFACE_B_X2-2, INTERFACE_B_Y1+2);
    line(INTERFACE_B_X1+2, INTERFACE_B_Y1+2, INTERFACE_B_X1+2, INTERFACE_B_Y2-2);
    line(INTERFACE_B_X1+2, INTERFACE_B_Y2-2, INTERFACE_B_X2-2, INTERFACE_B_Y2-2);
    line(INTERFACE_B_X2-2, INTERFACE_B_Y1+2, INTERFACE_B_X2-2, INTERFACE_B_Y2-2);
    setcolor(MY_LIGHTGRAY);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    line(INTERFACE_B_X1+2, INTERFACE_B_Y1+2, INTERFACE_B_X2-2, INTERFACE_B_Y1+2);
    line(INTERFACE_B_X1+2, INTERFACE_B_Y1+2, INTERFACE_B_X1+2, INTERFACE_B_Y2-2);
    line(INTERFACE_B_X1+2, INTERFACE_B_Y2-2, INTERFACE_B_X2-2, INTERFACE_B_Y2-2);
    line(INTERFACE_B_X2-2, INTERFACE_B_Y1+2, INTERFACE_B_X2-2, INTERFACE_B_Y2-2);
}
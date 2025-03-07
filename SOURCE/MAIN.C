#include"GLOBAL.H"
#include "MOUSE.H"  // ?? 添加鼠标头文件引用 
 
int main() 
{
    int current_focus = 0; // 0:无焦点 1:账号框 2:密码框 
    int gd = DETECT, gm;
    InputBox account_box = {100, 100, 300, 130, "", 0, 0};
    InputBox password_box = {100, 160, 300, 190, "", 0, 0};
    MOUSE mouse = {0};  // ?? 声明鼠标结构体 
	
	
    initgraph(&gd, &gm, "C:\\BORLANDC\\BGI");
    mouse_init();      // ?? 初始化鼠标系统 
    // 绘制初始界面 
    setbkcolor(GREEN);
    cleardevice();
    settextstyle(SMALL_FONT, HORIZ_DIR, 5);
    // 绘制标签 
    outtextxy(account_box.x1 - 60, account_box.y1 + 5, "Account:");
    outtextxy(password_box.x1 - 60, password_box.y1 + 5, "Password:");
    
    // 主循环 
    while(!kbhit()) {
        // ?? 替换newmouse为以下代码段 
        mouse_show(&mouse);  // 更新鼠标显示 
        MouseGet(&mouse);    // 获取鼠标状态 
 
        // 检测鼠标点击 
        if (mouse.key  & 1) {  // ?? 使用结构体中的按键状态 
            // 判断点击区域 
            if (mouse.x > account_box.x1 && mouse.x < account_box.x2 &&
                mouse.y > account_box.y1 && mouse.y < account_box.y2) {
                current_focus = 1;
                account_box.is_active  = 1;
                password_box.is_active  = 0;
            } else if (mouse.x > password_box.x1 && mouse.x < password_box.x2 &&
                       mouse.y > password_box.y1 && mouse.y < password_box.y2) {
                current_focus = 2;
                password_box.is_active  = 1;
                account_box.is_active  = 0;
            } else {
                current_focus = 0;
                account_box.is_active  = 0;
                password_box.is_active  = 0;
            }
        }
 
        // 处理键盘输入（保持原逻辑不变）
        if (current_focus) {
            InputBox *box = (current_focus == 1) ? &account_box : &password_box;
            if (kbhit()) {
                int key = getch();
                if (key == 0) key = getch() + 256; // 扩展键 
                handle_input(box, key);
            }
        }
 
        // 重绘界面 
        draw_input_box(&account_box);
        draw_input_box(&password_box);
        delay(50);
    }
	
    closegraph();
	getch();
    return 0;
}
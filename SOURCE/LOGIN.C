#include"LOGIN.H"

// 登录界面
void login(int *page){
    /*初始化登录图形界面*/
    InputBox username_box = {240, 200, 400, 240, "Username" ,"", 0, 0, 0};//x1,y1,x2,y2,text,placeholder,cursor_pos,is_active,last_blink
    InputBox password_box = {240, 260, 400, 300, "Password", "", 0, 0, 0};
    InputBox* active_box = NULL;
    int username_hit = 0;
    int password_hit = 0;
    int exit_flag = 0;

    draw_login_graph(); // 绘制背景和静态元素
    draw_input_box(&username_box);
    draw_input_box(&password_box);

    // 绘制固定提示文字
    setcolor(WHITE);
    outtextxy(170, 205, "Username:");
    outtextxy(170, 265, "Password:");
    /*完成初始化登录图形界面*/

    while(!exit_flag) {
        // 每次刷新更新鼠标状态
        newmouse(&MouseX,&MouseY,&press);

        // 处理鼠标移动事件
        if(MouseX>=username_box.x1&&MouseX<=username_box.x2&&MouseY>=username_box.y1&&MouseY<=username_box.y2){
            MouseS=1;
        }
        else if(MouseX>=password_box.x1&&MouseX<=password_box.x2&&MouseY>=password_box.y1&&MouseY<=password_box.y2){
            MouseS=1;
        }
        else{
            MouseS=0;
        }

        // 处理鼠标点击事件
        if(mouse_press(0,0,640,480)){
            if(mouse_press(username_box.x1,username_box.y1,username_box.x2,username_box.y2)){
                username_hit = 1;
                password_hit = 0;
            }

            if(mouse_press(password_box.x1,password_box.y1,password_box.x2,password_box.y2)){
                username_hit = 0;
                password_hit = 1;
            }
    
            // 状态转移逻辑
            if(username_hit || password_hit){
                if(active_box){
                    active_box->is_active = 0;  // 退出前保存状态
                    if(strlen(active_box->text)==0){
                        // 空内容恢复默认提示
                        strcpy(active_box->text, (active_box==&username_box)?"Username":"Password");
                    }
                }
                
                active_box = username_hit ? &username_box : &password_box;
                active_box->is_active = 1;
                
                // 新激活状态初始化
                if(strcmp(active_box->text, "Username")==0 || strcmp(active_box->text, "Password")==0){
                    active_box->text[0] = '\0';
                    active_box->cursor_pos = 0;
                }
            }
        }
    
        // 处理键盘事件
        if(kbhit()){
            int key = getch();
            if(active_box){
                handle_input(active_box, key);
                // 特殊功能键处理
                if(key == '\r'){ // 回车提交
                    //validate_login(&username_box, &password_box);
                    exit_flag = 1;
                }
            }
        }
        draw_input_box(&username_box);
        draw_input_box(&password_box);
        delay(25); // 控制刷新率
    }

}


// 绘制输入框
void draw_input_box(InputBox *box) {
    // 动态文本选择 
    const char* display_text = box->text;
    int show_placeholder = (strlen(box->text) == 0 && !box->is_active);
    // 防溢出文本绘制 
    int max_width = box->x2 - box->x1 - 10;
    char clipped_text[MAX_INPUT_LEN];

    int text_width = textwidth(clipped_text);

    // 动态边框颜色 
    setcolor(box->is_active ? 0x0000FF : 0xA9A9A9);
    rectangle(box->x1, box->y1, box->x2, box->y2);
    
    // 区域刷新保障 
    setfillstyle(SOLID_FILL, WHITE);
    bar(box->x1+1, box->y1+1, box->x2-1, box->y2-1);
    
    if(show_placeholder) {
        setcolor(0xC0C0C0);    // 灰色提示文字 
        display_text = box->placeholder;
    } else {
        setcolor(BLACK);       // 黑色输入文字 
    }

    strncpy(clipped_text, display_text, textnwidth(display_text, max_width));
    outtextxy(box->x1 + 5, box->y1 + 5, clipped_text);
 
    // 智能光标系统 
    if(box->is_active) {
        // 500ms闪烁周期 
        if((GetTickCount() - box->last_blink) % 1000 < 500) {
            line(box->x1 + 5 + text_width, box->y1 + 5,
                 box->x1 + 5 + text_width, box->y1 + 15);
        }
        // 更新计时器 
        if(GetTickCount() - box->last_blink > 1000) {
            box->last_blink = GetTickCount();
        }
    }
}

// 处理键盘输入
void handle_input(InputBox *box, int key) {
    int len = strlen(box->text);
    
    switch(key) {
        case KEYBOARD_LEFT:
            if (box->cursor_pos > 0) box->cursor_pos--;
            break;
        case KEYBOARD_RIGHT:
            if (box->cursor_pos < len) box->cursor_pos++;
            break;
        case 8: // Backspace
            if (box->cursor_pos > 0) {
                memmove(&box->text[box->cursor_pos-1], 
                        &box->text[box->cursor_pos],
                        len - box->cursor_pos + 1);
                box->cursor_pos--;
            }
            break;
        default:
            if (key >= 32 && key <= 126 && len < MAX_INPUT_LEN-1) {
                // 首个字符覆盖逻辑
                if (box->cursor_pos == 0 && len == 0) {
                    box->text[0] = key;
                    box->text[1] = '\0';
                } else {
                    memmove(&box->text[box->cursor_pos+1],
                            &box->text[box->cursor_pos],
                            len - box->cursor_pos + 1);
                    box->text[box->cursor_pos] = key;
                }
                box->cursor_pos++;
            }
    }
}

// 输入框闪烁
unsigned long GetTickCount() {
    unsigned char low, high;
    unsigned long count;
    
    // 锁定计时器通道0 
    outportb(0x43, 0x00);
    delay(1);
    
    // 读取16位计数器值 
    low = inportb(0x40);
    high = inportb(0x40);
    count = (high << 8) | low;
    
    // 计算精确毫秒（基于递减计数器特性）
    return (TIMER_FREQ - count) * 1000L / TIMER_FREQ;
}

/*
int validate_input(InputBox *box) {
    if(strlen(box->text) == 0) 
        return EMPTY_WARNING;
    if(box == &password_box && strlen(box->text) < 8)
        return PASS_TOO_SHORT;
    return VALID_SUCCESS;
}
*/


void draw_login_graph(void)
{
    //开始你的创作吧~
    return;
}
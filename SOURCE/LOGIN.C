#include"LOGIN.H"


// 登录界面
void login(int *page,int *num){
    char a[10];
	char b[10];
	int tag=0;
	clrmous(MouseX,MouseY);
	save_bk_mou(MouseX,MouseY);
    drawgraph_login();
    while(1){
        newmouse(&MouseX,&MouseY,&MouseS);

        //鼠标移动事件
        // if(MouseX < USERNAME_X1 && MouseX > USERNAME_X2 && MouseY < USERNAME_Y1 && MouseY > USERNAME_Y2 || 
        //     MouseX < PASSWORD_X1 && MouseX > PASSWORD_X2 && MouseY < PASSWORD_Y1 && MouseY > PASSWORD_Y2 || 
        //     MouseX < LOGIN_X1 && MouseX > LOGIN_X2 && MouseY < LOGIN_Y1 && MouseY > LOGIN_Y2 || 
        //     MouseX < REGISTER_X1 && MouseX > REGISTER_X2 && MouseY < REGISTER_Y1 && MouseY > REGISTER_Y2 || 
        //     MouseX < ADMIN_X1 && MouseX > ADMIN_X2 && MouseY < ADMIN_Y1 && MouseY > ADMIN_Y2)
        // {
        //     MouseS = 1;
        // }
        // else MouseS = 0;

        //鼠标点击事件
        if(mouse_press(USERNAME_X1,USERNAME_Y1,USERNAME_X2,USERNAME_Y2) == 1){
            tag = 1;
            Input_Vis(a,220,170,20,WHITE);
        }
        if(mouse_press(PASSWORD_X1,PASSWORD_Y1,PASSWORD_X2,PASSWORD_Y2) == 1){
            tag = 2;
            Input_Invis(b,220,260,16,WHITE);
        }
        if(mouse_press(LOGIN_X1,LOGIN_Y1,LOGIN_X2,LOGIN_Y2) == 1){
            if(tag == 1 && tag == 2){
                if(strcmp(a,"admin") == 0 && strcmp(b,"admin") == 0){
                    *page = 0;
                }
            }
        }
        delay(25); // 控制刷新率
    }
    
}

// 绘制登录界面
void drawgraph_login(void){
    setrgbpalette(0, 12,158,245);//浅蓝背景-1
	setrgbpalette(1, 235,235,235);//浅灰框-1
	setrgbpalette(2, 0, 0, 0);//黑色
	setrgbpalette(3, 240, 230,75);//黄色
	setrgbpalette(4, 255, 0, 0);//红色
	setrgbpalette(5, 255, 255, 255);//白色
	setbkcolor(0);
	setcolor(WHITE);
	setlinestyle(0,0,3);
	setfillstyle(1,WHITE);//大框
	bar(120,120,520,390);
	setcolor(2);
	setlinestyle(0, 0, 3);
	setfillstyle(1,2);
	pieslice(160,175,0,360,10);//人头
	pieslice(160,205,0,180,20);
	pieslice(160,250,0,360,12);//钥匙
	bar(156,254,164,300);
	bar(164, 276, 170, 282);
	bar(163, 288,170, 294);
	setcolor(1);
	setlinestyle(0, 0, 3);
	setfillstyle(1, 1);
	bar(220, 170, 480, 205);//用户名框
	bar(220, 260, 480, 295);//密码框
	setcolor(4);
	setlinestyle(0, 0, 3);
	setfillstyle(1, 4);
	bar(230, 320, 330, 370);//分别为登录，注册
	bar(360, 320, 460, 370);
	setcolor(3);
	setlinestyle(0, 0, 3);
	setfillstyle(1, 3);
	bar(160, 330, 200, 360);//管理员模式
	setcolor(2); // 文本颜色为黑色
	settextstyle(1, HORIZ_DIR, 3);// 设置文本大小
	outtextxy(220,140, "Name");// 输出文本
	outtextxy(220, 230, "Password");
	setcolor(WHITE);
	settextstyle(1, HORIZ_DIR, 2);
	outtextxy(255, 330, "Log in");
	outtextxy(380, 330, "Register");
}
// // 绘制输入框
// void draw_input_box(InputBox *box) {
//     int max_width = box->x2 - box->x1 - 10;
//     int visible_chars = textnwidth(box->text, max_width);
//     // ▋动态光标位置计算（基于可见文本）
//     int text_width = textwidth(clipped_text);
//     // ▋新增缓冲区初始化 
//     static char clipped_text[MAX_INPUT_LEN] = {0};
//     memset(clipped_text, 0, sizeof(clipped_text));
 
//     // ▋修正文本裁剪逻辑顺序 
//     strncpy(clipped_text, box->text, visible_chars);
//     clipped_text[visible_chars] = '\0'; // 强制终止符 
    
//     // ▋条件化光标绘制（防溢出）
//     if(box->is_active && text_width < max_width) {
//         unsigned long current_time = GetTickCount();
//         // ▋优化闪烁周期算法 
//         if((current_time - box->last_blink) % 1000 < 500) {
//             line(box->x1 + 5 + text_width, box->y1 + 5,
//                  box->x1 + 5 + text_width, box->y1 + 15);
//         }
//         // ▋时间戳更新策略调整 
//         if(current_time - box->last_blink >= 1000) {
//             box->last_blink = current_time;
//         }
//     }
//     // 其余绘制逻辑保持原样...
// }

// // 处理键盘输入
// void handle_input(InputBox *box, int key) {
//     int len = strlen(box->text);
    
//     switch(key) {
//         case KEYBOARD_LEFT:
//             if (box->cursor_pos > 0) box->cursor_pos--;
//             break;
//         case KEYBOARD_RIGHT:
//             if (box->cursor_pos < len) box->cursor_pos++;
//             break;
//         case BACK:  // ▋修正退格逻辑 
//             if (box->cursor_pos > 0 && len > 0) {
//                 memmove(&box->text[box->cursor_pos-1], 
//                         &box->text[box->cursor_pos], 
//                         len - box->cursor_pos + 1); // ▋包含终止符 
//                 box->cursor_pos--;
//                 box->text[len-1] = '\0'; // ▋双重保障 
//             }
//             break;
//         default:
//             if (key >= 32 && key <= 126 && len < MAX_INPUT_LEN-1) {
//                 // 首个字符覆盖逻辑
//                 if (box->cursor_pos == 0 && len == 0) {
//                     box->text[0] = key;
//                     box->text[1] = '\0';
//                 } else {
//                     memmove(&box->text[box->cursor_pos+1],
//                             &box->text[box->cursor_pos],
//                             len - box->cursor_pos + 1);
//                     box->text[box->cursor_pos] = key;
//                 }
//                 box->cursor_pos++;
//             }
//     }
// }

// /* 计算字符串在不超过指定宽度时能显示的最大字符数
//  * @param str 输入字符串
//  * @param max_width 最大像素宽度
//  * @return 可完整显示的字符数 */
// int textnwidth(const char *str, int max_width) {
//     int total = 0;
//     int char_count = 0;
//     int cw;
    
//     // 逐字符遍历直到字符串结束
//     while (*str && total <= max_width) {
//         // 获取当前字符宽度（假设单字节字符）
//         char tmp[2];
//         tmp[0] = *str;
//         tmp[1] = '\0';
//         cw = textwidth(tmp);// 构造临时字符串
        
//         // 超出则终止（保留一个字符余量）
//         if (total + cw > max_width) break;
        
//         total += cw;
//         char_count++;
//         str++;
//     }
//     return char_count;
// }

// // 输入框闪烁
// unsigned long GetTickCount() {
//     struct time t;
//     gettime(&t);
//     return (t.ti_hund  * 10) + (t.ti_sec  * 1000) + (t.ti_min  * 60000);
// }

 
// /* 凭证验证函数 */
// void validate_login(InputBox *user_box, InputBox *pass_box, int *page) {
//     int i;//临时变量
//     char username[MAX_USERNAME_LEN+1] = {0};
//     char password[MAX_PASSWORD_LEN+1] = {0};
//     int validation_result = 0;
    
//     /* 输入规范化处理 */
//     // 去除首尾空格（需实现trim函数）
//     strncpy(username, trim_whitespace(user_box->text), MAX_USERNAME_LEN);
//     strncpy(password, trim_whitespace(pass_box->text), MAX_PASSWORD_LEN);
 
//     /* 空字段检测 */
//     if(strlen(username) == 0 || strlen(password) == 0) {
//         show_error_message(ERR_EMPTY, "Fields cannot be empty");
//         // 激活空字段输入框 
//         if(strlen(username) == 0) {
//             user_box->is_active = 1;
//             pass_box->is_active = 0;
//         } else {
//             pass_box->is_active = 1;
//         }
//         return;
//     }
 
//     /* 凭证验证逻辑 */
//     if(strcmp(username, ADMIN_USER) == 0) {
//         if(strcmp(password, ADMIN_PASS) == 0) {
//             validation_result = 1;  // 验证成功 
//             *page = 0;  // 假设已定义页面宏 
//         } else {
//             show_error_message(ERR_INVALID, "Wrong password");
//             pass_box->text[0] = '\0';  // 清空密码框 
//             pass_box->is_active = 1;  // 重新激活 
//         }
//     } else {
//         show_error_message(ERR_INVALID, "User not exist");
//         user_box->text[0] = '\0';  // 清空用户名 
//         pass_box->text[0] = '\0';
//         user_box->is_active = 1;  // 返回用户名输入 
//     }
 
//     /* 登录成功处理 */
//     if(validation_result) {
//         // 播放成功音效（BC3.1的sound函数）
//         sound(2000);
//         delay(100);
//         nosound();
        
//         // 绘制登录成功动画 
//         for(i=0; i<3; i++) {
//             setcolor(LIGHTGREEN);
//             rectangle(200, 180, 440, 320);
//             delay(100);
//             setcolor(WHITE);
//             rectangle(200, 180, 440, 320);
//             delay(100);
//         }
//     }
// }
 
// /* 辅助函数示例 */
// static char* trim_whitespace(char *str) {
//     char *end;
//     // 去除前置空格 
//     while(isspace(*str)) str++;
//     // 去除后置空格 
//     end = str + strlen(str) - 1;
//     while(end > str && isspace(*end)) end--;
//     *(end+1) = '\0';
//     return str;
// }
 
// /* 错误提示函数 */
// void show_error_message(int err_code, const char *msg) {
//     // BC3.1图形模式下的弹窗模拟 
//     setfillstyle(SOLID_FILL, LIGHTRED);
//     bar(150, 160, 490, 200);
//     setcolor(WHITE);
//     rectangle(150, 160, 490, 200);
    
//     settextstyle(SMALL_FONT, HORIZ_DIR, 4);
//     setcolor(WHITE);
//     outtextxy(160, 170, "Error:");
//     outtextxy(160, 185, msg);
    
//     // 错误音效 
//     sound(500);
//     delay(300);
//     nosound();
// }


// void draw_login_graph(void)
// {
//     //开始你的创作吧~
//     return;
// }


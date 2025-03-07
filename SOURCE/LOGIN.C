#include"LOGIN.H"


// 绘制输入框
void draw_input_box(InputBox *box) {
    setcolor(DARKGRAY);
    rectangle(box->x1, box->y1, box->x2, box->y2);
    setfillstyle(SOLID_FILL, WHITE);
    floodfill(box->x1+1, box->y1+1, DARKGRAY);
    
    setcolor(BLACK);
    outtextxy(box->x1 + 5, box->y1 + 5, box->text);
    
    // 绘制光标（若激活）
    if (box->is_active) {
        int text_width = textwidth(box->text);
        line(box->x1 + 5 + text_width, box->y1 + 5,
             box->x1 + 5 + text_width, box->y1 + 15);
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
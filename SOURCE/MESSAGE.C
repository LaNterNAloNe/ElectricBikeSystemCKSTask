#include "MESSAGE.H"

void message_display(int x, int y, char *text) {
    // 显示消息最多使用400像素的宽度，超过将换行
    int pos_x = x;
    int pos_y = y;
    char hz_buffer[3] = {'\0', '\0', '\0'}; // 用于存储汉字的缓冲区
    char asc_buffer[2] = {'\0', '\0'}; // 用于存储ASCII字符的缓冲区

    while (*text != '\0') {
        if (pos_x >= x + 400) { // 达到最大宽度，换行
            pos_x = x; // 重置x坐标
            pos_y += 20; // 增加y坐标，换行
        }

        // 显示字符，判断是汉字还是ASCII字符
        if (*text == '\n') { // 换行符
            pos_x = x; // 重置x坐标
            pos_y += 20; // 增加y坐标，换行
            text++; // 移动到下一个字符
            continue; // 跳过后续处理
        }
        
        if (*text >= (char)0x81 && *text <= (char)0xFE) { // 汉字
            hz_buffer[0] = *text;
            hz_buffer[1] = *(text + 1);
            puthz(pos_x, pos_y, hz_buffer, 16, 16, MY_WHITE); // 显示汉字
            pos_x += 16; // 汉字宽度为16像素
            text += 2; // 跳过已输出汉字的两个字节
        } else { // ASCII字符
            asc_buffer[0] = *text;
            pos_x += 3; // 适当分隔字符
            settextstyle(COMPLEX_FONT, HORIZ_DIR, 1);
            setcolor(MY_WHITE); // 设置字体颜色为白色
            outtextxy(pos_x, pos_y-7, asc_buffer); // 显示ASCII字符
            pos_x += 9; // 设置字符宽度
            text += 1; // 移动到下一个字符
        }
    }
}

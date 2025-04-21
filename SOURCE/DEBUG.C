#include "DEBUG.H"

/* 获取当前程序内存使用量（单位：KB） */
unsigned long get_used_memory()
{
    struct heapinfo hi = {0};
    unsigned long total = 0;
    int ret;

    hi.ptr = NULL;
    while ((ret = heapwalk(&hi)) == _HEAPOK)
    {
        if (hi.in_use)
            total += hi.size;
    }

    if (ret != _HEAPEND)
    {
        outportb(0x80, 0xFF); // 触发硬件调试信号
        return 0;
    }

    return (total * 16UL) / 1024;
}

void display_memory_usage(int x, int y)
{
    static char mem_str[32];
    static clock_t last_update = 0;

    if (clock() - last_update < CLOCKS_PER_SEC / 2)
        return;
    last_update = clock();

    setcolor(WHITE);
    setfillstyle(SOLID_FILL, BLUE);
    bar(x - 5, y - 5, x + 150, y + 20);

    sprintf(mem_str, "MEM: %lu KB", get_used_memory());
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    outtextxy(x, y, mem_str);

    sprintf(mem_str, "FARMEM: %lu B", farcoreleft());
    outtextxy(x, y + 10, mem_str);
}

void show_num(int x, int y, long value, int color)
{
    char text[20];
    sprintf(text, "%ld", value); // 将整数转换为字符串
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1); // 设置字体样式和大小

    setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
    setcolor(BLACK);
    setlinestyle(SOLID_LINE,0, 1);
    rectangle(x-1, y-1, x+textwidth(text)+1, y+textheight(text)+1);
    bar(x,y,x+textwidth(text),y+textheight(text));
    setcolor(color);
    outtextxy(x, y, text);
}

void show_text(int x, int y, char *text, int color){
    setcolor(MY_BLACK);
    setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
    setlinestyle(SOLID_LINE, 0, 1);
    bar(x,y,x+textwidth(text),y+textheight(text));
    rectangle(x - 1, y - 1, x + textwidth(text) + 1, y + textheight(text) + 1);
    setcolor(color);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    outtextxy(x, y, text);
}
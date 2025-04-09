#include "DEBUG.H"

/* 获取当前程序内存使用量（单位：KB） */
unsigned long get_used_memory()
{
    struct heapinfo *hi;
    unsigned long total = 0;

    // 遍历堆内存分配块
    hi->ptr = NULL;
    while (heapwalk(hi) == _HEAPOK)
    {
        if (hi->in_use)
            total += hi->size; // 累计已分配内存
    }

    // 转换为KB（DOS内存块以16字节为单位）
    return (total * 16) / 1024;
}

void display_memory_usage(int x, int y)
{
    static char mem_str[20];
    unsigned long mem_used;

    // 获取内存数据
    mem_used = get_used_memory();

    // 构建显示字符串
    sprintf(mem_str, "MEM: %lu KB", mem_used);

    // 图形模式输出（带背景刷新）
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, BLUE);
    bar(x - 5, y - 5, x + 100, y + 20);
    settextstyle(DEFAULT_FONT, NULL, 1);
    outtextxy(x, y, mem_str);
    sprintf(mem_str, "FARMEM: %lu Byte", farcoreleft());
    outtextxy(x, y + 10, mem_str);
}

void show_num(int x, int y, unsigned long value, int color)
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
    outtextxy(x, y, text);
}
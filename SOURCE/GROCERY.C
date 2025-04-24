#include"GROCERY.H"

/*
获取系统时间
*/
unsigned long get_approx_time(char *time_buffer)
{
    char buffer[10];
    time_t t = time(NULL);                                                            // 获取当前时间
    struct tm *tm = localtime(&t);
    sprintf(buffer, "%04d%02d%02d", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday); // 格式化时间字符串

    if(time_buffer !=NULL)
        strcpy(time_buffer, buffer); // 当传入的指针不为空时，将时间字符串复制到传入的指针指向的内存中

    tm == NULL; // 置零指针
    return atol(buffer);
}

unsigned long get_exact_time(char *exact_buffer)
{
    char buffer[10];
    time_t t = time(NULL);                                                            // 获取当前时间
    struct tm *tm = localtime(&t);
    sprintf(exact_buffer, "%02d%02d%02d", tm->tm_hour , tm->tm_min , tm->tm_sec); // 格式化时间字符串

    if (exact_buffer != NULL)
        strcpy(exact_buffer, buffer); // 当传入的指针不为空时，将时间字符串复制到传入的指针指向的内存中

    tm == NULL; // 置零指针
    return atol(buffer);
}

void initcolorpalette()
{
    setrgbpalette(MY_LIGHTBLUE, 12, 158, 245);  // 浅蓝背景-1
    setrgbpalette(MY_LIGHTGRAY, 235, 235, 235); // 浅灰框-1
    setrgbpalette(MY_BLACK, 0, 0, 0);           // 黑色
    setrgbpalette(MY_YELLOW, 240, 230, 75);     // 黄色
    setrgbpalette(MY_RED, 255, 0, 0);           // 红色
    setrgbpalette(MY_WHITE, 255, 255, 255);     // 白色
    setrgbpalette(MY_GREEN, 0, 255, 0);         // 绿色
    setrgbpalette(MY_CREAM, 61, 62, 55);        // 米色
}

void drawExittingProgram(int err)
{
    clrmous(MouseX, MouseY); // 隐藏鼠标
    setfillstyle(SOLID_FILL, CYAN);
    bar(120, 120, 520, 390);
    if (err == 0)
        puthz(180, 200, "你正在退出程序，按任意键退出", 24, 20, MY_WHITE);
    if (err == 1)
        puthz(180, 200, "无法打开用户数据库", 24, 20, MY_RED);
    if (err == 2)
        puthz(180, 200, "无法为链表分配空间", 24, 20, MY_RED);
}


long constrain_int(long input, long min, long max)
{
    if (input < min)
        return min;
    if (input > max)
        return max;
    return input;
}

void reset_file()
{
    int i = 0;
    FILE *fp;
    char buffer[20];
    char *file_name[] = {
        "DATA\\USER.DAT",
        "DATA\\ANUAL.DAT",
        "DATA\\BROKEN.DAT",
        "DATA\\VIOLA.DAT",
        "DATA\\LICENSE.DAT",
        "DATA\\REGISTER.DAT",
        "DATA\\USRDAT.TXT"};
    int counts = sizeof(file_name) / sizeof(file_name[0]);

    for (i = 0; i < counts; i++) // 遍历文件列表
    {
        fp = fopen(file_name[i], "w"); // 打开文件，清空内容
        if (fp == NULL)
        {
            sprintf(buffer, "%s", file_name[i]); // 拼接完整路径
            perror("reset_file: cannot reset ANUAL.DAT\n");
            getch();
            exit(1);
        }
        fclose(fp); // 关闭文件
    }
    
    if (debug_mode == 1)
        show_text(10, 10, "All files have been reset. Press any key to continue..."), getch();
}
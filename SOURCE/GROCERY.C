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

    return atol(buffer);
}
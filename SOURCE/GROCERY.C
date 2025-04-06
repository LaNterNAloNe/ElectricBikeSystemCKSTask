
#include"GROCERY.H"


long get_time(void)
{
    char buffer[10];
    time_t t = time(NULL);                                                            // 获取当前时间
    struct tm *tm = localtime(&t);                                                    // localtime和time都是time.h中的函数
    sprintf(buffer, "%04d%02d%02d", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday); // 格式化时间字符串
    return atol(buffer);
}
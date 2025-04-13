#include "RANDOM.H"

/** 生成随机字符串 **/

void rand_id(char *output)
{
    int i;
    output[0] = rand() % 9 + 1 + '0'; // 首位1-9
    for (i = 1; i < 9; i++)
        output[i] = rand() % 10 + '0';
    output[9] = '\0';
}

void rand_ebike_id(char *output)
{
    int i;
    for (i = 0; i < 2; i++)
        output[i] = 'A' + rand() % 26; // 生成大写字母
    for (i = 2; i < 6; i++)
        output[i] = '0' + rand() % 10; // 生成数字
    output[6] = '\0';
}

void rand_license(char *output)
{
    int i;
    output[0] = 'A' + rand() % 26;
    for (i = 1; i < 8; i++)
        output[i] = '0' + rand() % 10;
    output[8] = '\0';
}

void rand_time(long *output, int is_past_year)
{
    time_t now = time(NULL);
    struct tm base = *localtime(&now);
    int rand_days = rand() % 365; // 生成随机偏移量
    int rand_sec = rand() % 86400;

    // 设置时间范围
    if (is_past_year)
        base.tm_year--; // 前一年范围
    else
        base.tm_year++; // 后一年范围
    
    // 生成有效时间
    mktime(&base);
    base.tm_mday += rand_days;
    base.tm_sec += rand_sec;
    mktime(&base); // 自动处理时间溢出

    // 格式化为YYYYMMDD的8位数
    *output =  base.tm_year * 10000 + (base.tm_mon + 1) * 100 + base.tm_mday;
}

void rand_violations(int *output)
{
    int r = rand() % 100;
    if (r < 80)
        *output = 0; // 80%概率
    if (r < 98)
        *output = 1 + (r % 2); // 18%概率1-2
    *output = 3;               // 2%概率
}

void rand_location(char *output)
{
    const char *directions[] = {"EAST", "WEST", "SOUTH", "NORTH"};
    int dir = rand() % 4;

    // 生成1-2位数字
    int num_len = 1 + (rand() % 2);
    output[0] = '1' + rand() % 9;
    if (num_len > 1)
        output[1] = '0' + rand() % 10;

    // 组合字符串
    sprintf(output, "%s%c%c", directions[dir], output[0], (num_len > 1) ? output[1] : '\0');
}
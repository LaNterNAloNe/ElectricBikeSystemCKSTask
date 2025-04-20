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
void rand_exist_id(char *output, LINKLIST *LIST)
{
    long count = 0;
    LINKLIST_NODE *node = LIST->HEAD;
    strcpy(output, "\0");

    while (strcmp(output, "\0") == 0)
    {
        linklist_get_to_node(LIST, rand_int(1, linklist_get_length(LIST)), &node); // 随机获取链表中的数据

        if (strcmp(node->USER_DATA.ebike_ID, "\0") != 0)
            continue;
        else
        {
            strcpy(output, node->USER_DATA.ID); // 该id的数据有ebike_id信息，符合要求
            break;
        }
    }
}

void rand_ebike_id(char *output, LINKLIST *LIST)
{
    int i;
    LINKLIST_NODE *node = LIST->HEAD;
    strcpy(output, "\0");

    while(strcpy(output, "\0") == 0){
        for (i = 0; i < 2; i++)
            output[i] = 'A' + rand() % 26; // 生成大写字母
        for (i = 2; i < 6; i++)
            output[i] = '0' + rand() % 10; // 生成数字
        output[6] = '\0';
        // 确保id不与现有的重复
        while (node != NULL)
        {
            if (strcmp(node->USER_DATA.ebike_ID, output) == 0)
            {
                strcpy(output, "\0");
                break;
            }
            node = node->NEXT; // 继续遍历链表
        }
        // 经过上一个循环，如果output没有被设为"\0"，则说明没有重复，退出循环
    }

    node == NULL; // 置零指针
}

void rand_license(char *output)
{
    int i;
    output[0] = 'A' + rand() % 26;
    for (i = 1; i < 8; i++)
        output[i] = '0' + rand() % 10;
    output[8] = '\0';
}

void rand_time(long *output, int is_past_year, int is_today)
{
    time_t now = time(NULL);
    struct tm base = *localtime(&now);
    int rand_days = rand() % 365; // 生成随机偏移量

    if (is_today == 0)
    {
        // 设置时间范围
        if (is_past_year)
            base.tm_year--; // 前一年范围
        else
            base.tm_year++; // 后一年范围

        // 生成有效时间
        mktime(&base);
        base.tm_mday += rand_days;
        mktime(&base); // 自动处理时间溢出

        // 格式化为YYYYMMDD的8位数
        
    }

    *output = base.tm_year * 10000 + (base.tm_mon + 1) * 100 + base.tm_mday;
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

int rand_io_comment()
{
    const int comment[] = {
        EBIKE_IN_TAKE_OUT,
        EBIKE_OUT_TAKE_OUT,
        EBIKE_IN_VISIT,
        EBIKE_OUT_VISIT,
        EBIKE_IN_OTHER,
        EBIKE_OUT_OTHER,
    };
    int r = rand() % 6;
    return comment[r];
}

void rand_location(char *output, int gate_needed)
{
    const char *directions[] = {"EAST", 
                                "WEST", 
                                "SOUTH", 
                                "NORTH"};
    const char *gate[] = {"South1Gate", 
                          "South2Gate", 
                          "South3Gate", 
                          "WestGate", 
                          "East1Gate", 
                          "East2Gate", 
                          "NorthGate", 
                          "YunGate",
                          "ZiGate"}; // 门牌号
    int dir;
    int num_len;

    if (gate_needed == 0)
    {
        dir = rand() % 4;

        // 生成1-2位数字
        num_len = 1 + (rand() % 2);
        output[0] = '1' + rand() % 9;
        if (num_len > 1)
            output[1] = '0' + rand() % 10;

        // 组合字符串
        sprintf(output, "%s%c%c", directions[dir], output[0], (num_len > 1) ? output[1] : '\0');
    }
    else 
    {
        dir = rand() % 9; // 随机选择门牌号
        sprintf(output, "%s", gate[dir]); // 组合字符串
    }
}

long rand_int(long min, long max)
{
    long result = min + labs(rand() % (max - min + 1));
    return result;
}

// 这个函数会在程序开始时执行，生成随机的进出校园信息，采用覆盖之前文件的方式
void rand_io_data(LINKLIST *LIST)
{
    int i, rand_divide = 0, pos = -1;
    char buffer[20];
    FILE *fp = fopen("IOTMP.DAT", "wb+");
    LINKLIST_NODE *user_data;
    EBIKE_IN_OUT io_data;
    if (fp == NULL)
    {
        closegraph();
        printf("Error: Cannot open file IOTMP.DAT\n");
        getch();
        exit(1);
    }

    rand_divide += (linklist_get_length(LIST) / 12) % 4 + (linklist_get_length(LIST) % 12) || 0; // 计算概率
    rand_divide = constrain_int(rand_divide, 0, 3);      // 限制概率范围

    // 生成随机数据
    for (i = 0; i < 48; i++) // 一次生成48条数据
    {
        
        io_data.apply_id = rand_int(1000000000, 9999999999); // 生成10位数字

        if (rand_int(1, 4) <= rand_divide) // 概率生成在校成员进出校园，进入这个语句的前提是链表中有数据
        {
            rand_exist_id(io_data.ebike_id, LIST); // 生成选择已有ebike_id
            pos = linklist_find_data(LIST, io_data.ebike_id, "ebike_id");
            if (pos > 0)
            {
                linklist_get_to_node(LIST, pos, &user_data);
                strcpy(io_data.ebike_license, user_data->USER_DATA.ebike_license); // 复制ebike_license
                rand_location(io_data.location);                                   // 生成随机location
                if (rand_int(1, 2) == 1)                                           // 50%概率
                {
                    rand_time(&io_data.in_time, 0, 1);                                 // 生成随机time
                    io_data.out_time = 0;
                    io_data.comment = EBIKE_IN_OUT_REGISTERED_UNIT_IN;
                }
                else
                {
                    rand_time(&io_data.out_time, 0, 1); // 生成随机time
                    io_data.in_time = 0;
                    io_data.comment = EBIKE_IN_OUT_REGISTERED_UNIT_OUT;
                }

                io_data.result = 1; // 校园单位无需后台审核
            }
            else // 未在链表中找到ebike_id
            {
                i--; // 重新生成
                continue;
            }

        }
        else // 概率生成外放车辆进出校园
        {
            rand_ebike_id(io_data.ebike_id, LIST);                     // 生成随机现在没有的ebike_id
            strcmp(io_data.ebike_license, "\0");                       // 不生成通行证
            rand_location(io_data.location, 1);                        // 生成随机location
            if (rand_int(1, 2) == 1)                                    // 50%概率
            {
                rand_time(&io_data.in_time, 0, 1);                          // 生成随机time
                io_data.out_time = 0;
                io_data.comment = rand_io_comment();
            }
            else
            {
                rand_time(&io_data.out_time, 0, 1); // 生成随机time
                io_data.in_time = 0;
                io_data.comment = rand_io_comment(); 
            }

            if (i > 45)
                io_data.result = 0; // 校园单位无需后台审核
            else
                io_data.result = 1; // 校园单位需要后台审核
        }
    }

}


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

        if (strcmp(node->USER_DATA.ebike_ID, "0") == 0)
            continue;
        else
        {
            strcpy(output, node->USER_DATA.ebike_ID); // 该id的数据有ebike_id信息，符合要求
            break;
        }
    }
}

void rand_ebike_id(char *output, LINKLIST *LIST)
{
    int i;
    LINKLIST_NODE *node = LIST->HEAD;
    strcpy(output, "\0");

    while(strcmp(output, "\0") == 0)
    {
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

void rand_license(LINKLIST *LIST, char *output)
{
    int i;
    while(1){
        output[0] = 'A' + rand() % 26;
        for (i = 1; i <= 8; i++)
            output[i] = '0' + rand() % 10;
        output[9] = '\0';


        if (linklist_find_data(LIST, output, "license") == -1)
            break;
    }
}

void rand_time(long *output, int is_past_year, int is_today)
{
    time_t now = time(NULL);
    struct tm *base = localtime(&now);
    int rand_days = rand() % 365; // 生成随机偏移量
    
    if (is_today == 0)
    {
        // 设置时间范围
        if (is_past_year)
            base->tm_year--; // 前一年范围
        else
            base->tm_year++; // 后一年范围

        // 生成有效时间
        mktime(base);
        base->tm_mday += rand_days;
        mktime(base); // 自动处理时间溢出

        // 格式化为YYYYMMDD的8位数
        
    }

    *output = (long)(base->tm_year + 1900) * 10000 + (base->tm_mon + 1) * 100 + base->tm_mday;
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
        EBIKE_OUT_OTHER
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
    const char *gate[] = {"南大门", 
                          "南二门", 
                          "南三门", 
                          "西大门", 
                          "东一门", 
                          "东二门", 
                          "北大门", 
                          "韵苑大门",
                          "紫菘大门"}; // 门牌号
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
    long result;
    if (min > max)
        return -1;
    result = min + labs(rand() % (max - min + 1));
    return result;
}

// 这个函数会在程序开始时执行，生成随机的进出校园信息，采用覆盖之前文件的方式
void rand_io_data(LINKLIST *LIST)
{
    int i, rand_divide = 0, pos = -1;
    char buffer[20];
    FILE *fp = fopen("DATA\\IOTMP.DAT", "wb");
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
                rand_location(io_data.location, 0);                                   // 生成随机location
                if (rand_int(1, 2) == 1)                                           // 50%概率
                {
                    rand_time(&io_data.in_time, 0, 1);                                 // 生成随机time
                    io_data.out_time = 0;
                    io_data.comment = EBIKE_IN_OUT_REGISTERED_UNIT_IN;
                    rand_location(io_data.location, 1); // 生成随机门牌号
                }
                else
                {
                    rand_time(&io_data.out_time, 0, 1); // 生成随机time
                    io_data.in_time = 0;
                    io_data.comment = EBIKE_IN_OUT_REGISTERED_UNIT_OUT;
                    rand_location(io_data.location, 1); // 生成随机门牌号
                }

                io_data.result = PASSED; // 校园单位无需后台审核
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
                io_data.result = PENDING;
            else
                io_data.result = PASSED;
        }

        fseek(fp, i * sizeof(EBIKE_IN_OUT), SEEK_SET); // 移动文件指针到文件末尾
        fwrite(&io_data, sizeof(EBIKE_IN_OUT), 1, fp); // 写入文件
    }
    fclose(fp); // 关闭文件

    // 将temp文件替换IO文件
    remove("DATA\\IO.DAT"); // 删除IO文件

    if(rename("DATA\\IOTMP.DAT", "DATA\\IO.DAT") != 0) // 重命名temp文件为IO文件
    {
        closegraph();
        printf("Error: Cannot rename file IOTMP.DAT\n");
        getch();
        exit(1);
    }

}

void rand_msg()
{
    int i;
    char buffer[20];
    FILE *fp = fopen("DATA\\MSGTMP.DAT", "wb+");
    MESSAGE msg;
    if (fp == NULL)
    {
        closegraph();
        printf("Error: Cannot open file MSGTMP.DAT\n");
        getch();
        exit(1);
    }

    // 生成随机数据
    for (i = 0; i < 10; i++) // 一次生成10条数据
    {
        rand_id(buffer); // 生成随机id
        msg.message_id = atol(buffer);
        rand_time(&msg.time, 0, 1); // 生成随机time
        strcpy(msg.receiver_username, "all_admin");
        ltoa(msg.message_id, buffer, 10);
        strcpy(msg.sender_username, buffer);
        strcpy(msg.title, "测试消息");
        strcpy(msg.message, "这是一条测试消息");
        msg.is_read = 0; // 未读
        msg.is_replied = 0; // 未回复
        msg.message_type = ANNOUNCEMENT; // 公告

        fseek(fp, i * sizeof(MESSAGE), SEEK_SET); // 移动文件指针到文件末尾
        fwrite(&msg, sizeof(MESSAGE), 1, fp); // 写入文件
    }

    fflush(fp);
    fclose(fp); // 关闭文件

    // 将temp文件替换IO文件
    remove("DATA\\MESSAGE.DAT"); // 删除IO文件

    if(rename("DATA\\MSGTMP.DAT", "DATA\\MESSAGE.DAT") != 0) // 重命名temp文件为IO文件
    {
        closegraph();
        printf("Error: Cannot rename file MSGTMP.DAT to MESSAGE.DAT\n");
        getch();
        exit(1);
    }
}

void rand_violation_data(LINKLIST *LIST)
{
    int i;
    const int rand_devide = 90;
    char buffer[20];
    FILE *fp = NULL;
    EBIKE_INFO ebike_info;
    LINKLIST_NODE *node = NULL;

    if (rand_int(1, linklist_get_length(LIST)) != -1)
    {
        fp = fopen("DATA\\VIOLA.DAT", "rb+");
        fseek (fp, 0, SEEK_SET); // 移动文件指针到文件开头

        for (i = 0; i < 10; i++) // 一次尝试生成10条数据，可能不会生成10条
        {
            node = NULL;
            if (rand_int(1, 100) < rand_devide) // 随机获取链表中的数据
            {
                if (debug_mode == 1){
                    sprintf(buffer, "rand violation: %d", i);
                    show_text(50, 10 * i, buffer, MY_WHITE);
                }
                continue;
            }
            else
            {
                rand_exist_id(buffer, LIST);                                                           // 生成选择已有ebike_id
                linklist_get_to_node(LIST, linklist_find_data(LIST, buffer, "ebike_id"), &node); // 找到该id的数据
                if (node == NULL)
                {
                    if (debug_mode == 1){
                        show_text(10, 10, "Error: Cannot get random violation history: cannot find node", MY_WHITE);
                        getch();
                    }
                    fclose(fp);
                    return;
                }
                strcpy(ebike_info.ebike_ID, node->USER_DATA.ebike_ID); // 复制ebike_id
                strcpy(ebike_info.ebike_license, node->USER_DATA.ebike_license); // 复制ebike_license
                strcpy(ebike_info.location, node->USER_DATA.location);           // 复制location
                ebike_info.ID = node->USER_DATA.ID; // 复制ID
                ebike_info.violations = node->USER_DATA.violations; // 赋值违章次数
                ebike_info.result = PENDING;
                ebike_info.conduct_time = 0;
                ebike_info.apply_time = get_approx_time(NULL);
                
                fwrite (&ebike_info, sizeof(EBIKE_INFO), 1, fp); // 写入文件

                memset(&ebike_info, '\0', sizeof(EBIKE_INFO)); // 清空结构体
            }
        }
    }

    node = NULL;
    fclose(fp); // 关闭文件

    if (debug_mode == 1)
    {
        show_text(10, 10, "Success: Random violation history generated success", MY_WHITE);
        getch();
    }
}


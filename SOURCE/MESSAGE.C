#include "MESSAGE.H"

/*************************************************************
MESSAGE:用户与管理员产生交互的功能模块
RETURNL:返回值统一为：（1）执行成功返回1；（2）执行失败（含各种原因）返回0
*************************************************************/

void message_display(MESSAGE msg,int _x, int _y, int _listed_item, int _max, int _interval, int list_sequence)
{
    // 显示消息的主题
    char buffer[30]; // 定义缓冲区

    setcolor(MY_WHITE); // 设置字体颜色为白色
    if (list_sequence == ASCENDING)
    {
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);                                                                    // 设置字体样式和方向
        message_topic_display(_x, _y + _interval * _listed_item, 200, msg.title); // 显示消息的主题
        outtextxy(_x + 300, _y + _interval * _listed_item, msg.sender_username); // 显示空格
        if (msg.is_read == 1) { // 如果消息已读，则显示已读
            outtextxy(_x + 420, _y + _interval * _listed_item, "已读"); // 显示已读
        } else { // 如果消息未读，则显示未读
            outtextxy(_x + 420, _y + _interval * _listed_item, "未读"); // 显示未读
        }
    }
    else if (list_sequence == DESCENDING)
    {
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);                                                                    // 设置字体样式和方向
        message_topic_display(_x, _y + _interval * (_max - _listed_item - 1), 200, msg.title); // 显示消息的主题
        outtextxy(_x + 300, _y + _interval * (_max - _listed_item - 1), msg.sender_username); // 显示空格
        if (msg.is_read == 1) { // 如果消息已读，则显示已读
            outtextxy(_x + 420, _y + _interval * (_max - _listed_item - 1), "已读"); // 显示已读
        } else { // 如果消息未读，则显示未读
            outtextxy(_x + 420, _y + _interval * (_max - _listed_item - 1), "未读"); // 显示未读
        }
    }
    else
    {
        return; // 如果传入参数错误，则不做任何操作
    }

    delay(25); // 延时25ms，使列表的动画更有动感
}

void message_topic_display(int _x, int _y, int _width, char *_text)
{
    int pos_x = _x;
    int pos_y = _y;
    char hz_buffer[3] = {'\0', '\0', '\0'}; // 用于存储汉字的缓冲区
    char asc_buffer[2] = {'\0', '\0'};      // 用于存储ASCII字符的缓冲区

    if (_text == NULL)
    { // 检查传入的文本是否为空
        puthz(_x, _y, "文本为空", 16, 16, MY_RED);
        return; // 如果为空，直接返回
    }
    if (_width < 16)
    {
        puthz(_x, _y, "宽度不足", 16, 16, MY_RED);
        return; // 如果宽度不足，直接返回
    }

    while (*_text != '\0')
    {
        if (pos_x >= _x + _width)
        {                // 达到最大宽度，换行
            settextstyle(COMPLEX_FONT, HORIZ_DIR, 1);
            setcolor(MY_WHITE);                      // 设置字体颜色为白色
            outtextxy(pos_x, pos_y - 7, "..."); // 显示ASCII字符
        }

        if (*_text >= (char)0x81 && *_text <= (char)0xFE)
        { // 汉字
            hz_buffer[0] = *_text;
            hz_buffer[1] = *(_text + 1);
            puthz(pos_x, pos_y, hz_buffer, 16, 16, MY_WHITE); // 显示汉字
            pos_x += 16;                                      // 汉字宽度为16像素
            _text += 2;                                       // 跳过已输出汉字的两个字节
        }
        else
        { // ASCII字符
            asc_buffer[0] = *_text;
            pos_x += 3; // 适当分隔字符
            settextstyle(COMPLEX_FONT, HORIZ_DIR, 1);
            setcolor(MY_WHITE);                      // 设置字体颜色为白色
            outtextxy(pos_x, pos_y - 7, asc_buffer); // 显示ASCII字符
            pos_x += 9;                              // 设置字符宽度
            _text += 1;                              // 移动到下一个字符
        }
    }
}

// 显示消息
void message_text_display(int _x, int _y, int _width, char *_text)
{
    int pos_x = _x;
    int pos_y = _y;
    char hz_buffer[3] = {'\0', '\0', '\0'}; // 用于存储汉字的缓冲区
    char asc_buffer[2] = {'\0', '\0'}; // 用于存储ASCII字符的缓冲区

    if (_text == NULL) { // 检查传入的文本是否为空
        puthz(_x, _y, "文本为空", 16, 16, MY_RED);
        return; // 如果为空，直接返回
    }
    if (_width < 16) {
        puthz(_x, _y, "宽度不足", 16, 16, MY_RED);
        return; // 如果宽度不足，直接返回
    }

    while (*_text != '\0') {
        if (pos_x >= _x + _width)
        {               // 达到最大宽度，换行
            pos_x = _x; // 重置x坐标
            pos_y += 20; // 增加y坐标，换行
        }

        // 显示字符，判断是汉字还是ASCII字符
        if (*_text == '\n') { // 换行符
            pos_x = _x; // 重置x坐标
            pos_y += 20; // 增加y坐标，换行
            _text++; // 移动到下一个字符
            continue; // 跳过后续处理
        }
        
        if (*_text >= (char)0x81 && *_text <= (char)0xFE) { // 汉字
            hz_buffer[0] = *_text;
            hz_buffer[1] = *(_text + 1);
            puthz(pos_x, pos_y, hz_buffer, 16, 16, MY_WHITE); // 显示汉字
            pos_x += 16; // 汉字宽度为16像素
            _text += 2; // 跳过已输出汉字的两个字节
        } else { // ASCII字符
            asc_buffer[0] = *_text;
            pos_x += 3; // 适当分隔字符
            settextstyle(COMPLEX_FONT, HORIZ_DIR, 1);
            setcolor(MY_WHITE); // 设置字体颜色为白色
            outtextxy(pos_x, pos_y-7, asc_buffer); // 显示ASCII字符
            pos_x += 9; // 设置字符宽度
            _text += 1; // 移动到下一个字符
        }
    }
}

// 获取消息
int message_get(FILE *fp, MESSAGE *msg, char *search_str, char *search_needed)
{
    long i = 1;
    long counts;
    MESSAGE msg_buffer; // 用于存储读取的消息
    if (fp == NULL || msg == NULL)
    { // 检查文件指针是否为空
        return 0;
    }

    fseek(fp, 0, SEEK_END); // 将文件指针移动到文件开头

    counts = ftell(fp) / sizeof(MESSAGE); // 计算文件中的消息数量

    if (counts == 0) // 检查文件中是否有消息
    { // 如果没有消息，返回0
        return 0;
    }

    while (i > counts) { // 逐行读取文件内容
        if (fseek(fp, - i * sizeof(MESSAGE), SEEK_CUR) == -1); // 将文件指针回退到上一行的开头
        {
            return 0; // 如果回退失败，返回0
        }
        fread(&msg_buffer, sizeof(MESSAGE), 1, fp);

        if (message_is_valid(msg_buffer, search_str, search_needed) == 1)
        { // 检查消息是否有效
            *msg = msg_buffer; // 将有效消息复制到传入的指针指向的内存中
            return 1;
        }

        i++;
    }
}

// 检查消息是否有效
int message_is_valid(MESSAGE msg, char *search_str, char *search_needed) 
{
    if ((search_str == "\0" || search_str == NULL) &&
        (search_needed == "\0" || search_needed == NULL)) // 检查搜索字符串是否为空或为NULL
    { 
        return 1; // 如果为空或为NULL，返回1
    }
    if (msg.sender_id == atol(search_str) && strcmp(search_needed, "sender_id") == 0 ||
        msg.receiver_id == atol(search_str) && strcmp(search_needed, "receiver_id") == 0 ||
        strcmp(msg.sender_username, search_str) && strcmp(search_needed, "sender_username") == 0 ||
        strcmp(msg.receiver_username, search_str) && strcmp(search_needed, "receiver_username") == 0 ||
        strcmp(msg.sender_username, search_str) && strcmp(search_needed, "sender_username") == 0 ||
        msg.is_read == atoi(search_str) && strcmp(search_needed, "is_read") == 0) // 比较ID是否匹配
    { 
        return 1; // 如果匹配，返回1
    }
    else
    {
        return 0; // 如果不匹配，返回0
    }
}

// 尝试查找目标消息
int message_if_found(int __is_read)
{
    FILE *fp = fopen("DATA\\MESSAGE.DAT", "rb"); // 打开消息文件，以二进制读取模式打开
    MESSAGE msg; // 用于存储读取的消息
    long i = 1;
    int found = 0; // 用于记录是否找到消息
    long counts;

    if (fp == NULL) // 检查文件指针是否为空
    { // 如果为空，输出错误信息并返回
        return 0; // 返回
    }

    fseek(fp, 0, SEEK_END); // 将文件指针移动到文件末尾

    counts = ftell(fp) / sizeof(MESSAGE); // 计算文件中的消息数量

    if (counts == 0) // 检查文件中是否有消息
    { // 如果没有消息，输出错误信息并返回
        return 0; // 返回
    }

    while (i > counts || found) // 逐行读取文件内容
    { // 逐行读取文件内容
        if (fseek(fp, - i * sizeof(MESSAGE), SEEK_CUR) == -1); // 将文件指针回退到上一行的开头
        { // 如果回退失败，输出错误信息并返回
            return 0; // 返回
        }
        fread(&msg, sizeof(MESSAGE), 1, fp); // 读取消息到msg变量中

        if (msg.is_read == __is_read) // 检查消息是否已读
        { // 如果消息未读
            found = 1; // 设置found为1，表示找到了未读消息
            break; // 跳出循环
        }

        i++; // 增加计数器
    }

    fclose(fp);
    
    return found; // 返回found的值
}

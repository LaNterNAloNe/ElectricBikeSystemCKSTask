#include "MESSAGE.H"

/*************************************************************
MESSAGE:用户与管理员产生交互的功能模块
RETURN:返回值统一为：（1）执行成功返回1；（2）执行失败（含各种原因）返回0
*************************************************************/

void message_display(MESSAGE *msg)
{
    ADMIN_BUTTONS btn[3]; // 定义按钮变量
    int tag = ACTIVE_ADMIN_NULL; // 定义标签变量
    int is_return = 0;
    int mouse_flag;
    define_admin_buttons(btn, ADMIN_MESSAGE); // 定义按钮
    if (msg->message_type != PRIVATE_MESSAGE)
    {
        memset(&btn[2], '\0', sizeof(btn[2])); // 清空按钮变量
    }

    message_display_draw_bg();
    if (msg == NULL)
    {
        message_topic_display(120, 35, 400, "信息错误", MY_RED, 26, 3, 0); // 显示消息的主题
    }
    else
    {
        message_topic_display(120, 35, 400, msg->title, MY_BLACK, 26, 3, 0); // 显示消息的主题
        message_text_display(120, 80, 400, msg->sender_username, MY_BLACK);  // 显示消息的内容
        message_text_display(120, 110, 400, msg->message, MY_BLACK);         // 显示消息的发送者
    }
    
    while (is_return == 0)
    {
        newmouse_data(&MouseX, &MouseY, &press, &mouse_flag);

        admin_flush_buttons(&tag, 3, btn); // 刷新按钮
        message_handle_click_event(&is_return, msg); // 处理点击事件

        newmouse(&MouseX, &MouseY, &press, &mouse_flag);
    }
}

void message_reply(int *is_return, MESSAGE *msg)
{
    int tag = ACTIVE_ADMIN_NULL; // 定义标签变量
    ADMIN_BUTTONS btn[2]; // 定义按钮变量
    char message[512]; // 定义消息变量
    int mouse_flag;
    define_admin_buttons(btn, ADMIN_MESSAGE_REPLY); // 定义按钮

    message_draw_reply_bg(msg); // 绘制背景

    while (*is_return == 0)
    {
        newmouse_data(&MouseX, &MouseY, &press, &mouse_flag);

        admin_flush_buttons(&tag, 2, btn); // 刷新按钮
        message_handle_click_event(is_return, msg); // 处理点击事件

        newmouse(&MouseX, &MouseY, &press, &mouse_flag);
    }
}

void message_list(MESSAGE msg,int _x, int _y, int _listed_item, int _max, int _interval, int list_sequence)
{
    // 显示消息的主题
    char buffer[30]; // 定义缓冲区

    setcolor(MY_WHITE); // 设置字体颜色为白色
    if (list_sequence == ASCENDING)
    {
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);                                                                    // 设置字体样式和方向
        message_topic_display(_x, _y + _interval * _listed_item, 200, msg.title, MY_WHITE, 16, 1, 1); // 显示消息的主题
        outtextxy(_x + 300, _y + _interval * _listed_item, msg.sender_username);                      // 显示用户名
        if (msg.is_read == 1) { // 如果消息已读，则显示已读
            outtextxy(_x + 420, _y + _interval * _listed_item, "已读"); // 显示已读
        } else { // 如果消息未读，则显示未读
            outtextxy(_x + 420, _y + _interval * _listed_item, "未读"); // 显示未读
        }
    }
    else if (list_sequence == DESCENDING)
    {
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);                                                                    // 设置字体样式和方向
        message_topic_display(_x, _y + _interval * (_max - _listed_item - 1), 200, msg.title, MY_WHITE, 16, 1, 1);   // 显示消息的主题
        outtextxy(_x + 300, _y + _interval * (_max - _listed_item - 1), msg.sender_username);                        // 显示用户名
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

void message_topic_display(int _x, int _y, int _width, char *_text, int _text_color, int _hz_font_size, int _asc_font_size, int _is_light)
{
    int pos_x = _x;
    int pos_y = _y;
    char hz_buffer[3] = {'\0', '\0', '\0'}; // 用于存储汉字的缓冲区
    char asc_buffer[2] = {'\0', '\0'};      // 用于存储ASCII字符的缓冲区
    int real_size = _hz_font_size;

    if (_hz_font_size / 10  == 24){
        real_size = _hz_font_size / 10;
    }

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
            if (_is_light == 1) {
                settextstyle(COMPLEX_FONT, HORIZ_DIR, _asc_font_size);
                setcolor(_text_color);              // 设置字体颜色为白色
                outtextxy(pos_x, pos_y - 7, "..."); // 显示省略号
                break;
            }
            else {
                pos_x = _x; // 重置x坐标
                pos_y += _hz_font_size + 4; // 增加y坐标，换行
            }
        }

        if (*_text >= (char)0x81 && *_text <= (char)0xFE)
        { // 汉字
            hz_buffer[0] = *_text;
            hz_buffer[1] = *(_text + 1);
            puthz(pos_x, pos_y, hz_buffer, _hz_font_size, NULL, _text_color); // 显示汉字
            pos_x += real_size;                                               // 汉字宽度为16像素
            _text += 2;                                       // 跳过已输出汉字的两个字节
        }
        else
        { // ASCII字符
            asc_buffer[0] = *_text;
            pos_x += 3; // 适当分隔字符
            settextstyle(COMPLEX_FONT, HORIZ_DIR, _asc_font_size);
            setcolor(_text_color);                   // 设置字体颜色为白色
            outtextxy(pos_x, pos_y - 7, asc_buffer); // 显示ASCII字符
            pos_x += (8 + _asc_font_size);                              // 设置字符宽度
            _text += 1;                              // 移动到下一个字符
        }
    }
}

// 显示消息
void message_text_display(int _x, int _y, int _width, char *_text, int _text_color)
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
            puthz(pos_x, pos_y, hz_buffer, 16, 16, _text_color); // 显示汉字
            pos_x += 16; // 汉字宽度为16像素
            _text += 2; // 跳过已输出汉字的两个字节
        } else { // ASCII字符
            asc_buffer[0] = *_text;
            pos_x += 3; // 适当分隔字符
            settextstyle(COMPLEX_FONT, HORIZ_DIR, 1);
            setcolor(_text_color);                 // 设置字体颜色为白色
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

// 覆盖消息
int message_overwrite(FILE *fp, MESSAGE *msg, char *search_str, char *search_needed)
{
    long i = 1;
    long counts;
    MESSAGE msg_buffer; // 用于存储读取的消息

    if (fp == NULL || msg == NULL) // 检查文件指针和消息指针是否为空
    { // 如果为空，返回0
        return 0;
    }

    fseek(fp, 0, SEEK_END); // 将文件指针移动到文件末尾

    counts = ftell(fp) / sizeof(MESSAGE); // 计算文件中的消息数量

    if (counts == 0) // 检查文件中是否有消息
    { // 如果没有消息，返回0
        return 0;
    }

    while (i > counts)
    { // 逐行读取文件内容
        if (fseek(fp, -i * sizeof(MESSAGE), SEEK_CUR) == -1)
            ; // 将文件指针回退到上一行的开头
        {
            return 0; // 如果回退失败，返回0
        }
        fread(&msg_buffer, sizeof(MESSAGE), 1, fp);

        if (message_is_valid(msg_buffer, search_str, search_needed) == 1) // 检查消息是否为目标信息
        {
            fseek (fp, -i * sizeof(MESSAGE), SEEK_CUR); // 将文件指针回退到上一行的开头
            fwrite (msg, sizeof(MESSAGE), 1, fp); // 将消息写入文件
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
        strcmp("all_user", search_str) && strcmp(search_needed, "receiver_username") == 0 || // 枚举两种特殊情况
        strcmp("all_admin", search_str) && strcmp(search_needed, "receiver_username") == 0 ||
        strcmp(msg.sender_username, search_str) && strcmp(search_needed, "sender_username") == 0 ||
        msg.is_read == atoi(search_str) && strcmp(search_needed, "is_read") == 0)
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
        fclose(fp);
        return 0; // 返回
    }

    while (i > counts || found) // 逐行读取文件内容
    { // 逐行读取文件内容
        if (fseek(fp, - i * sizeof(MESSAGE), SEEK_CUR) == -1); // 将文件指针回退到上一行的开头
        { // 如果回退失败，输出错误信息并返回
            fclose(fp);
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

// 处理信息列表点击
void message_list_click(int _x, int _y, int _listed_item, int _max, int _interval, int _item_id[], long *_selected_id) 
{
    MESSAGE msg; // 用于存储读取的消息
    FILE *fp = NULL;
    int i = 0; // 用于循环计数
    unsigned int previous_selected_id = *_selected_id; // 用于存储上一次选中的消息ID，非静态变量

    for (i = 0; i < _max; i++)
    {
        if (mouse_press(_x + 20, _y + 70 + i * _interval, _x + 500, _y + 70 + (i + 1) * _interval - 1) == 1 &&
            _item_id[i] != 0 && _item_id[i] != previous_selected_id)
        {
            *_selected_id = _item_id[i]; // 更新选中的消息ID

            if (previous_selected_id == *_selected_id && *_selected_id != 0)
            // 如果选中的消息ID与上一次选中的消息ID相同，并且不为0
            // 则执行信息显示操作
            {
                fp = fopen("DATA\\MESSAGE.DAT", "rb+"); // 打开消息文件，以二进制读取模式打开
                if (fp == NULL) // 检查文件指针是否为空
                { // 如果为空，输出错误信息并返回
                    return; // 返回
                }

                message_get(fp, &msg, (char *)_selected_id, "message_id"); // 读取选中的消息
                message_display(&msg); // 显示选中的消息

                msg.is_read = 1; // 将消息标记为已读
                message_overwrite(fp, &msg, (char *)_selected_id, "message_id"); // 将选中的消息标记为已读
                previous_selected_id = 0;
                *_selected_id = 0;
                fclose(fp);
            }
            break;
        }
    }


    if (previous_selected_id == *_selected_id &&
        mouse_press(_x + 20, _y + 70 + _listed_item * _interval, _x + 500, _y + 70 + (_listed_item + 1) * _interval - 1) == -1)
    {
        // 经过上面循环发现没有选中正确的行，_selected_id不会发生改变，因此和previous相同
        *_selected_id = 0; // 重置选中的消息ID
    }
}

void message_handle_click_event(int *is_return, MESSAGE *msg)
{
    // 处理鼠标点击事件
    if (mouse_press(ADMIN_MESSAGE_REPLY_X1, ADMIN_MESSAGE_REPLY_Y1, ADMIN_MESSAGE_REPLY_X2, ADMIN_MESSAGE_REPLY_Y2) == 1 &&
        msg->message_type != ANNOUNCEMENT && msg->is_replied == 0) // 如果鼠标点击了回复信息
    {
        message_reply(is_return, msg);
    }
    if (mouse_press(ADMIN_MESSAGE_EXIT_X1, ADMIN_MESSAGE_EXIT_Y1, ADMIN_MESSAGE_EXIT_X2, ADMIN_MESSAGE_EXIT_Y2) == 1) // 如果鼠标点击了退出按钮
    {
        *is_return = 1;
    }
}

// 绘制消息背景
void message_display_draw_bg(int is_announcement)
{
    setwritemode(XOR_PUT);
    setfillstyle(LTBKSLASH_FILL, MY_GREEN); // 设置填充样式为实心
    bar(0, 0, 640, 480);                    // 清除整个屏幕

    setwritemode(COPY_PUT);
    setfillstyle(SOLID_FILL, MY_CREAM); // 设置填充样式为实心
    bar(100, 0, 540, 480);            // 绘制矩形框

    setcolor(MY_GREEN);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH); // 设置线条样式为实线，宽度为1
    line(120, 70, 450, 70); // 绘制直线

    setcolor(MY_BLACK);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1); // 设置字体样式和方向
    outtextxy(120, 10, "TOPIC");
    outtextxy(120, 80, "FROM");
    outtextxy(350, 80, "TIME");

    clear_exit(ADMIN_MESSAGE_EXIT_X1, ADMIN_MESSAGE_EXIT_Y1, ADMIN_MESSAGE_EXIT_X2, ADMIN_MESSAGE_EXIT_Y2); // 绘制退出按钮

    if (is_announcement == 0) { // 如果是公告
        bar(ADMIN_MESSAGE_REPLY_X1, ADMIN_MESSAGE_REPLY_Y1, ADMIN_MESSAGE_REPLY_X2, ADMIN_MESSAGE_REPLY_Y2);        // 绘制回复按钮
        puthz(ADMIN_MESSAGE_REPLY_X1 + 10, ADMIN_MESSAGE_REPLY_Y1 + 7, "回复信息", 20, 20, MY_WHITE); // 绘制回复按钮文字
    }
}

void message_draw_reply_bg(MESSAGE *prev_msg)
{
    char buffer[70];
    
    setwritemode(XOR_PUT);
    setfillstyle(LTBKSLASH_FILL, MY_GREEN); // 设置填充样式为实心
    bar(0, 0, 640, 480);                    // 清除整个屏幕

    setwritemode(COPY_PUT);
    setfillstyle(SOLID_FILL, MY_CREAM); // 设置填充样式为实心
    bar(100, 0, 540, 480);              // 绘制矩形框

    setcolor(MY_GREEN);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH); // 设置线条样式为实线，宽度为1
    line(120, 70, 450, 70);                  // 绘制直线

    setcolor(MY_BLACK);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1); // 设置字体样式和方向
    outtextxy(120, 10, "TOPIC");
    sprintf(buffer, "回复: %s", prev_msg->sender_username);          // 将消息ID转换为字符串
    message_topic_display(120, 30, 400, buffer, MY_WHITE, 24, 3, 0); // 显示消息的主题
    outtextxy(120, 80, "FROM");
    sprintf(buffer, "来自: %s", prev_msg->receiver_username);        // 将消息ID转换为字符串
    message_text_display(160, 80, 400, buffer, MY_WHITE); // 显示消息的主题
    outtextxy(350, 80, "TIME");
    get_approx_time(buffer); // 将消息ID转换为字符串
    message_text_display(390, 80, 400, buffer, MY_WHITE); // 显示消息的主题

    clear_exit(ADMIN_MESSAGE_EXIT_X1, ADMIN_MESSAGE_EXIT_Y1, ADMIN_MESSAGE_EXIT_X2, ADMIN_MESSAGE_EXIT_Y2); // 绘制退出按钮
}
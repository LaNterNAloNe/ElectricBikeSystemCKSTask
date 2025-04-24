#include "MESSAGE.H"

/*************************************************************
MESSAGE:用户与管理员产生交互的功能模块
RETURN:返回值统一为：（1）执行成功返回1；（2）执行失败（含各种原因）返回0
*************************************************************/

void message_display(MESSAGE *msg)
{
    int tag = ACTIVE_ADMIN_NULL; // 定义标签变量
    int is_return = 0;
    int mouse_flag;
    char buffer1[10];
    char buffer2[10];
    ADMIN_BUTTONS btn[2];                     // 定义按钮变量
    define_admin_buttons(btn, ADMIN_MESSAGE_DISPLAY); // 定义按钮
    if (msg->message_type != PRIVATE_MESSAGE)
    {
        memset(&btn[1], '\0', sizeof(btn[1])); // 清空按钮变量
    }

    clrmous(MouseX, MouseY); // 清除鼠标
    message_display_draw_bg();

    if (msg == NULL)
    {
        message_topic_display(120, 35, 400, "信息错误", MY_RED, 24, 3, 0); // 显示消息的主题
    }
    else
    {
        message_topic_display(120, 35, 400, msg->title, MY_BLACK, 24, 3, 0); // 显示消息的主题
        message_text_display(160, 80, 400, msg->sender_username, MY_BLACK);  // 显示消息的发送者
        ltoa(msg->time, buffer1, 10);
        sprintf(buffer2, "%.4s.%.2s.%.2s", buffer1, buffer1 + 4, buffer1 + 6);
        message_text_display(390, 80, 400, buffer2, MY_BLACK);         // 显示消息的发时间
        message_text_display(120, 110, 400, msg->message, MY_BLACK);         // 显示消息的内容
    }
    
    while (is_return == 0)
    {
        newmouse_data(&MouseX, &MouseY, &press, &mouse_flag);

        admin_flush_buttons(&tag, 3, btn); // 刷新按钮
        message_handle_click_event(&is_return, msg); // 处理点击事件

        newmouse(&MouseX, &MouseY, &press, &mouse_flag);
    }
    drawgraph_admin_menu();
    drawgraph_admin_message_center();
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
        outtextxy(_x + 300, _y + 4 + _interval * _listed_item, msg.sender_username);                      // 显示用户名
        if (msg.is_read == 1) { // 如果消息已读，则显示已读
            puthz(_x + 420, _y + _interval * _listed_item, "已读", 16, 16, MY_WHITE); // 显示已读
        } else { // 如果消息未读，则显示未读
            puthz(_x + 420, _y + _interval * _listed_item, "未读", 16, 16, MY_RED); // 显示未读
        }
    }
    else if (list_sequence == DESCENDING)
    {
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);                                                                    // 设置字体样式和方向
        message_topic_display(_x, _y + _interval * (_max - _listed_item - 1), 200, msg.title, MY_WHITE, 16, 1, 1);   // 显示消息的主题
        outtextxy(_x + 300, _y + 4 + _interval * (_max - _listed_item - 1), msg.sender_username);                        // 显示用户名
        if (msg.is_read == 1) { // 如果消息已读，则显示已读
            puthz(_x + 420, _y + _interval * (_max - _listed_item - 1), "已读", 16, 16, MY_WHITE); // 显示已读
        } else { // 如果消息未读，则显示未读
            puthz(_x + 420, _y + _interval * (_max - _listed_item - 1), "未读", 16, 16, MY_RED); // 显示未读
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

int message_admin_quick_message(LINKLIST *LIST, long _sender_id, long _receiver_id, int _message_type, int _quick_type)
{
    FILE *fp; // 定义文件指针
    MESSAGE msg; // 定义消息结构体变量
    int pos = -1;
    char buffer[20];
    char apply_time[20];
    char conduct_time[20];
    char anual_check[20];
    LINKLIST_NODE *node;
    EBIKE_INFO ebike_info; // 定义电动车信息结构体变量

    ltoa(_receiver_id, buffer, 10); // 将接收者ID转换为字符串
    
    /* 文件信息读取 */
    if (_quick_type == QUICK_REGISTER) // 如果是快速注册
        fp = fopen("DATA\\REGISTER.DAT", "rb"); // 打开注册信息文件，以二进制读取方式打开
    else if (_quick_type == QUICK_LICENSE) // 如果是快速注册
        fp = fopen("DATA\\LICENSE.DAT", "rb"); // 打开注册信息文件，以二进制读取方式打开
    else if (_quick_type == QUICK_ANUAL) // 如果是快速注册
        fp = fopen("DATA\\ANUAL.DAT", "rb"); // 打开注册信息文件，以二进制读取方式打开
    else if (_quick_type == QUICK_BROKEN) // 如果是快速注册
        fp = fopen("DATA\\BROKEN.DAT", "rb"); // 打开注册信息文件，以二进制读取方式打开
    else if (_quick_type == QUICK_VIOLA) // 如果是快速注册
        fp = fopen("DATA\\VIOLA.DAT", "rb"); // 打开注册信息文件，以二进制读取方式打开

    if (fp == NULL)
    { // 如果打开文件失败，返回0
        perror("message_admin_quick_message: file-pointer cannot open file\n");
        return 0;
    }
    pos = find_file_info(fp, "ebike_manage", buffer, "id"); // 获取文件信息
    if (pos == -1)
    { // 如果未找到文件信息，返回0
        perror("message_admin_quick_message: file-pointer cannot find file info\n");
        fclose(fp);
        return 0;
    }
    fseek(fp, pos, SEEK_SET);                      // 将文件指针移动到文件信息的位置
    fread(&ebike_info, sizeof(EBIKE_INFO), 1, fp); // 读取电动车信息
    fclose(fp);                                    // 关闭文件
    // 获取申请时间和操作时间
    ltoa(ebike_info.apply_time, buffer, 10);
    sprintf(apply_time, "%0.4s.%0.2s.%0.2s", buffer, buffer + 4, buffer + 6); // 将申请时间转换为字符串
    ltoa(ebike_info.conduct_time, buffer, 10);
    sprintf(conduct_time, "%0.4s.%0.2s.%0.2s", buffer, buffer + 4, buffer + 6); // 将操作时间转换为字符串

    /* 链表信息读取 */
    ltoa(_receiver_id, buffer, 10); // 将接受者ID转换为字符串
    pos = linklist_find_data(LIST, buffer, "id");
    if (pos == -1)
    { // 如果未找到接收者ID，返回0
        perror("message_admin_quick_message: linklist cannot find receiver id\n");
        return 0;
    }

    linklist_get_to_node(LIST, pos, &node); // 获取接收者信息

    msg.receiver_id = _receiver_id; // 设置消息的接收者ID
    strcpy(msg.receiver_username, node->USER_DATA.usrn); // 设置消息的接收者用户名
    msg.sender_id = _sender_id; // 设置消息的发送者ID
    strcpy(msg.sender_username, "Admin"); // 设置消息的发送者用户名
    msg.time = get_approx_time(NULL); // 设置消息的发送者ID
    msg.is_read = 0; // 设置消息的发送者ID
    msg.is_replied = 0; // 设置消息的发送者ID
    msg.message_type = ANNOUNCEMENT; // 设置消息的发送者ID

    if (_quick_type == QUICK_REGISTER) {
        strcpy(msg.title, "您的电动车已成功注册！"); // 设置消息的标题
        sprintf(msg.message, "您的电动车已成功注册！注册信息如下：\n注册人：%s\n车牌号：%s\n申请时间：%s\n处理日期：%s\n提示：如果希望长期在校园内行驶电动车，请尽快办理校园电动车通行证！\n\n祝生活愉快！", 
            node->USER_DATA.rln, node->USER_DATA.ebike_ID, apply_time, conduct_time); // 设置消息的内容
    } else if (_quick_type == QUICK_LICENSE) {
        strcpy(msg.title, "您已成功申请校园通行证！"); // 设置消息的标题
        sprintf(msg.message, "您的电动车校园通行证已成功申请！申请信息如下：\n注册人：%s\n车牌号：%s\n通行证：%s\n申请时间：%s\n处理日期：%s\n提示：成功申请后请及时前往预定的上牌地点完成上牌，预期视为作废！\n\n祝生活愉快！",
                node->USER_DATA.rln, node->USER_DATA.ebike_ID, node->USER_DATA.ebike_license, apply_time, conduct_time); // 设置消息的内容
    } else if (_quick_type == QUICK_ANUAL) {
        ltoa(node->USER_DATA.anual_check, buffer, 10);
        sprintf(anual_check, "%0.4s.%0.2s.%0.2s", buffer, buffer + 4, buffer + 6); // 将操作时间转换为字符串
        strcpy(msg.title, "您的电动车年检已完成！"); // 设置消息的标题
        sprintf(msg.message, "您的电动车年检已完成！年检信息如下：\n注册人：%s\n车牌号：%s\n最新年检日期：%s\n申请时间：%s\n处理日期：%s\n\n\n祝生活愉快！",
                node->USER_DATA.rln, node->USER_DATA.ebike_ID, anual_check, apply_time, conduct_time); // 设置消息的内容
    } else if (_quick_type == QUICK_BROKEN) {
        strcpy(msg.title, "您的电动车报废申请已通过！"); // 设置消息的标题
        sprintf(msg.message, "您的电动车报废申请已通过！报废信息如下：\n注册人：%s\n车牌号：%s\n通行证：%s\n申请时间：%s\n处理日期：%s\n提示：相关电动车数据已从数据库移出，请及时前往校园内检查点完成报废！\n\n祝生活愉快！",
                node->USER_DATA.rln, node->USER_DATA.ebike_ID, node->USER_DATA.ebike_license, apply_time, conduct_time); // 设置消息的内容
    } else if (_quick_type == QUICK_VIOLA) {
        strcpy(msg.title, "您有一项电动车违规行为！"); // 设置消息的标题
        sprintf(msg.message, "您有一项电动车违规行为！违规信息如下：\n注册人：%s\n车牌号：%s\n通行证：%s\n请遵守校园内电动车执行条例！\n\n祝生活愉快！",
                node->USER_DATA.rln, node->USER_DATA.ebike_ID, node->USER_DATA.ebike_license); // 设置消息的内容
    }

    fp = fopen("DATA\\MESSAGE.DAT", "rb+"); // 打开消息文件，以二进制追加方式打开
    if (fp == NULL)
    { // 如果打开文件失败，返回0
        perror("message_admin_quick_message: file-pointer cannot open file, after editting msg\n");
        node == NULL;
        return 0;
    }
    fseek(fp, 0, SEEK_END); // 将文件指针移动到文件末尾
    fwrite(&msg, sizeof(MESSAGE), 1, fp); // 写入消息
    fclose(fp); // 关闭文件
    node == NULL;
    return 1; // 返回1
}

// 获取消息
int message_get(FILE *fp, MESSAGE *msg, char *search_str, char *search_needed)
{
    long i = 0;
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

    while (i <= counts) { // 逐行读取文件内容
        fseek(fp, (counts - i - 1) * sizeof(MESSAGE), SEEK_SET); // 将文件指针回退到上一行的开头
        fread(&msg_buffer, sizeof(MESSAGE), 1, fp);
    
        if (message_is_valid(msg_buffer, search_str, search_needed) == 1)
        { // 检查消息是否有效
            *msg = msg_buffer; // 将有效消息复制到传入的指针指向的内存中
            return 1;
        }

        i++;
    }
    return 0;
}

// 覆盖消息
int message_overwrite(FILE *fp, MESSAGE *msg, char *search_str, char *search_needed)
{
    long i = 0;
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

    while (i <= counts)
    { // 逐行读取文件内容
        if (fseek(fp, (counts - i - 1) * sizeof(MESSAGE), SEEK_SET) == -1) // 将文件指针回退到上一行的开头
        {
            puthz (10, 10, "写入文件失败", 16, 16, MY_RED);
            return 0; // 如果回退失败，返回0
        }
        fread(&msg_buffer, sizeof(MESSAGE), 1, fp);
        
        if (message_is_valid(msg_buffer, search_str, search_needed) == 1) // 检查消息是否为目标信息
        {
            fseek(fp, (counts - i - 1) * sizeof(MESSAGE), SEEK_SET); // 将文件指针回退到上一行的开头
            fwrite (msg, sizeof(MESSAGE), 1, fp); // 将消息写入文件
            return 1;
        }

        i++;
    }
    return 0;
}

// 检查消息是否有效
int message_is_valid(MESSAGE msg, char *search_str, char *search_needed) 
{
    if (!strcmp(search_str, "all") && !strcmp(search_needed, "all") ||

        !strcmp(msg.receiver_username, "all_admin") && 
        (
        !strcmp(search_needed, "admin_all") ||
        msg.sender_id == atol(search_str) && !strcmp(search_needed, "admin_sender_id") ||
        msg.receiver_id == atol(search_str) && !strcmp(search_needed, "admn_receiver_id") ||
        !strcmp(msg.sender_username, search_str) && !strcmp(search_needed, "admin_sender_username") ||
        !strcmp(msg.receiver_username, search_str) && !strcmp(search_needed, "admin_receiver_username") ||
        msg.is_read == atoi(search_str) && !strcmp(search_needed, "admin_is_read") ||
        msg.message_id == atol(search_str) && !strcmp(search_needed, "admin_message_id")
        )
        ||
        msg.receiver_id == atol(search_str) && !strcmp(search_needed, "user_receiver_id")
    )
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
void message_list_click(int _x, int _y, int _max, int _interval, unsigned long _item_id[], unsigned long *_selected_id)
{
    MESSAGE msg; // 用于存储读取的消息
    FILE *fp = NULL;
    char buffer[20];
    int i = 0;                                         // 用于循环计数
    unsigned int previous_selected_id = *_selected_id; // 用于存储上一次选中的消息ID，非静态变量

    for (i = 0; i < _max; i++)
    {

        if (mouse_press(_x + 20, _y + 70 + i * _interval, _x + 500, _y + 70 + (i + 1) * _interval - 1) == 1 &&
            _item_id[i] != 0)
        {
            setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
            bar(_x + 10, _y + 70, _x + 18, _y + 310); // 清理所有高亮
            setfillstyle(SOLID_FILL, MY_YELLOW);
            bar(_x + 10, _y + 70 + i * _interval,
                _x + 18, _y + 70 + i * _interval + _interval / (_interval / 15)); // 生成当前高亮
            *_selected_id = _item_id[i]; // 更新选中的消息ID

            // if (previous_selected_id == *_selected_id && *_selected_id != 0)
            // // 如果选中的消息ID与上一次选中的消息ID相同，并且不为0
            // // 则执行信息显示操作
            // {
            //     fp = fopen("DATA\\MESSAGE.DAT", "rb+"); // 打开消息文件，以二进制读取模式打开
            //     if (fp == NULL)                         // 检查文件指针是否为空
            //     {                                       // 如果为空，输出错误信息并返回
            //         return;                             // 返回
            //     }

            //     ltoa(*_selected_id, buffer, 10);
            //     message_get(fp, &msg, buffer, "message_id"); // 读取选中的消息
            //     message_display(&msg);                       // 显示选中的消息

            //     msg.is_read = 1;                                   // 将消息标记为已读
            //     message_overwrite(fp, &msg, buffer, "message_id"); // 将选中的消息标记为已读
            //     previous_selected_id = 0;
            //     *_selected_id = 0;
            //     fclose(fp);

            //     break;
            // }
        }
    }

    if (previous_selected_id == *_selected_id &&
        mouse_press(_x + 20, _y + 70, _x + 500, _y + 70 + _max * _interval - 1) == -1)
    {
        // 经过上面循环发现没有选中正确的行，_selected_id不会发生改变，因此和previous相同
        // 清理所有高亮
        setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
        bar(_x + 10, _y + 70, _x + 18, _y + 310);
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
#include "LIST.H"

// 列表函数，用于列出相应
void admin_list_info(LINKLIST *LIST, const int max, const int interval, unsigned long item_id[], FILE *fp, char *file_type,
                     char *list_mode, int search_mode, int page_change, int is_clear, char *search_str, char *search_needed)
{
    /* 0.函数介绍 */
    /* 这是一个集成了多种应用场景的列表函数，可以从传入参数的数量来体会到，不同的场景对函数的调用方式有所不同，注意填写传入参数 */
    // LIST是传入的链表
    // max是一个常量，代表最大显示数量，若超出则不显示
    // interval是一个常量，代表列表间隔，即列表的间距
    // item_id是一个数组，用于储存id
    // fp是 某一种 文件指针，你可以在指明file_type的同时，选择不同的文件指针
    // file_type指明文件类型
    // page_change为1，向下列表，为-1，向上列表，为0，不翻页
    // mode为0，查找未处理，为1，查找已处理
    // is_clear为0，不做任何操作，为1，清理列表状态并不做任何操作，为2，清理列表状态并继续列表（重新开始列表）
    //         为3，从记录的start开始扫描重新列表（需搭配page_change=1使用）
    // list_mode为列表依据，"register"为列出注册请求，"license"为列出上牌请求, "broken"为列出报废请求， "violation"为列出违规请求
    // search_mode为搜索模式，0代表搜索未处理，1代表搜索已处理
    // search_str为搜索内容，search_needed为搜索依据

    /* 1.定义变量 */
    int i;
    int listed_item = 0;           // 列出的数量
    static unsigned int start = 0; // 储存当前列表第一个的物理位置
    static unsigned int end = 0;   // 储存当前列表最后一个物理位置
    unsigned int temp_start = 0;
    unsigned int temp_end = 0;          // 储存临时的列表第一个和最后一个位置，或辅助start和end正确赋值
    int counts = 0;                     // 文件长度
    int valid_counts = 0;               // 有效数据量
    int flag = -1;                      // 文件类型
    unsigned int page_count = 0;        // 记录页面数量，值>=0
    static unsigned int page_index = 0; // 记录页码
    char buffer[10];
    EBIKE_INFO ebike_temp;
    USER_LOGIN_DATA user_temp;
    MESSAGE message_temp;
    EBIKE_IN_OUT ebike_in_out_temp;
    LINKLIST_NODE *node = NULL;

    if (debug_mode == 1)
    {
        setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
        bar(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 70 + max * interval,
            ADMIN_INTERFACE_X1 + 320, ADMIN_INTERFACE_Y1 + 90 + max * interval); // 清理列表
        puthz(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 70 + max * interval, "检查一", 16, 16, MY_RED);
    }

    /* 2.判断是否需要清理或刷新列表 */
    switch (is_clear)
    {
    case 1:
        setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
        bar(ADMIN_INTERFACE_X1 + 10, ADMIN_INTERFACE_Y1 + 70,
            ADMIN_INTERFACE_X1 + 500, ADMIN_INTERFACE_Y1 + 70 + max * interval); // 清理列表
        start = 0;
        end = 0;
        page_index = 1;
        node = NULL;
        return;
    case 2:
        setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
        bar(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 70,
            ADMIN_INTERFACE_X1 + 500, ADMIN_INTERFACE_Y1 + 70 + max * interval); // 清理列表
        start = 0;
        end = 0;
        page_index = 1;
        break;
    case 3:
        end = start; // 从start开始扫描重新列表
        break;
    default:
        break;
    }

    /* 3.判断数据类型 */
    if (strcmp(file_type, "ebike_manage") == 0)
    {
        flag = ADMIN_DATABASE_EBIKE_MANAGE;
    }
    else if (strcmp(file_type, "user_data") == 0)
    {
        flag = ADMIN_DATABASE_USER_INFO;
    }
    else if (strcmp(file_type, "ebike_data") == 0)
    {
        flag = ADMIN_DATABASE_EBIKE_INFO;
    }
    else if (strcmp(file_type, "ebike_pass_in_out") == 0)
    {
        flag = ADMIN_DATABASE_EBIKE_PASS_IN_OUT;
    }
    else if (strcmp(file_type, "message") == 0)
    {
        flag = ADMIN_MESSAGE;
    }
    else
    {
        return; // 若指明文件类型错误，则不做任何操作
    }

    if (debug_mode == 1)
        puthz(ADMIN_INTERFACE_X1 + 80, ADMIN_INTERFACE_Y1 + 70 + max * interval, "检查二", 16, 16, MY_RED);

    /* 4.获取文件长度或初始化读取条件 */
    fseek(fp, 0, SEEK_END);
    switch (flag)
    {
        case ADMIN_DATABASE_EBIKE_MANAGE:
            counts = ftell(fp) / sizeof(EBIKE_INFO);
            break;
        case ADMIN_DATABASE_USER_INFO:
            counts = ftell(fp) / sizeof(USER_LOGIN_DATA);
            break;
        case ADMIN_DATABASE_EBIKE_INFO:
            node = LIST->HEAD;
            // 注意start和end的赋值，两个指数都标记一块数据的头部，一般来说start和end的数即指向对应节点序号 - 1
            counts = linklist_get_length(LIST);
            break;
        case ADMIN_DATABASE_EBIKE_PASS_IN_OUT:
            counts = ftell(fp) / sizeof(EBIKE_IN_OUT);
            break;
        case ADMIN_MESSAGE:
            counts = ftell(fp) / sizeof(MESSAGE);
            break;
    }

    // 计算有效数据量 valid_counts
    valid_counts = counts;
    if (flag != ADMIN_DATABASE_EBIKE_INFO)
    {
        if (strcmp(search_str, "\0") != 0)
        {
            valid_counts = 0;
            fseek(fp, 0, SEEK_SET);
            switch (flag)
            {
                case ADMIN_DATABASE_EBIKE_MANAGE:
                {
                    for (i = 0; i < counts; i++)
                    {
                        fread(&ebike_temp, sizeof(EBIKE_INFO), 1, fp);
                        if (list_ebike_manage_is_valid(ebike_temp, list_mode, search_str, search_needed, search_mode))
                        {
                            valid_counts++;
                        }
                    }
                }
                case ADMIN_DATABASE_USER_INFO:
                {
                    for (i = 0; i < counts; i++)
                    {
                        fread(&user_temp, sizeof(USER_LOGIN_DATA), 1, fp);
                        if (list_user_data_is_valid(user_temp, search_str, search_needed))
                        {
                            valid_counts++;
                        }
                    }
                }
                case ADMIN_MESSAGE:
                {
                    for (i = counts - 1; i > 0; i--)
                    {
                        fread(&message_temp, sizeof(MESSAGE), 1, fp);
                        if (message_is_valid(message_temp, search_str, search_needed))
                        {
                            valid_counts++;
                        }
                    }
                }
                case ADMIN_DATABASE_EBIKE_PASS_IN_OUT:
                {
                    for (i = counts - 1; i > 0; i--)
                    {
                        fread(&ebike_in_out_temp, sizeof(EBIKE_IN_OUT), 1, fp);
                        if (list_ebike_in_out_is_valid(ebike_in_out_temp, search_str, search_needed))
                        {
                            valid_counts++;
                        }
                    }
                }
            }
        }
    }
    else if (flag == ADMIN_DATABASE_EBIKE_INFO)
    { // 若为ebike_info文件，则遍历链表
        if (strcmp(search_str, "\0") != 0)
        {
            while (node != NULL)
            {
                if (list_ebike_info_is_valid(node->USER_DATA, search_str, search_needed))
                {
                    valid_counts++;
                }
                node = node->NEXT;
            }
        }
        node = LIST->HEAD; // 重置node指针
    }

    // 计算页面数量时使用 valid_counts
    page_count = valid_counts / max + (valid_counts % max ? 1 : 0);
    if (page_count < 1)
        page_index = 0;

    /* 5.初始化列表记录 */
    for (i = 0; i < max; i++)
    {
        item_id[i] = 0;
    }

    if (debug_mode == 1)
        puthz(ADMIN_INTERFACE_X1 + 140, ADMIN_INTERFACE_Y1 + 70 + max * interval, "检查三", 16, 16, MY_RED);


    /* 6.前置操作完成，正式开始列表 */
    // 收到下翻指令，或改变当前列表状态后从起点开始重新刷新列表 //
    if (valid_counts > 0 && page_change == LIST_PAGEDOWN)
    {

        if (debug_mode == 1)
            puthz(ADMIN_INTERFACE_X1 + 200, ADMIN_INTERFACE_Y1 + 70 + max * interval, "检查四", 16, 16, MY_RED);

        /* 条件判断 */
        if (end >= valid_counts - 1)
        {
            node = NULL;
            return; // 如果end指向结尾的数据，则不做任何操作
        }

        temp_start = end + 1; // 临时储存，先利用临时变量获取下一个可列出数据块的位置，如果没有则不会影响start和end的值
        while (1)
        {
            if (flag == ADMIN_DATABASE_EBIKE_MANAGE)
            {
                fseek(fp, (temp_start) * sizeof(ebike_temp), SEEK_SET); // 读取下一个数据块，此时offset总不为负，返回值一定为0，不用担心越界
                if (!fread(&ebike_temp, sizeof(ebike_temp), 1, fp))     // 读取下一个数据块
                {
                    return; // 到文件末尾都没有发现可列表的，则不执行下翻列表操作
                }
                if (list_ebike_manage_is_valid(ebike_temp, list_mode, search_str, search_needed, search_mode))
                {
                    break; // 下翻查找是一旦读到可以被列出的，则可以执行下翻列表操作
                }
            }
            else if (flag == ADMIN_DATABASE_USER_INFO)
            {
                fseek(fp, (temp_start) * sizeof(user_temp), SEEK_SET); // 先判断接下来是否有可以列出的数据
                if (!fread(&user_temp, sizeof(user_temp), 1, fp))      // 读取下一个数据块
                {
                    return; // 到文件末尾都没有发现可列表的，则不执行下翻列表操作
                }
                if (list_user_data_is_valid(user_temp, search_str, search_needed))
                {
                    break;
                }
            }
            else if (flag == ADMIN_DATABASE_EBIKE_INFO)
            {
                if (node == NULL)
                {
                    return; // 到文件末尾都没有发现可列表的，则不执行下翻列表操作
                }
                if (list_ebike_info_is_valid(node->USER_DATA, search_str, search_needed))
                {
                    break; // 下翻查找是一旦读到可以被列出的，则可以执行下翻列表操作
                }
                node = node->NEXT; // 指针移至下一节点
            }
            else if (flag == ADMIN_MESSAGE)
            {
                /* 信息的读取较为特殊，需要从后往前读取，且认为最后面的是第一个。为不造成冲突，要读取文件时采取即时计算读取位置的方式 */
                fseek(fp, (counts - temp_start) * sizeof(user_temp), SEEK_SET); // 先判断接下来是否有可以列出的数据
                if (!fread(&message_temp, sizeof(message_temp), 1, fp))             // 读取下一个数据块
                {
                    return; // 到文件末尾都没有发现可列表的，则不执行下翻列表操作
                }
                if (message_is_valid(message_temp, search_str, search_needed))
                {
                    break;
                }
            }
            else if (flag == ADMIN_DATABASE_EBIKE_PASS_IN_OUT)
            {
                fseek(fp, (counts - temp_start) * sizeof(ebike_in_out_temp), SEEK_SET); // 先判断接下来是否有可以列出的数据
                if (!fread(&ebike_in_out_temp, sizeof(ebike_in_out_temp), 1, fp))      // 读取下一个数据块
                {
                    return; // 到文件末尾都没有发现可列表的，则不执行下翻列表操作
                }
                if (list_ebike_in_out_is_valid(ebike_in_out_temp, search_str, search_needed))
                {
                    break; // 下翻查找是一旦读到可以被列出的，则可以执行下翻列表操作
                }
            }
            temp_start++; // 如果下翻读取时读到的数据不符条件，则进行下一轮循环
        }

        start = temp_start; // 成功找到可列出的数据，处理变量后进行进一步操作
        end = temp_start;
        temp_end = temp_start;

        if (debug_mode == 1)
            puthz(ADMIN_INTERFACE_X1 + 260, ADMIN_INTERFACE_Y1 + 70 + max * interval, "检查五", 16, 16, MY_RED);

        /* 列表操作 */
        setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
        bar(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 70,
            ADMIN_INTERFACE_X1 + 500, ADMIN_INTERFACE_Y1 + 70 + max * interval); // 清理列表
        list_show_page_index(++page_index, page_count, max, interval);           // 显示页码

        while (listed_item < max)
        {
            if (flag == ADMIN_DATABASE_EBIKE_MANAGE)
            {
                fseek(fp, (temp_end) * sizeof(ebike_temp), SEEK_SET);
                if (!fread(&ebike_temp, sizeof(ebike_temp), 1, fp))
                {
                    temp_end--; // 若读取到文件末尾，则将end指向文件末尾的前一个数据块，防止越界
                    puthz(ADMIN_INTERFACE_X1 + 190, ADMIN_INTERFACE_Y1 + 70 + listed_item * interval, "没有更多数据了哦！", 16, 16, MY_RED);
                    break; // 读取数据，直到达到文件末尾
                }
                if (!list_ebike_manage_is_valid(ebike_temp, list_mode, search_str, search_needed, search_mode))
                {
                    temp_end++;
                    continue; // 如果下翻读取时读到的数据不符条件，则进行下一轮循环
                }

                admin_show_ebike_manage_info(ebike_temp, max, interval, listed_item, list_mode, ASCENDING); // 输出数据
                item_id[listed_item] = ebike_temp.ID;
            }
            else if (flag == ADMIN_DATABASE_USER_INFO)
            {
                fseek(fp, (temp_end) * sizeof(user_temp), SEEK_SET);
                if (!fread(&user_temp, sizeof(user_temp), 1, fp))
                {
                    temp_end--; // 若读取到文件末尾，则将end指向文件末尾的前一个数据块，防止越界
                    puthz(ADMIN_INTERFACE_X1 + 190, ADMIN_INTERFACE_Y1 + 70 + listed_item * interval, "没有更多数据了哦！", 16, 16, MY_RED);
                    break; // 读取数据，直到达到文件末尾
                }
                if (!list_user_data_is_valid(user_temp, search_str, search_needed))
                {
                    temp_end++;
                    continue; // 如果下翻读取时读到的数据不符条件，则进行下一轮循环
                }

                admin_show_user_info(user_temp, max, interval, listed_item, ASCENDING); // 输出数据
                item_id[listed_item] = user_temp.ID;
            }
            else if (flag == ADMIN_DATABASE_EBIKE_INFO)
            {
                linklist_get_to_node(LIST, temp_end + 1, &node); // 将指针指向对应节点
                if (node == NULL)
                {
                    puthz(ADMIN_INTERFACE_X1 + 190, ADMIN_INTERFACE_Y1 + 70 + listed_item * interval, "没有更多数据了哦！", 16, 16, MY_RED);
                    break; // 到文件末尾都没有发现可列表的，则不执行下翻列表操作
                }
                if (!list_ebike_info_is_valid(node->USER_DATA, search_str, search_needed))
                {
                    temp_end++;
                    continue; // 如果下翻读取时读到的数据不符条件，则进行下一轮循环
                }

                admin_show_ebike_info(node->USER_DATA, interval, max, listed_item, ASCENDING); // 输出数据
                item_id[listed_item] = node->USER_DATA.ID;                                     // 记录ID
                node = node->NEXT;                                                             // 指针移至下一节点
            }
            else if (flag == ADMIN_MESSAGE)
            {
                fseek(fp, (counts - temp_end) * sizeof(message_temp), SEEK_SET); // 先判断接下来是否有可以列出的数据
                if (!fread(&message_temp, sizeof(message_temp), 1, fp))             // 读取下一个数据块
                {
                    puthz(ADMIN_INTERFACE_X1 + 190, ADMIN_INTERFACE_Y1 + 70 + listed_item * interval, "没有更多数据了哦！", 16, 16, MY_RED);
                    break; // 到文件末尾都没有发现可列表的，则不执行下翻列表操作
                }
                if (!message_is_valid(message_temp, search_str, search_needed))
                {
                    temp_end++;
                    continue; // 如果下翻读取时读到的数据不符条件，则进行下一轮循环
                }

                message_list(message_temp, ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 70, max, interval, listed_item, ASCENDING); // 输出数据
                item_id[listed_item] = message_temp.message_id; // 记录ID
            }
            else if (flag == ADMIN_DATABASE_EBIKE_PASS_IN_OUT)
            {
                fseek(fp, (counts - temp_end) * sizeof(ebike_in_out_temp), SEEK_SET); // 先判断接下来是否有可以列出的数据
                if (!fread(&ebike_in_out_temp, sizeof(ebike_in_out_temp), 1, fp))      // 读取下一个数据块
                {
                    puthz(ADMIN_INTERFACE_X1 + 190, ADMIN_INTERFACE_Y1 + 70 + listed_item * interval, "没有更多数据了哦！", 16, 16, MY_RED);
                    break; // 到文件末尾都没有发现可列表的，则不执行下翻列表操作  
                }
                if (!list_ebike_in_out_is_valid(ebike_in_out_temp, search_str, search_needed))
                {
                    temp_end++;
                    continue; // 如果下翻读取时读到的数据不符条件，则进行下一轮循环
                }

                admin_show_ebike_in_out(ebike_in_out_temp, max, interval, listed_item, ASCENDING); // 输出数据
                item_id[listed_item] = ebike_in_out_temp.apply_id; // 记录ID
            }

            end = temp_end; // 成功列出一个数据，更新end
            listed_item++;
            temp_end++;
        }
        node = NULL; // 防止野指针
        return;
    }
    // 收到上翻指令 //
    else if (valid_counts > 0 && page_change == LIST_PAGEUP)
    {

        if (debug_mode == 1)
            puthz(ADMIN_INTERFACE_X1 + 200, ADMIN_INTERFACE_Y1 + 70 + max * interval, "检查四", 16, 16, MY_RED);

        /*条件判断*/
        if (start <= 0)
        {
            return; // 如果start指向开头的数据，则不做任何操作
        }
        temp_start = start - 1; // 下面先自减
        temp_end = start - 1;

        while (1)
        { // 当能进入这个循环，说明列表上页有可列出数据
            if (flag == ADMIN_DATABASE_EBIKE_MANAGE)
            {
                if (fseek(fp, (temp_start) * sizeof(ebike_temp), SEEK_SET))
                {
                    return; // 到文件开头都没有发现可列表的，则不执行上翻列表操作
                }
                fread(&ebike_temp, sizeof(ebike_temp), 1, fp); // 读取上一个数据块

                if (list_ebike_manage_is_valid(ebike_temp, list_mode, search_str, search_needed, search_mode))
                {
                    break; // 上翻查找到一个可列出数据，则可以上翻
                }
            }
            else if (flag == ADMIN_DATABASE_USER_INFO)
            {
                if (fseek(fp, (temp_start) * sizeof(user_temp), SEEK_SET)) // 读取上一个数据块，当文件指针尝试移动到负数时，fseek会返回非零数
                {
                    return; // 到文件开头都没有发现可列表的，则不执行上翻列表操作
                }
                fread(&user_temp, sizeof(user_temp), 1, fp); // 读取上一个数据块

                if (list_user_data_is_valid(user_temp, search_str, search_needed))
                {
                    break;
                }
            }
            else if (flag == ADMIN_DATABASE_EBIKE_INFO)
            {
                if (node == NULL) // 如果node指针为NULL，则说明已经到达链表头部，不能再向前移动
                {
                    return; // 到文件开头都没有发现可列表的，则不执行上翻列表操作
                }
                if (list_ebike_info_is_valid(node->USER_DATA, search_str, search_needed))
                {
                    break; // 上翻查找到一个可列出数据，则可以上翻
                }
                node = node->PREVIOUS; // 指针移至上一节点
            }
            else if (flag == ADMIN_MESSAGE)
            {
                if (fseek(fp, (counts - temp_start) * sizeof(message_temp), SEEK_SET)) // 读取上一个数据块，当文件指针尝试移动到负数时，fseek会返回非零数
                {
                    return; // 到文件开头都没有发现可列表的，则不执行上翻列表操作 
                }
                fread(&message_temp, sizeof(message_temp), 1, fp); // 读取上一个数据块

                if (message_is_valid(message_temp, search_str, search_needed))
                {
                    break; // 上翻查找到一个可列出数据，则可以上翻
                }
            }
            else if (flag == ADMIN_DATABASE_EBIKE_PASS_IN_OUT)
            {
                if (fseek(fp, (counts - temp_start) * sizeof(ebike_in_out_temp), SEEK_SET)) // 读取上一个数据块，当文件指针尝试移动到负数时，fseek会返回非零数
                {
                    return; // 到文件开头都没有发现可列表的，则不执行上翻列表操作
                }
                fread(&ebike_in_out_temp, sizeof(ebike_in_out_temp), 1, fp); // 读取上一个数据块

                if (list_ebike_in_out_is_valid(ebike_in_out_temp, search_str, search_needed))
                {
                    break; // 上翻查找到一个可列出数据，则可以上翻
                }
            }
            temp_end = --temp_start;
        }
        start = temp_start; // 查找到首个可以读取的数据，将实际的标记指向该数据
        end = temp_end;

        // 此处 temp_start 和 temp_end 都应为 start - 1 或更小//
        if (debug_mode == 1)
            puthz(ADMIN_INTERFACE_X1 + 260, ADMIN_INTERFACE_Y1 + 70 + max * interval, "检查五", 16, 16, MY_RED);

        /*列表操作*/
        setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
        bar(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 70,
            ADMIN_INTERFACE_X1 + 500, ADMIN_INTERFACE_Y1 + 70 + max * interval); // 清理列表
        list_show_page_index(--page_index, page_count, max, interval);           // 更新页面索引

        while (listed_item < max)
        { // 由于此时是从后往前读取数据，因此是从下往上列表
            if (flag == ADMIN_DATABASE_EBIKE_MANAGE)
            {
                fseek(fp, (temp_start) * sizeof(ebike_temp), SEEK_SET);
                fread(&ebike_temp, sizeof(ebike_temp), 1, fp); // 读取数据，直到查找到未被处理的注册请求
                if (!list_ebike_manage_is_valid(ebike_temp, list_mode, search_str, search_needed, search_mode))
                {
                    temp_start--;
                    continue; // 如果下翻读取时读到的数据不符条件，则进行下一轮循环
                }

                admin_show_ebike_manage_info(ebike_temp, max, interval, listed_item, list_mode, DESCENDING); // 输出数据
                item_id[7 - listed_item] = ebike_temp.ID;                                                    // 记录ID
            }
            else if (flag == ADMIN_DATABASE_USER_INFO)
            {
                fseek(fp, (temp_start) * sizeof(user_temp), SEEK_SET);
                fread(&user_temp, sizeof(user_temp), 1, fp);
                if (!list_user_data_is_valid(user_temp, search_str, search_needed))
                {
                    temp_start--;
                    continue; // 如果下翻读取时读到的数据不符条件，则进行下一轮循环
                }

                admin_show_user_info(user_temp, max, interval, listed_item, DESCENDING); // 输出数据
                item_id[max - 1 - listed_item] = user_temp.ID;                           // 记录ID
            }
            else if (flag == ADMIN_DATABASE_EBIKE_INFO)
            {
                linklist_get_to_node(LIST, temp_start + 1, &node); // 将指针指向对应节点
                if (node == NULL)                                 // 如果node指针为NULL，则说明已经到达链表头部，不能再向前移动
                {
                    puthz(ADMIN_INTERFACE_X1 + 190, ADMIN_INTERFACE_Y1 + 70 + listed_item * interval, "没有更多数据了哦！", 16, 16, MY_RED);
                    break; // 到文件开头都没有发现可列表的，则不执行上翻列表操作
                }
                if (!list_ebike_info_is_valid(node->USER_DATA, search_str, search_needed))
                {
                    temp_start--;
                    continue; // 如果下翻读取时读到的数据不符条件，则进行下一轮循环
                }

                admin_show_ebike_info(node->USER_DATA, max, interval, listed_item, DESCENDING); // 输出数据
                item_id[7 - listed_item] = node->USER_DATA.ID;                                  // 记录ID
                node = node->PREVIOUS;                                                          // 指针移至上一节点
            }
            else if (flag == ADMIN_MESSAGE)
            {
                fseek(fp, (counts - temp_start) * sizeof(message_temp), SEEK_SET); // 读取上一个数据块，当文件指针尝试移动到负数时，fseek会返回非零数
                fread(&message_temp, sizeof(message_temp), 1, fp);                     // 读取上一个数据块
                if (!message_is_valid(message_temp, search_str, search_needed))
                {
                    temp_start--;
                    continue; // 如果下翻读取时读到的数据不符条件，则进行下一轮循环
                }

                message_list(message_temp, ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 70, max, interval, listed_item, DESCENDING); // 输出数据
                item_id[7 - listed_item] = message_temp.message_id;                                                                   // 记录ID
            }
            else if (flag == ADMIN_DATABASE_EBIKE_PASS_IN_OUT)
            {
                fseek(fp, (counts - temp_start) * sizeof(ebike_in_out_temp), SEEK_SET); // 读取上一个数据块，当文件指针尝试移动到负数时，fseek会返回非零数
                fread(&ebike_in_out_temp, sizeof(ebike_in_out_temp), 1, fp);                     // 读取上一个数据块
                if (!list_ebike_in_out_is_valid(ebike_in_out_temp, search_str, search_needed))
                {
                    temp_start--;
                    continue; // 如果下
                }

                admin_show_ebike_in_out(ebike_in_out_temp,  max, interval, listed_item, DESCENDING); // 输出数据
                item_id[7 - listed_item] = ebike_in_out_temp.apply_id;
            }

            start = temp_start;
            listed_item++;
            if (start == 0)
                break;    // 防止start越界
            temp_start--; // start在后面条件自减，防止start越界
        }
        node = NULL; // 防止野指针
        return;
    }
    // 不翻页，输出原内容（严格要求是原内容，如果操作后减少可列数据数目，请传入LIST_PAGEUP和LIST_FLUSH） //
    else if (valid_counts > 0 && page_change == LIST_STAY)
    {

        if (debug_mode == 1)
            puthz(ADMIN_INTERFACE_X1 + 200, ADMIN_INTERFACE_Y1 + 70 + max * interval, "检查四", 16, 16, MY_RED);

        /*条件判断*/
        end = start; // end不能赋为负数，因为end为无符号整形数
        temp_end = start;
        temp_start = start;
        while (1)
        {
            if (flag == ADMIN_DATABASE_EBIKE_MANAGE)
            {
                fseek(fp, (temp_start) * sizeof(ebike_temp), SEEK_SET); // 读取下一个数据块，此时offset总不为负，返回值一定为0，不用担心越界
                if (!fread(&ebike_temp, sizeof(ebike_temp), 1, fp))     // 读取下一个数据块
                {
                    return; // 到文件末尾都没有发现可列表的，则不执行下翻列表操作
                }
                if (list_ebike_manage_is_valid(ebike_temp, list_mode, search_str, search_needed, search_mode))
                {
                    break; // 下翻查找是一旦读到可以被列出的，则可以执行下翻列表操作
                }
            }
            else if (flag == ADMIN_DATABASE_USER_INFO)
            {
                fseek(fp, (temp_start) * sizeof(user_temp), SEEK_SET); // 先判断接下来是否有可以列出的数据
                if (!fread(&user_temp, sizeof(user_temp), 1, fp))      // 读取下一个数据块
                {
                    return; // 到文件末尾都没有发现可列表的，则不执行下翻列表操作
                }
                if (list_user_data_is_valid(user_temp, search_str, search_needed))
                {
                    break;
                }
            }
            else if (flag == ADMIN_DATABASE_EBIKE_INFO)
            {
                if (node == NULL)
                {
                    return; // 到文件末尾都没有发现可列表的，则不执行下翻列表操作
                }
                if (list_ebike_info_is_valid(node->USER_DATA, search_str, search_needed))
                {
                    break; // 下翻查找是一旦读到可以被列出的，则可以执行下翻列表操作
                }
                node = node->NEXT; // 指针移至下一节点
            }
            else if (flag == ADMIN_MESSAGE)
            {
                /* 信息的读取较为特殊，需要从后往前读取，且认为最后面的是第一个。为不造成冲突，要读取文件时采取即时计算读取位置的方式 */
                fseek(fp, (counts - temp_start - 1) * sizeof(user_temp), SEEK_SET); // 先判断接下来是否有可以列出的数据
                if (!fread(&message_temp, sizeof(message_temp), 1, fp))             // 读取下一个数据块
                {
                    return; // 到文件末尾都没有发现可列表的，则不执行下翻列表操作
                }
                if (message_is_valid(message_temp, search_str, search_needed))
                {
                    break;
                }
            }
            else if (flag == ADMIN_DATABASE_EBIKE_PASS_IN_OUT)
            {
                fseek(fp, (counts - temp_start - 1) * sizeof(ebike_in_out_temp), SEEK_SET); // 先判断接下来是否有可以列出的数据
                if (!fread(&ebike_in_out_temp, sizeof(ebike_in_out_temp), 1, fp))             // 读取下一个数据块
                {
                    return; // 到文件末尾都没有发现可列表的，则不执行下翻列表操作
                }
                if (list_ebike_in_out_is_valid(ebike_in_out_temp, search_str, search_needed))
                {
                    break; // 下翻查找是一旦读到可以被列出的，则可以执行下翻列表操作
                }
            }
            temp_start++; // 如果下翻读取时读到的数据不符条件，则进行下一轮循环
        }
        start = temp_start; // 成功找到可列出的数据，处理变量后进行进一步操作
        end = temp_start;

        if (debug_mode == 1)
            puthz(ADMIN_INTERFACE_X1 + 260, ADMIN_INTERFACE_Y1 + 70 + max * interval, "检查五", 16, 16, MY_RED);

        /*列表操作*/
        temp_end = start; // 将temp_end赋值为start，后续操作使用temp_end来读取数据
        setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
        bar(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 70,
            ADMIN_INTERFACE_X1 + 500, ADMIN_INTERFACE_Y1 + 70 + max * interval); // 清理列表
        list_show_page_index(page_index, page_count, max, interval);             // 显示页码

        while (listed_item < max)
        {
            if (flag == ADMIN_DATABASE_EBIKE_MANAGE)
            {
                fseek(fp, (temp_end) * sizeof(ebike_temp), SEEK_SET);
                if (!fread(&ebike_temp, sizeof(ebike_temp), 1, fp))
                {
                    temp_end--; // 若读取到文件末尾，则将end指向文件末尾的前一个数据块，防止越界
                    puthz(ADMIN_INTERFACE_X1 + 190, ADMIN_INTERFACE_Y1 + 70 + listed_item * interval, "没有更多数据了哦！", 16, 16, MY_RED);
                    return; // 读取数据，直到达到文件末尾
                } // 读取数据，直到查找到八个可列出数据

                if (!list_ebike_manage_is_valid(ebike_temp, list_mode, search_str, search_needed, search_mode))
                {
                    temp_end++; // end指数+1
                    continue;   // 如果下翻读取时读到的数据不符条件，则进行下一轮循环
                }

                admin_show_ebike_manage_info(ebike_temp, max, interval, listed_item, list_mode, ASCENDING); // 输出数据

                item_id[listed_item] = ebike_temp.ID;
            }
            else if (flag == ADMIN_DATABASE_USER_INFO)
            {
                fseek(fp, (temp_end) * sizeof(user_temp), SEEK_SET);
                // 此处不要传入start + listed_item，因为listed_item可能一直不会改变，导致读取的数据不会改变，进入死循环 2025.4.8
                if (!fread(&user_temp, sizeof(user_temp), 1, fp))
                {
                    temp_end--; // 若读取到文件末尾，则将end指向文件末尾的前一个数据块，防止越界
                    puthz(ADMIN_INTERFACE_X1 + 190, ADMIN_INTERFACE_Y1 + 70 + listed_item * interval, "没有更多数据了哦！", 16, 16, MY_RED);
                    return;
                } // 读取数据，直到查找到八个可列出数据

                if (!list_user_data_is_valid(user_temp, search_str, search_needed))
                {
                    temp_end++; // end指数+1
                    continue;   // 如果下翻读取时读到的数据不符条件，则进行下一轮循环
                }

                admin_show_user_info(user_temp, max, interval, listed_item, ASCENDING); // 输出数据

                item_id[listed_item] = user_temp.ID;
            }
            else if (flag == ADMIN_DATABASE_EBIKE_INFO)
            {
                linklist_get_to_node(LIST, temp_end + 1, &node); // 将指针指向对应节点
                if (node == NULL)                               // 如果node指针为NULL，则说明已经到达链表头部，不能再向前移动
                {
                    puthz(ADMIN_INTERFACE_X1 + 190, ADMIN_INTERFACE_Y1 + 70 + listed_item * interval, "没有更多数据了哦！", 16, 16, MY_RED);
                    return; // 到文件末尾都没有发现可列表的，则不执行下翻列表操作
                }
                if (!list_ebike_info_is_valid(node->USER_DATA, search_str, search_needed))
                {
                    temp_end++; // end指数+1
                    continue;   // 如果下翻读取时读到的数据不符条件，则进行下一轮循环
                }

                admin_show_ebike_info(node->USER_DATA, max, interval, listed_item, ASCENDING); // 输出数据

                item_id[listed_item] = node->USER_DATA.ID; // 记录ID
                node = node->NEXT;                         // 指针移至下一节点
            }
            else if (flag == ADMIN_MESSAGE)
            {
                fseek(fp, (counts - temp_end - 1) * sizeof(message_temp), SEEK_SET); // 读取上一个数据块，当文件指针尝试移动到负数时，fseek会返回非零数
                if (!fread(&message_temp, sizeof(message_temp), 1, fp))             // 读取上一个数据块
                {
                    temp_end--; // 若读取到文件末尾，则将end指向文件末尾的前一个数据块，防止越界
                }
                if (!message_is_valid(message_temp, search_str, search_needed))
                {
                    temp_end++; // end指数+1
                    continue;   // 如果下翻读取时读到的数据不符条件，则进行下一轮循环
                }
                message_list(message_temp, ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 70, max, interval, listed_item, ASCENDING); // 输出数据
                item_id[listed_item] = message_temp.message_id;                                                                   // 记录ID
            }
            else if (flag == ADMIN_DATABASE_EBIKE_PASS_IN_OUT)
            {
                fseek(fp, (counts - temp_end - 1) * sizeof(ebike_in_out_temp), SEEK_SET); // 读取上一个数据块，当文件指针尝试移动到负数时，fseek会返回非零数
                if (!fread(&ebike_in_out_temp, sizeof(ebike_in_out_temp), 1, fp))             // 读取上一个数据块
                {
                    temp_end--; // 若读取到文件末尾，则将end指向文件末尾的前一个数据块，防止越界
                }
                if (!list_ebike_in_out_is_valid(ebike_in_out_temp, search_str, search_needed))
                {
                    temp_end++; // end指数+1
                    continue;   // 如果下翻读取时读到的数据不符条件，则进行下一轮循环
                }

                admin_show_ebike_in_out(ebike_in_out_temp, max, interval, listed_item, ASCENDING); // 输出数据
                item_id[listed_item] = ebike_in_out_temp.apply_id; // 记录ID
            }

            end = temp_end;
            listed_item++;
            temp_end++; // 将end指向读取的数据的头部
        }
        node = NULL; // 防止野指针
        return;
    }
    else
    {
        list_show_page_index(0, 0, max, interval);
        puthz(ADMIN_INTERFACE_X1 + 140, ADMIN_INTERFACE_Y1 + 70, "未找到对应数据或传入参数错误", 16, 16, MY_RED);
        node = NULL; // 防止野指针
        return;
    }

    // 到函数末尾都还没返回，则出现异常，输出异常信息
    list_show_page_index(0, 0, max, interval);
    puthz(ADMIN_INTERFACE_X1 + 120, ADMIN_INTERFACE_Y1 + 70, "函数执行异常", 16, 16, MY_RED);
    node = NULL; // 防止野指针
}

/// 输出数据函数
void admin_show_ebike_manage_info(struct _EBIKE_INFO_ TEMP, const int max, const int interval, int listed_item, char *list_mode, int list_sequence)
{
    char buffer[50];
    itoa(TEMP.ID, buffer, 10); // 将ID转换为字符串

    if (list_sequence == ASCENDING)
    {
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

        if (strcmp(list_mode, "register") == 0 || strcmp(list_mode, "license") || strcmp(list_mode, "anual"))
        {
            puthz(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 70 + listed_item * 20, TEMP.rln, 16, 16, MY_WHITE); // 输出姓名
            outtextxy(ADMIN_INTERFACE_X1 + 100, ADMIN_INTERFACE_Y1 + 70 + listed_item * interval, buffer);          // 输出ID
            outtextxy(ADMIN_INTERFACE_X1 + 200, ADMIN_INTERFACE_Y1 + 70 + listed_item * interval, TEMP.ebike_ID);   // 输出电动车车牌号
        }
        else if (strcmp(list_mode, "broken") == 0 || strcmp(list_mode, "violation") == 0)
        {
            outtextxy(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 70 + listed_item * interval, buffer);         // 输出ID
            outtextxy(ADMIN_INTERFACE_X1 + 100, ADMIN_INTERFACE_Y1 + 70 + listed_item * interval, TEMP.ebike_ID); // 输出电动车车牌号
            outtextxy(ADMIN_INTERFACE_X1 + 200, ADMIN_INTERFACE_Y1 + 70 + listed_item * interval, TEMP.location); // 输出地址
        }

        outtextxy(ADMIN_INTERFACE_X1 + 300, ADMIN_INTERFACE_Y1 + 70 + listed_item * interval, buffer); // 输出请求时间

        if (TEMP.conduct_time == -1)
        { // 输出处理状态
            puthz(ADMIN_INTERFACE_X1 + 400, ADMIN_INTERFACE_Y1 + 70 + listed_item * interval, "未处理", 16, 16, MY_RED);
        }
        else
        {
            puthz(ADMIN_INTERFACE_X1 + 400, ADMIN_INTERFACE_Y1 + 70 + listed_item * interval, "已处理", 16, 16, MY_GREEN);
        }
    }
    else if (list_sequence == DESCENDING)
    {
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

        if (strcmp(list_mode, "register") == 0 || strcmp(list_mode, "license") == 0 || strcmp(list_mode, "anual"))
        {
            puthz(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 310 - listed_item * interval, TEMP.rln, 16, 16, MY_WHITE); // 输出姓名
            outtextxy(ADMIN_INTERFACE_X1 + 100, ADMIN_INTERFACE_Y1 + 310 - listed_item * interval, buffer);                // 输出ID
            outtextxy(ADMIN_INTERFACE_X1 + 200, ADMIN_INTERFACE_Y1 + 310 - listed_item * interval, TEMP.ebike_ID);
        }
        else if (strcmp(list_mode, "broken") == 0 || strcmp(list_mode, "violation") == 0)
        {
            outtextxy(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 310 - listed_item * interval, buffer);         // 输出ID
            outtextxy(ADMIN_INTERFACE_X1 + 200, ADMIN_INTERFACE_Y1 + 310 - listed_item * interval, TEMP.ebike_ID); // 输出电动车车牌号
            outtextxy(ADMIN_INTERFACE_X1 + 300, ADMIN_INTERFACE_Y1 + 310 - listed_item * interval, TEMP.location); // 输出地址
        }

        outtextxy(ADMIN_INTERFACE_X1 + 300, ADMIN_INTERFACE_Y1 + 310 - listed_item * interval, buffer); // 输出请求时间

        if (TEMP.conduct_time == -1)
        { // 输出处理状态
            puthz(ADMIN_INTERFACE_X1 + 400, ADMIN_INTERFACE_Y1 + 310 - listed_item * interval, "未处理", 16, 16, MY_RED);
        }
        else
        {
            puthz(ADMIN_INTERFACE_X1 + 400, ADMIN_INTERFACE_Y1 + 310 - listed_item * interval, "已处理", 16, 16, MY_GREEN);
        }
    }
    else
    {
        return; // 如果传入参数错误，则不做任何操作
    }

    delay(25); // 延时25ms，使列表的动画更有动感
}
void admin_show_user_info(USER_LOGIN_DATA TEMP, const int max, const int interval, int listed_item, int list_sequence)
{
    char buffer1[20];
    char buffer2[20];

    setcolor(MY_WHITE);
    if (list_sequence == ASCENDING)
    {
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
        ltoa(TEMP.ID, buffer1, 10);                                                                       // 将ID转换为字符串
        outtextxy(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 74 + listed_item * interval, buffer1);    // 输出ID
        outtextxy(ADMIN_INTERFACE_X1 + 120, ADMIN_INTERFACE_Y1 + 74 + listed_item * interval, TEMP.usrn); // 输出用户名
        outtextxy(ADMIN_INTERFACE_X1 + 240, ADMIN_INTERFACE_Y1 + 74 + listed_item * interval, TEMP.psw);  // 输出密码
        ltoa(TEMP.register_time, buffer1, 10);
        sprintf(buffer2, "%.4s.%.2s.%.2s", buffer1, buffer1 + 4, buffer1 + 6);                          // 将注册时间转换为字符串
        outtextxy(ADMIN_INTERFACE_X1 + 360, ADMIN_INTERFACE_Y1 + 74 + listed_item * interval, buffer2); // 输出注册时间
        if (TEMP.state == ACTIVE)
        {
            puthz(ADMIN_INTERFACE_X1 + 460, ADMIN_INTERFACE_Y1 + 70 + listed_item * interval, "活跃", 16, 16, MY_GREEN);
        }
        else if (TEMP.state == FROZEN)
        {
            puthz(ADMIN_INTERFACE_X1 + 460, ADMIN_INTERFACE_Y1 + 70 + listed_item * interval, "冻结", 16, 16, MY_LIGHTBLUE);
        }
        else if (TEMP.state == BANNED)
        {
            puthz(ADMIN_INTERFACE_X1 + 460, ADMIN_INTERFACE_Y1 + 70 + listed_item * interval, "封禁", 16, 16, MY_RED);
        }
    }
    else if (list_sequence == DESCENDING)
    {
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
        ltoa(TEMP.ID, buffer1, 10);                                                                                              // 将ID转换为字符串
        outtextxy(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 74 + (max - 1) * interval - listed_item * interval, buffer1);    // 输出ID
        outtextxy(ADMIN_INTERFACE_X1 + 120, ADMIN_INTERFACE_Y1 + 74 + (max - 1) * interval - listed_item * interval, TEMP.usrn); // 输出用户名
        outtextxy(ADMIN_INTERFACE_X1 + 240, ADMIN_INTERFACE_Y1 + 74 + (max - 1) * interval - listed_item * interval, TEMP.psw);  // 输出密码
        ltoa(TEMP.register_time, buffer1, 10);
        sprintf(buffer2, "%.4s.%.2s.%.2s", buffer1, buffer1 + 4, buffer1 + 6);                                                 // 将注册时间转换为字符串
        outtextxy(ADMIN_INTERFACE_X1 + 360, ADMIN_INTERFACE_Y1 + 74 + (max - 1) * interval - listed_item * interval, buffer2); // 输出注册时间
        if (TEMP.state == ACTIVE)
        {
            puthz(ADMIN_INTERFACE_X1 + 460, ADMIN_INTERFACE_Y1 + 70 + (max - 1) * interval - listed_item * interval, "活跃", 16, 16, MY_GREEN);
        }
        else if (TEMP.state == FROZEN)
        {
            puthz(ADMIN_INTERFACE_X1 + 460, ADMIN_INTERFACE_Y1 + 70 + (max - 1) * interval - listed_item * interval, "冻结", 16, 16, MY_LIGHTBLUE);
        }
        else if (TEMP.state == BANNED)
        {
            puthz(ADMIN_INTERFACE_X1 + 460, ADMIN_INTERFACE_Y1 + 70 + (max - 1) * interval - listed_item * interval, "封禁", 16, 16, MY_RED);
        }
    }
    else
    {
        return; // 如果传入参数错误，则不做任何操作
    }

    delay(25); // 延时25ms，使列表的动画更有动感
}
void admin_show_ebike_info(LINKLIST_USER usrdat, const int max, const int interval, int listed_item, int list_sequence)
{
    char buffer[30]; // 定义缓冲区

    setcolor(MY_WHITE); // 设置字体颜色为白色
    if (list_sequence == ASCENDING)
    {
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);                                                                    // 设置字体样式和方向
        ltoa(usrdat.ID, buffer, 10);                                                                                 // 将ID转换为字符串
        outtextxy(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 74 + listed_item * interval, buffer);                // 输出ID
        outtextxy(ADMIN_INTERFACE_X1 + 120, ADMIN_INTERFACE_Y1 + 74 + listed_item * interval, usrdat.ebike_ID);      // 输出电动车车牌
        outtextxy(ADMIN_INTERFACE_X1 + 220, ADMIN_INTERFACE_Y1 + 74 + listed_item * interval, usrdat.ebike_license); // 输出电动车牌照
        outtextxy(ADMIN_INTERFACE_X1 + 340, ADMIN_INTERFACE_Y1 + 74 + listed_item * interval, usrdat.location);      // 输出地址
        if (usrdat.ebike_state == ACTIVE)
        {
            puthz(ADMIN_INTERFACE_X1 + 440, ADMIN_INTERFACE_Y1 + 70 + listed_item * interval, "正常", 16, 16, MY_GREEN);
        }
        else if (usrdat.ebike_state == BROKEN)
        {
            puthz(ADMIN_INTERFACE_X1 + 440, ADMIN_INTERFACE_Y1 + 70 + listed_item * interval, "损坏", 16, 16, MY_RED);
        }
    }
    else if (list_sequence == DESCENDING)
    {
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);                                                                     // 设置字体样式和方向
        ltoa(usrdat.ID, buffer, 10);                                                                                  // 将ID转换为字符串
        outtextxy(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 284 - listed_item * interval, buffer);                // 输出ID
        outtextxy(ADMIN_INTERFACE_X1 + 120, ADMIN_INTERFACE_Y1 + 284 - listed_item * interval, usrdat.ebike_ID);      // 输出电动车车牌
        outtextxy(ADMIN_INTERFACE_X1 + 220, ADMIN_INTERFACE_Y1 + 284 - listed_item * interval, usrdat.ebike_license); // 输出电动车牌照
        outtextxy(ADMIN_INTERFACE_X1 + 340, ADMIN_INTERFACE_Y1 + 284 - listed_item * interval, usrdat.location);      // 输出地址
        if (usrdat.ebike_state == ACTIVE)
        {
            puthz(ADMIN_INTERFACE_X1 + 440, ADMIN_INTERFACE_Y1 + 280 - listed_item * interval, "正常", 16, 16, MY_GREEN);
        }
        else if (usrdat.ebike_state == BROKEN)
        {
            puthz(ADMIN_INTERFACE_X1 + 440, ADMIN_INTERFACE_Y1 + 280 - listed_item * interval, "损坏", 16, 16, MY_RED);
        }
    }
    else
    {
        return; // 如果传入参数错误，则不做任何操作
    }

    delay(25); // 延时25ms，使列表的动画更有动感
}

void admin_show_ebike_in_out(struct _EBIKE_IN_OUT_ TEMP, const int max, const int interval, int listed_item, int list_sequence)
{
    char buffer[30]; // 定义缓冲区

    setcolor(MY_WHITE); // 设置字体颜色为白色
    if (list_sequence == ASCENDING)
    {
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);                                                                     // 设置字体样式和方向
        outtextxy(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 74 + listed_item * interval, TEMP.ebike_id);            // 输出电动车车牌
        if(TEMP.in_time != 0){
            sprintf(buffer, "%.4s.%.2s.%.2s", TEMP.in_time, TEMP.in_time + 4, TEMP.in_time + 6, 10); // 将时间转换为字符串
            outtextxy(ADMIN_INTERFACE_X1 + 100, ADMIN_INTERFACE_Y1 + 74 + listed_item * interval, buffer);            // 输出时间
            puthz(ADMIN_INTERFACE_X1 + 200, ADMIN_INTERFACE_Y1 + 70 + listed_item * interval, "入", 16, 16, MY_GREEN);
            puthz(ADMIN_INTERFACE_X1 + 220, ADMIN_INTERFACE_Y1 + 70 + listed_item * interval, TEMP.location, 16, 16, MY_WHITE);
        }
        else{
            sprintf(buffer, "%.4s.%.2s.%.2s", TEMP.out_time, TEMP.out_time + 4, TEMP.out_time + 6, 10); // 将时间转换为字符串
            outtextxy(ADMIN_INTERFACE_X1 + 100, ADMIN_INTERFACE_Y1 + 74 + listed_item * interval, buffer);            // 输出时间
            puthz(ADMIN_INTERFACE_X1 + 200, ADMIN_INTERFACE_Y1 + 70 + listed_item * interval, "出", 16, 16, MY_LIGHTBLUE);
            puthz(ADMIN_INTERFACE_X1 + 220, ADMIN_INTERFACE_Y1 + 70 + listed_item * interval, TEMP.location, 16, 16, MY_WHITE);
        }
        admin_show_ebike_in_out_comment(TEMP.comment, listed_item, interval, max); // 输出备注

        if (TEMP.result == PENDING)
        {
            puthz(ADMIN_INTERFACE_X1 + 440, ADMIN_INTERFACE_Y1 + 70 + listed_item * interval, "待处理", 16, 16, MY_WHITE);
        }
        else if (TEMP.result == PASSED)
        {
            puthz(ADMIN_INTERFACE_X1 + 440, ADMIN_INTERFACE_Y1 + 70 + listed_item * interval, "已通过", 16, 16, MY_GREEN);
        }
        else if (TEMP.result == FAILED)
        {
            puthz(ADMIN_INTERFACE_X1 + 440, ADMIN_INTERFACE_Y1 + 70 + listed_item * interval, "未通过", 16, 16, MY_RED);
        }
    }
    else if (list_sequence == DESCENDING)
    {
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);                                                                     // 设置字体样式和方向
        outtextxy(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 284 - listed_item * interval, TEMP.ebike_id);            // 输出电动车车牌

        if(TEMP.in_time!= 0){
            sprintf(buffer, "%.4s.%.2s.%.2s", TEMP.in_time, TEMP.in_time + 4, TEMP.in_time + 6, 10); // 将时间转换为字符串
            outtextxy(ADMIN_INTERFACE_X1 + 100, ADMIN_INTERFACE_Y1 + 284 - listed_item * interval, buffer);            // 输出时间
            puthz(ADMIN_INTERFACE_X1 + 200, ADMIN_INTERFACE_Y1 + 280 - listed_item * interval, "入", 16, 16, MY_GREEN);
            puthz(ADMIN_INTERFACE_X1 + 220, ADMIN_INTERFACE_Y1 + 280 - listed_item * interval, TEMP.location, 16, 16, MY_WHITE);
        }
        else{
            sprintf(buffer, "%.4s.%.2s.%.2s", TEMP.out_time, TEMP.out_time + 4, TEMP.out_time + 6, 10); // 将时间转换为字符串
            outtextxy(ADMIN_INTERFACE_X1 + 100, ADMIN_INTERFACE_Y1 + 284 - listed_item * interval, buffer);            // 输出时间
            puthz(ADMIN_INTERFACE_X1 + 200, ADMIN_INTERFACE_Y1 + 280 - listed_item * interval, "出", 16, 16, MY_LIGHTBLUE);
            puthz(ADMIN_INTERFACE_X1 + 220, ADMIN_INTERFACE_Y1 + 280 - listed_item * interval, TEMP.location, 16, 16, MY_WHITE);
        }
        admin_show_ebike_in_out_comment(TEMP.comment, listed_item, interval, max); // 输出备注

        if (TEMP.result == PENDING)
        {
            puthz(ADMIN_INTERFACE_X1 + 440, ADMIN_INTERFACE_Y1 + 280 - listed_item * interval, "待处理", 16, 16, MY_WHITE);
        }
        else if (TEMP.result == PASSED)
        {
            puthz(ADMIN_INTERFACE_X1 + 440, ADMIN_INTERFACE_Y1 + 280 - listed_item * interval, "已通过", 16, 16, MY_GREEN);
        }
        else if (TEMP.result == FAILED)
        {
            puthz(ADMIN_INTERFACE_X1 + 440, ADMIN_INTERFACE_Y1 + 280 - listed_item * interval, "未通过", 16, 16, MY_RED);
        }
    }
}
void admin_show_ebike_in_out_comment(int comment, int listed_item, int interval, int max)
{
    char buffer[20];

    if (comment == EBIKE_IN_OUT_NULL)
        strcpy(buffer, "无");
    else if (comment == EBIKE_IN_OUT_REGISTERED_UNIT_IN || comment == EBIKE_IN_OUT_REGISTERED_UNIT_OUT)
        strcpy(buffer, "在校人员");
    else if (comment == EBIKE_IN_TAKE_OUT || comment == EBIKE_OUT_TAKE_OUT)
        strcpy(buffer, "外卖快递");
    else if (comment == EBIKE_IN_OTHER)
        strcpy(buffer, "其他");

    puthz(ADMIN_INTERFACE_X1 + 340, ADMIN_INTERFACE_Y1 + 70 + listed_item * interval, buffer, 16, 16, MY_WHITE);
}

// 判断一个数据块是否应该列出
int list_ebike_manage_is_valid(struct _EBIKE_INFO_ TEMP, char *list_mode, char *search_str, char *search_needed, int search_mode)
{
    if (
        (TEMP.conduct_time != -1 && search_mode == 0 || TEMP.conduct_time > 0 && search_mode == 1) &&
        (!strcmp(list_mode, "register") || !strcmp(list_mode, "license") || !strcmp(list_mode, "anual") ||
         !strcmp(list_mode, "broken") || !strcmp(list_mode, "violation")) &&
        (!strcmp(search_str, "\0") || TEMP.ID == atol(search_str) && !strcmp(search_needed, "ID")))
        return 1;
    else
        return 0;
}
int list_user_data_is_valid(USER_LOGIN_DATA TEMP, char *search_str, char *search_needed)
{
    if (!strcmp(search_str, "\0") ||
        TEMP.ID == atol(search_str) && !strcmp(search_needed, "ID") ||
        !strcmp(TEMP.usrn, search_str) && !strcmp(search_needed, "username") ||
        !strcmp(TEMP.psw, search_str) && !strcmp(search_needed, "password") ||
        TEMP.register_time == atol(search_str) && !strcmp(search_needed, "register_time"))
        return 1;
    else
        return 0;
}
int list_ebike_info_is_valid(LINKLIST_USER usrdat, char *search_str, char *search_needed)
{
    if (usrdat.ebike_ID != 0 && usrdat.ID != 0) // 要求一定要注册了车辆到数据库中，否则不予打印
    {
        if (!strcmp(search_str, "\0") ||
            usrdat.ID == atol(search_str) && !strcmp(search_needed, "ID") ||
            !strcmp(usrdat.usrn, search_str) && !strcmp(search_needed, "username") ||
            !strcmp(usrdat.rln, search_str) && !strcmp(search_needed, "realname") ||
            !strcmp(usrdat.location, search_str) && !strcmp(search_needed, "location") ||
            !strcmp(usrdat.ebike_ID, search_str) && !strcmp(search_needed, "ebike_ID") ||
            !strcmp(usrdat.ebike_license, search_str) && !strcmp(search_needed, "ebike_license") ||
            usrdat.anual_check == atol(search_str) && !strcmp(search_needed, "anual_check") ||
            usrdat.violations == atoi(search_str) && !strcmp(search_needed, "violations") ||
            usrdat.account_state == *search_str && !strcmp(search_needed, "account_state") ||
            usrdat.ebike_state == *search_str && !strcmp(search_needed, "ebike_state"))
        {
            return 1;
        }
        else
            return 0;
    }
    else
    {
        return 0;
    }
}

int list_ebike_in_out_is_valid(struct _EBIKE_IN_OUT_ TEMP, char *search_str, char *search_needed)
{
    if (!strcmp(search_str, "\0") ||
        strcmp(TEMP.ebike_id, search_str) &&!strcmp(search_needed, "ebike_ID") ||
        strcmp(TEMP.ebike_license, search_str) &&!strcmp(search_needed, "ebike_license") ||
        strcmp(TEMP.location, search_str) &&!strcmp(search_needed, "location") ||
        TEMP.in_time == atol(search_str) &&!strcmp(search_needed, "in_time") ||
        TEMP.out_time == atol(search_str) &&!strcmp(search_needed, "out_time") ||
        TEMP.result == atoi(search_str) &&!strcmp(search_needed, "result") ||
        TEMP.comment == atoi(search_str) &&!strcmp(search_needed, "comment")
    )
    {
        return 1;
    }
    else 
    {
        return 0;
    }


}

// 绘制页码
void list_show_page_index(unsigned int page_index, unsigned int page_count, const int max, const int interval)
{
    char buffer[20];

    setcolor(MY_WHITE);
    setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
    bar(ADMIN_INTERFACE_X1 + 460, ADMIN_INTERFACE_Y1 + 70 + max * interval,
        ADMIN_INTERFACE_X1 + 500, ADMIN_INTERFACE_Y1 + 80 + max * interval); // 清理页码
    sprintf(buffer, "<%d/%d>", page_index, page_count);                      // 格式化页码
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    outtextxy(ADMIN_INTERFACE_X1 + 460, ADMIN_INTERFACE_Y1 + 70 + max * interval, buffer); // 输出页码
}

// 绘制选中的行的图形动画，同时返回选中行对应数据的id
void handle_list_select_line_admin(LINKLIST *LIST, unsigned long item_id[], unsigned long *selected_id, const int max, const int interval,
                                   int page, int flag)
{
    int i;
    unsigned long previous_selected_id = *selected_id;
    LINKLIST_NODE *node = NULL;
    long pos = 0;
    char buffer[12];

    for (i = 0; i < max; i++)
    {
        if (mouse_press(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 70 + i * interval,
                        ADMIN_INTERFACE_X1 + 500, ADMIN_INTERFACE_Y1 + 70 + (i + 1) * interval - 1) == 1 &&
            item_id[i] != 0 && item_id[i] != previous_selected_id)
        {
            setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
            bar(ADMIN_INTERFACE_X1 + 10, ADMIN_INTERFACE_Y1 + 70, ADMIN_INTERFACE_X1 + 18, ADMIN_INTERFACE_Y1 + 310); // 清理所有高亮
            setfillstyle(SOLID_FILL, MY_YELLOW);
            bar(ADMIN_INTERFACE_X1 + 10, ADMIN_INTERFACE_Y1 + 70 + i * interval,
                ADMIN_INTERFACE_X1 + 18, ADMIN_INTERFACE_Y1 + 70 + i * interval + interval / (interval / 15)); // 生成当前高亮

            *selected_id = item_id[i];

            if(flag != ADMIN_DATABASE_EBIKE_PASS_IN_OUT && flag!= ADMIN_DATABASE_EBIKE_INFO)
            {
                // 输出选中行的补充信息
                setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
                bar(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 90 + max * interval,
                    ADMIN_INTERFACE_X1 + 420, ADMIN_INTERFACE_Y1 + 130 + max * interval); // 清理选中行显示的具体信息

                puthz(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 90 + max * interval, "姓名", 16, 16, MY_WHITE); // 输出选中行的具体信息
                puthz(ADMIN_INTERFACE_X1 + 120, ADMIN_INTERFACE_Y1 + 90 + max * interval, "电动车牌", 16, 16, MY_WHITE);
                puthz(ADMIN_INTERFACE_X1 + 220, ADMIN_INTERFACE_Y1 + 90 + max * interval, "通行证", 16, 16, MY_WHITE);
                puthz(ADMIN_INTERFACE_X1 + 340, ADMIN_INTERFACE_Y1 + 90 + max * interval, "违规次数", 16, 16, MY_WHITE);

                ltoa(*selected_id, buffer, 10);               // 将ID转换为字符串
                pos = linklist_find_data(LIST, buffer, "ID"); // 查找ID对应的节点
                if (pos == -1)
                {
                    puthz(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 110 + max * interval, "未找到对应数据", 16, 16, MY_RED);
                    return;
                }
                linklist_get_to_node(LIST, pos, &node); // 将指针指向对应节点

                if (node->USER_DATA.rln != "0" && node->USER_DATA.rln != NULL) // 输出电动车状态
                {
                    puthz(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 110 + max * interval, node->USER_DATA.rln, 16, 16, MY_WHITE); // 输出姓名
                }
                else
                {
                    puthz(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 110 + max * interval, "未登记姓名", 16, 16, MY_RED); // 输出姓名
                }
                if (node->USER_DATA.ebike_ID != "0" && node->USER_DATA.ebike_ID != NULL) // 输出电动车状态
                {
                    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
                    outtextxy(ADMIN_INTERFACE_X1 + 120, ADMIN_INTERFACE_Y1 + 114 + max * interval, node->USER_DATA.ebike_ID); // 输出电动车车牌
                }
                else
                {
                    puthz(ADMIN_INTERFACE_X1 + 120, ADMIN_INTERFACE_Y1 + 110 + max * interval, "未登记车牌", 16, 16, MY_RED); // 输出电动车车牌
                }
                if (node->USER_DATA.ebike_license != "0" && node->USER_DATA.ebike_license != NULL) // 输出电动车状态
                {
                    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
                    outtextxy(ADMIN_INTERFACE_X1 + 220, ADMIN_INTERFACE_Y1 + 114 + max * interval, node->USER_DATA.ebike_ID); // 输出电动车车牌
                }
                else
                {
                    puthz(ADMIN_INTERFACE_X1 + 220, ADMIN_INTERFACE_Y1 + 110 + max * interval, "未登记通行证", 16, 16, MY_RED); // 输出电动车车牌
                }
                ltoa(node->USER_DATA.violations, buffer, 10); // 将ID转换为字符串
                settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
                outtextxy(ADMIN_INTERFACE_X1 + 340, ADMIN_INTERFACE_Y1 + 110 + max * interval, buffer); // 违规次数
            }
        }
    }
    if (previous_selected_id == *selected_id &&
        mouse_press(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 70,
                    ADMIN_INTERFACE_X1 + 500, ADMIN_INTERFACE_Y1 + 70 + max * interval) == -1)
    {
        setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
        bar(ADMIN_INTERFACE_X1 + 10, ADMIN_INTERFACE_Y1 + 70, ADMIN_INTERFACE_X1 + 18, ADMIN_INTERFACE_Y1 + 310); // 清理所有高亮
        *selected_id = 0; // 如果点击时没有选中任何行，则将selected_id设置为0
        previous_selected_id = 0;

        // 清理选中行显示的具体信息
        setfillstyle(SOLID_FILL, MY_LIGHTGRAY);
        bar(ADMIN_INTERFACE_X1 + 20, ADMIN_INTERFACE_Y1 + 90 + max * interval,
            ADMIN_INTERFACE_X1 + 420, ADMIN_INTERFACE_Y1 + 130 + max * interval);
    }
}
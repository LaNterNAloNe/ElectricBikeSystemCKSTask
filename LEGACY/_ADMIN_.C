// 车辆注册界面
void admin_bike_register(int *page, unsigned long *id, LINKLIST *LIST);
// 车辆上牌界面
void admin_bike_license(int *page, unsigned long *id, LINKLIST *LIST);
// 车辆年检界面
void admin_bike_anual(int *page, unsigned long *id, LINKLIST *LIST);
// 车辆违章界面
void admin_bike_violation(int *page, unsigned long *id, LINKLIST *LIST);

/*****************************************************************
MODULE:管理员车辆注册
*****************************************************************/
void admin_bike_register(int *page, unsigned long *ID, LINKLIST *LIST)
{
    int mode = 0; // 搜索模式，列出已处理清单或待处理清单，主动清除该页面时重设为0（默认列出待处理清单）
    // static int visited=0; // 是否进入乐该页面，主动清除该页面时重设为0
    char search_str[10]; // 搜索框输入信息储存
    int selected_id = -1;
    unsigned long id_list[8] = {-1, -1, -1, -1, -1, -1, -1, -1}; // 记录当前显示的列表每行对应的ID
    int tag = ACTIVE_ADMIN_NULL;
    ADMIN_BUTTONS AdminButtons[18];
    FILE *fp_EBIKE_INFO_read = fopen("C:\\EBS\\DATA\\REGISTER.DAT", "rb+");
    if (!fp_EBIKE_INFO_read)
        exit(1);

    define_admin_buttons(AdminButtons, STRUCT_LENGTH(AdminButtons)); // 定义按钮

    fseek(fp_EBIKE_INFO_read, 0, SEEK_SET);
    drawgraph_admin_menu();
    drawgraph_admin_feature(*page);

    // 列出数据
    admin_list_info(id_list, fp_EBIKE_INFO_read, "register", mode, LIST_PAGEUP, LIST_CLEAR_CONTINUE, "\0", "\0");

    if (debug_mode == 1)
        display_memory_usage(400, 10); // 左上角显示

    while (*page == ADMIN_BIKE_REGISTER)
    {
        admin_flush_buttons(&tag, STRUCT_LENGTH(AdminButtons), AdminButtons);
        admin_handle_buttons_event(page);
        selected_id = handle_list_select_line_admin(id_list);
        newmouse(&MouseX, &MouseY, &press);

        admin_handle_features_event(LIST, page, search_str, id_list, fp_EBIKE_INFO_read, &mode, selected_id); // 处理点击事件

        delay(25);
    }

    fclose(fp_EBIKE_INFO_read);
    admin_list_info(NULL, NULL, NULL, NULL, NULL, 1, NULL, NULL);
    Input_Bar(NULL, NULL, NULL, NULL, NULL, 1, NULL);
    return;
}

/*****************************************************************
MODULE:管理员车辆上牌
*****************************************************************/
void admin_bike_license(int *page, unsigned long *id, LINKLIST *LIST)
{
    char *search_str;
    unsigned long id_list[8];
    int mode = 0;
    int selected_id;
    int tag = ACTIVE_ADMIN_NULL;
    ADMIN_BUTTONS AdminButtons[18];
    FILE *fp_EBIKE_LICENSE_read = fopen("C:\\EBS\\DATA\\LICENSE.DAT", "rb+");
    if (!fp_EBIKE_LICENSE_read)
        exit(1);

    define_admin_buttons(AdminButtons, STRUCT_LENGTH(AdminButtons)); // 定义按钮

    fseek(fp_EBIKE_LICENSE_read, 0, SEEK_SET);

    drawgraph_admin_menu();
    drawgraph_admin_feature(*page); // 画出界面

    if (debug_mode == 1)
        display_memory_usage(400, 10); // 左上角显示

    admin_list_info(id_list, fp_EBIKE_LICENSE_read, "license", mode, LIST_PAGEUP, LIST_CLEAR_CONTINUE, "\0", "\0"); // 列出数据

    while (*page == ADMIN_BIKE_LICENSE)
    {
        admin_flush_buttons(&tag, STRUCT_LENGTH(AdminButtons), AdminButtons);
        admin_handle_buttons_event(page);
        selected_id = handle_list_select_line_admin(id_list);
        newmouse(&MouseX, &MouseY, &press);

        admin_handle_features_event(LIST, page, search_str, id_list, fp_EBIKE_LICENSE_read, &mode, selected_id); // 处理点击事件
    }
    fclose(fp_EBIKE_LICENSE_read);
    admin_list_info(NULL, NULL, NULL, NULL, NULL, 1, NULL, NULL);
    Input_Bar(NULL, NULL, NULL, NULL, NULL, 1, NULL);
    return;
}

/*****************************************************************
MODULE:管理员车辆报废
*****************************************************************/
void admin_bike_broken(int *page, unsigned long *id, LINKLIST *LIST)
{
    char *search_str;
    unsigned long id_list[8];
    int mode = 0;
    int selected_id;
    int tag = ACTIVE_ADMIN_NULL;
    ADMIN_BUTTONS AdminButtons[18];
    FILE *fp_EBIKE_INFO_read = fopen("C:\\EBS\\DATA\\BROKEN.DAT", "rb+");
    if (!fp_EBIKE_INFO_read)
        exit(1);

    define_admin_buttons(AdminButtons, STRUCT_LENGTH(AdminButtons)); // 定义按钮

    fseek(fp_EBIKE_INFO_read, 0, SEEK_SET);

    drawgraph_admin_menu();
    drawgraph_admin_feature(*page); // 画出界面

    if (debug_mode == 1)
        display_memory_usage(400, 10); // 左上角显示

    admin_list_info(id_list, fp_EBIKE_INFO_read, "broken", mode, LIST_PAGEUP, LIST_CLEAR_CONTINUE, "\0", "\0"); // 列出数据

    while (*page == ADMIN_BIKE_BROKEN)
    {
        admin_flush_buttons(&tag, STRUCT_LENGTH(AdminButtons), AdminButtons);
        admin_handle_buttons_event(page);
        selected_id = handle_list_select_line_admin(id_list);
        newmouse(&MouseX, &MouseY, &press);

        admin_handle_features_event(LIST, page, search_str, id_list, fp_EBIKE_INFO_read, &mode, selected_id); // 处理点击事件
    }
    fclose(fp_EBIKE_INFO_read);
    admin_list_info(NULL, NULL, NULL, NULL, NULL, 1, NULL, NULL);
    Input_Bar(NULL, NULL, NULL, NULL, NULL, 1, NULL);
    return;
}

/*****************************************************************
MODULE:管理员车辆年检
*****************************************************************/
void admin_bike_anual(int *page, unsigned long *id, LINKLIST *LIST)
{
    char *search_str;
    unsigned long id_list[8];
    int mode = 0;
    int selected_id;
    int tag = ACTIVE_ADMIN_NULL;
    ADMIN_BUTTONS AdminButtons[18];
    FILE *fp_EBIKE_INFO_read = fopen("C:\\EBS\\DATA\\ANUAL.DAT", "rb+");
    if (!fp_EBIKE_INFO_read)
        exit(1);

    define_admin_buttons(AdminButtons, STRUCT_LENGTH(AdminButtons)); // 定义按钮

    fseek(fp_EBIKE_INFO_read, 0, SEEK_SET);

    drawgraph_admin_menu();
    drawgraph_admin_feature(*page); // 画出界面

    if (debug_mode == 1)
        display_memory_usage(400, 10); // 左上角显示

    admin_list_info(id_list, fp_EBIKE_INFO_read, "anual", mode, LIST_PAGEUP, LIST_CLEAR_CONTINUE, "\0", "\0"); // 列出数据

    while (*page == ADMIN_BIKE_ANUAL)
    {
        admin_flush_buttons(&tag, STRUCT_LENGTH(AdminButtons), AdminButtons);
        admin_handle_buttons_event(page);
        selected_id = handle_list_select_line_admin(id_list);
        newmouse(&MouseX, &MouseY, &press);

        admin_handle_features_event(LIST, page, search_str, id_list, fp_EBIKE_INFO_read, &mode, selected_id); // 处理点击事件
    }
    fclose(fp_EBIKE_INFO_read);
    admin_list_info(NULL, NULL, NULL, NULL, NULL, 1, NULL, NULL);
    Input_Bar(NULL, NULL, NULL, NULL, NULL, 1, NULL);
    return;
}

/*****************************************************************
MODULE:管理员车辆违章
*****************************************************************/
void admin_bike_violation(int *page, unsigned long *id, LINKLIST *LIST)
{
    char *search_str;
    unsigned long id_list[8];
    int mode = 0;
    int selected_id;
    int tag = ACTIVE_ADMIN_NULL;
    ADMIN_BUTTONS AdminButtons[18];
    FILE *fp_EBIKE_INFO_read = fopen("C:\\EBS\\DATA\\VIOLA.DAT", "rb+");
    if (!fp_EBIKE_INFO_read)
        exit(1);

    define_admin_buttons(AdminButtons, STRUCT_LENGTH(AdminButtons)); // 定义按钮

    fseek(fp_EBIKE_INFO_read, 0, SEEK_SET);

    drawgraph_admin_menu();
    drawgraph_admin_feature(*page); // 画出界面

    if (debug_mode == 1)
        display_memory_usage(400, 10); // 左上角显示

    admin_list_info(id_list, fp_EBIKE_INFO_read, "violation", mode, LIST_PAGEUP, LIST_CLEAR_CONTINUE, "\0", "\0"); // 列出数据

    while (*page == ADMIN_BIKE_VIOLATION)
    {
        admin_flush_buttons(&tag, STRUCT_LENGTH(AdminButtons), AdminButtons);
        admin_handle_buttons_event(page);
        selected_id = handle_list_select_line_admin(id_list);
        newmouse(&MouseX, &MouseY, &press);

        admin_handle_features_event(LIST, page, search_str, id_list, fp_EBIKE_INFO_read, &mode, selected_id); // 处理点击事件
    }
    fclose(fp_EBIKE_INFO_read);
    admin_list_info(NULL, NULL, NULL, NULL, NULL, 1, NULL, NULL);
    Input_Bar(NULL, NULL, NULL, NULL, NULL, 1, NULL);
    return;
}
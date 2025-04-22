#include"GLOBAL.H"

int main(void){
    int page = MAIN_USER; // 主页面
    char buffer[50];
    unsigned long ID = 1; // 记录登录用户的ID
    int driver=VGA,mode=VGAHI;
    LINKLIST *LIST = (LINKLIST *)malloc(sizeof(LINKLIST));
    if (LIST == NULL){ // 分配内存失败
        drawExittingProgram(2);
        exit(1); // 终止程序
    }
    LIST->HEAD = NULL;

    initgraph(&driver, &mode, "C:\\BORLANDC\\BGI");
    if (graphresult() != grOk)
    {
        printf("Graphics error: %s\n", grapherrormsg(graphresult()));
        exit(1);
    }
    cleardevice();
    
    initcolorpalette();
    mouseinit();
    linklist_get_user_data(LIST); // 生成链表
    rand_io_data(LIST); // 生成随机进出校园信息，采用覆盖之前文件的方式

    while(page != EXIT){   //循环直到page = EXIT ( 0 )
        // cleardevice();
        switch (page){
            // LOGIN.C
            case LOGIN:
                login(&page,&ID);
                break;
            case LOGIN_ADMIN:
                login_admin(&page,&ID);
                break;
            case REGISTER:
                _register(&page,&ID,LIST);
                break;
            case REGISTER_ID_INPUT:
                register_id_input(&page, &ID);
                break;
            
            // USER.C
            case MAIN_USER:
                user_main(&page);break;
            case USER_BIKE_REGISTER:
                user_bike_register(&page, &ID); break;
            case USER_BIKE_LICENSE:
                user_bike_license(&page, &ID); break;
            case USER_BIKE_LICENSE_NOTICE:
                user_bike_license_notice(&page, &ID); break;
            case USER_BIKE_WROTEOUT:
                user_bike_wroteout(&page, &ID); break;
            case USER_INFO:
                user_info(&page, &ID); break;
            case USER_INFO_BIKEINFO:
                user_bike_info(&page, &ID); break;
            case USER_HELP:
                user_help(&page, &ID); break;
            case USER_QUIZ:
                user_quiz(&page, &ID); break;
            

            //ADMIN.C
            case MAIN_ADMIN:
                main_admin(&page,&ID);
                break;
            case ADMIN_BIKE_REGISTER:
                admin_manage_bike_module(&page, &ID, LIST,"DATA\\REGISTER.DAT","register");
                break;
            case ADMIN_BIKE_LICENSE:
                admin_manage_bike_module(&page, &ID, LIST,"DATA\\LICENSE.DAT","license");
                break;
            case ADMIN_BIKE_ANUAL:
                admin_manage_bike_module(&page, &ID, LIST,"DATA\\ANUAL.DAT","anual");
                break;
            case ADMIN_BIKE_VIOLATION:
                admin_manage_bike_module(&page, &ID, LIST,"DATA\\VIOLA.DAT","violation");
                break;
            case ADMIN_BIKE_BROKEN:
                admin_manage_bike_module(&page, &ID, LIST,"DATA\\BROKEN.DAT","broken");
                break;
            case ADMIN_DATABASE:
                admin_database(&page, &ID, LIST);
                break;
            case ADMIN_MESSAGE:
                admin_message_center(&page, &ID);
                break;
            case ADMIN_INFO:
                admin_info(&page, &ID);
                break;

            // test
            case TEST:
                message_display_draw_bg();
                message_topic_display(120, 30, 400, "中科院研制出量子计算机“550W”", MY_BLACK, Hzk24s, 3, 0); // 标题
                message_text_display(160, 80, 200, "央视网", MY_BLACK);                                  // 文本
                message_text_display(390, 80, 200, "2058.7.10", MY_BLACK);                              // 文本
                message_text_display(120, 110, 400, "今年七月上旬，中国科学院数字生命研究所自主研发的550系列智能量子计算机第三代550W问世，并预计于今年年末正式投入使用。\n据悉，该智能量子计算机是目前最先进的自感知、自适应、自组织可重塑编译计算核心，拥有极为强大的算力。\n在前两代该系列智能量子计算机的帮助下，人类的空间技术得到飞速发展，进而拥有了星际航行和宇宙殖民的能力。该项目负责人表示，在新一代智能量子计算机的帮助下，人类建设外星家园的效率将极大幅度提高，甚至拥有殖民外星系的潜力。", MY_BLACK); // 文本
                hz_input(120, 420, 300, 460, buffer, 49, MY_CREAM, MY_BLACK, 16);
                getch();
                page = EXIT;
        }
    }
    drawExittingProgram(0);

    linklist_clear(LIST); // 清理链表
    getch(); //按任意键结束
    closegraph();
    return 0;
}




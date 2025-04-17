#include"GLOBAL.H"

int main(void){
    int page = MAIN_ADMIN; // 主页面
    // int page=NULL; // 副页面
    unsigned long ID=0;//记录登录用户的ID
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
    mouseinit();
    initcolorpalette();

    linklist_get_user_data(LIST); // 生成链表

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
            case USER_BIKE_WROTEOUT:
                user_bike_wroteout(&page, &ID); break;
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
                message_topic_display(120, 30, 400, "真是难得，日本“最强硬警告”美国", MY_BLACK, 24, 3, 0); // 标题
                message_text_display(120, 110, 400, "真是难得，按照外媒的说法，日本对美国发出“最强硬警告”。\n警告什么？\n警告美国不要欺人太甚。\n在4月14日的日本议会辩论中，日本首相石破茂批评特朗普的关税政策，说：“我完全清楚，迄今为止发生的事情，可能会扰乱全球经济秩序。”\n他表示：日本不打算做出重大让步，也不会急于在与美国进行的关税谈判中达成协议。\n对在野的野田佳彦提出“美国违反了《日美贸易协定》”的问题，石破茂回应称：“我们对此表示严重关切。与此同时，我们将考虑如何才能最有利于我们的国家利益，如何才能最有利于世界的利益。”", MY_BLACK); // 文本
                // message_display(NULL);
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




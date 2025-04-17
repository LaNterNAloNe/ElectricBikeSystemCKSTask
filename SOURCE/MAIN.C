#include"GLOBAL.H"

int main(void){
    int page = TEST; // 主页面
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
                message_topic_display(120, 30, 400, "AIA人都怎么了？", MY_BLACK, 24, 3, 0); // 标题
                message_text_display(120, 110, 400, "在CKS这个魔鬼课程的疯狂压榨下，老哥们人均化身赛博仓鼠，天天焊死在电脑前肝作业。凌晨三点的宿舍里，键盘敲得比发电报还响，黑眼圈都快掉到下巴了。\n现在翘课都成荣誉勋章了，群里天天比谁翘得狠——\n“老子这周就露脸两节课”\n“你那算啥？我连教授长啥样都忘了！” \n更离谱的是有人开发出三倍速刷网课的黑科技，主打一个“课可以不上，作业不能晚交”的极限操作。看着兄弟们逐渐魔怔的样子，突然觉得这破课怕不是个大型PUA现场——卷又卷不动，躺又躺不平，最后全成了秃头小宝贝（悲）", MY_BLACK); // 文本
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




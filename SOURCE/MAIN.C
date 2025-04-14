#include"GLOBAL.H"

int main(void){
    int page = MAIN_ADMIN; // 主页面
    // int page=NULL; // 副页面
    unsigned long ID=0;//记录登录用户的ID
    int driver=VGA,mode=VGAHI;
    LINKLIST *LIST;

    linklist_init(&LIST); // 初始化链表

    initgraph(&driver, &mode, "C:\\BORLANDC\\BGI");
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
                _register(&page,&ID);
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
        }
    }
    drawExittingProgram(0);

    linklist_clear(LIST); // 清理链表
    getch(); //按任意键结束
    closegraph();
    return 0;
}




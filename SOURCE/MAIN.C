#include"GLOBAL.H"

void main(){
    int page_1=MAIN_ADMIN; // 主页面
    int page_2=NULL; // 副页面
    int ID=-1;//记录登录用户的ID
    // 如果想测试函数，将page设为TEST //如果想正常执行程序，将page设为LOGIN
    int driver=VGA,mode=VGAHI;

    initgraph(&driver, &mode, "C:\\BORLANDC\\BGI");
    cleardevice();
    mouseinit();
    initcolorpalette();

    while(page_1 != EXIT){   //循环直到page = EXIT ( 0 )
        switch (page_1){
            // LOGIN.C
            case LOGIN:
                login(&page_1,&ID);break;
            case LOGIN_ADMIN:
                login_admin(&page_1,&ID);break;
            case REGISTER:
                _register(&page_1);break;
            
            // USER_MAIN_GRAPH.C
            case MAIN_USER:
                user_main(&page_1,&ID);break;

            //ADMIN_MAIN_GRAPH.C
            case MAIN_ADMIN:
                switch (page_2){
                    case NULL:
                        main_admin(&page_1,&page_2,&ID);break;
                    case ADMIN_BIKE_LICENSE:
                        admin_bike_license(&page_1,&page_2,&ID);break;
                }
        }
    }
    clrmous(MouseX,MouseY);
    drawExittingProgram(page_1);

    getch(); //按任意键结束
    closegraph();
}


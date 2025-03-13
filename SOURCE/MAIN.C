#include"GLOBAL.H"

void main(){
    int page=LOGIN;
    // 如果想测试函数，将page设为TEST //如果想正常执行程序，将page设为LOGIN
    int driver=VGA,mode=VGAHI;

    int uid=-1;//记录登录用户的uid

    initgraph(&driver, &mode, "C:\\BORLANDC\\BGI");
    cleardevice();
    mouseinit();
    initcolorpalette();

    while(page != EXIT){   //循环直到page = EXIT ( 0 )
        switch (page){
            // LOGIN.C
            case LOGIN:
                login(&page,&uid);break;
            case LOGIN_ADMIN:
                login_admin(&page,&uid);break;
            case REGISTER:
                _register(&page);break;
            
            // USER_MAIN_GRAPH.C
            case MAIN_USER:
                user_main(&page);
                break;

            //ADMIN_MAIN_GRAPH.C
            case MAIN_ADMIN:
                main_admin(&page);break;
        }
    }
    clrmous(MouseX,MouseY);
    drawExittingProgram(page);

    getch(); //按任意键结束
    closegraph();
}


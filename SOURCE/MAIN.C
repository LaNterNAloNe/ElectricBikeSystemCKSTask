#include"GLOBAL.H"



void main(){
    int page=LOGIN;
    // 如果想测试函数，将page设为TEST //如果想正常执行程序，将page设为LOGIN
    int driver=VGA,mode=VGAHI;

    initgraph(&driver, &mode, "C:\\BORLANDC\\BGI");
    cleardevice();
    mouseinit();

    while(page != EXIT){   //循环直到page = EXIT ( 0 )
        switch (page){
            // LOGIN.C
            case LOGIN:
                login(&page);break;
            case LOGIN_ADMIN:
                login_admin(&page);break;
            case REGISTER:
                _register(&page);break;
            case TEST:
                break;
            // USER_MAIN_GRAPH.C

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


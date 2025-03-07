#include"GLOBAL.H"
 
void main(){
    int page=LOGIN;

    initgraph(&driver, &mode, "C:\\BORLANDC\\BGI");
    cleardevice();
    mouseinit();

    while(page){
        
        switch (page){
            case LOGIN:
                {
                    login(&page);
                }
        }

        delay(25);
    }

    getch(); //按任意键结束
    closegraph();
}


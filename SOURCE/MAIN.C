#include"GLOBAL.H"
 
void main(){
    int page=LOGIN;
    int num = 0;

    initgraph(&driver, &mode, "C:\\BORLANDC\\BGI");
    cleardevice();
    mouseinit();

    while(page){
        
        switch (page){
            case LOGIN:
                {
                    login(&page,&num);
                }
        }

        delay(25);
    }
    clrmous(MouseX,MouseY);

    drawExittingProgram();

    getch(); //�����������
    closegraph();
}

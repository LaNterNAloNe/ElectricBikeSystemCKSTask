#include"GLOBAL.H"
 
void main(){
    int page=0;
    int driver =VGA;
    int mode =VGAHI;

    initgraph(&driver, &mode, "C:\\BORLANDC\\BGI");//“d:\\bc31”是bc31的安装路径
    cleardevice();

    mouseinit();
    while(1){
        newmouse(&MouseX,&MouseY,&press);
        
        if(mouse_press(0,0,640,480)==1){
            setcolor(RED);
            circle(MouseX,MouseY,10);
            floodfill(MouseX,MouseY,RED);
        }
        delay(25);
    }

getch(); //按任意键结束
closegraph();

}


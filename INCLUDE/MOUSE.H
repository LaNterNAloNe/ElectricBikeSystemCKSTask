#ifndef _mouse_h_
#define _mouse_h_

#define	SCR_WIDTH	640	 //屏幕宽度像素 
#define	SCR_HEIGHT	480		 //屏幕高度像素 

int mouse_press(int x1, int y1, int x2, int y2);//濡傛灉鍦ㄦ?嗕腑鐐瑰嚮锛屽垯杩斿洖1锛涘湪妗嗕腑鏈?鐐瑰嚮锛屽垯杩斿洖2锛涗笉鍦ㄦ?嗕腑鍒欒繑鍥?0
void mouse(int,int);//璁捐?￠紶鏍?
void mouseinit(void);//鍒濆?嬪寲
//void mou_pos(int*,int*,int*);//鏇存敼榧犳爣浣嶇疆
void mread(int *,int *,int*);//鏀瑰潗鏍囦笉鐢?
void save_bk_mou(int x,int y);//瀛橀紶鏍囪儗鏅?
void clrmous(int x,int y);//娓呴櫎榧犳爣
void drawmous(int x,int y);//鐢婚紶鏍?
void newmouse(int *nx,int *ny,int *nbuttons);   //鏇存柊榧犳爣
unsigned int Getpixel64k(int x, int y);

extern int MouseX;
extern int MouseY;
extern int MouseS;
extern int press;
extern union REGS regs;
#endif

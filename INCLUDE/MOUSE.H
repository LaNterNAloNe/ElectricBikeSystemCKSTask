#ifndef _mouse_h_
#define _mouse_h_

#define	SCR_WIDTH	640
#define	SCR_HEIGHT	480

int mouse_press(int x1, int y1, int x2, int y2);
void mouse(int,int);
void mouseinit(void);
//void mou_pos(int*,int*,int*);
void mread(int *,int *,int*);
void save_bk_mou(int x,int y);
void clrmous(int x,int y);
void drawmous(int x,int y);
// 以下为改进函数
void newmouse_data(int *nx, int *ny, int *nbuttons, int *mouse_flag);
void newmouse(int *nx, int *ny, int *nbuttons, int *mouse_flag);

extern int MouseX;
extern int MouseY;
extern int MouseS;
extern int press;

// 因为bc抽风，必须要补充定义，所以这里的extern变量直接不用了
// extern int mouse_flag;

extern union REGS regs;
#endif

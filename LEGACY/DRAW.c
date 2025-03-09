#include "DRAW.H"
void drawpic(int n)
{
	switch (n)
	{
	case(0):
		setrgbpalette(0, 12,158,245);//浅蓝背景-1
		setrgbpalette(1, 235,235,235);//浅灰框-1
		setrgbpalette(2, 0, 0, 0);//黑色
		setrgbpalette(3, 240, 230,75);//黄色
		setrgbpalette(4, 255, 0, 0);//红色
		setrgbpalette(5, 255, 255, 255);//白色
		setbkcolor(0);
		setcolor(WHITE);
		setlinestyle(0,0,3);
		setfillstyle(1,WHITE);//大框
		bar(120,120,520,390);
		setcolor(2);
		setlinestyle(0, 0, 3);
		setfillstyle(1,2);
		pieslice(160,175,0,360,10);//人头
		pieslice(160,205,0,180,20);
		pieslice(160,250,0,360,12);//钥匙
		bar(156,254,164,300);
		bar(164, 276, 170, 282);
		bar(163, 288,170, 294);
		setcolor(1);
		setlinestyle(0, 0, 3);
		setfillstyle(1, 1);
		bar(220, 170, 480, 205);//用户名框
		bar(220, 260, 480, 295);//密码框
		setcolor(4);
		setlinestyle(0, 0, 3);
		setfillstyle(1, 4);
		bar(230, 320, 330, 370);//分别为登录，注册
		bar(360, 320, 460, 370);
		setcolor(3);
		/*setlinestyle(0, 0, 3);
		setfillstyle(1, 3);
		bar(160, 330, 200, 360);//管理员模式*/

		setcolor(2); // 文本颜色为黑色
		settextstyle(1, HORIZ_DIR, 3);// 设置文本大小
		outtextxy(220,140, "Name");// 输出文本
		outtextxy(220, 230, "Password");
		setcolor(WHITE);
		settextstyle(1, HORIZ_DIR, 2);
		outtextxy(255, 330, "Log in");
		outtextxy(380, 330, "Register");
		break;
	default:
		setbkcolor(5);
		break;
	}
}
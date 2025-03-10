#include"INPUTCH.H"

/************************************************************************
CHANGETAG:这些函数经过了优化，更符合CKS宝宝体质
CHANGEINFO:1.实现记忆性，每次离开输入框时可记录输入内容
		   2.添加超出限制提示，可以适当修改提示内容所在位置
************************************************************************/

/************************************************************************
FUNCTION:Input_Vis
DESCRIPTION:实现可视化输入，有记忆的输入框
INPUT:输入内容，输入框左上角坐标x,y，字数限制，输入框颜色
RETURN:无
************************************************************************/
int Input_Vis(char* ip,int x,int y,int lim,int color) //输入内容，输入框左上角坐标x,y，字数限制，输入框颜色
//注意：该输入函数要求输入框宽度为25
{   
	static InputMemory memory_pool[5]={{0,0,"",0}};
	static int memory_count = 0;                       //记录总共输入了多少个输入框

	int i = 0;                                         //记录输入框位置
	int j = 0;  									   // 原定义位置不变 
	int found = 0;
	//int blinkTick = 0;                                 //记录光标闪烁时间
                                         
	char c;                                            //读取键盘输入的内容
	
	for (i = 0; i < memory_count; i++) {
        if (memory_pool[i].x == x && memory_pool[i].y == y) {
            strcpy(ip, memory_pool[i].content);
            j = memory_pool[i].cursor_pos;
            break;
        }
    }                                                  //查找对应的输入内容，并记录输入数

	
	setcolor(MY_BLACK);                                //设置显示字体为黑色
	setlinestyle(SOLID_LINE,0,THICK_WIDTH);            //设置线型

    if (j == 0) {  // 仅当无历史内容时执行原渲染逻辑 
		line(x+10,y+6,x+10,y+20); 
	} else {        // 有历史内容时直接定位到末尾光标 
		line(x+10+j*18,y+6,x+10+j*18,y+20);
	}

	clrmous(MouseX, MouseY);
	setcolor(MY_BLACK);                                //设置显示字体为白
	setfillstyle(SOLID_FILL,color);                    //保持填充颜色与输入框颜色一致
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,2);
	settextjustify(LEFT_TEXT,TOP_TEXT);
	while(bioskey(1))
	{
		i=bioskey(0);
	}
	while(1)
	{
	    c=bioskey(0);                                  //读取键盘输入内容
		setlinestyle(SOLID_LINE,0,THICK_WIDTH);        //设置线型，防止线条样式变为细线
		if(j<lim)
		{
			if(c!='\n'&&c!='\r'&&c!=' '&&c!=033)       //如果读入非换行、回车、空格或退出
			{
				if(c!='\b')                            //如果读入非退格
				{   
					if(c>='0'&&c<='9' || c>='a'&&c<='z' || c>='A'&&c<='Z' || c=='_')
					{
						*(ip+j)=c;                         //将读入的c存入输入内容字符串ip
						*(ip+j+1)='\0';                    //结束字符串ip
						bar(x+8+j*18,y+3,x+12+j*18,y+24);  //清除光标（注意在原光标坐标上加上已经输入的内容）
						settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2); //设置字体
						outtextxy(x+8+j*18,y-1,ip+j);      //在输入框中显示输入的字符（在其实光标右侧j*18处画字符）
						j++;                               //输入数加一
						line(x+10+j*18,y+6,x+10+j*18,y+20);//在新输入的字符后重画光标
					}else
					    return  1;
				}
				else if (c=='\b'&&j>0)                 //如果读入退格
				{	
					
					bar(x-10+j*18,y+3,x+7+j*18,y+24);  //清除上一输入字符
					bar(x+8+j*18,y+3,x+12+j*18,y+24);  //清除光标
					j--;                               //输入数减一
					line(x+10+j*18,y+6,x+10+j*18,y+20);//在上一输入的字符后重画光标
					*(ip+j)='\0';                      //清除字符串ip读入的上一字符
					*(ip+j+1)='\0';                    //结束字符串ip
				}
			}
			else                                       //如果读入换行、回车、空格或退出
			{
				setfillstyle(SOLID_FILL, color);       //结束当前输入操作
				bar(x+8+j*18,y+3,x+12+j*18,y+24);      //清除光标
				break;
			}
		}
		else if(j>=lim)                                //如果达到输入限制
		{
			if(c!='\n'&&c!='\r'&&c!=' '&&c!=033)       //其余功能不变
			{                                          //读入除换行、回车、空格、退出或退格以外字符不再存储与显示
				settextstyle(SMALL_FONT, HORIZ_DIR, 5); //设置字体
				outtextxy(x,y+30,"OUT OF LIMIT(13)");
				if(c=='\b'&&j>0)
				{	
					bar(x,y+33,x+150,y+45);			   //清除输入框下方的超出限制提示
					bar(x+8+j*18,y+3,x+12+j*18,y+24);  //清除要清楚的字符，用背景色覆盖
					bar(x-10+j*18,y+3,x+7+j*18,y+24);
					j--;
					line(x+10+j*18,y+6,x+10+j*18,y+20);
					*(ip+j)='\0';
				}
			}
			else
			{
				setfillstyle(SOLID_FILL, color);
				bar(x+8+j*18,y+3,x+12+j*18,y+24); 
				break;
			}
		}
	}

	bar(x,y+33,x+150,y+45);			   //清除输入框下方的超出限制提示

	//记录输入状态（以输入框的位置作为每个输入框的独特标识）
    for (i = 0; i < memory_count; i++) {
        if (memory_pool[i].x == x && memory_pool[i].y == y) {
            strcpy(memory_pool[i].content, ip);
            memory_pool[i].cursor_pos = j;
            found = 1;
            break;
        }
    }
    if (!found && memory_count < 10) {
        strcpy(memory_pool[memory_count].content, ip);
        memory_pool[memory_count].x = x;
        memory_pool[memory_count].y = y;
        memory_pool[memory_count].cursor_pos = j;
        memory_count++;
    }

	return 2;
}



/************************************************************************
FUNCTION:Input_Invis
DESCRIPTION:实现不可视化输入，有记忆的输入框
INPUT:输入内容，输入框左上角坐标x,y，字数限制，输入框颜色
RETURN:无
************************************************************************/
int Input_Invis(char* ip,int x,int y,int lim,int color)//大体与Input_Vis函数相同，仅对显示的字符做不可视处理
{
	static InputMemory memory_pool[5]={{0,0,"",0}};
	static int memory_count = 0;                      //记录总共输入了多少个输入框

	int i = 0;                                         //记录输入框位置
	int j = 0;  // 原定义位置不变 
	int found = 0;
                                         
	char c;                                            //读取键盘输入的内容
	
	for (i = 0; i < memory_count; i++) {
        if (memory_pool[i].x == x && memory_pool[i].y == y) {
            strcpy(ip, memory_pool[i].content);
            j = memory_pool[i].cursor_pos;
            break;
        }
    }                                                  //记录输入数

	setcolor(MY_BLACK);
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);
	setlinestyle(SOLID_LINE,0,THICK_WIDTH);             //设置线型

    if (j == 0) {  // 仅当无历史内容时执行原渲染逻辑 
		line(x+10,y+6,x+10,y+20); 
	} else {        // 有历史内容时直接定位到末尾光标 
		line(x+10+j*18,y+6,x+10+j*18,y+20);
	}

	clrmous(MouseX, MouseY);
	setfillstyle(SOLID_FILL,color);                    //设置填充形式
	setcolor(MY_BLACK);                                   //设置输出形式
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,2);
	settextjustify(LEFT_TEXT,TOP_TEXT);
	while(bioskey(1))
	{
		i=bioskey(0);
	}
	while(1)
	{
	    c=bioskey(0);                                  //读取键盘输入内容
		setlinestyle(SOLID_LINE,0,THICK_WIDTH);        //设置线型，防止线条样式变为细线
		if(j<lim)
		{
			if(c!='\n'&&c!='\r'&&c!=' '&&c!=033)       //如果读入非换行、回车、空格或退出
			{
				
			  
				if(c!='\b')                            //如果读入非退格
				{   
					if(c>='0'&&c<='9' || c>='a'&&c<='z' || c>='A'&&c<='Z' || c=='_')
				  	{ 
						*(ip+j) =c;                        //将读入的c存入输入内容字符串ip
						*(ip+j+1) = '\0';                  //结束字符串ip
						bar(x+8+j*18,y+3,x+12+j*18,y+24);  //清除光标
						outtextxy(x+8+j*18,y+4,"*");       //在输入框中显示字符“*”
						j++;                               //输入数加一
						line(x+10+j*18,y+6,x+10+j*18,y+20);//重画光标
					}else
						return 1;
				}
				else if (c=='\b'&&j>0)                 //如果读入退格
				{
					bar(x-10+j*18,y+3,x+7+j*18,y+24);  //清除上一输入字符
					bar(x+8+j*18,y+3,x+12+j*18,y+24);  //清除光标
					j--;                               //输入数减一
					line(x+10+j*18,y+6,x+10+j*18,y+20);//重画
					*(ip+j)='\0';                      //清除字符串ip读入的上一字符
					*(ip+j+1)='\0';                    //结束字符串ip
				}
			}
			else                                       //如果读入换行、回车、空格或退出
			{
				setfillstyle(SOLID_FILL, color);       //结束当前输入操作
				bar(x+8+j*18,y+3,x+12+j*18,y+24);      //清除光标
				break;
			}
		}
		else if(j>=lim)                                //如果达到输入限制
		{
			settextstyle(SMALL_FONT, HORIZ_DIR, 5); //设置字体
			outtextxy(x,y+30,"OUT OF LIMIT(13)");
			if(c!='\n'&&c!='\r'&&c!=' '&&c!=033)       //其余功能不变
			{                                          //读入除换行、回车、空格、退出或退格以外字符不再存储与显示
				if (c=='\b'&&j>0)
				{	
					bar(x,y+33,x+150,y+45);			   //清除输入框下方的超出限制提示
					
					bar(x+8+j*18,y+3,x+12+j*18,y+24);
					bar(x-10+j*18,y+3,x+7+j*18,y+24);
					j--;
					line(x+10+j*18,y+6,x+10+j*18,y+20);
					*(ip+j)='\0';
				}
			}
			else
			{
				setfillstyle(SOLID_FILL, color);
				bar(x+8+j*18,y+3,x+12+j*18,y+24); 
				break;
			}
		}
	}

	bar(x,y+33,x+150,y+45);			   //清除输入框下方的超出限制提示

	//记录输入状态
    for (i = 0; i < memory_count; i++) {
        if (memory_pool[i].x == x && memory_pool[i].y == y) {
            strcpy(memory_pool[i].content, ip);
            memory_pool[i].cursor_pos = j;
            found = 1;
            break;
        }
    }
    if (!found && memory_count < 10) {
        strcpy(memory_pool[memory_count].content, ip);
        memory_pool[memory_count].x = x;
        memory_pool[memory_count].y = y;
        memory_pool[memory_count].cursor_pos = j;
        memory_count++;
    }

	return 2;
}


#include"INPUTCH.H"

/************************************************************************
CHANGETAG:这些函数经过了优化，更符合CKS宝宝体质
CHANGEINFO:1.实现记忆性，每次离开输入框时可记录输入内容，实现这种功能时，添加了新的传入函数的参数int is_clear_memory
		   2.添加超出限制提示，可以适当修改提示内容所在位置
		   3.屏蔽了不会使用的字符的输入，防止函数运行异常和破坏画面
		   4.将两函数合为一体，因为确实只有一句话差别，加个调整的传入参数就好
************************************************************************/

/************************************************************************
FUNCTION:ch_input
DESCRIPTION:实现可视化或不可视化输入，有记忆的输入框
INPUT:输入内容，输入框左上角坐标x,y，字数限制，输入框颜色
RETURN:无
************************************************************************/
int ch_input(char* ip,int x,int y,int lim,int color,int is_clear_memory,int is_visible) 
//输入内容，输入框左上角坐标x,y，字数限制，输入框颜色，是否清除输入记忆，输入字符是否可见
//注意：该输入函数要求输入框宽度为25
{
    static InputMemory memory_pool[MAX_MEM];
    static int memory_count = 0;                       //记录总共输入了多少个输入框

	int i = 0;                                         //记录输入框位置
	int j = 0;  									   //原定义位置不变 
	int found = 0;
                                         
	unsigned int c;                                    //读取键盘输入的内容
	unsigned char scan_code_c; 						   //获取读数内容的扫描码
	unsigned char ascii_code_c;						   //获取读数内容的ASCII码

	char lim_str_buffer[3];							   //生成超出限制提示的字符串
	char out_of_limit_warnning[20]={'\0'};
	itoa(lim,lim_str_buffer,10);
    sprintf(out_of_limit_warnning, "%s%s%s", "OUT OF LIMIT(", lim_str_buffer,")");

	if(is_clear_memory){                         //如果收到清除记忆需求，则判断：1.只清除记忆，并退出函数 2.清除记忆，并执行接下来的代码
		memory_count = 0;
        for (i = 0; i < MAX_MEM; i++)
        {
            memory_pool[i].x = 0;
			memory_pool[i].y = 0;
			memory_pool[i].cursor_pos = 0;
			strcpy(memory_pool[i].content, "");
        }
        if(is_clear_memory == 1) return;
	}
	
	for (i = 0; i < memory_count; i++) {               //查找对应的输入内容，并记录输入数
        if (memory_pool[i].x == x && memory_pool[i].y == y) {
            strcpy(ip, memory_pool[i].content);
            j = memory_pool[i].cursor_pos;
            break;
        }
    }                                                  

	
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
		scan_code_c = (c >> 8) & 0xFF;
		ascii_code_c = c & 0xFF;
		setlinestyle(SOLID_LINE,0,THICK_WIDTH);        //设置线型，防止线条样式变为细线

		if (!(ascii_code_c>='0'&&ascii_code_c<='9' || ascii_code_c>='a'&&ascii_code_c<='z' || 
			ascii_code_c>='A'&&ascii_code_c<='Z' || ascii_code_c=='_'||ascii_code_c=='\n'||
			ascii_code_c=='\r'||ascii_code_c==' '|| ascii_code_c=='\b' ||ascii_code_c==033)) {
			continue;  
		}													
		//将输入内容限制在以上列出的按键中，防止错误地退出而不能正常存储输入状态和破坏画面

		if(j<lim)
		{	
			if(ascii_code_c!='\n'&&ascii_code_c!='\r'&&ascii_code_c!=' '&&ascii_code_c!=033)       //如果读入非换行、回车、空格或退出
			{
				if(ascii_code_c!='\b')                            //如果读入非退格
				{   
					if(ascii_code_c>='0'&&ascii_code_c<='9' || ascii_code_c>='a'&&ascii_code_c<='z' || 
						ascii_code_c>='A'&&ascii_code_c<='Z' || ascii_code_c=='_')
					{
						*(ip+j)=ascii_code_c;                         //将读入的c存入输入内容字符串ip
						*(ip+j+1)='\0';                    //结束字符串ip
						bar(x+8+j*18,y+3,x+12+j*18,y+24);  //清除光标（注意在原光标坐标上加上已经输入的内容）
						settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2); //设置字体

						if(is_visible == 1) outtextxy(x+8+j*18,y-1,ip+j);      //若传入的is_visible参数为1，在输入框中显示输入的字符（在其实光标右侧j*18处画字符）
						else if(is_visible == 0) outtextxy(x+8+j*18,y+4,"*");  //若传入的is_visible参数为1，在输入框中显示字符“*”

						j++;                               //输入数加一
						line(x+10+j*18,y+6,x+10+j*18,y+20);//在新输入的字符后重画光标
					}else
					    return  1;
				}
				else if (ascii_code_c=='\b'&&j>0)                 //如果读入退格
				{	
					
					bar(x-10+j*18,y+3,x+7+j*18,y+24);  //清除上一输入字符
					bar(x+8+j*18,y+3,x+12+j*18,y+24);  //清除光标
					j--;                               //输入数减一
					line(x+10+j*18,y+6,x+10+j*18,y+20);//在上一输入的字符后重画光标
					*(ip+j)='\0';                      //清除字符串ip读入的上一字符
					*(ip+j+1)='\0';                    //结束字符串ip
				}
			}else                                       //如果读入换行、回车、空格或退出
			{
				setfillstyle(SOLID_FILL, color);       //结束当前输入操作
				bar(x+8+j*18,y+3,x+12+j*18,y+24);      //清除光标
				break;
			}
		}
		else if(j>=lim)                                //如果达到输入限制
		{
			if(ascii_code_c!='\n'&&ascii_code_c!='\r'&&ascii_code_c!=' '&&ascii_code_c!=033)       //其余功能不变
			{                                          //读入除换行、回车、空格、退出或退格以外字符不再存储与显示
				settextstyle(SMALL_FONT, HORIZ_DIR, 5); //设置字体
				outtextxy(x,y+30,out_of_limit_warnning);
				if(ascii_code_c=='\b'&&j>0)
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



// /************************************************************************
// FUNCTION:Input_Invis
// DESCRIPTION:实现不可视化输入，有记忆的输入框
// INPUT:输入内容，输入框左上角坐标x,y，字数限制，输入框颜色
// RETURN:无
// ************************************************************************/
// int Input_Invis(char* ip,int x,int y,int lim,int color,int *page)//大体与Input_Vis函数相同，仅对显示的字符做不可视处理
// {	
// 	static int current_page = -1;                       //记录当前页面
// 	static InputMemory memory_pool[5]={{0,0,"",0}};
// 	static int memory_count = 0;                      //记录总共输入了多少个输入框

// 	int i = 0;                                         //记录输入框位置
// 	int j = 0;  // 原定义位置不变 
// 	int found = 0;
                                         
// 	unsigned int c;                                    //读取键盘输入的内容
// 	unsigned char scan_code_c; 						   //获取读数内容的扫描码
// 	unsigned char ascii_code_c;						   //获取读数内容的ASCII码

// 	char lim_str_buffer[3];							   //生成超出限制提示的字符串
// 	char out_of_limit_warnning[20]={'\0'};
// 	itoa(lim,lim_str_buffer,10);
// 	strcat(out_of_limit_warnning,"OUT OF LIMIT(");
// 	strcat(out_of_limit_warnning,lim_str_buffer);
// 	strcat(out_of_limit_warnning,")");

// 	if(current_page != *page){                         //如果当前输入与上一次输入所在页面不同，则清理输入记忆
// 		memory_count = 0;
// 		current_page = *page;
// 		for (i = 0; i < 5; i++) {
// 			memory_pool[i].x = 0;
// 			memory_pool[i].y = 0;
// 			memory_pool[i].cursor_pos = 0;
// 			strcpy(memory_pool[i].content, "");
// 		}
// 	}
	
// 	for (i = 0; i < memory_count; i++) {		        //查找对应的输入内容，并记录输入数
//         if (memory_pool[i].x == x && memory_pool[i].y == y) {
//             strcpy(ip, memory_pool[i].content);
//             j = memory_pool[i].cursor_pos;
//             break;
//         }
//     }                                                  

// 	setcolor(MY_BLACK);
//     settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);
// 	setlinestyle(SOLID_LINE,0,THICK_WIDTH);             //设置线型

//     if (j == 0) {  // 仅当无历史内容时执行原渲染逻辑 
// 		line(x+10,y+6,x+10,y+20); 
// 	} else {        // 有历史内容时直接定位到末尾光标 
// 		line(x+10+j*18,y+6,x+10+j*18,y+20);
// 	}

// 	clrmous(MouseX, MouseY);
// 	setfillstyle(SOLID_FILL,color);                    //设置填充形式
// 	setcolor(MY_BLACK);                                   //设置输出形式
// 	settextstyle(TRIPLEX_FONT,HORIZ_DIR,2);
// 	settextjustify(LEFT_TEXT,TOP_TEXT);
// 	while(bioskey(1))
// 	{
// 		i=bioskey(0);
// 	}
// 	while(1)
// 	{
// 	    c=bioskey(0);                                  //读取键盘输入内容
// 		scan_code_c = (c >> 8) & 0xFF;
// 		ascii_code_c = c & 0xFF;
// 		setlinestyle(SOLID_LINE,0,THICK_WIDTH);        //设置线型，防止线条样式变为细线

// 		if (!(ascii_code_c>='0'&&ascii_code_c<='9' || ascii_code_c>='a'&&ascii_code_c<='z' || 
// 			ascii_code_c>='A'&&ascii_code_c<='Z' || ascii_code_c=='_'||ascii_code_c=='\n'||
// 			ascii_code_c=='\r'||ascii_code_c==' '|| ascii_code_c=='\b' ||ascii_code_c==033)) {
// 			continue;  
// 		}													
// 		//将输入内容限制在以上列出的按键中，方式错误地退出而不能正常存储输入状态和破坏画面

// 		if(j<lim)
// 		{
// 			if(ascii_code_c!='\n'&&ascii_code_c!='\r'&&ascii_code_c!=' '&&ascii_code_c!=033)       //如果读入非换行、回车、空格或退出
// 			{
// 				if(ascii_code_c!='\b')                            //如果读入非退格
// 				{   
// 					if(ascii_code_c>='0'&&ascii_code_c<='9' || ascii_code_c>='a'&&ascii_code_c<='z' || 
// 						ascii_code_c>='A'&&ascii_code_c<='Z' || ascii_code_c=='_')
// 				  	{ 
// 						*(ip+j) =ascii_code_c;             //将读入的c存入输入内容字符串ip
// 						*(ip+j+1) = '\0';                  //结束字符串ip
// 						bar(x+8+j*18,y+3,x+12+j*18,y+24);  //清除光标
// 						outtextxy(x+8+j*18,y+4,"*");       //在输入框中显示字符“*”
// 						j++;                               //输入数加一
// 						line(x+10+j*18,y+6,x+10+j*18,y+20);//重画光标
// 					}else
// 						return 1;
// 				}
// 				else if (ascii_code_c=='\b'&&j>0)                 //如果读入退格
// 				{
// 					bar(x-10+j*18,y+3,x+7+j*18,y+24);  //清除上一输入字符
// 					bar(x+8+j*18,y+3,x+12+j*18,y+24);  //清除光标
// 					j--;                               //输入数减一
// 					line(x+10+j*18,y+6,x+10+j*18,y+20);//重画
// 					*(ip+j)='\0';                      //清除字符串ip读入的上一字符
// 					*(ip+j+1)='\0';                    //结束字符串ip
// 				}
// 			}
// 			else                                       //如果读入换行、回车、空格或退出
// 			{
// 				setfillstyle(SOLID_FILL, color);       //结束当前输入操作
// 				bar(x+8+j*18,y+3,x+12+j*18,y+24);      //清除光标
// 				break;
// 			}
// 		}
// 		else if(j>=lim)                                //如果达到输入限制
// 		{
// 			settextstyle(SMALL_FONT, HORIZ_DIR, 5); //设置字体
// 			outtextxy(x,y+30,out_of_limit_warnning);
// 			if(ascii_code_c!='\n'&&ascii_code_c!='\r'&&ascii_code_c!=' '&&c!=033)       //其余功能不变
// 			{                                          //读入除换行、回车、空格、退出或退格以外字符不再存储与显示
// 				if (ascii_code_c=='\b'&&j>0)
// 				{	
// 					bar(x,y+33,x+150,y+45);			   //清除输入框下方的超出限制提示
					
// 					bar(x+8+j*18,y+3,x+12+j*18,y+24);
// 					bar(x-10+j*18,y+3,x+7+j*18,y+24);
// 					j--;
// 					line(x+10+j*18,y+6,x+10+j*18,y+20);
// 					*(ip+j)='\0';
// 				}
// 			}
// 			else
// 			{
// 				setfillstyle(SOLID_FILL, color);
// 				bar(x+8+j*18,y+3,x+12+j*18,y+24); 
// 				break;
// 			}
// 		}
// 	}

// 	bar(x,y+33,x+150,y+45);			   //清除输入框下方的超出限制提示

// 	//记录输入状态
//     for (i = 0; i < memory_count; i++) {
//         if (memory_pool[i].x == x && memory_pool[i].y == y) {
//             strcpy(memory_pool[i].content, ip);
//             memory_pool[i].cursor_pos = j;
//             found = 1;
//             break;
//         }
//     }
//     if (!found && memory_count < 10) {
//         strcpy(memory_pool[memory_count].content, ip);
//         memory_pool[memory_count].x = x;
//         memory_pool[memory_count].y = y;
//         memory_pool[memory_count].cursor_pos = j;
//         memory_count++;
//     }

// 	return 2;
// }


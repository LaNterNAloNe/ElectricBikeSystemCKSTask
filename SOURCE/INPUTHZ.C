#include "INPUTHZ.h"

/************************************************************************
FUNCTION:hz_input
DESCRIPTION: 汉字输入法
INPUT:x1,x2,y1,y2,s(input string),len(string's maxlength),color(input box background color),color2(font color),size(font size)
RETURN:汉字个数len
IMPROVE:只能输入小写字母,可输出汉字或英文
************************************************************************/

int hz_input(int x1, int y1, int x2, int y2, char* s, int len, int color, int color2, int size)
{
    int i;
    int flag = 0;
    int ST = -1; // 输入法返回方式：1.按SPACE键返回输入汉字 2.按ENTER键返回输入英文 3.退格键返回不输入
    char* image;
    char* p = s + len;
    int value = 0;
    int asc;
    int Line = 0, L_len = 0; // 当前行数和该行字符数
    int pylen = 0;
    int xx1 = x1 + 2, xx2 = x2 - 2; // 防止输入溢出
    int L_maxwords = (xx2 - xx1) / (size / 2); // 每行最大字符数（按汉字计算）
    int maxline = (y2 - y1) / 30; // 最大行数
    int barx1, barx2, bary1, bary2;
    char str[3] = { '\0', '\0', '\0' }; // 存储一个汉字
    char py[12] = { '\0' }; // 拼音字符串

    int current_x = xx1;
    int current_line = 0;
    int current_columns = 0;
    char* current = s;
    char asc_str[2];

    int cursor_visible = 1; // 光标是否可见
    int cursor_x = xx1 + L_len * (size / 2); // 光标初始位置
    int cursor_y = y1 + Line * 30 - 30;

    struct textsettingstype old_text_settings;
    gettextsettings(&old_text_settings);

    settextjustify(LEFT_TEXT, CENTER_TEXT);
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 3);

    clrmous(MouseX, MouseY);
    setfillstyle(SOLID_FILL, WHITE);
    bar(x1 - 1, y1 + 1, x2 - 1, y2 - 1);

    // 绘制已存在的字符串内容
   
    while (current < s + len) {
        if ((unsigned char)*current >= 0xA1 && current + 1 < s + len) { // 处理汉字
            if (current_columns + 2 > L_maxwords) { // 换行
                current_line++;
                current_columns = 0;
                current_x = xx1;
                if (current_line >= maxline) break;
            }
            str[0] = *current;
            str[1] = *(current + 1);
            puthz(current_x, y1 + current_line * 30, str, size, size + 4, color2);
            current_x += size + 4;
            current_columns += 2;
            current += 2;
        }
        else { // 处理ASCII字符
            if (current_columns + 1 > L_maxwords) { // 换行
                current_line++;
                current_columns = 0;
                current_x = xx1;
                if (current_line >= maxline) 
                    break;
            }
            asc_str[0] = *current;
            asc_str[1] = '\0';
            xouttextxy(current_x, y1 + current_line * 30-28, asc_str, color2);//
            current_x += size + 4; // 假设ASCII字符宽8像素
            current_columns++;
            current++;
        }
    }
    Line = current_line + 1; // 初始行数
    L_len = current_columns; // 当前行字符数

    
    while (bioskey(1)) bioskey(0); // 清空键盘缓冲区

    if ((image = malloc(8241)) == NULL) {
        closegraph();
        printf("error!,hz_input");
        getch();
        exit(1);
    }
    
    
    cursor_x = xx1 + L_len * (size / 2 + 2) - 2; // 更新光标X位置
    cursor_y = y1 + (Line - 1) * 30;      // 更新Y位置
    setcolor(BLACK); // 光标颜色
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    line(cursor_x, cursor_y, cursor_x, cursor_y + size); // 绘制竖线作为光标// 初始化光标为可见状态
    while (1) {
        
        if (kbhit()) {
            value = bioskey(0);
            switch (value) {
            case BACK:
                if (len <= 0) break;
                if (*(p - 1) > 31 && *(p - 1) < 127) { // ASCII字符
                    setfillstyle(1, WHITE);
                    bar(xx1 + (L_len - 1) * 8, y1 + (Line - 1) * 30, xx1 + L_len * 8, y1 + Line * 30);
                    p--;
                    len--;
                    L_len--;

                    //删除光标
                    setcolor(WHITE); // 光标颜色
                    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
                    line(cursor_x, cursor_y, cursor_x, cursor_y + size); // 绘制竖线作为光标// 初始化光标为可见状态
                    //新位置绘制光标
                    cursor_x = xx1 + L_len * (size / 2 + 2) - 2; // 更新光标X位置
                    cursor_y = y1 + (Line - 1) * 30;      // 更新Y位置
                    setcolor(BLACK); // 光标颜色
                    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
                    line(cursor_x, cursor_y, cursor_x, cursor_y + size); // 绘制竖线作为光标// 初始化光标为可见状态

                }
                else { // 汉字
                    setfillstyle(1, WHITE);
                    bar(xx1 + (L_len - 2) * (size / 2 + 2), y1 + (Line - 1) * 30, xx1 + L_len * (size / 2 + 2), y1 + Line * 30);
                    p -= 2;
                    len -= 2;
                    L_len -= 2;

                    //删除光标
                    setcolor(WHITE); // 光标颜色
                    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
                    line(cursor_x, cursor_y, cursor_x, cursor_y + size); // 绘制竖线作为光标// 初始化光标为可见状态
                    //新位置绘制光标
                    cursor_x = xx1 + L_len * (size / 2 + 2) - 2; // 更新光标X位置
                    cursor_y = y1 + (Line - 1) * 30;      // 更新Y位置
                    setcolor(BLACK); // 光标颜色
                    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
                    line(cursor_x, cursor_y, cursor_x, cursor_y + size); // 绘制竖线作为光标// 初始化光标为可见状态
                }
                *p = '\0'; // 更新终止符
                break;
            case ENTER:
                *p = '\0';
                free(image);
                settextjustify(old_text_settings.horiz, old_text_settings.vert);
                settextstyle(old_text_settings.font, old_text_settings.direction, old_text_settings.charsize);
                //删除光标
                setcolor(WHITE); // 光标颜色
                setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
                line(cursor_x , cursor_y, cursor_x , cursor_y + size); // 绘制竖线作为光标// 初始化光标为可见状态
                return len;
            }

            asc = value & 0xff;
            if (asc >= 97 && asc <= 122) { // 输入法处理
                barx1 = (xx1 + L_len * 8 - 50 > 0) ? xx1 + L_len * 8 - 50 : 0;
                barx2 = (barx1 + 200 < 630) ? barx1 + 200 : 430;
                bary1 = y1 + Line * 30 + 10;
                bary2 = (bary1 + 40 < 480) ? bary1 + 40 : bary1 - 40;
                getimage(barx1, bary1, barx2, bary2, image);
                pyFrm(barx1, bary1, barx2, bary2);
                setfillstyle(1, color);
                ST = input_method(barx1, bary1, str, value, py);

                switch (ST) {
                case 1: // 输入汉字
                    if (strlen(str)) {
                        if ((L_len + 2) > L_maxwords && Line <= maxline) {
                            Line++;
                            L_len = 0;
                        }
                        strcpy(p, str);
                        puthz(xx1 + L_len * (size / 2 + 2), y1 + (Line - 1) * 30, str, size, size + 4, color2);
                        p += 2;
                        len += 2;
                        L_len += 2;
                    }
                    

                    //删除光标
                    setcolor(WHITE); // 光标颜色
                    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
                    line(cursor_x, cursor_y, cursor_x, cursor_y + size); // 绘制竖线作为光标// 初始化光标为可见状态
                    //新位置绘制光标
                    cursor_x = xx1 + L_len * (size / 2 + 2) - 2; // 更新光标X位置
                    cursor_y = y1 + (Line - 1) * 30;      // 更新Y位置
                    setcolor(BLACK); // 光标颜色
                    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
                    line(cursor_x, cursor_y, cursor_x, cursor_y + size); // 绘制竖线作为光标// 初始化光标为可见状态

                    putimage(barx1, bary1, image, 0);
                    memset(py, 0, sizeof(py));//重置拼音
                    break;
                case 2: // 输入英文
                    pylen = strlen(py);
                    if (L_len + pylen > L_maxwords && Line <= maxline) {
                        Line++;
                        L_len = 0;
                    }
                    xouttextxy(xx1 + L_len * 8, y1 + (Line - 1) * 30 - 28, py, color2);
                    strcpy(p, py);
                    len += pylen;
                    p += pylen;
                    L_len += pylen;

                    //删除光标
                    setcolor(WHITE); // 光标颜色
                    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
                    line(cursor_x, cursor_y, cursor_x, cursor_y + size); // 绘制竖线作为光标// 初始化光标为可见状态
                    //新位置绘制光标
                    cursor_x = xx1 + L_len * (size / 2 + 2) - 2; // 更新光标X位置
                    cursor_y = y1 + (Line - 1) * 30;      // 更新Y位置
                    setcolor(BLACK); // 光标颜色
                    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
                    line(cursor_x, cursor_y, cursor_x, cursor_y + size); // 绘制竖线作为光标// 初始化光标为可见状态

                    putimage(barx1, bary1, image, 0);
                    break;
                case 3: // 取消输入
                      //删除光标
                    setcolor(WHITE); // 光标颜色
                    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
                    line(cursor_x, cursor_y, cursor_x, cursor_y + size); // 绘制竖线作为光标// 初始化光标为可见状态
                    //新位置绘制光标
                    cursor_x = xx1 + L_len * (size / 2 + 2) - 2; // 更新光标X位置
                    cursor_y = y1 + (Line - 1) * 30;      // 更新Y位置
                    setcolor(BLACK); // 光标颜色
                    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
                    line(cursor_x, cursor_y, cursor_x, cursor_y + size); // 绘制竖线作为光标// 初始化光标为可见状态

                    putimage(barx1, bary1, image, 0);
                    memset(py, 0, sizeof(py));
                    break;
                }
            }
            else if (asc > 31 && asc < 127) { // 直接输入ASCII
                if (L_len >= L_maxwords && Line < maxline) {
                    Line++;
                    L_len = 0;
                }
                *p = asc;
                xouttextxy(xx1 + L_len * 8, y1 + (Line - 1) * 30 - 28, &asc, color2);
                p++;
                len++;
                L_len++;
                *p = '\0'; // 确保终止符

                   //删除光标
                setcolor(WHITE); // 光标颜色
                setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
                line(cursor_x, cursor_y, cursor_x, cursor_y + size); // 绘制竖线作为光标// 初始化光标为可见状态
                //新位置绘制光标
                cursor_x = xx1 + L_len * (size / 2 + 2) - 2; // 更新光标X位置
                cursor_y = y1 + (Line - 1) * 30;      // 更新Y位置
                setcolor(BLACK); // 光标颜色
                setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
                line(cursor_x, cursor_y, cursor_x, cursor_y + size); // 绘制竖线作为光标// 初始化光标为可见状态
            }
        }

        if ((MouseX < x1 || MouseX > x2 || MouseY < y1 || MouseY > y2) && press) {
            *p = '\0';
            settextjustify(old_text_settings.horiz, old_text_settings.vert);
            settextstyle(old_text_settings.font, old_text_settings.direction, old_text_settings.charsize);
            free(image);
            return len;
        }
        
    }
}



/************************************************************************
FUNCTION:input_method
DESCRIPTION: 汉字输入法调入
INPUT:x,y,str,value,py
RETURN:1:输出汉字；2：输出字母；3：输出空格
************************************************************************/

int input_method(int x, int y, char *str, int value, char *py)
{
    FILE *fp = NULL, *oldfp = NULL;
    int fJudge = FAIL;
    char *p = py;
    int trigger = 1; // 进入时触发输入标志
    char temphz[5][3] = {{'\0', '\0', '\0'}, {'\0', '\0', '\0'}, {'\0', '\0', '\0'}, {'\0', '\0', '\0'}, {'\0', '\0', '\0'}}, temp[3];
    int fposition = 0;
    int hznow = 0, hznum = 0;
    int asc, i;
    int PyStartx = x + 8, PyStarty = y + 4;
    int HzStartx = x + 8, HzStarty = y + 22;
    char *ABpath = "pinyin\\"; // 汉语拼音检索标准路径
    char pypath[45];           // 汉语拼音检索相对路径
    settextjustify(LEFT_TEXT, CENTER_TEXT);
    strcpy(pypath, "pinyin\\");
    while (1)
    {
        if (trigger || kbhit()) // 第一次进入自动触发 以后均需键盘
        {
            clrmous(MouseX, MouseY);
            trigger = 0;
            if (kbhit())
                value = bioskey(0);
            asc = value & 0xff;
            /*特殊按键处理*/
            switch (value)
            {
            case BACK:
                p--;
                *p = '\0';
                if (py[0] == '\0')
                {
                    if (oldfp)
                        fclose(oldfp);
                    if (fp)
                        fclose(fp);
                    return 3;
                }
                break;
            case SPACE:
                strcpy(str, temphz[hznow]);
                if (oldfp)
                    fclose(oldfp);
                if (fp)
                    fclose(fp);
                return 1;
            case ENTER:
                if (oldfp)
                    fclose(oldfp);
                if (fp)
                    fclose(fp);
                return 2;
            case LASTLINE:
                if (fposition >= 8) // 接下来重定位文件指针前八个字节（四个汉字）
                {
                    fposition -= 8;
                }
                break;
            case NEXTLINE:
                if (!feof(fp)) // 接下来重定位文件指针后八个字节（四个汉字）
                {
                    fposition += 8;
                }
                break;
            case LEFT: // 左移动一个
                if (hznow)
                {
                    hznow--;
                }
                else if (fposition >= 8) // 需要左换页
                {
                    fposition -= 8;
                    hznow = 3;
                }
                break;
            case RIGHT:
                if (hznow < hznum - 1) // 同左
                {
                    hznow++;
                }
                else if (!feof(fp))
                {
                    fposition += 8;
                    hznow = 0;
                }
                break;
                /*按数字键选中输入汉字*/
            case FIRST:
                strcpy(str, temphz[0]);
                if (oldfp)
                    fclose(oldfp);
                if (fp)
                    fclose(fp);
                return 1;
            case SECOND:
                strcpy(str, temphz[1]);
                if (oldfp)
                    fclose(oldfp);
                if (fp)
                    fclose(fp);
                return 1;
            case THIRD:
                strcpy(str, temphz[2]);
                if (oldfp)
                    fclose(oldfp);
                if (fp)
                    fclose(fp);
                return 1;
            case FOURTH:
                strcpy(str, temphz[3]);
                if (oldfp)
                    fclose(oldfp);
                if (fp)
                    fclose(fp);
                return 1;
            }
            /*输入字符处理*/
            if (asc > 31 && asc < 127 && strlen(py) < MAXPY && asc != '[' && asc != ']') // 有效输入时则复位
            {
                *p = asc;
                p++;
                fposition = 0;
                hznow = 0;
            }
            pyFrm(x, y, x + 200, y + 40);
            setfillstyle(1, WHITE);
            settextstyle(1, 0, 2);
            outtextxy(PyStartx, PyStarty, py); // 拼音字体
            strcat(pypath, py);
            strcat(pypath, ".txt");
            if (fJudge) // 将当前文件指针保存 同时关闭上一个文件  为输入特殊字符准备
            {
                if (oldfp)
                {
                    fclose(oldfp);
                }
                oldfp = fp;
            }
            if ((fp = fopen(pypath, "r")) == NULL) // 特殊字符存在  保留上一个文件检索结果
            {
                fJudge = FAIL;
                fp = oldfp;
            }
            else
            {
                fJudge = SUCCESS;
            }
            if (fp)
            {
                fseek(fp, fposition, SEEK_SET);
                for (i = 0; i < 5; i++)
                {
                    fread(temphz[i], 2, 1, fp); // 读入一个汉字
                    if (feof(fp))               // 读到文件尾
                    {
                        hznum = i; // 按道理此处文件尾多读一次 需要减一  然而此处不减一的效果更好
                        break;
                    }
                }
                if (!feof(fp)) // 未读到文件尾 全显汉字
                {
                    hznum = 4;
                }
                for (i = 0; i < hznum; i++)
                {
                    setcolor(BLUE);
                    settextstyle(1, 0, 2);
                    xouttextxy(HzStartx + i * 50, HzStarty + 5, itostr(i + 1, temp), DARKGRAY);
                    puthz(HzStartx + i * 50 + 16, HzStarty, temphz[i], 16, 16, DARKGRAY);
                }
                puthz(HzStartx + hznow * 50 + 16, HzStarty, temphz[hznow], 16, 16, CYAN); // 显示选中汉字
            }
        }
        strcpy(pypath, ABpath); // 绝对路径复原（不可少）
        value = 0;
    }
}

/************************************************************************
FUNCTION:itostr
DESCRIPTION: 数字标号
INPUT:a,s
RETURN:数字s
************************************************************************/

char *itostr(int a, char *s)
{
    switch (a)
    {
    case 1:
        strcpy(s, "1.");
        return s;
    case 2:
        strcpy(s, "2.");
        return s;
    case 3:
        strcpy(s, "3.");
        return s;
    case 4:
        strcpy(s, "4.");
        return s;
    }
    return s;
}

/************************************************************************
FUNCTION:pyFrm
DESCRIPTION: 输入法小框
INPUT:x1,y1,x2,y2
RETURN:无
************************************************************************/

void pyFrm(int x1, int y1, int x2, int y2)
{
    setfillstyle(1, WHITE);
    bar(x1, y1, x2, y2);
    setcolor(BLUE);
    setlinestyle(0, 0, 1);
    line(x1 + 5, y1 + 20, x2 - 5, y1 + 20);
    setcolor(DARKGRAY);
    rectangle(x1, y1, x2, y2);
}

/************************************************************************
FUNCTION:xouttextxy
DESCRIPTION: 字符输入法
INPUT:x,y,s,color
RETURN:字符长度len
************************************************************************/

int xouttextxy(int x, int y, char *s, int color) // 8x16点阵字库
{
    FILE *asc = NULL;
    int i, j, k;
    char *mat, *temp;
    int len;
    long offset;
    int mask;

    len = strlen(s);
    if (!len)
        return 0; // 空字符串不执行操作
    if ((asc = fopen("HZK\\ASC16", "rb")) == NULL)
    {
        closegraph();
        printf("outtextxy can't open asc16!,xouttextxy");
        delay(3000);
        exit(1);
    }
    if ((mat = (char *)malloc(16 * sizeof(char) * len)) == NULL) // 存放点阵
    {
        closegraph();
        printf("Failed!,xouttextxy");
        fclose(asc);
        getch();
        exit(1);
    }
    temp = mat;
    for (i = 0; i < len; i++)
    {
        offset = (long)16 * s[i]; // 计算字符的文件偏移
        fseek(asc, offset, SEEK_SET);
        fread(temp, sizeof(char), 16, asc); // 将所有字符点阵存入mat
        temp += 16;
    }
    fclose(asc);
    for (i = 0; i < len; i++) // 通过放点显示字符
    {
        for (j = 0; j < 16; j++)
        {
            mask = 0x80;
            for (k = 0; k < 8; k++)
            {
                if (mat[i * 16 + j] & mask)
                    putpixel(x + 8 * i + k, y + j, color);
                mask >>= 1;
            }
        }
    }
    free(mat);
    return len;
}

#ifndef _graphic_h_
#define _graphic_h_

#include<graphics.h>
#include<math.h>
#include<ctype.h>

// 参数说明：
// x1,y1 - 起点坐标
// x2,y2 - 终点坐标 
// r     - 圆弧半径 
// isSolid - 是否填充：true实心/false空心
// borderWidth - 边框宽度
// convexSide - 凸侧方向：'L'左/'R'右/'U'上/'D'下（大小写均可）
// color - BGI颜色常量（0-15）或自定义调色板索引 

// 圆形绘制
void drawCircle(int x0, int y0, int r, int isSolid, int borderWidth, int color) {
	int originalColor = getcolor();
	struct linesettingstype originalLine;
	getlinesettings(&originalLine);

	if(isSolid) {
		setfillstyle(SOLID_FILL, color);    // 设置填充颜色
		fillellipse(x0, y0, r, r);          // 绘制实心圆
		setcolor(color);                    // 设置边框颜色
		setlinestyle(SOLID_LINE, 0, borderWidth);
		ellipse(x0, y0, 0, 360, r, r);      // 绘制边框
	} else {
		setcolor(color);                    // 设置线条颜色
		setlinestyle(SOLID_LINE, 0, borderWidth);
		ellipse(x0, y0, 0, 360, r, r);
	}
	setlinestyle(originalLine.linestyle,  originalLine.upattern,  originalLine.thickness);
	setcolor(originalColor);
}

// 圆弧绘制
void drawConvexArc(int x1, int y1, int x2, int y2, int r, char convexSide, int color) {
	// 保存原始绘图状态
	int originalColor = getcolor();
	// 计算弦长和角度
	float dx = x2 - x1;
	float dy = y2 - y1;
	float chordLength = sqrt(dx*dx + dy*dy);
	// 计算弦角参数
	float theta = atan2(dy, dx);      // 弦与X轴夹角
	float alpha = asin(chordLength/(2*r));  // 圆心角半角
	// 转换为角度制并绘制
	int startAngle = (theta - alpha) * 180/M_PI;  // 起始角度
	int endAngle = (theta + alpha) * 180/M_PI;   // 终止角度
	//
    float centerX,centerY;

	struct linesettingstype originalLine;
	getlinesettings(&originalLine);
	// 设置新颜色
	setcolor(color);

	// 有效性验证
	if(chordLength > 2*r || r <= 0) {
		restorecrtmode();  // 恢复原始模式避免错误
		closegraph();
		printf("Error: Invalid radius or points distance!");
		return;
	}

	switch(toupper(convexSide)) {
		case 'L':  // 向左凸
			centerX = (x1 + x2)/2 - r*sin(theta);
			centerY = (y1 + y2)/2 + r*cos(theta);
			break;
		case 'R':  // 向右凸
			centerX = (x1 + x2)/2 + r*sin(theta);
			centerY = (y1 + y2)/2 - r*cos(theta);
			break;
		case 'U':  // 向上凸
			centerX = (x1 + x2)/2 + r*cos(theta);
			centerY = (y1 + y2)/2 + r*sin(theta);
			break;
		case 'D':  // 向下凸
			centerX = (x1 + x2)/2 - r*cos(theta);
			centerY = (y1 + y2)/2 - r*sin(theta);
			break;
		default:   // 非法方向
			setcolor(originalColor);
			return;
	}

	arc(centerX, centerY, startAngle, endAngle, r);

	// 恢复原始状态
	setlinestyle(originalLine.linestyle,  originalLine.upattern,  originalLine.thickness);
	setcolor(originalColor);
}

// 矩形绘制
void drawRectangle(int x0, int y0, int h, int w, int isSolid, int borderWidth, int color) {
	int originalColor = getcolor();
	struct linesettingstype originalLine;
	getlinesettings(&originalLine);

	if(isSolid) {
		setfillstyle(SOLID_FILL, color);
		bar(x0 - w/2, y0 - h/2, x0 + w/2, y0 + h/2);  // 绘制填充矩形
		setcolor(color);                               // 设置边框颜色
		setlinestyle(SOLID_LINE, 0, borderWidth);
		rectangle(x0 - w/2, y0 - h/2, x0 + w/2, y0 + h/2);
	} else {
        setcolor(color);                    // 设置线条颜色 
        setlinestyle(SOLID_LINE, 0, borderWidth);
        rectangle(x0 - w/2, y0 - h/2, x0 + w/2, y0 + h/2);
    }
    setlinestyle(originalLine.linestyle,  originalLine.upattern,  originalLine.thickness); 
    setcolor(originalColor);
}
 
// 直线绘制
void drawLine(int x1, int y1, int x2, int y2, int color) {
    int originalColor = getcolor();
    setcolor(color);
	line(x1, y1, x2, y2);
	setcolor(originalColor);
}

#endif


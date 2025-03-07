#ifndef _graphic_h_
#define _graphic_h_

#include<graphics.h>
#include<math.h>
#include<ctype.h>

// ����˵����
// x1,y1 - �������
// x2,y2 - �յ����� 
// r     - Բ���뾶 
// isSolid - �Ƿ���䣺trueʵ��/false����
// borderWidth - �߿���
// convexSide - ͹�෽��'L'��/'R'��/'U'��/'D'�£���Сд���ɣ�
// color - BGI��ɫ������0-15�����Զ����ɫ������ 

// Բ�λ���
void drawCircle(int x0, int y0, int r, int isSolid, int borderWidth, int color) {
	int originalColor = getcolor();
	struct linesettingstype originalLine;
	getlinesettings(&originalLine);

	if(isSolid) {
		setfillstyle(SOLID_FILL, color);    // ���������ɫ
		fillellipse(x0, y0, r, r);          // ����ʵ��Բ
		setcolor(color);                    // ���ñ߿���ɫ
		setlinestyle(SOLID_LINE, 0, borderWidth);
		ellipse(x0, y0, 0, 360, r, r);      // ���Ʊ߿�
	} else {
		setcolor(color);                    // ����������ɫ
		setlinestyle(SOLID_LINE, 0, borderWidth);
		ellipse(x0, y0, 0, 360, r, r);
	}
	setlinestyle(originalLine.linestyle,  originalLine.upattern,  originalLine.thickness);
	setcolor(originalColor);
}

// Բ������
void drawConvexArc(int x1, int y1, int x2, int y2, int r, char convexSide, int color) {
	// ����ԭʼ��ͼ״̬
	int originalColor = getcolor();
	// �����ҳ��ͽǶ�
	float dx = x2 - x1;
	float dy = y2 - y1;
	float chordLength = sqrt(dx*dx + dy*dy);
	// �����ҽǲ���
	float theta = atan2(dy, dx);      // ����X��н�
	float alpha = asin(chordLength/(2*r));  // Բ�Ľǰ��
	// ת��Ϊ�Ƕ��Ʋ�����
	int startAngle = (theta - alpha) * 180/M_PI;  // ��ʼ�Ƕ�
	int endAngle = (theta + alpha) * 180/M_PI;   // ��ֹ�Ƕ�
	//
    float centerX,centerY;

	struct linesettingstype originalLine;
	getlinesettings(&originalLine);
	// ��������ɫ
	setcolor(color);

	// ��Ч����֤
	if(chordLength > 2*r || r <= 0) {
		restorecrtmode();  // �ָ�ԭʼģʽ�������
		closegraph();
		printf("Error: Invalid radius or points distance!");
		return;
	}

	switch(toupper(convexSide)) {
		case 'L':  // ����͹
			centerX = (x1 + x2)/2 - r*sin(theta);
			centerY = (y1 + y2)/2 + r*cos(theta);
			break;
		case 'R':  // ����͹
			centerX = (x1 + x2)/2 + r*sin(theta);
			centerY = (y1 + y2)/2 - r*cos(theta);
			break;
		case 'U':  // ����͹
			centerX = (x1 + x2)/2 + r*cos(theta);
			centerY = (y1 + y2)/2 + r*sin(theta);
			break;
		case 'D':  // ����͹
			centerX = (x1 + x2)/2 - r*cos(theta);
			centerY = (y1 + y2)/2 - r*sin(theta);
			break;
		default:   // �Ƿ�����
			setcolor(originalColor);
			return;
	}

	arc(centerX, centerY, startAngle, endAngle, r);

	// �ָ�ԭʼ״̬
	setlinestyle(originalLine.linestyle,  originalLine.upattern,  originalLine.thickness);
	setcolor(originalColor);
}

// ���λ���
void drawRectangle(int x0, int y0, int h, int w, int isSolid, int borderWidth, int color) {
	int originalColor = getcolor();
	struct linesettingstype originalLine;
	getlinesettings(&originalLine);

	if(isSolid) {
		setfillstyle(SOLID_FILL, color);
		bar(x0 - w/2, y0 - h/2, x0 + w/2, y0 + h/2);  // ����������
		setcolor(color);                               // ���ñ߿���ɫ
		setlinestyle(SOLID_LINE, 0, borderWidth);
		rectangle(x0 - w/2, y0 - h/2, x0 + w/2, y0 + h/2);
	} else {
        setcolor(color);                    // ����������ɫ 
        setlinestyle(SOLID_LINE, 0, borderWidth);
        rectangle(x0 - w/2, y0 - h/2, x0 + w/2, y0 + h/2);
    }
    setlinestyle(originalLine.linestyle,  originalLine.upattern,  originalLine.thickness); 
    setcolor(originalColor);
}
 
// ֱ�߻���
void drawLine(int x1, int y1, int x2, int y2, int color) {
    int originalColor = getcolor();
    setcolor(color);
	line(x1, y1, x2, y2);
	setcolor(originalColor);
}

#endif


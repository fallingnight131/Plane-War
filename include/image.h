#pragma once
#ifndef IMAGE_H
#define IMAGE_H

#include <graphics.h>
#include"settings.h"

const COLORREF TRANSPARENT_COLORS[] = {
    RGB(255, 255, 255),  // ��ɫ
    RGB(0, 0, 0)         // ��ɫ
};



const int NUM_TRANSPARENT_COLORS = sizeof(TRANSPARENT_COLORS) / sizeof(TRANSPARENT_COLORS[0]);

bool isTransparentColor(COLORREF color);											// �����ɫ�Ƿ�Ϊ͸��ɫ
void drawTransparentImage(int x, int y, IMAGE* srcImg);								// �޸ĺ��͸��ͼ����ƺ���
void loadTransparentImage(IMAGE* img, const TCHAR* filename);						// �޸ĺ��ͼ����غ���
int isCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);	// ͼ����ײ��⺯��




#endif // !IMAGE


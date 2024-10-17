#pragma once
#ifndef IMAGE_H
#define IMAGE_H

#include <graphics.h>
#include"settings.h"

const COLORREF TRANSPARENT_COLORS[] = {
    RGB(255, 255, 255),  // 白色
    RGB(0, 0, 0)         // 黑色
};



const int NUM_TRANSPARENT_COLORS = sizeof(TRANSPARENT_COLORS) / sizeof(TRANSPARENT_COLORS[0]);

bool isTransparentColor(COLORREF color);											// 检查颜色是否为透明色
void drawTransparentImage(int x, int y, IMAGE* srcImg);								// 修改后的透明图像绘制函数
void loadTransparentImage(IMAGE* img, const TCHAR* filename);						// 修改后的图像加载函数
int isCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);	// 图像碰撞检测函数




#endif // !IMAGE


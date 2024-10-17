#include"../include/image.h"

// 检查颜色是否为透明色
bool isTransparentColor(COLORREF color) {
    for (int i = 0; i < NUM_TRANSPARENT_COLORS; i++) {
        if (color == BGR(TRANSPARENT_COLORS[i])) {
            return true;
        }
    }
    return false;
}

// 修改后的透明图像绘制函数
void drawTransparentImage(int x, int y, IMAGE* srcImg) {
    DWORD* dst = GetImageBuffer();
    DWORD* src = GetImageBuffer(srcImg);
    int screenWidth = getwidth();
    int screenHeight = getheight();
    int imgWidth = srcImg->getwidth();
    int imgHeight = srcImg->getheight();

    for (int iy = 0; iy < imgHeight; iy++) {
        for (int ix = 0; ix < imgWidth; ix++) {
            int srcX = ix + x;
            int srcY = iy + y;
            if (srcX >= 0 && srcX < screenWidth && srcY >= 0 && srcY < screenHeight) {
                COLORREF color = src[iy * imgWidth + ix] & 0x00FFFFFF;  // 忽略 Alpha 通道
                if (!isTransparentColor(color)) {
                    dst[srcY * screenWidth + srcX] = src[iy * imgWidth + ix];
                }
            }
        }
    }
}


// 修改后的图像加载函数
void loadTransparentImage(IMAGE* img, const TCHAR* filename) {
    loadimage(img, filename);

    DWORD* imgData = GetImageBuffer(img);
    int width = img->getwidth();
    int height = img->getheight();

    for (int i = 0; i < width * height; i++) {
        COLORREF color = imgData[i] & 0x00FFFFFF;
        if (isTransparentColor(color)) {
            imgData[i] &= 0x00FFFFFF;  // 保留颜色信息，但设置 Alpha 为 0（完全透明）
        }
        else {
            imgData[i] |= 0xFF000000;  // 设置 Alpha 为 255（完全不透明）
        }
    }
}

// 图像碰撞检测函数
int isCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
    return !(x1 > x2 + w2 || x1 + w1 < x2 || y1 > y2 + h2 || y1 + h1 < y2);
}
#pragma once
#ifndef PLANE_H
#define PLANE_H

#include"image.h"

// 游戏对象类定义
class Plane {
public:
    int x, y, health, maxHealth;
    int coreX, coreY;
    float speed;  // 新增速度属性
    IMAGE img,imgCore;

    explicit Plane(int startX, int startY, LPCTSTR imagePath, LPCTSTR imagePathCore);
    ~Plane();
    void draw();
    void move(int dx, int dy);
};



#endif // !PLANE_H

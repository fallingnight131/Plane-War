#pragma once
#ifndef BULLET_H

#include"image.h"
#include <math.h>
#include <tchar.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class Bullet {
public:
    int x, y;
    IMAGE img;

    explicit Bullet(int startX, int startY, LPCTSTR imagePath);
    ~Bullet();
    void draw();
    void move(int speed);
};

class EnemyBullet {
public:
    int x, y, angle, img_width, img_height;
    IMAGE img;

    explicit EnemyBullet(int startX, int startY,  LPCTSTR imagePath);
    ~EnemyBullet();
    void draw();
    void move1(int speed);          //直线弹道
    void move2(int centerX, int centerY, int radius, int speed);            //环形弹道
};


#endif // !BULLET_H

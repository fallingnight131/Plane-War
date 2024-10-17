#pragma once
#ifndef ITEM_H
#define ITEM_H

#include <graphics.h>
#include<vector>
#include"plane.h"
#include"enemy.h"
#include"image.h"

// 前向声明
class Plane;
class Enemy;
class Boss;


// 道具类
class Item {
public:
    int x, y;
    int type;
    IMAGE img;
    int duration; // 道具持续时间（对于临时效果）

    explicit Item(int startX, int startY, int itemType);
    ~Item();
    void draw();
    void move(int dy);
    void applyEffect(Plane& player, std::vector<Enemy>& enemies, int& fireRate, int& bulletCount);  // 应用道具效果
    void applyEffectBoss(Plane& player, Boss& boss, int& fireRate, int& bulletCount);  // 应用道具效果
};



#endif // !ITEM_H

#pragma once
#ifndef ITEM_H
#define ITEM_H

#include <graphics.h>
#include<vector>
#include"plane.h"
#include"enemy.h"
#include"image.h"

// ǰ������
class Plane;
class Enemy;
class Boss;


// ������
class Item {
public:
    int x, y;
    int type;
    IMAGE img;
    int duration; // ���߳���ʱ�䣨������ʱЧ����

    explicit Item(int startX, int startY, int itemType);
    ~Item();
    void draw();
    void move(int dy);
    void applyEffect(Plane& player, std::vector<Enemy>& enemies, int& fireRate, int& bulletCount);  // Ӧ�õ���Ч��
    void applyEffectBoss(Plane& player, Boss& boss, int& fireRate, int& bulletCount);  // Ӧ�õ���Ч��
};



#endif // !ITEM_H

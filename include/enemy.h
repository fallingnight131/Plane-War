#pragma once
#ifndef ENEMY_H
#define ENEMY_H

// 定义旋转角度的增量
#define ANGLE_STEP 1

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include <graphics.h>
#include <vector>
#include <iostream>
#include <ctime>
#include <math.h>
#include"image.h"
#include"timer.h"

struct EnemyType {
    int health;
    int speed;
    int score;
    std::string imgPath;

    EnemyType(int h, int s, int sc, std::string path);
};

class Enemy {
public:
    int x, y, health, maxHealth, degree;
    IMAGE img;

    explicit Enemy(int startX, int startY, LPCTSTR imagePath, int startdegree, int maxhealth);
    ~Enemy();
    // 新增的构造函数，使用EnemyType来初始化
    explicit Enemy(const EnemyType& type, int startX, int startY, int startDegree);
    void draw();
    void move(int dy);
};

class Boss {
public:
    int angleX, angleY, x, y, health, maxHealth, degree, img_width, img_height;
    IMAGE img;
    explicit Boss(LPCTSTR imagePath,int maxhealth);
    ~Boss();
    // 新增的构造函数，使用EnemyType来初始化
    void draw();
    void move1(int radius, int speed);
    void move2(int radius, int speed);
    void move3(int radius, int speed);
    void move4(int radius, int speed);
};

// 敌人生成器类
class EnemySpawner {
private:
    int spawnInterval;//生成新敌人的时间间隔
    std::vector<EnemyType> enemyTypes;
public:
    explicit EnemySpawner(int interval, std::vector<EnemyType> types);
    ~EnemySpawner();
    void enemy_update(LevelTimer& timer, std::vector<Enemy>& enemies);
};

#endif // !ENEMY_H

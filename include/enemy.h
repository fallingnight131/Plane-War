#pragma once
#ifndef ENEMY_H
#define ENEMY_H

// ������ת�Ƕȵ�����
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
    // �����Ĺ��캯����ʹ��EnemyType����ʼ��
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
    // �����Ĺ��캯����ʹ��EnemyType����ʼ��
    void draw();
    void move1(int radius, int speed);
    void move2(int radius, int speed);
    void move3(int radius, int speed);
    void move4(int radius, int speed);
};

// ������������
class EnemySpawner {
private:
    int spawnInterval;//�����µ��˵�ʱ����
    std::vector<EnemyType> enemyTypes;
public:
    explicit EnemySpawner(int interval, std::vector<EnemyType> types);
    ~EnemySpawner();
    void enemy_update(LevelTimer& timer, std::vector<Enemy>& enemies);
};

#endif // !ENEMY_H

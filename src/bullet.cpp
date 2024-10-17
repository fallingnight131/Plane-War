#include"../include/bullet.h"

//Bullet
Bullet::Bullet(int startX, int startY, LPCTSTR imagePath):x(startX),y(startY) {
    loadimage(&img, imagePath);
}

Bullet::~Bullet() = default;

void Bullet::draw() {
    drawTransparentImage(x, y, &img);
}

void Bullet::move(int speed) {
    y += speed;
}

//EnemyBullet
EnemyBullet::EnemyBullet(int startX, int startY, LPCTSTR imagePath):x(startX),y(startY) {
    loadimage(&img, imagePath);
    angle = 0;
    // Í¼Æ¬µÄ¿í¸ß
    img_width = img.getwidth();
    img_height = img.getheight();
}

EnemyBullet::~EnemyBullet() = default;

void EnemyBullet::draw() {
    drawTransparentImage(x, y, &img);
}

void EnemyBullet::move1(int speed) {
    y += speed;
}

void EnemyBullet::move2(int centerX,int centerY, int radius, int speed) {
    angle += speed;
    if (angle >= 360) {
        angle -= 360;
    }
    if (angle < 0) {
        angle += 360;
    }
    x = centerX + int(radius * cos(angle * M_PI / 180.0)) - img_width / 2;
    y = centerY + int(radius * sin(angle * M_PI / 180.0)) - img_height / 2;
}
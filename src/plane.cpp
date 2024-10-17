#include"../include/plane.h"

Plane::Plane(int startX, int startY, LPCTSTR imagePath, LPCTSTR imagePathCore):x(startX),y(startY) {
  
    health = maxHealth = 500;
    speed = 5.0f;  // 设置默认速度
    loadimage(&img, imagePath);
    loadimage(&imgCore, imagePathCore);
    coreX = x + img.getwidth() / 2 - imgCore.getwidth() / 2;
    coreY = y + img.getheight() / 2 + 3;
}

Plane::~Plane() = default;

void Plane::draw() {
    drawTransparentImage(x, y, &img);
    drawTransparentImage(coreX,coreY, &imgCore);
    // 绘制血条
    int barWidth = 50;
    int barHeight = 5;
    int healthBarWidth = (health * barWidth) / maxHealth;
    setfillcolor(GREEN);
    solidrectangle(x, y - barHeight - 5, x + healthBarWidth, y - 5);
    setfillcolor(RED);
    solidrectangle(x + healthBarWidth, y - barHeight - 5, x + barWidth, y - 5);
}

void Plane::move(int dx, int dy) {
    float actualDx = dx * speed;
    float actualDy = dy * speed;
    if (x + actualDx >= 0 && x + actualDx <= SCREEN_WIDTH - img.getwidth())
        x += actualDx;
    if (y + actualDy >= 0 && y + actualDy <= SCREEN_HEIGHT - img.getheight())
        y += actualDy;
    coreX = x + img.getwidth() / 2 - imgCore.getwidth() / 2;
    coreY = y + img.getheight() / 2 + 3;
}
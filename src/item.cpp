#include"../include/item.h"

Item::Item(int startX, int startY, int itemType) : x(startX), y(startY), type(itemType), duration(0) 
{
    switch (type) {
    case 0: loadimage(&img, "../resources/images/item_health.bmp"); break;
    case 1: loadimage(&img, "../resources/images/item_fire_rate.bmp"); break;
    case 2: loadimage(&img, "../resources/images/item_bullet_count.bmp"); break;
    case 3: loadimage(&img, "../resources/images/item_speed.bmp"); break;
    case 4: loadimage(&img, "../resources/images/item_clear_enemies.bmp"); break;
    default: loadimage(&img, "../resources/images/item_default.bmp"); break;
    }
}

Item::~Item() = default;

void Item::draw() {
    drawTransparentImage(x, y, &img);
}

void Item::move(int dy) {
    y += dy;
}

// Ӧ�õ���Ч��
void Item::applyEffect(Plane& player, std::vector<Enemy>& enemies, int& fireRate, int& bulletCount) {
    switch (type) {
    case 0: // ��������
        player.health = (std::min)(player.maxHealth, player.health + 20);
        break;
    case 1: // ��������
        fireRate = (std::max)(1, fireRate - 2);
        duration = 1000;
        break;
    case 2: // �����ӵ�����
        bulletCount = (std::min)(5, bulletCount + 1);
        duration = 10000;
        break;
    case 3: // �����ƶ��ٶ�
        player.speed = (std::min)(10.0, player.speed * 1.2);
        duration = 1000;
        break;
    case 4: // �������
        enemies.clear();
        break;
    }
}

void Item::applyEffectBoss(Plane& player, Boss& boss, int& fireRate, int& bulletCount) {
    switch (type) {
    case 0: // ��������
        player.health = (std::min)(player.maxHealth, player.health + 100);
        break;
    case 1: // ��������
        fireRate = (std::max)(1, fireRate - 2);
        duration = 1000;
        break;
    case 2: // �����ӵ�����
        bulletCount = (std::min)(5, bulletCount + 1);
        duration = 10000;
        break;
    case 3: // �����ƶ��ٶ�
        player.speed = (std::min)(10.0, player.speed * 1.2);
        duration = 1000;
        break;
    case 4: // �������
        boss.health -= 2000;
        break;
    }
}
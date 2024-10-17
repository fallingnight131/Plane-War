#include"../include/enemy.h"

//EnemyType
EnemyType::EnemyType(int h, int s, int sc, std::string path)
    : health(h), speed(s), score(sc), imgPath(path) {}

//Enemy
Enemy::Enemy(int startX, int startY, LPCTSTR imagePath, int startdegree, int maxhealth)
    :x(startX),y(startY),degree(startdegree),maxHealth(maxhealth),health(maxhealth){
    loadimage(&img, imagePath);
}

// 新增的构造函数，使用EnemyType来初始化
Enemy::Enemy(const EnemyType& type, int startX, int startY, int startDegree)
    : x(startX), y(startY), health(type.health), maxHealth(type.health), degree(startDegree) 
{
    // 使用EnemyType中的imgPath来加载图片    
    loadimage(&img, type.imgPath.c_str()); // Assuming loadimage expects LPCTSTR
}

Enemy::~Enemy() = default;

void Enemy::draw() {
    drawTransparentImage(x, y, &img);
    // 绘制血条
    int barWidth = 50;
    int barHeight = 5;
    int healthBarWidth = (health * barWidth) / maxHealth;
    setfillcolor(GREEN);
    solidrectangle(x, y - barHeight - 5, x + healthBarWidth, y - 5);
    setfillcolor(RED);
    solidrectangle(x + healthBarWidth, y - barHeight - 5, x + barWidth, y - 5);
}

void Enemy::move(int dy) {
    y += dy;
}

//Boss
Boss::Boss(LPCTSTR imagePath, int maxhealth)
    : maxHealth(maxhealth), health(maxhealth) {
    loadimage(&img, imagePath);
    // 图片的宽高
    angleX = 270;
    angleY = 270;
    img_width = img.getwidth();
    img_height = img.getheight();
    // 计算当前角度的x和y偏移
    x = 300 + int((300 - img_width / 3) * cos(angleX * M_PI / 180.0)) - img_width / 2;
    y = 400 + int((400 - img_height / 2) * sin(angleY * M_PI / 180.0)) - img_height / 2;
}

Boss::~Boss() = default;

void Boss::draw() { 
    // 绘制血条
    int barWidth = 500;
    int barHeight = 20;
    int healthBarWidth = (health * barWidth) / maxHealth;
    setfillcolor(YELLOW);
    solidrectangle(50, 10, 50 + healthBarWidth, 10+barHeight);
    setfillcolor(RED);
    solidrectangle(50 + healthBarWidth, 10, 50 + barWidth, 10+barHeight);
    drawTransparentImage(x, y, &img);
}

void Boss::move1(int radius, int speed) {
    angleX += speed;
    if (angleX >= 360) {
        angleX -= 360;
    }
    x = 300 + int((radius - img_width / 3) * cos(angleX * M_PI / 180.0)) - img_width / 2;
}

void Boss::move2(int radius, int speed) {
    angleX -= speed;
    if (angleX < 0) {
        angleX += 360;
    }
    x = 300 + int((radius - img_width / 3) * cos(angleX * M_PI / 180.0)) - img_width / 2;
}

void Boss::move3(int radius, int speed) {
    angleY += speed;
    if (angleY >= 360) {
        angleY -= 360;
    }
    y = 400 + int((radius - img_height / 2) * sin(angleY * M_PI / 180.0)) - img_height / 2;
}

void Boss::move4(int radius, int speed) {
    angleY -= speed;
    if (angleX < 0) {
        angleX += 360;
    }
    y = 400 + int((radius - img_height / 2) * sin(angleY * M_PI / 180.0)) - img_height / 2;
}


//EnemySpawner
EnemySpawner::EnemySpawner(int interval, std::vector<EnemyType> types) : spawnInterval(interval), enemyTypes(types) {}

EnemySpawner::~EnemySpawner() = default;

void EnemySpawner::enemy_update(LevelTimer& timer, std::vector<Enemy>& enemies) {
    // 根据计时器的时间和生成间隔，决定是否生成新的敌人
    if (timer.getElapsedTime() % spawnInterval == 0) {
        // 生成新敌人并添加到敌人列表
        // 假设我们随机选择一种敌人类型来生成
        int typeIndex = rand() % enemyTypes.size();
        EnemyType& selectedType = enemyTypes[typeIndex];
        int startX = 1;
        int startY = 2;
        int startdegree = 3;
        Enemy newEnemy(selectedType, startX, startY, startdegree);// 根据enemyTypes[typeIndex]初始化新敌人
        enemies.push_back(newEnemy);
    }
}
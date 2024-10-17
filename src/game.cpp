#include"../include/game.h"

// 游戏主循环
void gameLoop1(int level) {
    playMusic(_T("../resources/sounds/fight.mp3"));
    Plane player(400, 500, "../resources/images/plane1.bmp", "../resources/images/core.bmp");
    std::vector<Bullet> bullets;
    std::vector<Enemy> enemies;
    std::vector<EnemyBullet> enemyBullets;
    std::vector<Item> items;
    std::vector<IMAGE> backgrounds; // 背景图像
    int fireRate = 10; // 发射间隔，帧数
    int bulletCount = 1; // 每次发射的子弹数量
    std::vector<Item> activeItems; // 当前激活的道具效果
    int epoch = 0;
    int score = 0;
    int aimScore = 400 + level * 200;
    bool isPaused = false;
    IMAGE background;

    BeginBatchDraw();   //执行批量绘画（防止过度闪屏）  结束为EndBatchDraw
    while (true) {
        switch (level) {
        case 1: case 2: loadimage(&background, _T("../resources/images/background1.bmp")); break;
        case 3: case 4: loadimage(&background, _T("../resources/images/background2.bmp")); break;
        case 5: case 6: loadimage(&background, _T("../resources/images/background3.bmp")); break;
        case 7: case 8: loadimage(&background, _T("../resources/images/background4.bmp")); break;
        default: loadimage(&background, _T("../resources/images/background1.bmp")); break;
        }



        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            if (!gamestop(level)) break;
            isPaused = false;
            FlushBatchDraw();
        }

        // 处理暂停键
        if (GetAsyncKeyState('P') & 0x8000) {
            isPaused = !isPaused;
            if (isPaused) {
                putimage(0, 0, &background);
                // 更新道具绘制
                for (auto& item : items) {
                    item.draw();
                }
                // 更新敌机绘制
                for (auto& enemy : enemies) {
                    enemy.draw();
                }
                // 更新敌机子弹绘制
                for (auto& bullet : enemyBullets) {
                    bullet.draw();
                }
                //更新玩家子弹绘制
                for (auto& bullet : bullets) {
                    bullet.draw();
                }
                // 绘制玩家飞机
                player.draw();
                // 绘制分数
                TCHAR scoreText[20];
                _stprintf_s(scoreText, _T("Score: %d"), score);
                settextcolor(BLACK);
                settextstyle(20, 0, _T("Consolas"));
                outtextxy(10, 10, scoreText);

                //绘制暂停提醒
                settextcolor(YELLOW);
                settextstyle(40, 0, _T("Consolas"));
                outtextxy(200, 250, _T("Game Paused"));
                outtextxy(150, 300, _T("Press P to Resume"));
                FlushBatchDraw();
            }
            else {
                cleardevice();
            }
            Sleep(200);
        }


        if (!isPaused) {
            putimage(0, 0, &background);
            // 处理用户输入
            if (GetAsyncKeyState(VK_LEFT) & 0x8000) player.move(-1, 0);
            if (GetAsyncKeyState(VK_RIGHT) & 0x8000) player.move(1, 0);
            if (GetAsyncKeyState(VK_UP) & 0x8000) player.move(0, -1);
            if (GetAsyncKeyState(VK_DOWN) & 0x8000) player.move(0, 1);

            // 处理射击
            if (GetAsyncKeyState(VK_SPACE) & 0x8000 && epoch % fireRate == 0) {
                for (int i = 0; i < bulletCount; i++) {
                    int offset = (i - (bulletCount - 1) / 2.0) * 20; // 子弹之间的间隔
                    bullets.emplace_back(player.x + player.img.getwidth() / 2 + offset, player.y, _T("../resources/images/bullet.bmp"));
                }
            }

            // 敌机生成
            switch (level) {
            case 1:
                if (epoch % 32 == 0) {
                    enemies.emplace_back(rand() % (SCREEN_WIDTH - 100), -rand() % 100, _T("../resources/images/enemy.bmp"), 0, 50);
                }
                if (epoch % 640 == 0) {
                    enemies.emplace_back(rand() % (SCREEN_WIDTH - 100), -rand() % 100, _T("../resources/images/enemy1.bmp"), 1, 100);
                }

                break;
            case 2:
                if (epoch % 31 == 0) {
                    enemies.emplace_back(rand() % (SCREEN_WIDTH - 100), -rand() % 100, _T("../resources/images/enemy2.bmp"), 0, 80);
                }
                if (epoch % 620 == 0) {
                    enemies.emplace_back(rand() % (SCREEN_WIDTH - 100), -rand() % 100, _T("../resources/images/enemy3.bmp"), 1, 160);
                }
                break;
            case 3:
                if (epoch % 30 == 0) {
                    enemies.emplace_back(rand() % (SCREEN_WIDTH - 100), -rand() % 100, _T("../resources/images/enemy4.bmp"), 0, 110);
                }
                if (epoch % 600 == 0) {
                    enemies.emplace_back(rand() % (SCREEN_WIDTH - 100), -rand() % 100, _T("../resources/images/enemy5.bmp"), 1, 220);
                }
                break;
            case 4:
                if (epoch % 29 == 0) {
                    enemies.emplace_back(rand() % (SCREEN_WIDTH - 100), -rand() % 100, _T("../resources/images/enemy6.bmp"), 0, 140);
                }
                if (epoch % 580 == 0) {
                    enemies.emplace_back(rand() % (SCREEN_WIDTH - 100), -rand() % 100, _T("../resources/images/enemy7.bmp"), 1, 280);
                }
                break;
            case 5:
                if (epoch % 28 == 0) {
                    enemies.emplace_back(rand() % (SCREEN_WIDTH - 100), -rand() % 100, _T("../resources/images/enemy8.bmp"), 0, 170);
                }
                if (epoch % 560 == 0) {
                    enemies.emplace_back(rand() % (SCREEN_WIDTH - 100), -rand() % 100, _T("../resources/images/enemy9.bmp"), 1, 340);
                }
                break;
            case 6:
                if (epoch % 27 == 0) {
                    enemies.emplace_back(rand() % (SCREEN_WIDTH - 100), -rand() % 100, _T("../resources/images/enemy.bmp"), 0, 200);
                }
                if (epoch % 540 == 0) {
                    enemies.emplace_back(rand() % (SCREEN_WIDTH - 100), -rand() % 100, _T("../resources/images/enemy1.bmp"), 1, 400);
                }
                break;
            case 7:
                if (epoch % 26 == 0) {
                    enemies.emplace_back(rand() % (SCREEN_WIDTH - 100), -rand() % 100, _T("../resources/images/enemy2.bmp"), 0, 230);
                }
                if (epoch % 520 == 0) {
                    enemies.emplace_back(rand() % (SCREEN_WIDTH - 100), -rand() % 100, _T("../resources/images/enemy3.bmp"), 1, 460);
                }
                break;
            case 8:
                if (epoch % 25 == 0) {
                    enemies.emplace_back(rand() % (SCREEN_WIDTH - 100), -rand() % 100, _T("../resources/images/enemy4.bmp"), 0, 250);
                }
                if (epoch % 500 == 0) {
                    enemies.emplace_back(rand() % (SCREEN_WIDTH - 100), -rand() % 100, _T("../resources/images/enemy5.bmp"), 1, 500);
                }
                break;
            }

            // 敌机射击
            switch (level) {
            case 1:
                if (epoch % 150 == 0) {
                    for (auto& enemy : enemies) {
                        if (!(rand() % 10)) {
                            enemyBullets.emplace_back(enemy.x + enemy.img.getwidth() / 2 - 3, enemy.y + enemy.img.getheight(), _T("../resources/images/bullet.bmp"));
                        }
                    }
                }
                break;
            case 2:
                if (epoch % 140 == 0) {
                    for (auto& enemy : enemies) {
                        if (!(rand() % 9)) {
                            enemyBullets.emplace_back(enemy.x + enemy.img.getwidth() / 2 - 3, enemy.y + enemy.img.getheight(), _T("../resources/images/bullet.bmp"));
                        }
                    }
                }
                break;
            case 3:
                if (epoch % 130 == 0) {
                    for (auto& enemy : enemies) {
                        if (!(rand() % 8)) {
                            enemyBullets.emplace_back(enemy.x + enemy.img.getwidth() / 2 - 3, enemy.y + enemy.img.getheight(), _T("../resources/images/bullet.bmp"));
                        }
                    }
                }
                break;
            case 4:
                if (epoch % 120 == 0) {
                    for (auto& enemy : enemies) {
                        if (!(rand() % 7)) {
                            enemyBullets.emplace_back(enemy.x + enemy.img.getwidth() / 2 - 3, enemy.y + enemy.img.getheight(), _T("../resources/images/bullet.bmp"));
                        }
                    }
                }
                break;
            case 5:
                if (epoch % 110 == 0) {
                    for (auto& enemy : enemies) {
                        if (!(rand() % 6)) {
                            enemyBullets.emplace_back(enemy.x + enemy.img.getwidth() / 2 - 3, enemy.y + enemy.img.getheight(), _T("../resources/images/bullet.bmp"));
                        }
                    }
                }
                break;
            case 6:
                if (epoch % 100 == 0) {
                    for (auto& enemy : enemies) {
                        if (!(rand() % 5)) {
                            enemyBullets.emplace_back(enemy.x + enemy.img.getwidth() / 2 - 3, enemy.y + enemy.img.getheight(), _T("../resources/images/bullet.bmp"));
                        }
                    }
                }
                break;
            case 7:
                if (epoch % 90 == 0) {
                    for (auto& enemy : enemies) {
                        if (!(rand() % 4)) {
                            enemyBullets.emplace_back(enemy.x + enemy.img.getwidth() / 2 - 3, enemy.y + enemy.img.getheight(), _T("../resources/images/bullet.bmp"));
                        }
                    }
                }
                break;
            case 8:
                if (epoch % 80 == 0) {
                    for (auto& enemy : enemies) {
                        if (!(rand() % 4)) {
                            enemyBullets.emplace_back(enemy.x + enemy.img.getwidth() / 2 - 3, enemy.y + enemy.img.getheight(), _T("../resources/images/bullet.bmp"));
                        }
                    }
                }
                break;
            }


            // 道具生成
            if (epoch % 200 == 0) {
                int itemType = rand() % 5; // 随机选择道具类型
                items.emplace_back(rand() % (SCREEN_WIDTH - 100), -rand() % 100, itemType);
            }


            //更新玩家子弹位置和绘制
            for (auto& bullet : bullets) {
                bullet.move(-20);
                bullet.draw();
            }

            // 更新道具位置和绘制
            for (auto& item : items) {
                item.move(1);
                item.draw();
            }

            // 删除屏幕外的子弹
            bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](Bullet& b) { return b.y < 0; }), bullets.end());

            // 更新敌机位置和绘制
            for (auto& enemy : enemies) {
                enemy.move(1);
                enemy.draw();
            }

            // 删除屏幕外的敌机
            enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](Enemy& e) { return e.y > SCREEN_HEIGHT; }), enemies.end());

            // 更新敌机子弹位置和绘制
            for (auto& bullet : enemyBullets) {
                bullet.move1(2);
                bullet.draw();
            }

            // 删除屏幕外的敌机子弹
            enemyBullets.erase(std::remove_if(enemyBullets.begin(), enemyBullets.end(), [](EnemyBullet& b) { return b.y > SCREEN_HEIGHT; }), enemyBullets.end());



            // 删除屏幕外的道具
            items.erase(std::remove_if(items.begin(), items.end(), [](Item& i) { return i.y > SCREEN_HEIGHT; }), items.end());

            // 检测道具与玩家的碰撞
            for (auto& item : items) {
                if (isCollision(item.x, item.y, item.img.getwidth(), item.img.getheight(),
                    player.x, player.y, player.img.getwidth(), player.img.getheight())) {
                    item.applyEffect(player, enemies, fireRate, bulletCount);
                    if (item.duration > 0) {
                        activeItems.push_back(item);
                    }
                    item.y = SCREEN_HEIGHT + 10; // 标记为超出屏幕
                }
            }

            // 更新激活的道具效果
            for (auto it = activeItems.begin(); it != activeItems.end();) {
                it->duration--;
                if (it->duration <= 0) {
                    // 道具效果结束，恢复原状
                    switch (it->type) {
                    case 1: fireRate = (std::min)(10,fireRate+2); break;
                    case 2: bulletCount = (std::max)(1,bulletCount-1); break;
                    case 3: player.speed = (std::max)(5.0f, player.speed / 1.2f); break;
                    }
                    it = activeItems.erase(it);
                }
                else {
                    ++it;
                }
            }

            // 检测敌机与玩家子弹的碰撞
            for (auto& bullet : bullets) {
                for (auto& enemy : enemies) {
                    if (isCollision(bullet.x, bullet.y, bullet.img.getwidth(), bullet.img.getheight(), enemy.x, enemy.y, enemy.img.getwidth(), enemy.img.getheight())) {
                        bullet.y = -10; // 将子弹标记为超出屏幕
                        enemy.health -= 30; // 减少敌人生命值
                        if (enemy.health <= 0) {
                            enemy.y = 810; // 将敌机标记为超出屏幕
                            score += 10;   // 增加得分
                        }
                    }
                }
            }

            // 检测敌机子弹与玩家飞机的碰撞
            for (auto& bullet : enemyBullets) {
                if (isCollision(bullet.x, bullet.y, bullet.img.getwidth(), bullet.img.getheight(), player.x, player.y, player.img.getwidth(), player.img.getheight())) {
                    bullet.y = SCREEN_HEIGHT + 10; // 标记敌机子弹为销毁
                    player.health -= 10; // 减少玩家生命值
                    if (player.health <= 0) {
                        FlushBatchDraw();
                        Sleep(1000);
                        EndBatchDraw();
                        gameend1(level);
                        setfillcolor(WHITE);
                        return;
                    }
                }
            }


            // 绘制玩家飞机
            player.draw();

            // 绘制分数
            TCHAR scoreText[20];
            settextcolor(YELLOW);
            settextstyle(20, 0, _T("Consolas"));
            _stprintf_s(scoreText, _T("Aim Score: %d"), aimScore);
            outtextxy(10, 10, scoreText);
            _stprintf_s(scoreText, _T("Your Score: %d\n"), score);
            outtextxy(10, 40, scoreText);

            // 检测得分是否满足胜利条件
            if (score >= aimScore) {
                FlushBatchDraw();
                Sleep(1000);
                EndBatchDraw();
                gameend2(level);
                setfillcolor(WHITE);
                return;
            }

            // 延时
            Sleep(10);
            epoch++;
            // 刷新屏幕
            FlushBatchDraw();
            cleardevice();

        }
    }
    EndBatchDraw();
}

void gameLoopBoss() {
    playMusic(_T("../resources/sounds/boss.mp3"));
    Plane player(400, 500, "../resources/images/plane1.bmp", "../resources/images/core.bmp");
    Boss boss("../resources/images/boss.bmp", 20000);
    std::vector<Bullet> bullets;
    std::vector<EnemyBullet> bossBulletsQik;       //快速光弹
    std::vector<EnemyBullet> bossBulletsMid;       //中速光弹
    std::vector<EnemyBullet> bossBulletsSlo;       //慢速光弹
    std::vector<EnemyBullet> bossBulletsMis;       //导弹
    std::vector<EnemyBullet> bossBulletsCir1;       //环圈光弹（内）
    std::vector<EnemyBullet> bossBulletsCir2;       //环圈光弹（中）
    std::vector<EnemyBullet> bossBulletsCir3;       //环圈光弹（外）
    std::vector<EnemyBullet> bossBulletsDef;        //环身防御盾
    std::vector<Item> items;
    std::vector<IMAGE> backgrounds; // 背景图像
    int fireRate = 10; // 发射间隔，帧数
    int bulletCount = 1; // 每次发射的子弹数量
    std::vector<Item> activeItems; // 当前激活的道具效果
    int epoch = 0;
    int cycle = 0;
    bool bossDef = 0;
    bool bossCir = 0;
    bool isPaused = false;
    IMAGE background;

    BeginBatchDraw();   //执行批量绘画（防止过度闪屏）  结束为EndBatchDraw
    while (true) {
        loadimage(&background, "../resources/images/background4.bmp");



        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            if (!gamestop(9)) break;
            isPaused = false;
            FlushBatchDraw();
        }

        // 处理暂停键
        if (GetAsyncKeyState('P') & 0x8000) {
            isPaused = !isPaused;
            if (isPaused) {
                putimage(0, 0, &background);
                // 更新道具位置和绘制
                for (auto& item : items) {
                    item.draw();
                }
                // 更新boss绘制
                boss.draw();
                // 更新boss子弹绘制
                for (auto& bullet : bossBulletsQik) {
                    bullet.draw();
                }
                for (auto& bullet : bossBulletsMid) {
                    bullet.draw();
                }
                for (auto& bullet : bossBulletsDef) {
                    bullet.draw();
                }
                for (auto& bullet : bossBulletsMis) {
                    bullet.draw();
                }
                for (auto& bullet : bossBulletsCir1) {
                    bullet.draw();
                }
                for (auto& bullet : bossBulletsCir2) {
                    bullet.draw();
                }
                for (auto& bullet : bossBulletsCir3) {
                    bullet.draw();
                }
                //更新玩家子弹位置和绘制
                for (auto& bullet : bullets) {
                    bullet.draw();
                }
                // 绘制玩家飞机
                player.draw();

                //绘制暂停提醒
                settextcolor(YELLOW);
                settextstyle(40, 0, _T("Consolas"));
                outtextxy(200, 250, _T("Game Paused"));
                outtextxy(150, 300, _T("Press P to Resume"));
                FlushBatchDraw();
            }
            else {
                cleardevice();
            }
            Sleep(200);
        }


        if (!isPaused) {
            putimage(0, 0, &background);
            // 处理用户输入
            if (GetAsyncKeyState(VK_LEFT) & 0x8000) player.move(-1, 0);
            if (GetAsyncKeyState(VK_RIGHT) & 0x8000) player.move(1, 0);
            if (GetAsyncKeyState(VK_UP) & 0x8000) player.move(0, -1);
            if (GetAsyncKeyState(VK_DOWN) & 0x8000) player.move(0, 1);

            // 处理射击
            if (GetAsyncKeyState(VK_SPACE) & 0x8000 && epoch % fireRate == 0) {
                for (int i = 0; i < bulletCount; i++) {
                    int offset = (i - (bulletCount - 1) / 2.0) * 20; // 子弹之间的间隔
                    bullets.emplace_back(player.x + player.img.getwidth() / 2 + offset, player.y, _T("../resources/images/bullet.bmp"));
                }
            }

            //boss行动
            if (!bossDef){
                if (epoch == 0 || epoch == 60 || epoch == 120 || epoch == 180 || epoch == 240 || epoch == 300){
                    bossBulletsDef.emplace_back(boss.x + boss.img.getwidth() / 2, boss.y + boss.img.getheight(), _T("../resources/images/trangle.bmp"));
                }
                if (epoch == 360){
                    bossDef = 1;
                }
            }
            if (epoch > 100 && epoch <= 820) {
                boss.move2(SCREEN_WIDTH/2, 1);
                //射击高速弹
                if (boss.angleX < 270 && boss.angleX >= 180 || boss.angleX < 90 && boss.angleX >= 0) {
                    if (epoch % 10 == 0) {
                        for (int i = 0; i < 5; i++) {
                            int offset = (i - (4.5) / 2.0) * 20; // 子弹之间的间隔
                            bossBulletsQik.emplace_back(boss.x + boss.img.getwidth() / 2 + offset, boss.y + boss.img.getheight(), _T("../resources/images/bullet1.bmp"));
                        }

                    }
                }
            }
            if (epoch > 820 && epoch <= 835) {
                boss.move3(SCREEN_HEIGHT / 2, 8);
                
            }
            if (epoch > 835 && epoch <= 850) {
                boss.move4(SCREEN_HEIGHT / 2, 8);

            }
            if (epoch > 850 && epoch <= 1210) {
                boss.move2(SCREEN_WIDTH / 3, 1);
                //射击高速弹
                if (epoch % 10 == 0) {
                    for (int i = 0; i < 2; i++) {
                        int offset = (i - (1) / 2.0) * 150; // 子弹之间的间隔
                        bossBulletsMid.emplace_back(boss.x + boss.img.getwidth() / 2 + offset, boss.y + boss.img.getheight(), _T("../resources/images/bullet1.bmp"));
                    }

                }
            }
            if (epoch > 1210 && epoch <= 1282) {
                boss.move2(SCREEN_WIDTH / 3, 5);
                //射击导弹
                if (epoch == 1230) {
                    bossBulletsMis.emplace_back(0,0, _T("../resources/images/missile.bmp"));
                }
                if (epoch == 1260) {
                    bossBulletsMis.emplace_back(100, 0, _T("../resources/images/missile.bmp"));
                }
            }
            if (epoch > 1282 && epoch <= 1354) {
                boss.move2(SCREEN_WIDTH / 2, 5);
                //射击导弹
                if (epoch == 1302) {
                    bossBulletsMis.emplace_back(200, 0, _T("../resources/images/missile.bmp"));
                }
                if (epoch == 1332) {
                    bossBulletsMis.emplace_back(300, 0, _T("../resources/images/missile.bmp"));
                }
            }
            if (epoch > 1354 && epoch <= 1426) {
                boss.move2(SCREEN_WIDTH / 2, 5);
                if(epoch > 1354 && epoch <= 1363|| epoch > 1372 && epoch <= 1381) boss.move3(SCREEN_HEIGHT / 2, 5);
                if (epoch > 1363 && epoch <= 1372 || epoch > 1381 && epoch <= 1390) boss.move4(SCREEN_HEIGHT / 2, 5);
                //射击导弹
                if (epoch == 1374) {
                    bossBulletsMis.emplace_back(400, 0, _T("../resources/images/missile.bmp"));
                }
                if (epoch == 1404) {
                    bossBulletsMis.emplace_back(500, 0, _T("../resources/images/missile.bmp"));
                }
            }
            if (epoch > 1440 && epoch <= 1530) {
                boss.move2(SCREEN_WIDTH / 2, 1);
            }
            if (epoch > 1530 && epoch <= 1602) {
                boss.move3(SCREEN_HEIGHT / 2, 5);
            }
            if (epoch > 1602 && epoch <= 1782) {
                boss.move2(SCREEN_WIDTH / 2, 1);
            }
            if (epoch > 1782 && epoch <= 1854) {
                boss.move3(SCREEN_HEIGHT / 2, 5);
            }
            if (epoch > 1854 && epoch <= 2034) {
                boss.move2(SCREEN_WIDTH / 2, 1);
            }
            if (epoch > 2034 && epoch <= 2106) {
                boss.move3(SCREEN_HEIGHT / 2, 5);
            }
            if (epoch > 2106 && epoch <= 2286) {
                boss.move2(SCREEN_WIDTH / 2, 1);
            }
            if (epoch > 2286 && epoch <= 2358) {
                boss.move3(SCREEN_HEIGHT / 2, 5);
            }
            if (epoch > 2358 && epoch <= 2448) {
                boss.move2(SCREEN_WIDTH / 2, 1);
            }
            if (epoch > 2450 && epoch <= 2990) {
                boss.move2(SCREEN_WIDTH / 2, 1);
                //射击慢速弹
                if (!(boss.angleX%90)) {
                    for (int i = 0; i < 5; i++) {
                        int offset = (i - (4.5) / 2.0) * 20; // 子弹之间的间隔
                        bossBulletsSlo.emplace_back(boss.x + boss.img.getwidth() / 2 + offset, boss.y + boss.img.getheight(), _T("../resources/images/bullet1.bmp"));
                    }
                }
                if (cycle >= 0) {
                    if (!bossCir) {
                        if (epoch == 2510 || epoch == 2570 || epoch == 2630) {
                            bossBulletsCir1.emplace_back(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200, _T("../resources/images/bullet2.bmp"));
                        }
                        if (epoch == 2660 || epoch == 2690 || epoch == 2720 || epoch == 2750 || epoch == 2780 || epoch == 2810) {
                            bossBulletsCir2.emplace_back(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 300, _T("../resources/images/bullet2.bmp"));
                        }
                        if (epoch == 2830 || epoch == 2850 || epoch == 2870 || epoch == 2890 || epoch == 2910 || epoch == 2930 || epoch == 2950 || epoch == 2970 || epoch == 2990) {
                            bossBulletsCir3.emplace_back(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 400, _T("../resources/images/bullet2.bmp"));
                        }
                        if (epoch == 2990) {
                            bossCir = 1;
                        }
                    }
               }
            }



            // 道具生成
            if (epoch % 200 == 0) {
                int itemType = rand() % 5; // 随机选择道具类型
                items.emplace_back(rand() % (SCREEN_WIDTH - 100), -rand() % 100, itemType);
            }



            for (auto& bullet : bullets) {
                bullet.move(-20);
                bullet.draw();
            }

            // 更新道具位置和绘制
            for (auto& item : items) {
                item.move(1);
                item.draw();
            }

            // 删除屏幕外的子弹
            bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](Bullet& b) { return b.y < 0; }), bullets.end());

            // 更新boss绘制
            boss.draw();

            
            // 更新敌机子弹位置和绘制
            for (auto& bullet : bossBulletsQik) {
                bullet.move1(20);
                bullet.draw();
            }
            for (auto& bullet : bossBulletsMid) {
                bullet.move1(10);
                bullet.draw();
            }
            for (auto& bullet : bossBulletsSlo) {
                bullet.move1(2);
                bullet.draw();
            }
            for (auto& bullet : bossBulletsDef) {
                bullet.move2(boss.x + boss.img_width / 2, boss.y + boss.img_height / 2, (std::max)(boss.img_height / 2, boss.img_width / 2), 1);
                bullet.draw();
            }
            for (auto& bullet : bossBulletsMis) {
                bullet.move1(10);
                bullet.draw();
            }
            for (auto& bullet : bossBulletsCir1) {
                bullet.move2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 150, 2);
                bullet.draw();
            }
            for (auto& bullet : bossBulletsCir2) {
                bullet.move2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 300, -2);
                bullet.draw();
            }
            for (auto& bullet : bossBulletsCir3) {
                bullet.move2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 450, 2);
                bullet.draw();
            }


            // 删除屏幕外的敌机子弹
            bossBulletsQik.erase(std::remove_if(bossBulletsQik.begin(), bossBulletsQik.end(), [](EnemyBullet& b) { return b.y > SCREEN_HEIGHT; }), bossBulletsQik.end());

            bossBulletsMid.erase(std::remove_if(bossBulletsMid.begin(), bossBulletsMid.end(), [](EnemyBullet& b) { return b.y > SCREEN_HEIGHT; }), bossBulletsMid.end());

            bossBulletsSlo.erase(std::remove_if(bossBulletsSlo.begin(), bossBulletsSlo.end(), [](EnemyBullet& b) { return b.y > SCREEN_HEIGHT; }), bossBulletsSlo.end());

            bossBulletsMis.erase(std::remove_if(bossBulletsMis.begin(), bossBulletsMis.end(), [](EnemyBullet& b) { return b.y > SCREEN_HEIGHT; }), bossBulletsMis.end());

            // 删除屏幕外的道具
            items.erase(std::remove_if(items.begin(), items.end(), [](Item& i) { return i.y > SCREEN_HEIGHT; }), items.end());

            // 检测道具与玩家的碰撞
            for (auto& item : items) {
                if (isCollision(item.x, item.y, item.img.getwidth(), item.img.getheight(),
                    player.x, player.y, player.img.getwidth(), player.img.getheight())) {
                    item.applyEffectBoss(player, boss, fireRate, bulletCount);
                    if (item.duration > 0) {
                        activeItems.push_back(item);
                    }
                    item.y = SCREEN_HEIGHT + 10; // 标记为超出屏幕
                }
            }

            // 更新激活的道具效果
            for (auto it = activeItems.begin(); it != activeItems.end();) {
                it->duration--;
                if (it->duration <= 0) {
                    // 道具效果结束，恢复原状
                    switch (it->type) {
                    case 1: fireRate = 10; break;
                    case 2: bulletCount = 1; break;
                    case 3: player.speed = (std::max)(5.0, player.speed / 1.2); break;
                    }
                    it = activeItems.erase(it);
                }
                else {
                    ++it;
                }
            }
            // 检测环身盾与玩家子弹的碰撞
            for (auto& bullet : bullets) {
                for (auto& def : bossBulletsDef) {
                    if (isCollision(bullet.x, bullet.y, bullet.img.getwidth(), bullet.img.getheight(), def.x, def.y, def.img.getwidth(), def.img.getheight())) {
                        bullet.y = -10; // 将子弹标记为超出屏幕
                    }
                }
            }
            // 检测敌机与玩家子弹的碰撞
            for (auto& bullet : bullets) {
                if (isCollision(bullet.x, bullet.y, bullet.img.getwidth(), bullet.img.getheight(), boss.x, boss.y, boss.img.getwidth(), boss.img.getheight())) {
                    bullet.y = -10; // 将子弹标记为超出屏幕
                    boss.health -= 20; // 减少敌人生命值
                    
                }
            }

            // 检测敌机子弹与玩家飞机的碰撞
            for (auto& bullet : bossBulletsQik) {
                if (isCollision(bullet.x, bullet.y, bullet.img.getwidth(), bullet.img.getheight(), player.coreX, player.coreY, player.imgCore.getwidth(), player.imgCore.getheight())) {
                    bullet.y = SCREEN_HEIGHT + 10; // 标记敌机子弹为销毁
                    player.health -= 10; // 减少玩家生命值
                    if (player.health <= 0) {
                        FlushBatchDraw();
                        Sleep(1000);
                        EndBatchDraw();
                        gameend1(9);
                        setfillcolor(WHITE);
                        return;
                    }
                }
            }
            for (auto& bullet : bossBulletsMid) {
                if (isCollision(bullet.x, bullet.y, bullet.img.getwidth(), bullet.img.getheight(), player.coreX, player.coreY, player.imgCore.getwidth(), player.imgCore.getheight())) {
                    bullet.y = SCREEN_HEIGHT + 10; // 标记敌机子弹为销毁
                    player.health -= 10; // 减少玩家生命值
                    if (player.health <= 0) {
                        FlushBatchDraw();
                        Sleep(1000);
                        EndBatchDraw();
                        gameend1(9);
                        setfillcolor(WHITE);
                        return;
                    }
                }
            }
            for (auto& bullet : bossBulletsSlo) {
                if (isCollision(bullet.x, bullet.y, bullet.img.getwidth(), bullet.img.getheight(), player.coreX, player.coreY, player.imgCore.getwidth(), player.imgCore.getheight())) {
                    bullet.y = SCREEN_HEIGHT + 10; // 标记敌机子弹为销毁
                    player.health -= 10; // 减少玩家生命值
                    if (player.health <= 0) {
                        FlushBatchDraw();
                        Sleep(1000);
                        EndBatchDraw();
                        gameend1(9);
                        setfillcolor(WHITE);
                        return;
                    }
                }
            }
            for (auto& bullet : bossBulletsDef) {
                if (isCollision(bullet.x, bullet.y, bullet.img.getwidth(), bullet.img.getheight(), player.coreX, player.coreY, player.imgCore.getwidth(), player.imgCore.getheight())) {
                    player.health -= 10; // 减少玩家生命值
                    if (player.health <= 0) {
                        FlushBatchDraw();
                        Sleep(1000);
                        EndBatchDraw();
                        gameend1(9);
                        setfillcolor(WHITE);
                        return;
                    }
                }
            }
            for (auto& bullet : bossBulletsCir1) {
                if (isCollision(bullet.x, bullet.y, bullet.img.getwidth(), bullet.img.getheight(), player.coreX, player.coreY, player.imgCore.getwidth(), player.imgCore.getheight())) {
                    player.health -= 10; // 减少玩家生命值
                    if (player.health <= 0) {
                        FlushBatchDraw();
                        Sleep(1000);
                        EndBatchDraw();
                        gameend1(9);
                        setfillcolor(WHITE);
                        return;
                    }
                }
            }
            for (auto& bullet : bossBulletsCir2) {
                if (isCollision(bullet.x, bullet.y, bullet.img.getwidth(), bullet.img.getheight(), player.coreX, player.coreY, player.imgCore.getwidth(), player.imgCore.getheight())) {
                    player.health -= 10; // 减少玩家生命值
                    if (player.health <= 0) {
                        FlushBatchDraw();
                        Sleep(1000);
                        EndBatchDraw();
                        gameend1(9);
                        setfillcolor(WHITE);
                        return;
                    }
                }
            }
            for (auto& bullet : bossBulletsCir3) {
                if (isCollision(bullet.x, bullet.y, bullet.img.getwidth(), bullet.img.getheight(), player.coreX, player.coreY, player.imgCore.getwidth(), player.imgCore.getheight())) {
                    player.health -= 10; // 减少玩家生命值
                    if (player.health <= 0) {
                        FlushBatchDraw();
                        Sleep(1000);
                        EndBatchDraw();
                        gameend1(9);
                        setfillcolor(WHITE);
                        return;
                    }
                }
            }
            for (auto& bullet : bossBulletsMis) {
                if (isCollision(bullet.x, bullet.y, bullet.img.getwidth(), bullet.img.getheight(), player.coreX, player.coreY, player.imgCore.getwidth(), player.imgCore.getheight())) {
                    bullet.y = SCREEN_HEIGHT + 10; // 标记敌机子弹为销毁
                    player.health -= 10; // 减少玩家生命值
                    if (player.health <= 0) {
                        FlushBatchDraw();
                        Sleep(1000);
                        EndBatchDraw();
                        gameend1(9);
                        setfillcolor(WHITE);
                        return;
                    }
                }
            }
            if (isCollision(boss.x, boss.y, boss.img.getwidth(), boss.img.getheight(), player.coreX, player.coreY, player.imgCore.getwidth(), player.imgCore.getheight())) {
                player.health -= 10; // 减少玩家生命值
                if (player.health <= 0) {
                    FlushBatchDraw();
                    Sleep(1000);
                    EndBatchDraw();
                    gameend1(9);
                    setfillcolor(WHITE);
                    return;
                }
            }


            // 绘制玩家飞机
            player.draw();

            

            // 检测得分是否满足胜利条件
            if (boss.health<=0) {
                FlushBatchDraw();
                Sleep(1000);
                EndBatchDraw();
                gameend2(9);
                setfillcolor(WHITE);
                return;
            }

            // 延时
            Sleep(10);
            epoch++;
            if (epoch >= 0) {
                if (!(epoch %= 3000)) {
                    cycle++;
                }
            }
            // 刷新屏幕
            FlushBatchDraw();
            cleardevice();

        }
    }
    EndBatchDraw();
}

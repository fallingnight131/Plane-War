#include"../include/game.h"

// ��Ϸ��ѭ��
void gameLoop1(int level) {
    playMusic(_T("../resources/sounds/fight.mp3"));
    Plane player(400, 500, "../resources/images/plane1.bmp", "../resources/images/core.bmp");
    std::vector<Bullet> bullets;
    std::vector<Enemy> enemies;
    std::vector<EnemyBullet> enemyBullets;
    std::vector<Item> items;
    std::vector<IMAGE> backgrounds; // ����ͼ��
    int fireRate = 10; // ��������֡��
    int bulletCount = 1; // ÿ�η�����ӵ�����
    std::vector<Item> activeItems; // ��ǰ����ĵ���Ч��
    int epoch = 0;
    int score = 0;
    int aimScore = 400 + level * 200;
    bool isPaused = false;
    IMAGE background;

    BeginBatchDraw();   //ִ�������滭����ֹ����������  ����ΪEndBatchDraw
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

        // ������ͣ��
        if (GetAsyncKeyState('P') & 0x8000) {
            isPaused = !isPaused;
            if (isPaused) {
                putimage(0, 0, &background);
                // ���µ��߻���
                for (auto& item : items) {
                    item.draw();
                }
                // ���µл�����
                for (auto& enemy : enemies) {
                    enemy.draw();
                }
                // ���µл��ӵ�����
                for (auto& bullet : enemyBullets) {
                    bullet.draw();
                }
                //��������ӵ�����
                for (auto& bullet : bullets) {
                    bullet.draw();
                }
                // ������ҷɻ�
                player.draw();
                // ���Ʒ���
                TCHAR scoreText[20];
                _stprintf_s(scoreText, _T("Score: %d"), score);
                settextcolor(BLACK);
                settextstyle(20, 0, _T("Consolas"));
                outtextxy(10, 10, scoreText);

                //������ͣ����
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
            // �����û�����
            if (GetAsyncKeyState(VK_LEFT) & 0x8000) player.move(-1, 0);
            if (GetAsyncKeyState(VK_RIGHT) & 0x8000) player.move(1, 0);
            if (GetAsyncKeyState(VK_UP) & 0x8000) player.move(0, -1);
            if (GetAsyncKeyState(VK_DOWN) & 0x8000) player.move(0, 1);

            // �������
            if (GetAsyncKeyState(VK_SPACE) & 0x8000 && epoch % fireRate == 0) {
                for (int i = 0; i < bulletCount; i++) {
                    int offset = (i - (bulletCount - 1) / 2.0) * 20; // �ӵ�֮��ļ��
                    bullets.emplace_back(player.x + player.img.getwidth() / 2 + offset, player.y, _T("../resources/images/bullet.bmp"));
                }
            }

            // �л�����
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

            // �л����
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


            // ��������
            if (epoch % 200 == 0) {
                int itemType = rand() % 5; // ���ѡ���������
                items.emplace_back(rand() % (SCREEN_WIDTH - 100), -rand() % 100, itemType);
            }


            //��������ӵ�λ�úͻ���
            for (auto& bullet : bullets) {
                bullet.move(-20);
                bullet.draw();
            }

            // ���µ���λ�úͻ���
            for (auto& item : items) {
                item.move(1);
                item.draw();
            }

            // ɾ����Ļ����ӵ�
            bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](Bullet& b) { return b.y < 0; }), bullets.end());

            // ���µл�λ�úͻ���
            for (auto& enemy : enemies) {
                enemy.move(1);
                enemy.draw();
            }

            // ɾ����Ļ��ĵл�
            enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](Enemy& e) { return e.y > SCREEN_HEIGHT; }), enemies.end());

            // ���µл��ӵ�λ�úͻ���
            for (auto& bullet : enemyBullets) {
                bullet.move1(2);
                bullet.draw();
            }

            // ɾ����Ļ��ĵл��ӵ�
            enemyBullets.erase(std::remove_if(enemyBullets.begin(), enemyBullets.end(), [](EnemyBullet& b) { return b.y > SCREEN_HEIGHT; }), enemyBullets.end());



            // ɾ����Ļ��ĵ���
            items.erase(std::remove_if(items.begin(), items.end(), [](Item& i) { return i.y > SCREEN_HEIGHT; }), items.end());

            // ����������ҵ���ײ
            for (auto& item : items) {
                if (isCollision(item.x, item.y, item.img.getwidth(), item.img.getheight(),
                    player.x, player.y, player.img.getwidth(), player.img.getheight())) {
                    item.applyEffect(player, enemies, fireRate, bulletCount);
                    if (item.duration > 0) {
                        activeItems.push_back(item);
                    }
                    item.y = SCREEN_HEIGHT + 10; // ���Ϊ������Ļ
                }
            }

            // ���¼���ĵ���Ч��
            for (auto it = activeItems.begin(); it != activeItems.end();) {
                it->duration--;
                if (it->duration <= 0) {
                    // ����Ч���������ָ�ԭ״
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

            // ���л�������ӵ�����ײ
            for (auto& bullet : bullets) {
                for (auto& enemy : enemies) {
                    if (isCollision(bullet.x, bullet.y, bullet.img.getwidth(), bullet.img.getheight(), enemy.x, enemy.y, enemy.img.getwidth(), enemy.img.getheight())) {
                        bullet.y = -10; // ���ӵ����Ϊ������Ļ
                        enemy.health -= 30; // ���ٵ�������ֵ
                        if (enemy.health <= 0) {
                            enemy.y = 810; // ���л����Ϊ������Ļ
                            score += 10;   // ���ӵ÷�
                        }
                    }
                }
            }

            // ���л��ӵ�����ҷɻ�����ײ
            for (auto& bullet : enemyBullets) {
                if (isCollision(bullet.x, bullet.y, bullet.img.getwidth(), bullet.img.getheight(), player.x, player.y, player.img.getwidth(), player.img.getheight())) {
                    bullet.y = SCREEN_HEIGHT + 10; // ��ǵл��ӵ�Ϊ����
                    player.health -= 10; // �����������ֵ
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


            // ������ҷɻ�
            player.draw();

            // ���Ʒ���
            TCHAR scoreText[20];
            settextcolor(YELLOW);
            settextstyle(20, 0, _T("Consolas"));
            _stprintf_s(scoreText, _T("Aim Score: %d"), aimScore);
            outtextxy(10, 10, scoreText);
            _stprintf_s(scoreText, _T("Your Score: %d\n"), score);
            outtextxy(10, 40, scoreText);

            // ���÷��Ƿ�����ʤ������
            if (score >= aimScore) {
                FlushBatchDraw();
                Sleep(1000);
                EndBatchDraw();
                gameend2(level);
                setfillcolor(WHITE);
                return;
            }

            // ��ʱ
            Sleep(10);
            epoch++;
            // ˢ����Ļ
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
    std::vector<EnemyBullet> bossBulletsQik;       //���ٹⵯ
    std::vector<EnemyBullet> bossBulletsMid;       //���ٹⵯ
    std::vector<EnemyBullet> bossBulletsSlo;       //���ٹⵯ
    std::vector<EnemyBullet> bossBulletsMis;       //����
    std::vector<EnemyBullet> bossBulletsCir1;       //��Ȧ�ⵯ���ڣ�
    std::vector<EnemyBullet> bossBulletsCir2;       //��Ȧ�ⵯ���У�
    std::vector<EnemyBullet> bossBulletsCir3;       //��Ȧ�ⵯ���⣩
    std::vector<EnemyBullet> bossBulletsDef;        //���������
    std::vector<Item> items;
    std::vector<IMAGE> backgrounds; // ����ͼ��
    int fireRate = 10; // ��������֡��
    int bulletCount = 1; // ÿ�η�����ӵ�����
    std::vector<Item> activeItems; // ��ǰ����ĵ���Ч��
    int epoch = 0;
    int cycle = 0;
    bool bossDef = 0;
    bool bossCir = 0;
    bool isPaused = false;
    IMAGE background;

    BeginBatchDraw();   //ִ�������滭����ֹ����������  ����ΪEndBatchDraw
    while (true) {
        loadimage(&background, "../resources/images/background4.bmp");



        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            if (!gamestop(9)) break;
            isPaused = false;
            FlushBatchDraw();
        }

        // ������ͣ��
        if (GetAsyncKeyState('P') & 0x8000) {
            isPaused = !isPaused;
            if (isPaused) {
                putimage(0, 0, &background);
                // ���µ���λ�úͻ���
                for (auto& item : items) {
                    item.draw();
                }
                // ����boss����
                boss.draw();
                // ����boss�ӵ�����
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
                //��������ӵ�λ�úͻ���
                for (auto& bullet : bullets) {
                    bullet.draw();
                }
                // ������ҷɻ�
                player.draw();

                //������ͣ����
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
            // �����û�����
            if (GetAsyncKeyState(VK_LEFT) & 0x8000) player.move(-1, 0);
            if (GetAsyncKeyState(VK_RIGHT) & 0x8000) player.move(1, 0);
            if (GetAsyncKeyState(VK_UP) & 0x8000) player.move(0, -1);
            if (GetAsyncKeyState(VK_DOWN) & 0x8000) player.move(0, 1);

            // �������
            if (GetAsyncKeyState(VK_SPACE) & 0x8000 && epoch % fireRate == 0) {
                for (int i = 0; i < bulletCount; i++) {
                    int offset = (i - (bulletCount - 1) / 2.0) * 20; // �ӵ�֮��ļ��
                    bullets.emplace_back(player.x + player.img.getwidth() / 2 + offset, player.y, _T("../resources/images/bullet.bmp"));
                }
            }

            //boss�ж�
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
                //������ٵ�
                if (boss.angleX < 270 && boss.angleX >= 180 || boss.angleX < 90 && boss.angleX >= 0) {
                    if (epoch % 10 == 0) {
                        for (int i = 0; i < 5; i++) {
                            int offset = (i - (4.5) / 2.0) * 20; // �ӵ�֮��ļ��
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
                //������ٵ�
                if (epoch % 10 == 0) {
                    for (int i = 0; i < 2; i++) {
                        int offset = (i - (1) / 2.0) * 150; // �ӵ�֮��ļ��
                        bossBulletsMid.emplace_back(boss.x + boss.img.getwidth() / 2 + offset, boss.y + boss.img.getheight(), _T("../resources/images/bullet1.bmp"));
                    }

                }
            }
            if (epoch > 1210 && epoch <= 1282) {
                boss.move2(SCREEN_WIDTH / 3, 5);
                //�������
                if (epoch == 1230) {
                    bossBulletsMis.emplace_back(0,0, _T("../resources/images/missile.bmp"));
                }
                if (epoch == 1260) {
                    bossBulletsMis.emplace_back(100, 0, _T("../resources/images/missile.bmp"));
                }
            }
            if (epoch > 1282 && epoch <= 1354) {
                boss.move2(SCREEN_WIDTH / 2, 5);
                //�������
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
                //�������
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
                //������ٵ�
                if (!(boss.angleX%90)) {
                    for (int i = 0; i < 5; i++) {
                        int offset = (i - (4.5) / 2.0) * 20; // �ӵ�֮��ļ��
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



            // ��������
            if (epoch % 200 == 0) {
                int itemType = rand() % 5; // ���ѡ���������
                items.emplace_back(rand() % (SCREEN_WIDTH - 100), -rand() % 100, itemType);
            }



            for (auto& bullet : bullets) {
                bullet.move(-20);
                bullet.draw();
            }

            // ���µ���λ�úͻ���
            for (auto& item : items) {
                item.move(1);
                item.draw();
            }

            // ɾ����Ļ����ӵ�
            bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](Bullet& b) { return b.y < 0; }), bullets.end());

            // ����boss����
            boss.draw();

            
            // ���µл��ӵ�λ�úͻ���
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


            // ɾ����Ļ��ĵл��ӵ�
            bossBulletsQik.erase(std::remove_if(bossBulletsQik.begin(), bossBulletsQik.end(), [](EnemyBullet& b) { return b.y > SCREEN_HEIGHT; }), bossBulletsQik.end());

            bossBulletsMid.erase(std::remove_if(bossBulletsMid.begin(), bossBulletsMid.end(), [](EnemyBullet& b) { return b.y > SCREEN_HEIGHT; }), bossBulletsMid.end());

            bossBulletsSlo.erase(std::remove_if(bossBulletsSlo.begin(), bossBulletsSlo.end(), [](EnemyBullet& b) { return b.y > SCREEN_HEIGHT; }), bossBulletsSlo.end());

            bossBulletsMis.erase(std::remove_if(bossBulletsMis.begin(), bossBulletsMis.end(), [](EnemyBullet& b) { return b.y > SCREEN_HEIGHT; }), bossBulletsMis.end());

            // ɾ����Ļ��ĵ���
            items.erase(std::remove_if(items.begin(), items.end(), [](Item& i) { return i.y > SCREEN_HEIGHT; }), items.end());

            // ����������ҵ���ײ
            for (auto& item : items) {
                if (isCollision(item.x, item.y, item.img.getwidth(), item.img.getheight(),
                    player.x, player.y, player.img.getwidth(), player.img.getheight())) {
                    item.applyEffectBoss(player, boss, fireRate, bulletCount);
                    if (item.duration > 0) {
                        activeItems.push_back(item);
                    }
                    item.y = SCREEN_HEIGHT + 10; // ���Ϊ������Ļ
                }
            }

            // ���¼���ĵ���Ч��
            for (auto it = activeItems.begin(); it != activeItems.end();) {
                it->duration--;
                if (it->duration <= 0) {
                    // ����Ч���������ָ�ԭ״
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
            // ��⻷���������ӵ�����ײ
            for (auto& bullet : bullets) {
                for (auto& def : bossBulletsDef) {
                    if (isCollision(bullet.x, bullet.y, bullet.img.getwidth(), bullet.img.getheight(), def.x, def.y, def.img.getwidth(), def.img.getheight())) {
                        bullet.y = -10; // ���ӵ����Ϊ������Ļ
                    }
                }
            }
            // ���л�������ӵ�����ײ
            for (auto& bullet : bullets) {
                if (isCollision(bullet.x, bullet.y, bullet.img.getwidth(), bullet.img.getheight(), boss.x, boss.y, boss.img.getwidth(), boss.img.getheight())) {
                    bullet.y = -10; // ���ӵ����Ϊ������Ļ
                    boss.health -= 20; // ���ٵ�������ֵ
                    
                }
            }

            // ���л��ӵ�����ҷɻ�����ײ
            for (auto& bullet : bossBulletsQik) {
                if (isCollision(bullet.x, bullet.y, bullet.img.getwidth(), bullet.img.getheight(), player.coreX, player.coreY, player.imgCore.getwidth(), player.imgCore.getheight())) {
                    bullet.y = SCREEN_HEIGHT + 10; // ��ǵл��ӵ�Ϊ����
                    player.health -= 10; // �����������ֵ
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
                    bullet.y = SCREEN_HEIGHT + 10; // ��ǵл��ӵ�Ϊ����
                    player.health -= 10; // �����������ֵ
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
                    bullet.y = SCREEN_HEIGHT + 10; // ��ǵл��ӵ�Ϊ����
                    player.health -= 10; // �����������ֵ
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
                    player.health -= 10; // �����������ֵ
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
                    player.health -= 10; // �����������ֵ
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
                    player.health -= 10; // �����������ֵ
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
                    player.health -= 10; // �����������ֵ
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
                    bullet.y = SCREEN_HEIGHT + 10; // ��ǵл��ӵ�Ϊ����
                    player.health -= 10; // �����������ֵ
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
                player.health -= 10; // �����������ֵ
                if (player.health <= 0) {
                    FlushBatchDraw();
                    Sleep(1000);
                    EndBatchDraw();
                    gameend1(9);
                    setfillcolor(WHITE);
                    return;
                }
            }


            // ������ҷɻ�
            player.draw();

            

            // ���÷��Ƿ�����ʤ������
            if (boss.health<=0) {
                FlushBatchDraw();
                Sleep(1000);
                EndBatchDraw();
                gameend2(9);
                setfillcolor(WHITE);
                return;
            }

            // ��ʱ
            Sleep(10);
            epoch++;
            if (epoch >= 0) {
                if (!(epoch %= 3000)) {
                    cycle++;
                }
            }
            // ˢ����Ļ
            FlushBatchDraw();
            cleardevice();

        }
    }
    EndBatchDraw();
}

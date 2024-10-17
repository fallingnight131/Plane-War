#include"../include/menu.h"
#include <algorithm>


//调整字体和背景样式
void initializeFont() {

    setbkmode(TRANSPARENT);  // 设置全局文本背景模式为透明
    LOGFONT f;
    gettextstyle(&f);
    f.lfHeight = 24;
    _tcscpy_s(f.lfFaceName, _T("微软雅黑"));
    f.lfQuality = ANTIALIASED_QUALITY;
    f.lfWeight = FW_NORMAL;
    settextstyle(&f);
    settextcolor(BLACK);
}

// 改进的按钮绘制函数
void drawButton(int x, int y, int width, int height, const TCHAR* text, COLORREF color) {
    // 绘制按钮背景
    setfillcolor(color);
    solidroundrect(x, y, x + width, y + height, 10, 10);

    // 设置文本样式
    LOGFONT f;
    gettextstyle(&f);
    f.lfHeight = height * 0.5;
    f.lfWeight = FW_BOLD;
    _tcscpy_s(f.lfFaceName, _T("微软雅黑"));
    f.lfQuality = ANTIALIASED_QUALITY;
    settextstyle(&f);
    settextcolor(BLACK);

    // 设置文本背景模式为透明
    setbkmode(TRANSPARENT);

    // 绘制文本
    int textX = x + (width - textwidth(text)) / 2;
    int textY = y + (height - textheight(text)) / 2;
    outtextxy(textX, textY, text);
}

// 改进的菜单背景绘制函数

void drawMenuBackground(const TCHAR* title) {
    // 清除屏幕并设置背景色
    setbkcolor(RGB(240, 240, 240));
    /*cleardevice();*/

    // 保存当前图形设置
    int oldBkMode = getbkmode();
    LOGFONT oldFont;
    gettextstyle(&oldFont);

    // 设置新的字体样式
    LOGFONT f;
    gettextstyle(&f);
    f.lfHeight = 48;
    f.lfWeight = FW_BOLD;
    _tcscpy_s(f.lfFaceName, _T("微软雅黑")); // 确保使用支持的字体
    f.lfQuality = ANTIALIASED_QUALITY; // 使用抗锯齿以提高质量
    settextstyle(&f);

    // 设置文本背景模式为透明
    setbkmode(TRANSPARENT);

    // 绘制标题
    settextcolor(RGB(240, 240, 240));
    int titleX = (SCREEN_WIDTH - textwidth(title)) / 2;
    int titleY = 50;
    RECT textRect = { titleX, titleY, titleX + textwidth(title), titleY + textheight(title) };
    drawtext(title, &textRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    // 恢复原来的图形设置
    setbkmode(oldBkMode);
    settextstyle(&oldFont);

    // 刷新屏幕
    FlushBatchDraw();
}

//主菜单
void showMainMenu() {
    playMusic(_T("../resources/sounds/PlaneWar.mp3"));

    initializeFont();
    // 清屏并设置背景颜色
    setbkcolor(RGB(240, 240, 240));
    cleardevice();
    IMAGE background;
    loadimage(&background, _T("../resources/images/background5.bmp"), 0, 0, true);
    putimage(0, 0, &background);
    const int buttonWidth = 200;
    const int buttonHeight = 60;
    const int startY = 200;
    const int spacing = 80;

    // 绘制标题
    settextstyle(48, 0, _T("微软雅黑"));
    settextcolor(RGB(255, 255, 255));
    int titleX = (SCREEN_WIDTH - textwidth(_T("飞机大战"))) / 2;
    outtextxy(titleX, 50, _T("飞机大战"));

    // 绘制按钮
    drawButton((SCREEN_WIDTH - buttonWidth) / 2, startY, buttonWidth, buttonHeight, _T("单人游戏"), RGB(70, 130, 180));
    drawButton((SCREEN_WIDTH - buttonWidth) / 2, startY + spacing, buttonWidth, buttonHeight, _T("游戏设置"), RGB(60, 179, 113));
    drawButton((SCREEN_WIDTH - buttonWidth) / 2, startY + spacing * 2, buttonWidth, buttonHeight, _T("退出游戏"), RGB(220, 20, 60));

    FlushBatchDraw();

    // Add a statement before the loop
    ExMessage msg;

    while (true) {
        ExMessage msg = getmessage(EM_MOUSE);
        if (msg.message == WM_LBUTTONDOWN) {
            int buttonY = (msg.y - startY) / spacing;
            if (msg.x >= (SCREEN_WIDTH - buttonWidth) / 2 && msg.x <= (SCREEN_WIDTH + buttonWidth) / 2) {
                switch (buttonY) {
                case 0: startSinglePlayerGame(); break;
                case 1: showGameSettings(); break;
                case 2: exit(0);
                }
            }
        }
    }
}

//调整音量
void SetVolume() {
    initializeFont();
    IMAGE background;
    loadimage(&background, _T("../resources/images/background5.bmp"));

    const int buttonWidth = 100;
    const int buttonHeight = 50;

    while (true) {
        putimage(0, 0, &background);
        drawButton(30, 30, 100, 40, _T("返回"), RGB(100, 100, 100));

        TCHAR volumeText[50];
        _stprintf_s(volumeText, _T("当前音量: %d"), getCurrentVolume());

        settextcolor(WHITE);
        outtextxy(SCREEN_WIDTH / 2 - textwidth(volumeText) / 2, 200, volumeText);

        drawButton(SCREEN_WIDTH / 2 - 150, 300, buttonWidth, buttonHeight, _T("-"), RGB(220, 20, 60));
        drawButton(SCREEN_WIDTH / 2 + 50, 300, buttonWidth, buttonHeight, _T("+"), RGB(60, 179, 113));

        FlushBatchDraw();

        ExMessage msg = getmessage(EM_MOUSE);
        if (msg.message == WM_LBUTTONDOWN) {
            //返回
            if (msg.x >= 30 && msg.x <= 130 && msg.y >= 30 && msg.y <= 70) {
                showGameSettings();
                return;
            }
            // 减小音量
            if (msg.x >= SCREEN_WIDTH / 2 - 150 && msg.x <= SCREEN_WIDTH / 2 - 50 &&
                msg.y >= 300 && msg.y <= 350) {
                int newVolume = (std::min)(0, getCurrentVolume() - 10);
                setVolume(newVolume);
            }
            // 增加音量
            if (msg.x >= SCREEN_WIDTH / 2 + 50 && msg.x <= SCREEN_WIDTH / 2 + 150 &&
                msg.y >= 300 && msg.y <= 350) {
                int newVolume = (std::min)(100, getCurrentVolume() + 10);
                setVolume(newVolume);
            }
        }
    }
}

//游戏设置菜单
void showGameSettings() {
    initializeFont();
    drawMenuBackground(_T("游戏设置"));
    IMAGE background;
    loadimage(&background, _T("../resources/images/background5.bmp"), 0, 0, true);
    putimage(0, 0, &background);
    const int buttonWidth = 200;
    const int buttonHeight = 60;
    const int startY = 200;
    const int spacing = 80;

    drawButton(30, 30, 100, 40, _T("返回"), RGB(100, 100, 100));
    drawButton((SCREEN_WIDTH - buttonWidth) / 2, startY, buttonWidth, buttonHeight, _T("音量设置"), RGB(70, 130, 180));
    drawButton((SCREEN_WIDTH - buttonWidth) / 2, startY + spacing, buttonWidth, buttonHeight, _T("操作设置"), RGB(60, 179, 113));

    FlushBatchDraw();

    while (true) {
        ExMessage msg = getmessage(EM_MOUSE);
        if (msg.message == WM_LBUTTONDOWN) {
            if (msg.x >= 30 && msg.x <= 130 && msg.y >= 30 && msg.y <= 70) {
                showMainMenu();
                return;
            }
            if (msg.x >= (SCREEN_WIDTH - buttonWidth) / 2 && msg.x <= (SCREEN_WIDTH + buttonWidth) / 2) {
                if (msg.y >= startY && msg.y <= startY + buttonHeight) {
                    SetVolume();
                    return;
                }
                if (msg.y >= startY + spacing && msg.y <= startY + spacing + buttonHeight) {
                    game_set_opera();
                    return;
                }
            }
        }
    }
}

// 操作设置
void game_set_opera() {
    initializeFont();
    drawMenuBackground(_T("操作设置"));
    IMAGE background;
    loadimage(&background, "../resources/images/background5.bmp");
    putimage(0, 0, &background);
    const int buttonWidth = 150;
    const int buttonHeight = 50;
    const int startY = 150;
    const int spacing = 60;

    drawButton(30, 30, 100, 40, _T("返回"), RGB(100, 100, 100));

    const TCHAR* controls[] = { _T("上: ↑"), _T("下: ↓"), _T("左: ←"), _T("右: →"), _T("射击: 空格") };
    for (int i = 0; i < 5; i++) {
        drawButton(SCREEN_WIDTH / 2 - buttonWidth / 2, startY + i * spacing, buttonWidth, buttonHeight, controls[i], RGB(70, 130, 180));
    }

    FlushBatchDraw();

    while (true) {
        ExMessage msg = getmessage(EM_MOUSE);
        if (msg.message == WM_LBUTTONDOWN) {
            if (msg.x >= 30 && msg.x <= 130 && msg.y >= 30 && msg.y <= 70) {
                showGameSettings();
                return;
            }
        }
    }
}


// 暂停界面(0代表不返回游戏，1代表返回游戏）
bool gamestop(int currentLevel) {
    initializeFont();
    drawMenuBackground(_T("游戏暂停"));
    IMAGE background;
    loadimage(&background, "../resources/images/background5.bmp");
    putimage(0, 0, &background);
    const int buttonWidth = 200;
    const int buttonHeight = 60;
    const int startY = 250;
    const int spacing = 80;

    drawButton(SCREEN_WIDTH / 2 - buttonWidth / 2, startY, buttonWidth, buttonHeight, _T("返回主菜单"), RGB(220, 20, 60));
    drawButton(SCREEN_WIDTH / 2 - buttonWidth / 2, startY + spacing, buttonWidth, buttonHeight, _T("重新开始"), RGB(60, 179, 113));
    drawButton(SCREEN_WIDTH / 2 - buttonWidth / 2, startY + 2 * spacing, buttonWidth, buttonHeight, _T("返回游戏"), RGB(60, 179, 113));

    FlushBatchDraw();

    while (true) {
        ExMessage msg = getmessage(EM_MOUSE);
        if (msg.message == WM_LBUTTONDOWN) {
            //返回主菜单
            if (msg.y >= startY && msg.y <= startY + buttonHeight &&
                msg.x >= SCREEN_WIDTH / 2 - buttonWidth / 2 && msg.x <= SCREEN_WIDTH / 2 + buttonWidth / 2) {
                showMainMenu();
                return 0;
            }
            //重新开始
            if (msg.y >= startY + spacing && msg.y <= startY + spacing + buttonHeight &&
                msg.x >= SCREEN_WIDTH / 2 - buttonWidth / 2 && msg.x <= SCREEN_WIDTH / 2 + buttonWidth / 2) {
                if (currentLevel == 9)
                    gameLoopBoss();
                else
                    gameLoop1(currentLevel);
                return 0;
            }
            //返回游戏
            if (msg.y >= startY + 2 * spacing && msg.y <= startY + 2 * spacing + buttonHeight &&
                msg.x >= SCREEN_WIDTH / 2 - buttonWidth / 2 && msg.x <= SCREEN_WIDTH / 2 + buttonWidth / 2) {
                return 1;
            }
        }
    }
}

//绘制游戏失败菜单
void gameend1(int currentLevel) {
    initializeFont();

    IMAGE background;
    loadimage(&background, "../resources/images/background5.bmp");
    putimage(0, 0, &background);
    drawMenuBackground(_T("战斗失败"));
    const int buttonWidth = 200;
    const int buttonHeight = 60;
    const int startY = 250;
    const int spacing = 80;


    settextcolor(BLACK);

    drawButton(SCREEN_WIDTH / 2 - buttonWidth / 2, startY, buttonWidth, buttonHeight, _T("返回主菜单"), RGB(220, 20, 60));
    drawButton(SCREEN_WIDTH / 2 - buttonWidth / 2, startY + spacing, buttonWidth, buttonHeight, _T("重新开始"), RGB(60, 179, 113));

    FlushBatchDraw();

    while (true) {
        ExMessage msg = getmessage(EM_MOUSE);
        if (msg.message == WM_LBUTTONDOWN) {
            //主菜单
            if (msg.y >= startY && msg.y <= startY + buttonHeight &&
                msg.x >= SCREEN_WIDTH / 2 - buttonWidth / 2 && msg.x <= SCREEN_WIDTH / 2 + buttonWidth / 2) {
                showMainMenu();
                return;
            }
            //重新开始
            if (msg.y >= startY + spacing && msg.y <= startY + spacing + buttonHeight &&
                msg.x >= SCREEN_WIDTH / 2 - buttonWidth / 2 && msg.x <= SCREEN_WIDTH / 2 + buttonWidth / 2) {
                if (currentLevel == 9)
                    gameLoopBoss();
                else
                    gameLoop1(currentLevel);
                return;
            }

        }
    }
}

//绘制游戏胜利菜单
void gameend2(int currentLevel) {
    initializeFont();

    IMAGE background;
    loadimage(&background, "../resources/images/background5.bmp");
    putimage(0, 0, &background);
    drawMenuBackground(_T("战斗胜利"));
    const int buttonWidth = 200;
    const int buttonHeight = 60;
    const int startY = 250;
    const int spacing = 80;


    settextcolor(BLACK);

    drawButton(SCREEN_WIDTH / 2 - buttonWidth / 2, startY, buttonWidth, buttonHeight, _T("返回主菜单"), RGB(220, 20, 60));

    if (currentLevel < 8) { // 假设总共有8关
        drawButton(SCREEN_WIDTH / 2 - buttonWidth / 2, startY + spacing, buttonWidth, buttonHeight, _T("下一关"), RGB(70, 130, 180));
    }
    if (currentLevel == 8) {
        drawButton(SCREEN_WIDTH / 2 - buttonWidth / 2, startY + spacing, buttonWidth, buttonHeight, _T("恭喜通过所有关卡"), RGB(70, 130, 180));
    }

    FlushBatchDraw();

    while (true) {
        ExMessage msg = getmessage(EM_MOUSE);
        if (msg.message == WM_LBUTTONDOWN) {
            //主菜单
            if (msg.y >= startY && msg.y <= startY + buttonHeight &&
                msg.x >= SCREEN_WIDTH / 2 - buttonWidth / 2 && msg.x <= SCREEN_WIDTH / 2 + buttonWidth / 2) {
                showMainMenu();
                return;
            }

            //下一关
            if (currentLevel < 8 &&
                msg.y >= startY + spacing && msg.y <= startY + spacing + buttonHeight &&
                msg.x >= SCREEN_WIDTH / 2 - buttonWidth / 2 && msg.x <= SCREEN_WIDTH / 2 + buttonWidth / 2) {
                gameLoop1(currentLevel + 1);
                return;
            }
            //通过所有关卡
            if (currentLevel == 8 &&
                msg.y >= startY + spacing && msg.y <= startY + spacing + buttonHeight &&
                msg.x >= SCREEN_WIDTH / 2 - buttonWidth / 2 && msg.x <= SCREEN_WIDTH / 2 + buttonWidth / 2) {
                showMainMenu();
                return;
            }
        }
    }
}

//绘制关卡选择菜单
void startSinglePlayerGame() {
    initializeFont();
    drawMenuBackground(_T("选择关卡"));
    IMAGE background;
    loadimage(&background, "../resources/images/background5.bmp");
    putimage(0, 0, &background);
    const int buttonWidth = 200;
    const int buttonHeight = 60;
    const int startX = (SCREEN_WIDTH - buttonWidth * 2 - 40) / 2;
    const int startY = 150;
    const int spacingX = buttonWidth + 40;
    const int spacingY = buttonHeight + 20;

    // 绘制返回按钮
    drawButton(30, 30, 100, 40, _T("返回"), RGB(100, 100, 100));

    // 绘制2x4网格的关卡选择按钮
    for (int i = 0; i < 8; i++) {
        TCHAR levelText[20];
        _stprintf_s(levelText, _T("第 %d 关"), i + 1);
        int x = startX + (i % 2) * spacingX;
        int y = startY + (i / 2) * spacingY;
        drawButton(x, y, buttonWidth, buttonHeight, levelText, RGB(70, 130, 180));
    }

    // 绘制boss关按钮
    drawButton(SCREEN_WIDTH / 2 - buttonWidth / 2, startY + (8 / 2) * spacingY, buttonWidth, buttonHeight, _T("Boss"), RGB(200, 179, 113));

    // "出击"按钮放在底部中央
    drawButton(SCREEN_WIDTH / 2 - buttonWidth / 2, SCREEN_HEIGHT - 80, buttonWidth, buttonHeight, _T("出击"), RGB(60, 179, 113));

    FlushBatchDraw();

    while (true) {
        ExMessage msg = getmessage(EM_MOUSE);
        if (msg.message == WM_LBUTTONDOWN) {
            // 处理返回按钮
            if (msg.x >= 30 && msg.x <= 130 && msg.y >= 30 && msg.y <= 70) {
                showMainMenu();
                return;
            }

            // 处理关卡选择按钮
            for (int i = 0; i < 8; i++) {
                int x = startX + (i % 2) * spacingX;
                int y = startY + (i / 2) * spacingY;
                if (msg.x >= x && msg.x <= x + buttonWidth &&
                    msg.y >= y && msg.y <= y + buttonHeight) {
                    gameLoop1(i + 1);
                    return;
                }
            }

            // 处理"Boss"按钮
            if (msg.x >= SCREEN_WIDTH / 2 - buttonWidth / 2 &&
                msg.x <= SCREEN_WIDTH / 2 + buttonWidth / 2 &&
                msg.y >= startY + (8 / 2) * spacingY &&
                msg.y <= startY + (8 / 2) * spacingY+ buttonHeight) {
                gameLoopBoss();
                return;
            }

            // 处理"出击"按钮
            if (msg.x >= SCREEN_WIDTH / 2 - buttonWidth / 2 &&
                msg.x <= SCREEN_WIDTH / 2 + buttonWidth / 2 &&
                msg.y >= SCREEN_HEIGHT - 80 &&
                msg.y <= SCREEN_HEIGHT - 80 + buttonHeight) {
                gameLoop1(1); // 默认从第一关开始
                return;
            }
        }
    }
}
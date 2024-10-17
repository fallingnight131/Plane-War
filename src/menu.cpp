#include"../include/menu.h"
#include <algorithm>


//��������ͱ�����ʽ
void initializeFont() {

    setbkmode(TRANSPARENT);  // ����ȫ���ı�����ģʽΪ͸��
    LOGFONT f;
    gettextstyle(&f);
    f.lfHeight = 24;
    _tcscpy_s(f.lfFaceName, _T("΢���ź�"));
    f.lfQuality = ANTIALIASED_QUALITY;
    f.lfWeight = FW_NORMAL;
    settextstyle(&f);
    settextcolor(BLACK);
}

// �Ľ��İ�ť���ƺ���
void drawButton(int x, int y, int width, int height, const TCHAR* text, COLORREF color) {
    // ���ư�ť����
    setfillcolor(color);
    solidroundrect(x, y, x + width, y + height, 10, 10);

    // �����ı���ʽ
    LOGFONT f;
    gettextstyle(&f);
    f.lfHeight = height * 0.5;
    f.lfWeight = FW_BOLD;
    _tcscpy_s(f.lfFaceName, _T("΢���ź�"));
    f.lfQuality = ANTIALIASED_QUALITY;
    settextstyle(&f);
    settextcolor(BLACK);

    // �����ı�����ģʽΪ͸��
    setbkmode(TRANSPARENT);

    // �����ı�
    int textX = x + (width - textwidth(text)) / 2;
    int textY = y + (height - textheight(text)) / 2;
    outtextxy(textX, textY, text);
}

// �Ľ��Ĳ˵��������ƺ���

void drawMenuBackground(const TCHAR* title) {
    // �����Ļ�����ñ���ɫ
    setbkcolor(RGB(240, 240, 240));
    /*cleardevice();*/

    // ���浱ǰͼ������
    int oldBkMode = getbkmode();
    LOGFONT oldFont;
    gettextstyle(&oldFont);

    // �����µ�������ʽ
    LOGFONT f;
    gettextstyle(&f);
    f.lfHeight = 48;
    f.lfWeight = FW_BOLD;
    _tcscpy_s(f.lfFaceName, _T("΢���ź�")); // ȷ��ʹ��֧�ֵ�����
    f.lfQuality = ANTIALIASED_QUALITY; // ʹ�ÿ�������������
    settextstyle(&f);

    // �����ı�����ģʽΪ͸��
    setbkmode(TRANSPARENT);

    // ���Ʊ���
    settextcolor(RGB(240, 240, 240));
    int titleX = (SCREEN_WIDTH - textwidth(title)) / 2;
    int titleY = 50;
    RECT textRect = { titleX, titleY, titleX + textwidth(title), titleY + textheight(title) };
    drawtext(title, &textRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    // �ָ�ԭ����ͼ������
    setbkmode(oldBkMode);
    settextstyle(&oldFont);

    // ˢ����Ļ
    FlushBatchDraw();
}

//���˵�
void showMainMenu() {
    playMusic(_T("../resources/sounds/PlaneWar.mp3"));

    initializeFont();
    // ���������ñ�����ɫ
    setbkcolor(RGB(240, 240, 240));
    cleardevice();
    IMAGE background;
    loadimage(&background, _T("../resources/images/background5.bmp"), 0, 0, true);
    putimage(0, 0, &background);
    const int buttonWidth = 200;
    const int buttonHeight = 60;
    const int startY = 200;
    const int spacing = 80;

    // ���Ʊ���
    settextstyle(48, 0, _T("΢���ź�"));
    settextcolor(RGB(255, 255, 255));
    int titleX = (SCREEN_WIDTH - textwidth(_T("�ɻ���ս"))) / 2;
    outtextxy(titleX, 50, _T("�ɻ���ս"));

    // ���ư�ť
    drawButton((SCREEN_WIDTH - buttonWidth) / 2, startY, buttonWidth, buttonHeight, _T("������Ϸ"), RGB(70, 130, 180));
    drawButton((SCREEN_WIDTH - buttonWidth) / 2, startY + spacing, buttonWidth, buttonHeight, _T("��Ϸ����"), RGB(60, 179, 113));
    drawButton((SCREEN_WIDTH - buttonWidth) / 2, startY + spacing * 2, buttonWidth, buttonHeight, _T("�˳���Ϸ"), RGB(220, 20, 60));

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

//��������
void SetVolume() {
    initializeFont();
    IMAGE background;
    loadimage(&background, _T("../resources/images/background5.bmp"));

    const int buttonWidth = 100;
    const int buttonHeight = 50;

    while (true) {
        putimage(0, 0, &background);
        drawButton(30, 30, 100, 40, _T("����"), RGB(100, 100, 100));

        TCHAR volumeText[50];
        _stprintf_s(volumeText, _T("��ǰ����: %d"), getCurrentVolume());

        settextcolor(WHITE);
        outtextxy(SCREEN_WIDTH / 2 - textwidth(volumeText) / 2, 200, volumeText);

        drawButton(SCREEN_WIDTH / 2 - 150, 300, buttonWidth, buttonHeight, _T("-"), RGB(220, 20, 60));
        drawButton(SCREEN_WIDTH / 2 + 50, 300, buttonWidth, buttonHeight, _T("+"), RGB(60, 179, 113));

        FlushBatchDraw();

        ExMessage msg = getmessage(EM_MOUSE);
        if (msg.message == WM_LBUTTONDOWN) {
            //����
            if (msg.x >= 30 && msg.x <= 130 && msg.y >= 30 && msg.y <= 70) {
                showGameSettings();
                return;
            }
            // ��С����
            if (msg.x >= SCREEN_WIDTH / 2 - 150 && msg.x <= SCREEN_WIDTH / 2 - 50 &&
                msg.y >= 300 && msg.y <= 350) {
                int newVolume = (std::min)(0, getCurrentVolume() - 10);
                setVolume(newVolume);
            }
            // ��������
            if (msg.x >= SCREEN_WIDTH / 2 + 50 && msg.x <= SCREEN_WIDTH / 2 + 150 &&
                msg.y >= 300 && msg.y <= 350) {
                int newVolume = (std::min)(100, getCurrentVolume() + 10);
                setVolume(newVolume);
            }
        }
    }
}

//��Ϸ���ò˵�
void showGameSettings() {
    initializeFont();
    drawMenuBackground(_T("��Ϸ����"));
    IMAGE background;
    loadimage(&background, _T("../resources/images/background5.bmp"), 0, 0, true);
    putimage(0, 0, &background);
    const int buttonWidth = 200;
    const int buttonHeight = 60;
    const int startY = 200;
    const int spacing = 80;

    drawButton(30, 30, 100, 40, _T("����"), RGB(100, 100, 100));
    drawButton((SCREEN_WIDTH - buttonWidth) / 2, startY, buttonWidth, buttonHeight, _T("��������"), RGB(70, 130, 180));
    drawButton((SCREEN_WIDTH - buttonWidth) / 2, startY + spacing, buttonWidth, buttonHeight, _T("��������"), RGB(60, 179, 113));

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

// ��������
void game_set_opera() {
    initializeFont();
    drawMenuBackground(_T("��������"));
    IMAGE background;
    loadimage(&background, "../resources/images/background5.bmp");
    putimage(0, 0, &background);
    const int buttonWidth = 150;
    const int buttonHeight = 50;
    const int startY = 150;
    const int spacing = 60;

    drawButton(30, 30, 100, 40, _T("����"), RGB(100, 100, 100));

    const TCHAR* controls[] = { _T("��: ��"), _T("��: ��"), _T("��: ��"), _T("��: ��"), _T("���: �ո�") };
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


// ��ͣ����(0����������Ϸ��1��������Ϸ��
bool gamestop(int currentLevel) {
    initializeFont();
    drawMenuBackground(_T("��Ϸ��ͣ"));
    IMAGE background;
    loadimage(&background, "../resources/images/background5.bmp");
    putimage(0, 0, &background);
    const int buttonWidth = 200;
    const int buttonHeight = 60;
    const int startY = 250;
    const int spacing = 80;

    drawButton(SCREEN_WIDTH / 2 - buttonWidth / 2, startY, buttonWidth, buttonHeight, _T("�������˵�"), RGB(220, 20, 60));
    drawButton(SCREEN_WIDTH / 2 - buttonWidth / 2, startY + spacing, buttonWidth, buttonHeight, _T("���¿�ʼ"), RGB(60, 179, 113));
    drawButton(SCREEN_WIDTH / 2 - buttonWidth / 2, startY + 2 * spacing, buttonWidth, buttonHeight, _T("������Ϸ"), RGB(60, 179, 113));

    FlushBatchDraw();

    while (true) {
        ExMessage msg = getmessage(EM_MOUSE);
        if (msg.message == WM_LBUTTONDOWN) {
            //�������˵�
            if (msg.y >= startY && msg.y <= startY + buttonHeight &&
                msg.x >= SCREEN_WIDTH / 2 - buttonWidth / 2 && msg.x <= SCREEN_WIDTH / 2 + buttonWidth / 2) {
                showMainMenu();
                return 0;
            }
            //���¿�ʼ
            if (msg.y >= startY + spacing && msg.y <= startY + spacing + buttonHeight &&
                msg.x >= SCREEN_WIDTH / 2 - buttonWidth / 2 && msg.x <= SCREEN_WIDTH / 2 + buttonWidth / 2) {
                if (currentLevel == 9)
                    gameLoopBoss();
                else
                    gameLoop1(currentLevel);
                return 0;
            }
            //������Ϸ
            if (msg.y >= startY + 2 * spacing && msg.y <= startY + 2 * spacing + buttonHeight &&
                msg.x >= SCREEN_WIDTH / 2 - buttonWidth / 2 && msg.x <= SCREEN_WIDTH / 2 + buttonWidth / 2) {
                return 1;
            }
        }
    }
}

//������Ϸʧ�ܲ˵�
void gameend1(int currentLevel) {
    initializeFont();

    IMAGE background;
    loadimage(&background, "../resources/images/background5.bmp");
    putimage(0, 0, &background);
    drawMenuBackground(_T("ս��ʧ��"));
    const int buttonWidth = 200;
    const int buttonHeight = 60;
    const int startY = 250;
    const int spacing = 80;


    settextcolor(BLACK);

    drawButton(SCREEN_WIDTH / 2 - buttonWidth / 2, startY, buttonWidth, buttonHeight, _T("�������˵�"), RGB(220, 20, 60));
    drawButton(SCREEN_WIDTH / 2 - buttonWidth / 2, startY + spacing, buttonWidth, buttonHeight, _T("���¿�ʼ"), RGB(60, 179, 113));

    FlushBatchDraw();

    while (true) {
        ExMessage msg = getmessage(EM_MOUSE);
        if (msg.message == WM_LBUTTONDOWN) {
            //���˵�
            if (msg.y >= startY && msg.y <= startY + buttonHeight &&
                msg.x >= SCREEN_WIDTH / 2 - buttonWidth / 2 && msg.x <= SCREEN_WIDTH / 2 + buttonWidth / 2) {
                showMainMenu();
                return;
            }
            //���¿�ʼ
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

//������Ϸʤ���˵�
void gameend2(int currentLevel) {
    initializeFont();

    IMAGE background;
    loadimage(&background, "../resources/images/background5.bmp");
    putimage(0, 0, &background);
    drawMenuBackground(_T("ս��ʤ��"));
    const int buttonWidth = 200;
    const int buttonHeight = 60;
    const int startY = 250;
    const int spacing = 80;


    settextcolor(BLACK);

    drawButton(SCREEN_WIDTH / 2 - buttonWidth / 2, startY, buttonWidth, buttonHeight, _T("�������˵�"), RGB(220, 20, 60));

    if (currentLevel < 8) { // �����ܹ���8��
        drawButton(SCREEN_WIDTH / 2 - buttonWidth / 2, startY + spacing, buttonWidth, buttonHeight, _T("��һ��"), RGB(70, 130, 180));
    }
    if (currentLevel == 8) {
        drawButton(SCREEN_WIDTH / 2 - buttonWidth / 2, startY + spacing, buttonWidth, buttonHeight, _T("��ϲͨ�����йؿ�"), RGB(70, 130, 180));
    }

    FlushBatchDraw();

    while (true) {
        ExMessage msg = getmessage(EM_MOUSE);
        if (msg.message == WM_LBUTTONDOWN) {
            //���˵�
            if (msg.y >= startY && msg.y <= startY + buttonHeight &&
                msg.x >= SCREEN_WIDTH / 2 - buttonWidth / 2 && msg.x <= SCREEN_WIDTH / 2 + buttonWidth / 2) {
                showMainMenu();
                return;
            }

            //��һ��
            if (currentLevel < 8 &&
                msg.y >= startY + spacing && msg.y <= startY + spacing + buttonHeight &&
                msg.x >= SCREEN_WIDTH / 2 - buttonWidth / 2 && msg.x <= SCREEN_WIDTH / 2 + buttonWidth / 2) {
                gameLoop1(currentLevel + 1);
                return;
            }
            //ͨ�����йؿ�
            if (currentLevel == 8 &&
                msg.y >= startY + spacing && msg.y <= startY + spacing + buttonHeight &&
                msg.x >= SCREEN_WIDTH / 2 - buttonWidth / 2 && msg.x <= SCREEN_WIDTH / 2 + buttonWidth / 2) {
                showMainMenu();
                return;
            }
        }
    }
}

//���ƹؿ�ѡ��˵�
void startSinglePlayerGame() {
    initializeFont();
    drawMenuBackground(_T("ѡ��ؿ�"));
    IMAGE background;
    loadimage(&background, "../resources/images/background5.bmp");
    putimage(0, 0, &background);
    const int buttonWidth = 200;
    const int buttonHeight = 60;
    const int startX = (SCREEN_WIDTH - buttonWidth * 2 - 40) / 2;
    const int startY = 150;
    const int spacingX = buttonWidth + 40;
    const int spacingY = buttonHeight + 20;

    // ���Ʒ��ذ�ť
    drawButton(30, 30, 100, 40, _T("����"), RGB(100, 100, 100));

    // ����2x4����Ĺؿ�ѡ��ť
    for (int i = 0; i < 8; i++) {
        TCHAR levelText[20];
        _stprintf_s(levelText, _T("�� %d ��"), i + 1);
        int x = startX + (i % 2) * spacingX;
        int y = startY + (i / 2) * spacingY;
        drawButton(x, y, buttonWidth, buttonHeight, levelText, RGB(70, 130, 180));
    }

    // ����boss�ذ�ť
    drawButton(SCREEN_WIDTH / 2 - buttonWidth / 2, startY + (8 / 2) * spacingY, buttonWidth, buttonHeight, _T("Boss"), RGB(200, 179, 113));

    // "����"��ť���ڵײ�����
    drawButton(SCREEN_WIDTH / 2 - buttonWidth / 2, SCREEN_HEIGHT - 80, buttonWidth, buttonHeight, _T("����"), RGB(60, 179, 113));

    FlushBatchDraw();

    while (true) {
        ExMessage msg = getmessage(EM_MOUSE);
        if (msg.message == WM_LBUTTONDOWN) {
            // �����ذ�ť
            if (msg.x >= 30 && msg.x <= 130 && msg.y >= 30 && msg.y <= 70) {
                showMainMenu();
                return;
            }

            // ����ؿ�ѡ��ť
            for (int i = 0; i < 8; i++) {
                int x = startX + (i % 2) * spacingX;
                int y = startY + (i / 2) * spacingY;
                if (msg.x >= x && msg.x <= x + buttonWidth &&
                    msg.y >= y && msg.y <= y + buttonHeight) {
                    gameLoop1(i + 1);
                    return;
                }
            }

            // ����"Boss"��ť
            if (msg.x >= SCREEN_WIDTH / 2 - buttonWidth / 2 &&
                msg.x <= SCREEN_WIDTH / 2 + buttonWidth / 2 &&
                msg.y >= startY + (8 / 2) * spacingY &&
                msg.y <= startY + (8 / 2) * spacingY+ buttonHeight) {
                gameLoopBoss();
                return;
            }

            // ����"����"��ť
            if (msg.x >= SCREEN_WIDTH / 2 - buttonWidth / 2 &&
                msg.x <= SCREEN_WIDTH / 2 + buttonWidth / 2 &&
                msg.y >= SCREEN_HEIGHT - 80 &&
                msg.y <= SCREEN_HEIGHT - 80 + buttonHeight) {
                gameLoop1(1); // Ĭ�ϴӵ�һ�ؿ�ʼ
                return;
            }
        }
    }
}
#include"../include/image.h"
#include"../include/plane.h"
#include"../include/settings.h"
#include"../include/enemy.h"
#include"../include/timer.h"
#include"../include/bullet.h"
#include"../include/item.h"
#include"../include/menu.h"
// Ö÷º¯Êý
int main() {
    initgraph(SCREEN_WIDTH, SCREEN_HEIGHT, SHOWCONSOLE);
    setbkcolor(YELLOW);
    cleardevice();
    setfillcolor(YELLOW);
    setlinecolor(BLUE);
    setlinestyle(PS_SOLID, 5);
    settextcolor(RGB(189, 128, 99));
    settextstyle(16, 0, _T("Arial"));
    showMainMenu();
    closegraph();
    return 0;
    

}

#include "../include/timer.h"

LevelTimer::LevelTimer() {
    startTime = clock();
}

LevelTimer::~LevelTimer() = default;
void LevelTimer::update() {
    // ����ʱ��
}

int LevelTimer::getElapsedTime() const {
    // ��ȡ������ʱ�䣨�룩
    return static_cast<int>((clock() - startTime) / CLOCKS_PER_SEC);
}
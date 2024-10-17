#include "../include/timer.h"

LevelTimer::LevelTimer() {
    startTime = clock();
}

LevelTimer::~LevelTimer() = default;
void LevelTimer::update() {
    // 更新时间
}

int LevelTimer::getElapsedTime() const {
    // 获取经过的时间（秒）
    return static_cast<int>((clock() - startTime) / CLOCKS_PER_SEC);
}
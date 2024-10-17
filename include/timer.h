#pragma once
#ifndef TIMER_H
#define TIMER_H

#include<ctime>

// 计时器类
class LevelTimer {
private:
    clock_t startTime;
public:
    LevelTimer();
    ~LevelTimer();
    void update();
    int getElapsedTime() const;         // 获取经过的时间（秒）
};

#endif // !TIMER_H

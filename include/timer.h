#pragma once
#ifndef TIMER_H
#define TIMER_H

#include<ctime>

// ��ʱ����
class LevelTimer {
private:
    clock_t startTime;
public:
    LevelTimer();
    ~LevelTimer();
    void update();
    int getElapsedTime() const;         // ��ȡ������ʱ�䣨�룩
};

#endif // !TIMER_H

#pragma once
#ifndef MENU_H
#define MENU_H

#include <graphics.h>
#include"settings.h"
#include"voice.h"
#include"game.h"
#include <wchar.h>
#include <easyx.h>
#include <algorithm>


void initializeFont();			//调整字体和背景样式
void drawButton(int x, int y, int width, int height, const TCHAR* text, COLORREF color);		// 改进的按钮绘制函数
void drawMenuBackground(const TCHAR* title);	// 改进的菜单背景绘制函数
void showMainMenu();							//绘制主菜单
void SetVolume();								//调整音量
void showGameSettings();						//绘制游戏设置菜单
void game_set_opera();							//绘制操作设置菜单
bool gamestop(int currentLevel);				//绘制游戏暂停菜单
void gameend1(int currentLevel);				//绘制游戏失败菜单
void gameend2(int currentLevel);				//绘制游戏胜利菜单
void startSinglePlayerGame();					//绘制关卡选择菜单



#endif // !MENU_H

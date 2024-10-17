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


void initializeFont();			//��������ͱ�����ʽ
void drawButton(int x, int y, int width, int height, const TCHAR* text, COLORREF color);		// �Ľ��İ�ť���ƺ���
void drawMenuBackground(const TCHAR* title);	// �Ľ��Ĳ˵��������ƺ���
void showMainMenu();							//�������˵�
void SetVolume();								//��������
void showGameSettings();						//������Ϸ���ò˵�
void game_set_opera();							//���Ʋ������ò˵�
bool gamestop(int currentLevel);				//������Ϸ��ͣ�˵�
void gameend1(int currentLevel);				//������Ϸʧ�ܲ˵�
void gameend2(int currentLevel);				//������Ϸʤ���˵�
void startSinglePlayerGame();					//���ƹؿ�ѡ��˵�



#endif // !MENU_H

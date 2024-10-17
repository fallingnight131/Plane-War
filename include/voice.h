#pragma once
#ifndef VOICE_H
#define VOICE_H

#include <windows.h>
#include <tchar.h>
#include <cstdio>
#include <iostream>
#include <fstream>

bool aliasExists(const TCHAR* alias);
void playMusic(const TCHAR* filePath);
void setVolume(int volume);
int getCurrentVolume();				//��ȡ��ǰ����

#endif // !VOICE_H

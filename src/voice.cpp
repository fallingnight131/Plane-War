#include"../include/voice.h"

// 音乐播放
// 全局变量，用于跟踪当前音量
int currentVolume = 50;

// 检查别名是否存在
bool aliasExists(const TCHAR* alias) {
    MCIERROR mciError;
    TCHAR statusCommand[256];
    TCHAR returnString[128];

    _stprintf_s(statusCommand, _T("status %s mode"), alias);
    mciError = mciSendString(statusCommand, returnString, 128, NULL);
    return (mciError == 0);
}


// 播放背景音乐
void playMusic(const TCHAR* filePath) {
    MCIERROR mciError;
    TCHAR errorText[128];

    // 检查文件是否存在
    std::ifstream file(filePath);
    if (!file) {
        std::wcerr << L"Error: File not found" << std::endl;
        return;
    }
    file.close();

    // 停止当前播放的音乐并关闭文件（如果存在）
    if (aliasExists(_T("bgm"))) {
        mciSendString(_T("stop bgm"), NULL, 0, NULL);
        mciSendString(_T("close bgm"), NULL, 0, NULL);
    }

    // 打开新的音频文件
    TCHAR command[256];
    _stprintf_s(command, _T("open %s alias bgm"), filePath);
    mciError = mciSendString(command, NULL, 0, NULL);
    if (mciError) {
        mciGetErrorString(mciError, errorText, 128);
        std::wcerr << L"Error opening file: " << errorText << std::endl;
        return;
    }

    // 播放新的音频文件
    mciError = mciSendString(_T("play bgm repeat"), NULL, 0, NULL);
    if (mciError) {
        mciGetErrorString(mciError, errorText, 128);
        std::wcerr << L"Error playing file: " << errorText << std::endl;
    }

    // 设置音量
    setVolume(currentVolume);
}

void setVolume(int volume) {
    currentVolume = volume;
    TCHAR volumeCommand[50];
    _stprintf_s(volumeCommand, _T("setaudio bgm volume to %d"), volume * 10); // 音量范围 0-1000
    mciSendString(volumeCommand, NULL, 0, NULL);
}

int getCurrentVolume() {
    return currentVolume;
}

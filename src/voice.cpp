#include"../include/voice.h"

// ���ֲ���
// ȫ�ֱ��������ڸ��ٵ�ǰ����
int currentVolume = 50;

// �������Ƿ����
bool aliasExists(const TCHAR* alias) {
    MCIERROR mciError;
    TCHAR statusCommand[256];
    TCHAR returnString[128];

    _stprintf_s(statusCommand, _T("status %s mode"), alias);
    mciError = mciSendString(statusCommand, returnString, 128, NULL);
    return (mciError == 0);
}


// ���ű�������
void playMusic(const TCHAR* filePath) {
    MCIERROR mciError;
    TCHAR errorText[128];

    // ����ļ��Ƿ����
    std::ifstream file(filePath);
    if (!file) {
        std::wcerr << L"Error: File not found" << std::endl;
        return;
    }
    file.close();

    // ֹͣ��ǰ���ŵ����ֲ��ر��ļ���������ڣ�
    if (aliasExists(_T("bgm"))) {
        mciSendString(_T("stop bgm"), NULL, 0, NULL);
        mciSendString(_T("close bgm"), NULL, 0, NULL);
    }

    // ���µ���Ƶ�ļ�
    TCHAR command[256];
    _stprintf_s(command, _T("open %s alias bgm"), filePath);
    mciError = mciSendString(command, NULL, 0, NULL);
    if (mciError) {
        mciGetErrorString(mciError, errorText, 128);
        std::wcerr << L"Error opening file: " << errorText << std::endl;
        return;
    }

    // �����µ���Ƶ�ļ�
    mciError = mciSendString(_T("play bgm repeat"), NULL, 0, NULL);
    if (mciError) {
        mciGetErrorString(mciError, errorText, 128);
        std::wcerr << L"Error playing file: " << errorText << std::endl;
    }

    // ��������
    setVolume(currentVolume);
}

void setVolume(int volume) {
    currentVolume = volume;
    TCHAR volumeCommand[50];
    _stprintf_s(volumeCommand, _T("setaudio bgm volume to %d"), volume * 10); // ������Χ 0-1000
    mciSendString(volumeCommand, NULL, 0, NULL);
}

int getCurrentVolume() {
    return currentVolume;
}

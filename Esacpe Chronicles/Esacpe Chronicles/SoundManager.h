#pragma once
#include <dsound.h>
#include <string>
#include <vector>

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")

class SoundManager {
public:
    SoundManager(HWND hWnd);
    ~SoundManager();

    bool Initialize();
    void PlayBGM(const std::wstring& filePath);
    void StopBGM();
    void PlayEffect(const std::wstring& filePath);

private:
    bool LoadWaveFile(const std::wstring& filePath, IDirectSoundBuffer8** buffer);
    void PlaySoundBuffer(IDirectSoundBuffer8* buffer);

    IDirectSound8* directSound;
    IDirectSoundBuffer* primaryBuffer;
    IDirectSoundBuffer8* bgmBuffer;
    HWND hWnd;
};
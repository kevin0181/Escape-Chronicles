#pragma once

#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <windows.h>  // windows.h 추가
#include <mmsystem.h> // mmsystem.h 추가
#include <dsound.h>
#include <string>
#include <map>

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")

class SoundManager {
public:
    SoundManager();
    ~SoundManager();

    bool Initialize(HWND hwnd);
    void Shutdown();
    bool LoadWaveFile(const std::wstring& filename, const std::wstring& soundName);
    void PlaySoundW(const std::wstring& soundName, bool loop = false);
    void SetVolume(const std::wstring& soundName, LONG volume);

private:
    bool InitializeDirectSound(HWND hwnd);
    void ShutdownDirectSound();
    void ShutdownWaveFile(LPDIRECTSOUNDBUFFER& buffer);

    IDirectSound8* directSound;
    IDirectSoundBuffer* primaryBuffer;
    std::map<std::wstring, LPDIRECTSOUNDBUFFER> soundMap;
};

#endif // SOUNDMANAGER_H

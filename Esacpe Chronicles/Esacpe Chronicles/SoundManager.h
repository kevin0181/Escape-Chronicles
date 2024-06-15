#pragma once
#include <dsound.h>
#include <string>
#include <map>
#include <memory>

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
    void SetVolume(const std::wstring& soundName, LONG volume); // 볼륨 조절 함수 추가

private:
    bool InitializeDirectSound(HWND hwnd);
    void ShutdownDirectSound();
    void ShutdownWaveFile(LPDIRECTSOUNDBUFFER& buffer);

    IDirectSound8* directSound;
    IDirectSoundBuffer* primaryBuffer;
    std::map<std::wstring, LPDIRECTSOUNDBUFFER> soundMap;
};

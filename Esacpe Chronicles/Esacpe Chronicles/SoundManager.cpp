#include "SoundManager.h"
#include <stdexcept>
#include <iostream>
#include <fstream>

SoundManager::SoundManager() : directSound(nullptr), primaryBuffer(nullptr) {}

SoundManager::~SoundManager() {
    Shutdown();
}

bool SoundManager::Initialize(HWND hwnd) {
    if (!InitializeDirectSound(hwnd)) {
        return false;
    }
    return true;
}

void SoundManager::Shutdown() {
    for (auto& sound : soundMap) {
        ShutdownWaveFile(sound.second);
    }
    ShutdownDirectSound();
}

bool SoundManager::LoadWaveFile(const std::wstring& filename, const std::wstring& soundName) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::wcerr << L"Could not open file: " << filename << std::endl;
        return false;
    }

    // Read the wave file header
    WAVEFORMATEX waveFormat;
    DSBUFFERDESC bufferDesc;
    unsigned char* waveData;
    unsigned long waveSize;
    LPDIRECTSOUNDBUFFER tempBuffer;
    file.seekg(0, std::ios::end);
    waveSize = file.tellg();
    waveData = new unsigned char[waveSize];
    file.seekg(0, std::ios::beg);
    file.read(reinterpret_cast<char*>(waveData), waveSize);
    file.close();

    // Fill the wave format structure
    waveFormat.wFormatTag = WAVE_FORMAT_PCM;
    waveFormat.nSamplesPerSec = 44100;
    waveFormat.wBitsPerSample = 16;
    waveFormat.nChannels = 2;
    waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
    waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
    waveFormat.cbSize = 0;

    // Set the buffer description
    bufferDesc.dwSize = sizeof(DSBUFFERDESC);
    bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME;
    bufferDesc.dwBufferBytes = waveSize;
    bufferDesc.dwReserved = 0;
    bufferDesc.lpwfxFormat = &waveFormat;

    // Create a temporary sound buffer
    HRESULT result = directSound->CreateSoundBuffer(&bufferDesc, &tempBuffer, nullptr);
    if (FAILED(result)) {
        delete[] waveData;
        return false;
    }

    // Lock the buffer
    unsigned char* bufferPtr;
    unsigned long bufferSize;
    result = tempBuffer->Lock(0, waveSize, (void**)&bufferPtr, &bufferSize, nullptr, 0, 0);
    if (FAILED(result)) {
        delete[] waveData;
        return false;
    }

    // Copy the wave data into the buffer
    memcpy(bufferPtr, waveData, waveSize);
    tempBuffer->Unlock(bufferPtr, bufferSize, nullptr, 0);
    delete[] waveData;

    // Store the buffer in the map
    soundMap[soundName] = tempBuffer;
    return true;
}

void SoundManager::PlaySoundW(const std::wstring& soundName, bool loop) {
    auto it = soundMap.find(soundName);
    if (it == soundMap.end()) {
        std::wcerr << L"Sound not found: " << soundName << std::endl;
        return;
    }

    DWORD flags = 0;
    if (loop) {
        flags = DSBPLAY_LOOPING;
    }
    it->second->SetCurrentPosition(0);
    it->second->Play(0, 0, flags);
}

void SoundManager::SetVolume(const std::wstring& soundName, LONG volume) {
    auto it = soundMap.find(soundName);
    if (it != soundMap.end()) {
        it->second->SetVolume(volume);
    }
}

bool SoundManager::InitializeDirectSound(HWND hwnd) {
    HRESULT result = DirectSoundCreate8(nullptr, &directSound, nullptr);
    if (FAILED(result)) {
        return false;
    }

    result = directSound->SetCooperativeLevel(hwnd, DSSCL_PRIORITY);
    if (FAILED(result)) {
        return false;
    }

    DSBUFFERDESC bufferDesc;
    bufferDesc.dwSize = sizeof(DSBUFFERDESC);
    bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER;
    bufferDesc.dwBufferBytes = 0;
    bufferDesc.dwReserved = 0;
    bufferDesc.lpwfxFormat = nullptr;

    result = directSound->CreateSoundBuffer(&bufferDesc, &primaryBuffer, nullptr);
    if (FAILED(result)) {
        return false;
    }

    WAVEFORMATEX waveFormat;
    waveFormat.wFormatTag = WAVE_FORMAT_PCM;
    waveFormat.nSamplesPerSec = 44100;
    waveFormat.wBitsPerSample = 16;
    waveFormat.nChannels = 2;
    waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
    waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
    waveFormat.cbSize = 0;

    result = primaryBuffer->SetFormat(&waveFormat);
    if (FAILED(result)) {
        return false;
    }

    return true;
}

void SoundManager::ShutdownDirectSound() {
    if (primaryBuffer) {
        primaryBuffer->Release();
        primaryBuffer = nullptr;
    }

    if (directSound) {
        directSound->Release();
        directSound = nullptr;
    }
}

void SoundManager::ShutdownWaveFile(LPDIRECTSOUNDBUFFER& buffer) {
    if (buffer) {
        buffer->Release();
        buffer = nullptr;
    }
}

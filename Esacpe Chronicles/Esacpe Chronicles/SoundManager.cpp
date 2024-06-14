#include "SoundManager.h"
#include <stdexcept>
#include <fstream>

SoundManager::SoundManager(HWND hWnd) : directSound(nullptr), primaryBuffer(nullptr), bgmBuffer(nullptr), hWnd(hWnd) {}

SoundManager::~SoundManager() {
    if (primaryBuffer) {
        primaryBuffer->Release();
        primaryBuffer = nullptr;
    }
    if (bgmBuffer) {
        bgmBuffer->Release();
        bgmBuffer = nullptr;
    }
    if (directSound) {
        directSound->Release();
        directSound = nullptr;
    }
}

bool SoundManager::Initialize() {
    if (FAILED(DirectSoundCreate8(NULL, &directSound, NULL))) {
        return false;
    }
    if (FAILED(directSound->SetCooperativeLevel(hWnd, DSSCL_PRIORITY))) {
        return false;
    }
    DSBUFFERDESC bufferDesc;
    ZeroMemory(&bufferDesc, sizeof(DSBUFFERDESC));
    bufferDesc.dwSize = sizeof(DSBUFFERDESC);
    bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER;
    if (FAILED(directSound->CreateSoundBuffer(&bufferDesc, &primaryBuffer, NULL))) {
        return false;
    }
    WAVEFORMATEX waveFormat;
    ZeroMemory(&waveFormat, sizeof(WAVEFORMATEX));
    waveFormat.wFormatTag = WAVE_FORMAT_PCM;
    waveFormat.nSamplesPerSec = 44100;
    waveFormat.wBitsPerSample = 16;
    waveFormat.nChannels = 2;
    waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
    waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
    if (FAILED(primaryBuffer->SetFormat(&waveFormat))) {
        return false;
    }
    return true;
}

void SoundManager::PlayBGM(const std::wstring& filePath) {
    if (bgmBuffer) {
        bgmBuffer->Release();
        bgmBuffer = nullptr;
    }
    if (LoadWaveFile(filePath, &bgmBuffer)) {
        PlaySoundBuffer(bgmBuffer);
    }
}

void SoundManager::StopBGM() {
    if (bgmBuffer) {
        bgmBuffer->Stop();
        bgmBuffer->Release();
        bgmBuffer = nullptr;
    }
}

void SoundManager::PlayEffect(const std::wstring& filePath) {
    IDirectSoundBuffer8* effectBuffer;
    if (LoadWaveFile(filePath, &effectBuffer)) {
        PlaySoundBuffer(effectBuffer);
        effectBuffer->Release();
    }
}

bool SoundManager::LoadWaveFile(const std::wstring& filePath, IDirectSoundBuffer8** buffer) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        return false;
    }

    char chunkId[4];
    file.read(chunkId, 4);
    if (strncmp(chunkId, "RIFF", 4) != 0) {
        return false;
    }

    file.seekg(22);
    uint16_t numChannels;
    file.read(reinterpret_cast<char*>(&numChannels), sizeof(numChannels));

    uint32_t sampleRate;
    file.read(reinterpret_cast<char*>(&sampleRate), sizeof(sampleRate));

    file.seekg(34);
    uint16_t bitsPerSample;
    file.read(reinterpret_cast<char*>(&bitsPerSample), sizeof(bitsPerSample));

    file.seekg(40);
    uint32_t dataSize;
    file.read(reinterpret_cast<char*>(&dataSize), sizeof(dataSize));

    std::vector<char> waveData(dataSize);
    file.read(waveData.data(), dataSize);

    WAVEFORMATEX waveFormat;
    ZeroMemory(&waveFormat, sizeof(WAVEFORMATEX));
    waveFormat.wFormatTag = WAVE_FORMAT_PCM;
    waveFormat.nSamplesPerSec = sampleRate;
    waveFormat.wBitsPerSample = bitsPerSample;
    waveFormat.nChannels = numChannels;
    waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
    waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;

    DSBUFFERDESC bufferDesc;
    ZeroMemory(&bufferDesc, sizeof(DSBUFFERDESC));
    bufferDesc.dwSize = sizeof(DSBUFFERDESC);
    bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME;
    bufferDesc.dwBufferBytes = dataSize;
    bufferDesc.lpwfxFormat = &waveFormat;

    IDirectSoundBuffer* tempBuffer;
    if (FAILED(directSound->CreateSoundBuffer(&bufferDesc, &tempBuffer, NULL))) {
        return false;
    }

    if (FAILED(tempBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)buffer))) {
        tempBuffer->Release();
        return false;
    }
    tempBuffer->Release();

    void* bufferPtr;
    DWORD bufferSize;
    if (FAILED((*buffer)->Lock(0, dataSize, &bufferPtr, &bufferSize, NULL, NULL, 0))) {
        (*buffer)->Release();
        return false;
    }

    memcpy(bufferPtr, waveData.data(), dataSize);
    (*buffer)->Unlock(bufferPtr, bufferSize, NULL, 0);

    return true;
}

void SoundManager::PlaySoundBuffer(IDirectSoundBuffer8* buffer) {
    buffer->SetCurrentPosition(0);
    buffer->Play(0, 0, DSBPLAY_LOOPING);
}
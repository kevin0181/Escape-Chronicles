#pragma once

#include <Windows.h>
#include <atlimage.h>
#include <memory>

class Block {
private:
    RECT rect;
    std::unique_ptr<CImage> cImage;
    LPCTSTR path_stage1 = L"img/block/blue_block.png";
public:

    // Default constructor
    Block(const RECT& stageRect) : cImage(std::make_unique<CImage>()) {
        rect = { 0, 0, 70, 70 };
        OffsetRect(&rect, 0, stageRect.bottom - 210);
        HRESULT hr = cImage->Load(path_stage1);
        if (FAILED(hr)) {
            // Load failed
            MessageBox(NULL, L"블록 이미지 로드 실패", L"오류", MB_OK);
        }
    }

    // Move constructor
    Block(Block&& other) noexcept : rect(other.rect), cImage(std::move(other.cImage)) {
        other.rect = { 0, 0, 70, 70 };
    }

    // Move assignment operator
    Block& operator=(Block&& other) noexcept {
        if (this != &other) {
            rect = other.rect;
            cImage = std::move(other.cImage);
            other.rect = { 0, 0, 70, 70 };
        }
        return *this;
    }

    // Deleted copy constructor and copy assignment operator to avoid copying
    Block(const Block&) = delete;
    Block& operator=(const Block&) = delete;
    void print(HDC& mDC, int i, int h) const;
};

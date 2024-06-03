#include "Block.h"

#define BLOCK_SIZE 70

void Block::print(HDC& mDC, int w, int h) const {
    if (!cImage->IsNull()) {
        // 각 블록의 x 좌표를 70*w로, y 좌표를 70*h로 설정
        int xOffset = BLOCK_SIZE * w;
        int yOffset = BLOCK_SIZE * h;
        RECT drawRect = { rect.left + xOffset, rect.top + yOffset, rect.right + xOffset, rect.bottom + yOffset };

        cImage->Draw(mDC, drawRect.left, drawRect.top, drawRect.right - drawRect.left, drawRect.bottom - drawRect.top, 0, 0, cImage->GetWidth(), cImage->GetHeight());
    }
    else {
        // Invalid image
        MessageBox(NULL, L"유효하지 않은 블록 이미지", L"오류", MB_OK);
    }
}
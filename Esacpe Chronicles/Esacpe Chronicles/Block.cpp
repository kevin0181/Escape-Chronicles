#include "Block.h"

#define BLOCK_SIZE 70

void Block::print(HDC& mDC, int w, int h) const {
    if (!cImage->IsNull()) {
        // �� ����� x ��ǥ�� 70*w��, y ��ǥ�� 70*h�� ����
        int xOffset = BLOCK_SIZE * w;
        int yOffset = BLOCK_SIZE * h;
        RECT drawRect = { rect.left + xOffset, rect.top + yOffset, rect.right + xOffset, rect.bottom + yOffset };

        cImage->Draw(mDC, drawRect.left, drawRect.top, drawRect.right - drawRect.left, drawRect.bottom - drawRect.top, 0, 0, cImage->GetWidth(), cImage->GetHeight());
    }
    else {
        // Invalid image
        MessageBox(NULL, L"��ȿ���� ���� ��� �̹���", L"����", MB_OK);
    }
}
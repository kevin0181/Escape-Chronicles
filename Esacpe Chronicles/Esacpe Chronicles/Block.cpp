#include "Block.h"
const LPCTSTR Block::path_stage1 = _T("img/block/blue_block.png");

void Block::print(HDC& mDC) const {
    if (!cImage->IsNull()) {
       cImage->Draw(mDC, rect.left, rect.top, rect.right - rect.left,
           rect.bottom - rect.top, 0, 0, cImage->GetWidth(), cImage->GetHeight());
    }
    else {
        // Invalid image
        MessageBox(NULL, L"��ȿ���� ���� ��� �̹���", L"����", MB_OK);
    }
}
#include "Block.h"

const LPCTSTR Block::path_stage1 = _T("img/block/blue_block.png");

void Block::print(HDC& mDC) const {
	HBRUSH hBrush = CreateSolidBrush(color);
	HBRUSH oldBrush = (HBRUSH) SelectObject(mDC, hBrush);

	Rectangle(mDC, rect.left, rect.top, rect.right, rect.bottom);

	SelectObject(mDC, oldBrush);
	DeleteObject(hBrush);
}
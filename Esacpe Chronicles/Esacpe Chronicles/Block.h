#pragma once

#include <Windows.h>
#include <atlimage.h>

class Block {
private:
	RECT rect;
	CImage cImage;
	LPCTSTR path = L"img/block/blue_block.png";
public:
	
	Block() {
		rect = { 0,0,20,20 };
		cImage.Load(path);
	}

	void print(HDC& mDC) {
		//cImage.Draw(mDC, 0, 0, rect.right, rect.bottom, 0, 0, cImage.GetWidth(), cImage.GetHeight());
		cImage.Draw(mDC, rect);
	}
};
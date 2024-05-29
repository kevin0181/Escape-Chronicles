#include <iostream>
#include <atlimage.h>
#include "Monster.h"
#include "Slime.h"
using namespace std;



void Slime::insert() {
	const wchar_t* imagePath[9] = { L"Slime_0",
	L"Slime_1",
	L"Slime_2",
	L"Slime_3",
	L"Slime_4",
	L"Slime_5",
	L"Slime_6",
	L"Slime_7",
	L"Slime_8"
	};
	
	img[0].Load(L"Slime_0");
	HRESULT result[9];

	for (int i = 0; i < 9; ++i) {
		result[i] = img[i].Load(imagePath[i]);
		if (FAILED(result)) {
			return;
		}
	}
}

void Slime::print(HDC& mDC, int imagenum,RECT rect, int x, int y) {
	int width = 100;
	int Height = 100;
	img[imagenum].Draw(mDC, x, y, rect.right - rect.left, rect.bottom - rect.top, 0, 0, width, Height);
}

void Slime::move(RECT rect, bool left) {
	if (left) {
		rect.left -= 2;
		rect.right -= 2;
		if (rect.left <= 0) {// 왼쪽 끝에 도달하면 방향 변경
			left = true;
		}
	}
	else {
		rect.left += 2;
		rect.right += 2;
		if (rect.right >= 1536) { // 오른쪽 끝에 도달하면 방향 변경
			left = false;
		}
	}
}

void Slime::attack() {

}
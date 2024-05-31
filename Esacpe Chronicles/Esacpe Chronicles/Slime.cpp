#include <iostream>
#include <atlimage.h>
#include "Monster.h"
#include "Slime.h"
using namespace std;

Slime::Slime() : Monster() {
	hp = 0; // 나중에 확정되면 바꾸기
	imageNum = 0;
	rect = { 500, 300, 700, 420 };
	left = true;
	bool_attack = true;
}

RECT Slime::getRect() const {
	return rect;
}

void Slime::insert() {
	if (!slime_img.IsNull()) {
		slime_img.Destroy();
	}

	if (hp != 0) {
		if (bool_attack) { 
			// 공격할 때
			slime_img.Load(slime_attack_img_path[imageNum]);
		}
		else {
			// 걍 움직일 떄
			slime_img.Load(slime_img_path[imageNum]);
		}
	}
	else {
		// 죽었을 떄
		slime_img.Load(slime_die_img_path[imageNum]);
	}
}

void Slime::print(HDC& mDC) {
	if (!slime_img.IsNull()) {
		slime_img.Draw(mDC, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0, 0, slime_img.GetWidth(), slime_img.GetHeight());
		//slime_img.StretchBlt(mDC, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0, 0, slime_img.GetWidth(), slime_img.GetHeight(),SRCCOPY);

	}
}

void Slime::move(RECT Rect) {
	if (left) {
		rect.left -= 2;
		rect.right -= 2;
		if (rect.left <= Rect.left) {// 왼쪽 끝에 도달하면 방향 변경
			left = true;
		}
	}
	else {
		rect.left += 2;
		rect.right += 2;
		if (rect.right >= Rect.right) { // 오른쪽 끝에 도달하면 방향 변경
			left = false;
		}
	}

	++imageNum;
	if (imageNum == 9) {
		imageNum = 0;
	}

	insert();
}

void Slime::attack() {
	bool_attack = true;
}

void Slime::die() {


}
#include <iostream>
#include <atlimage.h>
#include "Monster.h"
#include "Slime.h"
#include "Collision.h"
using namespace std;

Slime::Slime() : Monster() {
	hp = 500; // 나중에 확정되면 바꾸기
	imageNum = 0;
	rect = { 110, 300, 310, 420 };

	left = true;
	bool_attack = false;
}

RECT& Slime::getRect() {
	return rect;
}

void Slime::insert() {
	if (!slime_img.IsNull()) {
		slime_img.Destroy();
	}

	if(left){
		if (hp != 0) {
			if (bool_attack)// 공격할 때
				slime_img.Load(slime_attack_img_path_L[imageNum]);
			else// 걍 움직일 떄
				slime_img.Load(slime_img_path_L[imageNum]);
		}
		else// 죽었을 떄
			slime_img.Load(slime_die_img_path_L[imageNum]);
	}
	else {
		if (hp != 0) {
			if (bool_attack)// 공격할 때
				slime_img.Load(slime_attack_img_path_R[imageNum]);
			else// 걍 움직일 떄
				slime_img.Load(slime_img_path_R[imageNum]);
		}
		else// 죽었을 떄
			slime_img.Load(slime_die_img_path_R[imageNum]);
	}
}

void Slime::print(HDC& mDC) {
	if (!slime_img.IsNull() && (hp != 0 || imageNum != 9)) {
		slime_img.Draw(mDC, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0, 0, slime_img.GetWidth(), slime_img.GetHeight());
	}
}

void Slime::move(RECT Rect) {
	if (hp != 0) {
		++imageNum;
	}

	if(hp!=0&&!bool_attack){
		if (left) {
			OffsetRect(&rect, -2, 0);
			if (CheckBlockCollision(Rect, { 0,0,0,0 }, left, rect)) { // 화면 끝 도달 시 방향 변경
				OffsetRect(&rect, 2, 0);
				left = false;
			}
		}
		else {
			OffsetRect(&rect, 2, 0);
			if (CheckBlockCollision(Rect, { 0,0,0,0 }, left, rect)) {
				OffsetRect(&rect, -2, 0);
				left = true;
			}
		}

		if (CheckBlockCollision(Rect, { 0,0,0,0 }, left,rect))
			OffsetRect(&rect, 0, -4.5f);
	}

	if (imageNum == 9) {
		imageNum = 0;
		if (hp == 0) {
			slime_img.Destroy();
		}
	}

	if(hp!=0){
		insert();
	}
}

void Slime::attack(bool status) {
	bool_attack = status;
}
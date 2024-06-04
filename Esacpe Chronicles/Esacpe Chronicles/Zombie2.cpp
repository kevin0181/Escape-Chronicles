#include <iostream>
#include <atlimage.h>
#include "Monster.h"
#include "Zombie2.h"
using namespace std;

//srand(time(nullptr));

Zombie2::Zombie2() : Monster() {
	hp = 500; // 나중에 확정되면 바꾸기
	imageNum = 0;
	rect = { 1000, 300, 1200, 500 };
	left = false;
	bool_attack = true;
}

RECT Zombie2::getRect() const {
	return rect;
}

void Zombie2::insert() {
	if (!zombie2_img.IsNull()) {
		zombie2_img.Destroy();
	}

	if (left) {
		if (hp != 0) {
			if (bool_attack)// 공격할 때
				zombie2_img.Load(zombie2_attack_img_path_L[imageNum]);
			else// 걍 움직일 떄
				zombie2_img.Load(zombie2_img_path_L[imageNum]);
		}
		else// 죽었을 떄
			zombie2_img.Load(zombie2_die_img_path_L[imageNum]);
	}
	else{
		if (hp != 0) {
			if (bool_attack)// 공격할 때
				zombie2_img.Load(zombie2_attack_img_path_R[imageNum]);
			else// 걍 움직일 떄
				zombie2_img.Load(zombie2_img_path_R[imageNum]);
		}
		else// 죽었을 떄
			zombie2_img.Load(zombie2_die_img_path_R[imageNum]);
	}
}

void Zombie2::print(HDC& mDC) {
	if (!zombie2_img.IsNull() && (hp != 0 || imageNum != 5)) {
		zombie2_img.Draw(mDC, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0, 0, zombie2_img.GetWidth(), zombie2_img.GetHeight());
	}
}

void Zombie2::move(RECT Rect) {
	if (hp != 0 || imageNum != 5) {
		++imageNum;
	}

	if (hp != 0) {
		if (bool_attack && imageNum == 4) {
			// 공격할 때
			imageNum = 0;
		}
		else if (!bool_attack) {
			// 걍 움직일 떄
			if (left) {
				rect.left -= 4;
				rect.right -= 4;
				if (CheckBlockCollision(Rect, { 0,0,0,0 }, left, rect)) // 화면 끝 도달 시 방향 변경
					left = false;
			}
			else {
				rect.left += 4;
				rect.right += 4;
				if (CheckBlockCollision(Rect, { 0,0,0,0 }, left, rect))
					left = true;
			}

			if (imageNum == 7) {
				imageNum = 0;
			}
		}
	}
	else if (hp == 0 && imageNum == 5) {
		// 죽었을 떄
		zombie2_img.Destroy();
	}

	if (hp != 0 || imageNum != 5) {
		insert();
	}
}

void Zombie2::attack(bool status) {
	bool_attack = status;
}

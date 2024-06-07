#include <iostream>
#include <atlimage.h>
#include "Monster.h"
#include "Zombie3.h"
#include "Collision.h"
using namespace std;

//srand(time(nullptr));

Zombie3::Zombie3() : Monster() {
	hp = 0; // 나중에 확정되면 바꾸기
	imageNum = 0;
	rect = { 300, 300, 500, 500 };
	left = false;
	bool_attack = true;
}

RECT Zombie3::getRect() const {
	return rect;
}

void Zombie3::insert() {
	if (!zombie3_img.IsNull()) {
		zombie3_img.Destroy();
	}

	if (left) {
		if (hp != 0) {
			if (bool_attack)// 공격할 때
				zombie3_img.Load(zombie3_attack_img_path_L[imageNum]);
			else// 걍 움직일 떄
				zombie3_img.Load(zombie3_img_path_L[imageNum]);
		}
		else// 죽었을 떄
			zombie3_img.Load(zombie3_die_img_path_L[imageNum]);
	}
	
	else{
		if (hp != 0) {
			if (bool_attack)// 공격할 때
				zombie3_img.Load(zombie3_attack_img_path_R[imageNum]);
			else// 걍 움직일 떄
				zombie3_img.Load(zombie3_img_path_R[imageNum]);
		}
		else// 죽었을 떄
			zombie3_img.Load(zombie3_die_img_path_R[imageNum]);
	}
}

void Zombie3::print(HDC& mDC) {
	if (!zombie3_img.IsNull()&& (hp != 0 || imageNum != 5)) {
		zombie3_img.Draw(mDC, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0, 0, zombie3_img.GetWidth(), zombie3_img.GetHeight());
	}
}

void Zombie3::move(RECT Rect) {
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

			if(imageNum==10){
				imageNum = 0;
			}
		}
	}
	else if (hp == 0 && imageNum == 5) {
		// 죽었을 떄
		zombie3_img.Destroy();
	}

	if (hp != 0 || imageNum != 5) {
		insert();
	}
}

void Zombie3::attack(bool status) {
	bool_attack = status;
}

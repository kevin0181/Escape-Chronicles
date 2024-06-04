#include <iostream>
#include <atlimage.h>
#include "Monster.h"
#include "Zombie1.h"
using namespace std;

//srand(time(nullptr));

Zombie1::Zombie1() : Monster() {
	hp = 0; // ���߿� Ȯ���Ǹ� �ٲٱ�
	imageNum = 0;
	rect = { 1300, 300, 1500, 500 };
	left = false;
	bool_attack = false;
}

RECT Zombie1::getRect() const {
	return rect;
}

void Zombie1::insert() {
	if (!zombie1_img.IsNull()) {
		zombie1_img.Destroy();
	}

	if (left) {
		if (hp != 0) {
			if (bool_attack)// ������ ��
				zombie1_img.Load(zombie1_attack_img_path_L[imageNum]);
			else// �� ������ ��
				zombie1_img.Load(zombie1_img_path_L[imageNum]);
		}
		else// �׾��� ��
			zombie1_img.Load(zombie1_die_img_path_L[imageNum]);
	}
	else{
		if (hp != 0) {
			if (bool_attack)// ������ ��
				zombie1_img.Load(zombie1_attack_img_path_R[imageNum]);
			else// �� ������ ��
				zombie1_img.Load(zombie1_img_path_R[imageNum]);
		}
		else// �׾��� ��
			zombie1_img.Load(zombie1_die_img_path_R[imageNum]);
	}
}

void Zombie1::print(HDC& mDC) {
	if (!zombie1_img.IsNull() && (hp != 0 || imageNum != 4)) {
		zombie1_img.Draw(mDC, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0, 0, zombie1_img.GetWidth(), zombie1_img.GetHeight());
	}
}

void Zombie1::move(RECT Rect) {
	if (hp != 0 || imageNum != 4) {
		++imageNum;
	}

	if (hp != 0) {
		if (bool_attack && imageNum == 5) {
			// ������ ��
			imageNum = 0;
		}
		else if (!bool_attack) {
			// �� ������ ��
			if (left) {
				rect.left -= 4;
				rect.right -= 4;
				if (CheckBlockCollision(Rect, { 0,0,0,0 }, left, rect)) // ȭ�� �� ���� �� ���� ����
					left = false;
			}
			else {
				rect.left += 4;
				rect.right += 4;
				if (CheckBlockCollision(Rect, { 0,0,0,0 }, left, rect))
					left = true;
			}

			if (imageNum == 8) {
				imageNum = 0;
			}
		}
	}
	else if (hp == 0 && imageNum == 4) {
		// �׾��� ��
		zombie1_img.Destroy();
	}

	if (hp != 0 || imageNum != 4) {
		insert();
	}
}

void Zombie1::attack(bool status) {
	bool_attack = status;
}

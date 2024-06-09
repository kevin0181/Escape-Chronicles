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
	status = MOVE_;
}

RECT& Slime::getRect() {
	return rect;
}

void Slime::insert() {
	if (!slime_img.IsNull()) {
		slime_img.Destroy();
	}

	if (left) {
		switch (status) {
		case MOVE_:
			slime_img.Load(slime_img_path_L[imageNum]);
			break;
		case ATTACK_:
			slime_img.Load(slime_attack_img_path_L[imageNum]);
			break;
		case DIE_:
			slime_img.Load(slime_die_img_path_L[imageNum]);
			break;
		}	
	}
	else {
		switch (status) {
		case MOVE_:
			slime_img.Load(slime_img_path_R[imageNum]);
			break;
		case ATTACK_:
			slime_img.Load(slime_attack_img_path_R[imageNum]);
			break;
		case DIE_:
			slime_img.Load(slime_die_img_path_R[imageNum]);
			break;
		}
	}
}

void Slime::print(HDC& mDC) {
	if (!slime_img.IsNull() && (hp != 0 || imageNum != 9)) {
		slime_img.Draw(mDC, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0, 0, slime_img.GetWidth(), slime_img.GetHeight());
	}
}

void Slime::move(StageManager& stageManager,RECT Rect) {
		//중력
		RECT temprect = rect;
		gravity.UpdatePhysics(rect);

		if (CheckBlockCollision(rect, stageManager.blocks_stage1))
			rect = temprect;

		//이미지
		if (status != DIE_ || imageNum != 9)
		++imageNum;

		if (imageNum == 9) {
			if (status==DIE_)
				slime_img.Destroy();
			else
				imageNum = 0;
		}

		if(status==MOVE_) {
			int offset = left ? -2 : 2;
			OffsetRect(&rect, offset, 0);

			if (CheckClientRect(Rect,rect))
				left = !left;
		}

		if (status != DIE_ || imageNum != 9)
			insert();
}


void Slime::attack() {
	if (status == ATTACK_) {

	}
}
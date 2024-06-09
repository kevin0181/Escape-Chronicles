#include "Zombie1.h"
using namespace std;

//srand(time(nullptr));

Zombie1::Zombie1() : Monster() {
	hp = 500; // 나중에 확정되면 바꾸기
	imageNum = 0;
	rect = { 1000, 300, 1300, 600 };
	left = false;
	status = MOVE_;
}

RECT Zombie1::getRect() const {
	return rect;
}

void Zombie1::insert() {
	if (!zombie1_img.IsNull()) {
		zombie1_img.Destroy();
	}

	if (left) {
		switch (status) {
		case MOVE_:
			zombie1_img.Load(zombie1_img_path_L[imageNum]);
			break;
		case ATTACK_:
			zombie1_img.Load(zombie1_attack_img_path_L[imageNum]);
			break;
		case DIE_:
			zombie1_img.Load(zombie1_die_img_path_L[imageNum]);
			break;
		}
	}
	else {
		switch (status) {
		case MOVE_:
			zombie1_img.Load(zombie1_img_path_R[imageNum]);
			break;
		case ATTACK_:
			zombie1_img.Load(zombie1_attack_img_path_R[imageNum]);
			break;
		case DIE_:
			zombie1_img.Load(zombie1_die_img_path_R[imageNum]);
			break;
		}
	}
}

void Zombie1::print(HDC& mDC) {
	if (!zombie1_img.IsNull() && (hp != 0 || imageNum != 4)) {
		zombie1_img.Draw(mDC, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0, 0, zombie1_img.GetWidth(), zombie1_img.GetHeight());
	}
}

void Zombie1::move(StageManager& stageManager, RECT Rect) {

	//중력
	RECT temprect = rect;
	gravity.UpdatePhysics(rect);

	if (CheckBlockCollision(rect, stageManager.blocks_stage1))
		rect = temprect;

	//이미지
	if (status != DIE_ || imageNum != 4)
		++imageNum;

	switch (status) {
	case MOVE_:{
		int offset = left ? -4 : 4;
		OffsetRect(&rect, offset, 0);

		if (imageNum == 8)
			imageNum = 0;

		if (CheckClientRect(Rect, rect))
			left = !left;
	}
		break;
	case ATTACK_:
		if (imageNum == 5)
			imageNum = 0;
		break;
	case DIE_:
		if (imageNum == 4)
			zombie1_img.Destroy();
		break;
	}

	if (status != DIE_ || imageNum != 4)
		insert();
}

void Zombie1::attack() {

}

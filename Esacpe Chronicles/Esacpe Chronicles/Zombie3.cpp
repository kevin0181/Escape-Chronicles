#include "Zombie3.h"
using namespace std;

//srand(time(nullptr));

Zombie3::Zombie3() : Monster() {
	hp = 0; // 나중에 확정되면 바꾸기
	imageNum = 0;
	rect = { 300, 300, 600, 600 };
	left = false;
	status = MOVE_;
}

RECT Zombie3::getRect() const {
	return rect;
}

void Zombie3::insert() {
	if (!zombie3_img.IsNull()) {
		zombie3_img.Destroy();
	}

	if (left) {
		switch (status) {
		case MOVE_:
			zombie3_img.Load(zombie3_img_path_L[imageNum/5]);
			break;
		case ATTACK_:
			zombie3_img.Load(zombie3_attack_img_path_L[imageNum/5]);
			break;
		case DIE_:
			zombie3_img.Load(zombie3_die_img_path_L[imageNum/5]);
			break;
		}
	}
	else {
		switch (status) {
		case MOVE_:
			zombie3_img.Load(zombie3_img_path_R[imageNum/5]);
			break;
		case ATTACK_:
			zombie3_img.Load(zombie3_attack_img_path_R[imageNum/5]);
			break;
		case DIE_:
			zombie3_img.Load(zombie3_die_img_path_R[imageNum/5]);
			break;
		}
	}
}

void Zombie3::print(HDC& mDC) {
	if (!zombie3_img.IsNull()) {
		zombie3_img.Draw(mDC, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0, 0, zombie3_img.GetWidth(), zombie3_img.GetHeight());
	}
}

void Zombie3::move(StageManager& stageManager) {

	//중력
	RECT temprect = rect;
	gravity.UpdatePhysics(rect);

	if (CheckBlockCollision(rect, stageManager.blocks_stage1))
		rect = temprect;

	//이미지
	if (status != DIE_ || imageNum != 25)
		++imageNum;

	switch (status) {
	case MOVE_: {
		int offset = left ? -4 : 4;
		OffsetRect(&rect, offset, 0);

		if (imageNum == 50)
			imageNum = 0;

		if (CheckClientRect(stageManager.game_rect, rect))
			left = !left;
	}
			  break;
	case ATTACK_:
		if (imageNum == 20)
			imageNum = 0;
		break;
	case DIE_:
		if (imageNum == 25)
			zombie3_img.Destroy();
		break;
	}

	if (status != DIE_ || imageNum != 25)
		insert();
}

void Zombie3::attack() {
	
}

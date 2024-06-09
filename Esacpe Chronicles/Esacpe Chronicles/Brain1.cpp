#include "Brain1.h"
using namespace std;

//srand(time(nullptr));

Brain1::Brain1() : Monster() {
	hp = 0; // 나중에 확정되면 바꾸기
	imageNum = 0;
	rect = { 400, 500, 650, 750 };
	left = false;
	status = MOVE_;
}

RECT Brain1::getRect() const {
	return rect;
}

void Brain1::insert() {
	if (!brain1_img.IsNull()) {
		brain1_img.Destroy();
	}

	if (left) {
		switch (status) {
		case MOVE_:
			brain1_img.Load(brain1_img_path_L[imageNum]);
			break;
		case ATTACK_:
			brain1_img.Load(brain1_attack_img_path_L[imageNum]);
			break;
		case DIE_:
			brain1_img.Load(brain1_die_img_path_L[imageNum]);
			break;
		}
	}
	else {
		switch (status) {
		case MOVE_:
			brain1_img.Load(brain1_img_path_R[imageNum]);
			break;
		case ATTACK_:
			brain1_img.Load(brain1_attack_img_path_R[imageNum]);
			break;
		case DIE_:
			brain1_img.Load(brain1_die_img_path_R[imageNum]);
			break;
		}
	}
}

void Brain1::print(HDC& mDC) {
	if (!brain1_img.IsNull() ) {
		brain1_img.Draw(mDC, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0, 0, brain1_img.GetWidth(), brain1_img.GetHeight());
	}
}

void Brain1::move(StageManager& stageManager) {

	//중력
	RECT temprect = rect;
	gravity.UpdatePhysics(rect);

	if (CheckBlockCollision(rect, stageManager.blocks_stage1))
		rect = temprect;

	//이미지
	if (status != DIE_ || imageNum != 5)
		++imageNum;

	switch (status) {
	case MOVE_: {
		int offset = left ? -4 : 4;
		OffsetRect(&rect, offset, 0);

		if (imageNum == 8)
			imageNum = 0;

		if (CheckClientRect(stageManager.game_rect, rect))
			left = !left;
	}
			  break;
	case ATTACK_:
		if (imageNum == 7)
			imageNum = 0;
		break;
	case DIE_:
		if (imageNum == 5)
			brain1_img.Destroy();
		break;
	}

	if (status != DIE_ || imageNum != 5)
		insert();
}

void Brain1::attack() {

}

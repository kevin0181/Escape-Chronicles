#include "Brain2.h"
using namespace std;

//srand(time(nullptr));

Brain2::Brain2() : Monster() {
	hp = 0; // 나중에 확정되면 바꾸기
	imageNum = 0;
	rect = { 300, 300, 450, 450 };
	left = false;
	status = MOVE_;
}

RECT Brain2::getRect() const {
	return rect;
}

void Brain2::insert() {
	if (!brain2_img.IsNull()) {
		brain2_img.Destroy();
	}

	if (left) {
		switch (status) {
		case MOVE_:
			brain2_img.Load(brain2_img_path_L[imageNum]);
			break;
		case ATTACK_:
			brain2_img.Load(brain2_attack_img_path_L[imageNum]);
			break;
		case DIE_:
			brain2_img.Load(brain2_die_img_path_L[imageNum]);
			break;
		}
	}
	else {
		switch (status) {
		case MOVE_:
			brain2_img.Load(brain2_img_path_R[imageNum]);
			break;
		case ATTACK_:
			brain2_img.Load(brain2_attack_img_path_R[imageNum]);
			break;
		case DIE_:
			brain2_img.Load(brain2_die_img_path_R[imageNum]);
			break;
		}
	}
}

void Brain2::print(HDC& mDC) {
	if (!brain2_img.IsNull()) {
		brain2_img.Draw(mDC, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0, 0, brain2_img.GetWidth(), brain2_img.GetHeight());
	}
}

void Brain2::move(StageManager& stageManager) {

	//중력
	RECT temprect = rect;
	gravity.UpdatePhysics(rect);

	if (CheckBlockCollision(rect, stageManager.blocks_stage1))
		rect = temprect;

	//이미지
	if (status != DIE_ || imageNum != 10)
		++imageNum;

	switch (status) {
	case MOVE_: {
		int offset = left ? -4 : 4;
		OffsetRect(&rect, offset, 0);

		if (imageNum == 6)
			imageNum = 0;

		if (CheckClientRect(stageManager.game_rect, rect))
			left = !left;
	}
			  break;
	case ATTACK_:
		if (imageNum == 6)
			imageNum = 0;
		break;
	case DIE_:
		if (imageNum == 10)
			brain2_img.Destroy();
		break;
	}

	if (status != DIE_ || imageNum != 10)
		insert();
}

void Brain2::attack() {

}

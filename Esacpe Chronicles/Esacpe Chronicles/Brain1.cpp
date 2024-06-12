#include "Brain1.h"
using namespace std;


Brain1::Brain1() : Monster() {
	hp = 0; // 나중에 확정되면 바꾸기
	imageNum = 0;
	srand(static_cast<unsigned int>(time(NULL)));
	rect.left = 200 * (rand() % 7);
	rect = {rect.left, 500, rect.left+250, 750 };
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
			brain1_img.Load(brain1_img_path_L[imageNum/5]);
			break;
		case ATTACK_:
			brain1_img.Load(brain1_attack_img_path_L[imageNum/5]);
			break;
		case DIE_:
			brain1_img.Load(brain1_die_img_path_L[imageNum/5]);
			break;
		}
	}
	else {
		switch (status) {
		case MOVE_:
			brain1_img.Load(brain1_img_path_R[imageNum/5]);
			break;
		case ATTACK_:
			brain1_img.Load(brain1_attack_img_path_R[imageNum/5]);
			break;
		case DIE_:
			brain1_img.Load(brain1_die_img_path_R[imageNum/5]);
			break;
		}
	}
}

void Brain1::print(const HDC& mDC) {
	if (!brain1_img.IsNull() ) {
		brain1_img.Draw(mDC, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0, 0, brain1_img.GetWidth(), brain1_img.GetHeight());
	}
}

void Brain1::move(const StageManager& stageManager) {

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

		if (imageNum == 40)
			imageNum = 0;

		CheckClientRect(stageManager, rect, left);
	}
			  break;
	case ATTACK_:
		if (imageNum == 35)
			imageNum = 0;
		break;
	case DIE_:
		if (imageNum == 25)
			brain1_img.Destroy();
		break;
	}

	if (status != DIE_ || imageNum != 25)
		insert();
}

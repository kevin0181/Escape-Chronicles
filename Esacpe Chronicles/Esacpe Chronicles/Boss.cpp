#include "Boss.h"

using namespace std;

Boss::Boss() : Monster() {
	hp = 500; // 나중에 확정되면 바꾸기
	imageNum = 0;
	rect.left = 200 * (rand() % 7); //rand() % (stageManager.rect.right + 1);
	rect = { rect.left, 300, rect.left + 209, 501 };
	left = true;
	status = MOVE_;
}

RECT& Boss::getRect() {
	return rect;
}

void Boss::insert() {
	if (!boss_img.IsNull()) {
		boss_img.Destroy();
	}

	if (left) {
		switch (status) {
		case MOVE_:
			boss_img.Load(boss_img_path_L[imageNum/5]);
			break;
		case ATTACK_:
			boss_img.Load(boss_attack_img_path_L[imageNum/5]);
			break;
		case DIE_:
			boss_img.Load(boss_die_img_path_L[imageNum/5]);
			break;
		}
	}
	else {
		switch (status) {
		case MOVE_:
			boss_img.Load(boss_img_path_R[imageNum/5]);
			break;
		case ATTACK_:
			boss_img.Load(boss_attack_img_path_R[imageNum/5]);
			break;
		case DIE_:
			boss_img.Load(boss_die_img_path_R[imageNum/5]);
			break;
		}
	}
}

void Boss::print(const HDC& mDC) {
	if (!boss_img.IsNull()) {
		boss_img.Draw(mDC, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0, 0, boss_img.GetWidth(), boss_img.GetHeight());
	}
}

void Boss::move(const StageManager& stageManager) {
	//중력
	RECT temprect = rect;
	gravity.UpdatePhysics(rect);

	if (CheckBlockCollision(rect, stageManager.blocks_stage1))
		rect = temprect;

	//이미지
	if (status != DIE_ || imageNum != 30)
		++imageNum;

	if (imageNum == 30) {
		if (status == DIE_)
			boss_img.Destroy();
		else
			imageNum = 0;
	}

	if (status == MOVE_) {
		int offset = left ? -2 : 2;
		OffsetRect(&rect, offset, 0);

		CheckClientRect(stageManager, rect, left);
	}

	if (status != DIE_ || imageNum != 30)
		insert();
}

#include "Zombie3.h"
using namespace std;

//srand(time(nullptr));

Zombie3::Zombie3() : Monster() {
	hp = 0; // 나중에 확정되면 바꾸기
	imageNum = 0;
	srand(static_cast<unsigned int>(time(NULL)));
	rect.left = 200 * (rand() % 7);
	rect = { rect.left, 300, rect.left+300, 600 };
	left = false;
	status = MOVE_;
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

void Zombie3::print(const HDC& mDC) {
	if (!zombie3_img.IsNull()) {
		zombie3_img.Draw(mDC, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0, 0, zombie3_img.GetWidth(), zombie3_img.GetHeight());
	}
}

void Zombie3::move(const StageManager& stageManager) {

	//중력
	RECT temprect = rect;
	gravity.UpdatePhysics(rect);

	if (CheckBlockCollision(rect, stageManager))
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

		CheckClientRect(stageManager, rect, left);
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
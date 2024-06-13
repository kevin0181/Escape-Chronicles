#include "Zombie1.h"
using namespace std;

//srand(time(nullptr));

Zombie1::Zombie1() : Monster() {
	hp = 500; // 나중에 확정되면 바꾸기
	imageNum = 0;
	srand(static_cast<unsigned int>(time(NULL)));
	rect.left = 200 * (rand() % 7);
	rect = { rect.left, 300, rect.left+300, 600 };
	left = false;
	status = MOVE_;
}


void Zombie1::insert() {
	if (!zombie1_img.IsNull()) {
		zombie1_img.Destroy();
	}

	if (left) {
		switch (status) {
		case MOVE_:
			zombie1_img.Load(zombie1_img_path_L[imageNum/5]);
			break;
		case ATTACK_:
			zombie1_img.Load(zombie1_attack_img_path_L[imageNum/5]);
			break;
		case DIE_:
			zombie1_img.Load(zombie1_die_img_path_L[imageNum/5]);
			break;
		}
	}
	else {
		switch (status) {
		case MOVE_:
			zombie1_img.Load(zombie1_img_path_R[imageNum/5]);
			break;
		case ATTACK_:
			zombie1_img.Load(zombie1_attack_img_path_R[imageNum/5]);
			break;
		case DIE_:
			zombie1_img.Load(zombie1_die_img_path_R[imageNum/5]);
			break;
		}
	}
}

void Zombie1::print(const HDC& mDC) {
	if (!zombie1_img.IsNull()) {
		zombie1_img.Draw(mDC, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0, 0, zombie1_img.GetWidth(), zombie1_img.GetHeight());
	}
}

void Zombie1::move(const StageManager& stageManager) {

	//중력
	RECT temprect = rect;
	gravity.UpdatePhysics(rect);

	if (CheckBlockCollision(rect, stageManager))
		rect = temprect;

	//이미지
	if (status != DIE_ || imageNum != 20)
		++imageNum;

	switch (status) {
	case MOVE_:{
		int offset = left ? -4 : 4;
		OffsetRect(&rect, offset, 0);

		if (imageNum == 40)
			imageNum = 0;

		CheckClientRect(stageManager, rect, left);
	}
		break;
	case ATTACK_:
		if (imageNum == 25)
			imageNum = 0;
		break;
	case DIE_:
		if (imageNum == 20)
			zombie1_img.Destroy();
		break;
	}

	if (status != DIE_ || imageNum != 20)
		insert();
}

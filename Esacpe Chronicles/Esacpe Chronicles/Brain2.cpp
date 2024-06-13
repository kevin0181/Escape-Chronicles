#include "Brain2.h"
using namespace std;


Brain2::Brain2() : Monster() {
	hp = 0; // ���߿� Ȯ���Ǹ� �ٲٱ�
	imageNum = 0;
	srand(static_cast<unsigned int>(time(NULL)));
	rect.left = 200 * (rand() % 7);
	rect = { rect.left, 300, rect.left+150, 450 };
	left = false;
	status = MOVE_;
}


void Brain2::insert() {
	if (!brain2_img.IsNull()) {
		brain2_img.Destroy();
	}

	if (left) {
		switch (status) {
		case MOVE_:
			brain2_img.Load(brain2_img_path_L[imageNum/3]);
			break;
		case ATTACK_:
			brain2_img.Load(brain2_attack_img_path_L[imageNum/3]);
			break;
		case DIE_:
			brain2_img.Load(brain2_die_img_path_L[imageNum/3]);
			break;
		}
	}
	else {
		switch (status) {
		case MOVE_:
			brain2_img.Load(brain2_img_path_R[imageNum/3]);
			break;
		case ATTACK_:
			brain2_img.Load(brain2_attack_img_path_R[imageNum/3]);
			break;
		case DIE_:
			brain2_img.Load(brain2_die_img_path_R[imageNum/3]);
			break;
		}
	}
}

void Brain2::print(const HDC& mDC) {
	if (!brain2_img.IsNull()) {
		brain2_img.Draw(mDC, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0, 0, brain2_img.GetWidth(), brain2_img.GetHeight());
	}
}

void Brain2::move(const StageManager& stageManager) {

	//�߷�
	RECT temprect = rect;
	gravity.UpdatePhysics(rect);

	if (CheckBlockCollision(rect, stageManager))
		rect = temprect;

	//�̹���
	if (status != DIE_ || imageNum != 30)
		++imageNum;

	switch (status) {
	case MOVE_: {
		int offset = left ? -4 : 4;
		OffsetRect(&rect, offset, 0);

		if (imageNum == 18)
			imageNum = 0;

		CheckClientRect(stageManager, rect, left);
	}
			  break;
	case ATTACK_:
		if (imageNum == 18)
			imageNum = 0;
		break;
	case DIE_:
		if (imageNum == 30)
			brain2_img.Destroy();
		break;
	}

	if (status != DIE_ || imageNum != 30)
		insert();
}

void Brain2::MonsterPlayerCollision(Player& p) {
	RECT intersectRect;
	if (IntersectRect(&intersectRect, &p.getRECT(), &rect)) {
		Collisionplayer(p);
		//player�� �浹���� �� ��ó? ����? �Լ��� �θ���
	}
	else {

		status = MOVE_;
	}
}

void Brain2::Collisionplayer(const Player& p) { //�÷��̾�� �浹������ ������ ��ó
	switch (p.status) {
	case ATTACK:
		if (p.direction == PlayerStatus::RIGHT)
			OffsetRect(&rect, +20, -20);
		else
			OffsetRect(&rect, -20, -20);

		hp -= 10;
		break;
	default:
		status = ATTACK_;
		break;
	}
}
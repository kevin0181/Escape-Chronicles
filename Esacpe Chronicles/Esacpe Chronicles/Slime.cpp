#include "Slime.h"

using namespace std;



Slime::Slime() : Monster() {
	hp = 500; // ���߿� Ȯ���Ǹ� �ٲٱ�
	imageNum = 0;
	rect.left = 200 * (rand() % 7); //rand() % (stageManager.rect.right + 1);
	rect = { rect.left, 300, rect.left + 200, 420 };
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
			slime_img.Load(slime_img_path_L[imageNum / 3]);
			break;
		case ATTACK_:
			slime_img.Load(slime_attack_img_path_L[imageNum / 3]);
			break;
		case DIE_:
			slime_img.Load(slime_die_img_path_L[imageNum / 3]);
			break;
		}
	}
	else {
		switch (status) {
		case MOVE_:
			slime_img.Load(slime_img_path_R[imageNum / 3]);
			break;
		case ATTACK_:
			slime_img.Load(slime_attack_img_path_R[imageNum / 3]);
			break;
		case DIE_:
			slime_img.Load(slime_die_img_path_R[imageNum / 3]);
			break;
		}
	}
}

void Slime::print(const HDC& mDC) {
	if (!slime_img.IsNull()) {
		slime_img.Draw(mDC, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0, 0, slime_img.GetWidth(), slime_img.GetHeight());
	}
}

void Slime::move(const StageManager& stageManager) {
	//�߷�
	RECT temprect = rect;
	gravity.UpdatePhysics(rect);

	if (CheckBlockCollision(rect, stageManager))
		rect = temprect;

	//�̹���
	if (status != DIE_ || imageNum != 27)
		++imageNum;

	if (imageNum == 27) {
		if (status == DIE_)
			slime_img.Destroy();
		else
			imageNum = 0;
	}

	if (status == MOVE_) {
		int offset = left ? -2 : 2;
		OffsetRect(&rect, offset, 0);

		CheckClientRect(stageManager, rect, left);
	}

	if (status != DIE_ || imageNum != 27)
		insert();
}

void Slime::MonsterPlayerCollision(Player& p) {
	RECT intersectRect;
	if (IntersectRect(&intersectRect, &p.getRECT(), &rect)) {
		Collisionplayer(p);
		//player�� �浹���� �� ���~~�����ּ���!!!~~
	}
	else {

		status = MOVE_;
	}
}

void Slime::Collisionplayer(const Player& p) { //�÷��̾�� �浹������ ������ ��ó
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
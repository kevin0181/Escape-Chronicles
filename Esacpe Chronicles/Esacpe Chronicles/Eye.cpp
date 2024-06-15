#include "Eye.h"

using namespace std;



Eye::Eye() : Monster() {
	hp = 40; // ���߿� Ȯ���Ǹ� �ٲٱ�
	imageNum = 0;
	rect.left = 1500 + 200 * (rand() % 14); //rand() % (stageManager.rect.right + 1);
	rect = { rect.left, 300, rect.left + 150, 460 };
	left = true;
	status = MOVE_;
}

RECT& Eye::getRect() {
	return rect;
}

MonsterStatus Eye::getStatus() const {
	return status;
}

void Eye::insert() {
	if (!eye_img.IsNull()) {
		eye_img.Destroy();
	}

	if (left) {
		switch (status) {
		case MOVE_:
			eye_img.Load(eye_img_path_L[imageNum / 3]);
			break;
		case ATTACK_:
			eye_img.Load(eye_attack_img_path_L[imageNum / 3]);
			break;
		case DIE_:
			eye_img.Load(eye_die_img_path_L[imageNum / 3]);
			break;
		}
	}
	else {
		switch (status) {
		case MOVE_:
			eye_img.Load(eye_img_path_R[imageNum / 3]);
			break;
		case ATTACK_:
			eye_img.Load(eye_attack_img_path_R[imageNum / 3]);
			break;
		case DIE_:
			eye_img.Load(eye_die_img_path_R[imageNum / 3]);
			break;
		}
	}
}

void Eye::print(const HDC& mDC) {
	if (!eye_img.IsNull()) {
		if (attacked) {
			attacked_img.Draw(mDC, rect.left, rect.top - 56, 84, 56, 0, 0, attacked_img.GetWidth(), attacked_img.GetHeight());
			printAttack(mDC, rect);
		}
		eye_img.Draw(mDC, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0, 0, eye_img.GetWidth(), eye_img.GetHeight());
	}
}

void Eye::move(const StageManager& stageManager) {
	//�߷�
	RECT temprect = rect;
	gravity.UpdatePhysics(rect);

	if (CheckBlockCollision(rect, stageManager))
		rect = temprect;

	if (checkBlock(stageManager)) {
		rect = temprect;
	}

	//�̹���
	if (status != DIE_ || imageNum != 30)
		++imageNum;

	if (imageNum == 30) {
		if (status == DIE_)
			eye_img.Destroy();
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

bool Eye::checkBlock(const StageManager& stageManager) {
	RECT r;
	for (auto& block : stageManager.blocks_stage1) {
		if (IntersectRect(&r, &block.rect, &rect)) {
			if (rect.bottom <= block.rect.top + 20) {
				return true;
			}
		}
	}
	return false;
}

void Eye::MonsterPlayerCollision(Player& p) {
	if (status != MonsterStatus::DIE_) {
		RECT intersectRect = {};
		if (IntersectRect(&intersectRect, &p.getRECT(), &rect)) {
			Collisionplayer(p);
			//player�� �浹���� �� ���~~�����ּ���!!!~~
			p.collisionMonster(this);
		}
		else {
			status = MOVE_;
			attacked = false;
		}

		intersectRect = {};
		for (auto it = p.bullets.begin(); it != p.bullets.end(); ) {
			if (IntersectRect(&intersectRect, &it->rect, &rect)) {
				attacked = true;
				if (p.direction == PlayerStatus::RIGHT)
					OffsetRect(&rect, +20, -20);
				else
					OffsetRect(&rect, -20, -20);
				it = p.bullets.erase(it); // �ش� �Ѿ�, ȭ�� ����

				hp -= p.power;
				attacksize = p.power;
				if (hp <= 0) {
					status = DIE_;
					imageNum = 0;
				}
			}
			else {
				++it;
			}
		}
	}
}

void Eye::Collisionplayer(const Player& p) { //�÷��̾�� �浹������ ������ ��ó
	switch (p.status) {
	case ATTACK:
		attacked = true;
		if (p.direction == PlayerStatus::RIGHT)
			OffsetRect(&rect, +20, -20);
		else
			OffsetRect(&rect, -20, -20);

		hp -= p.power;
		attacksize = p.power;
		if (hp <= 0) {
			status = DIE_;
			imageNum = 0;
		}
		break;
	default:
		status = ATTACK_;
		attacked = false;
		break;
	}
}
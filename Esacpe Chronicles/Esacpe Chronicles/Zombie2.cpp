#include "Zombie2.h"

using namespace std;


Zombie2::Zombie2() : Monster() {
	hp = 40; // ���߿� Ȯ���Ǹ� �ٲٱ�
	imageNum = 0;
	srand(static_cast<unsigned int>(time(NULL)));
	rect.left = 1500 + 200 * (rand() % 14);
	rect = { rect.left, 300, rect.left+300, 600 };
	left = false;
	status = MOVE_;
}

MonsterStatus Zombie2::getStatus() const {
	return status;
}

void Zombie2::insert() {
	if (!zombie2_img.IsNull()) {
		zombie2_img.Destroy();
	}

	if (left) {
		switch (status) {
		case MOVE_:
			zombie2_img.Load(zombie2_img_path_L[imageNum/5]);
			break;
		case ATTACK_:
			zombie2_img.Load(zombie2_attack_img_path_L[imageNum/5]);
			break;
		case DIE_:
			zombie2_img.Load(zombie2_die_img_path_L[imageNum/5]);
			break;
		}
	}
	else {
		switch (status) {
		case MOVE_:
			zombie2_img.Load(zombie2_img_path_R[imageNum/5]);
			break;
		case ATTACK_:
			zombie2_img.Load(zombie2_attack_img_path_R[imageNum/5]);
			break;
		case DIE_:
			zombie2_img.Load(zombie2_die_img_path_R[imageNum/5]);
			break;
		}
	}
}

void Zombie2::print(const HDC& mDC) {
	if (!zombie2_img.IsNull() ) {
		if (attacked) {
			attacked_img.Draw(mDC, rect.left, rect.top - 56, 84, 56, 0, 0, attacked_img.GetWidth(), attacked_img.GetHeight());
			printAttack(mDC, rect);
		}
		zombie2_img.Draw(mDC, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0, 0, zombie2_img.GetWidth(), zombie2_img.GetHeight());
	}
}

void Zombie2::move(const StageManager& stageManager) {
	//�߷�
	RECT temprect = rect;
	gravity.UpdatePhysics(rect);

	if (CheckBlockCollision(rect, stageManager))
		rect = temprect;

	if (checkBlock(stageManager)) {
		rect = temprect;
	}

	//�̹���
	if (status != DIE_ || imageNum != 25)
		++imageNum;

	switch (status) {
	case MOVE_: {
		int offset = left ? -4 : 4;
		OffsetRect(&rect, offset, 0);

		if (imageNum == 35)
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
			zombie2_img.Destroy();
		break;
	}

	if (status != DIE_ || imageNum != 25)
		insert();
}

bool Zombie2::checkBlock(const StageManager& stageManager) {
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

void Zombie2::MonsterPlayerCollision(Player& p) {
	RECT intersectRect;
	if (IntersectRect(&intersectRect, &p.getRECT(), &rect)) {
		Collisionplayer(p);
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

void Zombie2::Collisionplayer(const Player& p) { //�÷��̾�� �浹������ ������ ��ó
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
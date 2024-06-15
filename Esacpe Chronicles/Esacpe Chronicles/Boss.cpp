#include "Boss.h"

using namespace std;

Boss::Boss() : Monster() {
	hp = 100; // 나중에 확정되면 바꾸기
	imageNum = 0;
	rect = { 3000, 300, 3209, 501 };
	left = false;
	status = MOVE_;
}

MonsterStatus Boss::getStatus() const {
	return status;
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
		if (attacked) {
			attacked_img.Draw(mDC, rect.left, rect.top - 56, 84, 56, 0, 0, attacked_img.GetWidth(), attacked_img.GetHeight());
			printAttack(mDC, rect);
		}
		boss_img.Draw(mDC, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0, 0, boss_img.GetWidth(), boss_img.GetHeight());
	}
}

void Boss::move(const StageManager& stageManager) {
	//중력
	RECT temprect = rect;
	gravity.UpdatePhysics(rect);

	if (CheckBlockCollision(rect, stageManager))
		rect = temprect;

	if (checkBlock(stageManager)) {
		rect = temprect;
	}

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

bool Boss::checkBlock(const StageManager& stageManager) {
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

void Boss::MonsterPlayerCollision(Player& p) {
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
			it = p.bullets.erase(it); // 해당 총알, 화살 제거

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

void Boss::Collisionplayer(const Player& p) { //플레이어랑 충돌했을때 몬스터의 대처
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
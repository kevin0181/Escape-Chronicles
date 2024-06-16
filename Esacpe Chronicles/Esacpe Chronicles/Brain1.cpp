#include "Brain1.h"
using namespace std;


Brain1::Brain1() : Monster() {
	hp = 100; // 나중에 확정되면 바꾸기
	imageNum = 0;
	rect.left = 200 * (rand() % 23);
	rect = {rect.left, 200, rect.left+250, 450 };
	if (rect.left < 3000)
		left = true;
	else
		left = false;
	status = MOVE_;
}

MonsterStatus Brain1::getStatus() const {
	return status;
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
		if (attacked) {
			attacked_img.Draw(mDC, rect.left, rect.top - 56, 84, 56, 0, 0, attacked_img.GetWidth(), attacked_img.GetHeight());
			printAttack(mDC, rect);
		}
		brain1_img.Draw(mDC, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0, 0, brain1_img.GetWidth(), brain1_img.GetHeight());
	}
}

void Brain1::move(const StageManager& stageManager) {

	//중력
	RECT temprect = rect;
	gravity.UpdatePhysics(rect);

	if (CheckBlockCollision(rect, stageManager))
		rect = temprect;

	if (checkBlock(stageManager)) {
		rect = temprect;
	}

	//이미지
	if (status != DIE_ || imageNum != 25)
		++imageNum;

	switch (status) {
	case MOVE_: {
		int offset = left ? -2 : 2;
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

bool Brain1::checkBlock(const StageManager& stageManager) {
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

void Brain1::MonsterPlayerCollision(Player& p) {
	if (status != MonsterStatus::DIE_) {
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
					OffsetRect(&rect, +30, -30);
				else
					OffsetRect(&rect, -30, -30);
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
}

void Brain1::Collisionplayer(const Player& p) { //플레이어랑 충돌했을때 몬스터의 대처
	switch (p.status) {
	case ATTACK:
		attacked = true;
		if (p.direction == PlayerStatus::RIGHT)
			OffsetRect(&rect, +30, -30);
		else
			OffsetRect(&rect, -30, -30);

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
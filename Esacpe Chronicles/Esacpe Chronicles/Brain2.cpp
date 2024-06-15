#include "Brain2.h"
using namespace std;


Brain2::Brain2() : Monster() {
	hp = 50; // 나중에 확정되면 바꾸기
	imageNum = 0;
	rect.left = 1500 + 200 * (rand() % 14);
	rect = { rect.left, 300, rect.left+150, 450 };
	left = true;
	status = MOVE_;
}

MonsterStatus Brain2::getStatus() const {
	return status;
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
		if (attacked) {
			attacked_img.Draw(mDC, rect.left, rect.top - 56, 84, 56, 0, 0, attacked_img.GetWidth(), attacked_img.GetHeight());
			printAttack(mDC, rect);
		}
		brain2_img.Draw(mDC, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0, 0, brain2_img.GetWidth(), brain2_img.GetHeight());
	}
}

void Brain2::move(const StageManager& stageManager) {

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

bool Brain2::checkBlock(const StageManager& stageManager) {
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

void Brain2::MonsterPlayerCollision(Player& p) {
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
}

void Brain2::Collisionplayer(const Player& p) { //플레이어랑 충돌했을때 몬스터의 대처
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
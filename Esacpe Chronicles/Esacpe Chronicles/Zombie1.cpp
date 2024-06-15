#include "Zombie1.h"
using namespace std;


Zombie1::Zombie1() : Monster() {
	hp = 40; // 나중에 확정되면 바꾸기
	imageNum = 0;
	srand(static_cast<unsigned int>(time(NULL)));
	rect.left = 200 * (rand() %14);
	rect = { rect.left, 300, rect.left+300, 600 };
	left = false;
	status = MOVE_;
}

MonsterStatus Zombie1::getStatus() const {
	return status;
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
		if (attacked) {
			attacked_img.Draw(mDC, rect.left, rect.top - 56, 84, 56, 0, 0, attacked_img.GetWidth(), attacked_img.GetHeight());
			printAttack(mDC, rect);
		}
		zombie1_img.Draw(mDC, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0, 0, zombie1_img.GetWidth(), zombie1_img.GetHeight());
	}
}

void Zombie1::move(const StageManager& stageManager) {

	//중력
	RECT temprect = rect;
	gravity.UpdatePhysics(rect);

	if (CheckBlockCollision(rect, stageManager))
		rect = temprect;

	if (checkBlock(stageManager)) {
		rect = temprect;
	}

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

bool Zombie1::checkBlock(const StageManager& stageManager) {
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

void Zombie1::MonsterPlayerCollision(Player& p) {
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

void Zombie1::Collisionplayer(const Player& p) { //플레이어랑 충돌했을때 몬스터의 대처
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
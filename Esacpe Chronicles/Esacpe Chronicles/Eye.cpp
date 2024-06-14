#include "Eye.h"

using namespace std;



Eye::Eye() : Monster() {
	hp = 50; // 나중에 확정되면 바꾸기
	imageNum = 0;
	rect.left = 200 * (rand() % 7); //rand() % (stageManager.rect.right + 1);
	rect = { rect.left, 300, rect.left + 100, 420 };
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
		eye_img.Draw(mDC, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0, 0, eye_img.GetWidth(), eye_img.GetHeight());
	}
}

void Eye::move(const StageManager& stageManager) {
	//중력
	RECT temprect = rect;
	gravity.UpdatePhysics(rect);

	if (CheckBlockCollision(rect, stageManager))
		rect = temprect;

	//이미지
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

void Eye::MonsterPlayerCollision(Player& p) {
	RECT intersectRect;
	if (status != MonsterStatus::DIE_) {
		if (IntersectRect(&intersectRect, &p.getRECT(), &rect)) {
			Collisionplayer(p);
			//player의 충돌했을 때 모션~~적어주세요!!!~~
			p.collisionMonster(this);
		}
		else {
			status = MOVE_;
		}
	}
}

void Eye::Collisionplayer(const Player& p) { //플레이어랑 충돌했을때 몬스터의 대처
	switch (p.status) {
	case ATTACK:
		if (p.direction == PlayerStatus::RIGHT)
			OffsetRect(&rect, +20, -20);
		else
			OffsetRect(&rect, -20, -20);

		hp -= p.power;
		break;
	default:
		status = ATTACK_;
		break;
	}
}
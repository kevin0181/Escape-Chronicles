#include "Zombie2.h"

using namespace std;

//srand(time(nullptr));

Zombie2::Zombie2() : Monster() {
	hp = 500; // 나중에 확정되면 바꾸기
	imageNum = 0;
	srand(static_cast<unsigned int>(time(NULL)));
	rect.left = 200 * (rand() % 7);
	rect = { rect.left, 300, rect.left+300, 600 };
	left = false;
	status = MOVE_;
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
		zombie2_img.Draw(mDC, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0, 0, zombie2_img.GetWidth(), zombie2_img.GetHeight());
	}
}

void Zombie2::move(const StageManager& stageManager) {
	//중력
	RECT temprect = rect;
	gravity.UpdatePhysics(rect);

	if (CheckBlockCollision(rect, stageManager))
		rect = temprect;

	//이미지
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

void Zombie2::MonsterPlayerCollision(Player& p) {
	RECT intersectRect;
	if (IntersectRect(&intersectRect, &p.getRECT(), &rect)) {
		Collisionplayer(p);
		//player의 충돌했을 때 대처? 반응? 함수를 부르기
	}
	else {

		status = MOVE_;
	}
}

void Zombie2::Collisionplayer(const Player& p) { //플레이어랑 충돌했을때 몬스터의 대처
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
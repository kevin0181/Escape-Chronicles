#pragma once
#include "Monster.h"

class Eye : public Monster {
	int hp;
	CImage eye_img;
	int imageNum;
	RECT rect;
	bool left; // 슬라임의 이동 방향
	MonsterStatus status;
	Gravity gravity;

	LPCTSTR eye_img_path_L[10] = { // 그냥 움직임 L
		L"img/monster/eye_L/eye_walk_1.png",
		L"img/monster/eye_L/eye_walk_2.png",
		L"img/monster/eye_L/eye_walk_3.png",
		L"img/monster/eye_L/eye_walk_4.png",
		L"img/monster/eye_L/eye_walk_5.png",
		L"img/monster/eye_L/eye_walk_6.png",
		L"img/monster/eye_L/eye_walk_7.png",
		L"img/monster/eye_L/eye_walk_8.png",
		L"img/monster/eye_L/eye_walk_9.png",
		L"img/monster/eye_L/eye_walk_10.png"
	};

	LPCTSTR eye_attack_img_path_L[10] = { // 공격 시 움직임 L
		L"img/monster/eye_L/eye_attack_1.png",
		L"img/monster/eye_L/eye_attack_2.png",
		L"img/monster/eye_L/eye_attack_3.png",
		L"img/monster/eye_L/eye_attack_4.png",
		L"img/monster/eye_L/eye_attack_5.png",
		L"img/monster/eye_L/eye_attack_6.png",
		L"img/monster/eye_L/eye_attack_7.png",
		L"img/monster/eye_L/eye_attack_8.png",
		L"img/monster/eye_L/eye_attack_9.png",
		L"img/monster/eye_L/eye_attack_10.png"
	};

	LPCTSTR eye_die_img_path_L[10] = { // L
		L"img/monster/eye_L/eye_die_1.png",
		L"img/monster/eye_L/eye_die_2.png",
		L"img/monster/eye_L/eye_die_3.png",
		L"img/monster/eye_L/eye_die_4.png",
		L"img/monster/eye_L/eye_die_5.png",
		L"img/monster/eye_L/eye_die_6.png",
		L"img/monster/eye_L/eye_die_7.png",
		L"img/monster/eye_L/eye_die_8.png",
		L"img/monster/eye_L/eye_die_9.png",
		L"img/monster/eye_L/eye_die_10.png"
	};

	LPCTSTR eye_img_path_R[10] = { // 그냥 움직임 R
		L"img/monster/eye_R/eye_walk_1.png",
		L"img/monster/eye_R/eye_walk_2.png",
		L"img/monster/eye_R/eye_walk_3.png",
		L"img/monster/eye_R/eye_walk_4.png",
		L"img/monster/eye_R/eye_walk_5.png",
		L"img/monster/eye_R/eye_walk_6.png",
		L"img/monster/eye_R/eye_walk_7.png",
		L"img/monster/eye_R/eye_walk_8.png",
		L"img/monster/eye_R/eye_walk_9.png",
		L"img/monster/eye_R/eye_walk_10.png"
	};

	LPCTSTR eye_attack_img_path_R[10] = { 
		L"img/monster/eye_R/eye_attack_1.png",
		L"img/monster/eye_R/eye_attack_2.png",
		L"img/monster/eye_R/eye_attack_3.png",
		L"img/monster/eye_R/eye_attack_4.png",
		L"img/monster/eye_R/eye_attack_5.png",
		L"img/monster/eye_R/eye_attack_6.png",
		L"img/monster/eye_R/eye_attack_7.png",
		L"img/monster/eye_R/eye_attack_8.png",
		L"img/monster/eye_R/eye_attack_9.png",
		L"img/monster/eye_R/eye_attack_10.png"
	};

	LPCTSTR eye_die_img_path_R[10] = { 
		L"img/monster/eye_R/eye_die_1.png",
		L"img/monster/eye_R/eye_die_2.png",
		L"img/monster/eye_R/eye_die_3.png",
		L"img/monster/eye_R/eye_die_4.png",
		L"img/monster/eye_R/eye_die_5.png",
		L"img/monster/eye_R/eye_die_6.png",
		L"img/monster/eye_R/eye_die_7.png",
		L"img/monster/eye_R/eye_die_8.png",
		L"img/monster/eye_R/eye_die_9.png",
		L"img/monster/eye_R/eye_die_10.png"
	};

public:
	Eye();

	void insert() override; // 움직일 때(사진 바꿀 때)도 쓴다
	void print(const HDC& mDC) override;
	void move(const StageManager& stageManager) override; // rect를 움직이고 insert를 호출해 사진도 바꿔줌

	MonsterStatus getStatus() const override;
	RECT& getRect() override;
	void MonsterPlayerCollision(Player& p) override; //플레이어랑 충돌했을 때 함수
	void Collisionplayer(const Player& p) override; //플레이어랑 충돌했을때 몬스터의 대처
	bool checkBlock(const StageManager& stageManager);
};



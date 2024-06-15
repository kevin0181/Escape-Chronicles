#pragma once
#include "Monster.h"

class Zombie3 : public Monster {
	int hp;
	CImage zombie3_img;
	int imageNum;
	RECT rect;
	bool left; // 좀비의 이동 방향
	MonsterStatus status;
	Gravity gravity;

	LPCTSTR zombie3_img_path_L[10] = { // wildzombie
		L"img/monster/wildzombie_L/wildzombie_walk_1.png",
		L"img/monster/wildzombie_L/wildzombie_walk_2.png",
		L"img/monster/wildzombie_L/wildzombie_walk_3.png",
		L"img/monster/wildzombie_L/wildzombie_walk_4.png",
		L"img/monster/wildzombie_L/wildzombie_walk_5.png",
		L"img/monster/wildzombie_L/wildzombie_walk_6.png",
		L"img/monster/wildzombie_L/wildzombie_walk_7.png",
		L"img/monster/wildzombie_L/wildzombie_walk_8.png",
		L"img/monster/wildzombie_L/wildzombie_walk_9.png",
		L"img/monster/wildzombie_L/wildzombie_walk_10.png"

	};

	LPCTSTR zombie3_attack_img_path_L[4] = {
		L"img/monster/wildzombie_L/wildzombie_attack_1.png",
		L"img/monster/wildzombie_L/wildzombie_attack_2.png",
		L"img/monster/wildzombie_L/wildzombie_attack_3.png",
		L"img/monster/wildzombie_L/wildzombie_attack_4.png",
	};

	LPCTSTR zombie3_die_img_path_L[5] = {
		L"img/monster/wildzombie_L/wildzombie_die_1.png",
		L"img/monster/wildzombie_L/wildzombie_die_2.png",
		L"img/monster/wildzombie_L/wildzombie_die_3.png",
		L"img/monster/wildzombie_L/wildzombie_die_4.png",
		L"img/monster/wildzombie_L/wildzombie_die_5.png"
	};

	LPCTSTR zombie3_img_path_R[10] = { // wildzombie
		L"img/monster/wildzombie_R/wildzombie_walk_1.png",
		L"img/monster/wildzombie_R/wildzombie_walk_2.png",
		L"img/monster/wildzombie_R/wildzombie_walk_3.png",
		L"img/monster/wildzombie_R/wildzombie_walk_4.png",
		L"img/monster/wildzombie_R/wildzombie_walk_5.png",
		L"img/monster/wildzombie_R/wildzombie_walk_6.png",
		L"img/monster/wildzombie_R/wildzombie_walk_7.png",
		L"img/monster/wildzombie_R/wildzombie_walk_8.png",
		L"img/monster/wildzombie_R/wildzombie_walk_9.png",
		L"img/monster/wildzombie_R/wildzombie_walk_10.png"

	};

	LPCTSTR zombie3_attack_img_path_R[4] = {
		L"img/monster/wildzombie_R/wildzombie_attack_1.png",
		L"img/monster/wildzombie_R/wildzombie_attack_2.png",
		L"img/monster/wildzombie_R/wildzombie_attack_3.png",
		L"img/monster/wildzombie_R/wildzombie_attack_4.png",
	};

	LPCTSTR zombie3_die_img_path_R[5] = {
		L"img/monster/wildzombie_R/wildzombie_die_1.png",
		L"img/monster/wildzombie_R/wildzombie_die_2.png",
		L"img/monster/wildzombie_R/wildzombie_die_3.png",
		L"img/monster/wildzombie_R/wildzombie_die_4.png",
		L"img/monster/wildzombie_R/wildzombie_die_5.png"
	};

public:
	Zombie3();


	void insert() override; // 움직일 때(사진 바꿀 때)도 쓴다
	void print(const HDC& mDC) override;
	void move(const StageManager& stageManager) override; // rect를 움직이고 insert를 호출해 사진도 바꿔줌
	
	MonsterStatus getStatus() const override;
	RECT& getRect() override {
		return rect;
	}
	void MonsterPlayerCollision(Player& p) override; //플레이어랑 충돌했을 때 함수
	void Collisionplayer(const Player& p) override; //플레이어랑 충돌했을때 몬스터의 대처
	bool checkBlock(const StageManager& stageManager); // slime & block
};



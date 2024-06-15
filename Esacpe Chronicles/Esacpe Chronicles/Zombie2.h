#pragma once
#include "Monster.h"

class Zombie2 : public Monster {
	int hp;
	CImage zombie2_img;
	int imageNum;
	RECT rect;
	bool left; // 좀비의 이동 방향
	MonsterStatus status;
	Gravity gravity;

	LPCTSTR zombie2_img_path_L[7] = { // zombiewoman
		L"img/monster/zombiewoman_L/zombiewoman_walk_1.png",
		L"img/monster/zombiewoman_L/zombiewoman_walk_2.png",
		L"img/monster/zombiewoman_L/zombiewoman_walk_3.png",
		L"img/monster/zombiewoman_L/zombiewoman_walk_4.png",
		L"img/monster/zombiewoman_L/zombiewoman_walk_5.png",
		L"img/monster/zombiewoman_L/zombiewoman_walk_6.png",
		L"img/monster/zombiewoman_L/zombiewoman_walk_7.png"
	};

	LPCTSTR zombie2_attack_img_path_L[4] = {
		L"img/monster/zombiewoman_L/zombiewoman_attack_1.png",
		L"img/monster/zombiewoman_L/zombiewoman_attack_2.png",
		L"img/monster/zombiewoman_L/zombiewoman_attack_3.png",
		L"img/monster/zombiewoman_L/zombiewoman_attack_4.png"
	};

	LPCTSTR zombie2_die_img_path_L[5] = {
		L"img/monster/zombiewoman_L/zombiewoman_die_1.png",
		L"img/monster/zombiewoman_L/zombiewoman_die_2.png",
		L"img/monster/zombiewoman_L/zombiewoman_die_3.png",
		L"img/monster/zombiewoman_L/zombiewoman_die_4.png",
		L"img/monster/zombiewoman_L/zombiewoman_die_5.png"
	};

	LPCTSTR zombie2_img_path_R[7] = { // zombiewoman
		L"img/monster/zombiewoman_R/zombiewoman_walk_1.png",
		L"img/monster/zombiewoman_R/zombiewoman_walk_2.png",
		L"img/monster/zombiewoman_R/zombiewoman_walk_3.png",
		L"img/monster/zombiewoman_R/zombiewoman_walk_4.png",
		L"img/monster/zombiewoman_R/zombiewoman_walk_5.png",
		L"img/monster/zombiewoman_R/zombiewoman_walk_6.png",
		L"img/monster/zombiewoman_R/zombiewoman_walk_7.png"
	};

	LPCTSTR zombie2_attack_img_path_R[4] = {
		L"img/monster/zombiewoman_R/zombiewoman_attack_1.png",
		L"img/monster/zombiewoman_R/zombiewoman_attack_2.png",
		L"img/monster/zombiewoman_R/zombiewoman_attack_3.png",
		L"img/monster/zombiewoman_R/zombiewoman_attack_4.png"
	};

	LPCTSTR zombie2_die_img_path_R[5] = {
		L"img/monster/zombiewoman_R/zombiewoman_die_1.png",
		L"img/monster/zombiewoman_R/zombiewoman_die_2.png",
		L"img/monster/zombiewoman_R/zombiewoman_die_3.png",
		L"img/monster/zombiewoman_R/zombiewoman_die_4.png",
		L"img/monster/zombiewoman_R/zombiewoman_die_5.png"
	};

public:
	Zombie2();

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



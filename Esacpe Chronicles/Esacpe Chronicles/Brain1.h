#pragma once
#include "Monster.h"

class Brain1 : public Monster {
	int hp;
	CImage brain1_img;
	int imageNum;
	RECT rect;
	bool left;
	MonsterStatus status;
	Gravity gravity;

	LPCTSTR brain1_img_path_L[8] = {
		L"img/monster/brain1_L/brain1_move_1_L.png",
		L"img/monster/brain1_L/brain1_move_2_L.png",
		L"img/monster/brain1_L/brain1_move_3_L.png",
		L"img/monster/brain1_L/brain1_move_4_L.png",
		L"img/monster/brain1_L/brain1_move_5_L.png",
		L"img/monster/brain1_L/brain1_move_6_L.png",
		L"img/monster/brain1_L/brain1_move_7_L.png",
		L"img/monster/brain1_L/brain1_move_8_L.png"
	};

	LPCTSTR brain1_attack_img_path_L[7] = {
		L"img/monster/brain1_L/brain1_attack_1_L.png",
		L"img/monster/brain1_L/brain1_attack_2_L.png",
		L"img/monster/brain1_L/brain1_attack_3_L.png",
		L"img/monster/brain1_L/brain1_attack_4_L.png",
		L"img/monster/brain1_L/brain1_attack_5_L.png",
		L"img/monster/brain1_L/brain1_attack_6_L.png",
		L"img/monster/brain1_L/brain1_attack_7_L.png"
	};

	LPCTSTR brain1_die_img_path_L[5] = {
		L"img/monster/brain1_L/brain1_die_1_L.png",
		L"img/monster/brain1_L/brain1_die_2_L.png",
		L"img/monster/brain1_L/brain1_die_3_L.png",
		L"img/monster/brain1_L/brain1_die_4_L.png",
		L"img/monster/brain1_L/brain1_die_5_L.png"
	};

	LPCTSTR brain1_img_path_R[8] = {
		L"img/monster/brain1_R/brain1_move_1_R.png",
		L"img/monster/brain1_R/brain1_move_2_R.png",
		L"img/monster/brain1_R/brain1_move_3_R.png",
		L"img/monster/brain1_R/brain1_move_4_R.png",
		L"img/monster/brain1_R/brain1_move_5_R.png",
		L"img/monster/brain1_R/brain1_move_6_R.png",
		L"img/monster/brain1_R/brain1_move_7_R.png",
		L"img/monster/brain1_R/brain1_move_8_R.png"
	};

	LPCTSTR brain1_attack_img_path_R[7] = {
		L"img/monster/brain1_R/brain1_attack_1_R.png",
		L"img/monster/brain1_R/brain1_attack_2_R.png",
		L"img/monster/brain1_R/brain1_attack_3_R.png",
		L"img/monster/brain1_R/brain1_attack_4_R.png",
		L"img/monster/brain1_R/brain1_attack_5_R.png",
		L"img/monster/brain1_R/brain1_attack_6_R.png",
		L"img/monster/brain1_R/brain1_attack_7_R.png"
	};

	LPCTSTR brain1_die_img_path_R[5] = {
		L"img/monster/brain1_R/brain1_die_1_R.png",
		L"img/monster/brain1_R/brain1_die_2_R.png",
		L"img/monster/brain1_R/brain1_die_3_R.png",
		L"img/monster/brain1_R/brain1_die_4_R.png",
		L"img/monster/brain1_R/brain1_die_5_R.png"
	};

public:
	Brain1();


	void insert() override; // 움직일 때(사진 바꿀 때)도 쓴다
	void print(const HDC& mDC) override;
	void move(const StageManager& stageManager) override; // rect를 움직이고 insert를 호출해 사진도 바꿔줌
	RECT& getRect() override {
		return rect;
	}
	void MonsterPlayerCollision(Player& p) override; //플레이어랑 충돌했을 때 함수
	void Collisionplayer(const Player& p) override; //플레이어랑 충돌했을때 몬스터의 대처
};



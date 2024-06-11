#pragma once
#pragma once
#include <atlimage.h>

#include "Monster.h"

class Brain2 : public Monster {
	int hp;
	CImage brain2_img;
	int imageNum;
	RECT rect;
	bool left; 
	MonsterStatus status;
	Gravity gravity;

	LPCTSTR brain2_img_path_L[6] = {
		L"img/monster/brain2_L/brain2_move_1_L.png",
		L"img/monster/brain2_L/brain2_move_2_L.png",
		L"img/monster/brain2_L/brain2_move_3_L.png",
		L"img/monster/brain2_L/brain2_move_4_L.png",
		L"img/monster/brain2_L/brain2_move_5_L.png",
		L"img/monster/brain2_L/brain2_move_6_L.png"
	};

	LPCTSTR brain2_attack_img_path_L[6] = {
		L"img/monster/brain2_L/brain2_attack_1_L.png",
		L"img/monster/brain2_L/brain2_attack_2_L.png",
		L"img/monster/brain2_L/brain2_attack_3_L.png",
		L"img/monster/brain2_L/brain2_attack_4_L.png",
		L"img/monster/brain2_L/brain2_attack_5_L.png",
		L"img/monster/brain2_L/brain2_attack_6_L.png"
	};

	LPCTSTR brain2_die_img_path_L[10] = {
		L"img/monster/brain2_L/brain2_die_1_L.png",
		L"img/monster/brain2_L/brain2_die_2_L.png",
		L"img/monster/brain2_L/brain2_die_3_L.png",
		L"img/monster/brain2_L/brain2_die_4_L.png",
		L"img/monster/brain2_L/brain2_die_5_L.png"
		L"img/monster/brain2_L/brain2_die_6_L.png",
		L"img/monster/brain2_L/brain2_die_7_L.png",
		L"img/monster/brain2_L/brain2_die_8_L.png",
		L"img/monster/brain2_L/brain2_die_9_L.png",
		L"img/monster/brain2_L/brain2_die_10_L.png"
	};

	LPCTSTR brain2_img_path_R[6] = {
		L"img/monster/brain2_R/brain2_move_1_R.png",
		L"img/monster/brain2_R/brain2_move_2_R.png",
		L"img/monster/brain2_R/brain2_move_3_R.png",
		L"img/monster/brain2_R/brain2_move_4_R.png",
		L"img/monster/brain2_R/brain2_move_5_R.png",
		L"img/monster/brain2_R/brain2_move_6_R.png"
	};

	LPCTSTR brain2_attack_img_path_R[6] = {
		L"img/monster/brain2_R/brain2_attack_1_R.png",
		L"img/monster/brain2_R/brain2_attack_2_R.png",
		L"img/monster/brain2_R/brain2_attack_3_R.png",
		L"img/monster/brain2_R/brain2_attack_4_R.png",
		L"img/monster/brain2_R/brain2_attack_5_R.png",
		L"img/monster/brain2_R/brain2_attack_6_R.png"
	};

	LPCTSTR brain2_die_img_path_R[10] = {
		L"img/monster/brain2_R/brain2_die_1_R.png",
		L"img/monster/brain2_R/brain2_die_2_R.png",
		L"img/monster/brain2_R/brain2_die_3_R.png",
		L"img/monster/brain2_R/brain2_die_4_R.png",
		L"img/monster/brain2_R/brain2_die_5_R.png",
		L"img/monster/brain2_R/brain2_die_6_R.png",
		L"img/monster/brain2_R/brain2_die_7_R.png",
		L"img/monster/brain2_R/brain2_die_8_R.png",
		L"img/monster/brain2_R/brain2_die_9_R.png",
		L"img/monster/brain2_R/brain2_die_10_R.png"
	};

public:
	Brain2();

	RECT getRect() const; //충돌 체크할 때 필요할까봐 해둠

	void insert() override; // 움직일 때(사진 바꿀 때)도 쓴다
	void print(HDC& mDC) override;
	void move(StageManager& stageManager) override; // rect를 움직이고 insert를 호출해 사진도 바꿔줌
	void attack() override;
	RECT& getRect() override {
		return rect;
	}
};



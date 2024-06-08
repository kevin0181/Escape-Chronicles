#pragma once
#include <atlimage.h>
#include "Monster.h"

#include "Collision.h"
#include "Gravity.h"

class Slime : public Monster {
private:
	int hp;
	CImage slime_img; 
	int imageNum;
	RECT rect;
	bool left; // 슬라임의 이동 방향
	bool bool_attack; //일정 범위 안에 플레이어가 있을시 true, 플레이어를 공격한다
public:
	Gravity gravity;

	LPCTSTR slime_img_path_L[9] = { // 그냥 움직임 L
		L"img/monster/slime_L/Slime_move(1).png",
		L"img/monster/slime_L/Slime_move(2).png",
		L"img/monster/slime_L/Slime_move(3).png",
		L"img/monster/slime_L/Slime_move(4).png",
		L"img/monster/slime_L/Slime_move(5).png",
		L"img/monster/slime_L/Slime_move(6).png",
		L"img/monster/slime_L/Slime_move(7).png",
		L"img/monster/slime_L/Slime_move(8).png",
		L"img/monster/slime_L/Slime_move(9).png"
	};

	LPCTSTR slime_attack_img_path_L[9] = { // 공격 시 움직임 L
		L"img/monster/slime_L/Slime_attack(1).png",
		L"img/monster/slime_L/Slime_attack(2).png",
		L"img/monster/slime_L/Slime_attack(3).png",
		L"img/monster/slime_L/Slime_attack(4).png",
		L"img/monster/slime_L/Slime_attack(5).png",
		L"img/monster/slime_L/Slime_attack(6).png",
		L"img/monster/slime_L/Slime_attack(7).png",
		L"img/monster/slime_L/Slime_attack(8).png",
		L"img/monster/slime_L/Slime_attack(9).png"
	};

	LPCTSTR slime_die_img_path_L[9] = { // L
		L"img/monster/slime_L/Slime_die(1).png",
		L"img/monster/slime_L/Slime_die(2).png",
		L"img/monster/slime_L/Slime_die(3).png",
		L"img/monster/slime_L/Slime_die(4).png",
		L"img/monster/slime_L/Slime_die(5).png",
		L"img/monster/slime_L/Slime_die(6).png",
		L"img/monster/slime_L/Slime_die(7).png",
		L"img/monster/slime_L/Slime_die(8).png",
		L"img/monster/slime_L/Slime_die(9).png",
	};

	LPCTSTR slime_img_path_R[9] = { // 그냥 움직임 R
		L"img/monster/slime_R/Slime_move(1).png",
		L"img/monster/slime_R/Slime_move(2).png",
		L"img/monster/slime_R/Slime_move(3).png",
		L"img/monster/slime_R/Slime_move(4).png",
		L"img/monster/slime_R/Slime_move(5).png",
		L"img/monster/slime_R/Slime_move(6).png",
		L"img/monster/slime_R/Slime_move(7).png",
		L"img/monster/slime_R/Slime_move(8).png",
		L"img/monster/slime_R/Slime_move(9).png"
	};

	LPCTSTR slime_attack_img_path_R[9] = { // 공격 시 움직임 R
		L"img/monster/slime_R/Slime_attack(1).png",
		L"img/monster/slime_R/Slime_attack(2).png",
		L"img/monster/slime_R/Slime_attack(3).png",
		L"img/monster/slime_R/Slime_attack(4).png",
		L"img/monster/slime_R/Slime_attack(5).png",
		L"img/monster/slime_R/Slime_attack(6).png",
		L"img/monster/slime_R/Slime_attack(7).png",
		L"img/monster/slime_R/Slime_attack(8).png",
		L"img/monster/slime_R/Slime_attack(9).png"
	};

	LPCTSTR slime_die_img_path_R[9] = { // R
		L"img/monster/slime_R/Slime_die(1).png",
		L"img/monster/slime_R/Slime_die(2).png",
		L"img/monster/slime_R/Slime_die(3).png",
		L"img/monster/slime_R/Slime_die(4).png",
		L"img/monster/slime_R/Slime_die(5).png",
		L"img/monster/slime_R/Slime_die(6).png",
		L"img/monster/slime_R/Slime_die(7).png",
		L"img/monster/slime_R/Slime_die(8).png",
		L"img/monster/slime_R/Slime_die(9).png",
	};

	Slime();


	RECT getRect() const; //충돌 체크할 때 필요할까봐 해둠

	void insert() override; // 움직일 때(사진 바꿀 때)도 쓴다
	void print(HDC& mDC) override; 
	void move(RECT Rect) override; // rect를 움직이고 insert를 호출해 사진도 바꿔줌
	void attack(bool status) override;

	RECT& getRect() override;
};



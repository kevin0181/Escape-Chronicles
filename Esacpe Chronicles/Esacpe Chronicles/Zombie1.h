#pragma once
#include <atlimage.h>
#include "Monster.h"

class Zombie1 : public Monster {
private:
	int hp;
	CImage zombie1_img;
	int imageNum;
	RECT rect;
	bool left; // 좀비의 이동 방향
	bool bool_attack; //일정 범위 안에 플레이어가 있을시 true, 플레이어를 공격한다
public:
	LPCTSTR zombie1_img_path[8] = { // zombieman
		L"img/monster/zombieman/zombieman_walk_1.png",
		L"img/monster/zombieman/zombieman_walk_2.png",
		L"img/monster/zombieman/zombieman_walk_3.png",
		L"img/monster/zombieman/zombieman_walk_4.png",
		L"img/monster/zombieman/zombieman_walk_5.png",
		L"img/monster/zombieman/zombieman_walk_6.png",
		L"img/monster/zombieman/zombieman_walk_7.png",
		L"img/monster/zombieman/zombieman_walk_8.png"
	};

	LPCTSTR zombie1_attack_img_path[5] = { 
		L"img/monster/zombieman/zombieman_attack_1.png",
		L"img/monster/zombieman/zombieman_attack_2.png",
		L"img/monster/zombieman/zombieman_attack_3.png",
		L"img/monster/zombieman/zombieman_attack_4.png",
		L"img/monster/zombieman/zombieman_attack_5.png"
	};

	LPCTSTR zombie1_die_img_path[4] = {
		L"img/monster/zombieman/zombieman_die_1.png",
		L"img/monster/zombieman/zombieman_die_2.png",
		L"img/monster/zombieman/zombieman_die_3.png",
		L"img/monster/zombieman/zombieman_die_4.png"
	};

	Zombie1();


	RECT getRect() const; //충돌 체크할 때 필요할까봐 해둠
	
	void insert() override; // 움직일 때(사진 바꿀 때)도 쓴다
	void print(HDC& mDC) override;
	void move(RECT Rect) override; // rect를 움직이고 insert를 호출해 사진도 바꿔줌
	void attack(bool status) override;
};



#pragma once
#include <atlimage.h>

#include "Monster.h"
#include "Collision.h"
#include "Gravity.h"
#include "StageManager.h"

class Zombie1 : public Monster {
	int hp;
	CImage zombie1_img;
	int imageNum;
	RECT rect;
	bool left; // ������ �̵� ����
	MonsterStatus status;
	Gravity gravity;

	LPCTSTR zombie1_img_path_L[8] = { // zombieman
		L"img/monster/zombieman_L/zombieman_walk_1.png",
		L"img/monster/zombieman_L/zombieman_walk_2.png",
		L"img/monster/zombieman_L/zombieman_walk_3.png",
		L"img/monster/zombieman_L/zombieman_walk_4.png",
		L"img/monster/zombieman_L/zombieman_walk_5.png",
		L"img/monster/zombieman_L/zombieman_walk_6.png",
		L"img/monster/zombieman_L/zombieman_walk_7.png",
		L"img/monster/zombieman_L/zombieman_walk_8.png"
	};

	LPCTSTR zombie1_attack_img_path_L[5] = {
		L"img/monster/zombieman_L/zombieman_attack_1.png",
		L"img/monster/zombieman_L/zombieman_attack_2.png",
		L"img/monster/zombieman_L/zombieman_attack_3.png",
		L"img/monster/zombieman_L/zombieman_attack_4.png",
		L"img/monster/zombieman_L/zombieman_attack_5.png"
	};

	LPCTSTR zombie1_die_img_path_L[4] = {
		L"img/monster/zombieman_L/zombieman_die_1.png",
		L"img/monster/zombieman_L/zombieman_die_2.png",
		L"img/monster/zombieman_L/zombieman_die_3.png",
		L"img/monster/zombieman_L/zombieman_die_4.png"
	};

	LPCTSTR zombie1_img_path_R[8] = { // zombieman
		L"img/monster/zombieman_R/zombieman_walk_1.png",
		L"img/monster/zombieman_R/zombieman_walk_2.png",
		L"img/monster/zombieman_R/zombieman_walk_3.png",
		L"img/monster/zombieman_R/zombieman_walk_4.png",
		L"img/monster/zombieman_R/zombieman_walk_5.png",
		L"img/monster/zombieman_R/zombieman_walk_6.png",
		L"img/monster/zombieman_R/zombieman_walk_7.png",
		L"img/monster/zombieman_R/zombieman_walk_8.png"
	};

	LPCTSTR zombie1_attack_img_path_R[5] = { 
		L"img/monster/zombieman_R/zombieman_attack_1.png",
		L"img/monster/zombieman_R/zombieman_attack_2.png",
		L"img/monster/zombieman_R/zombieman_attack_3.png",
		L"img/monster/zombieman_R/zombieman_attack_4.png",
		L"img/monster/zombieman_R/zombieman_attack_5.png"
	};

	LPCTSTR zombie1_die_img_path_R[4] = {
		L"img/monster/zombieman_R/zombieman_die_1.png",
		L"img/monster/zombieman_R/zombieman_die_2.png",
		L"img/monster/zombieman_R/zombieman_die_3.png",
		L"img/monster/zombieman_R/zombieman_die_4.png"
	};

public:
	Zombie1();


	RECT getRect() const; //�浹 üũ�� �� �ʿ��ұ�� �ص�
	void insert() override; // ������ ��(���� �ٲ� ��)�� ����
	void print(HDC& mDC) override;
	void move(StageManager& stageManager) override; // rect�� �����̰� insert�� ȣ���� ������ �ٲ���
	void attack() override;
	RECT& getRect() override {
		return rect;
	}
};



#pragma once
#include "Monster.h"

class Boss : public Monster {
	int hp;
	CImage boss_img;
	int imageNum;
	RECT rect;
	bool left;
	MonsterStatus status;
	Gravity gravity;

	LPCTSTR boss_img_path_L[6] = { // �׳� ������ L
		L"img/monster/boss_L/boss_walk_1.png",
		L"img/monster/boss_L/boss_walk_2.png",
		L"img/monster/boss_L/boss_walk_3.png",
		L"img/monster/boss_L/boss_walk_4.png",
		L"img/monster/boss_L/boss_walk_5.png",
		L"img/monster/boss_L/boss_walk_6.png"
	};
	
	LPCTSTR boss_attack_img_path_L[6] = { // ���� �� ������ L
		L"img/monster/boss_L/boss_attack_1.png",
		L"img/monster/boss_L/boss_attack_2.png",
		L"img/monster/boss_L/boss_attack_3.png",
		L"img/monster/boss_L/boss_attack_4.png",
		L"img/monster/boss_L/boss_attack_5.png",
		L"img/monster/boss_L/boss_attack_6.png"
	};

	LPCTSTR boss_die_img_path_L[6] = { // L
		L"img/monster/boss_L/boss_die_1.png",
		L"img/monster/boss_L/boss_die_2.png",
		L"img/monster/boss_L/boss_die_3.png",
		L"img/monster/boss_L/boss_die_4.png",
		L"img/monster/boss_L/boss_die_5.png",
		L"img/monster/boss_L/boss_die_6.png"
	};

	LPCTSTR boss_img_path_R[6] = { // �׳� ������ R
		L"img/monster/boss_R/boss_walk_1.png",
		L"img/monster/boss_R/boss_walk_2.png",
		L"img/monster/boss_R/boss_walk_3.png",
		L"img/monster/boss_R/boss_walk_4.png",
		L"img/monster/boss_R/boss_walk_5.png",
		L"img/monster/boss_R/boss_walk_6.png"
	};

	LPCTSTR boss_attack_img_path_R[6] = { // ���� �� ������ R
		L"img/monster/boss_R/boss_attack_1.png",
		L"img/monster/boss_R/boss_attack_2.png",
		L"img/monster/boss_R/boss_attack_3.png",
		L"img/monster/boss_R/boss_attack_4.png",
		L"img/monster/boss_R/boss_attack_5.png",
		L"img/monster/boss_R/boss_attack_6.png"
	};

	LPCTSTR boss_die_img_path_R[6] = { // R
		L"img/monster/boss_R/boss_die_1.png",
		L"img/monster/boss_R/boss_die_2.png",
		L"img/monster/boss_R/boss_die_3.png",
		L"img/monster/boss_R/boss_die_4.png",
		L"img/monster/boss_R/boss_die_5.png",
		L"img/monster/boss_R/boss_die_6.png"
	};

public:
	Boss();

	void insert() override; // ������ ��(���� �ٲ� ��)�� ����
	void print(const HDC& mDC) override;
	void move(const StageManager& stageManager) override; // rect�� �����̰� insert�� ȣ���� ������ �ٲ���

	RECT& getRect() override;
	void MonsterPlayerCollision(Player& p) override; //�÷��̾�� �浹���� �� �Լ�
	void Collisionplayer(const Player& p) override; //�÷��̾�� �浹������ ������ ��ó
};



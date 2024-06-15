#pragma once
#include "Monster.h"

class Eye : public Monster {
	int hp;
	CImage eye_img;
	int imageNum;
	RECT rect;
	bool left; // �������� �̵� ����
	MonsterStatus status;
	Gravity gravity;

	LPCTSTR eye_img_path_L[10] = { // �׳� ������ L
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

	LPCTSTR eye_attack_img_path_L[10] = { // ���� �� ������ L
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

	LPCTSTR eye_img_path_R[10] = { // �׳� ������ R
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

	void insert() override; // ������ ��(���� �ٲ� ��)�� ����
	void print(const HDC& mDC) override;
	void move(const StageManager& stageManager) override; // rect�� �����̰� insert�� ȣ���� ������ �ٲ���

	MonsterStatus getStatus() const override;
	RECT& getRect() override;
	void MonsterPlayerCollision(Player& p) override; //�÷��̾�� �浹���� �� �Լ�
	void Collisionplayer(const Player& p) override; //�÷��̾�� �浹������ ������ ��ó
	bool checkBlock(const StageManager& stageManager);
};



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

	LPCTSTR eye_attack_img_path_L[9] = { // ���� �� ������ L
		L"img/monster/slime_L_v2/Slime_attack(1).png",
		L"img/monster/slime_L_v2/Slime_attack(2).png",
		L"img/monster/slime_L_v2/Slime_attack(3).png",
		L"img/monster/slime_L_v2/Slime_attack(4).png",
		L"img/monster/slime_L_v2/Slime_attack(5).png",
		L"img/monster/slime_L_v2/Slime_attack(6).png",
		L"img/monster/slime_L_v2/Slime_attack(7).png",
		L"img/monster/slime_L_v2/Slime_attack(8).png",
		L"img/monster/slime_L_v2/Slime_attack(9).png"
	};

	LPCTSTR eye_die_img_path_L[9] = { // L
		L"img/monster/slime_L_v2/Slime_die(1).png",
		L"img/monster/slime_L_v2/Slime_die(2).png",
		L"img/monster/slime_L_v2/Slime_die(3).png",
		L"img/monster/slime_L_v2/Slime_die(4).png",
		L"img/monster/slime_L_v2/Slime_die(5).png",
		L"img/monster/slime_L_v2/Slime_die(6).png",
		L"img/monster/slime_L_v2/Slime_die(7).png",
		L"img/monster/slime_L_v2/Slime_die(8).png",
		L"img/monster/slime_L_v2/Slime_die(9).png",
	};

	LPCTSTR eye_img_path_R[9] = { // �׳� ������ R
		L"img/monster/slime_R_v2/Slime_move(1).png",
		L"img/monster/slime_R_v2/Slime_move(2).png",
		L"img/monster/slime_R_v2/Slime_move(3).png",
		L"img/monster/slime_R_v2/Slime_move(4).png",
		L"img/monster/slime_R_v2/Slime_move(5).png",
		L"img/monster/slime_R_v2/Slime_move(6).png",
		L"img/monster/slime_R_v2/Slime_move(7).png",
		L"img/monster/slime_R_v2/Slime_move(8).png",
		L"img/monster/slime_R_v2/Slime_move(9).png"
	};

	LPCTSTR eye_attack_img_path_R[9] = { // ���� �� ������ R
		L"img/monster/slime_R_v2/Slime_attack(1).png",
		L"img/monster/slime_R_v2/Slime_attack(2).png",
		L"img/monster/slime_R_v2/Slime_attack(3).png",
		L"img/monster/slime_R_v2/Slime_attack(4).png",
		L"img/monster/slime_R_v2/Slime_attack(5).png",
		L"img/monster/slime_R_v2/Slime_attack(6).png",
		L"img/monster/slime_R_v2/Slime_attack(7).png",
		L"img/monster/slime_R_v2/Slime_attack(8).png",
		L"img/monster/slime_R_v2/Slime_attack(9).png"
	};

	LPCTSTR eye_die_img_path_R[9] = { // R
		L"img/monster/slime_R_v2/Slime_die(1).png",
		L"img/monster/slime_R_v2/Slime_die(2).png",
		L"img/monster/slime_R_v2/Slime_die(3).png",
		L"img/monster/slime_R_v2/Slime_die(4).png",
		L"img/monster/slime_R_v2/Slime_die(5).png",
		L"img/monster/slime_R_v2/Slime_die(6).png",
		L"img/monster/slime_R_v2/Slime_die(7).png",
		L"img/monster/slime_R_v2/Slime_die(8).png",
		L"img/monster/slime_R_v2/Slime_die(9).png",
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
};



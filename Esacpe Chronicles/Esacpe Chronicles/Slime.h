#pragma once
#include "Monster.h"

class Slime : public Monster {
	int hp;
	CImage slime_img; 
	int imageNum;
	RECT rect;
	bool left; // �������� �̵� ����
	MonsterStatus status;
	Gravity gravity;

	LPCTSTR slime_img_path_L[9] = { // �׳� ������ L
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

	LPCTSTR slime_attack_img_path_L[9] = { // ���� �� ������ L
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

	LPCTSTR slime_img_path_R[9] = { // �׳� ������ R
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

	LPCTSTR slime_attack_img_path_R[9] = { // ���� �� ������ R
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

public:
	Slime();

	//RECT& getRect() const; //�浹 üũ�� �� �ʿ��ұ�� �ص�
	void insert() override; // ������ ��(���� �ٲ� ��)�� ����
	void print(HDC& mDC) override; 
	void move(StageManager& stageManager) override; // rect�� �����̰� insert�� ȣ���� ������ �ٲ���
	void attack() override;

	RECT& getRect() override;
	void MonsterPlayerCollision(Player& p) override; //�÷��̾�� �浹���� �� �Լ�
	void Collisionplayer(Player& p) override; //�÷��̾�� �浹������ ������ ��ó
};



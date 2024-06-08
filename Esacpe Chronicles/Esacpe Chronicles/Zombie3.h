#pragma once
#include <atlimage.h>
#include "Monster.h"
#include "Collision.h"

class Zombie3 : public Monster {
private:
	int hp;
	CImage zombie3_img;
	int imageNum;
	RECT rect;
	bool left; // ������ �̵� ����
	bool bool_attack; //���� ���� �ȿ� �÷��̾ ������ true, �÷��̾ �����Ѵ�
public:
	LPCTSTR zombie3_img_path_L[10] = { // wildzombie
		L"img/monster/wildzombie_L/wildzombie_walk_1.png",
		L"img/monster/wildzombie_L/wildzombie_walk_2.png",
		L"img/monster/wildzombie_L/wildzombie_walk_3.png",
		L"img/monster/wildzombie_L/wildzombie_walk_4.png",
		L"img/monster/wildzombie_L/wildzombie_walk_5.png",
		L"img/monster/wildzombie_L/wildzombie_walk_6.png",
		L"img/monster/wildzombie_L/wildzombie_walk_7.png",
		L"img/monster/wildzombie_L/wildzombie_walk_8.png",
		L"img/monster/wildzombie_L/wildzombie_walk_9.png",
		L"img/monster/wildzombie_L/wildzombie_walk_10.png"

	};

	LPCTSTR zombie3_attack_img_path_L[4] = {
		L"img/monster/wildzombie_L/wildzombie_attack_1.png",
		L"img/monster/wildzombie_L/wildzombie_attack_2.png",
		L"img/monster/wildzombie_L/wildzombie_attack_3.png",
		L"img/monster/wildzombie_L/wildzombie_attack_4.png",
	};

	LPCTSTR zombie3_die_img_path_L[5] = {
		L"img/monster/wildzombie_L/wildzombie_die_1.png",
		L"img/monster/wildzombie_L/wildzombie_die_2.png",
		L"img/monster/wildzombie_L/wildzombie_die_3.png",
		L"img/monster/wildzombie_L/wildzombie_die_4.png",
		L"img/monster/wildzombie_L/wildzombie_die_5.png"
	};

	LPCTSTR zombie3_img_path_R[10] = { // wildzombie
		L"img/monster/wildzombie_R/wildzombie_walk_1.png",
		L"img/monster/wildzombie_R/wildzombie_walk_2.png",
		L"img/monster/wildzombie_R/wildzombie_walk_3.png",
		L"img/monster/wildzombie_R/wildzombie_walk_4.png",
		L"img/monster/wildzombie_R/wildzombie_walk_5.png",
		L"img/monster/wildzombie_R/wildzombie_walk_6.png",
		L"img/monster/wildzombie_R/wildzombie_walk_7.png",
		L"img/monster/wildzombie_R/wildzombie_walk_8.png",
		L"img/monster/wildzombie_R/wildzombie_walk_9.png",
		L"img/monster/wildzombie_R/wildzombie_walk_10.png"

	};

	LPCTSTR zombie3_attack_img_path_R[4] = {
		L"img/monster/wildzombie_R/wildzombie_attack_1.png",
		L"img/monster/wildzombie_R/wildzombie_attack_2.png",
		L"img/monster/wildzombie_R/wildzombie_attack_3.png",
		L"img/monster/wildzombie_R/wildzombie_attack_4.png",
	};

	LPCTSTR zombie3_die_img_path_R[5] = {
		L"img/monster/wildzombie_R/wildzombie_die_1.png",
		L"img/monster/wildzombie_R/wildzombie_die_2.png",
		L"img/monster/wildzombie_R/wildzombie_die_3.png",
		L"img/monster/wildzombie_R/wildzombie_die_4.png",
		L"img/monster/wildzombie_R/wildzombie_die_5.png"
	};

	Zombie3();

	RECT getRect() const; //�浹 üũ�� �� �ʿ��ұ�� �ص�

	void insert() override; // ������ ��(���� �ٲ� ��)�� ����
	void print(HDC& mDC) override;
	void move(RECT Rect) override; // rect�� �����̰� insert�� ȣ���� ������ �ٲ���
	void attack(bool status) override;
	RECT& getRect() override {
		return rect;
	}
};



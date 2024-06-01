#pragma once
#include <atlimage.h>
#include "Monster.h"

class Zombie1 : public Monster {
private:
	int hp;
	CImage zombie1_img;
	int imageNum;
	RECT rect;
	bool left; // ������ �̵� ����
	bool bool_attack; //���� ���� �ȿ� �÷��̾ ������ true, �÷��̾ �����Ѵ�
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


	RECT getRect() const; //�浹 üũ�� �� �ʿ��ұ�� �ص�
	
	void insert() override; // ������ ��(���� �ٲ� ��)�� ����
	void print(HDC& mDC) override;
	void move(RECT Rect) override; // rect�� �����̰� insert�� ȣ���� ������ �ٲ���
	void attack(bool status) override;
};



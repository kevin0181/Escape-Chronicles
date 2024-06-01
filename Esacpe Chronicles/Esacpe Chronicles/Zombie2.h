#pragma once
#include <atlimage.h>
#include "Monster.h"

class Zombie2 : public Monster {
private:
	int hp;
	CImage zombie2_img;
	int imageNum;
	RECT rect;
	bool left; // ������ �̵� ����
	bool bool_attack; //���� ���� �ȿ� �÷��̾ ������ true, �÷��̾ �����Ѵ�
public:
	LPCTSTR zombie2_img_path[7] = { // zombiewoman
		L"img/monster/zombiewoman/zombiewoman_walk_1.png",
		L"img/monster/zombiewoman/zombiewoman_walk_2.png",
		L"img/monster/zombiewoman/zombiewoman_walk_3.png",
		L"img/monster/zombiewoman/zombiewoman_walk_4.png",
		L"img/monster/zombiewoman/zombiewoman_walk_5.png",
		L"img/monster/zombiewoman/zombiewoman_walk_6.png",
		L"img/monster/zombiewoman/zombiewoman_walk_7.png"
	};

	LPCTSTR zombie2_attack_img_path[4] = {
		L"img/monster/zombiewoman/zombiewoman_attack_1.png",
		L"img/monster/zombiewoman/zombiewoman_attack_2.png",
		L"img/monster/zombiewoman/zombiewoman_attack_3.png",
		L"img/monster/zombiewoman/zombiewoman_attack_4.png"
	};

	LPCTSTR zombie2_die_img_path[5] = {
		L"img/monster/zombiewoman/zombiewoman_die_1.png",
		L"img/monster/zombiewoman/zombiewoman_die_2.png",
		L"img/monster/zombiewoman/zombiewoman_die_3.png",
		L"img/monster/zombiewoman/zombiewoman_die_4.png",
		L"img/monster/zombiewoman/zombiewoman_die_5.png"
	};

	Zombie2();

	RECT getRect() const; //�浹 üũ�� �� �ʿ��ұ�� �ص�

	void insert() override; // ������ ��(���� �ٲ� ��)�� ����
	void print(HDC& mDC) override;
	void move(RECT Rect) override; // rect�� �����̰� insert�� ȣ���� ������ �ٲ���
	void attack(bool status) override;
};



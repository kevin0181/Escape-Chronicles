#pragma once
#include <atlimage.h>
#include "Monster.h"

class Zombie : public Monster {
private:
	int hp;
	int num; //���� 3�� ������ �� ����
	CImage zombie_img;
	int imagenum;
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
		L"img/monster/zombieman/zombieman_die_3.png"
	};

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

	LPCTSTR zombie3_img_path[10] = { // wildzombie
		L"img/monster/wildzombie/wildzombie_walk_1.png",
		L"img/monster/wildzombie/wildzombie_walk_2.png",
		L"img/monster/wildzombie/wildzombie_walk_3.png",
		L"img/monster/wildzombie/wildzombie_walk_4.png",
		L"img/monster/wildzombie/wildzombie_walk_5.png",
		L"img/monster/wildzombie/wildzombie_walk_6.png",
		L"img/monster/wildzombie/wildzombie_walk_7.png",
		L"img/monster/wildzombie/wildzombie_walk_8.png",
		L"img/monster/wildzombie/wildzombie_walk_9.png",
		L"img/monster/wildzombie/wildzombie_walk_10.png"

	};

	LPCTSTR zombie3_attack_img_path[4] = {
		L"img/monster/wildzombie/wildzombie_attack_1.png",
		L"img/monster/wildzombie/wildzombie_attack_2.png",
		L"img/monster/wildzombie/wildzombie_attack_3.png",
		L"img/monster/wildzombie/wildzombie_attack_4.png",
	};

	LPCTSTR zombie3_die_img_path[5] = {
		L"img/monster/wildzombie/wildzombie_die_1.png",
		L"img/monster/wildzombie/wildzombie_die_2.png",
		L"img/monster/wildzombie/wildzombie_die_3.png",
		L"img/monster/wildzombie/wildzombie_die_4.png",
		L"img/monster/wildzombie/wildzombie_die_5.png"
	};

	Zombie();


	RECT getRect() const; //�浹 üũ�� �� �ʿ��ұ�� �ص�
	/*
	void insert() override; // ������ ��(���� �ٲ� ��)�� ����
	void print(HDC& mDC) override;
	void move(RECT Rect) override; // rect�� �����̰� insert�� ȣ���� ������ �ٲ���
	void attack();
	void die();*/
};



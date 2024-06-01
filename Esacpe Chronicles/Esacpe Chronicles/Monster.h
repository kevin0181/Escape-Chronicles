#pragma once
#include <string>
#include < atlimage.h >
#include <windows.h>

class Monster {
public:
	virtual void insert() = 0;
	virtual void print(HDC& mDC) = 0;
	virtual void move(RECT Rect) = 0;
	virtual void attack(bool status) = 0;

	bool CheckMonsterCollision(RECT rect1,RECT rect2); // ���Ϳ� �浹Ȯ��
	bool CheckBlockCollision(RECT rect, RECT rect1, bool left, RECT rect2); // ȭ��,��ϰ� �浹Ȯ�� (ȭ�� rect, ��� rect, �񱳴�� �̵�����,�񱳴�� rect)
};
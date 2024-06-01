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

	bool CheckMonsterCollision(RECT rect1,RECT rect2); // 몬스터와 충돌확인
	bool CheckBlockCollision(RECT rect, RECT rect1, bool left, RECT rect2); // 화면,블록과 충돌확인 (화면 rect, 블록 rect, 비교대상 이동방향,비교대상 rect)
};
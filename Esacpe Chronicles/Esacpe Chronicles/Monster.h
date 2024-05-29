#pragma once
#include <string>
#include < atlimage.h >
#include <windows.h>

class Monster {
	RECT rect;
	int dx;
	int dy;
	int hp;
	int imagenum;

public:
	Monster();
	Monster(RECT r, int dx, int dy, int h, int i) :rect(r), dx(dx), dy(dy), hp(h), imagenum(i) {}

	virtual void insert() = 0;
	virtual void print(HDC& mDC,int imagenum, RECT rect, int x, int y) = 0;
	virtual void move(RECT rect, bool left) = 0;
};
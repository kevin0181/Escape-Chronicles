#pragma once
#include <atlimage.h>
#include "Monster.h"

class Slime : public Monster {
private:
	CImage img[9];
public:
	Slime() {
		Slime slime({ 0,0,40,50 }, 2, 0, 20, 0);
		slime.insert();
	}

	Slime(RECT r, int dx, int dy, int h, int i) : Monster(r, dx, dy, h, i) {}

	void insert() override;
	void print(HDC& mDC,int imagenum, RECT rect, int x, int y) override;
	void move(RECT rect, bool left) override;
	void attack();
};



#pragma once
#include <string>
#include < atlimage.h >
#include <windows.h>
#include "Player.h"

class Monster {
public:
	virtual void insert() = 0;
	virtual void print(HDC& mDC) = 0;
	virtual void move(RECT Rect) = 0;
	virtual void attack(bool status) = 0;
	virtual RECT getRect() = 0;
};
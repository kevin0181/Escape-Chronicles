#pragma once
#include <string>
#include < atlimage.h >
#include <windows.h>

class Monster {
public:
	virtual void insert() = 0;
	virtual void print(HDC& mDC) = 0;
	virtual void move(RECT Rect) = 0;
};
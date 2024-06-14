#pragma once
#include<atlimage.h>

#include "Player.h"

class Ui {
	CImage Hp_img;
	RECT rect;
	COLORREF Red = RGB(255, 0, 0);

	LPCTSTR hp_bar = L"img/ui/hp_bar.png";
public:
	Ui() : rect({ 0, 0, 0, 0 }) {
		Hp_img.Load(hp_bar);
	};
	void print(const HDC& mDC, const Player& player);
};
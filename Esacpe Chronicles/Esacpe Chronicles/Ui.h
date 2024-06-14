#pragma once
#include<atlimage.h>

class Ui {
	CImage Hp_img;
	RECT rect;

	LPCTSTR hp_bar = L"img/ui/hp_bar.png";
public:
	Ui() : rect({ 0, 0, 0, 0 }) {
		Hp_img.Load(hp_bar);
	};
	void print(const HDC& mDC);
};
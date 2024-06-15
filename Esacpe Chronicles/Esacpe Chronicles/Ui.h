#pragma once
#include<atlimage.h>

#include "StageManager.h"
#include "Player.h"

class Ui {
	CImage Hp_img;
	CImage Esc_img;
	RECT rect;
	COLORREF Red = RGB(255, 0, 0);

	LPCTSTR hp_bar = L"img/ui/hp_bar.png";
	LPCTSTR esc_bar = L"img/ui/esc.png";

public:
	Ui() : rect({ 0, 0, 0, 0 }) {
		Hp_img.Load(hp_bar);
		Esc_img.Load(esc_bar);
	};

	void print(const HDC& mDC, const Player& player);
	void escprint(const HDC& mDC, const StageManager& stagemanager);
};
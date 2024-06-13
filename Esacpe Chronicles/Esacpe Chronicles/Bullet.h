#pragma once
#include <atlimage.h>
#include <memory>

class Bullet {
public:

	LPCTSTR _arrow_r[1] = {
		L"img/character/main/weapon/bow/arrow.png"
	};

	LPCTSTR _bullet_r[1] = {
		L"img/character/main/weapon/gun/8.png"
	};

	Gdiplus::Image* img = nullptr;
	RECT rect;
	bool status = false;
	float vx;
	float vy;
	int weapon_status = 0;
	float angle;
};
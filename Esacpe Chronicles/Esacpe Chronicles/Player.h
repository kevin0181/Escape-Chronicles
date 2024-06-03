#pragma once

#include <atlimage.h>
#include <memory>

#include "ActiveStatus.h"

class Player {
	/*bool left;
	bool right;
	bool jump;
	bool attack;
	bool defense;*/

	Status status;
	int speed;
	RECT rect;

	int img_num;
	std::unique_ptr<CImage> cImage;

	LPCTSTR _default[5] = {
		L"img/character/main/stay/stay_1.png",
		L"img/character/main/stay/stay_2.png",
		//L"img/character/main/stay/stay_3.png",
		L"img/character/main/stay/stay_4.png",
		L"img/character/main/stay/stay_5.png",
		L"img/character/main/stay/stay_6.png",
	};


public:

	Player() :cImage(std::make_unique<CImage>()), status(Status::DEFAULT), speed(3), img_num(0) {
		rect = { 0,0,70,90 };
		OffsetRect(&rect, 0, 960);
		HRESULT hr = cImage->Load(_default[0]);
		if (FAILED(hr)) {
			MessageBox(NULL, L"��� �̹��� �ε� ����", L"����", MB_OK);
		}
	};

	void print(HDC& mDC) const;
	int getCimageSize() const; // ���� �ش� �̹����� ũ�⸦ ��������
	void setImg(int img_num); // ĳ���� �̹��� �Ҵ�

	int getImgNum() const;
};
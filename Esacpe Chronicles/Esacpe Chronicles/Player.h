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
			MessageBox(NULL, L"블록 이미지 로드 실패", L"오류", MB_OK);
		}
	};

	void print(HDC& mDC) const;
	int getCimageSize() const; // 현재 해당 이미지의 크기를 가져오기
	void setImg(int img_num); // 캐릭터 이미지 할당

	int getImgNum() const;
};
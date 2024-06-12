#pragma once
#include <atlimage.h>
#include <memory>

class Bullet {
public:
	LPCTSTR _arrow_r[1] = {
		L"img/character/main/weapon/bow/arrow.png"
	};

	LPCTSTR _arrow_l[2] = {
		L"img/character/main/weapon/bow/arrow_l.png"
	};

	std::unique_ptr<CImage> cImage;
	RECT rect;

	Bullet() :cImage(std::make_unique<CImage>()) {
		HRESULT hr3 = cImage->Load(_arrow_r[0]);

		if (FAILED(hr3)) {
			MessageBox(NULL, L"총알 이미지 로드 실패", L"오류", MB_OK);
		}
	}
};
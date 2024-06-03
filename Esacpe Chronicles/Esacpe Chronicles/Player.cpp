#include"Player.h"

int Player::getCimageSize() const{ 
	if (status == Status::DEFAULT) {
		return sizeof(_default) / sizeof(_default[0]);
	}
}

void Player::print(HDC& mDC) const {
    if (!cImage->IsNull()) {
        cImage->Draw(mDC, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0, 0, cImage->GetWidth(), cImage->GetHeight());
    }
    else {
        MessageBox(NULL, L"유효하지 않은 블록 이미지", L"오류", MB_OK);
    }
}

int Player::getImgNum()const {
	return img_num;
}

void Player::setImg(int img_num) {
	this->img_num = img_num;

	
	// main character
	if (img_num >= getCimageSize()) {
		this->img_num = 0;
	}

	cImage->Destroy();

	if (status == Status::DEFAULT) {
		cImage->Load(_default[this->img_num]);
	}

}
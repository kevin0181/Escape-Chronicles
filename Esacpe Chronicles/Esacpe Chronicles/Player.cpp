#include"Player.h"

int Player::getCimageSize() const{ 
	switch (status)
	{
	case DEFAULT_R:
		return sizeof(_default_r) / sizeof(_default_r[0]);
		break;
	case DEFAULT_L:
		return sizeof(_default_l) / sizeof(_default_l[0]);
		break;
	case LEFT:
		return sizeof(_left) / sizeof(_left[0]);
		break;
	case RIGHT:
		return sizeof(_right) / sizeof(_right[0]);
		break;
	/*case JUMP_R:
		return sizeof(_jump_r) / sizeof(_jump_r[0]);
		break;
	case JUMP_L:
		return sizeof(_jump_l) / sizeof(_jump_l[0]);
		break;*/
	case ATTACK:
		break;
	case DEFENSE:
		break;
	default:
		break;
	}
}

void Player::print(HDC& mDC) const {
    if (!cImage->IsNull()) {
        cImage->Draw(mDC, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0, 0, cImage->GetWidth(), cImage->GetHeight());
    }
    else {
        MessageBox(NULL, L"유효하지 않은 캐릭터 이미지", L"오류", MB_OK);
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

	switch (status)
	{
	case DEFAULT_L:
		cImage->Load(_default_l[this->img_num]);
		break;
	case DEFAULT_R:
		cImage->Load(_default_r[this->img_num]);
		break;
	case LEFT:
		cImage->Load(_left[this->img_num]);
		break;
	case RIGHT:
		cImage->Load(_right[this->img_num]);
		break;
	case ATTACK:
		break;
	case DEFENSE:
		break;
	default:
		break;
	}

}

void Player::setKeyDown(WPARAM wParam) {
	switch (wParam)
	{
	case 65: //a
		status = PlayerStatus::LEFT;
		break;
	case 87: //w
		isJumping = true;
		break;
	case 83: //s
		break;
	case 68: //d
		status = PlayerStatus::RIGHT;
		break;
	default:
		break;
	}
}

void Player::setKeyUp(WPARAM wParam) {
	switch (wParam)
	{
	case 65: //a
		status = PlayerStatus::DEFAULT_L;
		break;
	case 87: //w
		break;
	case 83: //s
		break;
	case 68: //d
		status = PlayerStatus::DEFAULT_R;
		break;
	default:
		break;
	}
}

void Player::move() {
	switch (status)
	{
	case DEFAULT_R:
		break;
	case DEFAULT_L:
		break;
	case LEFT:
		OffsetRect(&rect, -speed, 0);
		break;
	case RIGHT:
		OffsetRect(&rect, speed, 0);
		break;
	case ATTACK:
		break;
	case DEFENSE:
		break;
	default:
		break;
	}
}
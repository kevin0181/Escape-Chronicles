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
        MessageBox(NULL, L"��ȿ���� ���� ĳ���� �̹���", L"����", MB_OK);
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
		if (!isJumping) {
			isJumping = true;
			initialY = rect.top;
		}
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

void Player::jump() {
	if (isJumping) {
		rect.top -= jumpSpeed;
		rect.bottom -= jumpSpeed;
		currentJumpHeight += jumpSpeed;

		if (currentJumpHeight >= jumpHeight) {
			currentJumpHeight = 0;
			isJumping = false; // �߷¶����� �ϴ� �߰��ߴµ�, �浹 �˻��Ҷ� y�� �浹�̸� false�� �����ϰ� �ڵ� ���� �ʿ�
		}
	}
}

void Player::move() {

	if (isJumping) {
		jump();
	}

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

void Player::setRECT(RECT rect) {
	this->rect = rect;
}

RECT& Player::getRECT(){
	return rect;
}

RECT& Player::getSaveRect() {
	return saveRect;
}

void Player::setSaveRect(RECT rect) {
	this->saveRect = rect;
}

bool Player::crash_check_block(RECT& rect, std::vector<Block>& blocks) { //
	RECT crossRect;
	for (auto& block : blocks) {
		if (IntersectRect(&crossRect, &rect, &block.rect)) {
			return true;
		}
	}

	return false;
}

void Player::TIMER(StageManager& stageManager) {
	
	setImg(img_num + 1);

	move();
	setSaveRect(rect);
	gravity.UpdatePhysics(rect);
	if (crash_check_block(rect, stageManager.blocks_stage1)) {
		rect = saveRect;
	}
}
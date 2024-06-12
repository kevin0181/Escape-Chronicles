#include"Player.h"
#include "GlobalVariables.h"

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
		switch (attack_sword)
		{
		case 0:
		case 1:
		case 2:
		case 3:
			return 4;
			break;
		case 4:
			return 6;
		default:
			break;
		}
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
		weapon_cImage->Draw(mDC, weapon_rect.left, weapon_rect.top, weapon_rect.right - weapon_rect.left, weapon_rect.bottom - weapon_rect.top,
			0, 0, weapon_cImage->GetWidth(), weapon_cImage->GetHeight());
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

	cImage->Destroy(); // 이미지 삭제
	

	if (press_m_l && weapon == 2) { // 마우스 좌 클릭 누르고 있을때. // bow

		weapon_cImage->Destroy(); // 무기 이미지 삭제

		if (mouse_p.x < rect.right) {
			cImage->Load(_bow_default_l[0]);
			weapon_cImage->Load(_bow_l[0]);
		}
		else if (mouse_p.x > rect.right) {
			cImage->Load(_bow_default_r[0]);
			weapon_cImage->Load(_bow_r[0]);
		}

		return;
	}

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

		if (attack_sword == 0) { // 1번 공격
			if (direction == PlayerStatus::LEFT)
				cImage->Load(_attack_sword_1_l[this->img_num]);
			else if(direction == PlayerStatus::RIGHT)
				cImage->Load(_attack_sword_1_r[this->img_num]);

			if (img_num == 4) {
				if (direction == PlayerStatus::LEFT)
					status = saveStatus;
				else if (direction == PlayerStatus::RIGHT)
					status = saveStatus;
			}
		}

		if (attack_sword == 1) { // 2번 공격
			if (direction == PlayerStatus::LEFT)
				cImage->Load(_attack_sword_2_l[this->img_num]);
			else if (direction == PlayerStatus::RIGHT)
				cImage->Load(_attack_sword_2_r[this->img_num]);

			if (img_num == 4) {
				if (direction == PlayerStatus::LEFT)
					status = saveStatus;
				else if (direction == PlayerStatus::RIGHT)
					status = saveStatus;
			}
		}

		if (attack_sword == 2) {
			if (direction == PlayerStatus::LEFT)
				cImage->Load(_attack_sword_3_l[this->img_num]);
			else if (direction == PlayerStatus::RIGHT)
				cImage->Load(_attack_sword_3_r[this->img_num]);

			if (img_num == 4) {
				if (direction == PlayerStatus::LEFT)
					status = saveStatus;
				else if (direction == PlayerStatus::RIGHT)
					status = saveStatus;
			}
		}

		if (attack_sword == 3) {
			if (direction == PlayerStatus::LEFT)
				cImage->Load(_attack_sword_4_l[this->img_num]);
			else if (direction == PlayerStatus::RIGHT)
				cImage->Load(_attack_sword_4_r[this->img_num]);

			if (img_num == 4) {
				if (direction == PlayerStatus::LEFT)
					status = saveStatus;
				else if (direction == PlayerStatus::RIGHT)
					status = saveStatus;
			}
		}

		if (attack_sword == 4) {
			if (direction == PlayerStatus::LEFT)
				cImage->Load(_attack_sword_5_l[this->img_num]);
			else if (direction == PlayerStatus::RIGHT)
				cImage->Load(_attack_sword_5_r[this->img_num]);

			if (img_num == 6) {
				if (direction == PlayerStatus::LEFT)
					status = saveStatus;
				else if (direction == PlayerStatus::RIGHT)
					status = saveStatus;
			}
		}

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
	case 49: // 1번 -> sword
		weapon = 1;
		break;
	case 50: // 2번 -> bow
		weapon = 2;
		break;
	case 51: // 3번 -> gun
		weapon = 3;
		break;
	case 65: //a
		status = PlayerStatus::LEFT;
		direction = PlayerStatus::LEFT;
		break;
	case 87: //w
		if (!isJumping && isOnGround) {
			isJumping = true;
			isOnGround = false; // 점프 시작 시 땅에 있지 않음으로 설정
			initialY = rect.top;
		}
		break;
	case 83: //s
		break;
	case 68: //d
		status = PlayerStatus::RIGHT;
		direction = PlayerStatus::RIGHT;
		break;
	case 32: //spacebar
	{
		img_num = 0;

		if (weapon != 1)
			return;
	
		if (status != PlayerStatus::ATTACK) //공격 아닐때만 저장 (연속으로 공격 방지)
			saveStatus = status;

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> attck_dis(0, 4);

		status = PlayerStatus::ATTACK;
		attack_sword = attck_dis(gen);

	
		break;
	}
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
			isJumping = false; // 중력때문에 일단 추가했는데, 충돌 검사할때 y축 충돌이면 false로 변경하게 코드 수정 필요
		}
	}
}

bool Player::checkPosition(const StageManager& stageManager, const int r, bool status) {
	if (status) {
		if (r > stageManager.viewRect.right / 2) {
			return true;
		}
	}
	else {
		if (r < stageManager.viewRect.right / 2) {
			return true;
		}
	}		
	return false;
}

void Player::move(StageManager& stageManager) {

	if (press_m_l && weapon != 1) { // 공격 모션 중이면 못 움직이게
		return;
	}

	RECT tempRect = rect; // 현재 위치를 임시로 저장

	switch (status)
	{
	case DEFAULT_R:
		break;
	case DEFAULT_L:
		break;
	case LEFT:

		if (stageManager.rect.left < 0) {
			OffsetRect(&rect, -speed, 0); // player 이동
			OffsetRect(&stageManager.rect, stageManager.camera_move_speed, 0); // 뒷배경 이동 <-
			
			for (int i = 0; i < stageManager.blocks_stage1.size(); ++i) { // 블럭이동
				OffsetRect(&stageManager.blocks_stage1[i].rect, 10, 0);
			}
			
			moveMonster(false);

			if (crash_check_block(rect, stageManager.blocks_stage1) || checkPosition(stageManager, rect.right, false)) {
				rect = tempRect; // 충돌하면 원래 위치로 되돌림
			}
		}
		else {
			OffsetRect(&rect, -speed, 0);
			if (crash_check_block(rect, stageManager.blocks_stage1)) {
				rect = tempRect; // 충돌하면 원래 위치로 되돌림
			}
		}

		break;
	case RIGHT:
		if (std::abs(stageManager.rect.right) + std::abs(stageManager.rect.left) < stageManager.game_rect.right) { //카메라 우측이동
			OffsetRect(&rect, speed, 0);
			OffsetRect(&stageManager.rect, -stageManager.camera_move_speed, 0); // 뒷배경 이동 ->

			for (int i = 0; i < stageManager.blocks_stage1.size(); ++i) {
				OffsetRect(&stageManager.blocks_stage1[i].rect, -10, 0);
			}

			moveMonster(true);

			if (crash_check_block(rect, stageManager.blocks_stage1) || checkPosition(stageManager, rect.left, true)) {
				rect = tempRect; // 충돌하면 원래 위치로 되돌림
			}
		}
		else {
			OffsetRect(&rect, speed, 0);
			if (crash_check_block(rect, stageManager.blocks_stage1)) {
				rect = tempRect; // 충돌하면 원래 위치로 되돌림
			}
		}
		break;
	case ATTACK:
		break;
	case DEFENSE:
		break;
	default:
		break;
	}

	if (isJumping) {
		jump();
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

bool Player::crash_check_block(const RECT& rect, const std::vector<Block>& blocks) { //
	RECT crossRect;
	for (auto& block : blocks) {
		if (IntersectRect(&crossRect, &rect, &block.rect)) {
			isOnGround = true; // 땅에 닿았을 때
			isJumping = false; // 점프 중이 아님
			return true;
		}
	}
	isOnGround = false; // 충돌이 없으면 공중에 있음
	return false;
}

void Player::TIMER(StageManager& stageManager) {

	static int timer_player = 0;
	timer_player++;
	
	if (timer_player % 2 == 0)
		setImg(img_num + 1);

	move(stageManager);

	// 중력 돌 충도 체크
	setSaveRect(rect);
	gravity.UpdatePhysics(rect);
	if (crash_check_block(rect, stageManager.blocks_stage1)) {
		rect = saveRect;
	}
}

void Player::moveMonster(bool status) {

	if (status) { // ->
		for (auto& slime : slimes) {
			OffsetRect(&slime.getRect(), -10, 0);
		}
	}
	else { // <-
		for (auto& slime : slimes) {
			OffsetRect(&slime.getRect(), 10, 0);
		}
	}
}
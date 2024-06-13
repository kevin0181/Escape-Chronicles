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
		if (press_m_l && weapon != 1) {
			Gdiplus::Graphics graphics(mDC);
			Gdiplus::Rect destRect(weapon_rect.left, weapon_rect.top, weapon_rect.right - weapon_rect.left, weapon_rect.bottom - weapon_rect.top);

			int bullets_size = bullets.size() - 1;

			Gdiplus::Rect destRect2(bullets[bullets_size].rect.left, bullets[bullets_size].rect.top, 
				bullets[bullets_size].rect.right - bullets[bullets_size].rect.left, bullets[bullets_size].rect.bottom - bullets[bullets_size].rect.top);

			// 렌더링 품질 설정
			graphics.SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBicubic);
			graphics.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);

			// 이미지 중심 계산
			Gdiplus::PointF center(static_cast<Gdiplus::REAL>(weapon_rect.left + (weapon_rect.right - weapon_rect.left) / 2),
				static_cast<Gdiplus::REAL>(weapon_rect.top + (weapon_rect.bottom - weapon_rect.top) / 2));

			// 마우스 위치 기준 각도 계산
			float dx = static_cast<float>(mouse_p.x) - center.X;
			float dy = static_cast<float>(mouse_p.y) - center.Y;
			float angle = std::atan2(dy, dx) * 180.0f / 3.14159265f; // 라디안을 도로 변환

			// 회전 변환 설정
			graphics.TranslateTransform(center.X, center.Y);
			graphics.RotateTransform(angle);
			graphics.TranslateTransform(-center.X, -center.Y);

			// 회전된 이미지 그리기
			graphics.DrawImage(weapon_img, destRect);

			if (bullets.size() != 0)
				graphics.DrawImage(bullets[bullets_size].img, destRect2);

		}

		if (bullets.size() != 0) {
			for (int i = 0; i < bullets.size(); ++i) {
				if (bullets[i].status) {
					Gdiplus::Graphics graphics(mDC);
					Gdiplus::Rect destRect(bullets[i].rect.left, bullets[i].rect.top, bullets[i].rect.right - bullets[i].rect.left, bullets[i].rect.bottom - bullets[i].rect.top);

					// 회전 변환 설정
					graphics.TranslateTransform(destRect.X + destRect.Width / 2, destRect.Y + destRect.Height / 2);
					graphics.RotateTransform(bullets[i].angle * 180.0f / 3.14159265f); // 라디안을 도로 변환
					graphics.TranslateTransform(-destRect.X - destRect.Width / 2, -destRect.Y - destRect.Height / 2);

					// 회전된 이미지 그리기
					graphics.DrawImage(bullets[i].img, destRect);
				}
			}
		}
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

		if (weapon_img) {
			delete weapon_img;
		}

		if (press_cnt >= 30) {
			weapon_img = new Gdiplus::Image(_bow_r[1]);
		}
		else {
			weapon_img = new Gdiplus::Image(_bow_r[0]);
		}

		if (mouse_p.x <= rect.right) { // left
			cImage->Load(_bow_default_l[0]);
			weapon_rect = rect;
			InflateRect(&weapon_rect, -10, -10);
			OffsetRect(&weapon_rect, -10, 0);
		}
		else if (mouse_p.x >= rect.right) { // right
			cImage->Load(_bow_default_r[0]);
			weapon_rect = rect;
			InflateRect(&weapon_rect, -10, -10);
			OffsetRect(&weapon_rect, 10, 0);
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

	weapon_rect = rect;
	saveRect = rect;

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

			if (checkPosition(stageManager, rect.right, false)) { //카메라 이동
				OffsetRect(&rect, speed, 0); // player 이동
			}

			
		}
		else {
			OffsetRect(&rect, -speed, 0);
			OffsetRect(&rect, check_side(), 0);
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

			if (checkPosition(stageManager, rect.left, true)) {
				OffsetRect(&rect, -speed, 0); // player 이동
			}

		}
		else {
			OffsetRect(&rect, speed, 0);
			OffsetRect(&rect, -check_side(), 0);
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

bool Player::check_bottom() { 
	if (rect.bottom >= stageManager.game_rect.bottom) {
		isOnGround = true; // 땅에 닿았을 때
		isJumping = false; // 점프 중이 아님
		return true;
	}
	isOnGround = false; // 충돌이 없으면 공중에 있음
	return false;
}

int Player::check_side() {
	if (rect.left <= stageManager.viewRect.left || rect.right >= stageManager.viewRect.right)
		return speed;
	return 0;
}

void Player::TIMER(StageManager& stageManager) {

	static int timer_player = 0;
	timer_player++;
	
	if (timer_player % 2 == 0)
		setImg(img_num + 1);

	move(stageManager);
	moveBullet();

	// 중력 돌 충도 체크
	setSaveRect(rect);
	gravity.UpdatePhysics(rect);
	if (check_bottom()) { // 바닥 충돌 체크
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

void Player::moveBullet() {
	for (auto& bullet : bullets) {
		bullet.rect.left += static_cast<LONG>(bullet.vx);
		bullet.rect.right += static_cast<LONG>(bullet.vx);
		bullet.rect.top += static_cast<LONG>(bullet.vy);
		bullet.rect.bottom += static_cast<LONG>(bullet.vy);
	}
}

void Player::shootArrow() {
	if (weapon == 2) { // 무기가 활일 때

		// 마우스 위치 기준 각도 계산
		Gdiplus::PointF center(static_cast<Gdiplus::REAL>(bullets[bullets.size() - 1].rect.left + (bullets[bullets.size() - 1].rect.right - bullets[bullets.size() - 1].rect.left) / 2),
			static_cast<Gdiplus::REAL>(bullets[bullets.size() - 1].rect.top + (bullets[bullets.size() - 1].rect.bottom - bullets[bullets.size() - 1].rect.top) / 2));

		float dx = static_cast<float>(mouse_p.x) - center.X;
		float dy = static_cast<float>(mouse_p.y) - center.Y;
		float angle = std::atan2(dy, dx);

		// 속도 설정 (속도 값을 조정하여 화살의 속도를 변경할 수 있습니다)
		float speed = 10.0f;
		float vx = speed * std::cos(angle);
		float vy = speed * std::sin(angle);

		// 화살을 벡터에 추가
		bullets[bullets.size() - 1].vx = vx;
		bullets[bullets.size() - 1].vy = vy;
		bullets[bullets.size() - 1].angle = angle;
	}
}
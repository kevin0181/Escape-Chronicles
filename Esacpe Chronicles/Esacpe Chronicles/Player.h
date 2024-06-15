#pragma once

#include <atlimage.h>
#include <memory>
#include <vector>
#include <cmath> // abs 함수가 포함된 헤더 파일
#include <random>
#include <gdiplus.h>

#pragma comment (lib, "gdiplus.lib")

using namespace Gdiplus;

#include "PlayerStatus.h"
#include "Gravity.h"
#include "Block.h"
#include "StageManager.h"
#include "Bullet.h"
#include "Monster.h"

class Monster;  // Monster 클래스를 전방 선언

class Player {
	/*bool left;
	bool right;
	bool jump;
	bool attack;
	bool defense;*/

	PlayerStatus saveStatus;
	

	bool isOnGround = true; //땅에 닿았는지 체크
	bool isJumping = false;
	int jumpHeight = 200;
	int jumpSpeed = 30;
	int currentJumpHeight;
	int initialY; // 점프 전 Y 좌표 저장
	
	int press_speed_cnt = 0;
	int low_speed = 5;
	int speed;
	RECT rect;
	RECT saveRect;

	int weapon; // 1 = sword, 2 = bow, 3 = gun
	RECT weapon_rect = { 0, 0, 1, 1 };
	RECT bullet_rect = { 0,0,1,1 };
	int attack_sword = 4; // sword 공격 모션

	int img_num;
	std::unique_ptr<CImage> cImage;

	Gdiplus::Image* weapon_img = nullptr;

	LPCTSTR _default_r[5] = {
		L"img/character/main/stay/stay_1.png",
		L"img/character/main/stay/stay_2.png",
		//L"img/character/main/stay/stay_3.png",
		L"img/character/main/stay/stay_4.png",
		L"img/character/main/stay/stay_5.png",
		L"img/character/main/stay/stay_6.png",
	};

	LPCTSTR _default_l[5] = {
		L"img/character/main/stay/stay_1_l.png",
		L"img/character/main/stay/stay_2_l.png",
		//L"img/character/main/stay/stay_3.png",
		L"img/character/main/stay/stay_4_l.png",
		L"img/character/main/stay/stay_5_l.png",
		L"img/character/main/stay/stay_6_l.png",
	};

	LPCTSTR _left[6] = {
		L"img/character/main/wark/wark_1_l.png",
		L"img/character/main/wark/wark_2_l.png",
		L"img/character/main/wark/wark_3_l.png",
		L"img/character/main/wark/wark_4_l.png",
		L"img/character/main/wark/wark_5_l.png",
		L"img/character/main/wark/wark_6_l.png",
	};

	LPCTSTR _right[6] = {
		L"img/character/main/wark/wark_1.png",
		L"img/character/main/wark/wark_2.png",
		L"img/character/main/wark/wark_3.png",
		L"img/character/main/wark/wark_4.png",
		L"img/character/main/wark/wark_5.png",
		L"img/character/main/wark/wark_6.png",
	};

	LPCTSTR _jump_r[6] = {
		L"img/character/main/jump/jump_1_v2.png",
		L"img/character/main/jump/jump_1_v2.png",
		L"img/character/main/jump/jump_1_v2.png",
		L"img/character/main/jump/jump_2_v2.png",
		L"img/character/main/jump/jump_2_v2.png",
		L"img/character/main/jump/jump_2_v2.png",
	};

	LPCTSTR _jump_l[6] = {
		L"img/character/main/jump/jump_1_v2_l.png",
		L"img/character/main/jump/jump_1_v2_l.png",
		L"img/character/main/jump/jump_1_v2_l.png",
		L"img/character/main/jump/jump_2_v2_l.png",
		L"img/character/main/jump/jump_2_v2_l.png",
		L"img/character/main/jump/jump_2_v2_l.png",
	};

	LPCTSTR _attack_sword_1_r[5] = {
		L"img/character/main/attack1(sword)/attack1.png",
		L"img/character/main/attack1(sword)/attack2.png",
		L"img/character/main/attack1(sword)/attack3.png",
		L"img/character/main/attack1(sword)/attack4.png",
		L"img/character/main/attack1(sword)/attack5.png",
	};

	LPCTSTR _attack_sword_1_l[5] = {
		L"img/character/main/attack1(sword)/attack1_l.png",
		L"img/character/main/attack1(sword)/attack2_l.png",
		L"img/character/main/attack1(sword)/attack3_l.png",
		L"img/character/main/attack1(sword)/attack4_l.png",
		L"img/character/main/attack1(sword)/attack5_l.png",
	};

	LPCTSTR _attack_sword_2_r[5] = {
		L"img/character/main/attack2(sword)/attack1.png",
		L"img/character/main/attack2(sword)/attack2.png",
		L"img/character/main/attack2(sword)/attack3.png",
		L"img/character/main/attack2(sword)/attack4.png",
		L"img/character/main/attack2(sword)/attack5.png",
	};

	LPCTSTR _attack_sword_2_l[5] = {
		L"img/character/main/attack2(sword)/attack1_l.png",
		L"img/character/main/attack2(sword)/attack2_l.png",
		L"img/character/main/attack2(sword)/attack3_l.png",
		L"img/character/main/attack2(sword)/attack4_l.png",
		L"img/character/main/attack2(sword)/attack5_l.png",
	};

	LPCTSTR _attack_sword_3_r[5] = {
		L"img/character/main/attack3(sword)/attack1.png",
		L"img/character/main/attack3(sword)/attack2.png",
		L"img/character/main/attack3(sword)/attack3.png",
		L"img/character/main/attack3(sword)/attack4.png",
		L"img/character/main/attack3(sword)/attack5.png",
	};

	LPCTSTR _attack_sword_3_l[5] = {
		L"img/character/main/attack3(sword)/attack1_l.png",
		L"img/character/main/attack3(sword)/attack2_l.png",
		L"img/character/main/attack3(sword)/attack3_l.png",
		L"img/character/main/attack3(sword)/attack4_l.png",
		L"img/character/main/attack3(sword)/attack5_l.png",
	};

	LPCTSTR _attack_sword_4_r[5] = {
		L"img/character/main/attack4(sword)/attack1.png",
		L"img/character/main/attack4(sword)/attack2.png",
		L"img/character/main/attack4(sword)/attack3.png",
		L"img/character/main/attack4(sword)/attack4.png",
		L"img/character/main/attack4(sword)/attack5.png",
	};

	LPCTSTR _attack_sword_4_l[5] = {
		L"img/character/main/attack4(sword)/attack1_l.png",
		L"img/character/main/attack4(sword)/attack2_l.png",
		L"img/character/main/attack4(sword)/attack3_l.png",
		L"img/character/main/attack4(sword)/attack4_l.png",
		L"img/character/main/attack4(sword)/attack5_l.png",
	};

	LPCTSTR _attack_sword_5_r[7] = {
		L"img/character/main/attack5(sword)/attack1.png",
		L"img/character/main/attack5(sword)/attack2.png",
		L"img/character/main/attack5(sword)/attack3.png",
		L"img/character/main/attack5(sword)/attack4.png",
		L"img/character/main/attack5(sword)/attack5.png",
		L"img/character/main/attack5(sword)/attack6.png",
		L"img/character/main/attack5(sword)/attack7.png",
	};

	LPCTSTR _attack_sword_5_l[7] = {
		L"img/character/main/attack5(sword)/attack1_l.png",
		L"img/character/main/attack5(sword)/attack2_l.png",
		L"img/character/main/attack5(sword)/attack3_l.png",
		L"img/character/main/attack5(sword)/attack4_l.png",
		L"img/character/main/attack5(sword)/attack5_l.png",
		L"img/character/main/attack5(sword)/attack6_l.png",
		L"img/character/main/attack5(sword)/attack7_l.png",
	};

	LPCTSTR _hit_r[4] = {
		L"img/character/main/hit/hit1.png",
		L"img/character/main/hit/hit2.png",
		L"img/character/main/hit/hit3.png",
		L"img/character/main/hit/hit4.png",
	};

	LPCTSTR _hit_l[4] = {
		L"img/character/main/hit/hit1_l.png",
		L"img/character/main/hit/hit2_l.png",
		L"img/character/main/hit/hit3_l.png",
		L"img/character/main/hit/hit4_l.png",
	};

	LPCTSTR _Death_l[7] = {
		L"img/character/main/death/death1_l.png",
		L"img/character/main/death/death2_l.png",
		L"img/character/main/death/death3_l.png",
		L"img/character/main/death/death4_l.png",
		L"img/character/main/death/death5_l.png",
		L"img/character/main/death/death6_l.png",
		L"img/character/main/death/death7_l.png",
	};

	LPCTSTR _Death_r[7] = {
		L"img/character/main/death/death1.png",
		L"img/character/main/death/death2.png",
		L"img/character/main/death/death3.png",
		L"img/character/main/death/death4.png",
		L"img/character/main/death/death5.png",
		L"img/character/main/death/death6.png",
		L"img/character/main/death/death7.png",
	};

	LPCTSTR _bow_default_r[1] = {
		L"img/character/main/weapon/default.png"
	};

	LPCTSTR _bow_default_l[1] = {
		L"img/character/main/weapon/default_l.png"
	};

	LPCTSTR _bow_r[2] = {
		L"img/character/main/weapon/bow/bow1_v2.png",
		L"img/character/main/weapon/bow/bow2_v2.png"
	};

	LPCTSTR _bow_l[2] = {
		L"img/character/main/weapon/bow/bow1_l.png",
		L"img/character/main/weapon/bow/bow2_l.png"
	};

	LPCTSTR _gun_r[1] = {
		L"img/character/main/weapon/gun/gun1.png",
	};

	LPCTSTR _gun_l[1] = {
		L"img/character/main/weapon/gun/gun1_v2.png",
	};

public:
	PlayerStatus status;
	PlayerStatus direction = PlayerStatus::RIGHT;

	int player_i = 0;
	Gravity gravity;
	int power = 10;
	int default_power = 10;
	int hp = 200;
	bool press_m_l = false;
	int press_cnt = 0;
	POINT mouse_p;

	bool getDamage = false;

	std::vector<Bullet> bullets;

	Player() : cImage(std::make_unique<CImage>()), status(PlayerStatus::DEFAULT_R), speed(10), img_num(0), weapon(1) {
		rect = { 0,0,90,120 };
		//OffsetRect(&rect, 0, 770);
		//OffsetRect(&rect, 100, 500);
		HRESULT hr = cImage->Load(_default_r[0]);

		if (FAILED(hr)) {
			MessageBox(NULL, L"캐릭터 이미지 로드 실패", L"오류", MB_OK);
		}

		Gdiplus::GdiplusStartupInput gdiplusStartupInput;
		ULONG_PTR gdiplusToken;
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

		weapon_img = new Gdiplus::Image(_bow_r[0]);
		if (!weapon_img) {
			MessageBox(NULL, L"무기 이미지 로드 실패", L"Error", MB_OK | MB_ICONERROR);
		}

	};

	void setKeyDown(WPARAM wParam);
	void setKeyUp(WPARAM wParam);

	void print(HDC& mDC) const;
	int getCimageSize() const; // 현재 해당 이미지의 크기를 가져오기

	void TIMER(StageManager& stageManager);

	void setImg(int img_num); // 캐릭터 이미지 할당
	void move(StageManager& stageManager);
	void jump();

	void setRECT(RECT rect);
	RECT& getRECT();
	void setSaveRect(RECT rect);
	RECT& getSaveRect();

	int getImgNum() const;

	bool check_bottom();
	int check_side();
	bool checkPosition(const StageManager& stageManager, const int rect,const bool status);
	void moveMonster(bool status);
	void shootArrow();
	void moveBullet();
	void collisionMonster(Monster* monster);
	bool checkBlock(const StageManager& stageManager);

	int getWeapon() const {
		return weapon;
	}
};
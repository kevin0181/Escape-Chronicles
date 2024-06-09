#pragma once

#include <atlimage.h>
#include <memory>
#include <vector>

#include "PlayerStatus.h"
#include "Gravity.h"
#include "Block.h"
#include "StageManager.h"

class Player {
	/*bool left;
	bool right;
	bool jump;
	bool attack;
	bool defense;*/

	PlayerStatus status;

	bool isJumping = false;
	int jumpHeight = 150;
	int jumpSpeed = 30;
	int currentJumpHeight;
	int initialY; // ���� �� Y ��ǥ ����

	int speed;
	RECT rect;
	RECT saveRect;

	int weapon; // 0 = sword, 1 = bow, 2 = gun

	int img_num;
	std::unique_ptr<CImage> cImage;

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

public:

	int player_i = 0;
	Gravity gravity;

	Player() :cImage(std::make_unique<CImage>()), status(PlayerStatus::DEFAULT_R), speed(10), img_num(0), weapon(0) {
		rect = { 0,0,90,120 };
		//OffsetRect(&rect, 0, 770);
		OffsetRect(&rect, 0, 100);
		HRESULT hr = cImage->Load(_default_r[0]);
		if (FAILED(hr)) {
			MessageBox(NULL, L"��� �̹��� �ε� ����", L"����", MB_OK);
		}
	};

	void setKeyDown(WPARAM wParam);
	void setKeyUp(WPARAM wParam);

	void print(HDC& mDC) const;
	int getCimageSize() const; // ���� �ش� �̹����� ũ�⸦ ��������

	void TIMER(StageManager& stageManager);

	void setImg(int img_num); // ĳ���� �̹��� �Ҵ�
	void move(StageManager& stageManager);
	void jump();

	void setRECT(RECT rect);
	RECT& getRECT();
	void setSaveRect(RECT rect);
	RECT& getSaveRect();

	int getImgNum() const;

	bool crash_check_block(RECT& rect, std::vector<Block>& blocks);
	bool checkPosition(const StageManager& stageManager, const int rect,const bool status);
};
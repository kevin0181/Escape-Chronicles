#pragma once

#include <string>
#include <iostream>
#include <ctime>
#include <cstdlib>

#include "Player.h"
#include "StageManager.h"
#include "Collision.h"
#include "Gravity.h"

class Player;  // 전방 선언: 필요 시 Player를 사용하기 위함

enum MonsterStatus {
	MOVE_,
	ATTACK_,
	DIE_
};

class Monster {
public:
	CImage attacked_img;
	bool attacked = false;
	LPCTSTR attacked_img_path = L"img/Ui/attacked_v2.png";
	int attacksize;


	Monster() {
		HRESULT hResult = attacked_img.Load(attacked_img_path);
	};
	virtual void insert() = 0;
	virtual void print(const HDC& mDC) = 0;
	virtual void move(const StageManager& stageManager) = 0;
	virtual RECT& getRect() = 0;
	virtual MonsterStatus getStatus() const = 0;
	virtual void Collisionplayer(const Player& p) = 0;
	virtual void MonsterPlayerCollision(Player& p) = 0;
	void printAttack(const HDC& mDC, const RECT& rect) {
		HFONT hFont = CreateFont(
			-36,                      // 폰트 높이 (2배 크기)
			18,                       // 폰트 너비 (2배 크기)
			0,                        // 텍스트 기울기 각도
			0,                        // 텍스트 기울임 여부
			FW_NORMAL,                // 폰트 두께
			FALSE,                    // 기울임 폰트 여부
			FALSE,                    // 밑줄 여부
			FALSE,                    // 취소선 여부
			DEFAULT_CHARSET,          // 문자 집합
			OUT_DEFAULT_PRECIS,       // 출력 정밀도
			CLIP_DEFAULT_PRECIS,      // 클리핑 정밀도
			DEFAULT_QUALITY,          // 출력 품질
			DEFAULT_PITCH | FF_DONTCARE, // 피치 및 패밀리
			L"Arial"                  // 폰트 이름
		);

		HFONT hOldFont = (HFONT)SelectObject(mDC, hFont); // 폰트 선택

		SetBkMode(mDC, TRANSPARENT);
		SetTextColor(mDC, RGB(255, 0, 0));

		wchar_t text[20]; // 충분한 길이의 버퍼를 설정해야 합니다.
		swprintf(text, 20, L"-%d,", attacksize); // 형식화된 문자열 생성
		// 텍스트 출력
		TextOut(mDC, rect.left + 10, rect.top - 46, text, lstrlen(text));

		SelectObject(mDC, hOldFont);
	}
};



#pragma once

#include <string>
#include <iostream>
#include <ctime>
#include <cstdlib>

#include "Player.h"
#include "StageManager.h"
#include "Collision.h"
#include "Gravity.h"

class Player;  // ���� ����: �ʿ� �� Player�� ����ϱ� ����

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
			-36,                      // ��Ʈ ���� (2�� ũ��)
			18,                       // ��Ʈ �ʺ� (2�� ũ��)
			0,                        // �ؽ�Ʈ ���� ����
			0,                        // �ؽ�Ʈ ����� ����
			FW_NORMAL,                // ��Ʈ �β�
			FALSE,                    // ����� ��Ʈ ����
			FALSE,                    // ���� ����
			FALSE,                    // ��Ҽ� ����
			DEFAULT_CHARSET,          // ���� ����
			OUT_DEFAULT_PRECIS,       // ��� ���е�
			CLIP_DEFAULT_PRECIS,      // Ŭ���� ���е�
			DEFAULT_QUALITY,          // ��� ǰ��
			DEFAULT_PITCH | FF_DONTCARE, // ��ġ �� �йи�
			L"Arial"                  // ��Ʈ �̸�
		);

		HFONT hOldFont = (HFONT)SelectObject(mDC, hFont); // ��Ʈ ����

		SetBkMode(mDC, TRANSPARENT);
		SetTextColor(mDC, RGB(255, 0, 0));

		wchar_t text[20]; // ����� ������ ���۸� �����ؾ� �մϴ�.
		swprintf(text, 20, L"-%d,", attacksize); // ����ȭ�� ���ڿ� ����
		// �ؽ�Ʈ ���
		TextOut(mDC, rect.left + 10, rect.top - 46, text, lstrlen(text));

		SelectObject(mDC, hOldFont);
	}
};



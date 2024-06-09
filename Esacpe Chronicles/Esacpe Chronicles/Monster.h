#pragma once
#include <string>
#include < atlimage.h >
#include <windows.h>

#include "Player.h"
#include "StageManager.h"

class Monster {
public:
	virtual void insert() = 0;
	virtual void print(HDC& mDC) = 0;
	virtual void move(StageManager& stageManager, RECT Rect) = 0;
	virtual void attack() = 0;
	virtual RECT& getRect() = 0;
};

enum MonsterStatus {
	MOVE_,
	ATTACK_,
	DIE_
};
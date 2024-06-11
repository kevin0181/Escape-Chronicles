#pragma once
#include <string>
#include <iostream>
#include <ctime>
#include <cstdlib>

#include "Player.h"
#include "StageManager.h"
#include "Collision.h"
#include "Gravity.h"

class Monster {
public:
	virtual void insert() = 0;
	virtual void print(HDC& mDC) = 0;
	virtual void move(StageManager& stageManager) = 0;
	virtual void attack() = 0;
	virtual RECT& getRect() = 0;
};

enum MonsterStatus {
	MOVE_,
	ATTACK_,
	DIE_
};


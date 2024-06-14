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
	virtual void insert() = 0;
	virtual void print(const HDC& mDC) = 0;
	virtual void move(const StageManager& stageManager) = 0;
	virtual RECT& getRect() = 0;
	virtual MonsterStatus getStatus() const = 0;
	virtual void Collisionplayer(const Player& p) = 0;
	virtual void MonsterPlayerCollision(Player& p) = 0;
};



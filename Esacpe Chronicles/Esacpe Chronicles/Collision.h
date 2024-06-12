#pragma once
#include <atlimage.h>
#include <vector>

#include "Player.h"
#include "Monster.h"
#include "Block.h"
#include "StageManager.h"
// ���Ϳ� �÷��̾��� �浹�� ó���ϴ� ���.

//bool CheckBlockCollision(const RECT& rect, const std::vector<Block>& blocks); // ȭ��,��ϰ� �浹Ȯ�� (ȭ�� rect, ��� rect, �񱳴�� �̵�����,�񱳴�� rect)



void CheckClientRect(const StageManager& stagmeManager,const RECT rect, bool& left);


int CheckBlockCollision(const RECT& rect, const StageManager& stageManager);

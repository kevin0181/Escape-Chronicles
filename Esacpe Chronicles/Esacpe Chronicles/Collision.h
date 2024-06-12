#pragma once
#include <atlimage.h>
#include <vector>

#include "Player.h"
#include "Monster.h"
#include "Block.h"
#include "StageManager.h"
// ���Ϳ� �÷��̾��� �浹�� ó���ϴ� ���.

bool CheckBlockCollision(RECT& rect, std::vector<Block>& blocks); // ȭ��,��ϰ� �浹Ȯ�� (ȭ�� rect, ��� rect, �񱳴�� �̵�����,�񱳴�� rect)

void CheckClientRect(const StageManager& stagmeManager, RECT rect, bool& left);


#pragma once
#include <atlimage.h>
#include <vector>

#include "Player.h"
#include "Monster.h"
#include "Block.h"
#include "StageManager.h"
// 몬스터와 플레이어의 충돌을 처리하는 헤더.

bool CheckBlockCollision(RECT& rect, std::vector<Block>& blocks); // 화면,블록과 충돌확인 (화면 rect, 블록 rect, 비교대상 이동방향,비교대상 rect)

void CheckClientRect(const StageManager& stagmeManager, RECT rect, bool& left);


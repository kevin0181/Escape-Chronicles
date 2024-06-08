#pragma once
#include <atlimage.h>

// 몬스터와 플레이어의 충돌을 처리하는 헤더.
bool CheckCollision(RECT rect1, RECT rect2); // 몬스터와 충돌확인
// void Collision(Player p, Monster m);

bool CheckBlockCollision(RECT rect, RECT rect1, bool left, RECT rect2); // 화면,블록과 충돌확인 (화면 rect, 블록 rect, 비교대상 이동방향,비교대상 rect)
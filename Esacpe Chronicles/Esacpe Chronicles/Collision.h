#pragma once
#include <atlimage.h>
#include "Block.h"
#include <vector>

// ���Ϳ� �÷��̾��� �浹�� ó���ϴ� ���.
bool CheckCollision(RECT rect1, RECT rect2); // ���Ϳ� �浹Ȯ��
// void Collision(Player p, Monster m);

bool CheckBlockCollision(RECT& rect, std::vector<Block>& blocks); // ȭ��,��ϰ� �浹Ȯ�� (ȭ�� rect, ��� rect, �񱳴�� �̵�����,�񱳴�� rect)

void CheckClientRect(RECT clientrect, RECT rect,bool& left);
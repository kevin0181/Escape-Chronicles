#pragma once
#include <atlimage.h>

// ���Ϳ� �÷��̾��� �浹�� ó���ϴ� ���.
bool CheckCollision(RECT rect1, RECT rect2); // ���Ϳ� �浹Ȯ��
// void Collision(Player p, Monster m);

bool CheckBlockCollision(RECT rect, RECT rect1, bool left, RECT rect2); // ȭ��,��ϰ� �浹Ȯ�� (ȭ�� rect, ��� rect, �񱳴�� �̵�����,�񱳴�� rect)
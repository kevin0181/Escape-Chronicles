#include <iostream>
#include <atlimage.h>
#include "Monster.h"
#include "Zombie.h"
using namespace std;

//srand(time(nullptr));

Zombie::Zombie() : Monster() {
	hp = 500; // 나중에 확정되면 바꾸기
	num = rand() % 3;
	imagenum = 0;
	rect = { 500, 300, 700, 500 };
	left = true;
	bool_attack = false;
}

RECT Zombie::getRect() const {
	return rect;
}
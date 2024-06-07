#include <atlimage.h>
#include "Monster.h"
#include "Player.h"

bool CheckCollision(RECT rect1, RECT rect2) {
	if ((rect1.left < rect2.right) && (rect1.top < rect2.bottom) && (rect1.right > rect2.left) &&
		(rect1.bottom > rect2.top)) return true;
	else return false;
}



bool CheckBlockCollision(RECT rect, RECT rect1, bool left, RECT rect2) {
	if ((rect1.left < rect2.right) && (rect1.top < rect2.bottom) && (rect1.right > rect2.left) &&
		(rect1.bottom > rect2.top)) return true;
	else if ((left && rect2.left <= rect.left) || (!left && rect2.right >= rect.right))
		return true;
	else return false;
}
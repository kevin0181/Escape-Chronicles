#include "collision.h"

bool CheckCollision(RECT rect1, RECT rect2) {
	if ((rect1.left < rect2.right) && (rect1.top < rect2.bottom) && (rect1.right > rect2.left) &&
		(rect1.bottom > rect2.top)) return true;
	else return false;
}



bool CheckBlockCollision(RECT& rect,  std::vector<Block>& blocks) { //
	RECT crossRect;
	for (auto& block : blocks) {
		if (IntersectRect(&crossRect, &rect, &block.rect)) {
			return true;
		}
	}
	return false;
}

bool CheckClientRect(RECT clientrect, RECT rect) {
	if (rect.left <= clientrect.left || rect.right >= clientrect.right)
		return true;
	else return false;
}
#include "collision.h"

bool CheckBlockCollision(RECT& rect, std::vector<Block>& blocks) { //
	RECT crossRect;
	for (auto& block : blocks) {
		if (IntersectRect(&crossRect, &rect, &block.rect)) {
			return true;
		}
	}
	return false;
}

void CheckClientRect(const StageManager& stageManager, RECT rect, bool& left) {
	if (rect.left <= stageManager.rect.left)
	{
		left = false;
		return;
	}
	if (rect.right >= stageManager.game_rect.right + stageManager.rect.left)
	{
		left = true;
		return;
	}
}


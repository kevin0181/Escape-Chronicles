#include "Ui.h"

void Ui::print(const HDC& mDC, const Player& player) {
	if (!Hp_img.IsNull()) {
		HBRUSH hBrush = CreateSolidBrush(Red);
		HBRUSH oldBrush = (HBRUSH)SelectObject(mDC, hBrush);

		Rectangle(mDC, 53, 53, 50 + (354 * (max(player.hp, 0)) / 200), 92);

		SelectObject(mDC, oldBrush);
		DeleteObject(hBrush);

		Hp_img.Draw(mDC, 50, 50, 360, 45, 0, 0, Hp_img.GetWidth(), Hp_img.GetHeight());
	}
}

void Ui::escprint(const HDC& mDC, const StageManager& stagemanager) {
	if (!Esc_img.IsNull()) {

		Esc_img.Draw(mDC, (stagemanager.viewRect.left + stagemanager.viewRect.right) / 2 - 500, (stagemanager.viewRect.top + stagemanager.viewRect.bottom) / 2 - 342, 1000, 684, 0, 0, Esc_img.GetWidth(), Esc_img.GetHeight());
	}
}
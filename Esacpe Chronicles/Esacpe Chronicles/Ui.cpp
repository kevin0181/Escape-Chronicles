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

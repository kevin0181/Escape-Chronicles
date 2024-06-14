#include "Ui.h"

void Ui::print(const HDC& mDC) {
	if (!Hp_img.IsNull()) {
		Hp_img.Draw(mDC, 50, 50, 120, 15, 0, 0, Hp_img.GetWidth(), Hp_img.GetHeight());
	}
}

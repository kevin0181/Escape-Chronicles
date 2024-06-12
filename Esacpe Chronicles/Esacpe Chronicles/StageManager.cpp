#include "StageManager.h"
#include <stdexcept>

#define BLOCK_SIZE 70

void StageManager::setCurrent_stage(STAGE stage) {
	current_stage = stage;
}

void StageManager::setBackground_img(const LPCTSTR path) {
	destroyImg();
	background_img.Load(path);
}

STAGE StageManager::getCurrent_stage() const {
	return current_stage;
}

void StageManager::DrawBackground_img(HDC& mDC, const int& w) {

	if (!background_img.IsNull()) {

		background_img.Draw(mDC, rect.left, rect.top, (rect.right - rect.left) * w, rect.bottom - rect.top, 0, 0, background_img.GetWidth(), background_img.GetHeight()); //이미지 전체 화면

		if (current_stage == STAGE::STAGE_1) {
			for (int i = 0; i < blocks_stage1.size(); ++i) { //블럭 그리기
				blocks_stage1[i].print(mDC, i, 1);
			}
		}
	}
	else {
		throw std::runtime_error("Background image is not loaded.");
	}
}

void StageManager::setMainBackGround(HDC& mDC, const RECT& rect) {
	if (!startBtnImg.IsNull()) {
		startBtnImg.Draw(mDC, startBtn.left, startBtn.top, 100, 100, 0, 0, startBtnImg.GetWidth(), startBtnImg.GetHeight());
	}
	else {
		throw std::runtime_error("Background image is not loaded.");
	}
}

void StageManager::destroyImg() {
	// 배경 이미지가 로드되어 있으면 파괴
	if (!background_img.IsNull()) {
		background_img.Destroy();
	}
}


void StageManager::setBlock(const int& h, const LPCTSTR& path_block, const float& size) { // stageblock 바닥 1번생성!

	blocks_stage1.clear();

	for (int i = 0; i < (game_rect.right / BLOCK_SIZE) + 1; ++i) {
		for (int j = 0; j < h; ++j) {
			Block block;
			block.cImage->Load(path_block);
			block.rect = { i * BLOCK_SIZE, j * BLOCK_SIZE, (i + 1) * BLOCK_SIZE, (j + 1) * BLOCK_SIZE };
			OffsetRect(&block.rect, 0, this->game_rect.bottom * size);
			blocks_stage1.push_back(std::move(block));
		}
	}

	RECT rect_side_blocks[2] = { //옆 벽면
		{-70,0,0,game_rect.bottom},
		{game_rect.right,0,game_rect.right + 70,game_rect.bottom}
	};

	for (int i = 0; i < (game_rect.right / BLOCK_SIZE) + 1; ++i) {
		if (i < 5) {
			for (int j = 0; j < h; ++j) {
				Block block;
				block.cImage->Load(path_block);
				block.rect = { i * BLOCK_SIZE, j * BLOCK_SIZE, (i + 1) * BLOCK_SIZE, (j + 1) * BLOCK_SIZE };
				OffsetRect(&block.rect, 0, this->game_rect.bottom / 10*(10-i));
				blocks_stage1.push_back(std::move(block));
			}
		}
		else if (i%7==1|| i % 3 == 1) {
			for (int j = 0; j < h; ++j) {
				Block block;
				block.cImage->Load(path_block);
				block.rect = { i * BLOCK_SIZE, j * BLOCK_SIZE, (i + 1) * BLOCK_SIZE, (j + 1) * BLOCK_SIZE };
				OffsetRect(&block.rect, 0, this->game_rect.bottom / 2);
				blocks_stage1.push_back(std::move(block));
			}
		}



		/*if (j == -5 && i < 4 && i>0) {
			blocks_stage1[i].print(mDC, i, -(i - 1) * 2);
		}
		else if (j == -5 && i < 24 && i>20) {
			blocks_stage1[i].print(mDC, i, -(i - 21) * 2);
		}
		else if (j == -5 && (i == 6 || i == 7 || i == 10 || i == 15 || i == 17 || i == 18)) {}
		else if (j != -5 || i > 4) {
			blocks_stage1[i].print(mDC, i, j);
		}*/

	}


	for (int i = 0; i < 2; i++) {
		Block block;
		block.cImage->Load(path_block);
		block.rect = rect_side_blocks[i];
		blocks_stage1.push_back(std::move(block));
	}

}

void StageManager::setLMBtnDown(LPARAM lParam) {
	POINT mP;
	mP.x = LOWORD(lParam);
	mP.y = HIWORD(lParam);

	if (PtInRect(&startBtn, mP)) {
		setBlock(1, Block::path_stage1, 0.98); //block create
		current_stage = STAGE::STAGE_1;
		setBackground_img(background_img_path[0]);
	}
}

void StageManager::setKeyDown(WPARAM wParam) {
	switch (wParam)
	{
	case VK_RETURN:
		intro_cnt++;
		if (intro_cnt >= 5) {
			current_stage = STAGE::MAIN;
			setBackground_img(main_img_path[2]);
			break;
		}
		setBackground_img(this->intro_img_path[intro_cnt]);
		break;
	default:
		break;
	}
}
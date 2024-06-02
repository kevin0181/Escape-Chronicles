#pragma once

#include<atlimage.h>
#include<vector>

#include"Stage.h"
#include"Block.h"

class StageManager {
private:
	Stage current_stage;
	CImage background_img;
	RECT rect; // 현재 이미지의 전체 크기 (스테이지마다 이미지 크기가 다르기 때문에)
	std::vector<Block> blocks_stage1;

public:

	LPCTSTR img_path[3] = {
		L"img/background/stage1_background_img.png", // background stage 1
		L"img/background/stage2_background_img.png",
		L"img/background/stage3_background_img.png"
	};

	StageManager() :current_stage(Stage::MAIN), rect({ 0,0,0,0 }) {
		Block block;
		for (int i = 0; i < 20; ++i) {
			blocks_stage1.push_back(std::move(block));
		}
	};

	void setCurrent_stage(Stage stage); // 스테이지 변경
	void setBackground_img(LPCTSTR path); // 스테이지에 따른 뒷 배경 변경
	void DrawBackground_img(HDC& mDC, RECT rect,int w); // 뒷 배경 그리기
	void destroyImg(); // 이미지 삭제 (이미지 변경 시, 필수)
};
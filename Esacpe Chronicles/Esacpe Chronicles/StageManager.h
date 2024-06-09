#pragma once

#include<atlimage.h>
#include<vector>

#include"Stage.h"
#include"Block.h"

class StageManager {
private:
	STAGE current_stage;
	CImage background_img;
public:
	RECT rect; // 현재 이미지의 전체 크기 (스테이지마다 이미지 크기가 다르기 때문에)
	int camera_move_speed = 15;

	std::vector<Block> blocks_stage1;
	int intro_cnt = 1;
	RECT game_rect; // 게임 진행하는 화면 크기

	CImage startBtnImg;
	RECT startBtn;

	LPCTSTR main_img_path[3] = {
		L"img/main/start button.png", //start button
		L"img/main/extraction.png", //background
		L"img/main/Escape_Chronicles_logo.png"
	};

	LPCTSTR intro_img_path[5] = {
		L"img/intro_img/1.png", // 
		L"img/intro_img/1.png", //
		L"img/intro_img/3.png", // 
		L"img/intro_img/4.png",
		L"img/intro_img/5.png",
	};

	LPCTSTR background_img_path[3] = {
		L"img/background/stage1_background_img.png", // background stage 1
		L"img/background/stage2_background_img.png", // background stage 2
		L"img/background/stage3_background_img.png" // background stage 3
	};

	/*
		화면 전체 크기를 가져와서 화면에 맞춰 블록의 크기를 정해줌
	*/
	StageManager() :current_stage(STAGE::INTRO), rect({ 0,0,0,0 }) {
		startBtnImg.Load(main_img_path[0]);
	};
	
	void setBlock(const int& h, const LPCTSTR& path_block, const float& size);
	void setCurrent_stage(STAGE stage); // 스테이지 변경
	STAGE getCurrent_stage() const;
	void setBackground_img(const LPCTSTR path); // 스테이지에 따른 뒷 배경 변경
	void DrawBackground_img(HDC& mDC, const int& w); // 뒷 배경 그리기
	void destroyImg(); // 이미지 삭제 (이미지 변경 시, 필수)
	void setMainBackGround(HDC& mDC, const RECT& rect); //main 화면
	
	void setLMBtnDown(LPARAM lParam);
	void setKeyDown(WPARAM wParam);

	void updateStageRect(int offsetX); // 카메라이동
};
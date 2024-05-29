#pragma once
#include<atlimage.h>
#include"Stage.h"

class StageManager {
private:
	Stage current_stage;
	CImage background_img;
public:

	LPCTSTR img_path[3] = {
		L"img/background/stage1_background_img.png", // background stage 1
		L"",
		L""
	};

	StageManager() :current_stage(Stage::MAIN) {};

	void setCurrent_stage(Stage stage); // 스테이지 변경
	void setBackground_img(LPCTSTR path); // 스테이지에 따른 뒷 배경 변경
	void DrawBackground_img(HDC& mDC, RECT rect); // 뒷 배경 그리기
	void destroyImg(); // 이미지 삭제 (이미지 변경 시, 필수)
};
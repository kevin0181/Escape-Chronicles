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
		L"img/background/stage2_background_img.png",
		L"img/background/stage3_background_img.png"
	};

	StageManager() :current_stage(Stage::MAIN) {};

	void setCurrent_stage(Stage stage); // �������� ����
	void setBackground_img(LPCTSTR path); // ���������� ���� �� ��� ����
	void DrawBackground_img(HDC& mDC, RECT rect,int w); // �� ��� �׸���
	void destroyImg(); // �̹��� ���� (�̹��� ���� ��, �ʼ�)
};
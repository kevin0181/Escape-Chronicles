#pragma once
#include<atlimage.h>
#include"Stage.h"

class StageManager {
private:
	Stage current_stage;
	CImage background_img;
public:

	LPCTSTR img_path[3] = {
		L"img/background/darkened_pixel_art_image.png", // background stage 1
		L"",
		L""
	};

	StageManager() :current_stage(Stage::MAIN) {};

	void setCurrent_stage(Stage stage); // �������� ����
	void setBackground_img(LPCTSTR path); // ���������� ���� �� ��� ����
	void DrawBackground_img(HDC& mDC, RECT rect); // �� ��� �׸���
	void destroyImg(); // �̹��� ���� (�̹��� ���� ��, �ʼ�)
};
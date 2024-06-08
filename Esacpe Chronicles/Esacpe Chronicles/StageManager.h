#pragma once

#include<atlimage.h>
#include<vector>

#include"Stage.h"
#include"Block.h"

class StageManager {
private:
	STAGE current_stage;
	CImage background_img;
	RECT rect; // ���� �̹����� ��ü ũ�� (������������ �̹��� ũ�Ⱑ �ٸ��� ������)
	
public:
	std::vector<Block> blocks_stage1;
	int intro_cnt = 1;

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
		ȭ�� ��ü ũ�⸦ �����ͼ� ȭ�鿡 ���� ����� ũ�⸦ ������
	*/
	StageManager() :current_stage(STAGE::INTRO), rect({ 0,0,0,0 }) {
	
	};
	
	void setBlock(int h, LPCTSTR path_block, float size, int detail_size);
	void setCurrent_stage(STAGE stage); // �������� ����
	STAGE getCurrent_stage() const;
	void setBackground_img(LPCTSTR path); // ���������� ���� �� ��� ����
	void DrawBackground_img(HDC& mDC, RECT rect,int w); // �� ��� �׸���
	void destroyImg(); // �̹��� ���� (�̹��� ���� ��, �ʼ�)

	void setKeyDown(WPARAM wParam);
};
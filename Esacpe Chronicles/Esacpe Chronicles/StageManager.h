#pragma once

#include<atlimage.h>
#include<vector>

#include"Stage.h"
#include"Block.h"

class StageManager {
private:
public:
	STAGE current_stage;
	CImage background_img;
	RECT viewRect; //����� ȭ��ũ��
	RECT rect; // ���� ���̴� �̹����� ũ��
	RECT potal_rect;
	int camera_move_speed = 10;

	std::vector<Block> block_stage1_map; //����
	 
	std::vector<Block> blocks_stage1; //�ٴ�
	int intro_cnt = 1;
	RECT game_rect; // ���� �̹��� �޹�� ��ü ũ��

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
		L"img/background/stage1_background_img_v2.png", // background stage 1
		L"img/background/stage2_background_img.png", // background stage 2
		L"img/background/stage3_background_img.png" // background stage 3
	};

	/*
		ȭ�� ��ü ũ�⸦ �����ͼ� ȭ�鿡 ���� ����� ũ�⸦ ������
	*/
	StageManager() :current_stage(STAGE::INTRO), rect({ 0,0,0,0 }) {
		startBtnImg.Load(main_img_path[0]);
	};
	
	void setBlock(const int& h, const COLORREF color);
	void setCurrent_stage(STAGE stage); // �������� ����
	STAGE getCurrent_stage() const;
	void setBackground_img(const LPCTSTR path); // ���������� ���� �� ��� ����
	void DrawBackground_img(HDC& mDC, const int& w); // �� ��� �׸���
	void destroyImg(); // �̹��� ���� (�̹��� ���� ��, �ʼ�)
	void setMainBackGround(HDC& mDC, const RECT& rect); //main ȭ��
	
	void setLMBtnDown(LPARAM lParam);
	void setKeyDown(WPARAM wParam);
};
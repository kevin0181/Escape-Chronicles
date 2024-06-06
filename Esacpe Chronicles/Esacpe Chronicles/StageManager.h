#pragma once

#include<atlimage.h>
#include<vector>

#include"Stage.h"
#include"Block.h"

class StageManager {
private:
	Stage current_stage;
	CImage background_img;
	RECT rect; // ���� �̹����� ��ü ũ�� (������������ �̹��� ũ�Ⱑ �ٸ��� ������)
	std::vector<Block> blocks_stage1;

public:

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
	StageManager() :current_stage(Stage::INTRO), rect({ 0,0,0,0 }) {};
	
	void setBlock();
	void setCurrent_stage(Stage stage); // �������� ����
	Stage getCurrent_stage() const;
	void setBackground_img(LPCTSTR path); // ���������� ���� �� ��� ����
	void DrawBackground_img(HDC& mDC, RECT rect,int w); // �� ��� �׸���
	void destroyImg(); // �̹��� ���� (�̹��� ���� ��, �ʼ�)
};
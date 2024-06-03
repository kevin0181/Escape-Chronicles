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

	LPCTSTR img_path[3] = {
		L"img/background/stage1_background_img.png", // background stage 1
		L"img/background/stage2_background_img.png",
		L"img/background/stage3_background_img.png"
	};

	/*
		ȭ�� ��ü ũ�⸦ �����ͼ� ȭ�鿡 ���� ����� ũ�⸦ ������
	*/
	StageManager() :current_stage(Stage::MAIN), rect({ 0,0,0,0 }) {};
	
	void setBlock();
	void setCurrent_stage(Stage stage); // �������� ����
	void setBackground_img(LPCTSTR path); // ���������� ���� �� ��� ����
	void DrawBackground_img(HDC& mDC, RECT rect,int w); // �� ��� �׸���
	void destroyImg(); // �̹��� ���� (�̹��� ���� ��, �ʼ�)
};
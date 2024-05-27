#pragma once
#include<atlimage.h>
#include"Stage.h"

class StageManager {
private:
	Stage current_stage;
	CImage background_img;
public:
	StageManager() :current_stage(Stage::MAIN) {};

	void setCurrent_stage(Stage stage); // �������� ����
	void setBackground_img(LPCTSTR path); // ���������� ���� �� ��� ����
	void DrawBackground_img(HDC& mDC, RECT rect); // �� ��� �׸���
	void destroyImg(); // �̹��� ���� (�̹��� ���� ��, �ʼ�)
};
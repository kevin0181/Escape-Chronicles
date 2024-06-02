#include "StageManager.h"
#include <stdexcept>

void StageManager::setCurrent_stage(Stage stage) {
    current_stage = stage;
}

void StageManager::setBackground_img(LPCTSTR path) {
    // ���� �̹����� �ı��ϰ� ���ο� �̹����� ��ü
    destroyImg();
    background_img.Load(path);
    rect = { 0,0,background_img.GetWidth(),background_img.GetHeight() };
}

void StageManager::DrawBackground_img(HDC& mDC, RECT rect, int w) {
    // ���� ��� �̹����� �־��� HDC�� �׸���
    if (!background_img.IsNull()) {
        background_img.Draw(mDC, 0, 0, background_img.GetWidth() * w, rect.bottom, 0, 0, background_img.GetWidth(), background_img.GetHeight()); //�̹��� ��ü ȭ��
        blocks_stage1[0].print(mDC); //�� �׸���
    }
    else {
        throw std::runtime_error("Background image is not loaded.");
    }
}

void StageManager::destroyImg() {
    // ��� �̹����� �ε�Ǿ� ������ �ı�
    if (!background_img.IsNull()) {
        background_img.Destroy();
    }
}
#include "StageManager.h"
#include <stdexcept>

#define BLOCK_SIZE 70

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
        for (int i = 0; i < blocks_stage1.size(); ++i) { //�� �׸���
            blocks_stage1[i].print(mDC, i, 1);
        }
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


void StageManager::setBlock() { // block create

    blocks_stage1.clear();

    for (int i = 0; i < rect.right / BLOCK_SIZE; ++i) { // ����鿡�� 
        Block block;
        blocks_stage1.push_back(std::move(block));
    }
}
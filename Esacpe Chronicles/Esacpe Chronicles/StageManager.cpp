#include "StageManager.h"
#include <stdexcept>

#define BLOCK_SIZE 70

void StageManager::setCurrent_stage(STAGE stage) {
    current_stage = stage;
}

void StageManager::setBackground_img(const LPCTSTR path) {
    // ���� �̹����� �ı��ϰ� ���ο� �̹����� ��ü
    destroyImg();
    background_img.Load(path);
    rect = { 0,0,background_img.GetWidth(),background_img.GetHeight() };
}

STAGE StageManager::getCurrent_stage() const {
    return current_stage;
}

void StageManager::DrawBackground_img(HDC& mDC, const RECT& rect, const int& w) {
    // ���� ��� �̹����� �־��� HDC�� �׸���
    if (!background_img.IsNull()) {

        background_img.Draw(mDC, 0, 0, rect.right * w, rect.bottom, 0, 0, background_img.GetWidth(), background_img.GetHeight()); //�̹��� ��ü ȭ��

        if (current_stage == STAGE::STAGE_1) {
            for (int i = 0; i < blocks_stage1.size(); ++i) { //�� �׸���
                blocks_stage1[i].print(mDC, i, 1);
            }
        }
    }
    else {
        throw std::runtime_error("Background image is not loaded.");
    }
}

void StageManager::setMainBackGround(HDC& mDC, const RECT& rect) {
    if (!startBtnImg.IsNull()) {
        startBtnImg.Draw(mDC, startBtn.left, startBtn.top, 100, 100, 0, 0, startBtnImg.GetWidth(), startBtnImg.GetHeight());
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


void StageManager::setBlock(const int& h, const LPCTSTR& path_block, const float& size) { // block create

    blocks_stage1.clear();

    for (int i = 0; i < game_rect.right / BLOCK_SIZE; ++i) {
        for (int j = 0; j < h; ++j) {
            Block block;
            block.cImage->Load(path_block);
            block.rect = { i * BLOCK_SIZE, j * BLOCK_SIZE, (i + 1) * BLOCK_SIZE, (j + 1) * BLOCK_SIZE };
            OffsetRect(&block.rect, 0, this->game_rect.bottom * size);
            blocks_stage1.push_back(std::move(block));
        }
    }
}

void StageManager::setLMBtnDown(LPARAM lParam) {
    POINT mP;
    mP.x = LOWORD(lParam);
    mP.y = HIWORD(lParam);

    if (PtInRect(&startBtn, mP)) {
        setBlock(1, Block::path_stage1, 0.98); //block create
        current_stage = STAGE::STAGE_1;
        setBackground_img(background_img_path[0]);
    }
}

void StageManager::setKeyDown(WPARAM wParam) {
    switch (wParam)
    {
    case VK_RETURN:
        intro_cnt++;
        if (intro_cnt >= 5) {
            current_stage = STAGE::MAIN;
            setBackground_img(main_img_path[2]);
            break;
        }
        setBackground_img(this->intro_img_path[intro_cnt]);
        break;
    default:
        break;
    }
}
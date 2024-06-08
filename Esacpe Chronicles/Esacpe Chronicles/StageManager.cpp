﻿#include "StageManager.h"
#include <stdexcept>

#define BLOCK_SIZE 70

void StageManager::setCurrent_stage(STAGE stage) {
    current_stage = stage;
}

void StageManager::setBackground_img(LPCTSTR path) {
    // 기존 이미지를 파괴하고 새로운 이미지로 교체
    destroyImg();
    background_img.Load(path);
    rect = { 0,0,background_img.GetWidth(),background_img.GetHeight() };
}

STAGE StageManager::getCurrent_stage() const {
    return current_stage;
}

void StageManager::DrawBackground_img(HDC& mDC, RECT rect, int w) {
    // 현재 배경 이미지를 주어진 HDC에 그리기
    if (!background_img.IsNull()) {

        background_img.Draw(mDC, 0, 0, rect.right * w, rect.bottom, 0, 0, background_img.GetWidth(), background_img.GetHeight()); //이미지 전체 화면

        if (current_stage == STAGE::STAGE_1) {
            for (int i = 0; i < blocks_stage1.size(); ++i) { //블럭 그리기
                blocks_stage1[i].print(mDC, i, 1);
            }
        }
    }
    else {
        throw std::runtime_error("Background image is not loaded.");
    }
}

void StageManager::destroyImg() {
    // 배경 이미지가 로드되어 있으면 파괴
    if (!background_img.IsNull()) {
        background_img.Destroy();
    }
}


void StageManager::setBlock(int h, LPCTSTR path_block, float size, int detail_size) { // block create

    blocks_stage1.clear();

    // 전체 높이의 90% 지점에서 시작하여 블럭을 배치
    int startY = static_cast<int>(this->rect.bottom * size);

    for (int i = 0; i < rect.right / BLOCK_SIZE * 3; ++i) {
        for (int j = 0; j < h; ++j) {
            Block block;
            block.cImage->Load(path_block);
            block.rect = { i * BLOCK_SIZE, j * BLOCK_SIZE, (i + 1) * BLOCK_SIZE, (j + 1) * BLOCK_SIZE };
            OffsetRect(&block.rect, 0, startY + detail_size);
            blocks_stage1.push_back(std::move(block));
        }
    }
}

void StageManager::setKeyDown(WPARAM wParam) {
    switch (wParam)
    {
    case VK_RETURN:
        intro_cnt++;
        if (intro_cnt >= 5) {
            setBlock(1, Block::path_stage1, 1.0, 30); //block create
            current_stage = STAGE::STAGE_1;
            setBackground_img(background_img_path[0]);
            break;
        }
        setBackground_img(this->intro_img_path[intro_cnt]);
        break;
    default:
        break;
    }
}
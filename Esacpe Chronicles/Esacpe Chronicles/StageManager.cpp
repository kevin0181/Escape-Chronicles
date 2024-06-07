#include "StageManager.h"
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


void StageManager::setBlock() { // block create

    blocks_stage1.clear();

    for (int i = 0; i < rect.right / BLOCK_SIZE; ++i) { // 한장면에서 
        Block block(rect);
        blocks_stage1.push_back(std::move(block));
    }
}

void StageManager::setKeyDown(WPARAM wParam) {
    switch (wParam)
    {
    case VK_RETURN:
        intro_cnt++;
        if (intro_cnt >= 5) {
            setBlock(); //block create
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
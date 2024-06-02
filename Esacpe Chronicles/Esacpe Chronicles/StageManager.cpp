#include "StageManager.h"
#include <stdexcept>

void StageManager::setCurrent_stage(Stage stage) {
    current_stage = stage;
}

void StageManager::setBackground_img(LPCTSTR path) {
    // 기존 이미지를 파괴하고 새로운 이미지로 교체
    destroyImg();
    background_img.Load(path);
    rect = { 0,0,background_img.GetWidth(),background_img.GetHeight() };
}

void StageManager::DrawBackground_img(HDC& mDC, RECT rect, int w) {
    // 현재 배경 이미지를 주어진 HDC에 그리기
    if (!background_img.IsNull()) {
        background_img.Draw(mDC, 0, 0, background_img.GetWidth() * w, rect.bottom, 0, 0, background_img.GetWidth(), background_img.GetHeight()); //이미지 전체 화면
        blocks_stage1[0].print(mDC); //블럭 그리기
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
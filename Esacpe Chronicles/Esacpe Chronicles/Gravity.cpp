#include "Gravity.h"

void Gravity::UpdatePhysics(RECT& rect, DWORD deltaTime) {
    // 속도를 저장할 map에서 해당 객체의 속도를 가져옴, 없으면 초기화
    if (velocities.find(&rect) == velocities.end()) {
        velocities[&rect] = 0.0f; // 초기 속도를 0으로 설정
    }
    float& velocityY = velocities[&rect];

    // deltaTime을 초 단위로 변환
    float deltaSeconds = deltaTime / 1000.0f;

    // 중력에 의한 속도 업데이트
    velocityY += gravity * deltaSeconds;

    // 속도에 의한 위치 업데이트 (중력에 의한 이동)
    int offsetY = static_cast<int>(velocityY * deltaSeconds);
    OffsetRect(&rect, 0, offsetY);
}

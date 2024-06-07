#include "Gravity.h"

void Gravity::UpdatePhysics(RECT& rect, DWORD deltaTime) {
    // �ӵ��� ������ map���� �ش� ��ü�� �ӵ��� ������, ������ �ʱ�ȭ
    if (velocities.find(&rect) == velocities.end()) {
        velocities[&rect] = 0.0f; // �ʱ� �ӵ��� 0���� ����
    }
    float& velocityY = velocities[&rect];

    // deltaTime�� �� ������ ��ȯ
    float deltaSeconds = deltaTime / 1000.0f;

    // �߷¿� ���� �ӵ� ������Ʈ
    velocityY += gravity * deltaSeconds;

    // �ӵ��� ���� ��ġ ������Ʈ (�߷¿� ���� �̵�)
    int offsetY = static_cast<int>(velocityY * deltaSeconds);
    OffsetRect(&rect, 0, offsetY);
}

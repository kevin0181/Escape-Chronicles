#pragma once

#include <Windows.h>
#include <map>

class Gravity {
public:
    const float gravity = 98.0f;

    void UpdatePhysics(RECT& rect, DWORD deltaTime);

private:
    std::map<RECT*, float> velocities;
};

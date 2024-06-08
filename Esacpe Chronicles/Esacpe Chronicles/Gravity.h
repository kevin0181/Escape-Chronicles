#pragma once

#include <Windows.h>
#include <map>

class Gravity {
public:
    const float gravity = 9.5f;

    void UpdatePhysics(RECT& rect);

private:
};

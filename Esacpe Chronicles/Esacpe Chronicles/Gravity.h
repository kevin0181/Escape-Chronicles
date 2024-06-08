#pragma once

#include <Windows.h>
#include <map>

class Gravity {
public:
    const float gravity = 4.5f;

    void UpdatePhysics(RECT& rect);

private:
};

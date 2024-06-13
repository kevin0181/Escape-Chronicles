#pragma once

#include <Windows.h>
#include <atlimage.h>
#include <memory>
#include <gdiplus.h>
#pragma comment (lib, "gdiplus.lib")

using namespace Gdiplus;

#define BLOCK_SIZE 70

class Block {
private:
public:

    static const LPCTSTR path_stage1;
    COLORREF color;
    RECT rect;

    Block() {};

    void print(HDC& mDC) const;

    LPCTSTR getPath_stage1() {
        return path_stage1;
    }
};

#pragma once

#include <Windows.h>
#include <atlimage.h>

class Block {
private:
	RECT rect;
	CImage cimage;
	LPCTSTR path = L"";
public:
};
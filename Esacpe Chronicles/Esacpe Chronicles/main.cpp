#include <Windows.h>
#include <string>
#include <atlimage.h>
#include <vector>

// ------------------
#include "GlobalVariables.h"

#include "Stage.h"
#include "StageManager.h"
#include "Block.h"
#include "Player.h"

#define BLOCK_SIZE 70

using namespace std;

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Escape Chronicles";
LPCTSTR lpszWindowName = L"Escape Chronicles";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;

	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_QUESTION);
	WndClass.hCursor = LoadCursor(NULL, IDC_HAND);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_QUESTION);
	RegisterClassEx(&WndClass);

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_POPUP | WS_VISIBLE,
		0, 0, screenWidth, screenHeight, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return static_cast<int>(Message.wParam);
}

vector<Slime> slimes;
vector<Zombie1> zombie1;
vector<Zombie2> zombie2;
vector<Zombie3> zombie3;
vector<Brain1> brain1;
vector<Brain2> brain2;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	static RECT rect; // 화면 전체 크기

	PAINTSTRUCT ps;
	HDC hDC, mDC;
	HBITMAP hBitmap;
	HBITMAP hOldBitmap;

	static StageManager stageManager;
	static Player player;

    switch (uMsg) {
	case WM_CREATE:
	{
		GetClientRect(hWnd, &rect);
		stageManager.setBackground_img(stageManager.intro_img_path[0]);
		stageManager.game_rect = rect;
		stageManager.game_rect.right *= 3; //게임 크기 정해주기
		stageManager.viewRect = rect;

		// 시작버튼
		stageManager.startBtn = { rect.right - 300, rect.bottom - 150, rect.right - 200, rect.bottom - 50 };
		stageManager.rect = rect;
     
		for (int i = 0; i < 5;++i) {// 원하는 개수만큼 반복
			Slime slime;
			slime.insert();
			slimes.push_back(slime);
		}
        //zombie1.insert();
        //zombie2.insert();
        //zombie3.insert();
		//brain1.insert();
		//brain2.insert();

		

        SetTimer(hWnd, 1, 1, FALSE);
        break;
    }
	case WM_LBUTTONDOWN:

		if (stageManager.getCurrent_stage() == STAGE::MAIN)
			stageManager.setLMBtnDown(lParam);

		break;
    case WM_KEYDOWN:

		if (stageManager.getCurrent_stage() == STAGE::INTRO)
			stageManager.setKeyDown(wParam);

		if (stageManager.getCurrent_stage() == STAGE::STAGE_1 || stageManager.getCurrent_stage() == STAGE::STAGE_2 ||
			stageManager.getCurrent_stage() == STAGE::STAGE_3)
			player.setKeyDown(wParam);

		break;
	case WM_KEYUP:
		player.setKeyUp(wParam);
		break;
	case WM_PAINT: {
		hDC = BeginPaint(hWnd, &ps);
		mDC = CreateCompatibleDC(hDC);
		GetClientRect(hWnd, &rect);
		hBitmap = CreateCompatibleBitmap(hDC, rect.right, rect.bottom);
		hOldBitmap = static_cast<HBITMAP>(SelectObject(mDC, hBitmap));

		FillRect(mDC, &rect, static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)));

        /*
        intro
         스토리 이미지
        */
        if (STAGE::INTRO == stageManager.getCurrent_stage()) {
			stageManager.DrawBackground_img(mDC, 1);
        }
		if (STAGE::MAIN == stageManager.getCurrent_stage()) {
			stageManager.DrawBackground_img(mDC, 1);
			stageManager.setMainBackGround(mDC, rect);
		}

        /*
        stage 1
            플레이어, 슬라임, 파란색 벽돌
        */
        if (STAGE::STAGE_1 == stageManager.getCurrent_stage()) {
            stageManager.DrawBackground_img(mDC, 3);
			for (auto& slime : slimes) {
				slime.print(mDC);
			}
            player.print(mDC);
        }

		// ------------------------------------------------
		//zombie1[i].print(mDC);
		//zombie2[i].print(mDC);
		//zombie3[i].print(mDC);
		//brain1[i].print(mDC);
		//brain2[i].print(mDC);

		BitBlt(hDC, 0, 0, rect.right, rect.bottom, mDC, 0, 0, SRCCOPY);

		SelectObject(mDC, hOldBitmap);
		DeleteObject(hBitmap);
		DeleteDC(mDC);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_TIMER:
		if (wParam == 1) {

			switch (stageManager.getCurrent_stage())
			{
			case STAGE::STAGE_1:
			{
				for (auto& slime : slimes) {
					slime.move(stageManager);
				}
				
				//zombie1.move(stageManager);
				//zombie2.move(stageManager);
				//zombie3.move(stageManager);
				//brain1.move(stageManager);
				//brain2.move(stageManager);

				//player
				player.TIMER(stageManager);
				break;
			}
			default:
				break;
			}
		}
		InvalidateRect(hWnd, NULL, false);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return 0;
}
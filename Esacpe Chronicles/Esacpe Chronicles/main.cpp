#include <Windows.h>
#include <string>
#include <atlimage.h>
#include <vector>
#include <gdiplus.h>

#pragma comment (lib, "gdiplus.lib")

using namespace Gdiplus;
// ------------------
#include "GlobalVariables.h"

#include "collision.h"
#include "Stage.h"
#include "StageManager.h"
#include "Block.h"
#include "Player.h"
#include "Ui.h"
#include "SoundManager.h"

#define BLOCK_SIZE 70

using namespace std;

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Escape Chronicles";
LPCTSTR lpszWindowName = L"Escape Chronicles";

SoundManager soundManager;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;

	// GDI+ 초기화
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

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

	// SoundManager 초기화 및 사운드 파일 로드
	if (!soundManager.Initialize(hWnd)) {
		MessageBox(hWnd, L"Could not initialize DirectSound.", L"Error", MB_OK);
		return -1;
	}

	if (!soundManager.LoadWaveFile(L"sound/background_sound.wav", L"BGM")) {
		MessageBox(hWnd, L"Could not load BGM sound.", L"Error", MB_OK);
		return -1;
	}

	if (!soundManager.LoadWaveFile(L"sound/shoot-4-102361.wav", L"Gunshot")) {
		MessageBox(hWnd, L"Could not load Gunshot sound.", L"Error", MB_OK);
		return -1;
	}

	if (!soundManager.LoadWaveFile(L"sound/sword-sound-2-36274.wav", L"sword")) {
		MessageBox(hWnd, L"Could not load Sword sound.", L"Error", MB_OK);
		return -1;
	}

	if (!soundManager.LoadWaveFile(L"sound/arrow-sound.wav", L"arrow")) {
		MessageBox(hWnd, L"Could not load Sword sound.", L"Error", MB_OK);
		return -1;
	}

	soundManager.PlaySoundW(L"BGM", true); // 배경음악 재생
	soundManager.SetVolume(L"BGM", -2000); // 배경음악 볼륨 조절 (50%)

	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	soundManager.Shutdown(); // SoundManager 종료

	// GDI+ 해제
	GdiplusShutdown(gdiplusToken);

	return static_cast<int>(Message.wParam);
}


vector<std::unique_ptr<Monster>> monsters;
StageManager stageManager;
Ui ui;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	static RECT rect; // 화면 전체 크기

	PAINTSTRUCT ps;
	HDC hDC, mDC;
	HBITMAP hBitmap;
	HBITMAP hOldBitmap;

	static Player player;

	static CImage cursorImage;
	static int cursorWidth, cursorHeight;
	// 마우스 위치 가져오기
	static POINT cursorPos;

	static int collision_num = 0;

	switch (uMsg) {
	case WM_CREATE:
	{
		// 기본 커서 숨기기
		ShowCursor(FALSE);
		cursorImage.Load(L"img/cursor/cursor.png");
		cursorWidth = cursorImage.GetWidth();
		cursorHeight = cursorImage.GetHeight();

		GetClientRect(hWnd, &rect);
		stageManager.setBackground_img(stageManager.intro_img_path[0]);
		stageManager.game_rect = rect;
		stageManager.game_rect.bottom -= 10;
		stageManager.game_rect.right = (rect.right - rect.left) * 3;
		stageManager.viewRect = rect;

		// 시작버튼
		stageManager.startBtn = { rect.right - 300, rect.bottom - 150, rect.right - 200, rect.bottom - 50 };
		stageManager.rect = rect;

		SetTimer(hWnd, 1, 1, FALSE);
		break;
	}
	case WM_LBUTTONDOWN:

		if (stageManager.getCurrent_stage() == STAGE::MAIN)
			stageManager.setLMBtnDown(lParam);

		if (stageManager.getCurrent_stage() == STAGE::STAGE_1 || stageManager.getCurrent_stage() == STAGE::STAGE_2 ||
			stageManager.getCurrent_stage() == STAGE::STAGE_3) {

			if (player.getWeapon() == 2 && !player.press_m_l) {
				Bullet bullet;
				bullet.rect = player.getRECT();
				bullet.weapon_status = 2;
				bullet.img = new Gdiplus::Image(bullet._arrow_r[0]);
				InflateRect(&bullet.rect, -5, -40);
				OffsetRect(&bullet.rect, 0, -5);
				player.bullets.push_back(bullet);
			}

			if (player.getWeapon() == 3 && !player.press_m_l) {
				Bullet bullet;
				bullet.rect = player.getRECT();
				bullet.weapon_status = 3;
				bullet.img = new Gdiplus::Image(bullet._bullet_r[0]);
				InflateRect(&bullet.rect, -35, -50);
				OffsetRect(&bullet.rect, 0, -15);
				player.bullets.push_back(bullet);
			}

			player.mouse_p.x = LOWORD(lParam);
			player.mouse_p.y = HIWORD(lParam);
			player.press_m_l = true;

		}

		break;
	case WM_MOUSEMOVE:

		if (stageManager.getCurrent_stage() == STAGE::STAGE_1 || stageManager.getCurrent_stage() == STAGE::STAGE_2 ||
			stageManager.getCurrent_stage() == STAGE::STAGE_3) {
			if (player.press_m_l) {
				player.mouse_p.x = LOWORD(lParam);
				player.mouse_p.y = HIWORD(lParam);
			}
		}

		break;
	case WM_LBUTTONUP:

		if (stageManager.getCurrent_stage() == STAGE::STAGE_1 || stageManager.getCurrent_stage() == STAGE::STAGE_2 ||
			stageManager.getCurrent_stage() == STAGE::STAGE_3) {
			player.press_m_l = false;
			if (player.bullets.size() != 0) {
				if (player.getWeapon() == 2) {

					if (player.press_cnt >= 30) { //2.5초 정도 넘으면 발사 가능.
						soundManager.PlaySoundW(L"arrow", false); // 총 브금
						soundManager.SetVolume(L"arrow", -1000);
						player.bullets[player.bullets.size() - 1].status = true;
						player.shootArrow();
					}
				}
				else if (player.getWeapon() == 3) {
					soundManager.PlaySoundW(L"Gunshot", false); // 총 브금
					soundManager.SetVolume(L"Gunshot", -1000);

					player.bullets[player.bullets.size() - 1].status = true;
					player.shootArrow();
				}
				else { //아니면 지우기
					player.bullets.pop_back();
				}
			}
			player.press_cnt = 0;
		}
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
		//마우스 위치 가져오기
		GetCursorPos(&cursorPos);
		ScreenToClient(hWnd, &cursorPos);

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
			for (auto& monster : monsters) {
				monster->print(mDC);
			}
			player.print(mDC);

			ui.print(mDC, player);
		}

		/*
	   stage 2
		   플레이어, 슬라임, red 벽돌
	   */
		if (STAGE::STAGE_2 == stageManager.getCurrent_stage()) {
			stageManager.DrawBackground_img(mDC, 3);
			for (auto& monster : monsters) {
				monster->print(mDC);
			}
			player.print(mDC);

			ui.print(mDC, player);
		}

		/*
	   stage 3
		   플레이어, 슬라임, red 벽돌
	   */
		if (STAGE::STAGE_3 == stageManager.getCurrent_stage()) {
			stageManager.DrawBackground_img(mDC, 3);
			for (auto& monster : monsters) {
				monster->print(mDC);
			}
			player.print(mDC);

			ui.print(mDC, player);
		}

		// ------------------------------------------------
		//zombie1[i].print(mDC);
		//zombie2[i].print(mDC);
		//zombie3[i].print(mDC);
		//brain1[i].print(mDC);
		//brain2[i].print(mDC);


		//커서 이미지 그리기
		cursorImage.Draw(mDC, cursorPos.x - 40, cursorPos.y - 40, 80, 80, 0, 0, cursorWidth, cursorHeight);

		//boss.print(mDC);

		BitBlt(hDC, 0, 0, rect.right, rect.bottom, mDC, 0, 0, SRCCOPY);

		SelectObject(mDC, hOldBitmap);
		DeleteObject(hBitmap);
		DeleteDC(mDC);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_TIMER:
		if (wParam == 1) {

			if (player.press_m_l) { // 몇 초 누르고 있는지 확인
				player.press_cnt++;
			}

			switch (stageManager.getCurrent_stage())
			{
			case STAGE::STAGE_2:{}
			case STAGE::STAGE_3:
			case STAGE::STAGE_1:
			{
				++collision_num;

				for (auto& monster : monsters) {
					monster->move(stageManager);

					if (collision_num % 20 == 0) {
						monster->MonsterPlayerCollision(player);
					}
				}

				//zombie1.move(stageManager);
				//zombie2.move(stageManager);
				//zombie3.move(stageManager);
				//brain1.move(stageManager);
				//brain2.move(stageManager);
				//boss.move(stageManager);

				//player
				player.TIMER(stageManager);
				break;
			}
			default:
				break;
			}
			InvalidateRect(hWnd, NULL, false);
		}
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return 0;
}
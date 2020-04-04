#include "stdafx.h"
#include "util.h"

float MY_UTIL::getDistance(float startX, float startY, float endX, float endY)
{
	float x = endX - startX;
	float y = endY - startY;

	return sqrtf(x * x + y * y);
}

float MY_UTIL::getAngle(float startX, float startY, float endX, float endY)
{
	float x = endX - startX;
	float y = endY - startY;
	float distance = sqrtf(x * x + y * y);
	float angle = acosf(x / distance);
	if (endY > startY)
	{
		angle = PI2 - angle;
	}
	return angle;
}

void MY_UTIL::showTitle(HDC hdc, const char * title, int x, int y, COLORREF color)
{
	SetTextColor(hdc, color);
	TextOut(hdc, x, y, title, strlen(title));
}

HBITMAP MY_UTIL::ScreenCapture()
{
	// 메인 모니터의 해상도를 구한다.
	int ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	int ScreenHeight = GetSystemMetrics(SM_CYSCREEN);

	HDC hScrDC, hMemDC;
	HBITMAP hBitmap;

	// 화면 DC와 스크린샷을 저장할 비트맵을 생성한다.
	hScrDC = CreateDC("DISPLAY", NULL, NULL, NULL);
	hMemDC = CreateCompatibleDC(hScrDC);
	hBitmap = CreateCompatibleBitmap(hScrDC, ScreenWidth, ScreenHeight);
	SelectObject(hMemDC, hBitmap);

	// 현재 화면을 비트맵으로 복사한다.
	BitBlt(hMemDC, 0, 0, ScreenWidth, ScreenHeight, hScrDC, 0, 0, SRCCOPY);   

	DeleteDC(hMemDC);
	DeleteDC(hScrDC);

	return hBitmap;
}
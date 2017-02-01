#pragma once
#include "Header.h"

class Match
{
public:
	Match(POINT start);
	~Match();

	void Draw(HDC hdc);
	void Down(HDC hdc, POINT coordDown);

private:
	COLORREF cBrushIsDown;
	COLORREF cBrushIsntDown;
	COLORREF cPen;
	POINT start_;
	POINT matchSize_;

	BOOL isDown;
};

Match::Match(POINT start)
{
	cBrushIsDown = RGB(255, 255, 255);
	cBrushIsntDown = RGB(0, 255, 255);
	cPen = RGB(0, 0, 0);
	start_ = start;
	matchSize_.x = 15;
	matchSize_.y = 30;
	isDown = false;
}

Match::~Match()
{
}

void Match::Draw(HDC hdc)
{
	HBRUSH hBrush;
	if (isDown)
	{
		hBrush = CreateSolidBrush(cBrushIsDown);
	}
	else
	{
		hBrush = CreateSolidBrush(cBrushIsntDown);
	}

	HPEN hPen = CreatePen(PS_SOLID, 1, cPen);
	HBRUSH hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);
	HPEN hPenOld = (HPEN)SelectObject(hdc, hPen);

	Rectangle(hdc,
		start_.x,
		start_.y,
		start_.x + matchSize_.x,
		start_.y + matchSize_.y);

	SelectObject(hdc, hPenOld);
	SelectObject(hdc, hBrushOld);

	DeleteObject(hBrush);
	DeleteObject(hPen);
}

void Match::Down(HDC hdc, POINT coordDown)
{
	if ((start_.x < coordDown.x) && (coordDown.x < start_.x + matchSize_.x) &&
		(start_.y < coordDown.y) && (coordDown.y < start_.y + matchSize_.y))
	{
		if (isDown)
		{
			isDown = false;
		}
		else
		{
			isDown = true;
		}
	}
}
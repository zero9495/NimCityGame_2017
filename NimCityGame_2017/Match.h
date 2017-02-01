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
	HBRUSH GetNecessaryBrush();
	BOOL IsOnRect(POINT coordDown);
	void DrawRectangle(HDC hdc);
	void ChangeFlag();

private:
	COLORREF cBrushIsDown;
	COLORREF cBrushIsntDown;
	COLORREF cPen;
	POINT start_;
	POINT size_;

	BOOL isDown;
};

Match::Match(POINT start)
{
	cBrushIsDown = RGB(255, 255, 255);
	cBrushIsntDown = RGB(0, 255, 255);
	cPen = RGB(0, 0, 0);
	start_ = start;
	size_.x = 15;
	size_.y = 30;
	isDown = false;
}

Match::~Match()
{
}

void Match::Draw(HDC hdc)
{
	HBRUSH hBrush = this->GetNecessaryBrush();	

	HPEN hPen = CreatePen(PS_SOLID, 1, cPen);
	HBRUSH hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);
	HPEN hPenOld = (HPEN)SelectObject(hdc, hPen);

	this->DrawRectangle(hdc);	

	SelectObject(hdc, hPenOld);
	SelectObject(hdc, hBrushOld);

	DeleteObject(hBrush);
	DeleteObject(hPen);
}

void Match::Down(HDC hdc, POINT coordDown)
{
	if (this->IsOnRect(coordDown))
	{
		this->ChangeFlag();		
	}
}

HBRUSH Match::GetNecessaryBrush()
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

	return hBrush;
}

BOOL Match::IsOnRect(POINT coordDown)
{
	return (start_.x < coordDown.x) && (coordDown.x < start_.x + size_.x) &&
		(start_.y < coordDown.y) && (coordDown.y < start_.y + size_.y);
}

void Match::DrawRectangle(HDC hdc)
{
	Rectangle(hdc,
		start_.x,
		start_.y,
		start_.x + size_.x,
		start_.y + size_.y);
}

void Match::ChangeFlag()
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
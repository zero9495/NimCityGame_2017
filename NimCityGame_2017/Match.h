#pragma once
#include "Header.h"
#include "GameObject.h"

class Match : public GameObject
{
public:
	Match(POINT &start);
	~Match();
	Match(Match &match);

	void Draw(HDC &hdc);
	void Down(HDC &hdc, POINT &coordDown);

private:
	HBRUSH GetNecessaryBrush();

private:
	BOOL isDown;
};

Match::Match(POINT &start)
{
	start_ = start;
	size_ = &matchSize;
	isDown = false;
}

Match::~Match()
{
}

Match::Match(Match &match) :
	isDown(match.isDown)
{
}

void Match::Draw(HDC &hdc)
{
	HBRUSH hBrush = this->GetNecessaryBrush();	

	HPEN hPen = CreatePen(PS_SOLID, 1, cMatchPen);
	HBRUSH hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);
	HPEN hPenOld = (HPEN)SelectObject(hdc, hPen);

	this->DrawRectangle(hdc);	

	SelectObject(hdc, hPenOld);
	SelectObject(hdc, hBrushOld);

	DeleteObject(hBrush);
	DeleteObject(hPen);
}

void Match::Down(HDC &hdc, POINT &coordDown)
{
	if (this->IsOnRect(coordDown))
	{
		isDown = !isDown;
	}
}

HBRUSH Match::GetNecessaryBrush()
{
	if (isDown)
	{
		return CreateSolidBrush(cMatchBrushIsDown);
	}
	return CreateSolidBrush(cMatchBrushIsntDown);
}
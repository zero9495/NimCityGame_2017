#pragma once
#include "Match.h"

class Heap
{
public:
	Heap(int count, POINT start, POINT size);
	~Heap();

	void Draw(HDC hdc);
	void Down(HDC hdc, POINT coordDown);
	int GetCount();

private:
	BOOL IsOnRect(POINT coordDown);

private:
	COLORREF cBrush;
	COLORREF cPen;
	POINT start_;
	POINT size_;
	int count_;

	Match** matches;
};

Heap::Heap(int count, POINT start, POINT size)
{
	cBrush = RGB(255, 255, 255);
	cPen = RGB(0, 0, 0);
	start_ = start;
	size_ = size;
	count_ = count;

	POINT matchStart;

	matches = new Match*[count_];
	for (int i = 0; i < count_; i++)
	{
		if ((i) && (i % 7 == 0))
		{
			start.y += 40;
		}
		matchStart.x = 5 + start.x + 20 * (i % 7);
		matchStart.y = 5 + start.y;
		matches[i] = new Match(matchStart);
	}
}

Heap::~Heap()
{
	for (int i = 0; i < count_; i++)
	{
		delete matches[i];
	}
	delete []matches;
}

void Heap::Draw(HDC hdc)
{
	HBRUSH hBrush = CreateSolidBrush(cBrush);
	HPEN hPen = CreatePen(PS_SOLID, 1, cPen);
	HBRUSH hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);
	HPEN hPenOld = (HPEN)SelectObject(hdc, hPen);

	Rectangle(hdc,
		start_.x,
		start_.y,
		start_.x + size_.x,
		start_.y + size_.y);

	SelectObject(hdc, hPenOld);
	SelectObject(hdc, hBrushOld);

	DeleteObject(hBrush);
	DeleteObject(hPen);

	for (int i = 0; i < count_; i++)
	{
		matches[i]->Draw(hdc);
	}
}

void Heap::Down(HDC hdc, POINT coordDown)
{
	if (this->IsOnRect(coordDown))
	{
		for (int i = 0; i < count_; i++)
		{
			matches[i]->Down(hdc, coordDown);
		}
	}
}

int Heap::GetCount()
{
	return count_;
}

BOOL Heap::IsOnRect(POINT coordDown)
{
	return (start_.x < coordDown.x) && (coordDown.x < start_.x + size_.x) &&
		(start_.y < coordDown.y) && (coordDown.y < start_.y + size_.y);
}
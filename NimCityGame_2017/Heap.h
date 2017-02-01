#pragma once
#include "Match.h"

class Heap
{
public:
	Heap(int count, POINT start, POINT heapSize);
	~Heap();

	void Draw(HDC hdc);
	void Down(HDC hdc, POINT coordDown);
	int GetCount();

private:
	COLORREF cBrush;
	COLORREF cPen;
	POINT start_;
	POINT heapSize_;
	int count_;

	Match** matches;
};

Heap::Heap(int count, POINT start, POINT heapSize)
{
	cBrush = RGB(255, 255, 255);
	cPen = RGB(0, 0, 0);
	start_ = start;
	heapSize_ = heapSize;
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
		start_.x + heapSize_.x,
		start_.y + heapSize_.y);

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
	if ((start_.x < coordDown.x) && (coordDown.x < start_.x + heapSize_.x) &&
		(start_.y < coordDown.y) && (coordDown.y < start_.y + heapSize_.y))
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
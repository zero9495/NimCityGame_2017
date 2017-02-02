#pragma once
#include "Match.h"

class Heap : public GameObject
{
public:
	Heap(int &count, POINT &start, POINT &size);
	~Heap();

	void Draw(HDC &hdc);
	void Down(HDC &hdc, POINT &coordDown);
	int GetCount();

private:
	COLORREF cBrush;
	COLORREF cPen;
	int count_;

	Match** matches;
};

Heap::Heap(int &count, POINT &start, POINT &size)
{
	cBrush = RGB(255, 255, 255);
	cPen = RGB(0, 0, 0);
	start_ = start;
	size_ = size;
	count_ = count;

	POINT matchStart;
	int indent = start_.y;

	matches = new Match*[count_];
	for (int i = 0; i < count_; i++)
	{
		if ((i) && (i % 7 == 0))
		{
			indent += 40;
		}
		matchStart.x = 5 + start.x + 20 * (i % 7);
		matchStart.y = 5 + indent;
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

void Heap::Draw(HDC &hdc)
{
	HBRUSH hBrush = CreateSolidBrush(cBrush);
	HPEN hPen = CreatePen(PS_SOLID, 1, cPen);
	HBRUSH hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);
	HPEN hPenOld = (HPEN)SelectObject(hdc, hPen);

	this->DrawRectangle(hdc);

	SelectObject(hdc, hPenOld);
	SelectObject(hdc, hBrushOld);

	DeleteObject(hBrush);
	DeleteObject(hPen);

	for (int i = 0; i < count_; i++)
	{
		matches[i]->Draw(hdc);
	}
}

void Heap::Down(HDC &hdc, POINT &coordDown)
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
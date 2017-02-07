#pragma once
#include "Match.h"

class Heap : public GameObject
{
public:
	Heap(int &count, POINT &start);
	~Heap();
	Heap(Heap &heap);

	void Draw(HDC &hdc);
	void Down(HDC &hdc, POINT &coordDown);
	int GetCount();

private:
	int count_;
	Match** matches;
};

Heap::Heap(int &count, POINT &start)
{
	start_ = start;
	size_ = &heapSize;
	count_ = count;

	POINT matchStart;
	int indent = start_.y;

	matches = new Match*[count_];
	for (int i = 0; i < count_; i++)
	{
		if ((i) && (i % amountOfMatchesInARow == 0))
		{
			indent += matchSize.y + distanceBetweenMatches.y;
		}
		matchStart.x = distanceBetweenMatchesAndHeap.x + start.x + distanceBetweenMatches.x * (i % amountOfMatchesInARow);
		matchStart.y = distanceBetweenMatchesAndHeap.y + indent;
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

Heap::Heap(Heap &heap) :
	count_(heap.count_)
{
	matches = new Match*[count_];
	for (int i = 0; i < count_; i++)
	{
		matches[i] = new Match(*heap.matches[i]);
	}
}

void Heap::Draw(HDC &hdc)
{
	HBRUSH hBrush = CreateSolidBrush(cHeapBrush);
	HPEN hPen = CreatePen(PS_SOLID, 1, cHeapPen);
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
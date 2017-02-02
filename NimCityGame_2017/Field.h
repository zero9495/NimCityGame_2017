#pragma once
#include "Heap.h"

class Field
{
public:
	Field(HWND &hWnd, HINSTANCE &hInst);
	~Field();

	void Draw(HDC &hdc);
	void Down(HDC &hdc, POINT &coordDown);

private:
	POINT start;
	POINT heapSize;
	Heap **heaps;
	HWND hFirstBtn;
};

Field::Field(HWND &hWnd, HINSTANCE &hInst)
{
	heapSize.x = 150;
	heapSize.y = 130;
	start.x = 100;
	start.y = 50;

	POINT heapStart;
	heapStart.y = start.y;
	int count = 0;

	heaps = new Heap*[5];
	for (int i = 0; i < 5; i++)
	{
		heapStart.x = start.x + (heapSize.x + 10)*i;
		count = 17 + i;
		heaps[i] = new Heap(count,
			heapStart,
			heapSize);
	}
	
	hFirstBtn = CreateWindowEx(0, _T("Button"), _T("Takeee"), WS_VISIBLE | WS_CHILD | WS_TABSTOP,
		475,
		200,
		50,
		24,
		hWnd, (HMENU)FIRST_BTN_ID, hInst, NULL);

}

Field::~Field()
{
	for (int i = 0; i < 5; i++)
	{
		delete heaps[i];
	}
	delete[]heaps;
}

void Field::Draw(HDC &hdc)
{
	for (int i = 0; i < 5; i++)
	{
		heaps[i]->Draw(hdc);
	}

	/*char str[256];
	ZeroMemory(&str, sizeof(str));
	strcpy_s(str, "(");

	int num = 0;
	int lenNum = 0;
	int tempNum = 0;
	char s[256];
	for (int i = 0; i < 5; i++)
	{
	if (i)
	{
	strcat(str, ",");
	}

	ZeroMemory(&s, sizeof(s));

	num = heaps[i]->GetCount();
	lenNum = 0;
	tempNum = num;
	for (; tempNum > 0; lenNum++)
	{
	tempNum /= 10;
	}

	_itoa_s(num, s, lenNum + 1, 10);

	strcat(str, s);
	}
	strcat(str, ")");

	wchar_t wtext[256];
	mbstowcs(wtext, str, strlen(str) + 1);

	TextOut(hdc,
	445,
	230,
	wtext, _tcslen(wtext));
	*/
}

void Field::Down(HDC &hdc, POINT &coordDown)
{
	for (int i = 0; i < 5; i++)
	{
		heaps[i]->Down(hdc, coordDown);
	}
}
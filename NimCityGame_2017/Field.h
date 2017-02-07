#pragma once
#include "Heap.h"

class Field
{
public:
	Field(HWND &hWnd, HINSTANCE &hInst);
	~Field();
	Field(Field &field);

	void Draw(HDC &hdc);
	void Down(HDC &hdc, POINT &coordDown);

private:
	Heap **heaps;
	HWND hFirstBtn;
};

Field::Field(HWND &hWnd, HINSTANCE &hInst)
{
	POINT heapStart;
	heapStart.y = fieldStart.y;
	int count = 0;

	heaps = new Heap*[amountOfHeaps];
	for (int i = 0; i < amountOfHeaps; i++)
	{
		heapStart.x = fieldStart.x + (heapSize.x + distanceBetweenHeaps.x)*i;
		count = minAmountOfMatches + i;
		heaps[i] = new Heap(count,
			heapStart);
	}
	
	hFirstBtn = CreateWindowEx(0, _T("Button"), buttonText, WS_VISIBLE | WS_CHILD | WS_TABSTOP,
		buttonSize.left,
		buttonSize.top,
		buttonSize.right,
		buttonSize.bottom,
		hWnd, (HMENU)FIRST_BTN_ID, hInst, NULL);
}

Field::~Field()
{
	for (int i = 0; i < amountOfHeaps; i++)
	{
		delete heaps[i];
	}
	delete[]heaps;
}

Field::Field(Field &field) :
	hFirstBtn(field.hFirstBtn)
{
	heaps = new Heap*[amountOfHeaps];
	for (int i = 0; i < amountOfHeaps; i++)
	{
		heaps[i] = new Heap(*field.heaps[i]);
	}
}

void Field::Draw(HDC &hdc)
{
	for (int i = 0; i < amountOfHeaps; i++)
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
	for (int i = 0; i < amountOfHeaps; i++)
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
	for (int i = 0; i < amountOfHeaps; i++)
	{
		heaps[i]->Down(hdc, coordDown);
	}
}
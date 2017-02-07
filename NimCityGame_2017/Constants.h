#pragma once
#include "Header.h"

#define IDC_MYBUTTON 100
#define FIRST_BTN_ID 1

TCHAR *buttonText = _T("Takeee");

COLORREF cMatchBrushIsDown = RGB(255, 255, 255);
COLORREF cMatchBrushIsntDown = RGB(0, 255, 255);
COLORREF cMatchPen = RGB(0, 0, 0);

COLORREF cHeapBrush = RGB(255, 255, 255);
COLORREF cHeapPen = RGB(0, 0, 0);

POINT matchSize = { 15,30 };
POINT heapSize = { 150, 130 };

int amountOfMatchesInARow = 7;
POINT distanceBetweenMatches = { 20,10 };
POINT distanceBetweenMatchesAndHeap = { 5,5 };
POINT distanceBetweenHeaps = { 10,0 };

POINT fieldStart = { 100, 50 };

int amountOfHeaps = 5;
int minAmountOfMatches = 17;

RECT buttonSize = { 475,200,50,24, };
#pragma once
#include "Header.h"

void Echo(HDC& hdc, String& str)
{
	TextOut(hdc, 0, 0, str.data(), str.size());
}

void CreateMyMenu(HWND &hWnd)
{
	HMENU hMainMenu = CreateMenu();
	HMENU hPopMenuFile = CreatePopupMenu();

	AppendMenu(hMainMenu, MF_STRING | MF_POPUP, (UINT)hPopMenuFile, _T("Файл"));
	AppendMenu(hMainMenu, MF_STRING, 1000, _T("Справка"));

	AppendMenu(hPopMenuFile, MF_STRING, 1001, _T("Отправить данные"));

	SetMenu(hWnd, hMainMenu);
	SetMenu(hWnd, hPopMenuFile);
}
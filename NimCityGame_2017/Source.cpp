/*

������
- ������� ������� �������� ��������� � ���� � � ������ (������) �����������
- �������� ����� ����, ����� � ������� ���� ������������ ������ ����������
- �������� ����������� ����������� (� ���������)
- ����������� ��������� �� � ������ ������ ������
- ������� �����, ������� � ������� � ���� � �����������
- ���������� �� ������������ ����� (������ �� ��� �� �������� � �����)
- �������� ���-������� ��� �������� ������ � ����
- �������� ���-������� ����������� � ����� ���� ��� ����� ������
- ����������� � HINSANCE. ��� ��� � �����?
- ����� ������� �� ������ ��������� ������ �������������, � �� ���.
- � GetNecessaryBrush() ���������� �������� ������ �� �������

*/

#define _CRT_SECURE_NO_WARNINGS

#include "Functions.h"
#include "Constants.h"
//#include "Resource.h"
#include "Heap.h"

#define FIRST_BTN_ID 1

HINSTANCE hInst; //���������� ���������� ����������. �� ����� handle instance

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR WinName[] = _T("MainFrame");

int APIENTRY _tWinMain(HINSTANCE This, // ���������� �������� ����������
	HINSTANCE Prev, // � ����������� �������� ������ 0
	LPTSTR cmd, // ��������� ������
	int mode) // ����� ����������� ����
{
	HWND hWnd; // ���������� �������� ���� ���������
	MSG msg; // ��������� ��� �������� ���������
	WNDCLASS wc; // ����� ����
				 // ����������� ������ ����
	wc.hInstance = This;
	wc.lpszClassName = WinName; // ��� ������ ����
	wc.lpfnWndProc = WndProc; // ������� ����
	wc.style = CS_HREDRAW | CS_VREDRAW; // ����� ����
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); // ����������� ������
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // ����������� ������
	wc.lpszMenuName = NULL; // ��� ����
	wc.cbClsExtra = 0; // ��� �������������� ������ ������
	wc.cbWndExtra = 0; // ��� �������������� ������ ����
					   // ���������� ���� ����� ������
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	if (!RegisterClass(&wc)) return 0; // ����������� ������ ����

	// �������� ����
	hWnd = CreateWindow(WinName, // ��� ������ ����
		_T("������ Windows-����������"), // ��������� ����
		WS_OVERLAPPEDWINDOW, // ����� ����
		CW_USEDEFAULT,// x
		CW_USEDEFAULT,// y
		CW_USEDEFAULT,// Width
		CW_USEDEFAULT,// Height
		HWND_DESKTOP, // ���������� ������������� ����
		NULL, // ��� ����
		This, // ���������� ����������
		NULL); // �������������� ���������� ���

	ShowWindow(hWnd, mode); //�������� ����
							// ���� ��������� ���������
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);// ������� ���������� ����� ������� �������
		DispatchMessage(&msg); // �������� ��������� ������� WndProc()
	}
	return 0;
}


// ������� ������� ���������� ������������ ��������
// � �������� ��������� �� ������� ��� ������� ����������
LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{ // ���������� ���������
	PAINTSTRUCT ps;
	HDC hdc;
	//static String str;
	//int x, y;

	static POINT coordDown;
	static POINT start;
	static POINT heapSize;
	static Heap **heaps;
	static HWND hFirstBtn;

	
	switch (message)
	{
	case WM_CREATE:
	{
		CreateMyMenu(hWnd);

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

		break;
	}
	case WM_RBUTTONDOWN:
	{
		//x = LOWORD(lParam);
		//y = HIWORD(lParam);
	}
	case WM_CHAR:
	{
		//str += (TCHAR)wParam;
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	}
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		
		//Echo(hdc, str);

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
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		HDC hdc = GetDC(hWnd);

		coordDown.x = LOWORD(lParam);
		coordDown.y = HIWORD(lParam);

		for (int i = 0; i < 5; i++)
		{
			heaps[i]->Down(hdc, coordDown);
		}

		ReleaseDC(hWnd, hdc);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	// ��������� ��������� �� ���������
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
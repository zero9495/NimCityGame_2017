/*

������
- ������� ������� �������� ��������� � ���� � � ������ (������) �����������
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

#include "Functions.h"
#include "Constants.h"
#include "Field.h"

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

	static POINT coordDown;
	static Field *gameField;
	
	switch (message)
	{
	case WM_CREATE:
	{
		CreateMyMenu(hWnd);		
		gameField = new Field(hWnd, hInst);

		break;
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
		gameField->Draw(hdc);
		
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		HDC hdc = GetDC(hWnd);

		coordDown.x = LOWORD(lParam);
		coordDown.y = HIWORD(lParam);

		gameField->Down(hdc, coordDown);

		ReleaseDC(hWnd, hdc);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	}
	case WM_DESTROY:
	{
		delete gameField;
		PostQuitMessage(0);
		break;
	}
	// ��������� ��������� �� ���������
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
/*

Задачи
- Сделать функцию проверки попадания в кучу и в спичку (приват) виртуальной
- ДОбавить конструктор копирования (и сравнения)
- Разобраться правильно ли я удаляю массив спичек
- Вывести цвета, размеры и надписи в файл с константами
- Попытаться не пользоваться ифами (узнать на что их заменять и зачем)
- Добавить хеш-таблицу для хранения спичек в куче
- Добавить хеш-функцию определения в каком ряду был нажат курсор
- Разобраться с HINSANCE. Что это и зачем?
- После нажатия на спичку обновлять нужный прямоугольник, а не все.
- В GetNecessaryBrush() возвращать напрямую объект из функции

*/

#include "Functions.h"
#include "Constants.h"
#include "Field.h"

HINSTANCE hInst; //дескриптор экземпляра приложения. От фразы handle instance

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR WinName[] = _T("MainFrame");

int APIENTRY _tWinMain(HINSTANCE This, // Дескриптор текущего приложения
	HINSTANCE Prev, // В современных системах всегда 0
	LPTSTR cmd, // Командная строка
	int mode) // Режим отображения окна
{
	HWND hWnd; // Дескриптор главного окна программы
	MSG msg; // Структура для хранения сообщения
	WNDCLASS wc; // Класс окна
				 // Определение класса окна
	wc.hInstance = This;
	wc.lpszClassName = WinName; // Имя класса окна
	wc.lpfnWndProc = WndProc; // Функция окна
	wc.style = CS_HREDRAW | CS_VREDRAW; // Стиль окна
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); // Стандартная иконка
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // Стандартный курсор
	wc.lpszMenuName = NULL; // Нет меню
	wc.cbClsExtra = 0; // Нет дополнительных данных класса
	wc.cbWndExtra = 0; // Нет дополнительных данных окна
					   // Заполнение окна белым цветом
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	if (!RegisterClass(&wc)) return 0; // Регистрация класса окна

	// Создание окна
	hWnd = CreateWindow(WinName, // Имя класса окна
		_T("Каркас Windows-приложения"), // Заголовок окна
		WS_OVERLAPPEDWINDOW, // Стиль окна
		CW_USEDEFAULT,// x
		CW_USEDEFAULT,// y
		CW_USEDEFAULT,// Width
		CW_USEDEFAULT,// Height
		HWND_DESKTOP, // Дескриптор родительского окна
		NULL, // Нет меню
		This, // Дескриптор приложения
		NULL); // Дополнительной информации нет

	ShowWindow(hWnd, mode); //Показать окно
							// Цикл обработки сообщений
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);// Функция трансляции кодов нажатой клавиши
		DispatchMessage(&msg); // Посылает сообщение функции WndProc()
	}
	return 0;
}


// Оконная функция вызывается операционной системой
// и получает сообщения из очереди для данного приложения
LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{ // Обработчик сообщений
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
	// Обработка сообщения по умолчанию
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
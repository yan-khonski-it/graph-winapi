#include "KWnd.h"

KWnd::KWnd(
		LPCSTR windowName, HINSTANCE hInstance, int CmdShow,
		LRESULT (WINAPI * pWndProc) (HWND, UINT, WPARAM, LPARAM),
		LPCSTR menuName,
		int x, int y,
		int width, int height,
		UINT classStyle,
		DWORD windowStyle,
		HWND hParent)
{
	char szClassName[] = " Class name. ";


/////////////////////////////////////////////////////////////////////
	//Заполняем структуру класса окна.

	wc.cbSize = sizeof(wc);
	wc.style = classStyle;
	wc.lpfnWndProc = pWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION );//IDI_APPLICATION .
	wc.hCursor = LoadCursor(NULL, IDC_ARROW );//IDC_ARROW.
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //(HBRUSH) - Преобразование к типу HBRUSH.
	wc.lpszMenuName = menuName; //Пока нет меню.
	wc.lpszClassName = szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION );/*IDI_ERROR*/ /*IDI_QUESTION*/ //Другие иконки.

//////////////////////////////////////////////////////////////////////
	//Регестрируем класс окна.

	if (!RegisterClassEx(&wc))
	{
		char msg[100] = " Can't register class: ";
		strcat(msg, szClassName);
		MessageBox(NULL, msg, "ERROR", MB_OK);
		return;
	}

/////////////////////////////////////////////////////////////////////
	//Создаём основное окно приложения.

	hWnd = CreateWindow(
		szClassName, windowName, windowStyle,
		x, y, width, height,
		hParent, (HMENU) NULL,
		hInstance, NULL
	);

	if (!hWnd)
	{
		char text[100] = " Can't create main window ";
		strcat(text, szClassName);
		MessageBox(NULL, text, "ERROR", MB_OK);
		return;
	}
/////////////////////////////////////////////////////////////////////
	//Показываем окно.
	
	ShowWindow(hWnd, CmdShow);
	//UpdateWindow(hMainWnd);	//Можно без этого.
}


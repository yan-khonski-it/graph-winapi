#pragma once
#include <windows.h>

class KWnd
{

protected:

	HWND hWnd;
	WNDCLASSEX wc;

public:

	KWnd(
		LPCSTR windowName, HINSTANCE hInstance, int CmdShow,
		LRESULT (WINAPI * pWndProc) (HWND, UINT, WPARAM, LPARAM),
		LPCSTR menuName = NULL,
		int x = CW_USEDEFAULT, int y = 0,
		int width = CW_USEDEFAULT, int height = 0,
		UINT classStyle = CS_HREDRAW | CS_VREDRAW,
		DWORD windowStyle = WS_OVERLAPPEDWINDOW,
		HWND hParent = NULL
		);

	HWND GethWnd()
	{
		return hWnd;
	}

	~KWnd(void)
	{
	}
};

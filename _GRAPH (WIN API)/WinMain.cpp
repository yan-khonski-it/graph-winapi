#include "solution.h"



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdline, int nCmdShow)
{
	MSG msg;
	KWnd mainWnd(" G R A P H  ", hInstance, nCmdShow, WndProc, MAKEINTRESOURCE(IDR_MENU1), 0, 0, 1200, 700);
	
	while(GetMessage(& msg, NULL, 0, 0))
	{
		TranslateMessage(& msg);	//Обработка данных с клавиатуры.
		DispatchMessage(& msg);		//Передаёт структуру MSG обратно в ОС.
	}
	return msg.wParam;
}
#include "solution.h"



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdline, int nCmdShow)
{
	MSG msg;
	KWnd mainWnd(" G R A P H  ", hInstance, nCmdShow, WndProc, MAKEINTRESOURCE(IDR_MENU1), 0, 0, 1200, 700);
	
	while(GetMessage(& msg, NULL, 0, 0))
	{
		TranslateMessage(& msg);	//��������� ������ � ����������.
		DispatchMessage(& msg);		//������� ��������� MSG ������� � ��.
	}
	return msg.wParam;
}
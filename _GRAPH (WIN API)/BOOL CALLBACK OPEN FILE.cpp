#include "solution.h"
#include "CONSTANTS.h"


extern char * filename;

BOOL CALLBACK Open_the_file(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	char * buffer = NULL;
	UINT check_up = 0;
	switch (uMsg) 
	{
	
	case WM_COMMAND:

		switch (LOWORD(wParam))
		{

		case IDOK:
			buffer = new char [80];
			buffer[0] = '\0';
			check_up = GetDlgItemText(hDlg, IDC_EDIT2, buffer, 80);
			buffer[strlen(buffer)] = '\0';
			
			filename = buffer;
			EndDialog(hDlg, 0);
			return FALSE;

		case IDCANCEL:
			EndDialog(hDlg, 0);
			return FALSE;

		case (IDC_BUTTON1):
			buffer = new char [80];
			buffer[0] = '\0';
			strcpy(buffer, "input.txt");
			
			
			filename = buffer;
			EndDialog(hDlg, 0);
			return FALSE;
		}
		break;

	}

	return FALSE;
}
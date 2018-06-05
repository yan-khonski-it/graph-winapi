#include "solution.h"
#include "CONSTANTS.h"


extern unsigned int interval;
extern int ID_from, ID_to;



BOOL CALLBACK show_the_minimal_distance(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	char * buffer = NULL;
	switch (uMsg) 
	{

	case (WM_INITDIALOG):
		buffer = new char [80];
		itoa(ID_from, buffer, 10);
		SetDlgItemText(hDlg, IDC_DLG4_from, buffer); 
		itoa(ID_to, buffer, 10);
		SetDlgItemText(hDlg, IDC_DLG4_to, buffer);
		if (interval <= (unsigned int) MAX_INTERVAL)
			itoa(interval, buffer, 10);
		else
			strcpy(buffer, " It isn't possible. No such way. ");
		SetDlgItemText(hDlg, IDC_EDIT_RESULT, buffer); 
		delete [] buffer;
		return TRUE;

	case WM_COMMAND:

		switch (LOWORD(wParam))
		{

		case (IDOK4):
			EndDialog(hDlg, 0);
			return TRUE;
		}
	}
	return FALSE;
}
#include "solution.h"
#include "CONSTANTS.h"



extern int ID_from, ID_to;



BOOL CALLBACK Find__the_shortest_way(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int _ID_from = 0, _ID_to = 0;
	int check_up = 0;
	char * buffer = NULL;


	switch (uMsg) 
	{
	
	case WM_COMMAND:

		switch (LOWORD(wParam))
		{

		case IDOK:
			buffer = new char [20];		//Buffer hold coordinates objects.
			buffer[0] = '\0';
			check_up = GetDlgItemText(hDlg, IDC_EDIT2, buffer, 80);
			buffer[strlen(buffer)] = '\0';
			if (check_up == 0)
			{
				MessageBox(NULL, " You've entered nothing. ", " ERROR ", NULL);
				delete [] buffer;
				EndDialog(hDlg, 0);
				return TRUE;
			}
			_ID_from = atoi(buffer);

			check_up = GetDlgItemText(hDlg, IDC_EDIT9, buffer, 80);
			buffer[strlen(buffer)] = '\0';
			if (check_up == 0)
			{
				MessageBox(NULL, " You've entered nothing. ", " ERROR ", NULL);
				delete [] buffer;
				EndDialog(hDlg, 0);
				return TRUE;
			}
			_ID_to = atoi(buffer);

			ID_from = _ID_from;
			ID_to = _ID_to;

			delete [] buffer;
			EndDialog(hDlg, 0);
			return TRUE;

		case IDCANCEL:
			EndDialog(hDlg, 0);
			return TRUE;
		}
		break;

	}

	return FALSE;
}
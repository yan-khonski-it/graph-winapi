#include "solution.h"
#include "CONSTANTS.h"


extern int new_edge_id1;
extern int new_edge_id2;


BOOL CALLBACK _Delete_edge(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	char * buffer = NULL;
	UINT check_up = 0;
	int new_id1 = 0;
	int new_id2 = 0;
	int new_weight = 0;

	switch (uMsg) 
	{
	
	case WM_COMMAND:

		switch (LOWORD(wParam))
		{

		case (IDOK_DELETE_EDGE):
			buffer = new char [80];
			buffer[0] = '\0';

			check_up = GetDlgItemText(hDlg, IDC_EDIT1_DELETE_EDGE, buffer, 80);
			buffer[strlen(buffer)] = '\0';
			new_id1 = atoi(buffer);
			new_edge_id1 = new_id1;

			check_up = GetDlgItemText(hDlg, IDC_EDIT2_DELETE_EDGE, buffer, 80);
			buffer[strlen(buffer)] = '\0';
			new_id2 = atoi(buffer);
			new_edge_id2 = new_id2;

			EndDialog(hDlg, 0);
			return FALSE;

		case (IDCANCEL_DELETE_EDGE):
			new_id1 = -1;
			new_edge_id1 = new_id1;
			new_edge_id2 = new_id1;
			EndDialog(hDlg, 0);
			return FALSE;

		
		}
		break;

	}

	return FALSE;
}

#include "solution.h"
#include "CONSTANTS.h"


extern int new_edge_id1;
extern int new_edge_id2;
extern int new_edge_weight;


BOOL CALLBACK _Add_edge(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
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

		case (IDOK_ADD_EDGE):
			buffer = new char [80];
			buffer[0] = '\0';
			check_up = GetDlgItemText(hDlg, IDC_EDIT_1_ADD_EDGE, buffer, 80);
			buffer[strlen(buffer)] = '\0';
			
			new_id1 = atoi(buffer);
			new_edge_id1 = new_id1;

			check_up = GetDlgItemText(hDlg, IDC_EDIT_2_ADD_EDGE, buffer, 80);
			buffer[strlen(buffer)] = '\0';
			new_id2 = atoi(buffer);
			new_edge_id2 = new_id2;

			check_up = GetDlgItemText(hDlg, IDC_EDIT_3_ADD_EDGE, buffer, 80);
			buffer[strlen(buffer)] = '\0';
			new_weight = atoi(buffer);
			new_edge_weight = new_weight;

			EndDialog(hDlg, 0);
			return FALSE;

		case (IDCANCEL_ADD_EDGE):
			new_id1 = -1;
			new_edge_id1 = new_id1;
			new_edge_id2 = new_id1;
			new_edge_weight = new_id1;
			EndDialog(hDlg, 0);
			return FALSE;

		
		}
		break;

	}

	return FALSE;
}

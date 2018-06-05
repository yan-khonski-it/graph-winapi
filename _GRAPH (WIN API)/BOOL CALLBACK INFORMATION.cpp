#include "solution.h"
#include "CONSTANTS.h"




BOOL CALLBACK Information(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) 
	{
	
	case WM_COMMAND:

		switch (LOWORD(wParam))
		{

		case (IDOK):
			EndDialog(hDlg, 0);
			return FALSE;

		}
		break;

	}

	return FALSE;
}
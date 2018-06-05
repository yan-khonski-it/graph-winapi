#include "solution.h"
#include "CONSTANTS.h"



extern int random_quantity_of_vertexes;
extern int random_quantity_of_edges;



BOOL CALLBACK CreateRandomGraph(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	char * buffer = NULL;
	UINT check_up = 0;
	int rand_qunt_of_vertexes = 0;
	int rand_qunt_of_edges = 0;

	switch (uMsg) 
	{
	
	case WM_COMMAND:

		switch (LOWORD(wParam))
		{

		case (IDOK_RANDOM_GRAPH):
			buffer = new char [80];
			buffer[0] = '\0';
			check_up = GetDlgItemText(hDlg, IDC_EDIT2_RANDOM_GRAPH_VERTEXES, buffer, 80);
			buffer[strlen(buffer)] = '\0';
			
			rand_qunt_of_vertexes = atoi(buffer);
			random_quantity_of_vertexes = rand_qunt_of_vertexes;

			check_up = GetDlgItemText(hDlg, IDC_EDIT3_RANDOM_GRAPH_EDGES, buffer, 80);
			buffer[strlen(buffer)] = '\0';
			rand_qunt_of_edges = atoi(buffer);
			random_quantity_of_edges = rand_qunt_of_edges;

			EndDialog(hDlg, 0);
			return FALSE;

		case (IDCANCEL_RANDOM_GRAPH):
			rand_qunt_of_vertexes = -1;
			rand_qunt_of_edges = -1;
			random_quantity_of_vertexes = rand_qunt_of_vertexes;
			random_quantity_of_edges = rand_qunt_of_edges;

			EndDialog(hDlg, 0);
			return FALSE;

		case (IDC_BUTTON1_RANDOM_GRAPH):
			srand((unsigned int )time (NULL));
			rand_qunt_of_vertexes = rand() % max_nodes + 1;
			rand_qunt_of_edges = rand() % max_edges + 1;
			random_quantity_of_vertexes = rand_qunt_of_vertexes;
			random_quantity_of_edges = rand_qunt_of_edges;

			EndDialog(hDlg, 0);
			return FALSE;

		
		}
		break;

	}

	return FALSE;
}
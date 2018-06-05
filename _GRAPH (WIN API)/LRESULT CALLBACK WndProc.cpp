#include "solution.h"
#include "CONSTANTS.h"

char * filename;
int ID_from, ID_to;
unsigned int interval;
int new_edge_id1;
int new_edge_id2;
int new_edge_weight;
int random_quantity_of_vertexes;
int random_quantity_of_edges;


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	UINT style;			//Style of the main window.
	static HINSTANCE hInst;
	RECT rect;
	HDC hDC, hMemoryDC;	//HMemoryDC needs to drow moving figure.
	PAINTSTRUCT ps;
	HICON hIcon, hIconSm;
	HGDIOBJ hBitmap;

	RECT clientArea;
	
	static int index_of_moving_vertex = 0;
	static bool moving_of_vertex = false;   //Will the vertex be moved.
	static int mouseX = 0, mouseY = 0, last_mouseX = 0, last_mouseY = 0;
	POINT coordinates_of_mouse;		//Coordinates of the pushed mouse.

	switch(uMsg)
	{
		
		int userReply;


	case (WM_CREATE):
		
		hInst = GetModuleHandle(NULL);			//Icon.

		hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));
		hIconSm = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON1),
			IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
		SetClassLong(hWnd, GCL_HICON, (LONG)hIcon);
		SetClassLong(hWnd, GCL_HICONSM, (LONG)hIconSm);

		style = GetClassLong(hWnd, GCL_STYLE);
		SetClassLong(hWnd, GCL_STYLE, style | CS_DBLCLKS);			//For the processing a message DBLCLKS.

		break;

	case (WM_PAINT):	//Часть или вся клиентская область недействительна. Перерисовать.
		hDC = BeginPaint(hWnd, & ps);

		hMemoryDC = CreateCompatibleDC(hDC);		//Virtua graphic device.
		SetGraphicsMode(hMemoryDC, GM_ADVANCED);
		
		GetClientRect(hWnd, &clientArea);

		hBitmap = CreateCompatibleBitmap(hDC, clientArea.right-clientArea.left,clientArea.bottom-clientArea.top);
		(HGDIOBJ)SelectObject(hMemoryDC, hBitmap);	//We draw in hMemoryDC, but then it redraws to hDC.

		FillRect(hMemoryDC, &clientArea, 0);	

		
		G.drowGraph(hMemoryDC);
		if ( (interval < MAX_INTERVAL) && (interval > 0) )
			G._show_the_shortest_way(hMemoryDC);

		GetClientRect(hWnd, & rect);

		BitBlt(hDC, 0,0, clientArea.right-clientArea.left,clientArea.bottom-clientArea.top,hMemoryDC,0,0,SRCCOPY);		//Copying contains from hMemoryDC to hDC.
		
		DeleteDC(hMemoryDC);
		DeleteObject(hBitmap);
		EndPaint(hWnd, &ps);		//Освободить контекст у-ва.
		break;

	case (WM_CLOSE):
		userReply = MessageBox(hWnd, "Do you want to exit?", "", MB_YESNO | MB_ICONQUESTION);
		if (userReply == IDYES)
		{	
			DestroyWindow(hWnd);
		}
		break;

	case (WM_DESTROY):
		PostQuitMessage(0);
		break;

	case (WM_COMMAND):

		switch (LOWORD(wParam)) 
		{
		case (ID_FILE_OPEN40001):
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hWnd, Open_the_file);
			if (filename != NULL)
			{
				G.read(filename);
				delete [] filename;
				filename = NULL;
			}
			break;

		case (ID_FILE_EXIT):
			SendMessage(hWnd, WM_CLOSE, wParam, lParam);
			break;

		case (ID_GRAPH_SEARCINGOFTHESHORERWAY):
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Find__the_shortest_way);

			interval = G.search_the_shortest_way(ID_from, ID_to);
			if (interval != 0)
			{	
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG4), hWnd, show_the_minimal_distance);
				G.set_way(ID_from, ID_to);	
			}

			ID_from = 0;
			ID_to = 0;
			break;

		case (ID_GRAPH_DELETEGRAPH):
			G.destroy();
			break;

		case (ID_SAVE):
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG3), hWnd, Save_file);
			if (filename != NULL)
			{
				G.save(filename);
				delete [] filename;
				filename = NULL;
			}
			break;


		case (ID_GRAPH_ADDVERTEX):
			G.add_vertex();
			break;

		case(ID_GRAPH_ADDEDGE):
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG6), hWnd, _Add_edge);
			if ((new_edge_id1 != -1) && (new_edge_id2 != -1) && (new_edge_weight > 0))
				G.add_edge(new_edge_id1, new_edge_id2, new_edge_weight);

			new_edge_id1 = -1;
			new_edge_id2 = -1;
			new_edge_weight = -1;
			break;

		case (ID_GRAPH_DELETE_EDGE):
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG7_DELETE_EDGE), hWnd, _Delete_edge);
			if (	(new_edge_id1 != -1) && (new_edge_id2 != -1)	)
				G.delete_edge(new_edge_id1, new_edge_id2);
			break;

		case (ID_GRAPH_RANDOMGRAPH):
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG7_RANDOM_GRAPH), hWnd, CreateRandomGraph);
			if ((random_quantity_of_vertexes != -1) && (random_quantity_of_edges != -1))
			{
				G.create_rand_graph(random_quantity_of_vertexes, random_quantity_of_edges);
				random_quantity_of_vertexes = -1;
				random_quantity_of_edges = -1;
			}
			break;

		case (ID_INFORMATION_HELP):
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG8_HELP), hWnd, Information);
			break;

		case (ID_INFORMATION_ABOUT):
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG9_ABOUT), hWnd, Information);
			break;
		}
		if (GetClientRect(hWnd, &clientArea))
				InvalidateRect(hWnd, &clientArea, 0);
		
		break;
	

	case (WM_LBUTTONDOWN):
		last_mouseX = LOWORD(lParam);
		last_mouseY = HIWORD(lParam);
		coordinates_of_mouse.x = last_mouseX;
		coordinates_of_mouse.y = last_mouseY;

		index_of_moving_vertex = G.indexMovingVertex(coordinates_of_mouse);
		if (index_of_moving_vertex == -1)
			moving_of_vertex = false;
		else
			moving_of_vertex = true;
		break;

	case (WM_LBUTTONUP):
		moving_of_vertex = false;
		if (GetClientRect(hWnd, &clientArea))
				InvalidateRect(hWnd, &clientArea, 0);
		break;

	case (WM_MOUSEMOVE):
		if (moving_of_vertex == false)
			break;
		mouseX = LOWORD(lParam);
		mouseY = HIWORD(lParam);
		POINT new_mouse;
		new_mouse.x = mouseX;
		new_mouse.y = mouseY;

		G.moveVertex(index_of_moving_vertex, new_mouse);

		last_mouseX = mouseX;
		last_mouseY = mouseY;
		if (GetClientRect(hWnd, &clientArea))
			InvalidateRect(hWnd, &clientArea, 0);
		break;

	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);

	}
	return 0;
}
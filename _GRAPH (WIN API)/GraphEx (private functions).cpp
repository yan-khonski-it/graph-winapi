#include "GraphEx.h"



void GraphEx::draw_edge(int index, HDC hdc)
{
	char * weight_of_edge = NULL;
	int x1 = 0, y1 = 0;
	int x2 = 0, y2 = 0;
	int x3 = 0, y3 = 0;
	int id_1 = 0, id_2 = 0;

	if ( (index < quantity_of_edges) && (index < quantity_of_edges) && (index >= 0) && (index >= 0) )
	{
		weight_of_edge = new char [10];
		weight_of_edge[0] = '\0';
		x1 = node[edge[index].id1].centre.x;
		y1 = node[edge[index].id1].centre.y;
		x2 = node[edge[index].id2].centre.x;
		y2 = node[edge[index].id2].centre.y;
		MoveToEx(hdc, x1, y1, NULL);
		LineTo(hdc, x2, y2);
		x3 = (x1 + x2) / 2;
		y3 = (y1 + y2) / 2;	
		_itoa  (edge[index].weg, weight_of_edge, 10);
		TextOut(hdc, x3, y3, weight_of_edge, strlen(weight_of_edge));
		delete [] weight_of_edge;
	}
}



void GraphEx::replace_graph()
{
	for (int i = 0; i < quantity_of_vertexes; i++)
	{
		node[i].minWay = -1;
		node[i].wayFrom = -1;
	}
	_ID_from = _ID_to = 0;
}


bool GraphEx::is_posible_to_add_such_vertex(int ID)
{
	if (quantity_of_vertexes + 1 >= MAX_NODES)
	{
		MessageBox(NULL, " There are too many vertex in the graph. ", " ERROR ", NULL);
		return false;
	}
	return true;
}


bool GraphEx::is_posible_to_add_such_edge(int _id1, int _id2, int _weight)
{
	if (	( quantity_of_edges + 1 >= C_n_k(quantity_of_vertexes, quantity_of_vertexes - 2) ) || (quantity_of_edges >= MAX_EDGES)	)
	{
		MessageBox(NULL, " There are too many edges in the graph. ", " ERROR ", NULL);
		return false;
	}
	if (_weight < 0)
	{
		MessageBox(NULL, " It isn't possible to add such edge. ", " ERROR ", NULL);
		return false;
	}
	
	if ((_id1 >= quantity_of_vertexes) || (_id2 >= quantity_of_vertexes) || (_id1 < 0) || (_id2 < 0))
	{
		MessageBox(NULL, " It isn't possible to add such edge. ", " ERROR ", NULL);
		return false;
	}
	if (_id1 == _id2)
	{
		MessageBox(NULL, " It isn't possible to add such edge. ", " ERROR ", NULL);
		return false;
	}
	Edge New_edge(_id1, _id2, _weight);
	for (int i = 0; i < quantity_of_edges; i++)
		if (edge[i] == New_edge)
		{
			MessageBox(NULL, " There is such edge in the graph. ", " ERROR ", NULL);
			return false;
		}
	return true;
}


bool GraphEx::is_posible_to_add_such_edgeEx(const Edge & edge1)
{
	if (	( quantity_of_edges + 1 >= C_n_k(quantity_of_vertexes, quantity_of_vertexes - 2) ) || (quantity_of_edges >= MAX_EDGES)	)
		return false;
	
	if (edge1.weg <= 0)
		return false;
	
	
	if ((edge1.id1 >= quantity_of_vertexes) || (edge1.id2 >= quantity_of_vertexes) || (edge1.id1 < 0) || (edge1.id2 < 0))
		return false;
	if (edge1.id1 == edge1.id2)
		return false;

	for (int i = 0; i < quantity_of_edges; i++)
		if (edge[i] == edge1)
			return false;
		
	return true;
}
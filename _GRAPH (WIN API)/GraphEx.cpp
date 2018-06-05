#include "GraphEx.h"


GraphEx::~GraphEx()  
{
	 
}


void GraphEx::drowGraph(HDC hdc)
{
	for (int i = 0; i < quantity_of_edges; i++)
		draw_edge(i, hdc);
	for (int i = 0; i < quantity_of_vertexes; i++)
		node[i].drow_Vertex(hdc);
}



GraphEx::GraphEx()
{
	replace_graph();
	initialised = false;
	MAX_NODES = max_nodes;
	MAX_EDGES = max_edges;
	quantity_of_vertexes = quantity_of_edges = 0;
}


void GraphEx::read(const char * filename)
{
	if (initialised == true)
		return;
	else
	{	
		if (graph_read(filename) == true)
		{
			initialised = true;
			replace_graph();
		}
		else
			initialised = false;
	}
}



int GraphEx::indexMovingVertex(POINT coordinates_of_mouse)
{
	for (int i = 0; i < (int) node.size(); i++)
	{
		if (node[i].the_vertex_is_selected(coordinates_of_mouse) == true)
			return i;
	}
	return -1;
}


void GraphEx::moveVertex(int index, POINT new_coordinates)
{
	node[index].centre = new_coordinates;
}



void GraphEx::destroy()
{
	node.clear();
	edge.clear();
	initialised = false;
	quantity_of_vertexes = quantity_of_edges = 0;
}



void GraphEx::save(const char * filename)
{
	if (graph_save(filename) == false)
		MessageBox(NULL, " File have failed to save. ", " ERROR ", NULL);
}



unsigned int GraphEx::search_the_shortest_way(int id1, int id2)
{
	replace_graph();
	if (id1 == id2)
		return 0;
	int i = 0;
	for (i = 0; i < (int) node.size(); i++)
	{
		if (node[i].index == id1)
			break;
	}
	if (i >= (int) node.size())
	{
		MessageBox(NULL, " There is not such vertex in the graph. ", " ERROR ", NULL);
		return 0;
	}
	dijkstra(i);
	unsigned interval = -1;
	for (i = 0; i < (int) node.size(); i++)
	{
		if (node[i].index == id2)
			break;
	}
	if (i < (int) node.size())
	{
		if (node[i].minWay < MAX_INTERVAL)
			interval = node[i].minWay; 
		return interval;
	}
	else
		return 0;
}






void GraphEx::set_way(int id1, int id2)
{
	_ID_from = id1;
	_ID_to = id2;
}



void GraphEx::_show_the_shortest_way(HDC hdc)
{
	int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
	if (_ID_from == _ID_to)
		return;
	int tmp_ID = _ID_to;

	if ( (_ID_to < 0) || (_ID_to >= quantity_of_vertexes) )
		return;
	x1 = node[_ID_to].centre.x;
	y1 = node[_ID_to].centre.y;
	HPEN hPen, hOldPen;
	hPen = CreatePen(PS_SOLID, 3, RGB(255, 0,0));
	hOldPen = (HPEN) SelectObject(hdc, hPen);
	while (tmp_ID != _ID_from)
	{
		tmp_ID = node[tmp_ID].wayFrom;
		if ((tmp_ID < 0) || (tmp_ID >= quantity_of_vertexes) )
			return;
		x2 = node[tmp_ID].centre.x;
		y2 = node[tmp_ID].centre.y;
		MoveToEx(hdc, x1, y1, NULL);
		LineTo(hdc, x2, y2);
		x1 = x2;
		y1 = y2;	
	}

	hPen = (HPEN) SelectObject(hdc, hOldPen);
	DeleteObject(hPen);
	
}


void GraphEx::add_vertex()
{
	int ID = quantity_of_vertexes;
	if (!is_posible_to_add_such_vertex(ID))
		return;
	Node new_node(ID);
	node.push_back(new_node);
	quantity_of_vertexes = (int) node.size();
	if (initialised == false)
		initialised = true;
}


void GraphEx::add_edge(int _id1, int _id2, int _weight)
{
	if (is_posible_to_add_such_edge(_id1, _id2, _weight) == false)
		return;
	Edge new_edge(_id1, _id2, _weight);
	edge.push_back(new_edge);
	quantity_of_edges = edge.size();
	replace_graph();
}


int GraphEx::_quantity_of_vertexes()
{
	return quantity_of_vertexes;
}


int GraphEx::_quantity_of_edges()
{
	return quantity_of_edges;
}


void GraphEx::delete_edge(int _id1, int _id2)
{
	if (_id1 == _id2)
	{
		MessageBox(NULL, " There isn't such edge. ", " ERROR ", NULL);
		return;
	}
	if ((_id1 >= quantity_of_edges) || (_id1 < 0) || (_id2 >= quantity_of_edges) || (_id2 < 0))
	{
		MessageBox(NULL, " There isn't such edge. ", " ERROR ", NULL);
		return;
	}

	Edge del_edge(_id1, _id2, 10);
	for (int i = 0; i < quantity_of_edges; i++)
	{
		if (edge[i] == del_edge)
		{
			if (i != quantity_of_edges - 1)
				edge[i] = edge[quantity_of_edges - 1];
			edge.pop_back();
			quantity_of_edges = (int) edge.size();
			return;
		}
	}
	MessageBox(NULL, " There isn't such edge. ", " ERROR ", NULL);
}


void GraphEx::create_rand_graph(int _quantity_of_vertexes, int _quantity_of_edges)
{
	if (initialised == true)
		return;
	if (_quantity_of_edges > C_n_k(_quantity_of_vertexes, _quantity_of_vertexes - 2))
	{
		MessageBox(NULL, " It's impossible to bild such graph. ", " ERROR ", NULL);
		return;
	}

	if ((_quantity_of_vertexes <= 0) || (_quantity_of_vertexes > max_nodes) || (_quantity_of_edges > max_edges) || (_quantity_of_edges <= 0))
	{
		MessageBox(NULL, " It's impossible to bild such graph. ", " ERROR ", NULL);
		return;
	}

	srand((unsigned int )time (NULL));
	Node rand_node;
	for (int i = 0; i < _quantity_of_vertexes; i++)
	{
		rand_node.centre.x = rand() % 851 + 15;
		rand_node.centre.y = rand() % 551 + 15;
		rand_node.minWay = -1;
		rand_node.wayFrom = -1;
		rand_node.index = i;
		node.push_back(rand_node);
	}
	quantity_of_vertexes = (int) node.size();	
	
	Edge rand_edge;
	for (int i = 0; i < _quantity_of_edges; i++)
	{
		rand_edge.weg = rand() % 1001;
		rand_edge.id1 = rand() % _quantity_of_vertexes;
		rand_edge.id2 = rand() % _quantity_of_vertexes;
		if ( is_posible_to_add_such_edgeEx(rand_edge) == true)
			edge.push_back(rand_edge);
	}

	
	quantity_of_edges = edge.size();
	initialised = true;
}


void GraphEx::drow_GraphEx(HDC hdc)
{
}
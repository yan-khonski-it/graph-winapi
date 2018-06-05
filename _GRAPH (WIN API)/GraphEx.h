#pragma once
#include <Windows.h>
#include "_graph (dima).h"
#include "CONSTANTS.h"
#include "number.h"


class GraphEx :
	public graph
{

private:

	int MAX_NODES;
	int MAX_EDGES;
	bool initialised;
	int _ID_from;
	int _ID_to;

public:

	int _quantity_of_vertexes();
	int _quantity_of_edges();
	void read(const char * filename);
	void drowGraph(HDC hdc);
	GraphEx();
	~GraphEx();
	int indexMovingVertex(POINT coordinates_of_mouse);
	void moveVertex(int index, POINT new_coordinates);
	void destroy();
	void save(const char * filename);
	unsigned int search_the_shortest_way(int id1, int id2);
	void _show_the_shortest_way(HDC hdc);
	void set_way(int id1, int id2);
	void drow_GraphEx(HDC hdc);
	void add_vertex();
	void add_edge(int _id1, int _id2, int _weight);
	void delete_edge(int _id1, int _id2);
	void create_rand_graph(int _quantity_of_vertexes, int _quantity_of_edges);


private:

	void replace_graph();
	void draw_edge(int index, HDC hdc);
	bool is_posible_to_add_such_vertex(int ID);
	bool is_posible_to_add_such_edge(int _id1, int _id2, int _weight);
	bool is_posible_to_add_such_edgeEx(const Edge & edge1);
};


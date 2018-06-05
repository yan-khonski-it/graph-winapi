#pragma once
#include <iostream> 
#include <fstream>
#include <vector>
#include <stack>
#include <Windows.h>
#include <time.h>
#include <string>
using namespace std;
int const d=81;

int massiv_slov(char string[], char ** words); // разделяет строку string на слова и заполняет ими массив  words

 
struct Node
{
	unsigned int minWay;
	int wayFrom; //index peaks, from which we came to this
	int index;
	POINT centre;

	void drow_Vertex(HDC hdc)
	{	
		Ellipse(hdc, centre.x - 15, centre.y - 15, centre.x + 15, centre.y + 15);
		char * Name = new char [10];
		_itoa  (index, Name, 10);
		TextOut(hdc, centre.x - 5, centre.y - 7, Name, strlen(Name));
		delete [] Name;
	}


	bool the_vertex_is_selected(POINT coordinates_of_mouse)
	{
		return ((coordinates_of_mouse.x - centre.x) * (coordinates_of_mouse.x - centre.x) + (coordinates_of_mouse.y - centre.y) * (coordinates_of_mouse.y - centre.y) <= 225);
	}


	bool operator == (const Node & node1)
	{
		return (index == node1.index);
	}


	Node(int ID)
	{
		srand((unsigned int )time (NULL));
		centre.x = rand() % 851 + 15;
		centre.y = rand() % 551 + 15;
		index = ID;
		minWay = -1;
		wayFrom = -1;
	}


	Node()
	{
	}
} ;


struct Edge
{
	int id1;
	int id2;
	int weg;

	Edge()
	{
	}


	Edge(int _id1, int _id2, int _weight)
	{
		id1 = _id1;
		id2 = _id2;
		weg = _weight;
	}


	Edge & operator = (const Edge & edge1)
	{
		if (this == & edge1)
			return * this;
		id1 = edge1.id1;
		id2 = edge1.id2;
		weg = edge1.weg;
		return * this;
	}


	bool operator == (const Edge & edge1)
	{
		if (edge1.id1 == edge1.id2)
			return false;
		int _id_1 = edge1.id1;
		int _id_2 = edge1.id2;
		bool answ1 = (	(_id_1 == id1) || (_id_1 == id2)	);
		bool answ2 = false;
		if (answ1 == true)
		{
			answ2 = (	(_id_2 == id1) || (_id_2 == id2)	);
			return answ2;
		}
		else
			return false;
	}
};

class graph
{

protected:

	int quantity_of_vertexes;				//Quantity of vertexes.
	int quantity_of_edges;				//Quantity of edges.
	vector<Node> node;
	vector<Edge> edge;

public:

	graph()
	{
		quantity_of_vertexes = 0;
		quantity_of_edges = 0;
	}


	virtual	~graph()
	{
		node.clear();
		edge.clear();
		quantity_of_vertexes = 0;
		quantity_of_edges = 0;
	}


	bool graph_read(const char*filename)
	{
		char*str=new char[100];
		int i=0;
		char *mas[100];
		FILE*u;
		int point;
		vector<Edge>::iterator iter=edge.begin();
		u=fopen(filename,"r");
		if (u == NULL)
		{
			MessageBox(NULL, " No such file. " , " ERROR ", NULL);
			return false;
		}
		fgets(str,80,u);
		quantity_of_vertexes=atoi(str);
		while(feof(u)==0)
		{
			Edge edge1;
			fgets(str,80,u);

			point=massiv_slov(str,mas);


			for(i=0;i<point;i++)
			{
			  
					if(i==2)
					{
						edge1.weg=atoi(mas[i]);
					}
					if(i==0)
					{

						edge1.id1=atoi(mas[i]);
					}
					if(i==1)
					{

						edge1.id2=atoi(mas[i]);
					}


				 
				
			}
			edge.push_back(edge1);
			 

		}
		 
		Node node1;
		srand((unsigned int )time (NULL));
		for(int i=0;i<quantity_of_vertexes;i++)
		{
			node1.index=i;
			node1.minWay=-1;
			node1.wayFrom=-1;
			node1.centre.x = rand() % 851 + 15;
			node1.centre.y = rand() % 551 + 15;
			node.push_back(node1);
		}

		quantity_of_edges = (int) edge.size();
		return true;

	}
	void dijkstra(int index)
	{
		stack<Node>st_n;
	//	vector<Node>::iterator n_iter=node.begin();
		vector<Edge>::iterator e_iter=edge.begin();
		node[index].minWay=0;
		 for_dijkstra(node[index],index,st_n,e_iter);

	}
	void for_dijkstra(Node a,int index,stack<Node>st_n,vector<Edge>::iterator e_iter)
	{
		for(   ; e_iter!=edge.end();e_iter++)
		{
			if((*e_iter).id1==index)
			{
				if(node[(*e_iter).id1].minWay+(*e_iter).weg<node[(*e_iter).id2].minWay)
				{
					node[(*e_iter).id2].minWay=(*e_iter).weg+node[(*e_iter).id1].minWay;
					node[(*e_iter).id2].wayFrom=index;
					st_n.push(node[(*e_iter).id2]);
				}

			}
			if((*e_iter).id2==index)
			{
				if(node[(*e_iter).id2].minWay+(*e_iter).weg<node[(*e_iter).id1].minWay)
				{
					node[(*e_iter).id1].minWay=(*e_iter).weg+node[(*e_iter).id2].minWay;
					node[(*e_iter).id1].wayFrom=index;
					st_n.push(node[(*e_iter).id1]);
				}

			}
		}
		if(st_n.size()!=0)
		{
			Node a=st_n.top();
			st_n.pop();
			for_dijkstra(a ,a.index, st_n,e_iter=edge.begin());
	    }
	}
	
	
	
	bool graph_save(const char*filename)
	{
		ofstream output;
		output.open(filename, ios::out);
		if (!output.is_open())
		{
			MessageBox(NULL, " Graph has not saved. ", " FATAL ERROR ", NULL);
			return false;
		}


		output << quantity_of_vertexes << endl;
		for (int i = 0; i < (int) edge.size(); i++)
			output << "{" << edge[i].id1 << ", " << edge[i].id2 << ", " << edge[i].weg << "}" << endl; 
		output.close();
		return true;
	}



	/*void print()
	{
		vector<Node>::iterator n_iter=node.begin();
		for(   ; n_iter!=node.end();n_iter++)
		{
			cout<<(*n_iter).index<<" :"<<(*n_iter).minWay<<" "<<(*n_iter).wayFrom;
			cout<<endl;
		}
	}*/

};




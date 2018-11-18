#pragma once
#include <string>
/*
 Melroy Dsouza
 Last edited: Nov 10, 2018
 Edge .h file
*/
class Vertex;
class Edge
{
public:
	//creates an edge using two vertex pointers and a weight for the edge.
	Edge(Vertex* from, Vertex* two, int weight);
	//sets the pointers for the two vertices to null.
	~Edge();
	//returns the weight of the edge.
	int getWeight();
private:
	//all private functions and var. are available to graph class.
	friend class graph;
	// The two vertexes the edge is connected to.
	Vertex *from{ nullptr };
	Vertex *to{ nullptr };
	int weight; //weight for the edge created
};


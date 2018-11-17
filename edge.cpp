/*
 Melroy Dsouza
 Last edited: Nov 10, 2018
 Edge .cpp file
*/

#include "edge.h"


//sets the two pointers to the classes variable and sets weight equal to the 
//params weight.
Edge::Edge(Vertex* from, Vertex* to, int weight)
{
	from = from;
	to = to;
	this->weight = weight;
}

// sets the two pointers to nulptr so edge points to nothing.
Edge::~Edge()
{
	from = nullptr;
	to = nullptr;
}
int Edge::getWeight()
{
	return weight;
}
//returns vertex the edge is directed to.


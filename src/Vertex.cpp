/*
 Melroy Dsouza
 Last edited: Nov 10, 2018
 Vertex .cpp file
*/

#include "vertex.h"

//creates a vertex with edge map, and a label and
//a visited boolean set to false.
Vertex::Vertex(const std::string & label1)
{
	label = label1;
	edges = new std::map<std::string, Edge*>();
	visited = false;
	edgeNum = 0;
}
//returns the name of the vertex.
std::string Vertex::getName()
{
	return label;
}
// creates edge and has its intial
// vertex equal to 'this' and have its pointing
// vertex equal to the Vertex* to.
bool Vertex::createEdge(Vertex* to, int weight)
{
	// exception when you create an edge that
	// points to itself or if the pointer already exists. Or, the to vertex is null
	std::string name = to->getName();
	if (this->getName() == to->getName() || edges->count(name) !=0 || to == nullptr) {
		return false;
	}
	Edge * ed = new Edge(this, to, weight);

	edges->insert(std::pair<std::string, Edge*>(name, ed));
	//check if addition happens
	//std::cout << "HI" << std::endl;
	edgeNum++;
	return true;
}

// deletes all edges 
//in the edge map and deletes edge map.
Vertex::~Vertex()
{

	for (auto it = edges->begin(); it != edges->end(); it++) {
		delete it->second;
	}

	delete edges;
	edges = nullptr;

}
//goes through the vertexes edge map and
//prints out the vertices the current vertex
//is connected to and the weight of those individual connections.
std::string Vertex::getAllEdges()
{
	std::string out = this->label + " All edges: ";
	for (std::map<std::string, Edge*>::iterator it = edges->begin(); it != edges->end(); it++) {
		out += it->first;
			out += "(";
			out += std::to_string(it->second->getWeight());
			out += ") ";
	}
	return out;
}
//deletes edge from the vertex if the connection exists in 
//the vertexes edge map. 
bool Vertex::deleteEdge(const std::string &toLabel)
{
	if (edges->count(toLabel) == 0) {
		return false;
	}
	std::map<std::string, Edge*>::iterator it; //for deleting key from the map.
	it =edges->find(toLabel);
	delete edges->at(toLabel);
	edges->erase(it);
	edgeNum--;
	return true;
}
//returns number of edges on the vertex.
int Vertex::getEdgeNum()
{
	return edgeNum;
}
//sets the vertex to visited or not based on param.
//used for BFS and DFS methods.
bool Vertex::setVisited(bool vis)
{
	visited = vis;
	return true;
}


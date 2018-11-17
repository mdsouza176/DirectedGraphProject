/*
 Melroy Dsouza
 Last edited: Nov 10, 2018
 Graph .h file.
*/

#include "graph.h"


//graph construc. does nothing.
Graph::Graph()
{
	

}

//deletes all vertices in the graph.
Graph::~Graph()
{
	for (auto it = vertices.begin(); it != vertices.end(); it++) {
		delete it->second;
	}
}
//returns the size of the vertex map
//which is equivalent to how many vertices
//are in the graph.
int Graph::NumberOfVertices() const
{
	return vertices.size();
}
//goes through vertex map
//and uses each vertexes function getEdgeNum
//to get the number of edges for each vertex and
//adds them up and returns that to give the
//overall number of edges in the graph.
int Graph::NumberOfEdges() const
{
	int sum = 0;
	for (auto it = vertices.begin(); it != vertices.end(); it++) {
		sum += vertices.at(it->first)->getEdgeNum();
	}
	return sum;
}
//finds vertex in the graph and uses the vertexes method
//getEdgeNum to get the number of edges for the single vertex.
int Graph::NumberOfEdges(const std::string & label) const
{
	if (vertices.count(label) == 0) {
		return -1;
	}
	std::string s = label;
	return vertices.at(label)->getEdgeNum();
}
//If the vertex does not exist in the
//vertex map, creates the vertex with the given label
//and adds that vertex to the vertex map.
bool Graph::AddVertex(const std::string & label)
{
	if (vertices.count(label) == 0) {
		Vertex* n = new Vertex(label);
		vertices[label] = n;
		
		return true;
	}
	return false;
}
//checks the vertex map to see if a
//vertex with the given label exists. 
bool Graph::HasVertex(const std::string & label) const
{
	if (vertices.count(label) == 0) {
		return false;
	}
	return true;
}
//checks for vertex in vertex map
//based on given label. Use's the vertex class method
//method getAllEdges to return a string of all the edges of that vertex.
std::string Graph::GetEdges(const std::string & label) const
{
	if (vertices.count(label) == 0) {
		return "";
	}
	return vertices.at(label)->getAllEdges();
}
//if the two vertices don't exist in the vertex map, create them
//using AddVertex. Then create edge from fromLabel to toLabel using
//createEdge method if the conditions for the two vertices
//to have an edge there meet.
bool Graph::Connect(const std::string & fromLabel, const std::string & toLabel, int edgeWeight)
{
	
	AddVertex(fromLabel);
	AddVertex(toLabel);
	 //checks if possible to make edge and makes it if true possible and returns true, else returns false.
	return vertices[fromLabel]->createEdge(vertices[toLabel], edgeWeight);
}
//first checks if the two edges are both in the vertex map. If they are,
//checks for the edge in the fromLabel's edge map, and if it exists, 
//deletes that edge.
bool Graph::Disconnect(const std::string & fromLabel, const std::string & toLabel)
{
	if (vertices.count(fromLabel) == 0 || vertices.count(toLabel) == 0) { //makes sure the two vertexes exist in the graph.
		return false;
	}

	return vertices[fromLabel]->deleteEdge(toLabel); //this returns based on whether there is a edge between 
													//the two vertices and if there is, deletes it and returns true, else false.
}
//Opens a .txt file if it exists and reads through the file
//which first has a number indicating how
//long the file is. The method runs through that
//many lines in the file and creates edges and
//vertices based on the file. Single Command: A  B  10
//Translations: Create if it does not exist and B if it doesn't,
//make edge from A to B with weight 10.
//conditions: The method does not allow for 
//creating an edge from a vertex to itself,
//it does not allow creating multiple edges between two vertices.
bool Graph::ReadFile(const std::string & filename)
{
	std::ifstream myFile;
	myFile.open(filename);
	if (!myFile.is_open()) {
		return false;
	}
	std::string temp = "";
	int lines = 0;
	std::getline(myFile, temp);
	lines = std::stoi(temp);
	for (int i = 0; i < lines; i++) {
		std::getline(myFile, temp);
		std::stringstream ss(temp);
		std::string f = "";
		std::string s = "";
		std::string w = "";
		int weight = 0;
		ss >> f >> s >> w;
		weight = std::stoi(w);
		if (s == f) {
			return false;
		}
		if (!this->HasVertex(s)) {
			this->AddVertex(s);
		}
		if (!this->HasVertex(f)) {
			this->AddVertex(f);
		}
		this->Connect(f, s, weight);
	}
	myFile.close();
	return true;
}
//first checks if the starting vertex exists in the vertex map,
//if it does, unvisits all vertices using the helper func.
//uses the recursive helper function dfsHelper to go through
//graph using the depth first search algorithm using 
//alphabet order to decide which direction to go and
//prints that path that goes through all the vertices.
void Graph::DFS(const std::string & startLabel, void visit(const std::string &))
{
	if (vertices.count(startLabel) == 0) {
		return;
	}
	unvisitVertices(); //first univist all vertices for DFS to start.
	std::cout << "DFS path: ";
	visit(startLabel);
	vertices.at(startLabel)->setVisited(true);
	dfsHelper(vertices[startLabel], visit);
	std::cout << std::endl;
}

//first checks if the vertex exists in the map
//if it does, unvisits all vertices in map.
//goes through map in breadth-first
//search algorithm using a queue to add
//all adjacent edges of current vertex which have
//not been visited into the queue and visiting
//all the vertices in the queue and printing that path.
void Graph::BFS(const std::string & startLabel, void visit(const std::string &))
{
	if (vertices.count(startLabel) == 0) {
		return;
	}
	unvisitVertices();
	std::cout << "BFS path: ";
	std::queue<Vertex*> vert;
	vert.push(vertices.at(startLabel));
	visit(startLabel);
	vertices.at(startLabel)->setVisited(true);
	while (!vert.empty()) {
		for (auto it = vert.front()->edges->begin(); it != vert.front()->edges->end(); it++) {
			if (!vertices.at(it->first)->visited) {
				vert.push(vertices.at(it->first));
				vertices.at(it->first)->setVisited(true);
				visit(it->first);
			}
		}
		vert.pop();
	}
	std::cout << std::endl;
}
//first checks if the starting vertex is in the vertex map.
//if it is, creates a set that keeps track of the vertex
//with min. distance from starting vertex.
//sets the weights in the graph to INF.
//adds starting label to the set with a weight of 0 since the distance to itself is 0.
//sets the weight map to correspond with that.
//The while loop then checks adjacent vertexes to
//the smallest weighted vertex in the set and modifies the 
//other vertices weights and adds them to the set if they get
//modified. This happens till the set is empty, meaning
//all vertices have been looked into and have the least distance
//to get to teh startingLabel.
void Graph::Dijkstra(const std::string & startLabel, std::map<std::string, int>& weights, std::map<std::string, std::string>& previous)
{
	if (vertices.count(startLabel) == 0) {
		return;
	}
	std::set<IV> setIds;
	for (auto it = vertices.begin(); it != vertices.end(); it++) {
		weights[it->first] = INT_MAX;
	}
	setIds.insert(std::make_pair(0, vertices[startLabel]));
	weights[startLabel] = 0;

	while (!setIds.empty()) {
		std::pair<int, Vertex*> temp = *(setIds.begin());
		setIds.erase(setIds.begin());
		for (auto it = temp.second->edges->begin(); it != temp.second->edges->end(); it++) {
			int weight = it->second->getWeight();
			std::string label = it->first;
			if (weights[label] > weights[temp.second->getName()] + weight) {
				if (weights.at(label) != INT_MAX) {
					setIds.erase(setIds.find(std::make_pair(weights[label], vertices[label])));
				}
			weights[label] = weights[temp.second->getName()] + weight;
			setIds.insert(std::make_pair(weights[label], vertices[label]));
			previous[label] = temp.second->getName();
			}

		}
	}
	std::cout << "Dijstra weights from O: ";
	for (auto it = weights.begin(); it != weights.end(); it++) {
		if (it->second != INT_MAX && it->first != startLabel) {
			std::cout << "[" << it->first << ":" << it->second << "]";
		}
	}
	std::cout << std::endl;
	std::cout << "Previous: ";
	for (auto it = previous.begin(); it != previous.end(); it++) {
		std::cout << "[" << it->first << ":" << it->second << "]";
	}
	std::cout << std::endl; 
}

//helper method that goes through
//vertex map and uses setVisited to 
//set all vertices to unvisited via. false.
//used for BFS and DFS.
void Graph::unvisitVertices()
{
	for (auto it = vertices.begin(); it != vertices.end(); it++) {
		it->second->setVisited(false);
	}
}
//recursive helper function that goes through 
//the graph using depth-first search from one vertex's
//edge to another until all vertices are visited.
void Graph::dfsHelper(Vertex * v, void visit(const std::string &))
{
	for (auto it = v->edges->begin(); it != v->edges->end(); it++) {
		if (!vertices.at(it->first)->visited ) {
			std::string s = it->first;
			visit(s);
			vertices.at(it->first)->setVisited(true);
			dfsHelper(vertices.at(it->first), visit);
		}
	}
}


//checks if the vertex is in the vertex and if true,
//returns a pointer to that vertex.
Vertex * Graph::findVertex(const std::string & vertexLabel) const
{
	if (vertices.count(vertexLabel) == 0) {
		return nullptr;
	}
	return vertices.at(vertexLabel);
}

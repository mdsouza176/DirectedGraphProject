/*
  Melroy Dsouza
  last edited: Nov 10, 2018
  main driver file for the graph project
  runs all the test method for the graph project.
*/



#include <iostream>
#include <string>
#include <map>
#include "graph.h"



using namespace std;
//tests the vertex classes createEdge method and
//sees if connections between edges are really created
//and if only a single version of a connection is allowed.
void testVertexConnect() {
	cout << "Test Vertex createEdges: " << endl;
	Vertex a("A");
	Vertex b("B");
	Vertex c("C");
	a.createEdge(&b, 20);
	a.createEdge(&c, 20);
	cout << "A Should have edges b and c: " << a.getAllEdges() << endl;
	cout << "B shoud have no edges: " << b.getAllEdges() << endl;
	cout << "SHould print 0, it prints: " << c.createEdge(&c, 20) << endl;
	cout << "Should print 0, it prints: " << a.createEdge(&c, 10) << endl;
	b.createEdge(&a, 20);
	cout << "B should now have an edge to A: "<<b.getAllEdges() << endl;
	cout << "A should have edges to B and C: " << a.getAllEdges() << endl;
	cout << endl << endl;
}
//tests the vertex classes delete edge method
//and how the number of edges for that vertex is correspondingly effected.
void testVertexDeleteEdges() {
	cout << "Test Vertex delete edges + edgeCount: " << endl;
	Vertex a("A");
	Vertex b("B");
	Vertex c("C");
	cout << "a, b, and c should have 0 edge count, Prints: " << (a.getEdgeNum() + b.getEdgeNum() + c.getEdgeNum()) << endl;
	a.createEdge(&b, 20); a.createEdge(&c, 20);
	cout << "A has 2 edges, should print 2, prints: " << a.getEdgeNum() << endl;
	cout <<"Should print 1, it prints: " << a.deleteEdge("B") << endl;
	cout << "A should only have c as its edge: "<< a.getAllEdges() << endl;
	cout << "Should print 0, it prints: " << a.deleteEdge("A") <<endl;
	cout << endl << endl;
}
//test the graphs add vertex method and if
//it adds only a single version of a vertex.
void testGraphAddVertex() {
	cout << "Test graph add vertices and number of vertices count: " << endl;
	Graph r1;
	cout << "It should print 0 for num of vertices, prints: " << r1.NumberOfVertices() << endl;
	r1.AddVertex("C"); r1.AddVertex("B"); r1.AddVertex("A");
	cout << "It should print 3, prints: " << r1.NumberOfVertices() << endl;
	cout <<"It should print 0, it prints: " << r1.AddVertex("A") << endl;
	cout << "It should print 3, it prints: "<< r1.NumberOfVertices() << endl;
	cout << endl << endl;
}
//tests the graphs has vertex method.
void testGraphHasVertex() {
	cout << "Test hasVertex method: " << endl;
	Graph r1;
	r1.AddVertex("A"); r1.AddVertex("B"); r1.AddVertex("C");
	cout << "should print 1, it prints: " << r1.HasVertex("A") << endl;
	cout << "Should print 0, it prints: " << r1.HasVertex("D") << endl;
	cout << endl << endl;
}
//checks wether graph can connect different vertices, create vertices
//if non-existent, and how the edge and vertex numbers are corespondingly
//effected.
void testGraphConnect() {
	cout << "Test graph connect method + edgeNum method + vertex count: " << endl;
	Graph r1;
	cout << "It should print 1, it prints: " <<r1.Connect("A", "B", 20) << endl;
	cout << "Vertex Count (Should be 2): " << r1.NumberOfVertices() << "  edges count(Should be 1): " <<r1.NumberOfEdges() <<endl;
	cout << "It should print 0, it prints: " << r1.Connect("A", "B", 20) << endl;
	cout << "It should print 1, it prints: " << r1.Connect("A", "C", 10) << endl;
	cout << "It should print 0, it prints: " << r1.Connect("A", "B", 5) << endl;
	cout << "It should print 1, it prints: " << r1.Connect("B", "A", 5) << endl;
	cout << "vertex count (3): " << r1.NumberOfVertices()<< "  edges count(3): " << r1.NumberOfEdges() << endl;
	cout << endl << endl;
}
//Tests whther disconnect gets rid of
//actual connections and how vertice and edge numbers are 
//effected as a result.
void testGraphDisconnect() {
	cout << "Test graph disconnect + edgeNum + vertex count: " << endl;
	Graph r1;
	cout << "Should print 1, it prints: " << r1.Connect("A", "C", 30) << endl;
	cout << "Should print 1, it prints: " << r1.Connect("D", "A", 4) << endl;
	cout << "vertex count(3): " << r1.NumberOfVertices() << "  edgeCount(2): " << r1.NumberOfEdges() << endl;
	cout << "Should print 0, it prints: " << r1.Disconnect("A", "D") << endl;
	cout << "Should print 1, it prints: " << r1.Disconnect("D", "A") << endl;
	cout << "vertex count(3): " << r1.NumberOfVertices() << "  edgecount(1): " << r1.NumberOfEdges() << endl;

	cout << endl << endl;
}
//visit function used for BFS adn DFS methods
void visit(const string& s) {
	cout << s;

}
//uses the sample graphs given
//plus spec sample graph to check
//whther the readfile function can
//correctly add vertices and edges to graph
//and then tries BFS adn DFS on spec. sample graph and see's if correct
//path is found.
void testGraphReadFile() {
	cout << "Test graph readFile + DfS and BFS: " << endl;
	Graph r1;
	r1.ReadFile("graph0.txt");
	cout << "Should print 3, it prints: " << r1.NumberOfEdges() << endl;
	cout << "Should print 3, it prints: " << r1.NumberOfVertices() << endl;
	Graph r2;
	r2.ReadFile("graph1.txt");
	cout << "Should print 9, it prints: " << r2.NumberOfEdges() << endl;
	cout << "Should print 10, it prints: " << r2.NumberOfVertices() << endl;
	Graph r3;
	r3.ReadFile("graph2.txt");
	cout << "Should print 24, it prints: " << r3.NumberOfEdges() << endl;
	cout << "Should print 21, it prints: " << r3.NumberOfVertices() << endl;
	Graph r4;
	r4.ReadFile("graph3.txt");
	cout << "Should print 10, it prints: " << r4.NumberOfEdges() << endl;
	cout << "Should print 7, it prints: " << r4.NumberOfVertices() << endl;
	cout << "Should print, OPRSTUQ, it prints: ";
	r4.DFS("O", visit);
	cout << "Should print, OPQRSTU, it prints: ";
	r4.BFS("O", visit);
	cout << endl << endl;
}
//uses spec example to test whether dijstra method works.
void testGraphDijstra() {
	cout << "Test Dijstra: " << endl;
	Graph r1;
	r1.ReadFile("graph3.txt");
	map<string, string> previous;
	map<string, int> weights;
	cout << "Test dijstra on spec. example: Should print: [P:5][Q:2][R:3][S:6][T:8][U:9]" << endl;
	r1.Dijkstra("O", weights, previous);
	cout << endl << endl;

}
// driver function that tests the states of graph and vertices
int main() {
	testVertexConnect();
	testVertexDeleteEdges();
	testGraphAddVertex();
	testGraphHasVertex();
	testGraphConnect();
	testGraphDisconnect();
	testGraphReadFile();
	testGraphDijstra();
	cin.get();
	return 0;
}
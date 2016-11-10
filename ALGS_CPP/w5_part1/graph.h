#ifndef __GRAPH_H_
#define __GRAPH_H_
#include <vector>
#include <list>

struct Neighbor
{
	int id;
	int weight;	
};

class Graph
{
public:
	Graph(int numVertex);
	Graph(Graph &p);
	void addEdge(int i, struct Neighbor);
	void printGraph();
	Graph& operator=(Graph &p);
	int  getVertices();
	std::list<struct Neighbor> adj(int v);

private:
	int numVertices;
	std::vector<std::list<struct Neighbor> > adjList;
};

#endif

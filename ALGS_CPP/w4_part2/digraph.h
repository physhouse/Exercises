#ifndef __DIGRAPH_H_
#define __DIGRAPH_H_
#include <vector>
#include <list>

struct Edge
{
	int from;
	int to;
	int weight;
};

class DiGraph
{
public:
	DiGraph(int numVertex);
	DiGraph(DiGraph &p);
	void addEdge(struct Edge);
	void printGraph();
	DiGraph& operator=(DiGraph &p);
	int  getVertices();
	int  floyd();

private:
	int numVertices;
	std::vector<std::list<struct Edge> > adjList;
	std::vector<std::vector<int> > dist;
};

#endif

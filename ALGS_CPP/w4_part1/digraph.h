#ifndef __DIGRAPH_H_
#define __DIGRAPH_H_
#include <vector>
#include <list>

struct Edge
{
	int from;
	int to;
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
	void postOrder();
	void normalDFS();
	void DFS(int v);
	void dfs(int v);
	int strongConnectedComponents();

private:
	int numVertices;
	std::vector<std::list<int> > adjList;
	std::vector<std::list<int> > revList;
	std::vector<bool> mark;
	std::vector<int> pOrder;
};

#endif

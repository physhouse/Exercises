#include "graph.h"
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <cstdlib>
#include <cstdio>

Graph::Graph(int n)
{
	numVertices = n;
	adjList.resize(n);
}

Graph::Graph(Graph& p)
{
	numVertices = p.numVertices;
	adjList.resize(numVertices);

	std::copy(p.adjList.begin(), p.adjList.end(), adjList.begin());
}

int Graph::getVertices()
{
	return numVertices;
}

Graph& Graph::operator=(Graph& p)
{
	numVertices = p.numVertices;
	adjList.resize(numVertices);

	std::copy(p.adjList.begin(), p.adjList.end(), adjList.begin());
	return *this;
}

void Graph::addEdge(int i, struct Neighbor n)
{
	adjList[i].push_back(n);
}

void Graph::printGraph()
{
	for (int i=0; i<numVertices; i++)
	{
		for (auto j = adjList[i].begin(); j != adjList[i].end(); j++)
		{
			printf("%d\t%d\n", j->id, j->weight);
		}
	}
}

std::list<Neighbor> Graph::adj(int nv)
{
	return adjList[nv];
}

/*int main()
{
	FILE* fp = fopen("edges.txt", "r");
	int nV, nE;
	fscanf(fp, "%d %d", &nV, &nE);
	Graph G(nV);

	struct Edge e;
	for (int i=0; i<nE; i++)
	{
		fscanf(fp, "%d %d %d", &e.from, &e.to, &e.weight);
		G.addEdge(e);
	}

	Graph H(G);
	//H.printGraph();

	Graph M = H;
	//M.printGraph();

	for (auto e : M.adj(100))
	{
		printf("%d\t%d\t%d\n", e.from, e.to, e.weight);
	}

	for (auto e : M.edges())
	{
		printf("%d\t%d\t%d\n", e.from, e.to, e.weight);
	}
	return 0;
}*/

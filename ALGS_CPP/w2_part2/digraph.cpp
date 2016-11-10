#include "digraph.h"
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <cstdlib>
#include <cstdio>

DiGraph::DiGraph(int n)
{
	numVertices = n;
	adjList.resize(n);
}

DiGraph::DiGraph(DiGraph& p)
{
	numVertices = p.numVertices;
	adjList.resize(numVertices);

	std::copy(p.adjList.begin(), p.adjList.end(), adjList.begin());
}

int DiGraph::getVertices()
{
	return numVertices;
}

DiGraph& DiGraph::operator=(DiGraph& p)
{
	numVertices = p.numVertices;
	adjList.resize(numVertices);

	std::copy(p.adjList.begin(), p.adjList.end(), adjList.begin());
	return *this;
}

void DiGraph::addEdge(Edge e)
{
	//int i = e.from - 1;  // p1
	//int j = e.to - 1;	// p1
	int i = e.from;
	int j = e.to;
	adjList[i].push_back(e);
	adjList[j].push_back(e);
}

void DiGraph::printGraph()
{
	for (int i=0; i<numVertices; i++)
	{
		for (auto j = adjList[i].begin(); j != adjList[i].end(); j++)
		{
			printf("%d\t%d\t%d\n", j->from, j->to, j->weight);
		}
	}
}

std::list<Edge> DiGraph::adj(int nv)
{
	return adjList[nv];
}

std::list<Edge> DiGraph::edges()
{
	std::list<Edge> edges;
	for (int i=0; i<numVertices; i++)
	{
		for (Edge e : adj(i))
		{
			int other;

			//if (i == e.from - 1) other = e.to - 1; //p1
			//else other = e.from - 1; //p1
			if (i == e.from) other = e.to;
			else other = e.from;

			if (other > i)
				edges.push_back(e);
		}
	}

	return edges;
}

/*int main()
{
	FILE* fp = fopen("edges.txt", "r");
	int nV, nE;
	fscanf(fp, "%d %d", &nV, &nE);
	DiGraph G(nV);

	struct Edge e;
	for (int i=0; i<nE; i++)
	{
		fscanf(fp, "%d %d %d", &e.from, &e.to, &e.weight);
		G.addEdge(e);
	}

	DiGraph H(G);
	//H.printGraph();

	DiGraph M = H;
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

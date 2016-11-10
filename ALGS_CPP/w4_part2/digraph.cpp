#include "digraph.h"
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <stack>
#include <cstdlib>
#include <cstdio>

DiGraph::DiGraph(int n)
{
	numVertices = n;
	adjList.resize(n);
	dist.resize(n);
	for (int i=0; i<n; i++)
		dist[i].resize(n);
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
	int i = e.from;
	int j = e.to;
	adjList[i].push_back(e);
}

void DiGraph::printGraph()
{
	for (int i=0; i<numVertices; i++)
	{
		for (auto j = adjList[i].begin(); j != adjList[i].end(); j++)
		{
			printf("%d\n", j->weight);
		}
	}
}

int DiGraph::floyd()
{
	for (int i=0; i<numVertices; i++)
	{
		for (int j=0; j<numVertices; j++)
		{
			if (i == j)
				dist[i][j] = 0;
			else
				dist[i][j] = 1000000;
		}
	}

	printf("passing 1\n");
	for (int i=0; i<numVertices; i++)
	{
		for (auto it = adjList[i].begin(); it != adjList[i].end(); it++)
		{
			int j = it->to;
			int w = it->weight;
			dist[i][j] = w;
		}
	}

	printf("passing 1\n");
	// Start the Dynamic Programming Subroutine
	int min = 1000000;
	for (int k=0; k<numVertices; k++)
		for (int i=0; i<numVertices; i++)
			for (int j=0; j<numVertices; j++)
			{
				if (dist[i][j] > dist[i][k] + dist[k][j])
				{
					dist[i][j] = dist[i][k] + dist[k][j];
					if (dist[i][j] < min)
						min = dist[i][j];
				}
			}

	// Check Negative Circle
	bool neg = false;
	for (int i=0; i<numVertices; i++)
	{
		if (dist[i][i] < 0)
		{
			neg = true;
			break;
		}
	}

	if (neg == true)
		return -100;
	else
		return min;
}

int main(int argc, char** argv)
{
	FILE* fp = fopen(argv[1], "r");
	int nV, nE;
	fscanf(fp, "%d %d", &nV, &nE);
	DiGraph G(nV);

	struct Edge e;
	for (int i=0; i<nE; i++)
	{
		int from, to, weight;
		fscanf(fp, "%d %d %d", &from, &to, &weight);
		e.from = from - 1;
		e.to = to - 1;
		e.weight = weight;
		G.addEdge(e);
	}

	printf("finished here\n");
	int answer = G.floyd();
	printf("answer = %d\n", answer);

	return 0;
}

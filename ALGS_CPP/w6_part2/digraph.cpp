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
	revList.resize(n);
	SCC.resize(n);
	mark.resize(n);
	for (int i=0; i<n; i++)
		mark[i] = false;
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
	adjList[i].push_back(j);
	revList[j].push_back(i);
}

void DiGraph::printGraph()
{
	for (int i=0; i<numVertices; i++)
	{
		for (auto j = adjList[i].begin(); j != adjList[i].end(); j++)
		{
			printf("%d\n", *j);
		}
	}
}

void DiGraph::postOrder()
{
	printf("preSize = %lu\n", pOrder.size());
	for (int i=0; i<numVertices; i++)
	{
		if (!mark[i])
			DFS(i);
	}
}


void DiGraph::DFS(int v)
{
	std::stack<int> p;
	p.push(v);
	mark[v] = true;

	while (!p.empty())
	{
		int top = p.top();
		//mark[top] = true;
		int count = 0;
		for (auto j = revList[top].begin(); j != revList[top].end(); j++)
		{
			if (!mark[*j])
			{
				p.push(*j);
				mark[*j] = true;
				count++;
				break;
			}
		}
		if (count == 0)
		{
			pOrder.push_back(top);
			p.pop();
		}
	}
}

/*void DiGraph::normalDFS()
{
	for (int i=0; i<numVertices; i++)
	{
		if (!mark[i])
			dfs(i);
	}
}*/

void DiGraph::dfs(int v, int scc)
{
	mark[v] = true;
	SCC[v] = scc;
	std::stack<int> p;
	p.push(v);

	int size = 0;

	while (!p.empty())
	{
		int top = p.top();
		int count = 0;
		for (auto j = adjList[top].begin(); j != adjList[top].end(); j++)
		{
			if (!mark[*j])
			{
				p.push(*j);
				mark[*j] = true;
				SCC[*j] = scc;
				count++;
				break;
			}
		}
		if (count == 0)
		{
			p.pop();
			size++;
		}
	}
	//printf("%d\n", size);
}

int DiGraph::strongConnectedComponents()
{
	printf("size = %lu\n", pOrder.size());

	int count = 0;
	for (int i=0; i<numVertices; i++)
		mark[i] = false;

	for (int j = pOrder.size()-1; j >= 0; j--)
	{
		int v = pOrder[j];
		if (!mark[v])
		{
			dfs(v, count);
			count++;
		}
	}

	for (int i=0; i<numVertices; i++)
	{
		printf("%d : %d\n", i+1, SCC[i]);
	}
	printf("components: %d\n", count);
	return count;
}

int DiGraph::twoSAT()
{
	postOrder();
	int result = strongConnectedComponents();
	for (int i=0; i<numVertices/2; i++)
	{
		if (SCC[2*i] == SCC[2*i+1])
			return i+1;
	}

	return -100;
}

/*int main(int argc, char** argv)
{
	FILE* fp = fopen(argv[1], "r");
	//FILE* fp = fopen("test.txt", "r");
	int nV = 875714;
	int nE = 5105043;
	//int nV = 13;
	//int nE = 22;
	DiGraph G(nV);

	struct Edge e;
	for (int i=0; i<nE; i++)
	{
		int from, to;
		fscanf(fp, "%d %d", &from, &to);
		e.from = from - 1;
		e.to = to - 1;
		G.addEdge(e);
	}

	G.postOrder();
	printf("post Order\n");
	int count = G.strongConnectedComponents();
	printf("answer = %d\n", count);

	return 0;
}*/

int main(int argc, char** argv)
{
	FILE* fp = fopen(argv[1], "r");
	int nE;
	fscanf(fp, "%d", &nE);
	int nV = 2 * nE;

	DiGraph G(nV);

	for (int i=0; i<nE; i++)
	{
		int v1, v2;
		fscanf(fp, "%d %d", &v1, &v2);
		// printf("%d %d\n", v1, v2);
		// build the DiGraph
		if (v1 < 0 && v2 < 0) //~xV~y == x -> ~y && y -> ~x
		{
			Edge e;
			e.from = 2*(-v1 - 1);
			e.to = 2*(-v2 - 1) + 1;
			G.addEdge(e);
			e.from = 2*(-v2 - 1);
			e.to = 2*(-v1 - 1) + 1;
			G.addEdge(e);
		}

		if (v1 > 0 && v2 > 0) // xVy == ~x -> y && ~y -> x
		{
			Edge e;
			e.from = 2*(v1 - 1) + 1;
			e.to = 2*(v2 - 1);
			G.addEdge(e);
			e.from = 2*(v2 - 1) + 1;
			e.to = 2*(v1 - 1);
			G.addEdge(e);
		}

		if (v1 < 0 && v2 > 0) // ~xVy == x -> y && ~y -> ~x
		{
			Edge e;
			e.from = 2*(-v1 - 1);
			e.to = 2*(v2 - 1);
			G.addEdge(e);
			e.from = 2*(v2 - 1) + 1;
			e.to = 2*(-v1 - 1) + 1;
			G.addEdge(e);
		}

		if (v1 > 0 && v2 < 0) // xV~y == ~x -> ~y && y -> x
		{
			Edge e;
			e.from = 2*(v1 - 1) + 1;
			e.to = 2*(-v2 - 1) + 1;
			G.addEdge(e);
			e.from = 2*(-v2 - 1);
			e.to = 2*(v1 - 1);
			G.addEdge(e);
		}
	}

	int result = G.twoSAT();
	printf("answer = %d\n", result);
	return 0;
}

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
	mark.resize(n);
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
		mark[i] = false;

	for (int i=0; i<numVertices; i++)
	{
		if (!mark[i])
			DFS(i);
	}

	printf("size = %lu\n", pOrder.size());
	for (int i=pOrder.size()-1; i >= 0; i--)
		printf("%d\n", pOrder[i]);
}


void DiGraph::DFS(int v)
{
	std::stack<int> p;
	p.push(v);
	mark[v] = true;

	while (!p.empty())
	{
		int top = p.top();
		int count = 0;
		for (auto j : revList[top])
		{
			if (mark[j] == false)
			{
				p.push(j);
				mark[j] = true;
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

void DiGraph::normalDFS()
{
	for (int i=0; i<numVertices; i++)
	{
		if (!mark[i])
			dfs(i);
	}
}

void DiGraph::dfs(int v)
{
	mark[v] = true;
	std::stack<int> p;
	p.push(v);

	int size = 0;

	while (!p.empty())
	{
		int top = p.top();
		int count = 0;
		for (auto j : adjList[top])
		{
			if (mark[j] == false)
			{
				p.push(j);
				mark[j] = true;
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
}

int DiGraph::strongConnectedComponents()
{
	printf("size = %lu\n", pOrder.size());
	/*for (int i=0; i<pOrder.size(); i++)
		printf("%d\n", pOrder[i]);

	printf("*************\n");*/

	int count = 0;
	for (int i=0; i<numVertices; i++)
		mark[i] = false;

	for (int j = pOrder.size()-1; j >= 0; j--)
	{
		int v = pOrder[j];
		if (!mark[v])
		{
			dfs(v);
			count++;
		}
	}
	return count;
}

int main()
{
	FILE* fp = fopen("SCC.txt", "r");
	//FILE* fp = fopen("mediumDG.txt", "r");
	int nV = 875714;
	int nE = 5105043;
	//int nV = 50;
	//int nE = 147;
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
}

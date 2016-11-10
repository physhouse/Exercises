#include "dijkstra.h"
#include "assert.h"
#include <queue>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <list>

#define INT_INFINITY 99999999

Dijkstra::Dijkstra(Graph& p) : G(p)
{
	int numVertices = p.getVertices();
	left = numVertices;
	dist.resize(numVertices);
	for (int i=0; i<numVertices; i++)
	{
		dist[i] = INT_INFINITY;
	}
	dist[0] = 0;

	visited.resize(numVertices);
	for (int i=0; i<numVertices; i++)
		visited[i] = false;
}

void Dijkstra::Solve()
{
	while (left > 0)
	{
		int min_v = INT_INFINITY;
		int candidate = INT_INFINITY;
		for (int i=0; i<G.getVertices(); i++)
		{
			if ((visited[i] == false) && dist[i] < min_v)
			{
				min_v = dist[i];
				candidate = i;
			}
		}

		if (candidate >=0 && candidate < G.getVertices())
			Scan(candidate);
		else
		{
			printf("something wrong \n");
			exit(-1);
		}
		left--;
	}

	printf("finished\n");
	printf("%d\n", dist[6]);
	printf("%d\n", dist[36]);
	printf("%d\n", dist[58]);
	printf("%d\n", dist[81]);
	printf("%d\n", dist[98]);
	printf("%d\n", dist[114]);
	printf("%d\n", dist[132]);
	printf("%d\n", dist[164]);
	printf("%d\n", dist[187]);
	printf("%d\n", dist[196]);
}

void Dijkstra::Scan(int nV)
{
	printf("nv: %d\n", nV);
	assert(visited[nV] == false);
	visited[nV] = true;

	for (auto E : G.adj(nV))
	{
		int w = E.id;
		if (dist[w] > dist[nV] + E.weight)
		{
			dist[w] = dist[nV] + E.weight; // Relax operation
		}
	}
}

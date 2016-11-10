#include "cluster.h"
#include "digraph.h"
#include "uf.h"
#include <queue>
#include <vector>
#include <cstdio>
#include <cstdlib>

cluster::cluster(DiGraph& P, int numVertices) : G(P), connect(numVertices)
{
	printf("start initilization\n");

	for (Edge e : P.edges())
	{
		//printf("edges: %d <--> %d\n", e.to, e.from);
		pq.push(e);
	}
}

int cluster::maxDistance(int size)
{
	printf("entering function\n");
	while (!pq.empty() && connect.getCount() > size)
	{
		Edge e = pq.top();
		pq.pop();
		if (!connect.connected(e.to - 1, e.from - 1))
		{
			printf("edges: %d <--> %d w %d cluster %d\n", e.to, e.from, e.weight, connect.getCount());
			connect.union_path(e.to - 1, e.from - 1);
		}
	}

	Edge solution = pq.top();
	return solution.weight;
}

int main(int argc, char** argv)
{
	printf("%s\n", argv[1]);
	FILE* fp = fopen(argv[1], "r");
	int nv;
	fscanf(fp, "%d", &nv);
	printf("nv = %d\n", nv);
	int ne = nv * (nv - 1) / 2;
	DiGraph P(nv);

	printf("reading started ne = %d\n", ne);
	for (int i=0; i<ne; i++)
	{
		Edge e;
		fscanf(fp, "%d %d %d", &e.from, &e.to, &e.weight);
		//printf("edges: %d <--> %d w %d\n", e.to, e.from, e.weight);
		P.addEdge(e);
	}
	fclose(fp);

	/*for (Edge e : P.edges())
	{
		printf("Reading edges: %d <--> %d\n", e.to, e.from);
	}*/
	printf("reading finished\n");

	cluster kruskal(P, nv);
	int answer = kruskal.maxDistance(3);
	printf("answer = %d\n", answer);
	
	return 0;
}

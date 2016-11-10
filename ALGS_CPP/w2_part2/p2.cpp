#include "cluster.h"
#include "digraph.h"
#include "uf.h"
#include <queue>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <unordered_map>

cluster::cluster(DiGraph& P, int numVertices) : G(P), connect(numVertices)
{
	printf("start initilization\n");

	for (Edge e : P.edges())
	{
		pq.push(e);
	}
}

int cluster::maxDistance(int size)
{
	printf("entering function\n");
	while (!pq.empty())
	{
		Edge e = pq.top();
		pq.pop();
		if (!connect.connected(e.to, e.from))
		{
			//printf("edges: %d <--> %d w %d cluster %d\n", e.to, e.from, e.weight, connect.getCount());
			connect.union_path(e.to, e.from);
		}
	}

	return connect.getCount();
}

int main(int argc, char** argv)
{
	printf("%s\n", argv[1]);
	FILE* fp = fopen(argv[1], "r");
	int nv;
	int nbits;
	fscanf(fp, "%d %d", &nv, &nbits);

	printf("nv = %d nbits = %d\n", nv, nbits);

	std::vector<std::vector<bool> > data;
	std::unordered_map<std::vector<bool>, int> hashTable;

	int count = 0;
	for (int i=0; i<nv; i++)
	{
		std::vector<bool> vertex(nbits);
		for (int id=0; id<nbits; id++)
		{
			int bit;
			fscanf(fp, "%d", &bit);
			vertex[id] = (bool)bit;
		}
		if (hashTable.count(vertex) == 0)
		{
			data.push_back(vertex);
			std::pair<std::vector<bool>, int> thisVertex(vertex, count);
			count++;
			hashTable.insert(thisVertex);
		}
	}
	printf("reading finished\n");
	printf("#of vertices = %d \n", count);

	nv = count;

	printf("hashTable: size %lu bucked count %lu\n", hashTable.size(), hashTable.bucket_count());
	printf("vector size = %lu\n", data.size());

	fclose(fp);

	//UF connect(count);

	DiGraph P(nv);

	printf("preparing...\n");
	auto end = hashTable.end();
	//Draw links between 2-differences
	for (int i=0; i<nv; i++)
	{
		int counti = 0;
		std::vector<bool> s = data[i];

		for (int j = 0; j<nbits; j++)
		{
			s[j] = !s[j];
			for (int k = j; k<nbits; k++)
			{
				if (k != j)	{ s[k] = !s[k];}
				auto iter = hashTable.find(s);
				if (k != j)	{ s[k] = !s[k];}

				if (iter != end)
				{
					counti++;
					int index = iter->second;

					if (index > i)
					{
						Edge e;
						e.from = i;
						e.to = index;
						if (k == j)
							e.weight = 1;
						else
							e.weight = 2;
						P.addEdge(e);
						//connect.union_path(i, index);
					}
				}
				else
				{
					continue;
				}
			}
			s[j] = !s[j];
		}
		//printf("%d : count = %d\n", i, counti);
	}

	cluster kruskal(P, nv);
	int answer = kruskal.maxDistance(3);
	//int answer = connect.getCount();
	printf("answer = %d\n", answer);
	
	return 0;
}

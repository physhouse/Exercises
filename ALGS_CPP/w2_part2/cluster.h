#ifndef _CLUSTER_H_
#define _CLUSTER_H_

#include "digraph.h"
#include <vector>
#include <queue>
#include "uf.h"


struct Compare
{
	bool operator()(const Edge& l, const Edge& r)
	{
		return l.weight > r.weight;
	}
};
 
class cluster
{
public:
	cluster(DiGraph &P, int numVertices);
	int maxDistance(int clusterSize);

private:
	DiGraph G;
	UF 		connect;
	std::priority_queue<struct Edge, std::vector<struct Edge>, Compare>	pq;
};

#endif


#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_

#include "graph.h"
#include <queue>
#include <vector>

struct Compare
{
	bool operator()(const Neighbor& l, const Neighbor& r)
	{
		return l.weight > r.weight;
	}
};

class Dijkstra
{
public:
	Dijkstra(Graph& p);
	void Solve();
	void Scan(int nV);

private:
	Graph G;
	int left;
	std::vector<int> dist;
	//std::priority_queue<int, std::vector<int>, std::greater<int> > pq;
	std::vector<bool> visited;
};

#endif


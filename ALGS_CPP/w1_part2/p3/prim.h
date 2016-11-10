#ifndef _PRIM_H_
#define _PRIM_H_

#include "digraph.h"
#include <queue>
#include <vector>

struct Compare
{
	bool operator()(const Edge& l, const Edge& r)
	{
		return l.weight > r.weight;
	}
};

class Prim
{
public:
	Prim(DiGraph& p);
	int Solve();
	void runPrim(int nv);
	void scan(int nv);

private:
	DiGraph G;
	int	weights;
	std::queue<struct Edge> mst;
	std::priority_queue<struct Edge, std::vector<struct Edge>, Compare> pq;
	std::vector<bool> marked;
};

#endif


#include "prim.h"
#include "assert.h"

Prim::Prim(DiGraph& P) : G(P)
{
	int nV = G.getVertices();
	printf("nV = %d\n", nV);

	marked.resize(nV);
	for (int i=0; i<nV; i++)
		marked[i] = false;

	weights = 0;
}

int Prim::Solve()
{
	for (int i=0; i<G.getVertices(); i++)
	{
		if (!marked[i])
			runPrim(i);
	}
	return weights;
}

void Prim::runPrim(int nv)
{
	scan(nv);
	while (!pq.empty())
	{
		Edge e = pq.top();
		pq.pop();
		
		int n1 = e.from - 1;
		int n2 = e.to - 1;
		if (marked[n1] && marked[n2])
			continue;

		weights += e.weight;
		mst.push(e);

		if (!marked[n1]) scan(n1);
		if (!marked[n2]) scan(n2);
	}
}

void Prim::scan(int nv)
{
	assert(!marked[nv]);

	marked[nv] = true;
	for (Edge e : G.adj(nv))
	{
		int other;
		if (e.from == nv + 1) other = e.to - 1;
		else
			other = e.from - 1;
		if (!marked[other]) pq.push(e);
	}
}


int main()
{
	FILE* fp = fopen("edges.txt", "r");
	int nV, nE;
	fscanf(fp, "%d %d", &nV, &nE);
	DiGraph G(nV);
	int sum = 0;
	struct Edge e;
	for (int i=0; i<nE; i++)
	{
		fscanf(fp, "%d %d %d", &e.from, &e.to, &e.weight);
		G.addEdge(e);
		sum += e.weight;
	}
	fclose(fp);
	printf("sum = %d\n", sum);
	
	Prim pm(G);
	int result = pm.Solve();
	printf("Result = %d\n", result);
	return 0;
}

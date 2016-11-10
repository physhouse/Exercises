#include <list>
#include <vector>
#include <cstdlib>
#include <cstdio>

struct Edge
{
	int	end_A;
	int end_B;
};

class Graph
{
private:
	int	nVertices;
	int nEdges;
	std::vector<std::list<int> > adjList;
	std::vector<struct Edge>	Edges;

public:
	Graph(int);
	void addEdge(int, int);
	int  myEdges(int);
	void combine(int);
	int  getEdges();
	int  getVertices();
	void append();
};


Graph::Graph(int num)
{
	nVertices = num;
	nEdges = 0;
	adjList.resize(num);
}

void Graph::append()
{
	Edge e;
	e.end_A = 999;
	e.end_B = 999;

	Edges.push_back(e);
}

int Graph::getEdges()
{
	return nEdges;
}

int Graph::getVertices()
{
	return nVertices;
}

void Graph::addEdge(int i, int j)
{
	Edge ei;
	ei.end_A = i;
	ei.end_B = j;

	nEdges++;
	Edges.push_back(ei);

	adjList[i].push_back(j);
	adjList[j].push_back(i);
}

void Graph::combine(int i)
{
	Edge e = Edges[i];
	int end_A = e.end_A;
	int end_B = e.end_B;

	//combine enda and endb
	int keep = (end_A < end_B) ? end_A : end_B; //keep the smaller one
	int gone = (end_A < end_B) ? end_B : end_A;

	//First Step: Remove the self loops
	adjList[gone].remove(keep);
	adjList[keep].remove(gone);
	/*printf("-------\n");
	for (auto it = Edges.begin(); it != Edges.end(); it++)
	{
		printf("%d %d\n", it->end_A, it->end_B);
	}
	printf("-------\n");*/

	for (auto it = Edges.begin(); it != Edges.end(); it++)
	{
		//printf("#edges %lu\n", Edges.size());
		if ((it->end_A == keep && it->end_B == gone) || (it->end_A == gone && it->end_B == keep))
		{
			//printf("entering\n");
			//printf("delete %d -- %d\n", it->end_A, it->end_B);
			Edges.erase(it);
			it--;
			nEdges--;
		}
		else
		{
			if (it->end_A == gone && it->end_B != keep)
			{
				it->end_A = keep;
			}
			if (it->end_B == gone && it->end_A != keep)
			{
				it->end_B = keep;
			}
		}
	}
	
	//print
	/*printf("-------\n");
	for (auto it = Edges.begin(); it != Edges.end(); it++)
	{
		printf("%d %d\n", it->end_A, it->end_B);
	}
	printf("-------\n");*/
	
	//Merge
	//printf("merging\n");
	for (auto iter = adjList[gone].begin() ; iter != adjList[gone].end(); iter++)
	{
		int item = *iter;
		for (auto ii = adjList[item].begin(); ii != adjList[item].end(); ii++)
		{
			if (*ii == gone)
			{
				*ii = keep;
				adjList[keep].push_back(item);
				break;
			}
		}
	}
	
	adjList[gone].clear();

	/*printf("keep %d gone %d : ", keep, gone);
	for (auto it = adjList[keep].begin(); it != adjList[keep].end(); it++)
	{
		printf("%d ", *it); 
	}
	printf("\n");*/
	nVertices--;
}

int Graph::myEdges(int i)
{
	return adjList[i].size();
}

int main(int argc, char** argv)
{
	int min = 10000;
	for (int i=0; i<40000; i++)
	{
	FILE* fp = fopen(argv[1], "r");
	int	read;
	char* line = NULL;
	size_t len = 0;

	Graph G(atoi(argv[2]));
	int sum_degree = 0;
	while((read = getline(&line, &len, fp)) != -1)
	{
		//printf("%s", line);
		int degree = 0;
		char* token = strtok(line, "\t");
		int iline = atoi(token);
		//printf("%d : ", iline);
		token = strtok(NULL, "\t");
		while (token)
		{
			int other = atoi(token);
			//printf("%d ", other);
			if (other > iline) G.addEdge(iline - 1, other - 1);
			token = strtok(NULL, "\t\n");
			degree++;
		}
		//printf("\n");
		//printf("vertex %d : degree = %d\n", iline, G.myEdges(iline - 1));
		sum_degree += G.myEdges(iline - 1);
	}
	fclose(fp);
	G.append();

	//printf("nEdges = %d, nVertices = %d degrees = %d\n", G.getEdges(), G.getVertices(), sum_degree);
	while (G.getVertices() > 2)
	{
		int range = G.getEdges();
		int entry = rand() % range;
		G.combine(entry);
		if (G.getEdges() < min)
			min = G.getEdges();
	}
	printf("min = %d\n", min);
	}
	return 0;
}

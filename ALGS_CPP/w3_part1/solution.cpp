#include <list>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include "linklist.h"

class Graph
{
private:
	int	nVertices;
	int nEdges;
	std::vector<std::list<struct EdgeNode*> >	adjList;
	EdgeList	Edges;

public:
	Graph(int);
	void addEdge(int, int);
	int  myEdges(int);
	void combine(int);
};

Graph::Graph(int num)
{
	nVertices = num;
	adjList.resize(num);
}

void Graph::addEdge(int i, int j)
{
	Edge ei;
	ei.end_A = i;
	ei.end_B = j;

	Edge ej;
	ej.end_A = j;
	ej.end_B = i;

	adjList[i].push_back(ei);
	adjList[j].push_back(ej);

	nEdges++;
	Edges.push_back(ei);
}

void Graph::combine(int i)
{
	Edge e = Edges[i];
	int end_A = e.end_A;
	int end_B = e.end_B;
	Edges.erase(Edges.begin() + i + 1);
	nEdges
}

int Graph::myEdges(int i)
{
	return adjList[i].size();
}

int main(int argc, char** argv)
{
	FILE* fp = fopen(argv[1], "r");
	int	read;
	char* line = NULL;
	size_t len = 0;

	Graph G(200);
	while((read = getline(&line, &len, fp)) != -1)
	{
		//printf("%s", line);
		int degree = 0;
		char* token = strtok(line, "\t");
		int iline = atoi(token);
		printf("%d : ", iline);
		token = strtok(NULL, "\t");
		while (token)
		{
			int other = atoi(token);
			printf("%d ", other);
			if (other > iline) G.addEdge(iline - 1, other - 1);
			token = strtok(NULL, "\t\n");
			degree++;
		}
		printf("\n");
		printf("vertex %d : degree = %d\n", iline, G.myEdges(iline - 1));
	}
	fclose(fp);


	return 0;
}

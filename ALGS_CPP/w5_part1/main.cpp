#include <cstdlib>
#include "graph.h"
#include "dijkstra.h"
#include <cstdio>
#include <cstring>
#include <vector>
#include <list>
#include <queue>

struct Neighbor  process_entry(char* str)
{
	char* pch = strchr(str, ',');
	int length = (int)(pch - str);

	char num[length+1];
	memcpy(num, str, length);
	num[length] = '\0';

	int str_len = strlen(str);
	length = str_len - length - 1;
	char weight[length+1];
	memcpy(weight, pch+1, length);
	weight[length] = '\0';

	struct Neighbor ret;
	ret.id = atoi(num) - 1;
	ret.weight = atoi(weight);

	return ret;
}

int main(int argc, char** argv)
{
	FILE* fp = fopen(argv[1], "r");
	ssize_t read;
	size_t len = 0;
	char* line = NULL;


	Graph G(200);

	while ((read = getline(&line, &len, fp)) != -1)
	{
		//printf("Retrieved line of length %zu :\n", read);
		char* token;
		token = strtok(line, " \t\n");
		int my_entry = atoi(token) - 1;
		token = strtok(NULL, " \t\n");

		while (token != NULL)
		{
			int length = strlen(token);
			if (length > 1)
			{
				struct Neighbor n;
				n = process_entry(token);
				G.addEdge(my_entry, n);
				//printf("%d,%d\t", n.id, n.weight);
			}
			token = strtok(NULL, " \t\n");
		}
		//printf("\n");
		auto list = G.adj(my_entry);
		int size_this = list.size();
		printf("size %d : %d\n", my_entry, size_this);
	}

	//G.printGraph();
	//check if the graph is correctly built
	/*printf("checking\n");
	for (int i=0; i<200; i++)
	{
		printf("%d\t", i+1);
		for (auto j : adjList[i])
		{
			printf("%d,%d\t", j.id, j.weight);
		}
		printf("\n");
	}*/

	Dijkstra D(G);
	D.Solve();

	return 0;
}

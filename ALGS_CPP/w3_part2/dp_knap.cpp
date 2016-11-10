#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>

#define MAX(a,b) (a>b) ? a : b

int main(int argc, char** argv)
{
	FILE* fp = fopen(argv[1], "r");
	int capacity;
	int nitems;
	fscanf(fp, "%d %d", &capacity, &nitems);

	std::vector<int> F(capacity + 1, 0);
	std::vector<int> W(nitems);
	std::vector<int> V(nitems);

	for (int i=0; i<nitems; i++)
	{
		fscanf(fp, "%d %d", &V[i], &W[i]);
	}
	fclose(fp);

	for (int i=0; i<nitems; i++)
	{
		for (int v = capacity; v>0; v--)
		{
			if ( v < W[i] )
			{
				continue;
			}
			else
				F[v] = MAX(F[v], F[v-W[i]] + V[i]);
		}
	}

	printf("answer = %d\n", F[capacity]);

}

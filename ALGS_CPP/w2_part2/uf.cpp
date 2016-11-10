#include <vector>
#include "uf.h"

UF::UF(int num)
{
	count = num;
	parent.resize(count);
	rank.resize(count);

	for (int i=0; i<count; i++)
	{
		parent[i] = i;
		rank[i] = 0;
	}
}

void UF::union_path(int i, int j)
{
	int iroot = find(i);
	int jroot = find(j);

	if (iroot == jroot)
		return;

	if (rank[iroot] < rank[jroot])
	{
		parent[iroot] = jroot;
	}
	else if (rank[iroot] > rank[jroot])
	{
		parent[jroot] = iroot;
	}
	else
	{
		parent[jroot] = iroot;
		rank[iroot]++;
	}

	count--;
}

int UF::find(int p)
{
	int i = p;
	while (i != parent[i])
	{
		parent[i] = parent[parent[i]];  //Path Compression
		i = parent[i];
	}
	return i;
}

bool UF::connected(int i, int j)
{
	return find(i) == find(j);
}

int UF::getCount()
{
	return count;
}

/*int main()
{
	UF uf(7);
	uf.union_path(1,2);
	uf.union_path(5,6);
	uf.union_path(2,6);
	printf("is connected? %d\n", uf.connected(1,6));
	printf("is connected? %d\n", uf.connected(1,3));
	printf("root of 2 %d\n", uf.find(2));
	printf("root of 6 %d\n", uf.find(6));
	printf("count = %d\n", uf.getCount());
	return 0;
}*/

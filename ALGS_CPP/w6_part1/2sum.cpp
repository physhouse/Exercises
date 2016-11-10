#include <cstdlib>
#include <cstdio>
#include <unordered_set>
#include <vector>

int main(int argc, char** argv)
{
	FILE* fp = fopen(argv[1], "r");
	std::vector<long long> data;
	for (int i=0; i<1000000; i++)
	{
		long long entry;
		fscanf(fp, "%lld", &entry);
		data.push_back(entry);
	}

	//using hash set
	int sum = 0;
	std::unordered_set<long long> map;
	for (int i=0; i<1000000; i++)
		map.insert(data[i]);

	printf("size = %lu\n", map.size());
	for (long long t = -10000; t<=10000; t++)
	{
		for (long long i=0; i<1000000; i++)
		{
			auto it = map.find(t - data[i]);
			if (it != map.end() )
			{
				if (*it == data[i])
					continue;
				else
				{
					sum = sum + 1;
					break;
				}
			}
		}
		printf("finishing %lld sun = %d\n", t, sum);
	}

	printf("answer = %d\n", sum);

}

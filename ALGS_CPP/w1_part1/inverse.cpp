#include <cstdlib>
#include <cstdio>
#include <vector>

unsigned int countSplit(std::vector<int> &data, int start, int end)
{
	int mid = (start + end) / 2;
	std::vector<int> left(data.begin()+start, data.begin()+mid+1);
	std::vector<int> right(data.begin()+mid+1, data.begin()+end+1);

	//printf("end = %d start = %d ls = %d rs = %d\n", end, start, (int)left.size(), (int)right.size());
	int i=0, j=0;
	unsigned int count = 0;
	int k = start;

	while (i<left.size() && j<right.size())
	{
		if (left[i] < right[j])
		{
			data[k++] = left[i++];
		}
		else
		{
			count = count + left.size() - i;
			data[k++] = right[j++];
		}
	}

	while (i < left.size())
	{
		data[k++] = left[i++];
	}
	while (j < right.size())
	{
		data[k++] = right[j++];
	}

	//printf("count = %u, start %d, end %d\n", count, start, end);
	return count;
}

unsigned int countInverse(std::vector<int> &data, int start, int end)
{
	//printf("end = %d start = %d\n", end, start);
	if (end - start == 0) return 0;
	int mid = (start + end) / 2;
	unsigned int x = countInverse(data, start, mid);
	unsigned int y = countInverse(data, mid+1, end);
	unsigned int z = countSplit(data, start, end);
	return x + y + z;
}

int main()
{
	FILE* fp = fopen("IntegerArray.txt", "r+");
	int size = 100000;
	//FILE* fp = fopen("test.txt", "r+");
	//int size = 10;
	std::vector<int> data(size);

	for (int i=0; i<size; i++)
	{
		fscanf(fp, "%d", &data[i]);
	}

	printf("size = %d\n", size);

	unsigned int stat = countInverse(data, 0, size - 1);
	printf("Result = %u\n", stat);
	return 0;
}

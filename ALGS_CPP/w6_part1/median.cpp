#include <cstdlib>
#include <cstdio>
#include <queue>
#include <vector>

int main(int argc, char** argv)
{
	FILE* fp = fopen(argv[1], "r");
	std::vector<int> data;
	data.resize(atoi(argv[2]));

	for (int i=0; i<data.size(); i++)
	{
		fscanf(fp, "%d", &data[i]);
	}

	std::priority_queue<int> heap_max;
	std::priority_queue<int, std::vector<int>, std::greater<int> > heap_min;
	
	int sum_median = data[0] % 10000;

	int smaller = (data[0] < data[1]) ? data[0] : data[1];
	int bigger = (data[0] + data[1]) - smaller;

	heap_max.push(smaller);
	heap_min.push(bigger);

	sum_median += smaller % 10000;

	printf("initialization finished\n");

	for (int i=2; i<data.size(); i++)
	{
		if (data[i] < heap_max.top())
			heap_max.push(data[i]);
		else if (data[i] > heap_min.top())
			heap_min.push(data[i]);
		else  // in the middle?
		{
			heap_max.push(data[i]);
		}
		// Rebalance the two heap
		
		while (heap_max.size() < heap_min.size())
		{
			int temp = heap_min.top();
			heap_min.pop();
			heap_max.push(temp);
		} // Make sure l(d) >= l(t)

		while (heap_min.size() < heap_max.size() - 1)
		{
			int temp = heap_max.top();
			heap_max.pop();
			heap_min.push(temp);
		} // Make sure l(t) >= l(d) -1

		printf("top: %d bottom : %d\n", heap_min.top(), heap_max.top());
		sum_median = (sum_median + heap_max.top()) % 10000;
	}

	printf("answer = %d\n", sum_median);
	return 0;
}

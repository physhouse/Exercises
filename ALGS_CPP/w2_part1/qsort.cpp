#include <cstdlib>
#include <cstdio>

template<typename T>
void swap(T* a, int i, int j)
{
	T temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

template<typename T>
int median(T* a, int i, int j, int k)
{
	if (a[i] <= a[j])
	{
		if (a[j] <= a[k])
			return j;
		else 
		{
			if (a[i] <= a[k])
				return k;
			else
				return i;
		}
	}
	else
	{
		if (a[i] <= a[k])
			return i;
		else
		{
			if (a[k] >= a[j])
				return k;
			else
				return j;
		}
	}
}

template<typename T>
int partition(T* a, int start, int end)
{
	//int pivot = median(a, start, end, start + (end - start)/2);
	//swap(a, start, pivot);
	//swap(a, start, end);

	int i = start + 1;
	int j = start + 1;
	for(; j<=end; j++)
	{
		if (a[j] > a[start])
			continue;
		else
		{
			swap(a, i, j);
			i++;
		}
	}
	swap(a, start, i - 1);
	return i - 1;
}

template<typename T>
int quickSort(T* a, int start, int end)
{
	if (start >= end)
		return 0;

	int p = partition(a, start, end);
	printf("p = %d a[p] = %d\n", p, a[p]);
	int s1 = quickSort(a, start, p-1);
	int s2 = quickSort(a, p+1, end);
	return s1 + s2 + (end - start);
}

int main()
{
	FILE* fp = fopen("QuickSort.txt", "r+");
	int *a = new int(10000);
	for (int i=0; i<10000; i++)
	{
		fscanf(fp, "%d", &a[i]);
	}
	fclose(fp);

	printf("Sorted:\n");
	int compare = quickSort(a, 0, 9999);
	for (int i=0; i<10000; i++)
		printf("%d\n", a[i]);
	
	printf("compares = %d\n", compare);
	return 0;
}

#include <vector>
#include <cstdlib>
#include <cstdio>
#include <cmath>

using namespace std;

int num_ones(int k, int n)
{
	int n1 = 0;
	for (int i=0; i<n; i++)
	{
		int bit = k & 0x1;
		if (bit == 1)
			n1++;

		k = k >> 1;
	}
	return n1;
}

vector<int> index_ones(int k, int n)
{
	vector<int> indices;
	indices.push_back(0);

	for (int i=0; i<n; i++)
	{
		int bit = k & 0x1;
		if (bit == 1)
		{
			indices.push_back(i + 1);
		}
		k = k >> 1;
	}
	return indices;
}

int main()
{
	int n = 24;
	int size = 1 << 24;
	printf("size = %d\n", size);
	vector<vector<int> > set;
	set.resize(n + 1);

	printf("24: ones = %d\n", num_ones(24, n));
	printf("size: ones = %d\n", num_ones(size - 1, n));
	vector<vector<double> > dp;
	dp.resize(size);
	
	for (int i=0; i<size; i++)
	{
		int n1 = num_ones(i, n);
		set[n1].push_back(i);
		dp[i].resize(n + 1);
	}

	for (int i=0; i<n+1; i++)
	{
		printf("size %d = %lu\n", i, set[i].size());
	}
	printf("end = %d\n", set[24][0]);

	//readin the file
	vector<vector<double> > x;
	vector<vector<double> > distance;
	distance.resize(n+1);
	x.resize(n+1);

	for (int i=0; i<n+1; i++)
	{
		distance[i].resize(n+1);
		x[i].resize(2);
	}

	FILE* fp = fopen("tsp.txt", "r");

	int nV;
	fscanf(fp, "%d", &nV);
	for (int i=0; i<n+1; i++)
		fscanf(fp, "%lf %lf", &x[i][0], &x[i][1]);

	for (int i=0; i<n+1; i++)
	{
		for (int j=0; j<n+1; j++)
		{
			double dx = x[i][0] - x[j][0];
			double dy = x[i][1] - x[j][1];
			distance[i][j] = sqrt(dx * dx + dy * dy);
			printf("%lf\t", distance[i][j]);
		}
		printf("\n");
	}
	//initialization of dp matrix
	dp[0][0] = 0.0;
	for (int i=1; i<size; i++)
		dp[i][0] = INFINITY;


	printf("entering dynamic programming\n");
	//start the dynamic programming
	for (int i=1; i<n+1; i++)
	{
		if (i == n)
			printf("set[24] = %d\n", set[i][0]);

		for (int jj=0; jj<set[i].size(); jj++)
		{
			int myset = set[i][jj];
			vector<int> vSet = index_ones(myset, n);

			for (auto j : vSet)
			{
				if (j != 0)
				{
					double min = INFINITY;
					int offset = 1 << (j-1);
					int set_minusj = myset - offset;

					for (auto k : vSet)
					{
						if (k != j)
						{
							double this_k = distance[k][j] + dp[set_minusj][k];
							if (this_k < min)
								min = this_k;
						}
					}

					dp[myset][j] = min;
				}
			}
		}
	}

	printf("finishing dynamic programming\n");
	double min = INFINITY;
	for (int j=1; j<25; j++)
	{
		double thisj = dp[size - 1][j] + distance[j][0];
		if (thisj < min)
			min = thisj;
	}

	printf("answer = %lf\n", min);

	return 0;
}

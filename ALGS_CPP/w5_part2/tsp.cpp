#include <cstdlib>
#include <cstdio>
#include <vector>
using namespace std;
#define INFINITY 9.99e20

int main()
{
	vector<vector<double> > a;
	int n = 24;
	int setSize = (int)pow(2.0, (double)n);

	a.resize(setSize);
	for (int i=0; i<setSize; i++)
	{
		a[i].resize(n + 1);
		for (int j=0; j<n; j++)
			a[i][j] = INFINITY;
	}

	permutation(a, n);
}

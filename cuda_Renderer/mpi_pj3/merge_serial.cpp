#include <iostream>
#include <cstdlib>
#include "merge_mpi.h"

using namespace std;

void MergeMPI::MergeArray(double* Array, double* Temp, int first, int mid, int last)
{
  int i, j, k;
  i = 0;
  j = first;
  k = mid + 1;
  
  while (j <= mid && k <= last)
  {
    if (Array[j] < Array[k])
    {
	Temp[i++] = Array[j++];
    }
    else
    {
	Temp[i++] = Array[k++];
    }
  }

  while (j<=mid)
  {
	Temp[i++] = Array[j++];
  }
  
  while (k<=last)
  {
	Temp[i++] = Array[k++];
  }

  for (int index = 0; index < i; index++)
  {
	Array[first+index] = Temp[index];
  }
}

/*void printArray(double* A, int length)
{
   for (int i=0; i<length; i++)
   {
	printf("%lf   ", A[i]);
   }
   printf("\n");
}*/

void MergeMPI::MergeSort()
{
  //Non-Iteratively
  int fir = 0;
  int end = size_own-1;
  int s = 2;
  int n = end-fir+1;
  double* Temp = new double[n];
  double* A = Data_own;

  while (s <= n)
  {
     int k=0;
     while (k+s<=n)
     {
       mergeArray(fir+k, fir+k+(s-1)/2, fir+k+s-1, A, Temp);
       k = k + s;
     }
     if (fir+k < end)
     {
     	mergeArray(fir+k, fir+k+(s-1)/2, end, A, Temp);
     }
     s = s*2;
  }
  if (s != 2*n)
  mergeArray(fir, s/2-1, end, A, Temp);
}



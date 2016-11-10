#include <iostream>
#include <cstdlib>
#include "mergesort.h"

using namespace std;

void mergeArray(int first, int mid, int last, double* Array, double* Temp)
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

void printArray(double* A, int length)
{
   for (int i=0; i<length; i++)
   {
	printf("%lf   ", A[i]);
   }
   printf("\n");
}

void mergesort(double* A, int fir, int end, double* Temp)
{
   //Iteratively
   /*if (fir == end)
      return;

   int first = fir;
   int last = end;
   int mid = (end+fir)/2;

   mergesort(A, first, mid, Temp);
   mergesort(A, mid+1, last, Temp);
   mergeArray(first, mid, last, A, Temp);*/

  //Non-Iteratively
  int s = 2;
  int n = end-fir+1;
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


/*int main(int argc, char** argv)
{

  double A[17] = {0,7,8,9,1,2,3,4,0,7,8,9,1,2,3,4,-2};
  double* Temp = new double[17];
  mergesort(A,0,16,Temp);
  printArray(A,17);

  delete[] Temp;
  return 0;
}*/

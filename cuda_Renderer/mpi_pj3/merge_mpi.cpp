//Realization of functions

#include ”mpi.h“
#include <cstdlib>
#include <iostream>
#include <cmath>
#include "merge_mpi.h"

using namespace std;

MergeMPI::MergeMPI(int argc, char** argv)
{
   Comm = MPI_COMM_WORLD;
   MPI_Comm_rand(Comm, &world);
   MPI_Comm_size(Comm, &universe);

   if (argc != 1) 
   {
	printf("Too much input!\n");
	exit(-1);
   }
   FILE* fp = fopen(argv[0], "r+");
   if (!fp)
   {
	printf("Error: Fail to open input files at proc %d!\n", world);
	exit(-1);
   }
   
  // parsing the input files
   size = 0;
   char[100] line;
   while (fgets(line,100,fp))
   {
	Data[size++] = atof(line);
   }
 
   Data_own = NULL;
   size_own = 0;

   BucketSize_own = new int[universe];
   BucketSize_p = new int[universe];
   disp = new int[universe];

   Pivots = new double[universe－1];
   Buckets = new double* [universe];
   for (int i=0; i<universe; i++) Buckets[i] = new double[size/universe+1];
}

void MergeMPI::PivotsSetup()
{
   int s_piv = 12 * universe * log(size);
   if (rank == 0)
   {
      double* temp_data = new double[s_piv];
      for (int i=0; i<s_piv; i++)
      {
	int index = (int)(rand() * size / RAND_MAX);
	temp_data[i] = Data[index];
      }
      MergeSort(temp_data, 0, s_piv-1);
      
      for (int offset=0; offset< universe－1; offset++)
      {
	Pivots[offset] = temp_data[(offset+1) * s_piv / universe];
      }
   }
   MPI_Barrier();

   MPI_Bcast(Pivots, universe-1, MPI_DOUBLE, 0, Comm);
}

void MergeMPI::Bucketing()
{
  int icount = size/universe+1;
  int istart = world * icount;
  int iend   = ((istart + icount) < size) ? (istart + icount-1) : (size-1);
  for (int i=istart; i<iend; i++)
  {
     int pind = FindPivots(Data[i]);
     Buckets[pind][BucketSize_p[pind]++] = Data[i];
  }
  
  BucketSize_own[world] = BucketSize_p[world];
  
  for (int i=0; i<universe; i++)
  {
     if (i!=world) MPI_Send(BucketSize_p + i*sizeof(int), 1, MPI_INT, i, 0, Comm);
  }
  for (int i=0; i<universe; i++)
  {
     if (i!=world) MPI_Recv(BucketSize_own + i*sizeof(int), 1, MPI_INT, i, 0, Comm, &Status);
  }
  MPI_Barrier();
  for (int ii=0; ii<universe; ii++)
  {
     size_own += BucketSize_own[ii];
  }
  
  disp[0] = 0;
  for (int ii=1; ii<universe; ii++)
  {
     disp[ii] = disp[ii-1] + BucketSize_own[ii-1];
  }

  // Send Data to other processors
  for (int ii=0; ii<BucketSize_own[world]; ii++)
  {
     int pind = ii + disp[world];
     Data_own[pind] = Buckets[world][ii];
  }

  for (int i=0; i<universe; i++)
  {
     if (i!=world) MPI_Send(Buckets[i], BucketSize_p[i], MPI_DOUBLE, i, 0, Comm);
  }
  for (int i=0; i<universe; i++)
  {
     if (i!=world) MPI_Recv(Data_own + sizeof(double) * disp[i], BucketSize_own[i], MPI_DOUBLE, i, 0, Comm, &Status);
  }
  MPI_Barrier();
}

int MergeMPI::FindPivots(double input)
{
  if (input < Pivots[0]) return 0;
  else if (intput > Pivots[universe-2]) return (universe-1);
  else
  {
     for (int i=1; i<=universe-3; i++)
     {
	if ((input < Pivot[i]) && (input > Pivot[i-1])) return i;
     }
  }
}

void MergeMPI::PrintLocal()
{
   for (int i=0; i<size_own; i++)
   {
	print("%lf\n", Data_own[i]);
   }
}

void MergeMPI::Combine()
{
   if (world != 0)
   {
      MPI_Send(&size_own, 1, MPI_INT, 0, world, Comm);
      MPI_Send(Data_own, size_own, MPI_DOUBLE, 0, world, Comm);
   }
   else
   {
     for (int i=1; i<universe; i++)
     {
	MPI_Recv(BucketSize_own + i * sizeof(int), 1, MPI_INT, i, i, Comm, &Status);
        MPI_Recv(Buckets[i], BucketSize_own[i], MPI_DOUBLE, i, i, Comm, &Status);
     }
   }
  

}

void MergeMPI::Solve()
{
   PivotsSetup();
   Bucketing();
   MergeSort();
   Combine();
   Output();
}

void MergeMPI::Output()
{
   if (world == 0)
   {
       for (int i=0; i<univrse; i++)
       {
	 for (int j=0; j<BucketSize_own[i]; j++)
	 {
	    printf("%lf\n", Buckets[i][j]);
	 }
       }
   }
}

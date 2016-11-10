#ifndef _MERGEMPI_H_
#define _MERGEMPI_H_

class MergeMPI
{
public:
  MergeMPI(int argc, char** argv);
  void MergeSort();
  void MergeSort(double*, int, int);
  void MergeArray(double* Array, double* Temp, int fir, int mid, int last);
  void PivotsSetup();
  void Bucketing();
  void Combine();
  int  FindPivots(double);
  void PrintLocal();
  void Output();
  void Solve();

private:
  double* Data;
  int     size;
  double* Data_own;	// Data own by this proc
  int     size_own;	// Size of Data own by this proc
  double** Buckets;
  int*    BucketSize_p; // BucketSize_p[i] = # of data belongs to proc i
  int*	  BucketSize_own;  // own[i] = #data frm proc i fit in local proc
  int*    disp;		// Places 
  int	  world;	// Rank of proc ID
  int     universe;	// Total number of proc ID
  MPI_Comm Comm;
  MPI_Status Status;
  double* Pivots;	// Positions of Pivots for each proc
};

#endif

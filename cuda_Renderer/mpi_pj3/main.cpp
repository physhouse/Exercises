#include <iostream>
#include "merge_mpi.h"
using namespace std;

int main(int argc, char** argv)
{
   MPI_Init();
   MergeMPI* m_mpi(argc, argv);
   m_mpi->solve();
   
   return 0;
}

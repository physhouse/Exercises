#include <cuda.h>
#include "cudaListTable.h"
#include "exclusiveScan.h"
#include <stdlib.h>
#include <stdio.h>

void initializeTable(ListTable& table, int entries)
{
  table.count = entries;
  int rounded_length = nextPow2(entries);

  cudaMalloc((void**)&table.size, rounded_length * sizeof(int));
  cudaMemset(table.size, 0, rounded_length * sizeof(int*));
  cudaMalloc((void**)&table.index, rounded_length * sizeof(int));
  cudaMemset(table.size, 0, rounded_length * sizeof(int*));
}

void generateScan(ListTable& table)  //return the total number of entries
{
  int entries = table.count;
  exclusive_scan(table.size, entries, table.index);

  int sum = 0;
  int last = 0;
  cudaMemcpy(&sum, table.index + entries - 1, sizeof(int), cudaMemcpyDeviceToHost);
  cudaMemcpy(&last, table.size + entries - 1, sizeof(int), cudaMemcpyDeviceToHost);

  table.elements = sum + last;
  printf("elements: %d, counts: %d\n", table.elements, table.count);
  cudaFree(table.entry);
  cudaMalloc((void**)&table.entry, sizeof(int) * table.elements);
}

void freeTable(ListTable& table)
{
  cudaFree(table.entry);
  cudaFree(table.index);
  cudaFree(table.size);
}

void copyTable2Host(const ListTable& table, ListTable& hostTable)
{
  hostTable.count = table.count;
  hostTable.elements = table.elements;
  hostTable.size  = (int*) malloc(sizeof(int) * table.count);
  hostTable.index  = (int*) malloc(sizeof(int) * table.count);
  hostTable.entry  = (int*) malloc(sizeof(int*) * table.elements);
  cudaMemcpy(hostTable.size, table.size, table.count * sizeof(int), cudaMemcpyDeviceToHost);
  cudaMemcpy(hostTable.index, table.index, table.count * sizeof(int), cudaMemcpyDeviceToHost);
  cudaMemcpy(hostTable.entry, table.entry, table.elements * sizeof(int), cudaMemcpyDeviceToHost);
}

void deleteHost(ListTable& host)
{
  free(host.entry);
  free(host.index);
  free(host.size);
}

void checkHost(ListTable& host)
{
  for (int i=0; i<host.count; i++)
  {
    int start = host.index[i];
    for (int j=0; j<3; j++)
      printf("%d ", host.entry[start + j]);
    printf(" -> %d\n", i);
  } 
}

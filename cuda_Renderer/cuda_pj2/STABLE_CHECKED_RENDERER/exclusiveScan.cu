#include "cuda.h"
#include "exclusiveScan.h"
#include "stdio.h"

__global__ void excScan(int* device_start, int* device_result, int n)
{
   //Blelloch implementation of exclusive scan
   extern __shared__ int temp[];

   int thid = blockDim.x * blockIdx.x + threadIdx.x;
   int tid  = threadIdx.x;

   temp[2*tid] = device_start[2*thid];
   temp[2*tid + 1] = device_start[2*thid + 1];

   //Up Sweeping
   int offset = 1;
   for (int d = n>>1; d > 0; d >>= 1)
   {
     __syncthreads();
     if (tid < d)
     {
       int a = offset * (2*tid + 1) - 1;
       int b = offset * (2*tid + 2) - 1;
       temp[b] += temp[a];
     }
     offset *= 2;
   }

   if (tid == 0) temp[n-1] = 0;

   //Down Sweeping Algorithms
   offset = n;
   for (int d = 1; d < n; d *= 2)
   {
      __syncthreads();
      if (tid < d)
      {
        //int a = offset * (2*tid + 1) - 1;
        //int b = offset * (2*tid + 2) - 1;

        int a = n - tid * offset - 1;
        int b = n - tid * offset - 1 - offset / 2;

        int tmp = temp[a];
        temp[a] += temp[b];
        temp[b] = tmp;
      }
      offset >>= 1;
   }
   __syncthreads();

   device_result[2*thid] = temp[2*tid];
   device_result[2*thid + 1] = temp[2*tid + 1];
}

__global__ void postSum(int* device_result, int* scanBlocks, int length)
{
   int thid = blockDim.x * blockIdx.x + threadIdx.x;
   int bid = blockIdx.x;

   device_result[2*thid] += scanBlocks[bid];
   device_result[2*thid + 1] += scanBlocks[bid];
}

__global__ void preSum(int* device_start, int* device_result, int* sumBlocks, int n)
{
   int tid = threadIdx.x;
   int bid = blockIdx.x; // Recursive
   //if (tid == 0) sumBlocks[tid] = device_start[n*(tid+1) - 1] + device_result[n*(tid+1) - 1];
   if (tid == 0) sumBlocks[bid] = device_start[n*(bid+1) - 1] + device_result[n*(bid+1) - 1];
}

void exclusive_scan(int* device_start, int length, int* device_result)
{
    /* Fill in this function with your exclusive scan implementation.
     * You are passed the locations of the input and output in device memory,
     * but this is host code -- you will need to declare one or more CUDA 
     * kernels (with the __global__ decorator) in order to actually run code
     * in parallel on the GPU.
     * Note you are given the real length of the array, but may assume that
     * both the input and the output arrays are sized to accommodate the next
     * power of 2 larger than the input.
     */
    int blocksize = 512; //512;
    while (length < 2 * blocksize)
    {
       blocksize /= 2;
    }
    //length = nextPow2(length);
    int nblocks = (length/2 + blocksize - 1) / blocksize;
    int bytesShared = 0;

    int* sumBlocks;
    int* scanBlocks;
    int sizeNext = nextPow2(nblocks);
    cudaMalloc((void**)&sumBlocks, sizeof(int) * sizeNext);
    cudaMalloc((void**)&scanBlocks, sizeof(int) * sizeNext);
    cudaMemset(sumBlocks, 0, sizeof(int) * nblocks);
    cudaMemset(scanBlocks, 0, sizeof(int) * nblocks);

    bytesShared = sizeof(int) * 2 * blocksize;
    excScan<<<nblocks, blocksize, bytesShared>>>(device_start, device_result, 2*blocksize);

    if (nblocks > 1)
    {
      preSum<<<nblocks, blocksize>>>(device_start, device_result, sumBlocks, 2*blocksize);

      exclusive_scan(sumBlocks, nblocks, scanBlocks);

      postSum<<<nblocks, blocksize>>>(device_result, scanBlocks, 2*blocksize);
    }

    cudaFree(sumBlocks);
    cudaFree(scanBlocks);
}

void cudaScan(int* inarray, int length, int* resultarray)
{
  int* device_result;
  int* device_input;
  int rounded = nextPow2(length);
  cudaMalloc((void**)&device_result, sizeof(int) * rounded);
  cudaMalloc((void**)&device_input, sizeof(int) * rounded);
  cudaMemcpy(device_input, inarray, sizeof(int) * length, cudaMemcpyHostToDevice);

  cudaMemcpy(device_result, inarray, sizeof(int) * length, cudaMemcpyHostToDevice); 

  exclusive_scan(device_input, length, device_result);
  
  cudaMemcpy(resultarray, device_result, length * sizeof(int), cudaMemcpyDeviceToHost);
}

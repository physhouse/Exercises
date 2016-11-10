#ifndef _SCAN_H_
#define _SCAN_H_

void exclusive_scan(int* device_start, int length, int* device_result);
void cudaScan(int* inarray, int length, int* resultarray);

static inline int nextPow2(int n)
{
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n++;
    return n;
}

#endif

#!/bin/python

f = open("num.txt", "r")
num = []
for line in f.readlines():
  num.append(int(line))
n = len(num)

def maxsum(start, end):
  if start==end:
     return max(0, num[start])

  mid = (end + start) / 2
  sum_max = num[mid]
  wsum = 0
  for i in range(mid, start-1, -1):
    wsum += num[i]
    if wsum > sum_max:
       sum_max = wsum

  fsum_max = num[mid+1]
  wsum = 0
  for i in range(mid+1, end+1, 1):
    wsum += num[i]
    if wsum > fsum_max:
       fsum_max = wsum

  cross = sum_max + fsum_max

  return max(maxsum(start, mid), maxsum(mid+1, end), cross)
 
print maxsum(0, n-1)

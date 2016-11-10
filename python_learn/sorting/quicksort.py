#!/bin/env python

def quickSort(arr):
   less=[]
   more=[]
   pivotList=[]
 
   if len(arr) <= 1:
      return arr
   else:
     pivot=arr[0]
     for i in arr:
       if i < pivot:
	  less.append(i)
       elif i > pivot:
  	  more.append(i)
       else:
	  pivotList.append(i)

     less=quickSort(less)
     more=quickSort(more)
     return less+pivotList+more

if __name__ == "__main__":
   a=[2,188,39999,-2435,101.324,3,3,3,3,2,2,2,93,-2,-2]
   result=quickSort(a)
   print(result)


#!/bin/env python

def mergeArray(arr, first, middle, last):
   Temp=[]
   i=first
   j=middle+1
   
   while (i<=middle) and (j<=last):
     if arr[i] < arr[j]:
	Temp.append(arr[i])
	i=i+1
     else:
	Temp.append(arr[j])
	j=j+1

   if i<middle:
      Temp.append(arr[i:middle])
   else:
      Temp.append(arr[i])

   if j<last:	
      Temp.append(arr[j:last+1])
   else:
      Temp.append(arr[j])

   arr[first:last+1]=Temp[:]


if __name__== "__main__":
   a=[3,4,5,2,4,6]
   mergeArray(a, 0, 2, 5)
   print(a)


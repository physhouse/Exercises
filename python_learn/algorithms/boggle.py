#!/bin/env/python

list = [['a','b','c','d'],['e','f','g','h'],['i','j','k','l'],['m','n','p','q']]
mark = [[0 for col in range(4)] for row in range(4)]
out = []

def traverse(i, j, n):

  if len(out) >= 5:
    #mark[i][j] = 0
    #out.pop()
    return

  mark[i][j] = 1
  out.append(list[i][j])
  print(out)


  #print(repr(i)+" and "+repr(j))
  #print(mark)
  for offsetx in range(-1,2,1):
    for offsety in range(-1,2,1):
      if (i+offsetx) < n and (i+offsetx) >= 0 and j+offsety < n and j+offsety >= 0:
        if (mark[i+offsetx][j+offsety] == 0):
           traverse(i+offsetx, j+offsety, n)

  mark[i][j] = 0
  out.pop()

traverse(0, 0, 4)

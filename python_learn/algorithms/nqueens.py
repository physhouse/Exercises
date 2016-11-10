position = [-1,-1,-1,-1,-1,-1,-1,-1]

def valid(row, k):
  for i in range(0, row, 1):
    if position[i] == k:
      return False
    elif position[i]+(row-i) == k:
      return False
    elif position[i]-(row-i) == k:
      return False
	
  return True

def putQueen(row, n):
  for k in range(0, n, 1):
    if valid(row, k):
      position[row] = k
      if row == n-1:
        print(position)
      putQueen(row+1, n)
      #position[row] = -1

def nQueens(n):
   putQueen(0, n)

nQueens(8)


#!/usr/env/python

board = [[0 for i in range(6)] for j  in range(6)]

fx = [2,  1,  -1, -2, -2, -1, 1, 2]
fy = [-1, -2, -2, -1, 1,   2, 2, 1]

def valid(i,j):
  if i > 5 or i < 0 or j > 5 or j < 0 or board[i][j] != 0:
    return False
  return True

def knightGo(i, j , number):
  #board[i][j] = number;
  if number == 36:
    for m in range(6):
      print(board[m])
    return

  for k in range(8):
    new_i = i + fx[k]
    new_j = j + fy[k]

    if valid(new_i, new_j):
      board[new_i][new_j] = number+1
      knightGo(new_i, new_j, number+1)
      board[new_i][new_j] = 0
  #board[i][j] = 0

def solve(x,y):
  board[x][y] = 1
  knightGo(x, y, 1)

solve(0,0)

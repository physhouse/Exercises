#!/bin/env/python

class kmp(object):
  def __init__(self,string):
    self.R = 256
    self.length = len(string)
    self.dfa = [[0 for i in range(self.R)] for j in range(self.length)]
    self.dfa[0][ord(string[0])] = 1
    X = 0
    for j in range(1,self.length):
      for c in range(0, self.R):
        self.dfa[j][c] = self.dfa[j][X]

      self.dfa[j][ord(string[j])] = j+1
      X = self.dfa[X][ord(string[j])]

  def match(self, string):
    M = len(string)
    i = 0
    j = 0
    while i < M and j < self.length:
      j = self.dfa[j][ord(string[i])]
      i = i + 1
	
    if j == self.length:
      return i-self.length
    else:
      return -1

if __name__ == '__main__':
   p = kmp("yining")
   print(p.match("sssyininss"))
   print(p.match("uchicagoyiningvothgroup"))


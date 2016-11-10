#!/bin/python
from collections import deque

class Graph(object):
  def __init__(self,*args,**kargs):
     self.node_neighbors={}

  def addnode(self, node):
     if not node in self.nodes():
       self.node_neighbors[node]=[]

  def nodes(self):
     return self.node_neighbors.keys()

  def neighbors(self):
     return self.node_neighbors

  def addnodes(self, nodelist):
     for i in nodelist:
	self.addnode(i)

  def add_edge(self, edge):
     u,v = edge
     self.node_neighbors[u].append(v)
     self.node_neighbors[v].append(u)
    
  def depth_first_search(self, root=None):
     order=[]
     visited={}
     def DFS(node):
        visited[node]=True
	order.append(node)
     	for n in self.node_neighbors[node]:
	   if n not in visited:
	      DFS(n)

     if root:
	DFS(root)

     for n in self.nodes():
	if n not in visited:
	   DFS(n)

     return order

  def dfs_nonrecursive(self, root=None):
     order=[]
     Stack=[]
     visited={}

     Stack.append(root)
     while 1:
       while len(Stack)>0:
	 rr=Stack[-1]
	 if rr not in visited:
	    order.append(rr)
	    visited[rr] = True
	 a=0
         for n in self.node_neighbors[rr]:
	   if n not in visited:
	      Stack.append(n)
	      a=a+1
	      break
	 if (a==0):	
	   Stack.pop()
	
       if len(visited)==len(self.nodes()) :
	 break
       else:
	 for node in self.node_neighbors.keys():
	   if node not in visited:
	      Stack.append(node)
	      break

     return order

  def broad_first_search(self, root=None):
     Queue=deque()
     Queue.append(root)
     order=[]
     visited={}
     visited[root]=True

     while 1:
	while len(Queue)>0:
	  rr = Queue.popleft()
	  order.append(rr)
	  for n in self.node_neighbors[rr]:
	     if n not in visited:
	        Queue.append(n)
		visited[n]=True
	     
        if len(visited)==len(self.nodes()):
	  break
        else:
	  for node in self.node_neighbors.keys():
	    if node not in visited:
	      Queue.append(node)
	      visited[node]=True
	      break

     return order 
	
if __name__ == '__main__':
  g = Graph()
  g.addnode(1)
  g.addnode(2)
  g.addnodes([i+1 for i in range(6)])
  print(g.nodes())

  g.add_edge((1,3))
  g.add_edge((3,4))
  g.add_edge((4,5))
  g.add_edge((1,2))
  print(g.neighbors())

  print(g.dfs_nonrecursive(1)) 
  print(g.depth_first_search(2)) 
  print(g.broad_first_search(1)) 
  print(g.nodes())


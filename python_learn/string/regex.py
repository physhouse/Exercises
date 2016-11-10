class Digraph(object):
  def __init__(self, n):
    self.V = n
    self.E = 0
    self.Neighbors = {}
    for i in range(n):
      self.Neighbors[i] = []

  def addNode(self, node):
    if not node in self.nodes():
      self.Neighbors[node] = []
      self.V = self.V + 1

  def nodes(self):
    return self.Neighbors.keys()

  def addEdge(self, edge):
    u, v = edge
    self.Neighbors[u].append(v)

  def DFS(self, start):
    visited=[False for i in range(self.V)]
    order=[]

	def search(node):
	  visited[node] = True
	  order.append(node)
	  for nb in self.Neighbors[node]:
	    if visited[nb] == False
		  search(nb)

    search(start)
    return order

#if __name__ == '__main__':
 # G = Digraph(5)
  #print(G.nodes())

class NFA(object):
  def __init__(self, regexp):
    M = len(regexp)
	p = []
    self.G = Digraph(M+1)
    self.nodes = regexp
    
    for i in range(M):
      lp = i
      if self.nodes[i] == '(' or self.nodes[i] == '|':
        p.append(i)
      elif self.nodes[i] == ')':
        lp = p.pop()
        if self.nodes[lp] == '|':
          left = p.pop();
          self.G.addEdge(left, lp+1)
          self.G.addEdge(lp, i)
          lp = left
      if i < M-1 and nodes[i+1] == '*':
        G.addEdge(lp, i+1)
        G.addEdge(i+1, lp)
      
      if nodes[i] == '(' or nodes[i] == '*' or nodes[i] == ')':
        G.addEdge(i, i+1)

  def recognize(self, string):
    

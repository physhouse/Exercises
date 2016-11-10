import networkx as nx  

def read(fileName):
    with open(fileName, "r") as f:
        lines = f.readlines()
        array = list(map(int, line.split(" ", 1)) for line in lines[0:])
        return array
  
def process(filename):  
    clauses = read(filename)  
  
    literalCount = 875714
    G=nx.DiGraph()  
    G.add_nodes_from(range(0, literalCount))  
  
    for clause in clauses:  
        G.add_edge(clause[0], clause[1])  
  
    print "Graph creation for %s completed" % filename  
	
    nodes = nx.dfs_postorder_nodes(G)
    print "Order creation for %s completed" % filename  
    for item in nodes:
        print(item)
#components = nx.strongly_connected_components(G)  
  
#   print "Calculation of SSC for %s completed" % filename  
  
#   size = 0
#   for component in components:
 
#size = size + 1
#       print(len(component))

#   print(size)

#for component in filter(lambda component : len(component) > 1, components):  
  
process("test.txt")  

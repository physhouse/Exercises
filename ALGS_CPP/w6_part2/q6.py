import networkx as nx  

def read(fileName):
    with open(fileName, "r") as f:
        lines = f.readlines()
        eCount = int(lines[0])
        array = list(map(int, line.split(" ", 1)) for line in lines[1:])
        return array, eCount  
  
def process(filename):  
    clauses, literalCount = read(filename)  
  
    G=nx.DiGraph()  
    G.add_nodes_from(range(1, literalCount + 1) + range(-literalCount, 0))  
  
    for clause in clauses:  
        G.add_edge(-clause[0], clause[1])  
        G.add_edge(-clause[1], clause[0])  
  
    print "Graph creation for %s completed" % filename  
  
    components = nx.strongly_connected_components(G)  
  
    print "Calculation of SSC for %s completed" % filename  
  
    size = 0
    for component in components:
        size = size + 1

    print(size)

    isSatisfiable = True  
    for component in filter(lambda component : len(component) > 1, components):  
        isSatisfiableComponent = True  
        vertexes = set()  
        for vertex in component:  
            if -vertex in vertexes:  
                isSatisfiableComponent = False  
                break  
            vertexes.add(vertex)  
        if not isSatisfiableComponent:  
            isSatisfiable = False  
            break  
  
    print "%s satisfiable result: %s" % (filename, isSatisfiable)  
    return isSatisfiable  
  
  
process("2sat1.txt")  
process("2sat2.txt")  
process("2sat3.txt")  
process("2sat4.txt")  
process("2sat5.txt")  
process("2sat6.txt") 

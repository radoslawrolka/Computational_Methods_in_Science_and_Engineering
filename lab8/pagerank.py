import networkx as nx

# F_u = u points to v
# B_u = v points to u
# N_u = number of outgoing links from u
# c = normalization factor

def rank(graph, vertex, c=0.85):
    F = graph.out_edges(vertex)
    B = graph.in_edges(vertex)
    N = len(F)
    rank = 0
    for u, v in B:
        rank += graph.nodes[u]['rank'] / len(graph.out_edges(u))
    return (1 - c) + c * rank

def read_graph(filename):
    graph = nx.DiGraph()
    with open(filename, 'r') as f:
        for _ in range(4): f.readline()
        for line in f:
            u, v = line.strip().split()
            graph.add_edge(u, v)
    return graph

if __name__ == '__main__':
    graph = read_graph('p2p-Gnutella04.txt')
    pr = nx.pagerank(graph, alpha=0.85)
    nx.draw_networkx(graph, with_labels=True)